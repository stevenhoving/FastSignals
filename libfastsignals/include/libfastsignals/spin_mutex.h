#pragma once
#include <atomic>

#define ENABLE_YIELD 1
#if ENABLE_YIELD
#include <thread>
#endif // ENABLE_YIELD

namespace is::signals::detail
{

class spin_mutex
{
public:
    spin_mutex() noexcept = default;
    spin_mutex(const spin_mutex&) = delete;
    spin_mutex& operator=(const spin_mutex&) = delete;
    spin_mutex(spin_mutex&&) = delete;
    spin_mutex& operator=(spin_mutex&&) = delete;
#if ENABLE_YIELD == 0
    inline bool try_lock() noexcept
    {
        return !m_busy.test_and_set(std::memory_order_acquire);
    }

    inline void lock() noexcept
    {
        while (!try_lock())
        {
            /* do nothing */;
            std::this_thread::yield();
        }
    }

    inline void unlock() noexcept
    {
        m_busy.clear(std::memory_order_release);
    }

#else

public:
    inline bool try_lock() noexcept
    {
        if (!m_busy.test_and_set(std::memory_order_acquire))
        {
            m_owner_thread_id.store(std::this_thread::get_id(), std::memory_order_release);
        }
        else if (m_owner_thread_id.load(std::memory_order_acquire) != std::this_thread::get_id())
        {
            return false;
        }
        ++m_recursive_counter;
        return true;
    }

    inline void lock() noexcept
    {
        while (!try_lock())
        {
            std::this_thread::yield();
        }
    }

    inline void unlock() noexcept
    {
        assert(m_owner_thread_id.load(std::memory_order_acquire) == std::this_thread::get_id());
        assert(m_recursive_counter > 0);

        if (--m_recursive_counter == 0)
        {
            m_owner_thread_id.store(std::thread::id(), std::memory_order_release);
            m_busy.clear(std::memory_order_release);
        }
    }
#endif // ENABLE_YIELD

private:
    std::atomic<std::thread::id> m_owner_thread_id = std::thread::id();
    std::uint32_t m_recursive_counter = 0;
    std::atomic_flag m_busy = ATOMIC_FLAG_INIT;
};

} // namespace is::signals::detail

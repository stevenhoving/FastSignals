

add_library(libfastsignals
    src/connection.cpp
    src/function_detail.cpp
    src/signal_impl.cpp
    include/libfastsignals/bind_weak.h
    include/libfastsignals/combiners.h
    include/libfastsignals/connection.h
    include/libfastsignals/function.h
    include/libfastsignals/function_detail.h
    include/libfastsignals/signal.h
    include/libfastsignals/signal_impl.h
    include/libfastsignals/spin_mutex.h
    include/libfastsignals/type_traits.h
)
custom_enable_cxx17(libfastsignals)

target_include_directories(libfastsignals
  PUBLIC
    include
  PRIVATE
    include/libfastsignals
    src
)

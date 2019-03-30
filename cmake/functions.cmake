function(custom_enable_cxx17 TARGET)
	target_compile_features(${TARGET} PUBLIC cxx_std_17)
	if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
		set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "/std:c++latest")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
		set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "-stdlib=libc++ -pthread")
        target_link_libraries(${TARGET} c++experimental pthread)
    endif()
endfunction(custom_enable_cxx17)


function(custom_add_library_from_dir TARGET)
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_library(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_executable_from_dir TARGET)
    file(GLOB TARGET_SRC "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
    add_executable(${TARGET} ${TARGET_SRC})
endfunction()

function(custom_add_test_from_dir TARGET LIBRARY)
    custom_add_executable_from_dir(${TARGET})
    target_link_libraries(${TARGET}
        ${LIBRARY}
        catch2::catch2
    )
    add_test(${TARGET} ${TARGET})
endfunction()

add_executable (cmaketest main.cpp)
add_executable (runtests runtests.cpp)

set(EXECUTABLE_OUTPUT_PATH ..)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
target_link_libraries (runtests LINK_PUBLIC gtest)

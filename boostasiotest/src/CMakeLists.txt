find_package( OpenSSL REQUIRED )
find_package( Boost 1.54 COMPONENTS system REQUIRED )

set( EXECUTABLE_OUTPUT_PATH .. )

add_executable ( boostasiotest main.cpp client.cpp )
include_directories( ${OPENSSL_INCLUDE_DIR} ${Boost_INCLUDE_DIR} )
target_link_libraries( boostasiotest LINK_PUBLIC ${OPENSSL_LIBRARIES} ${Boost_LIBRARIES} )


add_executable ( runtests runtests.cpp )
include_directories( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )
target_link_libraries ( runtests LINK_PUBLIC gtest )

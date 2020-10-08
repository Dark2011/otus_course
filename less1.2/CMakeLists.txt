cmake_minimum_required(VERSION 3.2)
cmake_policy(SET CMP0074 NEW)

set(BUILD_NUM 1)
if($ENV{TRAVIS_BUILD_NUMBER})
	set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
endif()

message (STATUS "Current build number is: " ${BUILD_NUM})

project(ip_filter VERSION 0.0.${BUILD_NUM})


set(Boost_USE_MULTITHREADED ON)
#message (STATUS "Boost inlude dir is: " $ENV{BOOST_INCLUDEDIR})
find_package(Boost)


include_directories("${PROJECT_SOURCE_DIR}/include")
configure_file(version.h.in ${PROJECT_SOURCE_DIR}/include/version.h)

set(APP_HDR src/ip_filter.h src/tools.h)
set(APP_SRC src/main.cpp src/ip_filter.cpp)
set(TEST_SRC tests/test_ip_filter.cpp)

add_executable(ip_filter ${APP_HDR} ${APP_SRC})
add_executable(test_ip_filter ${APP_HDR} ${TEST_SRC} src/ip_filter.cpp)

set_target_properties(ip_filter PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON 
)

target_include_directories(ip_filter
    PRIVATE "${PROJECT_SOURCE_DIR}/include/version.h"
	PRIVATE ${Boost_INCLUDE_DIR} 
)


set_target_properties(test_ip_filter PROPERTIES
	CXX_STANDARD 14
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK	 
)


target_include_directories(test_ip_filter
	PRIVATE ${Boost_INCLUDE_DIR} 
)

target_link_libraries(test_ip_filter
    ${Boost_LIBRARIES}
)

install(TARGETS ip_filter RUNTIME DESTINATION bin)
	
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ilya.zah86@gmail.com)
include(CPack)		
	
enable_testing()
add_test(check_stream_splitter test_ip_filter)
add_test(check_ip_sort test_ip_filter)
add_test(check_octet_filter test_ip_filter)

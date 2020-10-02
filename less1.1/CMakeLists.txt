cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)


set(BUILD_NUM 1)
if($ENV{TRAVIS_BUILD_NUMBER})
	set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
endif()

message (STATUS "Current build number is: " ${BUILD_NUM})

project(helloworld VERSION 0.0.${BUILD_NUM})


set(Boost_USE_MULTITHREADED ON)
message (STATUS "Boost inlude dir is: " $ENV{BOOST_INCLUDEDIR})
find_package(Boost COMPONENTS unit_test_framework)


include_directories("${PROJECT_SOURCE_DIR}/include")
configure_file(version.h.in ${PROJECT_SOURCE_DIR}/include/version.h)

set(HDR include/version.h)
set(APP_SRC src/helloworld.cpp)
set(TEST_SRC src/test_version.cpp)

add_executable(helloworld_cli ${APP_SRC})
add_executable(test_version ${TEST_SRC})

set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wall -Wextra -pedantic
)



set_target_properties(test_version PROPERTIES
	CXX_STANDARD 14
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK	 
)

target_include_directories(test_version
    PRIVATE "${PROJECT_SOURCE_DIR}/include/version.h"
	PRIVATE ${Boost_INCLUDE_DIR} 
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
)



install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
	
enable_testing()
add_test(validate_test_version test_version)

cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)


set(BUILD_NUM 1)
if($ENV{TRAVIS_BUILD_NUMBER})
	set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
endif()

message (STATUS "Current build number is: " ${BUILD_NUM})

project(helloworld VERSION 0.0.${BUILD_NUM})

message (STATUS "Boost inlude dir is: " $ENV{BOOST_INCLUDEDIR})
find_package(Boost 1.72.0 COMPONENTS unit_test_framework)



include_directories("${PROJECT_SOURCE_DIR}/include")
configure_file(version.h.in ${PROJECT_SOURCE_DIR}/include/version.h)

set(HDR include/version.h)
set(SRC src/helloworld.cpp)

add_executable(helloworld_cli ${HDR} ${SRC})


set_target_properties(helloworld_cli PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	COMPILE_OPTIONS -Wall -Wextra -pedantic
)
	
	
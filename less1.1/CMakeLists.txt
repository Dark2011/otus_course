cmake_minimum_required(VERSION 3.12)
cmake_policy(SET CMP0074 NEW)


set(BUILD_NUM 1)
if($ENV{TRAVIS_BUILD_NUMBER})
	set(BUILD_NUM $ENV{TRAVIS_BUILD_NUMBER})
endif()

message (STATUS "Current build number is: " ${BUILD_NUM})

project(helloworld VERSION 0.0.${BUILD_NUM})


set(Boost_USE_MULTITHREADED ON)
set(BOOST_TEST_LOG_LEVEL message)
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
)



set_target_properties(test_version PROPERTIES
	CXX_STANDARD 14
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK	 
)

#target_include_directories(helloworld_cli
    #PRIVATE "${PROJECT_SOURCE_DIR}/include/version.h"
#)


target_include_directories(test_version
    PRIVATE "${PROJECT_SOURCE_DIR}/include/version.h"
	PRIVATE ${Boost_INCLUDE_DIR} 
)

target_link_libraries(test_version
    ${Boost_LIBRARIES}
)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)
	
set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT ilya.zah86@gmail.com)
include(CPack)	
	
	
enable_testing()
add_test(test_version test_version)

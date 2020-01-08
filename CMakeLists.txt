cmake_minimum_required(VERSION 3.12)
project(matrix VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(matrix)
target_sources(matrix PRIVATE
        main.cpp
        )

add_library(matrix_lib INTERFACE)
target_include_directories(matrix_lib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(test_matrix)
target_sources(test_matrix PRIVATE
        test_matrix.cpp
        )

set_target_properties(test_matrix PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
        )

target_link_libraries(matrix
        matrix_lib
        )

message("BOOST:" ${Boost_LIBRARIES})

target_link_libraries(test_matrix
        ${Boost_LIBRARIES}
        matrix_lib
        )

install(TARGETS matrix RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT tnovits@yandex.ru)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

enable_testing()

add_test(matrix_tests test_matrix)
cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VESRION})

option(WITH_BOOST_TEST "Whether to build Boost test" ON)
option(WITH_GTEST_TEST "Whether to build GTest test" OFF)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld_lib lib.cpp)

set_target_properties(helloworld_cli helloworld_lib PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld_lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(helloworld_cli PRIVATE
    helloworld_lib
)

if(WITH_BOOST_TEST)
    find_package(Boost COMPONENTS unit_test_framework REQUIRED)
    add_executable(helloworld_test1 test_version.cpp)

    set_target_properties(helloworld_test1 PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    set_target_properties(helloworld_test1 PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )

    target_link_libraries(helloworld_test1
        ${Boost_LIBRARIES}
        helloworld_lib
    )
endif()

if(WITH_GTEST_TEST)
    add_executable(helloworld_test2 allgtests.cpp test2_version.cpp)
    
    target_link_libraries(helloworld_test2
        gtest
        pthread
        helloworld_lib
    )
    
    target_compile_definitions(helloworld_test2 PRIVATE
        TEST_DIR="${CMAKE_CURRENT_LIST_DIR}/test"
    )

    install(TARGETS helloworld_test2 DESTINATION bin)
endif()

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld_lib PRIVATE
        /W4
    )
    if()
        target_compile_options(helloworld_test1 PRIVATE
            /W4
        )
    endif()

    if(WITH_GTEST_TEST)

    endif()
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld_lib PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_BOOST_TEST)
        target_compile_options(helloworld_test1 PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()

    if(WITH_GTEST_TEST)

    endif()
endif()

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

if(WITH_BOOST_TEST)
    enable_testing()
    add_test(helloworld_test1 helloworld_test1)
endif()

if(WITH_GTEST_TEST)

endif()


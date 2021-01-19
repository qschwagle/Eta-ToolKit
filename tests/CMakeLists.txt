add_executable(tests  test_application.cpp)

find_package(GTest CONFIG REQUIRED)
#target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main ${PROJECT_NAME})

# Either of the bottom due to redundent linking in vcpkg
# https://github.com/google/googletest/issues/2157
#target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main ${PROJECT_NAME})
target_link_libraries(tests PRIVATE GTest::gmock_main ${PROJECT_NAME})

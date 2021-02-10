add_executable(tests  test_application.cpp "test_window.cpp" "test_label.cpp" "test_widget.cpp")

# find_package(GTest CONFIG REQUIRED)

include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.10.0
)

FETCHCONTENT_MAKEAVAILABLE(googletest)

#target_link_libraries(tests PRIVATE GTest::gmock GTest::gtest GTest::gmock_main GTest::gtest_main ${PROJECT_NAME})

# Either of the bottom due to redundent linking in vcpkg
# https://github.com/google/googletest/issues/2157
#target_link_libraries(tests PRIVATE GTest::gtest GTest::gtest_main ${PROJECT_NAME})
target_link_libraries(tests PRIVATE gmock_main ${PROJECT_NAME})

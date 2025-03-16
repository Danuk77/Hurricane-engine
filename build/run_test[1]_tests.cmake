add_test([=[HelloTest.BasicAssertions]=]  [==[X:/Side projects/Hurricane/build/run_test.exe]==] [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY [==[X:/Side projects/Hurricane/build]==] SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  run_test_TESTS HelloTest.BasicAssertions)

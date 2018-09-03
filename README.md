# gtest-extension
This header adds time-based assertion macros for the [google test](https://github.com/google/googletest) framework.

**Availability**: Linux

# Usage
Simply include this header file in your google unit test and compile with the google test library.

## Timed functions
The `ASSERT_TIME` macro can be used to check if a function finishes executing within a specified duration. The macro accepts two parameters, the function that is checked and the time limit in microseconds.

The example below results in a test failure if the `gcd` function takes more than 1000 microseconds to execute.

```cpp
ASSERT_TIME(gcd(20, 15), 1000);
```

## Timed blocks
The `ASSERT_TIMED_BLOCK_START` and `ASSERT_TIMED_BLOCK_END` macros are used to test whether a block of statements finish executing within a specific duration. `ASSERT_TIMED_BLOCK_END` accepts two parameters, the name of the test block and the time limit in microseconds. Do not forget to add the `ASSERT_TIMED_BLOCK_END` macro otherwise it may incorrectly report a failure.

The example below results in a failure if it takes longer than 5000 microseconds to complete the enclosed statements. Take note that the block can contain other assertion statements as well.

```cpp
ASSERT_TIMED_BLOCK_START(TestBlock, 5000)
ASSERT_EQ(6, squareRoot(36.0));
// other statements
ASSERT_TIMED_BLOCK_END()
```

## main() output
Unit tests are often used to check functions, but beginners may not yet know how to construct them. The `ASSERT_MAIN_OUTPUT_EQ` and `ASSERT_MAIN_OUTPUT_THAT` macros can test the output of the main() function. However, the code needs to be compiled first so that the macro runs the exectuable file and tests its output. Both macros require the name of the executable file and a string that simulates keyboard input.

The example below uses `ASSERT_MAIN_OUTPUT_EQ` to test the main() function of a file called `square.cpp` that was compiled to produce the `square` executable file. It shows the output of the square program that asks the user to input a number and outputs the result. This is followed by a unit test code snippet showing how this can be tested.

Output of the square program:

```
Please enter a number: 5
The square of 5 is 25
```
Unit test code snippet:

```cpp
ASSERT_MAIN_OUTPUT_EQ("square", "5", "Please enter a number: The square of 5 is 25");
```

The `ASSERT_MAIN_OUTPUT_THAT` macro uses [googlemock's](https://github.com/google/googletest/tree/master/googlemock) Matcher objects for advanced tests such as regular expressions, startsWith, and substrings. The example below uses a `HasSubstr` matcher to check if the result from the `square` program contains part of the expected output.

```cpp
ASSERT_MAIN_OUTPUT_THAT("square", "5", HasSubstr("5 is 25"));
```

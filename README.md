# gtest-extension
This single header adds time-based assertion macros for the [google test](https://github.com/google/googletest) framework.

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

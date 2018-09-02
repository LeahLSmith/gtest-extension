// This file contains implementations that extend the functionality of the
// google test framework
#include <gtest/gtest.h>
#include <unistd.h>
#include <setjmp.h>
#include <signal.h>

// variable used to store jump locations used in the
// time-based assertion macros (ASSERT_TIME, ASSERT_TIMED_BLOCK_START,
// ASSERT_TIMED_BLOCK_END)
static jmp_buf jmp_env;

// This function catches alarms from time-based assertion macros (ASSERT_TIME,
// ASSERT_TIMED_BLOCK_START, ASSERT_TIMED_BLOCK_END)
// @param sig signal number
static void catch_alarm(int sig)
{
    longjmp(jmp_env, 1);
}

// This macro checks whether a function executes within a given time
// @param fn    function tested
// @param usecs microseconds to wait before function is considered to have
//              timed out
#define ASSERT_TIME(fn, usecs) { \
    // line where longjmp will return when alarm is signalled
    const auto val = setjmp(jmp_env); \
    // val is 0 during initialization and when it finishes before the time limit
    // val is 1 if alarm was caught (i.e., it took longer to execute the
    // statements compared to the time limit).
    if (val == 0) { \
        // assigns the alarm handler, starts the alarm, runs the function,
        // and cances the alarm (if function finishes before time limit)
        signal(SIGALRM, catch_alarm); \
        ualarm((usecs), 0); \
        { fn; }; \
        ualarm(0, 0); \
    } else { \
        GTEST_FATAL_FAILURE_("      " #fn " timed out (> " #usecs \
        " microseconds)"); \
    } }

// This macro indicates the start of a block that checks whether the statements
// it contains executes with a given time. This block must be followed by an
// ASSERT_TIMED_BLOCK_END macro
// @param name name of the timed block
// @param usecs microseconds to wait before the statements in the block are
//              considered to have timed out
#define ASSERT_TIMED_BLOCK_START(name, usecs) { \
  // line where longjmp will return when alarm is signalled
  const auto val = setjmp(jmp_env); \
  // val is 1 if alarm was caught (i.e., it took longer to execute the
  // statements compared to the time limit).
  // val is 0 during initialization and when it finishes before the time limit
  if (val == 1) {\
    GTEST_FATAL_FAILURE_("      " #name " timed out (>" #usecs \
                         " microseconds)"); \
  } else { \
      // assigns the alarm handler and starts the alarm
      signal(SIGALRM, catch_alarm); \
      ualarm((usecs), 0); \
  } }

// This macro indicates the end of the block that checks whether contained
// statements execute with a given time.
#define ASSERT_TIMED_BLOCK_END() { \
  // cancels the alarm
   ualarm(0, 0); \
  }

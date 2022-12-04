#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "stufflib.h"

int test_stufflib_parse_argv_flag() {
  {
    int argc = 2;
    char* const argv[3] = {
        "bin/path",
        "-v",
        0,
    };
    if (!stufflib_parse_argv_flag(argc, argv, "-v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "-vv")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "-wvv")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "- v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "")) {
      return 1;
    }
  }
  {
    int argc = 1;
    char* const argv[2] = {
        "bin/path",
        0,
    };
    if (stufflib_parse_argv_flag(argc, argv, "-v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "-vv")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "-wvv")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "- v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "v")) {
      return 1;
    }
    if (stufflib_parse_argv_flag(argc, argv, "")) {
      return 1;
    }
  }
  return 0;
}

int test_stufflib_fill_random() {
  const size_t n = 1000;
  double x[n];
  stufflib_fill_random(n, x, 0);
  for (size_t i = 0; i < n; ++i) {
    if (fabs(x[i]) > 0) {
      return 1;
    }
  }
  stufflib_fill_random(n, x, 10);
  for (size_t i = 0; i < n; ++i) {
    if (fabs(x[i]) > 10) {
      return 1;
    }
  }
  return 0;
}

int test_stufflib_set_zero_random() {
  const size_t n = 1000;
  double x[n];
  for (size_t i = 0; i < n; ++i) {
    x[i] = i + 1;
  }
  stufflib_set_zero_random(n, x, 0);
  for (size_t i = 0; i < n; ++i) {
    if (fabs(x[i]) < 1) {
      return 1;
    }
  }
  stufflib_set_zero_random(n, x, 1);
  for (size_t i = 0; i < n; ++i) {
    if (fabs(x[i]) > 0) {
      return 1;
    }
  }
  return 0;
}

int test_stufflib_double_almost() {
  if (!stufflib_double_almost(1, 1.5, 1)) {
    return 1;
  }
  if (stufflib_double_almost(1, 1.5, 0.1)) {
    return 1;
  }
  return 0;
}

typedef int (*test_function)(void);

int main(void) {
  test_function tests[] = {
      test_stufflib_parse_argv_flag,
      test_stufflib_fill_random,
      test_stufflib_set_zero_random,
      test_stufflib_double_almost,
  };
  for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); ++i) {
    if (tests[i]()) {
      fprintf(stderr, "test %zu failed\n", i);
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

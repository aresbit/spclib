#include "sp.h"
#include "test.h"

#include "utest.h"

SP_TEST_MAIN()

#define QSORT_TEST_MAX 16

typedef struct {
  s32 values [QSORT_TEST_MAX];
  u32 len;
} qsort_expect_t;

typedef struct {
  s32 values [QSORT_TEST_MAX];
  u32 len;
  qsort_expect_t expect;
} qsort_test_t;

static int qsort_cmp_s32(const void* a, const void* b) {
  s32 x = *(const s32*)a;
  s32 y = *(const s32*)b;
  return (x > y) - (x < y);
}

UTEST_EMPTY_FIXTURE(qsort)

void run_qsort_test(s32* utest_result, qsort_test_t t) {
  sp_os_qsort(t.values, t.len, sizeof(t.values[0]), qsort_cmp_s32);

  EXPECT_EQ(t.expect.len, t.len);
  sp_for(it, t.len) {
    EXPECT_EQ(t.expect.values[it], t.values[it]);
  }
}

UTEST_F(qsort, two_out_of_order) {
  run_qsort_test(&ur, (qsort_test_t) {
    .values = { 2, 1 },
    .len = 2,
    .expect = {
      .values = { 1, 2 },
      .len = 2,
    },
  });
}

UTEST_F(qsort, two_in_order) {
  run_qsort_test(&ur, (qsort_test_t) {
    .values = { 1, 2 },
    .len = 2,
    .expect = {
      .values = { 1, 2 },
      .len = 2,
    },
  });
}

UTEST_F(qsort, three_out_of_order) {
  run_qsort_test(&ur, (qsort_test_t) {
    .values = { 3, 1, 2 },
    .len = 3,
    .expect = {
      .values = { 1, 2, 3 },
      .len = 3,
    },
  });
}

UTEST_F(qsort, many_reversed) {
  run_qsort_test(&ur, (qsort_test_t) {
    .values = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
    .len = 10,
    .expect = {
      .values = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 },
      .len = 10,
    },
  });
}

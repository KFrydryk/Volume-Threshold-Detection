#ifdef TEST

#include "unity.h"

#include "thresholds.h"
#include "linked-list.h"

uint32_t data;
uint32_t data2;

void setUp(void)
{
}

void tearDown(void)
{
}

void test_thresholds_init(void)
{
	int ret;
	struct threshold thr;
	struct linked_list lli;

	ret = linked_list_init(&lli);
	TEST_ASSERT_EQUAL(0, ret);
	lli.data = &data;

	ret = threshold_init(&thr, &lli);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(thr.lli, &lli);
	TEST_ASSERT_EQUAL(thr.val, *(uint32_t *)lli.data);
}

void test_thresholds_init_null_lli(void)
{
	int ret;
	struct threshold thr;

	ret = threshold_init(&thr, NULL);
	TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_thresholds_init_null_thr(void)
{
	int ret;
	struct linked_list lli;

	ret = linked_list_init(&lli);
	TEST_ASSERT_EQUAL(0, ret);
	lli.data = &data;

	ret = threshold_init(NULL, &lli);
	TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_thresholds_next(void)
{
	int ret;
	struct threshold thr;
	struct linked_list lli;
	struct linked_list lli2;

	ret = linked_list_init(&lli);
	TEST_ASSERT_EQUAL(0, ret);
	lli.data = &data;

	ret = linked_list_append(&lli, &lli2);
	TEST_ASSERT_EQUAL(0, ret);
	lli2.data = &data2;

	ret = threshold_init(&thr, &lli);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(thr.lli, &lli);
	TEST_ASSERT_EQUAL(thr.val, *(uint32_t *)lli.data);

	ret = threshold_next(&thr);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(thr.lli, &lli2);
	TEST_ASSERT_EQUAL(thr.val, *(uint32_t *)lli2.data);
}

void test_thresholds_next_null_lli(void)
{
	/* prepare */
	int ret;
	struct threshold thr;
	struct linked_list lli;
	struct linked_list lli2;

	ret = linked_list_init(&lli);
	TEST_ASSERT_EQUAL(0, ret);
	lli.data = &data;

	ret = linked_list_append(&lli, &lli2);
	TEST_ASSERT_EQUAL(0, ret);
	lli2.data = &data2;

	ret = threshold_init(&thr, &lli);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(thr.lli, &lli);
	TEST_ASSERT_EQUAL(thr.val, *(uint32_t *)lli.data);

	thr.lli = NULL;

	/* test */
	ret = threshold_next(&thr);
	TEST_ASSERT_NOT_EQUAL(0, ret);
}




#endif // TEST

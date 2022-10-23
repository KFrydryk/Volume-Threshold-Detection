#ifdef TEST

#include "unity.h"

#include "linked-list.h"

void setUp(void)
{
}

void tearDown(void)
{
}

/* init 1 element list */
void test_linked_list_init_test(void)
{
	int ret;
	struct linked_list list;

	ret = linked_list_init(&list);
	TEST_ASSERT_EQUAL(&list, list.next);
	TEST_ASSERT_EQUAL(&list, list.prev);
	TEST_ASSERT_EQUAL(0, ret);
}

void test_linked_list_init_null(void)
{
	int ret;

	ret = linked_list_init(NULL);
	TEST_ASSERT_NOT_EQUAL(0, ret);
}

void test_linked_list_append_element(void)
{
	int ret;
	struct linked_list list1;
	struct linked_list list2;

	ret = linked_list_init(&list1);
	TEST_ASSERT_EQUAL(0, ret);
	ret = linked_list_append(&list1, &list2);
	TEST_ASSERT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(&list1, list2.next);
	TEST_ASSERT_EQUAL(&list1, list2.prev);
	TEST_ASSERT_EQUAL(&list2, list1.next);
	TEST_ASSERT_EQUAL(&list2, list1.prev);
}

void test_linked_list_append_null(void)
{
	int ret;
	struct linked_list list1;

	ret = linked_list_init(&list1);
	TEST_ASSERT_EQUAL(0, ret);
	ret = linked_list_append(&list1, NULL);
	TEST_ASSERT_NOT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(&list1, list1.prev);
	TEST_ASSERT_EQUAL(&list1, list1.next);
}

void test_linked_list_append_to_null(void)
{
	int ret;
	struct linked_list list2;

	ret = linked_list_init(&list2);
	TEST_ASSERT_EQUAL(0, ret);
	ret = linked_list_append(NULL, &list2);
	TEST_ASSERT_NOT_EQUAL(0, ret);
	TEST_ASSERT_EQUAL(&list2, list2.prev);
	TEST_ASSERT_EQUAL(&list2, list2.next);
}

void test_linked_list_append_to_target_with_nulls(void)
{
	int ret;
	struct linked_list list1;
	struct linked_list list2;

	ret = linked_list_init(&list2);
	TEST_ASSERT_EQUAL(0, ret);

	list1.prev = NULL;

	ret = linked_list_append(&list1, &list2);
	TEST_ASSERT_NOT_EQUAL(0, ret);
	/* expected not to change list2 */
	TEST_ASSERT_EQUAL(&list2, list2.prev);
	TEST_ASSERT_EQUAL(&list2, list2.next);

	list1.prev = &list1;
	/* same for target->next */
	list1.next = NULL;

	ret = linked_list_append(&list1, &list2);
	TEST_ASSERT_NOT_EQUAL(0, ret);
	/* expected not to change list2 */
	TEST_ASSERT_EQUAL(&list2, list2.prev);
	TEST_ASSERT_EQUAL(&list2, list2.next);
}

#endif // TEST

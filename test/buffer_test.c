#include "unity.h"
#include "buffer.h"

void setUp(void) {}

void tearDown(void) {}

void test_buffer_insert_extract_on_single_byte(void)
{

    // Sample array created with 3 elements of unit8_t
    uint8_t sample_arr[3] = {1, 2, 3};
    // Sample array buffer shall be like
    // Index 23 ....                    ......0
    //        0000 0011 | 0000 0010 | 0000 0001
    buffer_insert(sample_arr, 0, 8, 64);
    // Inserting at 0th index value of 64 for length of 8 bits

    // Expected array after buffer insert
    // Index 23 ....                    ......0
    //        0000 0011 | 0000 0010 | 0100 0000

    // Trying to extract from index 2, length of 8
    // Expected value = 1001 0000
    uint8_t value = buffer_extract(sample_arr, 2, 8);
    TEST_ASSERT_EQUAL(144, value);

    // After buffer inserting, array elements would be changed as shown in comments
    TEST_ASSERT_EQUAL(64, sample_arr[0]);
    TEST_ASSERT_EQUAL(2, sample_arr[1]);
    TEST_ASSERT_EQUAL(3, sample_arr[2]);
}
void test_buffer_insert_extract_on_two_bytes(void)
{
    // Sample array created with 3 elements of unit8_t
    uint8_t sample_arr[3] = {1, 2, 3};
    // Sample array buffer shall be like
    // Index 23 ....                    ......0
    //        0000 0011 | 0000 0010 | 0000 0001

    buffer_insert(sample_arr, 10, 8, 128);
    // Inserting value 128 at 10th index to the length 8
    // Expected array after buffer insert
    // Index 23 ....                    ......0
    //        0000 0001 | 0000 0010 | 0000 0001

    // Trying to extract from index 9 to lenght 9
    // Expected value(16 bit) = 0000 0001 | 0000 0001 (257)
    //        0000 0010 | 0000 0010 | 0000 0001
    uint16_t value = buffer_extract(sample_arr, 9, 9);
    TEST_ASSERT_EQUAL(1, sample_arr[0]);
    TEST_ASSERT_EQUAL(2, sample_arr[1]);
    TEST_ASSERT_EQUAL(2, sample_arr[2]);
    TEST_ASSERT_EQUAL(257, value);
}

void test_buffer_insert_extract_on_three_bytes(void)
{
    // Sample array created with 3 elements of unit8_t
    uint8_t sample_arr[3] = {1, 2, 3};
    // Sample array buffer shall be like
    // Index 23 ....                    ......0
    //        0000 0011 | 0000 0010 | 0000 0001
    buffer_insert(sample_arr, 12, 8, 192);
    // inserting value 192 in the index 12 to the lenght 8
    // Expected array after buffer insert
    // Index 23 ....                    ......0
    //        0000 1100 | 0000 0000 | 0000 0001
    // Trying to extract from index 6 to lenght 16
    // Expected value = 0000 0000 | 0000 0000 | 0000 0000 | 0000 0100
    uint32_t value = buffer_extract(sample_arr, 6, 11);
    TEST_ASSERT_EQUAL(1, sample_arr[0]);
    TEST_ASSERT_EQUAL(2, sample_arr[1]);
    TEST_ASSERT_EQUAL(12, sample_arr[2]);
    TEST_ASSERT_EQUAL(8, value);
}
void test_buffer_insert_extract_rewrite(void)
{
    // sample array     0000 0011 | 0000 0010 | 0000 0001
    uint8_t sample_arr[3] = {1, 2, 3};
    buffer_insert(sample_arr, 12, 8, 192);
    // after insertion  0000 0011 | 0000 0010 | 0000 0001
    uint32_t value = buffer_extract(sample_arr, 6, 11);
    // extracted value = 0000 1100 | 0000 0010 | 0000 0001
    TEST_ASSERT_EQUAL(1, sample_arr[0]);
    TEST_ASSERT_EQUAL(2, sample_arr[1]);
    TEST_ASSERT_EQUAL(12, sample_arr[2]);
    TEST_ASSERT_EQUAL(8, value);

    // STEP2
    // before insertion 0000 0011 | 0000 0010 | 0000 0001
    buffer_insert(sample_arr, 14, 4, 8);
    // insert at 14th index to length 4 with value 8
    //  after rewrite 0000 1110 | 0000 0010 | 0000 0001
    uint32_t value1 = buffer_extract(sample_arr, 12, 10);
    // extract from 12th index to length 10
    //  extracted value = 0000 0000 | 1110 0000 | 0000 0000
    TEST_ASSERT_EQUAL(1, sample_arr[0]);
    TEST_ASSERT_EQUAL(2, sample_arr[1]);
    TEST_ASSERT_EQUAL(14, sample_arr[2]);
    TEST_ASSERT_EQUAL(224, value1);
}
int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_buffer_insert_extract_on_single_byte);
    RUN_TEST(test_buffer_insert_extract_on_two_bytes);
    RUN_TEST(test_buffer_insert_extract_on_three_bytes);
    RUN_TEST(test_buffer_insert_extract_rewrite);
    return UNITY_END();
}

#include "buffer.h"

void buffer_insert(uint8_t *buffer, uint8_t start, uint8_t length, uint64_t value)
{
    // STEP1: Pointer must be moved according to the start requestes
    // start bit for insertion
    uint8_t ptr_increment_needed = start / 8 ;
    while (ptr_increment_needed > 0)
    {
        buffer++;
        ptr_increment_needed -= 1;
    }

    start %= 8;
    // STEP2: Based on the length in argument, we are inserting the bits from value
    while(length > 0)
    {
        // STEP3: bit that needed to be inserted is calculated
        uint8_t bit_insert = value % 2;
        *buffer = *buffer & ~(1 << start);
        *buffer = *buffer | (bit_insert << start);

        // STEP4: Once bit is inserted
        // length is decremented, value is recalculated, start_bit is incremented
        length -= 1;
        value /= 2;
        start += 1;

        // STEP5: Race around condition,
        // Once start bit reached the end bit of a byte, pointer shall be incremented
        // After which start bit points to 0th index of the new value in pointer
        if(start == 8)
        {
            buffer++;
            start = start % 8;
        }
    }
}

uint64_t buffer_extract(uint8_t *buffer, uint8_t start, uint8_t length)
{
    // Value to be returned to the caller
    uint64_t cal_total = 0;
    uint8_t exp_cal = 0; //Initializing for calculating the exp of 2 equivalent to pow(2,x)

    // STEP1: Incrementing the pointer based on the start  
    uint8_t ptr_increment_needed = start / 8 ;
    while (ptr_increment_needed > 0)
    {
        buffer++;
        ptr_increment_needed -= 1;
    }

    start %= 8;

    // STEP2: Looping the length based on the user requirement
    while(length > 0)
    {

        uint64_t exp_val = 1;
        uint8_t temp_exp_cal = exp_cal;
        // To avoid tinkering the buffer, we are storing in a temp_val
        uint8_t temp_val= *buffer;
        uint8_t ret_bit = ((temp_val>>start) & 1);
        
        // STEP3: Calculating the exponential of 2, based on the index (exp_cal)
        if (temp_exp_cal != 0)
        {
            while(temp_exp_cal > 0)
            {
                exp_val = exp_val * 2;
                temp_exp_cal -= 1;
            }
        }

        // STEP4: calculating the total based on the bit
        cal_total += (ret_bit * exp_val);
        
        // STEP5: Bit value added to total, so reducing the length,
        // Incrementing the start and incrementing the exp_cal
        length -= 1;
        start += 1;
        exp_cal += 1;

        // STEP6: Checking for the Loop around condition and incrementing the buffer
        if(start == 8)
        {
            buffer++;
            start = start % 8;
        }
    }
    return cal_total;

}

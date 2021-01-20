/****************************************************************************************
> File Name: wwpc_config.h
> Description£º
> Log:    Author     Time            modification
        | wwpc       2021/1/5        Create
        |
******************************************************************************************/
#include "wwpc_config.h"



//uint16_t






uint8_t lutec_check_sum(uint8_t *data, uint8_t len)
{
    uint8_t i,sum = 0;
    for(i = 0; i < len; i++)
    {
        sum += data[i];
    }
    return sum;
}




/*************************************File end********************************************/

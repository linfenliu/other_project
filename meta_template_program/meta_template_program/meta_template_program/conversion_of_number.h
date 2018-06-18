#ifndef FLEW_CONVERSION_OF_NUMBER_H
#define FLEW_CONVERSION_OF_NUMBER_H

#include "config.h"

FL_ENTER

template<unsigned long N>
struct DecToBinary
{
    static const unsigned long value = DecToBinary<N/2>::value * 10 + N % 2;
};

template<>
struct DecToBinary<0>
{
    static const unsigned long value = 0;
};




template<unsigned long N>
struct BinaryToDec
{
    static const unsigned long value = BinaryToDec<N/10>::value * 2 + (N & 1);
};

template<>
struct BinaryToDec<0>
{
    static const unsigned long value = 0;
};

FL_LEAVE

#endif /* conversion_of_number_h */

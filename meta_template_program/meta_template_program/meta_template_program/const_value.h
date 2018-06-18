#ifndef FLEW_CONST_VALUE
#define FLEW_CONST_VALUE

#include "config.h"

FL_ENTER

template<typename T, T _Value>
struct integral_const
{
	static const T value = _Value;

	typedef T value_type;
	typedef integral_const<T, _Value> type;

	operator value_type() const
	{
		return value;
	}

};

typedef integral_const<bool, true> true_type;
typedef integral_const<bool, false> false_type;



template<bool>
struct _Cat_base
{};

template<>
struct _Cat_base<true> :true_type
{};

template<>
struct _Cat_base<false> :false_type
{};





FL_LEAVE

#endif 
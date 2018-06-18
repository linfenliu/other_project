#ifndef FLEW_VECTOR_H
#define FLEW_VECTOR_H

#include "config.h"
#include "type_traits.h"
#include "number.h"

FL_ENTER


template<typename... T>
struct vector;

template<typename Car, typename... Cdr>
struct vector<Car, Cdr...>
{
	typedef Car car;
	typedef vector<Cdr...> cdr;
};

template<typename T>
struct vector<T>
{
	typedef T car;
	typedef nil_list cdr;
};


namespace fivimpl
{
	template<typename Vec, typename Key, bool>
	struct find_in_vector_impl;

	template<typename Vec, typename Key>
	struct find_in_vector_impl<Vec, Key, true>
	{
		static const bool value = true;
	};

	template<typename Vec, typename Key>
	struct find_in_vector_impl<Vec, Key, false>
	{
		static const bool value = find_in_vector_impl<Vec::cdr, Key, is_same<Vec::car, Key>::value>::value;
	};

	template<>
	struct find_in_vector_impl<nil_list, nil, false>
	{
		static const bool value = true;
	};

	template<typename Key>
	struct find_in_vector_impl<nil_list, Key, false>
	{
		static const bool value = false;
	};
}




template<typename Vec, typename Key>
struct find_in_vector
{
	static const bool value = typename fivimpl::find_in_vector_impl<Vec::cdr, Key, is_same<Vec::car, Key>::value>::value;
};




FL_LEAVE

#endif
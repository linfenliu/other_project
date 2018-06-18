#ifndef ONLY_FOR_TEST_3_H
#define ONLY_FOR_TEST_3_H

#include "config.h"


struct F
{
	double value;
};

struct m
{
	double value;
};

struct a
{
	double value;
};

struct v
{
	double value;
};

template<typename T1, typename T2>
struct multi_type;

template<>
struct multi_type<m, a>
{
	typedef F type;
};

template<typename T1, typename T2>
typename multi_type<T1, T2>::type operator*(T1 v1, T2 v2)
{
	return { v1.value * v2.value };
}

struct Nil{};





template<typename... T>
struct mpl_vector_impl;


template<typename T0, typename... Rest>
struct mpl_vector_impl<T0, Rest...>
{
	typedef T0 car;
	typedef mpl_vector_impl<Rest...> cdr;
};


template<typename... T>
struct mpl_vector;

template<typename T0, typename... Rest>
struct mpl_vector<T0, Rest...> : mpl_vector_impl<T0, Rest..., Nil>
{};



template<typename T>
struct is_vector
{
	static const bool value = false;
};

template<typename... T>
struct is_vector<mpl_vector<T...> >
{
	static const bool value = true;
};


typedef mpl_vector_impl<Nil> NilList;

template<typename T>
struct is_Nil_list
{
	static const bool value = false;
};

template<>
struct is_Nil_list<NilList>
{
	static const bool value = true;
};







template<typename T0, typename T1>
struct mpl_find_inner
{
	static const bool value = false;
};

template<typename T>
struct mpl_find_inner<T, T>
{
	static const bool value = true;
};




template<typename T0, typename T1>
struct mpl_find_vector
{
	static const bool value = mpl_find_inner<T0::car, T1>::value || mpl_find_vector<T0::cdr, T1>::value;
};


template<>
struct  mpl_find_vector<NilList, Nil>
{
	static const bool value = true;
};

template<typename T>
struct  mpl_find_vector<NilList, T>
{
	static const bool value = false;
};






template<typename T0, typename T1, bool>
struct mpl_find_impl;

template<typename T0, typename T1>
struct mpl_find_impl<T0, T1, true>
{
	static const bool value = mpl_find_vector<T0, T1>::value;
};

template<typename T0, typename T1>
struct mpl_find_impl<T0, T1, false>
{
	static const bool value = mpl_find_inner<T0, T1>::value;
};




template<typename T0, typename T1>
struct mpl_find
{
	static const bool value = mpl_find_impl<T0, T1, is_vector<T0>::value>::value;
};


#endif
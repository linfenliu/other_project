#ifndef FLEW_NUMBER_H
#define FLEW_NUMBER_H

#include "config.h"

FL_ENTER

struct nil
{};

struct nil_list
{
	typedef nil car;
	typedef nil_list cdr;
};


template<typename T>
struct is_nil
{
	static const bool value = false;
};

template<>
struct is_nil<nil>
{
	static const bool value = true;
};

template<typename T>
struct is_nil_list
{
	static const bool value = false;
};

template<>
struct is_nil_list<nil_list>
{
	static const bool value = true;
};



template<int N>
struct num
{
	static const int value = N;
};

template<typename Beg, unsigned int N>
struct number_arr
{
	typedef Beg car;
	typedef number_arr<num<Beg::value + 1>, N - 1> cdr;
};

template<typename Beg>
struct number_arr<Beg, 0>
{
	typedef Beg car;
	typedef nil_list cdr;
};


template<typename T1, typename T2>
struct mul
{
	typedef num<T1::value * T2::value> type;
};

template<typename T1, typename T2>
struct add
{
	typedef num<T1::value + T2::value> type;
};

template<typename T1, typename T2>
struct sub
{
	typedef num<T1::value - T2::value> type;
};

template<typename T1, typename T2>
struct div
{
	typedef num<T1::value / T2::value> type;
};




FL_LEAVE

#endif
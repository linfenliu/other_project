#ifndef FLEW_TYPE_TRAITS_H
#define FLEW_TYPE_TRAITS_H

#include "config.h"
#include "const_value.h"

FL_ENTER


//***************************************************************************************
//judge pointer type
template<typename T>
struct _Ptr_traits
{};

template<typename T>
struct _Ptr_traits<T*>
{
	static const bool _Is_const = false;
	static const bool _Is_volatile = false;
};

template<typename T>
struct _Ptr_traits<const T*>
{
	static const bool _Is_const = true;
	static const bool _Is_volatile = false;
};

template<typename T>
struct _Ptr_traits<T* const>
{
	static const bool _Is_const = false;
	static const bool _Is_volatile = true;
};

template<typename T>
struct _Ptr_traits<const T* const>
{
	static const bool _Is_const = true;
	static const bool _Is_volatile = true;
};


template<typename T>
struct _Is_funptr :false_type
{};

//C调用方法
template<typename _Ret, typename... _Params>
struct _Is_funptr<_Ret (__cdecl*) (_Params...)> : true_type
{};

//C++调用方法
template<typename _Ret, typename... _Params>
struct _Is_funptr<_Ret (__stdcall*) (_Params...)> : true_type
{};

//编译器快速调用方法
template<typename _Ret, typename... _Params>
struct _Is_funptr<_Ret (__fastcall*) (_Params...)> : true_type
{};

//若有省略的调用参数
template<typename _Ret, typename... _Params>
struct _Is_funptr<_Ret(__fastcall*) (_Params..., ...)> : true_type
{};

template<typename T>
struct _Is_memfunptr : false_type
{};
//涉及成员函数的调用方法比较复杂，包括const、volatile、const volatile调用
//***************************************************************************************





//***************************************************************************************
//判断引用类型
template<typename T>
struct is_lvalue_reference : false_type
{};

template<typename T>
struct is_lvalue_reference<T&> : true_type
{};

template<typename T>
struct is_rvalue_reference : false_type
{};

template<typename T>
struct is_rvalue_reference<T&&> : true_type
{};


template<typename T>
struct is_reference :_Cat_base<is_lvalue_reference<T>::value || is_rvalue_reference<T>::value >
{};
//***************************************************************************************



//***************************************************************************************
//类型修饰
template<typename T>
struct add_const
{
	typedef const T type;
};

template<typename T>
struct add_volatile
{
	typedef volatile T type;
};

template<typename T>
struct add_cv
{
	typedef const volatile T type;
};

template<typename T>
struct add_reference
{
	typedef T& type;
};

template<typename T>
struct add_lvalue_reference
{
	typedef typename add_reference<T>::type type;
};

template<typename T>
struct add_rvalue_reference
{
	typedef T&& type;
};

template<typename T>
struct remove_extent
{
	typedef T type;
};

template<typename T, unsigned int Ix>
struct remove_extent<T[Ix]>
{
	typedef T type;
};

template<typename T>
struct remove_extent<T[]>
{
	typedef T type;
};

template<typename T>
struct remove_all_extents
{
	typedef T type;
};

template<typename T, unsigned int Ix>
struct remove_all_extents<T[Ix]>
{
	typedef typename remove_all_extents<T>::type type;
};

template<typename T>
struct remove_all_extents<T[]>
{
	typedef typename remove_all_extents<T>::type type;
};


template<typename T>
struct remove_pointer
{
	typedef T type;
};

template<typename T>
struct remove_pointer<T*>
{
	typedef T type;
};

template<typename T>
struct remove_pointer<T* const>
{
	typedef T type;
};

template<typename T>
struct remove_pointer<T* volatile>
{
	typedef T type;
};

template<typename T>
struct remove_pointer<T* const volatile>
{
	typedef T type;
};


template<typename T>
struct add_pointer
{
	typedef typename T* type;
};

//***************************************************************************************






//***************************************************************************************
template<typename T>
struct is_void : false_type
{};

template<>
struct is_void<void> : true_type
{};

template<typename T>
struct is_array : false_type
{};

template<typename T>
struct is_array<T[]>:true_type
{};

template<typename T, unsigned int Ix>
struct is_array<T[Ix]> : true_type
{};

template<typename T>
struct is_pointer : false_type
{};

template<typename T>
struct is_pointer<T*>:true_type
{};

//***************************************************************************************




template<size_t... Values>
struct _Maximum;

template<>
struct _Maximum<>
{
	static const size_t value = 0;
};


template<size_t Value>
struct _Maximum<Value>
{
	static const size_t value = Value;
};

template<size_t First, size_t Second, size_t... Rest>
struct _Maximum<First, Second, Rest...> : _Maximum<(First < Second? Second:First), Rest...>
{};



<<<<<<< HEAD
=======

template<typename T1, typename T2>
struct is_same : false_type
{};

template<typename T>
struct is_same<T, T> : true_type
{};


>>>>>>> ed944bfea73ddb77fbdbf12929e7e26aeeb9924f
FL_LEAVE


#endif
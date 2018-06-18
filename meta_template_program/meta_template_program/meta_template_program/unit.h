#ifndef FLEW_UNIT_H
#define FLEW_UNIT_H

#include "config.h"

#include "vector.h"

FL_ENTER

template<typename T>
struct SI
{
	typedef T unit;
	double value;

	SI() = default;
	SI(double _val) :value(_val){};
};


             //长度   质量    时间    电流   热力学温度 物质的量 发光强度

typedef SI<vector<num<0>, num<0>, num<0>, num<0>, num<0>, num<0>, num<0> > >	SI_none;
typedef SI<vector<num<1>, num<0>, num<0>, num<0>, num<0>, num<0>, num<0> > >	SI_m;
typedef SI<vector<num<0>, num<1>, num<0>, num<0>, num<0>, num<0>, num<0> > >	SI_kg;
typedef SI<vector<num<0>, num<0>, num<1>, num<0>, num<0>, num<0>, num<0> > >	SI_s;
typedef SI<vector<num<0>, num<0>, num<0>, num<1>, num<0>, num<0>, num<0> > >	SI_A;
typedef SI<vector<num<0>, num<0>, num<0>, num<0>, num<1>, num<0>, num<0> > >	SI_K;
typedef SI<vector<num<0>, num<0>, num<0>, num<0>, num<0>, num<1>, num<0> > >	SI_mol;
typedef SI<vector<num<0>, num<0>, num<0>, num<0>, num<0>, num<0>, num<1> > >	SI_cd;

typedef SI<vector<num<1>, num<0>, num<1>, num<0>, num<0>, num<0>, num<0> > >	SI_m_s;
typedef SI<vector<num<1>, num<0>, num<-1>, num<0>, num<0>, num<0>, num<0> > >	SI_m_ds;


template<typename Lhs, typename Rhs, template<typename T, typename U> class Opr>
struct SI_OP
{
	typedef typename Lhs::car								Lfirval;
	typedef typename Lhs::cdr::car							Lsecval;
	typedef typename Lhs::cdr::cdr::car						Lthival;
	typedef typename Lhs::cdr::cdr::cdr::car				Lforval;
	typedef typename Lhs::cdr::cdr::cdr::cdr::car			Lfifval;
	typedef typename Lhs::cdr::cdr::cdr::cdr::cdr::car		Lsixval;
	typedef typename Lhs::cdr::cdr::cdr::cdr::cdr::cdr::car	Lsevval;

	typedef typename Rhs::car								Rfirval;
	typedef typename Rhs::cdr::car							Rsecval;
	typedef typename Rhs::cdr::cdr::car						Rthival;
	typedef typename Rhs::cdr::cdr::cdr::car				Rforval;
	typedef typename Rhs::cdr::cdr::cdr::cdr::car			Rfifval;
	typedef typename Rhs::cdr::cdr::cdr::cdr::cdr::car		Rsixval;
	typedef typename Rhs::cdr::cdr::cdr::cdr::cdr::cdr::car	Rsevval;

	typedef vector
		<
		typename Opr<Lfirval, Rfirval>::type,
		typename Opr<Lsecval, Rsecval>::type,
		typename Opr<Lthival, Rthival>::type,
		typename Opr<Lforval, Rforval>::type,
		typename Opr<Lfifval, Rfifval>::type,
		typename Opr<Lsixval, Rsixval>::type,
		typename Opr<Lsevval, Rsevval>::type
		>
	type;
};

template<typename Lhs, typename Rhs>
struct SI_MUL
{
	typedef typename SI_OP<Lhs, Rhs, add>::type type;
};

template<typename Lhs, typename Rhs>
struct SI_DIV
{
	typedef typename SI_OP<Lhs, Rhs, sub>::type type; 
};

template<typename T, typename U>
inline SI<typename SI_MUL<T, U>::type> operator*(const SI<T>& lhs, const SI<U>& rhs)
{
	return typename lhs.value * rhs.value;
}


template<typename T, typename U>
inline SI<typename SI_DIV<T, U>::type> operator/(const SI<T>& lhs, const SI<U>& rhs)
{
	return typename lhs.value / rhs.value;
}


FL_LEAVE

#endif
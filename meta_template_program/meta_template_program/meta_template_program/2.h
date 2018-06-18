#ifndef ONLY_FOR_TEST_2_H
#define ONLY_FOR_TEST_2_H

#include "config.h"
#include <assert.h>

#include <string>

FL_ENTER


template<typename T>
struct add_const_ref
{
	typedef const T& type;
};

template<typename T>
struct add_const_ref<const T&>
{
	typedef const T& type;
};

template<typename T>
struct add_const_ref<T&>
{
	typedef const T& type;
};

template<typename T>
struct add_const_ref<const T>
{
	typedef const T& type;
};



template<typename Src, typename Str, typename Dest>
struct replace_type
{
	typedef Src type;
};


#define CALL_MULTI_META_FUNC(FUNC) \
	FUNC(const)		\
	FUNC(const &)	\
	FUNC(const *)	\
	FUNC(*)			\
	FUNC(&)			\
	FUNC(* const)	\
	FUNC(const * const)	\


#define _REPLACE_TYPE(CALL_OPT)	\
template<typename Src, typename Dest>	\
struct replace_type<Src CALL_OPT, Src, Dest>	\
{	\
	typedef Dest CALL_OPT type;	\
};
CALL_MULTI_META_FUNC(_REPLACE_TYPE)
#undef _REPLACE_TYPE



template<typename Dest, typename Src>
inline Dest polymorphic_downcast(Src* x)
{
	assert(dynamic_cast<Dest>(x) == x);
	return static_cast<Dest>(x);
}

template<typename Dest, typename Src>
inline Dest polymorphic_downcast(Src& x)
{
	dynamic_cast<Dest>(x);
	return static_cast<Dest>(x);
}



template<typename Dest, typename Src>
struct PolyDownCast;

template<typename Dest, typename Src>
struct PolyDownCast<Dest*, Src*>
{
	Dest* operator()(Src* p) const
	{
		assert(dynamic_cast<Dest*>(p) == p);
		return static_cast<Dest*>(p);
	}
};

template<typename Dest, typename Src>
struct PolyDownCast<Dest&, Src&>
{
	Dest& operator()(Src& p) const
	{
		dynamic_cast<Dest&>(p);
		return static_cast<Dest&>(p);
	}
};



template<typename T>
struct type_descriptor;

template<>
struct type_descriptor<char>
{
	std::string operator()() const
	{
		return "char";
	}
};

template<typename T>
struct type_descriptor<T[]>
{
	std::string operator()() const
	{
		return "array of " + type_descriptor<T>()();
	}
};

template<typename T>
struct type_descriptor<T*>
{
	std::string operator()() const
	{
		return "pointer to " + type_descriptor<T>()();
	}
};

template<typename T>
struct type_descriptor<T&>
{
	std::string operator()() const
	{
		return "reference to " + type_descriptor<T>()();
	}
};

template<typename Dest, typename... Src>
struct type_descriptor<Dest(*) (Src...)>
{
	std::string operator()() const
	{
		return "pointer to function returning " + type_descriptor<Dest>()();
	}
};






//template<typename T>
//std::string type_descriptor<T*>()
//{
//	return std::string("pointer to ") + type_descriptor<T>();
//}




FL_LEAVE





#endif
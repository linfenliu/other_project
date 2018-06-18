#ifndef ITERATOR_TRAITS_H
#define ITERATOR_TRAITS_H

#include "config.h"

FL_ENTER

template<typename Iterator>
struct iterator_traits
{
	typedef Iterator::value_type value_type;
	typedef Iterator::reference reference;
	typedef Iterator::pointer pointer;
	typedef Iterator::difference_type difference_type;
	typedef Iterator::iterator_category iterator_category;
};



FL_LEAVE


#endif
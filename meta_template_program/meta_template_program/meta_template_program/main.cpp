#include <iostream>
#include "conversion_of_number.h"
#include "color.h"
#include "type_traits.h"
#include <type_traits>
//#include "2.h"
//#include "3.h"
#include "unit.h"

class Base
{
	virtual void a(){};
};

class Derived : public Base
{

};

class Base1{};

int main(int argc, const char * argv[])
{
	using namespace FL;

  /*  std::cout << DecToBinary<0>::value << std::endl;
    std::cout << DecToBinary<5>::value << std::endl;
    
    
    std::cout << BinaryToDec<101>::value << std::endl;
    
    std::cout << ColorRGB<Red>::value << std::endl;
    std::cout << ColorRGB<White>::value << std::endl;
    std::cout << ColorRGB<Black>::value << std::endl;
    
	std::cout << is_reference<int&>::value << std::endl;
	std::cout << is_reference<int>::value << std::endl;

<<<<<<< HEAD
	
=======
	std::cout << is_array<int[]>::value << std::endl;
	std::cout << is_array<int>::value << std::endl;*/



	/*std::cout << is_same<add_const_ref<int>::type, int>::value << std::endl;
	std::cout << is_same<add_const_ref<int&>::type, int&>::value << std::endl;
>>>>>>> ed944bfea73ddb77fbdbf12929e7e26aeeb9924f
    
	std::cout << type_descriptor<char*&(*[])()>()() << '\n';

	m m0 = { 1.0 };
	a a0 = { 2.0 };

	auto f0 = m0 * a0;

	typedef mpl_vector<char, int, double, int*> test_mpl;

	test_mpl::car mpl_char = 'a';
	test_mpl::cdr::car mpl_int = 10;
	test_mpl::cdr::cdr::car mpl_double = 10.0;
	test_mpl::cdr::cdr::cdr::car mpl_intx = new int(10);

	std::cout << is_vector<test_mpl>::value << '\t' << is_vector<int>::value << '\n' ;

	std::cout << mpl_find<test_mpl, bool>::value << '\n';

	std::cout << mpl_find<test_mpl, int**>::value << '\n';

	std::cout << mpl_find<test_mpl, Nil>::value << '\n';*/

	SI_m length = 5;
	SI_s time = 10;

	SI_m_s xxx = length * time;
	SI_m_ds yyy = length / time;

	typedef vector<int, char> test_vector;

	std::cout << find_in_vector<test_vector, int>::value << std::endl;

    return 0;
}

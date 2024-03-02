/**
 * @file test_function_tratis.cpp
 * @author Teruaki Ata (PFA03027@nifty.com)
 * @brief
 * @version 0.1
 * @date 2024-03-02
 *
 * @copyright Copyright (c) 2024, Teruaki Ata (PFA03027@nifty.com)
 *
 */

#include <cstdlib>
#include <iostream>

#include "function_traits.hpp"

struct fc {
	long operator()( short x )
	{
		return x;
	}

	long mf( short, int, double )
	{
		return 1;
	}
};

void f( double x )
{
	std::cout << "call double: " << x << std::endl;
}

void g( double x, int y )
{
	std::cout << "call double: " << x << "  int: " << y << std::endl;
}

int main( void )
{
	std::cout << typeid( function_traits<decltype( f )>::function_type ).name() << std::endl;

	static_assert( function_traits<decltype( f )>::size_of_args == 1, "It should be 1" );
	static_assert( function_traits<decltype( g )>::size_of_args == 2, "It should be 2" );
	static_assert( function_traits<fc>::size_of_args == 1, "It should be 1" );
	static_assert( function_traits<decltype( &fc::mf )>::size_of_args == 3, "It should be 3" );

	static_assert( std::is_same<function_traits<decltype( f )>::nth_argument_type<0>, double>::value, "It should be double" );
	static_assert( std::is_same<function_traits<decltype( g )>::nth_argument_type<0>, double>::value, "It should be double" );
	static_assert( std::is_same<function_traits<decltype( g )>::nth_argument_type<1>, int>::value, "It should be int" );
	static_assert( std::is_same<function_traits<fc>::nth_argument_type<0>, short>::value, "It should be short" );
	static_assert( std::is_same<function_traits<decltype( &fc::mf )>::nth_argument_type<0>, short>::value, "It should be short" );
	static_assert( std::is_same<function_traits<decltype( &fc::mf )>::nth_argument_type<1>, int>::value, "It should be int" );
	static_assert( std::is_same<function_traits<decltype( &fc::mf )>::nth_argument_type<2>, double>::value, "It should be double" );

	static_assert( std::is_same<function_traits<decltype( f )>::return_type, void>::value, "It should be void" );
	static_assert( std::is_same<function_traits<decltype( g )>::return_type, void>::value, "It should be void" );
	static_assert( std::is_same<function_traits<fc>::return_type, long>::value, "It should be long" );
	static_assert( std::is_same<function_traits<decltype( &fc::mf )>::return_type, long>::value, "It should be long" );

	return EXIT_SUCCESS;
}
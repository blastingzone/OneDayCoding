#include <regex>
// by regex

bool isNumber(const char* c)
{
	// re1 == (+-)number?
	std::regex re1( "[' ']*[+-]?[0-9]+[' ']*" );
	// == regex re1( "[' ']*[0-9]+[' ']*" );

	// re2 == (+-)number(.)( e )(+-)number?
	std::regex re2( "[' ']*[+-]?[0-9]+[.]?e[+-]?[0-9]+[' ']*" );

	// re3 ==  (+-)number.(number)?
	std::regex re3( "[' ']*[+-]?[0-9]+[.][0-9]*[' ']*" );

	// re4 ==  (+-)(number).number?
	std::regex re4( "[' ']*[+-]?[0-9]*[.][0-9]+[' ']*" );
	
	bool test1 = std::regex_match( c, re1 );
	bool test2 = std::regex_match( c, re2 );
	bool test3 = std::regex_match( c, re3 );
	bool test4 = std::regex_match( c, re4 );

	return ( std::regex_match( c, re1 ) || std::regex_match( c, re2 ) || std::regex_match( c, re3 ) || std::regex_match( c, re4 ) );
}


void PrintTestSet( const char* test )
{
	printf( "test : %s : \"%s\"\n", isNumber( test ) ? "true" : "false", test );
}

void main()
{
	const char* test1 = "12345";
	const char* test2 = "     12345 ";
	const char* test3 = " 123e1234 ";
	const char* test4 = "abcd";
	const char* test5 = "1.0";
	const char* test6 = "0";
	const char* test7 = "1 a";
	const char* test8 = "2e10";
	const char* test9 = "2eee10";
	const char* test10 = "2e"; // false
	const char* test11 = "3.e5"; // true
	const char* test12 = "+3."; // true
	const char* test13 = "+"; // false
	const char* test14 = "+++3"; // false
	const char* test15 = "-+3."; // false
	const char* test16 = "-3.e-5"; // true
	const char* test17 = "3.e+5"; // true
	const char* test18 = "+3.e5"; // true
	const char* test19 = "  "; // false


	PrintTestSet( test1 );
	PrintTestSet( test2 );
	PrintTestSet( test3 );
	PrintTestSet( test4 );
	PrintTestSet( test5 );
	PrintTestSet( test6 );
	PrintTestSet( test7 );
	PrintTestSet( test8 );
	PrintTestSet( test9 );
	PrintTestSet( test10 );
	PrintTestSet( test11 );
	PrintTestSet( test12 );
	PrintTestSet( test13 );
	PrintTestSet( test14 );
	PrintTestSet( test15 );
	PrintTestSet( test16 );
	PrintTestSet( test17 );
	PrintTestSet( test18 );
	PrintTestSet( test19 );


	getchar();

	return;
}
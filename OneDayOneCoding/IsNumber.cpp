#include <regex>
// by regex

using namespace std;

bool isNumber(const char* c)
{
	// re1 == number?
	basic_regex<char> re1( "[' ']*[0-9]+[' ']*" );
	// == regex re1( "[' ']*[0-9]+[' ']*" );

	// re2 == number( e )number?
	basic_regex<char> re2( "[' ']*[0-9]+e[0-9]+[' ']*" );

	// re3 == number.number?
	basic_regex<char> re3( "[' ']*[0-9]+[.][0-9]+[' ']*" );

	return ( std::regex_match(c, re1) || std::regex_match(c, re2) || std::regex_match(c, re3));
}


void main()
{
	const char* test1 = "12345";
	const char* test2 = " 12345 ";
	const char* test3 = " 123e1234 ";
	const char* test4 = "abcd";
	const char* test5 = "1.0";
	const char* test6 = "0";
	const char* test7 = "1 a";
	const char* test8 = "2e10";

	printf( "test 1 : %s : %s\n", isNumber( test1 ) ? "true" : "false" , test1 );
	printf( "test 2 : %s : %s\n", isNumber( test2 ) ? "true" : "false" , test2 );
	printf( "test 3 : %s : %s\n", isNumber( test3 ) ? "true" : "false", test3 );
	printf( "test 4 : %s : %s\n", isNumber( test4 ) ? "true" : "false", test4 );
	printf( "test 5 : %s : %s\n", isNumber( test5 ) ? "true" : "false", test5 );
	printf( "test 6 : %s : %s\n", isNumber( test6 ) ? "true" : "false", test6 );
	printf( "test 7 : %s : %s\n", isNumber( test7 ) ? "true" : "false", test7 );
	printf( "test 8 : %s : %s\n", isNumber( test8 ) ? "true" : "false", test8 );

	getchar();

	return;
}
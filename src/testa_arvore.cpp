#ifndef CATCH_CONFIG_MAIN
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#endif  // CATCH_CONFIG_MAIN

#ifndef  CATCH_H_INCLUDED   // SE CATCH JÁ TIVER SIDO INCORPORADO ANTERIORMENTE, ELE NÃO FAZ DE NOVO
#define  CATCH_H_INCLUDED
#include "catch.hpp"



unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? 1 : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(0) == 1 );
    REQUIRE_FALSE( Factorial(0) == 2 );
    REQUIRE( Factorial(10) == 3628800 );
}


#endif //CATCH_H_INCLUDED

// Use array_view

#include "gsl-lite.h"
#include <iostream>

using namespace gsl;

void bad( int * arr, size_t num )
{
    for ( size_t i = 0; i != num; ++i )
    {
        std::cout << (i==0 ? "[":"") << arr[i] << (i!=num-1 ? ", ":"]\n"); 
    }
}

void good( array_view<int> arr )
{
    for ( size_t i = 0; i != arr.size(); ++i )
    {
        std::cout << (i==0 ? "[":"") << arr[i] << (i!=arr.size()-1 ? ", ":"]\n"); 
    }
}

int main()
{
    int arr[] = { 1, 2, 3, 4, 5, };
    
    bad(  arr, gsl_DIMENSION_OF(arr) ); // specify elements and length separately
    good( arr );                        // deduce length

    bad(  arr, 3 );                     // fine-ish
    bad(  arr, 7 );                     // WRONG, array length exceeded

#if  gsl_CPP11_OR_GREATER
    good( { arr, 3 } );                 // fine
    good( { arr, 7 } );                 // run-time error, terminate
#else
    good( array_view<int>( arr, 3 ) );  // fine
    good( array_view<int>( arr, 7 ) );  // run-time error, terminate
#endif
}

#if 0
cl -EHsc -I../include/gsl 02-array_view.cpp && 02-array_view.exe
g++ -std=c++03 -Wall -I../include/gsl -o 02-array_view.exe 02-array_view.cpp && 02-array_view.exe
#endif 

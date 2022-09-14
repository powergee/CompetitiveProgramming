#include <algorithm>
#include <cstdio>
#include <cstring>

#define MAXT 300000
#define MAXA 25

int lenA, lenT;
char T[MAXT+1];
char A[MAXA+1];

struct stack {
   int top;
   char x[MAXT+1];
   char w[MAXA];

   void init( char *A ) {
      for( int i = 0; i < lenA; ++i ) w[i] = A[lenA-1-i];
      top = 0;
   }

   int add( char c ) {
      int ret = 0;
      x[top++] = c;
      if( top >= lenA ) {
         ret = 1;
         for( int i = 0; i < lenA; ++i ) 
            if( x[top-i-1] != w[i] ) 
               ret = 0;
         if( ret ) top -= lenA;
      }
      return ret;
   }
} L, D;

int main( void ) {
   scanf("%s", A);
   lenA = strlen( A );
   scanf("%s", T);
   lenT = strlen( T );
   L.init( A );
   std::reverse( A, A+lenA );
   D.init( A );

   int turn = 0;
   int lpos = 0, dpos = lenT-1;
   while( lpos <= dpos ) 
      if( turn == 0 ) turn ^= L.add( T[lpos++] );
      else turn ^= D.add( T[dpos--] );

   while( L.top ) D.add( L.x[--L.top] );

   while( D.top ) printf( "%c", D.x[--D.top] );
   
   return 0;
}

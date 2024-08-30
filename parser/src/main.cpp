#include "calculator.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
   // Fibonacci number in sequence
   // 23's number shall be 17711
   std::string e = R"(
    {
      foo(a, b)
      {
        print(a);
      }
      foo(a,b);
      n = 23;  
      a = 0;
      b = 1;
      i = 2;
      while( i < n )
      {
          c = a + b;
          a = b;
          b = c;
          i = i + 1;
      }
      print(b); 
    })";
   //
   //        if(3 < 2)
   //        {
   //            print(123);
   //
   //            3+5;
   //        }
   //        print(456);
   //
   //        2 < 3;
   //        2 > 3;
   //        -1+3;
   //        {
   //            2+2;
   //        }
   //    std::string e = "((-1+2)-3)";
   //    std::string e = "{a=5+5;b=10+17;}";

   //    int n = 5;
   //    for (int i=1; i<n; ++i)
   //    {
   //        if( i % 2 == 0 )
   //        {
   //            e += std::to_string(i)+"+";
   //        }
   //        else
   //        {
   //            e += std::to_string(i)+"*";
   //        }
   //    }
   //    e += std::to_string(n);
   std::cout << e << std::endl;

   Calculator calculator;
   auto result0 = calculator.solve( e );
   cout << result0 << std::endl;
   return 0;
}

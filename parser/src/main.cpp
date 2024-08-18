#include "calculator.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
   std::string e = R"(
    {
      if(2 < 3)
      {
          print(123);

          1+(3+5);
      }
      print(456);
    })";

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

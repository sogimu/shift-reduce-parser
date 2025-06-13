// #include <catch2/catch_session.hpp>
#include <gtest/gtest.h>

int main( int argc, char* argv[] )
{
   // your setup ...

   // int result = Catch::Session().run( argc, argv );

   // your clean-up...

   // return result;
   ::testing::InitGoogleTest( &argc, argv );

   return RUN_ALL_TESTS();
}

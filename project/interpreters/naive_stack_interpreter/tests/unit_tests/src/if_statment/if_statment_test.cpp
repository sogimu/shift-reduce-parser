#include "interpreter.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_IF_STATMENT, VARIBLE_LESS_INT )
{
   // ARRANGE
   const auto& input = R"""({var a = 231; if( a < 1000 ) { return 234; } })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 234 );
}

TEST( NAIVE_STACK_INTERPRETER_IF_STATMENT, INT_LESS_INT )
{
   // ARRANGE
   const auto& input = R"""({if( 1 < 1000 ) { return 234; } })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 234 );
}

TEST( NAIVE_STACK_INTERPRETER_IF_STATMENT, BIN_EXPR_LESS_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""({if( 1+2 < 1000+2000 ) { return 234; } })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 234 );
}

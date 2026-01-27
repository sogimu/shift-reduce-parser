#include "interpreter.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_FUNCTION_CALL, RETURN_INT )
{
   // ARRANGE
   const auto& input = R"""({ function foo() { return 234; } return foo(); })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 234 );
}

TEST( NAIVE_STACK_INTERPRETER_FUNCTION_CALL, CALL_IS_INT )
{
   // ARRANGE
   const auto& input = R"""({ function foo(val) { return 234 + val; } return foo(1); })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 235 );
}

TEST( NAIVE_STACK_INTERPRETER_FUNCTION_CALL, BIN_EXPR_LESS_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""({ var counter = 0; function foo(val) { print(val); counter = counter + 1; if( val > 0 ) { foo(val-1); } } foo(5); return counter; })""";

   // ACT
   Interpreter interpreter;
   auto result = interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result.is_int(), true );
   EXPECT_EQ( result.get_int(), 234 );
}

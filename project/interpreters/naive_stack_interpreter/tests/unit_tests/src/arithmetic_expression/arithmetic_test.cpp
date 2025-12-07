#include "interpreter.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, NUMBER_INT )
{
   // ARRANGE
   const auto& input = R"""(1;)""";

   // ACT
   Interpreter naive_stack_machine;
   auto result = naive_stack_machine.eval( input );

   // ASSERT
   EXPECT_EQ( result, 1 );
}

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, BIN_EXPR_INT_ADDITION_INT )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";

   // ACT
   Interpreter naive_stack_machine;
   auto result = naive_stack_machine.eval( input );

   // ASSERT
   EXPECT_EQ( result, 3 );
}

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, RETURN_INT )
{
   // ARRANGE
   const auto& input = R"""(return 1;)""";

   // ACT
   Interpreter naive_stack_machine;
   auto result = naive_stack_machine.eval( input );

   // ASSERT
   EXPECT_EQ( result, 1 );
}

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, FUNCTION_CALL_INT )
{
   // ARRANGE
   const auto& input = R"""({ function foo(arg){ return arg+1; } foo(1); } )""";

   // ACT
   Interpreter naive_stack_machine;
   auto result = naive_stack_machine.eval( input );

   // ASSERT
   EXPECT_EQ( result, 2 );
}


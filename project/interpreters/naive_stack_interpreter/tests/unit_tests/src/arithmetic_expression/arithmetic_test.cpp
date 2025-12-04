#include "interpreter.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(1;)""";

   // ACT
  Interpreter naive_stack_machine;
   auto result = naive_stack_machine.eval( input );

   // ASSERT
   EXPECT_EQ( result, 1 );
}


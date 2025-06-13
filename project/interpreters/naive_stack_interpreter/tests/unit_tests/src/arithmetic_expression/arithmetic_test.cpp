#include "naive_stack_interpreter.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAIVE_STACK_INTERPRETER_ARITHMETIC, INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(1;)""";

   // ACT
   NaiveStackInterpreter naive_stack_interpreter;
   auto result = naive_stack_interpreter.eval( input );

   // ASSERT
   EXPECT_EQ( result, 1 );
}


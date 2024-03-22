#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NameSyntaxNode, Test0 )
{
   // ARRANGE
   const auto& input = R"""(A=2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "A", Token_Type::NAME },
                                            { "=", Token_Type::EQUAL },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

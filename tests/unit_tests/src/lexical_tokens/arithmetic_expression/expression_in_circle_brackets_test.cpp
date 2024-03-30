#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

TEST( EXPRESSIONS_IN_CIRCLE_BRACKETS, DIVIDE_IN_CIRCLIE_BRACKETS )
{
   // ARRANGE
   const auto& input = R"""((1/2);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "(", Token_Type::OPEN_CIRCLE_BRACKET },
                                            { "1", Token_Type::INT },
                                            { "/", Token_Type::DIVIDE },
                                            { "2", Token_Type::INT },
                                            { ")", Token_Type::CLOSE_CIRCLE_BRACKET },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( EXPRESSIONS_IN_CIRCLE_BRACKETS, ADVANCE_EXPRESSION )
{
   // ARRANGE
   const auto& input = R"""((1/2)*2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "(", Token_Type::OPEN_CIRCLE_BRACKET },
                                            { "1", Token_Type::INT },
                                            { "/", Token_Type::DIVIDE },
                                            { "2", Token_Type::INT },
                                            { ")", Token_Type::CLOSE_CIRCLE_BRACKET },
                                            { "*", Token_Type::MULTIPLY },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

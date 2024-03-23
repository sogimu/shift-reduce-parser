#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

TEST( NAME, Test0 )
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

TEST( PLUS, Test0 )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "1", Token_Type::INT },
                                            { "+", Token_Type::PLUS },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( MINUS, Test0 )
{
   // ARRANGE
   const auto& input = R"""(1-2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "1", Token_Type::INT },
                                            { "-", Token_Type::MINUS },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( MULTIPLY, Test0 )
{
   // ARRANGE
   const auto& input = R"""(1*2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "1", Token_Type::INT },
                                            { "*", Token_Type::MULTIPLY },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( DIVIDE, Test0 )
{
   // ARRANGE
   const auto& input = R"""(1/2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "1", Token_Type::INT },
                                            { "/", Token_Type::DIVIDE },
                                            { "2", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( ARITHMETIC_EXPRESSIONS, Test0 )
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

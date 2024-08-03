#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

TEST( DIVISION, ONE_DIVIDE )
{
   // ARRANGE
   const auto& input = R"""(1/2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{
      { { "", Token_Type::BOL }, { "1", Token_Type::INT }, { "/", Token_Type::SLASH }, { "2", Token_Type::INT }, { ";", Token_Type::SEMICOLON }, { "", Token_Type::EOL } }
   };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

TEST( DIVISION, MANY_DIVIDEs )
{
   // ARRANGE
   const auto& input = R"""(1/2/3;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens expected_lexical_tokens{ { { "", Token_Type::BOL },
                                            { "1", Token_Type::INT },
                                            { "/", Token_Type::SLASH },
                                            { "2", Token_Type::INT },
                                            { "/", Token_Type::SLASH },
                                            { "3", Token_Type::INT },
                                            { ";", Token_Type::SEMICOLON },
                                            { "", Token_Type::EOL } } };
   EXPECT_EQ( lexical_tokens, expected_lexical_tokens );
}

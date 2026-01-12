#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( LEXICAL_TOKENS_NUMBERS, INT )
{
   // ARRANGE
   const auto& input = R"""(
    1
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="1", .type=Token_Type::INT, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[2], t2 );
}

TEST( LEXICAL_TOKENS_NUMBERS, DOUBLE_SHORT )
{
   // ARRANGE
   const auto& input = R"""(
    1.2
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="1.2", .type=Token_Type::DOUBLE, .line=1, .col=4, .length=3 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[2], t2 );
}

TEST( LEXICAL_TOKENS_NUMBERS, DOUBLE_LONG )
{
   // ARRANGE
   const auto& input = R"""(
    12.23
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="12.23", .type=Token_Type::DOUBLE, .line=1, .col=4, .length=5 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[2], t2 );
}

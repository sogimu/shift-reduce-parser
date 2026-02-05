#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( LEXICAL_TOKENS_STRINGS, LITERAL )
{
   // ARRANGE
   const auto& input = R"""(
    "qwerty23w"
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="qwerty23w", .type=Token_Type::STRING, .line=1, .col=4, .length=9 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[2], t2 );
}

TEST( LEXICAL_TOKENS_STRINGS, LITERAL_ASSIGMENT )
{
   // ARRANGE
   const auto& input = R"""(
    a = "qwerty23w"
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="a", .type=Token_Type::NAME, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="=", .type=Token_Type::EQUAL, .line=1, .col=6, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="qwerty23w", .type=Token_Type::STRING, .line=1, .col=8, .length=9 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[4], t4 );
}

TEST( LEXICAL_TOKENS_STRINGS, LITERAL_WITH_SPACE_ASSIGMENT )
{
   // ARRANGE
   const auto& input = R"""(
    a = "qwerty 23w"
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="a", .type=Token_Type::NAME, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="=", .type=Token_Type::EQUAL, .line=1, .col=6, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="qwerty 23w", .type=Token_Type::STRING, .line=1, .col=8, .length=10 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[4], t4 );
}

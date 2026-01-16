#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( LEXICAL_TOKENS_OBJECTS, DEFINITION )
{
   // ARRANGE
   const auto& input = R"""(
    {"key": 12, "key1": 42}
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="{", .type=Token_Type::OPEN_CURLY_BRACKET, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="key", .type=Token_Type::STRING, .line=1, .col=5, .length=3 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text=":", .type=Token_Type::COLON, .line=1, .col=10, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text="12", .type=Token_Type::INT, .line=1, .col=12, .length=2 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text=",", .type=Token_Type::COMMA, .line=1, .col=14, .length=1 };
   EXPECT_EQ( lexical_tokens[5], t5 );
   LexicalTokens::LexicalToken t6{ .text="key1", .type=Token_Type::STRING, .line=1, .col=16, .length=4 };
   EXPECT_EQ( lexical_tokens[6], t6 );
   LexicalTokens::LexicalToken t7{ .text=":", .type=Token_Type::COLON, .line=1, .col=22, .length=1 };
   EXPECT_EQ( lexical_tokens[7], t7 );
   LexicalTokens::LexicalToken t8{ .text="42", .type=Token_Type::INT, .line=1, .col=24, .length=2 };
   EXPECT_EQ( lexical_tokens[8], t8 );
   LexicalTokens::LexicalToken t9{ .text="}", .type=Token_Type::CLOSE_CURLY_BRACKET, .line=1, .col=26, .length=1 };
   EXPECT_EQ( lexical_tokens[9], t9 );
   LexicalTokens::LexicalToken t10{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[10], t10 );
}

TEST( LEXICAL_TOKENS_OBJECTS, SUBSCRIPT_OPERATOR )
{
   // ARRANGE
   const auto& input = R"""(
    a["key"]
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="a", .type=Token_Type::NAME, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="[", .type=Token_Type::OPEN_SQUARE_BRACKET, .line=1, .col=5, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="key", .type=Token_Type::STRING, .line=1, .col=6, .length=3 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text="]", .type=Token_Type::CLOSE_SQUARE_BRACKET, .line=1, .col=11, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[5], t5 );
}

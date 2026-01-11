#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( LEXICAL_TOKENS_ADDITION, ONE_PLUS )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="1", .type=Token_Type::NUMBER, .line=0, .col=0, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="+", .type=Token_Type::PLUS, .line=0, .col=1, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="2", .type=Token_Type::NUMBER, .line=0, .col=2, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text=";", .type=Token_Type::SEMICOLON, .line=0, .col=3, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[5], t5 );
}

TEST( LEXICAL_TOKENS_ADDITION, MANY_PLUSs )
{
   // ARRANGE
   const auto& input = R"""(1+2+3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="1", .type=Token_Type::NUMBER, .line=0, .col=0, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="+", .type=Token_Type::PLUS, .line=0, .col=1, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="2", .type=Token_Type::NUMBER, .line=0, .col=2, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text="+", .type=Token_Type::PLUS, .line=0, .col=3, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="3", .type=Token_Type::NUMBER, .line=0, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[5], t5 );
   LexicalTokens::LexicalToken t6{ .text="+", .type=Token_Type::PLUS, .line=0, .col=5, .length=1 };
   EXPECT_EQ( lexical_tokens[6], t6 );
   LexicalTokens::LexicalToken t7{ .text="4", .type=Token_Type::NUMBER, .line=0, .col=6, .length=1 };
   EXPECT_EQ( lexical_tokens[7], t7 );
   LexicalTokens::LexicalToken t8{ .text=";", .type=Token_Type::SEMICOLON, .line=0, .col=7, .length=1 };
   EXPECT_EQ( lexical_tokens[8], t8 );
   LexicalTokens::LexicalToken t9{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[9], t9 );
}

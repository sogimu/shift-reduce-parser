#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( VARIBLE_EXPRESSION, SIMPLE_ASSIGMENT )
{
   // ARRANGE
   const auto& input = R"""(A=2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="A", .type=Token_Type::NAME, .line=0, .col=0, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="=", .type=Token_Type::EQUAL, .line=0, .col=1, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="2", .type=Token_Type::NUMBER, .line=0, .col=2, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text=";", .type=Token_Type::SEMICOLON, .line=0, .col=3, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[5], t5 );
}

TEST( VARIBLE_EXPRESSION, SIMPLE_ASSIGMENT_LONG_NAME )
{
   // ARRANGE
   const auto& input = R"""(abc=2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="abc", .type=Token_Type::NAME, .line=0, .col=0, .length=3 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text="=", .type=Token_Type::EQUAL, .line=0, .col=3, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="2", .type=Token_Type::NUMBER, .line=0, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text=";", .type=Token_Type::SEMICOLON, .line=0, .col=5, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[5], t5 );
}

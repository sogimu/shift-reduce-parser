#include "lexical_tokens.h"

#include <gtest/gtest.h>

using namespace std;

TEST( MULTILINES, TEST0 )
{
   // ARRANGE
   const auto& input = R"""(
    1;
    2;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );

   // ASSERT
   LexicalTokens::LexicalToken t0{ .text="", .type=Token_Type::BOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[0], t0 );
   LexicalTokens::LexicalToken t1{ .text="1", .type=Token_Type::INT, .line=1, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[1], t1 );
   LexicalTokens::LexicalToken t2{ .text=";", .type=Token_Type::SEMICOLON, .line=1, .col=5, .length=1 };
   EXPECT_EQ( lexical_tokens[2], t2 );
   LexicalTokens::LexicalToken t3{ .text="2", .type=Token_Type::INT, .line=2, .col=4, .length=1 };
   EXPECT_EQ( lexical_tokens[3], t3 );
   LexicalTokens::LexicalToken t4{ .text=";", .type=Token_Type::SEMICOLON, .line=2, .col=5, .length=1 };
   EXPECT_EQ( lexical_tokens[4], t4 );
   LexicalTokens::LexicalToken t5{ .text="", .type=Token_Type::EOL, .line=0, .col=0, .length=0 };
   EXPECT_EQ( lexical_tokens[5], t5 );
}

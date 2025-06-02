#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_VARIBLE_ASSIGN, F )
{
   // ARRANGE
   const auto& input = R"""(
      a=1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "VaribleAssigmentStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "FSyntaxNode": [
            1
          ]
        }
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_VARIBLE_ASSIGN, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      a=1+2;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "VaribleAssigmentStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "BinExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                2
              ]
            },
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        }
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_VARIBLE_ASSIGN, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      a=-1;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "VaribleAssigmentStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "UnExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        }
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_VARIBLE_ASSIGN, NAME )
{
   // ARRANGE
   const auto& input = R"""(
      a=b;
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "VaribleAssigmentStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "NameSyntaxNode": [
            "b"
          ]
        }
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
TEST( SYNTAX_TREE_VARIBLE_ASSIGN, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      a=foo(1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "VaribleAssigmentStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "FunctionCallSyntaxNode": [
            "foo",
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        }
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

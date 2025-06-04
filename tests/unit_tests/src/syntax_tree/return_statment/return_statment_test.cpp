#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_RETURN_STATMENT, F )
{
   // ARRANGE
   const auto& input = R"""(
      return 1;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "ReturnStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_RETURN_STATMENT, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      return 1+2;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "ReturnStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_RETURN_STATMENT, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
      return -1;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "ReturnStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_RETURN_STATMENT, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
      return foo(1);
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "ReturnStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_RETURN_STATMENT, NAME )
{
   // ARRANGE
   const auto& input = R"""(
      return a;
  )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "ReturnStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
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

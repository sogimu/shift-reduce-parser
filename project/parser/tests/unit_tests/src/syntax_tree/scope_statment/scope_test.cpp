#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_F_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      2;
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "ScopeSyntaxNode": [
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            1
          ]
        }
      ]
    },
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            2
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

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_F )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      2
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "ScopeSyntaxNode": [
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            1
          ]
        }
      ]
    },
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            2
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

TEST( SYNTAX_TREE_SCOPE, F_SEMICOLON_VARIBLE_ASSIGMENT )
{
   // ARRANGE
   const auto& input = R"""(
    {
      1;
      a=2
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "ScopeSyntaxNode": [
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            1
          ]
        }
      ]
    },
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
                2
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

TEST( SYNTAX_TREE_SCOPE, NESTED_SCOPE )
{
   // ARRANGE
   const auto& input = R"""(
    {
      { 
        1;
        2;
      }
      3;
      4;
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "ScopeSyntaxNode": [
    {
      "ScopeSyntaxNode": [
        {
          "StatmentSyntaxNode": [
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        },
        {
          "StatmentSyntaxNode": [
            {
              "FSyntaxNode": [
                2
              ]
            }
          ]
        }
      ]
    },
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            3
          ]
        }
      ]
    },
    {
      "StatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            4
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

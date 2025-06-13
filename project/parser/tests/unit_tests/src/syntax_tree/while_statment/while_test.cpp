#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_WHILE, F_EQUAL_F )
{
   // ARRANGE
   const auto& input = R"""(
    while(1==1)
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "BinExprSyntaxNode": [
            4,
            {
              "FSyntaxNode": [
                1
              ]
            },
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, F )
{
   // ARRANGE
   const auto& input = R"""(
    while(1)
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "FSyntaxNode": [
            1
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, NAME )
{
   // ARRANGE
   const auto& input = R"""(
    while(a)
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "NameSyntaxNode": [
            "a"
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    while(1+2)
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
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
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    while(-1)
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "UnExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
    while(foo(1))
    {
    
    }
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "FunctionCallSyntaxNode": [
            "foo",
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_WHILE, IF_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(
    while(foo(1))
    {
    
    };
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "WhileStatmentSyntaxNode": [
        {
          "FunctionCallSyntaxNode": [
            "foo",
            {
              "FSyntaxNode": [
                1
              ]
            }
          ]
        },
        {
          "ScopeSyntaxNode": []
        }
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_IF, F_EQUAL_F )
{
   // ARRANGE
   const auto& input = R"""(
    if(1==1)
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, F )
{
   // ARRANGE
   const auto& input = R"""(
    if(1)
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, NAME )
{
   // ARRANGE
   const auto& input = R"""(
    if(a)
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    if(1+2)
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    if(-1)
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
    if(foo(1))
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
      "IfStatmentSyntaxNode": [
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

TEST( SYNTAX_TREE_IF, IF_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(
    if(foo(1))
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
      "IfStatmentSyntaxNode": [
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

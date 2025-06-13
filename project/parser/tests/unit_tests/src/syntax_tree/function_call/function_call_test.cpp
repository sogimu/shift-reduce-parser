#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ZERO_VARIBLE )
{
   // ARRANGE
   const auto& input = R"""(
    foo();
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo"
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_VARIBLE )
{
   // ARRANGE
   const auto& input = R"""(
    foo(a);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
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

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_VARIBLIES )
{
   // ARRANGE
   const auto& input = R"""(
    foo(a,b);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
        {
          "NameSyntaxNode": [
            "b"
          ]
        },
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
TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_F )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
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
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_F )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1,2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
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
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1+2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
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

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(1+2,3+4);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
        {
          "BinExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                4
              ]
            },
            {
              "FSyntaxNode": [
                3
              ]
            }
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
TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(-1);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
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

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_UN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(
    foo(-1,-2);
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
        {
          "UnExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                2
              ]
            }
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

TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_ONE_FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(
    foo(bar(1));
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
        {
          "FunctionCallSyntaxNode": [
            "bar",
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
TEST( SYNTAX_TREE_FUNCTION_CALL, FROM_TWO_FUNCTION_CALLS )
{
   // ARRANGE
   const auto& input = R"""(
    foo( bar(1), zigbee(2) );
   )""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FunctionCallSyntaxNode": [
        "foo",
        {
          "FunctionCallSyntaxNode": [
            "zigbee",
            {
              "FSyntaxNode": [
                2
              ]
            }
          ]
        },
        {
          "FunctionCallSyntaxNode": [
            "bar",
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

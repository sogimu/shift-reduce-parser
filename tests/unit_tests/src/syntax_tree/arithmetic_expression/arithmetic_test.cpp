#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_ARITHMETIC, INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(1;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FSyntaxNode": [
        1
      ]
    }
  ]
}
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_ARITHMETIC, MINUS_INT_SEMICOLON )
{
   // ARRANGE
   const auto& input = R"""(-1;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
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
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}
TEST( SYNTAX_TREE_ARITHMETIC, UN_EXPR_LAST )
{
   // ARRANGE
   const auto& input = R"""(1--2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        1,
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

TEST( SYNTAX_TREE_ARITHMETIC, UN_EXPR_NOT_LAST )
{
   // ARRANGE
   const auto& input = R"""(-2-1;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        1,
        {
          "FSyntaxNode": [
            1
          ]
        },
        {
          "UnExprSyntaxNode": [
            0,
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
TEST( SYNTAX_TREE_ARITHMETIC, OPEN_BRACKET_NUMBER_MINUS_NUMBER_DIVIDE_NUMBER_CLOSE_BRACKET )
{
   // ARRANGE
   const auto& input = R"""((5-2/3);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        1,
        {
          "BinExprSyntaxNode": [
            3,
            {
              "FSyntaxNode": [
                3
              ]
            },
            {
              "FSyntaxNode": [
                2
              ]
            }
          ]
        },
        {
          "FSyntaxNode": [
            5
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
TEST( SYNTAX_TREE_ARITHMETIC, OPEN_BRACKET_NUMBER_MULTIPLY_OPEN_BRACKET_NUMBER_CLOSE_BRACKET_CLOSE_BRACKET )
{
   // ARRANGE
   const auto& input = R"""((1*(8));)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        2,
        {
          "FSyntaxNode": [
            8
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

TEST( SYNTAX_TREE_ARITHMETIC, OPEN_BRACKET_NUMBER_CLOSE_BRACKET )
{
   // ARRANGE
   const auto& input = R"""((1);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "FSyntaxNode": [
        1
      ]
    }
  ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_ARITHMETIC, ONE_PLUS )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
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
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_F_EQUAL_F )
{
   // ARRANGE
   const auto& input = R"""(1==2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        4,
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

TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_BIN_EXPR_EQUAL_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(1+2==3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        4,
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

TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_BIN_EXPR_MORE_EQUAL_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(1+2>=3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        8,
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
TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_BIN_EXPR_LESS_EQUAL_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(1+2<=3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        6,
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

TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_BIN_EXPR_LESS_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(1+2<3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        5,
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

TEST( SYNTAX_TREE_ARITHMETIC, CONDITION_BIN_EXPR_MORE_BIN_EXPR )
{
   // ARRANGE
   const auto& input = R"""(1+2>3+4;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        7,
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

TEST( SYNTAX_TREE_ARITHMETIC, F_PLUS_VARIBLE )
{
   // ARRANGE
   const auto& input = R"""(1+a;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
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

TEST( SYNTAX_TREE_ARITHMETIC, F_PLUS_FUNCTION_CALL )
{
   // ARRANGE
   const auto& input = R"""(1+foo(2);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
        {
          "FunctionCallSyntaxNode": [
            "foo",
            {
              "FSyntaxNode": [
                2
              ]
            }
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
TEST( SYNTAX_TREE_ARITHMETIC, ONE_DIVISION )
{
   // ARRANGE
   const auto& input = R"""(6/2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        3,
        {
          "FSyntaxNode": [
            2
          ]
        },
        {
          "FSyntaxNode": [
            6
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

TEST( SYNTAX_TREE_ARITHMETIC, MANY_PLUSs )
{
   // ARRANGE
   const auto& input = R"""(1+2+3;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
        {
          "BinExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                3
              ]
            },
            {
              "FSyntaxNode": [
                2
              ]
            }
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

TEST( SYNTAX_TREE_ARITHMETIC, ADVANCE_EXPRESSION )
{
   // ARRANGE
   const auto& input = R"""(1+2*3;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
        {
          "BinExprSyntaxNode": [
            2,
            {
              "FSyntaxNode": [
                3
              ]
            },
            {
              "FSyntaxNode": [
                2
              ]
            }
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

TEST( SYNTAX_TREE_ARITHMETIC, CIRCLE_CASE0 )
{
   // ARRANGE
   const auto& input = R"""(1+(2*3);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
        {
          "BinExprSyntaxNode": [
            2,
            {
              "FSyntaxNode": [
                3
              ]
            },
            {
              "FSyntaxNode": [
                2
              ]
            }
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

TEST( SYNTAX_TREE_ARITHMETIC, CIRCLE_CASE1 )
{
   // ARRANGE
   const auto& input = R"""(1+(2+3);)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        0,
        {
          "BinExprSyntaxNode": [
            0,
            {
              "FSyntaxNode": [
                3
              ]
            },
            {
              "FSyntaxNode": [
                2
              ]
            }
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

TEST( SYNTAX_TREE_ARITHMETIC, ONE_MINUS )
{
   // ARRANGE
   const auto& input = R"""(1-2;)""";

   // ACT
   const auto& lexical_tokens = LexicalTokens( input );
   const auto& syntax_tree = SyntaxTree( lexical_tokens );

   // ASSERT
   const auto& expected_syntax_tree_description = R"""(
{
  "StatmentSyntaxNode": [
    {
      "BinExprSyntaxNode": [
        1,
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


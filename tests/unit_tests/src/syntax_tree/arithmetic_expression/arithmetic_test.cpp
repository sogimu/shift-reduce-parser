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
          "ComputationalExpressionSyntaxNode": [
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
          "ComputationalExpressionSyntaxNode": [
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
                "ComputationalExpressionSyntaxNode": [
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
                "ComputationalExpressionSyntaxNode": [
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
          "ComputationalExpressionSyntaxNode": [
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
              "ComputationalExpressionSyntaxNode": [
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
                "ComputationalExpressionSyntaxNode": [
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
                "ComputationalExpressionSyntaxNode": [
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
          "ComputationalExpressionSyntaxNode": [
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
      ]
}
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

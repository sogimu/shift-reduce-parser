#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_ADDITION, ONE_PLUS )
{
   // ARRANGE
   const auto& input = R"""(1+2;)""";

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
                "ComputationalExpressionSyntaxNode": [
                  {
                    "AdditionSyntaxNode": [
                      {
                        "ComputationalExpressionSyntaxNode": [
                          {
                            "FSyntaxNode": [
                              2 
                            ]
                          }
                        ]
                      },
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

TEST( SYNTAX_TREE_ADDITION, ONE_DIVISION )
{
   // ARRANGE
   const auto& input = R"""(6/2;)""";

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
                "ComputationalExpressionSyntaxNode": [
                  {
                    "DivisionSyntaxNode": [
                      {
                        "ComputationalExpressionSyntaxNode": [
                          {
                            "FSyntaxNode": [
                              6 
                            ]
                          }
                        ]
                      },
                      {
                        "ComputationalExpressionSyntaxNode": [
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
            ]
          }
        ]
      }
      )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

TEST( SYNTAX_TREE_ADDITION, MANY_PLUSs )
{
   // ARRANGE
   const auto& input = R"""(1+2+3+4;)""";

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
          "ComputationalExpressionSyntaxNode": [
            {
              "AdditionSyntaxNode": [
                {
                  "ComputationalExpressionSyntaxNode": [
                    {
                      "AdditionSyntaxNode": [
                        {
                          "ComputationalExpressionSyntaxNode": [
                            {
                              "AdditionSyntaxNode": [
                                {
                                  "ComputationalExpressionSyntaxNode": [
                                    {
                                      "FSyntaxNode": [
                                        4 
                                      ]
                                    }
                                  ]
                                },
                                {
                                  "ComputationalExpressionSyntaxNode": [
                                    {
                                      "FSyntaxNode": [
                                        3
                                      ]
                                    }
                                  ]
                                }
                              ]
                            }
                          ]
                        },
                        {
                          "ComputationalExpressionSyntaxNode": [
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
                },
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

TEST( SYNTAX_TREE_ADDITION, ADVANCE_EXPRESSION )
{
   // ARRANGE
   const auto& input = R"""(1+2*3;)""";

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
              "ComputationalExpressionSyntaxNode": [
                {
                  "AdditionSyntaxNode": [
                    {
                      "ComputationalExpressionSyntaxNode": [
                        {
                          "MultiplySyntaxNode": [
                            {
                              "ComputationalExpressionSyntaxNode": [
                                {
                                  "FSyntaxNode": [
                                    2 
                                  ]
                                }
                              ]
                            },
                            {
                              "ComputationalExpressionSyntaxNode": [
                              {
                                "FSyntaxNode": [
                                  3
                                ]
                              }
                            ]
                          }
                        ]
                      }
                    ]
                  },
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

// #include "catch2/catch_all.hpp"
// #include "enums.h"
#include "lexical_tokens.h"
// #include "syntax_node_empty_visitor.h"
// #include "syntax_tree.h"
// #include "utils.h"
// #include "utils/dfs_pre_order_range.h"
#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

// Demonstrate some basic assertions.
TEST( BasicAssertions, Styntax_tree )
{
    std::vector<LexicalTokens::LexicalToken> tokens{ { "{", Token_Type::OPEN_CURLY_BRACKET },
                                                     { "m", Token_Type::NAME },
                                                     { "=", Token_Type::EQUAL },
                                                     { "42", Token_Type::INT },
                                                     { ";", Token_Type::SEMICOLON },
                                                     { "}", Token_Type::CLOSE_CURLY_BRACKET } };

    LexicalTokens lexical_tokens{ tokens };
    SyntaxTree expected_syntax_tree( lexical_tokens );

    const auto& syntax_tree = CreateSyntaxNodeTree( R"""(
                {
                  "ScopeSyntaxNode": [
                    {
                      "ExpressionSyntaxNode": [
                        {
                          "VaribleAssigmentSyntaxNode": [
                            {
                              "NameSyntaxNode": [
                                "m"
                              ]
                            },
                            {
                              "ComputationalExpressionSyntaxNode": [
                                {
                                  "FSyntaxNode": [
                                    42
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
                )""" );

    EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

// SCENARIO( "Styntax tree" )
// {
//     GIVEN( "Tokens are describing varible initialization" )
//     {
//         std::vector<LexicalTokens::LexicalToken> tokens{ { "{", Token_Type::OPEN_CURLY_BRACKET },
//                                                          { "m", Token_Type::NAME },
//                                                          { "=", Token_Type::EQUAL },
//                                                          { "42", Token_Type::INT },
//                                                          { ";", Token_Type::SEMICOLON },
//                                                          { "}", Token_Type::CLOSE_CURLY_BRACKET } };
//         //   LexicalTokens lexical_tokens(tokens);
//         WHEN( "Create SyntaxTree from tokens" )
//         {
//             //       //     SyntaxTree syntax_tree(lexical_tokens);
//             THEN( "SyntaxTree has filled right way" )
//             {
//                 //       const auto &expected_syntax_tree =
//                 CreateSyntaxNodeTree( R"""(
//                         //               {
//                         //                 "ScopeSyntaxNode": [
//                         //                   {
//                         //                     "ExpressionSyntaxNode": [
//                         //                       {
//                         //                         "VaribleAssigmentSyntaxNode": [
//                         //                           {
//                         //                             "NameSyntaxNode": [
//                         //                               "m"
//                         //                                 ]
//                         //                               },
//                         //                               {
//                         // "ComputationalExpressionSyntaxNode":
//                         //                                 [
//                         //                               {
//                         //                                 "FSyntaxNode": [
//                         //                                   42
//                         //                                 ]
//                         //                               }
//                         //                             ]
//                         //                           }
//                         //                         ]
//                         //                       }
//                         //                     ]
//                         //                   }
//                         //                 ]
//                         //               }
//                         //               )""" );
//                 //
//                 //       CHECK(syntax_tree == expected_syntax_tree);
//             }
//         }
//     }
//
//     GIVEN( "Tokens are describing sum of two constans" )
//     {
//         std::vector<LexicalTokens::LexicalToken> tokens{ { "{", Token_Type::OPEN_CURLY_BRACKET },
//                                                          { "1", Token_Type::INT },
//                                                          { "+", Token_Type::SUM },
//                                                          { "2", Token_Type::INT },
//                                                          { ";", Token_Type::SEMICOLON },
//                                                          { "}", Token_Type::CLOSE_CURLY_BRACKET } };
//         LexicalTokens lexical_tokens( tokens );
//         WHEN( "Create SyntaxTree from tokens" )
//         {
//             // SyntaxTree syntax_tree(lexical_tokens);
//             THEN( "SyntaxTree has filled right way" )
//             {
//                 const auto& expected_syntax_tree = CreateSyntaxNodeTree( R"""(
//           {
//             "ScopeSyntaxNode": [
//               {
//                 "ExpressionSyntaxNode": [
//                   {
//                     "VaribleAssigmentSyntaxNode": [
//                       {
//                         "NameSyntaxNode": [
//                           "m"
//                             ]
//                           },
//                           {
//                             "ComputationalExpressionSyntaxNode": [
//                           {
//                             "FSyntaxNode": [
//                               42
//                             ]
//                           }
//                         ]
//                       }
//                     ]
//                   }
//                 ]
//               }
//             ]
//           }
//           )""" );
//
//                 CHECK( syntax_tree == expected_syntax_tree );
//             }
//         }
//     }
// }

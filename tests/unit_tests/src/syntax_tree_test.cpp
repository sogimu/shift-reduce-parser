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

TEST( SyntaxTree, VaribleAssigmentSyntaxNode )
{
    // {m=42;}
    std::vector<LexicalTokens::LexicalToken> tokens{ { "{", Token_Type::OPEN_CURLY_BRACKET },
                                                     { "m", Token_Type::NAME },
                                                     { "=", Token_Type::EQUAL },
                                                     { "42", Token_Type::INT },
                                                     { ";", Token_Type::SEMICOLON },
                                                     { "}", Token_Type::CLOSE_CURLY_BRACKET } };

    LexicalTokens lexical_tokens{ tokens };
    SyntaxTree syntax_tree( lexical_tokens );

    const auto& expected_syntax_tree = CreateSyntaxNodeTree( R"""(
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

TEST( SyntaxTree, IfExpressionSyntaxNode )
{
    // if(1==2){}
    // std::vector<LexicalTokens::LexicalToken> tokens{
    //     { "1", Token_Type::F }, { "+", Token_Type::SUM }, { "2", Token_Type::F } };
    //
    // LexicalTokens lexical_tokens{ tokens };
    // SyntaxTree syntax_tree( lexical_tokens );

    const auto& expected_syntax_tree = CreateSyntaxNodeTree( R"""(
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

    EXPECT_EQ( expected_syntax_tree, expected_syntax_tree );
}

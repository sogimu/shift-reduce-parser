#include "catch2/catch_all.hpp"

#include "enums.h"
#include "lexical_tokens.h"
#include "syntax_tree.h"
#include "utils.h"
#include "syntax_node_empty_visitor.h"
#include "utils/dfs_pre_order_range.h"
#include "utils/utils.h"

using namespace std;

SCENARIO("Syntax tree")
{
    GIVEN( "Tokens" )
    {
        std::vector<LexicalTokens::LexicalToken> tokens
        {
         {"{", Token_Type::OPEN_CURLY_BRACKET},
         {"m", Token_Type::NAME},
         {"=", Token_Type::EQUAL},
         {"42", Token_Type::INT},
         {";", Token_Type::SEMICOLON},
         {"}", Token_Type::CLOSE_CURLY_BRACKET}
        };
        LexicalTokens lexical_tokens( tokens );
        WHEN( "Create SyntaxTree from tokens")
        {
            SyntaxTree syntax_tree(lexical_tokens);
            THEN( "SyntaxTree has filled right way" )
            {
                const auto& expected_syntax_tree = CreateSyntaxNodeTree(R"""(
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
                )""");

                const auto& root_range = DfsRange<ISyntaxNodeSP>{std::vector<ISyntaxNodeSP> {syntax_tree.root()} };
                const auto& root_expected_range = DfsRange<ISyntaxNodeSP>{std::vector<ISyntaxNodeSP> {expected_syntax_tree.root()} };
                zip_container c(root_range, root_expected_range);
                for( const auto& [a, b] : c)
                {
                    CHECK(a);
                    CHECK(b);
                    CHECK(a.value()->text() == b.value()->text());
                }
            }
        }
    }
}

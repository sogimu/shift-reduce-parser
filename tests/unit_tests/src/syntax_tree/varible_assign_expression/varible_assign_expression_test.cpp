#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_VARIBLE_ASSIGN, TEST0 )
{
   // ARRANGE
   const auto& input = R"""(
    {
      a=1;
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
          "ExpressionSyntaxNode": [
            {
              "VaribleAssigmentSyntaxNode": [
              {
                "NameSyntaxNode": [
                  "a" 
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
    )""";

   const auto& expected_syntax_tree = CreateSyntaxNodeTree( expected_syntax_tree_description );
   EXPECT_EQ( syntax_tree, expected_syntax_tree );
}

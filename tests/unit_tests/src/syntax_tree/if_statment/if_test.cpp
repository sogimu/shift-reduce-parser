#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_IF, WITHOUT_ELSE )
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
          "ConditionalExpressionSyntaxNode": [
            4,
            {
              "ComputationalExpressionSyntaxNode": [
                {
                  "FSyntaxNode": [
                    1
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

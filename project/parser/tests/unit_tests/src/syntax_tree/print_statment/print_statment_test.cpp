#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_PRINT, TEST0 )
{
   // ARRANGE
   const auto& input = R"""(
    {
      print(1);
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
      "StatmentSyntaxNode": [
        {
          "PrintStatmentSyntaxNode": [
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

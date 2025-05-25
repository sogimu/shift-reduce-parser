#include "syntax_tree.h"

#include <gtest/gtest.h>
#include "utils/utils.h"

using namespace std;

TEST( SYNTAX_TREE_FUNCTION, CASE0 )
{
   // ARRANGE
   const auto& input = R"""(
    foo(a)
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
                  "FunctionStatmentSyntaxNode": [
                    "foo",
                    {
                        "NameSyntaxNode": [
                          "a"
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

#include "i_syntax_node.h"
#include "utils/utils.h"

#include <gtest/gtest.h>

using namespace std;

TEST( CreateSyntaxNodeTree, Test0 )
{
   // ARRANGE
   const auto& tree_description = R"""(
      {
        "ScopeSyntaxNode": [
          {
           "StatmentSyntaxNode": [
              {
                "VaribleAssigmentStatmentSyntaxNode": [
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
      )""";

   // ACT
   const auto& result_syntax_tree = CreateSyntaxNodeTree( tree_description );

   // ASSERT
   const auto& f = std::make_shared< FSyntaxNode >( 42 );
   const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >( f );
   const auto& name = std::make_shared< NameSyntaxNode >( "m" );
   const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, computational_expression );
   const auto& expression = std::make_shared< StatmentSyntaxNode >( varible_assigment );
   const auto& root = std::make_shared< ScopeSyntaxNode >( std::vector< ISyntaxNodeSP >{ expression } );
   SyntaxTree expected_syntax_tree( root );

   EXPECT_EQ( result_syntax_tree, expected_syntax_tree );
}

#include "catch2/catch_all.hpp"

#include "utils/utils.h"

using namespace std;

TEST_CASE("CreateSyntaxNodeTree test")
{
    // ARRANGE
    const auto& f = std::make_shared<FSyntaxNode>(42);
    const auto& computational_expression = std::make_shared<ComputationalExpressionSyntaxNode>(f);
    const auto& name = std::make_shared<NameSyntaxNode>("m");
    const auto& varible_assigment = std::make_shared<VaribleAssigmentSyntaxNode>(name, computational_expression);
    const auto& expression = std::make_shared<ExpressionSyntaxNode>(varible_assigment);
    const auto& root = std::make_shared<ScopeSyntaxNode>(std::vector<ISyntaxNodeSP>{expression});
    SyntaxTree expected_syntax_tree(root);

    // ACT
    const auto& result_syntax_tree = CreateSyntaxNodeTree(R"""(
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

    // ASSERT
    CHECK( result_syntax_tree == expected_syntax_tree );
}

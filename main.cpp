#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <stack>
#include <map>
#include <iomanip>
#include <functional>
#include <optional>

#include "enums.h"
#include "lexical_tokens.h"
#include "syntax_tree.h"
#include "utils.h"

using namespace std;

class Calculator
{
public:
    double solve(const std::string& expression) const
    {
        LexicalTokens lexical_tokens(expression);
        SyntaxTree syntax_tree(lexical_tokens);

        syntax_tree.print_ast();

        std::map<std::string, double> variables;

        iterative_dfs(syntax_tree.root(),
        [&syntax_tree, &variables](const SyntaxNodeSP& node) -> bool
        {
            if( node->token.text == "=" )
            {
                const auto& result = syntax_tree.execute_ast(node->second, [&variables](const double& first_operand, const double& second_operand, const std::string& o) -> double
                {
                    double result_operand = 0.0;
                    if( o == "+" )
                    {
                        result_operand = first_operand + second_operand;
                    }
                    else if( o == "-" )
                    {
                        result_operand = first_operand - second_operand;
                    }
                    else if( o == "*" )
                    {
                        result_operand = first_operand * second_operand;
                    }
                    else if( o == "/" )
                    {
                        result_operand = first_operand / second_operand;
                    }

                    std::cout << std::setprecision(3) << std::setw(4) << first_operand << o  << std::setw(4) << second_operand << "=" << result_operand << std::endl;
                    return result_operand;
                });

                variables[node->first->token.text] = result;
            }
            return true;
        });

        for(const auto& p : variables)
        {
            std::cout << p.first << "=" << p.second << std::endl;
        }

        return 0.0;
    }

private:

};

int main()
{
//    std::string e = "((-1+2)-3)";
    std::string e = "a=5+5;";

//    int n = 5;
//    for (int i=1; i<n; ++i)
//    {
//        if( i % 2 == 0 )
//        {
//            e += std::to_string(i)+"+";
//        }
//        else
//        {
//            e += std::to_string(i)+"*";
//        }
//    }
//    e += std::to_string(n);
    std::cout << e << std::endl;

    Calculator calculator;
    auto result0 = calculator.solve(e);
    cout << result0 << std::endl;
    return 0;
}

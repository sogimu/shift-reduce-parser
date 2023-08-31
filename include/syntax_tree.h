#pragma once

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
#include "utils.h"
#include "i_grammar.h"
#include "grammars/f.h"
#include "grammars/e.h"
#include "grammars/t.h"
#include "grammars/p.h"
#include "grammars/assignment.h"

class SyntaxTree
{
public:
    SyntaxTree(const LexicalTokens& lexical_tokens)
    {
        // E -> T + E | T - E | T
        // T -> F * T | F / T | F
        // F -> (E)   | -N    | N

        std::vector<IGrammarSP> grammars
        {
            std::make_shared<F>(),
            std::make_shared<T>(),
            std::make_shared<E>(),
            std::make_shared<P>(),
            std::make_shared<Assigment>()
        };

        std::deque<SyntaxNodeSP> stack;
        const auto& tokens = lexical_tokens.list();
        for( auto it = tokens.begin(); it != tokens.end(); ++it )
        {
            const auto& token = *it;
            const auto& node = std::make_shared<SyntaxNode>(token);
            stack.emplace_back(node);

            bool is_production_can_be = stack.size() >= 1;
            while( is_production_can_be )
            {
                is_production_can_be = false;
                for( const auto& grammar : grammars )
                {
                    auto production = grammar->TryFindProduction(stack);
                    while( production )
                    {
                        is_production_can_be = true;
                        const auto& plan = production->make_plan();

                        for( size_t i=0; i< plan.to_remove.nodes.size(); ++i )
                            stack.pop_back();

                        for( const auto& d : plan.to_add.nodes )
                            stack.push_back(d);

                        production = grammar->TryFindProduction(stack);
                    }
                }
            }
        }

        mRoot = stack.front();
    }

    SyntaxNodeSP root()
    {
        return mRoot;
    }

    template<typename Func>
    double execute_ast(const SyntaxNodeSP& root, Func func) const
    {
        double result = 0.0;

        std::map<SyntaxNodeSP, double> valueByASTNode;

        iterative_dfs(root, [](const SyntaxNodeSP& node) -> bool
        {
            return false;
        },
        [&result, &valueByASTNode, &func](const SyntaxNodeSP& node)
        {
            if( node->first && node->second )
            {
                double first_operand;
                if( valueByASTNode.count(node->first) )
                {
                    first_operand = valueByASTNode[node->first];
                }
                else
                {
                    first_operand = std::stod(node->first->token.text);
                }

                double second_operand;
                if( valueByASTNode.count(node->second) )
                {
                    second_operand = valueByASTNode[node->second];
                }
                else
                {
                    second_operand = std::stod(node->second->token.text);
                }

                double result_operand = 0.0;
                result_operand = func(first_operand, second_operand, node->token.text);

                valueByASTNode[node] = result_operand;
                result = result_operand;
            }
            else
            {
                result = std::stod(node->token.text);
            }
        });

        return result;
    }

    void print_ast() const
    {
        size_t n = 0;
        iterative_dfs(mRoot,
        [&n](const SyntaxNodeSP& node) -> bool
        {
            if( node->token.type == Token_Type::MULTIPLY || node->token.type == Token_Type::DIVIDE || node->token.type == Token_Type::PLUS || node->token.type == Token_Type::MINUS )
            {
                for(int i=0; i<n; ++i)
                    std::cout << "   ";
                std::cout << "{" << node->first->token.text << node->token.text << node->second->token.text << "}";
                std::cout << std::endl;
            }
            ++n;
            return false;
        },
        [&n](const SyntaxNodeSP& node)
        {
            --n;
        });
    }

private:
    SyntaxNodeSP mRoot;
};

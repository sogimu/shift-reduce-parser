#pragma once

#include <vector>
#include "enums.h"
#include "i_grammar.h"

class E;
class T;
class P;

class T : public IGrammar
{
public:
    T()
    {
        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MULTIPLY, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MULTIPLY, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MULTIPLY, Token_Type::F}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& e = *(it);
            const auto& multiply = *(++it);
            const auto& f = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(e);
            plan.to_remove.nodes.push_back(multiply);
            plan.to_remove.nodes.push_back(f);

            plan.to_add.nodes.push_back(e->first);
            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {e->token.text, (e->token.text == "+" ? Token_Type::PLUS : Token_Type::MINUS) };
            plan.to_add.nodes.push_back(d);

            plan.to_add.nodes.push_back(e->second);
            plan.to_add.nodes.push_back(multiply);
            plan.to_add.nodes.push_back(f);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MULTIPLY, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::MULTIPLY, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MULTIPLY, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MULTIPLY, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MULTIPLY, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MULTIPLY, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MULTIPLY, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::MULTIPLY, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MULTIPLY, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::DIVIDE, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::DIVIDE, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::DIVIDE, Token_Type::F}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& e = *(it);
            const auto& multiply = *(++it);
            const auto& f = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(e);
            plan.to_remove.nodes.push_back(multiply);
            plan.to_remove.nodes.push_back(f);

            plan.to_add.nodes.push_back(e->first);
            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {e->token.text, (e->token.text == "+" ? Token_Type::PLUS : Token_Type::MINUS) };
            plan.to_add.nodes.push_back(d);

            plan.to_add.nodes.push_back(e->second);
            plan.to_add.nodes.push_back(multiply);
            plan.to_add.nodes.push_back(f);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::DIVIDE, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::DIVIDE, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::DIVIDE, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::DIVIDE, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "*", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::DIVIDE, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::DIVIDE, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::DIVIDE, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::DIVIDE, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::DIVIDE, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "/", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::BOL, Token_Type::T, Token_Type::EOL}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& bol = *it;
            const auto& t = *(++it);
            const auto& eol = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(bol);
            plan.to_remove.nodes.push_back(t);
            plan.to_remove.nodes.push_back(eol);

            plan.to_add.nodes.push_back(t);

            return Production{plan};
        });

    }
};

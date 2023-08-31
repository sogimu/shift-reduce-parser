#pragma once

#include <vector>
#include "enums.h"
#include "i_grammar.h"

class E;
class T;
class P;

class E : public IGrammar
{
public:
    E()
    {
        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::PLUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::PLUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::PLUS, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::PLUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::PLUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::PLUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::PLUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::PLUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::PLUS, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::PLUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::PLUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::PLUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::PLUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::PLUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "+", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MINUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MINUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MINUS, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MINUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MINUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::MINUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::MINUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::E);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MINUS, Token_Type::F}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MINUS, Token_Type::E}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MINUS, Token_Type::T}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::F, Token_Type::MINUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::E, Token_Type::MINUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::T, Token_Type::MINUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::P, Token_Type::MINUS, Token_Type::P}, [](const Stack& stack) -> Production
        {
            return planAOpB(stack, "-", Token_Type::T);
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::BOL, Token_Type::E, Token_Type::EOL}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& bol = *it;
            const auto& e = *(++it);
            const auto& eol = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(bol);
            plan.to_remove.nodes.push_back(e);
            plan.to_remove.nodes.push_back(eol);

            plan.to_add.nodes.push_back(e);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::BOL, Token_Type::E, Token_Type::EOL}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& bol = *it;
            const auto& e = *(++it);
            const auto& eol = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(bol);
            plan.to_remove.nodes.push_back(e);
            plan.to_remove.nodes.push_back(eol);

            plan.to_add.nodes.push_back(e);

            return Production{plan};
        });

    }

};

#pragma once

#include <vector>
#include "enums.h"
#include "i_grammar.h"

class E;
class T;
class P;

class F : public IGrammar
{
public:
    F()
    {
        mProductionByFeature.emplace_back(Feature{Token_Type::MINUS, Token_Type::MINUS, Token_Type::INT}, [](const Stack& stack) -> Production
        {

            auto it = stack.begin();
            std::advance(it, stack.size() - 2);

            const auto& minus = *(it);
            const auto& number = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(minus);
            plan.to_remove.nodes.push_back(number);

            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {minus->token.text + number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);
            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::BOL, Token_Type::MINUS, Token_Type::INT}, [](const Stack& stack) -> Production
        {

            auto it = stack.begin();
            std::advance(it, stack.size() - 3);

            const auto& bol = *(it);
            const auto& minus = *(++it);
            const auto& number = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(minus);
            plan.to_remove.nodes.push_back(number);

            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {minus->token.text + number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::OPEN_BRACKET, Token_Type::MINUS, Token_Type::INT}, [](const Stack& stack) -> Production
        {

            auto it = stack.begin();
            std::advance(it, stack.size() - 3);

            const auto& open_bracket = *(it);
            const auto& minus = *(++it);
            const auto& number = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(minus);
            plan.to_remove.nodes.push_back(number);

            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {minus->token.text + number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::MULTIPLY, Token_Type::MINUS, Token_Type::INT}, [](const Stack& stack) -> Production
        {

            auto it = stack.begin();
            std::advance(it, stack.size() - 2);

            const auto& minus = *(it);
            const auto& number = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(minus);
            plan.to_remove.nodes.push_back(number);


            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {minus->token.text + number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::DIVIDE, Token_Type::MINUS, Token_Type::INT}, [](const Stack& stack) -> Production
        {

            auto it = stack.begin();
            std::advance(it, stack.size() - 2);

            const auto& minus = *(it);
            const auto& number = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(minus);
            plan.to_remove.nodes.push_back(number);


            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {minus->token.text + number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);

            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::INT}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 1);
            const auto& number = *it;

            Production::Plan plan;
            plan.to_remove.nodes.push_back(number);


            const auto& d = std::make_shared<SyntaxNode>();
            d->token = {number->token.text, Token_Type::F};
            plan.to_add.nodes.push_back(d);


            return Production{plan};
        });

        mProductionByFeature.emplace_back(Feature{Token_Type::BOL, Token_Type::F, Token_Type::EOL}, [](const Stack& stack) -> Production
        {
            auto it = stack.begin();
            std::advance(it, stack.size() - 3);
            const auto& bol = *it;
            const auto& f = *(++it);
            const auto& eol = *(++it);

            Production::Plan plan;
            plan.to_remove.nodes.push_back(bol);
            plan.to_remove.nodes.push_back(f);
            plan.to_remove.nodes.push_back(eol);

            plan.to_add.nodes.push_back(f);

            return Production{plan};
        });

    }

};

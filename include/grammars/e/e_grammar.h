#pragma once

#include <vector>
#include "enums.h"
#include "i_grammar.h"
#include "e_syntax_node.h"
#include "sum/sum_syntax_node.h"
//#include "diff/syntax_node.h"
#include "utils.h"

class E;
class T;
class P;

class E : public IGrammar
{
public:
    E()
    {
        enum class State
        {
            START,
            FINISH,
            ERROR,
            BOL,
            EOL,
            SUM,
            E
        };

        // SUM
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            SumSyntaxNodeSP sum;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.sum_syntax_node = [&sum, &state](const SumSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    state = State::SUM;
                    sum = node;
                    state = State::FINISH;
                }
            };
            iterate_over_last_n_nodes(stack, 1, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(sum);

            const auto& e_node = std::make_shared<ESyntaxNode>(sum);
            plan.to_add.nodes.push_back(e_node);
            return plan;
        });

        // BOL E EOL
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            BolSyntaxNodeSP bol;
            ESyntaxNodeSP e;
            EolSyntaxNodeSP eol;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.bol_syntax_node = [&bol, &state](const BolSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    bol = node;
                    state = State::BOL;
                }
            };
            handlers.e_syntax_node = [&e, &state](const ESyntaxNodeSP& node)
            {
                if( state == State::BOL )
                {
                    e = node;
                    state = State::E;
                }
            };
            handlers.eol_syntax_node = [&eol, &state](const EolSyntaxNodeSP& node)
            {
                if( state == State::E )
                {
                    state = State::EOL;
                    eol = node;
                    state = State::FINISH;
                }
            };
            iterate_over_last_n_nodes(stack, 3, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(bol);
            plan.to_remove.nodes.push_back(e);
            plan.to_remove.nodes.push_back(eol);

            plan.to_add.nodes.push_back(e);
            return plan;
        });
//        mProductionByFeature.emplace_back(Features{one(Token_Type::DIFF)}, [this](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 1);
//            const auto& diff = *(it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(diff);

//            const auto& d = std::make_shared<SyntaxNodeE>(diff);
//            plan.to_add.nodes.push_back(d);
//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::E), one(Token_Type::EOL)}, [this](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 3);
//            const auto& bol = *it;
//            const auto& e = *(++it);
//            const auto& eol = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(bol);
//            plan.to_remove.nodes.push_back(e);
//            plan.to_remove.nodes.push_back(eol);

//            plan.to_add.nodes.push_back(e);

//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::E), one(Token_Type::EOL)}, [this](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 3);
//            const auto& bol = *it;
//            const auto& e = *(++it);
//            const auto& eol = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(bol);
//            plan.to_remove.nodes.push_back(e);
//            plan.to_remove.nodes.push_back(eol);

//            plan.to_add.nodes.push_back(e);

//            return Production{plan};
//        });

    }

};

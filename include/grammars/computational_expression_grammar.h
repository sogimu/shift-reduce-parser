#pragma once

#include <vector>

#include "enums.h"
#include "i_grammar.h"
#include "e/e_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

class ComputationalExpression : public IGrammar
{
public:
    ComputationalExpression()
    {
        enum class State
        {
            START,
            FINISH,
            ERROR,
            E,
            F,
            OPEN_CIRCLE_BRACKET,
            NAME,
            CLOSE_CIRCLE_BRACKET,
        };

        // E
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            ESyntaxNodeSP e;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.e_syntax_node = [&e, &state](const ESyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    e = node;
                    state = State::E;
                    state = State::FINISH;
                }
            };
            iterate_over_last_n_nodes(stack, 1, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(e);

            const auto& expression_node = std::make_shared<ComputationalExpressionSyntaxNode>(e);
            plan.to_add.nodes.push_back(expression_node);
            return plan;
        });

        // F
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            FSyntaxNodeSP f;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.f_syntax_node = [&f, &state](const FSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    f = node;
                    state = State::F;
                    state = State::FINISH;
                }
            };
            iterate_over_last_n_nodes(stack, 1, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(f);

            const auto& expression_node = std::make_shared<ComputationalExpressionSyntaxNode>(f);
            plan.to_add.nodes.push_back(expression_node);
            return plan;
        });

        // OPEN_CIRCLE_BRACKET NAME CLOSE_CIRCLE_BRACKET
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            OpenCircleBracketSyntaxNodeSP open;
            NameSyntaxNodeSP name;
            CloseCircleBracketSyntaxNodeSP close;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.open_circle_bracket_syntax_node = [&open, &state](const OpenCircleBracketSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    state = State::OPEN_CIRCLE_BRACKET;
                    open = node;
                }
            };
            handlers.name_syntax_node = [&name, &state](const NameSyntaxNodeSP& node)
            {
                if( state == State::OPEN_CIRCLE_BRACKET )
                {
                    state = State::NAME;
                    name = node;
                }
            };
            handlers.close_circle_bracket_syntax_node = [&close, &state](const CloseCircleBracketSyntaxNodeSP& node)
            {
                if( state == State::NAME )
                {
                    state = State::CLOSE_CIRCLE_BRACKET;
                    state = State::FINISH;
                    close = node;
                }
            };
            iterate_over_last_n_nodes(stack, 3, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(open);
            plan.to_remove.nodes.push_back(name);
            plan.to_remove.nodes.push_back(close);

            const auto& computational_expression = std::make_shared<ComputationalExpressionSyntaxNode>(name);
            plan.to_add.nodes.push_back(open);
            plan.to_add.nodes.push_back(computational_expression);
            plan.to_add.nodes.push_back(close);
            return plan;
        });
//        mProductionByFeature.emplace_back(Features{ one(Token_Type::ASSIGMENT)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 1);
//            const auto& assigment = *(it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(assigment);

//            const auto& d = std::make_shared<ISyntaxNode>();
//            d->token = {assigment->token.text, Token_Type::EXPRESSION };
//            d->first = assigment->first;
//            d->second = assigment->second;
//            plan.to_add.nodes.push_back(d);
//            return Production{plan};
//        });
    }
};

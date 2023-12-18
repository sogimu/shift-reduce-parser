#pragma once

#include <vector>
#include <memory>

#include "enums.h"
#include "i_grammar.h"
#include "conditional_expression_syntax_node.h"
//#include "less_expression_syntax_node.h"
//#include "more_expression_syntax_node.h"
#include "utils.h"

class ISyntaxNodeVisitor;

class ConditionalExpression : public IGrammar
{
public:
    ConditionalExpression()
    {
        enum class State
        {
            START,
            FINISH,
            ERROR,
            EQUAL_EXPRESSION0,
            EQUAL_EXPRESSION1,
            FIRST_COMPUTATIONAL_EXPRESSION,
            SECOND_COMPUTATIONAL_EXPRESSION,
            MORE,
            LESS
        };

        // COMPUTATIONAL_EXPRESSION EQUAL EQUAL COMPUTATIONAL_EXPRESSION
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            EqualSyntaxNodeSP equal0;
            EqualSyntaxNodeSP equal1;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.computational_expression_syntax_node = [&computational_expression0, &computational_expression1, &state](const ComputationalExpressionSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                    computational_expression0 = node;
                }
                else if( state == State::EQUAL_EXPRESSION1 )
                {
                    state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                    computational_expression1 = node;
                    state = State::FINISH;
                }
            };
            handlers.equal_syntax_node = [&equal0, &equal1, &state](const EqualSyntaxNodeSP& node)
            {
                if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
                {
                    equal0 = node;
                    state = State::EQUAL_EXPRESSION0;
                }
                else if( state == State::EQUAL_EXPRESSION0 )
                {
                    equal1 = node;
                    state = State::EQUAL_EXPRESSION1;
                }
            };

            iterate_over_last_n_nodes(stack, 4, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(computational_expression0);
            plan.to_remove.nodes.push_back(equal0);
            plan.to_remove.nodes.push_back(equal1);
            plan.to_remove.nodes.push_back(computational_expression1);

            const auto& conditional_expression_node = std::make_shared<ConditionalExpressionSyntaxNode>(computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::EQUAL);
            plan.to_add.nodes.push_back(conditional_expression_node);
            return plan;
        });

        // COMPUTATIONAL_EXPRESSION LESS COMPUTATIONAL_EXPRESSION
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            LessSyntaxNodeSP less;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.computational_expression_syntax_node = [&computational_expression0, &computational_expression1, &state](const ComputationalExpressionSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                    computational_expression0 = node;
                }
                else if( state == State::LESS )
                {
                    state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                    computational_expression1 = node;
                    state = State::FINISH;
                }
            };
            handlers.less_syntax_node = [&less, &state](const LessSyntaxNodeSP& node)
            {
                if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
                {
                    less = node;
                    state = State::LESS;
                }
            };

            iterate_over_last_n_nodes(stack, 3, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(computational_expression0);
            plan.to_remove.nodes.push_back(less);
            plan.to_remove.nodes.push_back(computational_expression1);

            const auto& conditional_expression_node = std::make_shared<ConditionalExpressionSyntaxNode>(computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::LESS);
            plan.to_add.nodes.push_back(conditional_expression_node);
            return plan;
        });

        // COMPUTATIONAL_EXPRESSION MORE COMPUTATIONAL_EXPRESSION
        mProductions.emplace_back([this](const Stack& stack) -> std::optional<Plan>
        {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            MoreSyntaxNodeSP more;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [&state](const ISyntaxNodeSP&)
            {
                state = State::ERROR;
            };
            handlers.computational_expression_syntax_node = [&computational_expression0, &computational_expression1, &state](const ComputationalExpressionSyntaxNodeSP& node)
            {
                if( state == State::START )
                {
                    state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                    computational_expression0 = node;
                }
                else if( state == State::MORE )
                {
                    state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                    computational_expression1 = node;
                    state = State::FINISH;
                }
            };
            handlers.more_syntax_node = [&more, &state](const MoreSyntaxNodeSP& node)
            {
                if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
                {
                    more = node;
                    state = State::MORE;
                }
            };

            iterate_over_last_n_nodes(stack, 3, handlers);

            if( state != State::FINISH )
                return {};

            Plan plan;
            plan.to_remove.nodes.push_back(computational_expression0);
            plan.to_remove.nodes.push_back(more);
            plan.to_remove.nodes.push_back(computational_expression1);

            const auto& conditional_expression_node = std::make_shared<ConditionalExpressionSyntaxNode>(computational_expression0, computational_expression1, ConditionalExpressionSyntaxNode::Type::MORE);
            plan.to_add.nodes.push_back(conditional_expression_node);
            return plan;
        });
//        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS), one(Token_Type::F)}, [this](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 3);
//            const auto& f0 = *(it);
//            const auto& plus = *(++it);
//            const auto& f1 = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(f0);
//            plan.to_remove.nodes.push_back(plus);
//            plan.to_remove.nodes.push_back(f1);

//            const auto& d = std::make_shared<SyntaxNodeSum>(f0, f1);
//            plan.to_add.nodes.push_back(d);
//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS), one(Token_Type::T)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS), one(Token_Type::E)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS), one(Token_Type::F)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS), one(Token_Type::T)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS), one(Token_Type::F)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS), one(Token_Type::T)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS), one(Token_Type::F)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS), one(Token_Type::E)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS), one(Token_Type::T)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS), one(Token_Type::P)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS), one(Token_Type::P)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS), one(Token_Type::P)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS), one(Token_Type::P)}, [this](const Stack& stack) -> Production
//        {
//            return planAOpB(stack);
//        });

    }
//private:
//    Production planAOpB(const Stack& stack)
//    {
//        auto it = stack.begin();
//        std::advance(it, stack.size() - 3);
//        const auto& f0 = *(it);
//        const auto& plus = *(++it);
//        const auto& f1 = *(++it);

//        Production::Plan plan;
//        plan.to_remove.nodes.push_back(f0);
//        plan.to_remove.nodes.push_back(plus);
//        plan.to_remove.nodes.push_back(f1);

//        const auto& d = std::make_shared<SyntaxNodeSum>(f0, f1);
//        plan.to_add.nodes.push_back(d);
//        return Production{plan};
//    }

};

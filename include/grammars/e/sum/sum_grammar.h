#pragma once

#include "enums.h"
#include "i_grammar.h"
#include "sum_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Sum : public IGrammar
{
public:
   Sum()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         BOL,
         EOL,
         PLUS,
         FIRST_F,
         SECOND_F,
         FIRST_COMPUTATIONAL_EXPRESSION,
         SECOND_COMPUTATIONAL_EXPRESSION,
      };

      // F PLUS F
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            FSyntaxNodeSP f0;
            PlusSyntaxNodeSP plus;
            FSyntaxNodeSP f1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &f0, &f1, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_F;
                  f0 = node;
               }
               else if( state == State::PLUS )
               {
                  state = State::SECOND_F;
                  f1 = node;
                  state = State::FINISH;
               }
            };
            handlers.plus_syntax_node = [ &plus, &state ]( const PlusSyntaxNodeSP& node )
            {
               if( state == State::FIRST_F )
               {
                  plus = node;
                  state = State::PLUS;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( f0 );
            plan.to_remove.nodes.push_back( plus );
            plan.to_remove.nodes.push_back( f1 );

            const auto& sum_node = std::make_shared< SumSyntaxNode >( f0, f1 );
            plan.to_add.nodes.push_back( sum_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION PLUS COMPUTATIONAL_EXPRESSION
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression0;
            PlusSyntaxNodeSP plus;
            ComputationalExpressionSyntaxNodeSP computational_expression1;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node =
               [ &computational_expression0, &computational_expression1,
                 &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::FIRST_COMPUTATIONAL_EXPRESSION;
                  computational_expression0 = node;
               }
               else if( state == State::PLUS )
               {
                  state = State::SECOND_COMPUTATIONAL_EXPRESSION;
                  computational_expression1 = node;
                  state = State::FINISH;
               }
            };
            handlers.plus_syntax_node = [ &plus, &state ]( const PlusSyntaxNodeSP& node )
            {
               if( state == State::FIRST_COMPUTATIONAL_EXPRESSION )
               {
                  plus = node;
                  state = State::PLUS;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression0 );
            plan.to_remove.nodes.push_back( plus );
            plan.to_remove.nodes.push_back( computational_expression1 );

            const auto& sum_node =
               std::make_shared< SumSyntaxNode >( computational_expression0, computational_expression1 );
            plan.to_add.nodes.push_back( sum_node );
            return plan;
         } );
      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
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

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS),
      //        one(Token_Type::E)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS),
      //        one(Token_Type::E)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::PLUS),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::PLUS),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::PLUS),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::PLUS),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });
   }
   // private:
   //     Production planAOpB(const Stack& stack)
   //     {
   //         auto it = stack.begin();
   //         std::advance(it, stack.size() - 3);
   //         const auto& f0 = *(it);
   //         const auto& plus = *(++it);
   //         const auto& f1 = *(++it);

   //        Production::Plan plan;
   //        plan.to_remove.nodes.push_back(f0);
   //        plan.to_remove.nodes.push_back(plus);
   //        plan.to_remove.nodes.push_back(f1);

   //        const auto& d = std::make_shared<SyntaxNodeSum>(f0, f1);
   //        plan.to_add.nodes.push_back(d);
   //        return Production{plan};
   //    }
};

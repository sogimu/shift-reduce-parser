#pragma once

#include "base/close_circle_bracket_syntax_node.h"
#include "base/open_circle_bracket_syntax_node.h"
#include "base/print_syntax_node.h"
#include "base/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "print_expression_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Print : public IGrammar
{
public:
   Print()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         PRINT,
         OPEN_CIRCLE_BRACKET,
         COMPUTATIONAL_EXPRESSION,
         CLOSE_CIRCLE_BRACKET,
      };

      // PRINT OPEN_CIRCLE_BRACKET COMPUTATIONAL_EXPRESSION CLOSE_CIRCLE_BRACKET SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            PrintSyntaxNodeSP print;
            OpenCircleBracketSyntaxNodeSP open;
            ComputationalExpressionSyntaxNodeSP computational_expression;
            CloseCircleBracketSyntaxNodeSP close;
            SemicolonSyntaxNodeSP semiclon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.print_syntax_node = [ &print, &state ]( const PrintSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::PRINT;
                  print = node;
               }
            };
            handlers.open_circle_bracket_syntax_node = [ &open, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::PRINT )
               {
                  state = State::OPEN_CIRCLE_BRACKET;
                  open = node;
               }
            };
            handlers.computational_expression_syntax_node =
               [ &computational_expression, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  state = State::COMPUTATIONAL_EXPRESSION;
                  computational_expression = node;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::COMPUTATIONAL_EXPRESSION )
               {
                  state = State::CLOSE_CIRCLE_BRACKET;
                  state = State::FINISH;
                  close = node;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( print );
            plan.to_remove.nodes.push_back( open );
            plan.to_remove.nodes.push_back( computational_expression );
            plan.to_remove.nodes.push_back( close );

            const auto& print_expression_node =
               std::make_shared< PrintExpressionSyntaxNode >( computational_expression );
            plan.to_add.nodes.push_back( print_expression_node );
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

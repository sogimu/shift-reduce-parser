#pragma once

#include "base/f_syntax_node.h"
#include "base/minus_syntax_node.h"
#include "base/number_syntax_node.h"
#include "enums.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <vector>

class E;
class T;
class P;

class F : public IGrammar
{
public:
   F()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         BOL,
         EOL,
         FIRST_MINUS,
         SECOND_MINUS,
         NUMBER
      };

      // MINUS NUMBER
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            MinusSyntaxNodeSP minus;
            NumberSyntaxNodeSP number;

            State state = State::START;

            iterate_over_last_n_nodes(
               stack, 2,
               SyntaxNodeEmptyVisitor::Handlers{ .default_handler = [ &state ]( const ISyntaxNodeSP& )
                                                 { state = State::ERROR; },
                                                 .minus_syntax_node =
                                                    [ &minus, &number, &state ]( const MinusSyntaxNodeSP& node )
                                                 {
                                                    if( state == State::START )
                                                    {
                                                       state = State::FIRST_MINUS;
                                                       minus = node;
                                                    }
                                                 },
                                                 .number_syntax_node =
                                                    [ &number, &state ]( const NumberSyntaxNodeSP& node )
                                                 {
                                                    if( state == State::FIRST_MINUS )
                                                    {
                                                       state = State::NUMBER;
                                                       number = node;
                                                       state = State::FINISH;
                                                    }
                                                 }

               } );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( minus );
            plan.to_remove.nodes.push_back( number );

            const auto& f_node = std::make_shared< FSyntaxNode >( minus, number );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );

      // NUMBER
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            NumberSyntaxNodeSP number;

            State state = State::START;

            iterate_over_last_n_nodes(
               stack, 1,
               SyntaxNodeEmptyVisitor::Handlers{ .default_handler = [ &state ]( const ISyntaxNodeSP& )
                                                 { state = State::ERROR; },
                                                 .number_syntax_node =
                                                    [ &number, &state ]( const NumberSyntaxNodeSP& node )
                                                 {
                                                    if( state == State::START )
                                                    {
                                                       state = State::NUMBER;
                                                       number = node;
                                                       state = State::FINISH;
                                                    }
                                                 } } );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( number );

            const auto& f_node = std::make_shared< FSyntaxNode >( number );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );

      // MINUS MINUS NUMBER
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            MinusSyntaxNodeSP first_minus;
            MinusSyntaxNodeSP second_minus;
            NumberSyntaxNodeSP number;

            State state = State::START;

            iterate_over_last_n_nodes(
               stack, 3,
               SyntaxNodeEmptyVisitor::Handlers{
                  .default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; },
                  .minus_syntax_node =
                     [ &first_minus, &second_minus, &number, &state ]( const MinusSyntaxNodeSP& node )
                  {
                     if( state == State::START )
                     {
                        state = State::FIRST_MINUS;
                        first_minus = node;
                     }
                     else if( state == State::FIRST_MINUS )
                     {
                        state = State::SECOND_MINUS;
                        second_minus = node;
                     }
                  },
                  .number_syntax_node =
                     [ &number, &state ]( const NumberSyntaxNodeSP& node )
                  {
                     if( state == State::SECOND_MINUS )
                     {
                        state = State::NUMBER;
                        number = node;
                        state = State::FINISH;
                     }
                  }

               } );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( first_minus );
            plan.to_remove.nodes.push_back( second_minus );
            plan.to_remove.nodes.push_back( number );

            const auto& f_node = std::make_shared< FSyntaxNode >( second_minus, number );
            plan.to_add.nodes.push_back( first_minus );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );

      // BOL MINUS NUMBER EOL
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            BolSyntaxNodeSP bol;
            MinusSyntaxNodeSP minus;
            NumberSyntaxNodeSP number;
            EolSyntaxNodeSP eol;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.bol_syntax_node = [ &bol, &state ]( const BolSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::BOL;
                  bol = node;
               }
            };
            handlers.minus_syntax_node = [ &minus, &number, &state ]( const MinusSyntaxNodeSP& node )
            {
               if( state == State::BOL )
               {
                  state = State::FIRST_MINUS;
                  minus = node;
               }
            };
            handlers.number_syntax_node = [ &number, &state ]( const NumberSyntaxNodeSP& node )
            {
               if( state == State::FIRST_MINUS )
               {
                  state = State::NUMBER;
                  number = node;
               }
            };
            handlers.eol_syntax_node = [ &eol, &state ]( const EolSyntaxNodeSP& node )
            {
               if( state == State::NUMBER )
               {
                  eol = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( bol );
            plan.to_remove.nodes.push_back( minus );
            plan.to_remove.nodes.push_back( number );
            plan.to_remove.nodes.push_back( eol );

            const auto& f_node = std::make_shared< FSyntaxNode >( minus, number );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::OPEN_CIRCLE_BRACKET),
      //        one(Token_Type::MINUS), one(Token_Type::INT)}, [this](const Stack& stack) -> Production
      //        {

      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);

      //            const auto& open_bracket = *(it);
      //            const auto& minus = *(++it);
      //            const auto& number = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(minus);
      //            plan.to_remove.nodes.push_back(number);

      //            const auto& d = std::make_shared<SyntaxNodeF>(minus, number);
      ////            d->token = {minus->token.text + number->token.text, Token_Type::F};
      //            plan.to_add.nodes.push_back(d);

      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::MULTIPLY), one(Token_Type::MINUS),
      //        one(Token_Type::INT)}, [this](const Stack& stack) -> Production
      //        {

      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 2);

      //            const auto& minus = *(it);
      //            const auto& number = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(minus);
      //            plan.to_remove.nodes.push_back(number);

      //            const auto& d = std::make_shared<SyntaxNodeF>(minus, number);
      ////            d->token = {minus->token.text + number->token.text, Token_Type::F};
      //            plan.to_add.nodes.push_back(d);

      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::DIVIDE), one(Token_Type::MINUS),
      //        one(Token_Type::INT)}, [this](const Stack& stack) -> Production
      //        {

      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 2);

      //            const auto& minus = *(it);
      //            const auto& number = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(minus);
      //            plan.to_remove.nodes.push_back(number);

      //            const auto& d = std::make_shared<SyntaxNodeF>(minus, number);
      ////            d->token = {minus->token.text + number->token.text, Token_Type::F};
      //            plan.to_add.nodes.push_back(d);

      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::INT)}, [this](const Stack& stack) ->
      //        Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 1);
      //            const auto& number = *it;

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(number);

      //            const auto& d = std::make_shared<SyntaxNodeF>(number);
      ////            d->token = {number->token.text, Token_Type::F};
      //            plan.to_add.nodes.push_back(d);

      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::F),
      //        one(Token_Type::EOL)}, [this](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& bol = *it;
      //            const auto& f = *(++it);
      //            const auto& eol = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(bol);
      //            plan.to_remove.nodes.push_back(f);
      //            plan.to_remove.nodes.push_back(eol);

      //            plan.to_add.nodes.push_back(f);

      //            return Production{plan};
      //        });
   }
};

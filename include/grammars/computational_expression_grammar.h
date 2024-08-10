#pragma once

#include "base/plus_syntax_node.h"
#include "base/semicolon_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
// #include "multiply/multiply_grammar.h"
#include "print_expression_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <iterator>
#include <memory>
#include <vector>

inline bool is_argument_or_operation( const ISyntaxNodeSP& node )
{
   bool result = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = false; };
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& node ) { result = true; };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& node ) { result = true; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& node ) { result = true; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& node ) { result = true; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& node ) { result = true; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& node ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& node ) { result = true; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline bool is_operation( const ISyntaxNodeSP& node )
{
   bool result = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = false; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& node ) { result = true; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& node ) { result = true; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& node ) { result = true; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& node ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& node ) { result = true; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline bool is_argument( const ISyntaxNodeSP& node )
{
   bool result = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = false; };
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& node ) { result = true; };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& node ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& node ) { result = false; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline int operation_weight( const ISyntaxNodeSP& node )
{
   int result = 0;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = -1; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& node ) { result = 1; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& node ) { result = 1; };
   handlers.subtraction_syntax_node = [ &result ]( const SubtractionSyntaxNodeSP& node ) { result = 2; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& node ) { result = 2; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& node ) { result = 2; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& node ) { result = -1; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

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
         ADDITION,
         SUBTRACTION,
         MULTIPLY,
         DIVISION,
         F,
         OPEN_CIRCLE_BRACKET,
         NAME,
         CLOSE_CIRCLE_BRACKET,
      };

      // AdditionSyntaxNodeSP SemicolonSyntaxNodeSP
      // SubtractionSyntaxNodeSP SemicolonSyntaxNodeSP
      // MultiplySyntaxNodeSP SemicolonSyntaxNodeSP
      // SemicolonSyntaxNodeSP  SemicolonSyntaxNodeSP
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            AdditionSyntaxNodeSP addition;
            SubtractionSyntaxNodeSP subtraction;
            MultiplySyntaxNodeSP multiply;
            DivisionSyntaxNodeSP division;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.addition_syntax_node = [ &addition, &state ]( const AdditionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  addition = node;
                  state = State::ADDITION;
               }
            };
            handlers.subtraction_syntax_node = [ &subtraction, &state ]( const SubtractionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  subtraction = node;
                  state = State::SUBTRACTION;
               }
            };
            handlers.multiply_syntax_node = [ &multiply, &state ]( const MultiplySyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  multiply = node;
                  state = State::MULTIPLY;
               }
            };
            handlers.division_syntax_node = [ &division, &state ]( const DivisionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  division = node;
                  state = State::DIVISION;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::ADDITION || state == State::MULTIPLY || state == State::SUBTRACTION || state == State::DIVISION )
               {
                  semicolon = node;
                  state = State::FINISH;
               }
            };
            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            ISyntaxNodeSP expression;
            if( addition )
               expression = addition;
            else if( subtraction )
               expression = subtraction;
            else if( multiply )
               expression = multiply;
            else if( division )
               expression = division;
            plan.to_remove.nodes.push_back( expression );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
            expression_node->Add( expression );
            plan.to_add.nodes.push_back( expression_node );
            plan.to_add.nodes.push_back( semicolon );
            return plan;
         } );

      State state;

      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            auto start_it = stack.end();
            for( auto it = stack.rbegin(); it != stack.rend(); ++it )
            {
               if( !is_argument_or_operation( *it ) )
                  break;
               start_it = it.base() - 1;
            }

            if( start_it != stack.end() )
               auto d = *start_it;

            std::stack< ISyntaxNodeSP > operations;
            std::stack< ISyntaxNodeSP > arguments;

            for( auto it = start_it; it != stack.end(); ++it )
            {
               const auto& node = *it;
               if( is_operation( node ) )
               {
                  int current_op = operation_weight( node );
                  int prev_op = -1;
                  ISyntaxNodeSP prev_operation;
                  if( !operations.empty() )
                  {
                     prev_operation = operations.top();
                     prev_op = operation_weight( prev_operation );
                  }

                  if( current_op < prev_op )
                  {
                     std::optional< Plan > plan_opt;
                     SyntaxNodeEmptyVisitor::Handlers handlers;
                     handlers.plus_syntax_node = [ &node, &plan_opt, &arguments ]( const PlusSyntaxNodeSP& prev_operation )
                     {
                        const auto& f0 = arguments.top();
                        arguments.pop();
                        const auto& f1 = arguments.top();
                        arguments.pop();

                        Plan plan;
                        plan.to_remove.nodes.push_back( f0 );
                        plan.to_remove.nodes.push_back( prev_operation );
                        plan.to_remove.nodes.push_back( f1 );
                        plan.to_remove.nodes.push_back( node );

                        const auto& addition_node = std::make_shared< AdditionSyntaxNode >();
                        addition_node->Add( f0 );
                        addition_node->Add( f1 );
                        plan.to_add.nodes.push_back( addition_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     handlers.minus_syntax_node = [ &node, &plan_opt, &arguments ]( const MinusSyntaxNodeSP& prev_operation )
                     {
                        const auto& f0 = arguments.top();
                        arguments.pop();
                        const auto& f1 = arguments.top();
                        arguments.pop();

                        Plan plan;
                        plan.to_remove.nodes.push_back( f0 );
                        plan.to_remove.nodes.push_back( prev_operation );
                        plan.to_remove.nodes.push_back( f1 );
                        plan.to_remove.nodes.push_back( node );

                        const auto& subtraction_node = std::make_shared< SubtractionSyntaxNode >();
                        subtraction_node->Add( f0 );
                        subtraction_node->Add( f1 );
                        plan.to_add.nodes.push_back( subtraction_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     handlers.asterisk_syntax_node = [ &node, &plan_opt, &arguments ]( const AsteriskSyntaxNodeSP& prev_operation )
                     {
                        const auto& f1 = arguments.top();
                        arguments.pop();
                        const auto& f0 = arguments.top();
                        arguments.pop();

                        Plan plan;
                        plan.to_remove.nodes.push_back( f0 );
                        plan.to_remove.nodes.push_back( prev_operation );
                        plan.to_remove.nodes.push_back( f1 );
                        plan.to_remove.nodes.push_back( node );

                        const auto& multiply_node = std::make_shared< MultiplySyntaxNode >();
                        multiply_node->Add( f0 );
                        multiply_node->Add( f1 );
                        plan.to_add.nodes.push_back( multiply_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     handlers.slash_syntax_node = [ &node, &plan_opt, &arguments ]( const SlashSyntaxNodeSP& prev_operation )
                     {
                        const auto& f1 = arguments.top();
                        arguments.pop();
                        const auto& f0 = arguments.top();
                        arguments.pop();

                        Plan plan;
                        plan.to_remove.nodes.push_back( f0 );
                        plan.to_remove.nodes.push_back( prev_operation );
                        plan.to_remove.nodes.push_back( f1 );
                        plan.to_remove.nodes.push_back( node );

                        const auto& division_node = std::make_shared< DivisionSyntaxNode >();
                        division_node->Add( f0 );
                        division_node->Add( f1 );
                        plan.to_add.nodes.push_back( division_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     // handlers.minus_syntax_node = [ &new_node, f0, f1 ]( const MinusSyntaxNodeSP& node ) { new_node = std::make_shared< SubtractionSyntaxNode >( f0, f1
                     // );
                     // };
                     const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
                     prev_operation->accept( visitor );
                     return plan_opt;
                  }
                  else if( current_op >= prev_op )
                  {
                     operations.push( node );
                  }
               }
               else if( is_argument( node ) )
               {
                  arguments.push( node );
               }
            }

            return {};
         } );

      // F+F
      // (F+F)
      // F+(F+F)
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            FSyntaxNodeSP f;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &f, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  f = node;
                  state = State::F;
                  state = State::FINISH;
               }
            };
            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( f );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >( f );
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // F
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            FSyntaxNodeSP f;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &f, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  f = node;
                  state = State::F;
                  state = State::FINISH;
               }
            };
            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( f );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >( f );
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // OPEN_CIRCLE_BRACKET NAME CLOSE_CIRCLE_BRACKET
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            OpenCircleBracketSyntaxNodeSP open;
            NameSyntaxNodeSP name;
            CloseCircleBracketSyntaxNodeSP close;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.open_circle_bracket_syntax_node = [ &open, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::OPEN_CIRCLE_BRACKET;
                  open = node;
               }
            };
            handlers.name_syntax_node = [ &name, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  state = State::NAME;
                  name = node;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::NAME )
               {
                  state = State::CLOSE_CIRCLE_BRACKET;
                  state = State::FINISH;
                  close = node;
               }
            };
            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( open );
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( close );

            const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >( name );
            plan.to_add.nodes.push_back( open );
            plan.to_add.nodes.push_back( computational_expression );
            plan.to_add.nodes.push_back( close );
            return plan;
         } );
      //        mProductionByFeature.emplace_back(Features{ one(Token_Type::ASSIGMENT)}, [](const Stack& stack) ->
      //        Production
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

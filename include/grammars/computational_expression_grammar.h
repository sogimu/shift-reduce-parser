#pragma once

#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "nonterminals/print_expression_syntax_node.h"
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
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& /* node */ ) { result = true; };
   // handlers.multiply_syntax_node = [ &result ]( const MultiplySyntaxNodeSP& node ) { result = true; };
   // handlers.division_syntax_node = [ &result ]( const DivisionSyntaxNodeSP& node ) { result = true; };
   // handlers.addition_syntax_node = [ &result ]( const AdditionSyntaxNodeSP& node ) { result = true; };
   // handlers.subtraction_syntax_node = [ &result ]( const SubtractionSyntaxNodeSP& node ) { result = true; };
   handlers.name_syntax_node = [ &result ]( const NameSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.open_circle_bracket_syntax_node = [ &result ]( const OpenCircleBracketSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.close_circle_bracket_syntax_node = [ &result ]( const CloseCircleBracketSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& /* node */ ) { result = true; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline bool is_operation( const ISyntaxNodeSP& node )
{
   bool result = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = false; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.close_circle_bracket_syntax_node = [ &result ]( const CloseCircleBracketSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& /* node */ ) { result = true; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline bool is_argument( const ISyntaxNodeSP& node )
{
   bool result = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = false; };
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& /* node */ ) { result = true; };
   // handlers.multiply_syntax_node = [ &result ]( const MultiplySyntaxNodeSP& node ) { result = true; };
   // handlers.division_syntax_node = [ &result ]( const DivisionSyntaxNodeSP& node ) { result = true; };
   // handlers.addition_syntax_node = [ &result ]( const AdditionSyntaxNodeSP& node ) { result = true; };
   // handlers.subtraction_syntax_node = [ &result ]( const SubtractionSyntaxNodeSP& node ) { result = true; };
   handlers.name_syntax_node = [ &result ]( const NameSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.computational_expression_syntax_node = [ &result ]( const ComputationalExpressionSyntaxNodeSP& /* node */ ) { result = true; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& /* node */ ) { result = false; };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   node->accept( visitor );
   return result;
}

inline int operation_weight( const ISyntaxNodeSP& node )
{
   int result = 0;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.default_handler = [ &result ]( const ISyntaxNodeSP& ) { result = -1; };
   handlers.plus_syntax_node = [ &result ]( const PlusSyntaxNodeSP& /* node  */ ) { result = 1; };
   handlers.minus_syntax_node = [ &result ]( const MinusSyntaxNodeSP& /* node */ ) { result = 1; };
   handlers.asterisk_syntax_node = [ &result ]( const AsteriskSyntaxNodeSP& /* node */ ) { result = 2; };
   handlers.slash_syntax_node = [ &result ]( const SlashSyntaxNodeSP& /* node */ ) { result = 2; };
   handlers.close_circle_bracket_syntax_node = [ &result ]( const CloseCircleBracketSyntaxNodeSP& /* node */ ) { result = -1; };
   handlers.semicolon_syntax_node = [ &result ]( const SemicolonSyntaxNodeSP& /* node */ ) { result = -1; };
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

      // OPEN_CIRCLE_BRACKET ADDITION|SUBTRACTION|MULTIPLY|DIVISION CLOSE_CIRCLE_BRACKET
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            ISyntaxNodeSP expression;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  open_circle_bracket = node;
                  state = State::OPEN_CIRCLE_BRACKET;
               }
            };
            handlers.addition_syntax_node = [ &expression, &state ]( const AdditionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  expression = node;
                  state = State::ADDITION;
               }
            };
            handlers.subtraction_syntax_node = [ &expression, &state ]( const SubtractionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  expression = node;
                  state = State::SUBTRACTION;
               }
            };
            handlers.multiply_syntax_node = [ &expression, &state ]( const MultiplySyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  expression = node;
                  state = State::MULTIPLY;
               }
            };
            handlers.division_syntax_node = [ &expression, &state ]( const DivisionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  expression = node;
                  state = State::DIVISION;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::ADDITION || state == State::MULTIPLY || state == State::SUBTRACTION || state == State::DIVISION )
               {
                  close_circle_bracket = node;
                  state = State::FINISH;
               }
            };
            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( open_circle_bracket );
            plan.to_remove.nodes.push_back( expression );
            plan.to_remove.nodes.push_back( close_circle_bracket );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
            expression_node->add_back( expression );
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // State state;

      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            auto start_it = stack.end();
            for( auto it = stack.rbegin(); it != stack.rend(); ++it )
            {
               if( !is_argument_or_operation( *it ) )
                  break;
               start_it = it.base() - 1;
            }

            std::stack< ISyntaxNodeSP > operations;
            std::stack< ISyntaxNodeSP > arguments;

            for( auto it = start_it; it != stack.end(); ++it )
            {
               const auto& node = *it;
               if( is_argument( node ) )
               {
                  arguments.push( node );
               }
               else if( is_operation( node ) )
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
                        addition_node->add_back( f0 );
                        addition_node->add_back( f1 );
                        const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
                        expression_node->add_back( addition_node );
                        plan.to_add.nodes.push_back( expression_node );
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
                        subtraction_node->add_back( f0 );
                        subtraction_node->add_back( f1 );
                        const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
                        expression_node->add_back( subtraction_node );
                        plan.to_add.nodes.push_back( expression_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     handlers.asterisk_syntax_node = [ &node, &plan_opt, &arguments ]( const AsteriskSyntaxNodeSP& prev_operation )
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

                        const auto& multiply_node = std::make_shared< MultiplySyntaxNode >();
                        multiply_node->add_back( f0 );
                        multiply_node->add_back( f1 );
                        const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
                        expression_node->add_back( multiply_node );
                        plan.to_add.nodes.push_back( expression_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     handlers.slash_syntax_node = [ &node, &plan_opt, &arguments ]( const SlashSyntaxNodeSP& prev_operation )
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

                        const auto& division_node = std::make_shared< DivisionSyntaxNode >();
                        division_node->add_back( f0 );
                        division_node->add_back( f1 );
                        const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
                        expression_node->add_back( division_node );
                        plan.to_add.nodes.push_back( expression_node );
                        plan.to_add.nodes.push_back( node );
                        plan_opt = plan;
                     };
                     const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
                     prev_operation->accept( visitor );
                     return plan_opt;
                  }
                  else if( current_op >= prev_op )
                  {
                     operations.push( node );
                  }
               }
            }

            return {};
         } );

      // F|ADDITION|SUBTRACTION|MULTIPLY|DIVISION SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            ISyntaxNodeSP expression;
            // SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &expression, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  expression = node;
                  state = State::FINISH;
               }
            };
            handlers.addition_syntax_node = [ &expression, &state ]( const AdditionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  expression = node;
                  state = State::FINISH;
               }
            };
            handlers.subtraction_syntax_node = [ &expression, &state ]( const SubtractionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  expression = node;
                  state = State::FINISH;
               }
            };
            handlers.multiply_syntax_node = [ &expression, &state ]( const MultiplySyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  expression = node;
                  state = State::FINISH;
               }
            };
            handlers.division_syntax_node = [ &expression, &state ]( const DivisionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  expression = node;
                  state = State::FINISH;
               }
            };
            // handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            // {
            //    if( state == State::F || state == State::ADDITION || state == State::MULTIPLY || state == State::SUBTRACTION || state == State::DIVISION )
            //    {
            //       semicolon = node;
            //       state = State::FINISH;
            //    }
            // };
            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( expression );
            // plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
            expression_node->add_back( expression );
            plan.to_add.nodes.push_back( expression_node );
            // plan.to_add.nodes.push_back( semicolon );
            return plan;
         } );
      //
      // // F
      // mProductions.emplace_back(
      //    [ this ]( const Stack& stack ) -> std::optional< Plan >
      //    {
      //       FSyntaxNodeSP f;
      //
      //       State state = State::START;
      //
      //       SyntaxNodeEmptyVisitor::Handlers handlers;
      //       handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
      //       handlers.f_syntax_node = [ &f, &state ]( const FSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             f = node;
      //             state = State::F;
      //             state = State::FINISH;
      //          }
      //       };
      //       iterate_over_last_n_nodes( stack, 1, handlers );
      //
      //       if( state != State::FINISH )
      //          return {};
      //
      //       Plan plan;
      //       plan.to_remove.nodes.push_back( f );
      //
      //       const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >( f );
      //       plan.to_add.nodes.push_back( expression_node );
      //       return plan;
      //    } );
   }
};

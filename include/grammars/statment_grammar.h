#pragma once

#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/semicolon_syntax_node.h"
#include "utils.h"

class Statment : public IGrammar
{
public:
   Statment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         COMPUTATIONAL_EXPRESSION,
         CONDITIONAL_EXPRESSION,
         IF_STATMENT,
         WHILE_STATMENT,
         FUNCTION,
         FUNCTION_CALL,
         PRINT_STATMENT,
         VARIBLE_ASSIGMENT_STATMENT,
         EQUAL,
         SEMICOLON,
         RETURN_STATMENT
      };

      // IF_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            IfStatmentSyntaxNodeSP if_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.if_statment_syntax_node = [ &if_statment_syntax_node, &state ]( const IfStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if_statment_syntax_node = node;
                  state = State::IF_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( if_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( if_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // WHILE_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            WhileStatmentSyntaxNodeSP while_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.while_statment_syntax_node = [ &while_statment_syntax_node, &state ]( const WhileStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  while_statment_syntax_node = node;
                  state = State::WHILE_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( while_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( while_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // FUNCTION
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionSyntaxNodeSP function_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_syntax_node = [ &function_syntax_node, &state ]( const FunctionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function_syntax_node = node;
                  state = State::FUNCTION;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( function_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // FUNCTION_CALL
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionCallSyntaxNodeSP function_call_syntax_node;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_call_syntax_node = [ &function_call_syntax_node, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function_call_syntax_node = node;
                  state = State::FUNCTION_CALL;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION_CALL )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_call_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( function_call_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );
      // PRINT_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            PrintStatmentSyntaxNodeSP print_statment_syntax_node;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.print_statment_syntax_node = [ &print_statment_syntax_node, &state ]( const PrintStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  print_statment_syntax_node = node;
                  state = State::PRINT_STATMENT;
                  state = State::FINISH;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::PRINT_STATMENT )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( print_statment_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( print_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // RETURN_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            ReturnStatmentSyntaxNodeSP return_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.return_statment_syntax_node = [ &return_statment_syntax_node, &state ]( const ReturnStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  return_statment_syntax_node = node;
                  state = State::RETURN_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( return_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( return_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION_NODE SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            ComputationalExpressionSyntaxNodeSP computational_expression_syntax_node;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.computational_expression_syntax_node = [ &computational_expression_syntax_node, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  computational_expression_syntax_node = node;
                  state = State::COMPUTATIONAL_EXPRESSION;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::COMPUTATIONAL_EXPRESSION )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( computational_expression_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_node = std::make_shared< StatmentSyntaxNode >( computational_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // CONDITIONAL_EXPRESSION SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            ConditionalExpressionSyntaxNodeSP conditional_expression_syntax_node;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.conditional_expression_syntax_node = [ &conditional_expression_syntax_node, &state ]( const ConditionalExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  conditional_expression_syntax_node = node;
                  state = State::CONDITIONAL_EXPRESSION;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::CONDITIONAL_EXPRESSION )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( conditional_expression_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( conditional_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // VARIBLE_ASSIGMENT_STATMENT SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            VaribleAssigmentStatmentSyntaxNodeSP varible_assigment_statment_syntax_node;
            // SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.varible_assigment_statment_syntax_node = [ &varible_assigment_statment_syntax_node, &state ]( const VaribleAssigmentStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  varible_assigment_statment_syntax_node = node;
                  state = State::VARIBLE_ASSIGMENT_STATMENT;
                  state = State::FINISH;
               }
            };
            // handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            // {
            //    if( state == State::VARIBLE_ASSIGMENT_STATMENT )
            //    {
            //       semicolon = node;
            //       // state = State::SEMICOLON;
            //       state = State::FINISH;
            //    }
            // };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( varible_assigment_statment_syntax_node );
            // plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( varible_assigment_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );
   }
};

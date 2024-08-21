#pragma once

#include "computational_expression_syntax_node.h"
#include "conditional_expression_syntax_node.h"
#include "expression_syntax_node.h"
#include "i_grammar.h"
#include "if_expression_syntax_node.h"
#include "print_expression_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <vector>

class Expression : public IGrammar
{
public:
   Expression()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         COMPUTATIONAL_EXPRESSION,
         CONDITIONAL_EXPRESSION,
         IF_EXPRESSION,
         WHILE_EXPRESSION,
         PRINT_EXPRESSION,
         VARIBLE_ASSIGMENT,
         EQUAL,
         SEMICOLON
      };

      // IF_EXPRESSION
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            IfExpressionSyntaxNodeSP if_expression_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.if_expression_syntax_node = [ &if_expression_syntax_node, &state ]( const IfExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if_expression_syntax_node = node;
                  state = State::IF_EXPRESSION;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( if_expression_syntax_node );

            const auto& expression_syntax_node = std::make_shared< ExpressionSyntaxNode >( if_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // WHILE_EXPRESSION
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            WhileExpressionSyntaxNodeSP while_expression_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.while_expression_syntax_node = [ &while_expression_syntax_node, &state ]( const WhileExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  while_expression_syntax_node = node;
                  state = State::WHILE_EXPRESSION;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( while_expression_syntax_node );

            const auto& expression_syntax_node = std::make_shared< ExpressionSyntaxNode >( while_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // PRINT_EXPRESSION
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            PrintExpressionSyntaxNodeSP print_expression_syntax_node;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.print_expression_syntax_node = [ &print_expression_syntax_node, &state ]( const PrintExpressionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  print_expression_syntax_node = node;
                  state = State::PRINT_EXPRESSION;
                  state = State::FINISH;
               }
            };
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::PRINT_EXPRESSION )
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
            plan.to_remove.nodes.push_back( print_expression_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< ExpressionSyntaxNode >( print_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // COMPUTATIONAL_EXPRESSION_NODE SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
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

            const auto& expression_node = std::make_shared< ExpressionSyntaxNode >( computational_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // CONDITIONAL_EXPRESSION SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
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

            const auto& expression_syntax_node = std::make_shared< ExpressionSyntaxNode >( conditional_expression_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // VARIBLE_ASSIGMENT SEMICOLON
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            VaribleAssigmentSyntaxNodeSP varible_assigment_syntax_node;
            // SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.varible_assigment_syntax_node = [ &varible_assigment_syntax_node, &state ]( const VaribleAssigmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  varible_assigment_syntax_node = node;
                  state = State::VARIBLE_ASSIGMENT;
                  state = State::FINISH;
               }
            };
            // handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            // {
            //    if( state == State::VARIBLE_ASSIGMENT )
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
            plan.to_remove.nodes.push_back( varible_assigment_syntax_node );
            // plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_syntax_node = std::make_shared< ExpressionSyntaxNode >( varible_assigment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );
   }
};

#pragma once

#include "terminals/return_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Return : public IGrammar
{
public:
   Return()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         RETURN,
         ARGUMENT,
         SEMICOLON,
      };

      // RETURN computational_expression SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
         {
            ReturnSyntaxNodeSP return_node;
            ISyntaxNodeSP argument;
            SemicolonSyntaxNodeSP semiclon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.return_syntax_node = [ &return_node, &state ]( const ReturnSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::RETURN;
                  return_node = node;
               }
            };
            handlers.name_syntax_node = [ &argument, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  state = State::ARGUMENT;
                  argument = node;
               }
            };
            handlers.computational_expression_syntax_node = [ &argument, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  state = State::ARGUMENT;
                  argument = node;
               }
            };
            handlers.function_call_syntax_node = [ &argument, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  std::vector< ISyntaxNodeSP > arguments;
                  for( const auto& argument : *node )
                     arguments.push_back( argument );
                  const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( node->name(), arguments );
                  argument = function_call;
                  state = State::ARGUMENT;
               }
            };
            handlers.semicolon_syntax_node = [ &semiclon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::ARGUMENT )
               {
                  state = State::SEMICOLON;
                  state = State::FINISH;
                  semiclon = node;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( return_node );
            plan.to_remove.nodes.push_back( argument );
            plan.to_remove.nodes.push_back( semiclon );

            const auto& return_statment_node = std::make_shared< ReturnStatmentSyntaxNode >( argument );
            plan.to_add.nodes.push_back( return_statment_node );
            return plan;
         } );
   }
};

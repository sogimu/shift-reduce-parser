#pragma once

#include "i_grammar.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Function : public IGrammar
{
public:
   Function()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         FUNCTION,
         NAME,
         ARGUMENT,
         OPEN_CIRCLE_BRACKET,
         CLOSE_CIRCLE_BRACKET,
         COMMA,
         SCOPE_STATMENT,
         FUNCTION_CALL
      };

      // FUNCTION FUNCTION_CALL SCOPE
      mProductions.emplace_back(
         []( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionSyntaxNodeSP function;
            FunctionCallSyntaxNodeSP function_call;
            ScopeSyntaxNodeSP scope_statment;
            State state = State::START;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_syntax_node = [ &function, &state ]( const FunctionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function = node;
                  state = State::FUNCTION;
               }
            };
            handlers.function_call_syntax_node = [ &function_call, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION )
               {
                  function_call = node;
                  state = State::FUNCTION_CALL;
               }
            };
            handlers.scope_statment_syntax_node = [ &scope_statment, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION_CALL )
               {
                  scope_statment = node;
                  state = State::SCOPE_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function );
            plan.to_remove.nodes.push_back( function_call );
            plan.to_remove.nodes.push_back( scope_statment );

            const auto& function_node = std::make_shared< FunctionStatmentSyntaxNode >( function_call->name() );
            for( const auto& argument : *function_call )
               function_node->add_back( argument );
            function_node->add_back( scope_statment );
            plan.to_add.nodes.push_back( function_node );
            return plan;
         } );
   }
};

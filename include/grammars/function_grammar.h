#pragma once

#include "i_grammar.h"
#include "nonterminals/function_call_or_definition_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "nonterminals/scope_syntax_node.h"
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
         NAME,
         ARGUMENT,
         OPEN_CIRCLE_BRACKET,
         CLOSE_CIRCLE_BRACKET,
         COMMA,
         SCOPE,
         FUNCTION_CALL_OR_DEFINITION
      };

      // FUNCTION_CALL_OR_DEFINITION SCOPE
      mProductions.emplace_back(
         []( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionCallOrDefinitionSyntaxNodeSP function_call_or_definition_syntax_node;
            ScopeSyntaxNodeSP scope_expression;
            State state = State::START;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_call_or_definition_syntax_node = [ &function_call_or_definition_syntax_node, &state ]( const FunctionCallOrDefinitionSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function_call_or_definition_syntax_node = node;
                  state = State::FUNCTION_CALL_OR_DEFINITION;
               }
            };
            handlers.scope_syntax_node = [ &scope_expression, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION_CALL_OR_DEFINITION )
               {
                  scope_expression = node;
                  state = State::SCOPE;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_call_or_definition_syntax_node );
            plan.to_remove.nodes.push_back( scope_expression );

            const auto& function_node = std::make_shared< FunctionSyntaxNode >( function_call_or_definition_syntax_node->name() );
            for( const auto& argument : *function_call_or_definition_syntax_node )
               function_node->add_back( argument );
            function_node->add_back( scope_expression );
            plan.to_add.nodes.push_back( function_node );
            return plan;
         } );
   }
};

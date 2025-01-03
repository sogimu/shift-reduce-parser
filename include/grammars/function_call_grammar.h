#pragma once

#include "nonterminals/expression_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "i_grammar.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class FunctionCall : public IGrammar
{
public:
   FunctionCall()
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
         FUNCTION_CALL_OR_DEFINITION,
         SEMICOLON,
      };

      // FUNCTION_CALL_OR_DEFINITION SEMICOLON
      mProductions.emplace_back(
         []( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionCallOrDefinitionSyntaxNodeSP function_call_or_definition_syntax_node;
            SemicolonSyntaxNodeSP semicolon;
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
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION_CALL_OR_DEFINITION )
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
            plan.to_remove.nodes.push_back( function_call_or_definition_syntax_node );
            plan.to_remove.nodes.push_back( semicolon );

            std::vector< ISyntaxNodeSP > arguments;
            for( const auto& argument : *function_call_or_definition_syntax_node )
               arguments.push_back( argument );
            const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( function_call_or_definition_syntax_node->name(), arguments );

            plan.to_add.nodes.push_back( function_call );
            return plan;
         } );

      // FUNCTION_CALL_OR_DEFINITION CLOSE_CIRCLE_BRACKET
      mProductions.emplace_back(
         []( const Stack& stack ) -> std::optional< Plan >
         {
            FunctionCallOrDefinitionSyntaxNodeSP function_call_or_definition_syntax_node;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
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
            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::FUNCTION_CALL_OR_DEFINITION )
               {
                  close_circle_bracket = node;
                  state = State::CLOSE_CIRCLE_BRACKET;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_call_or_definition_syntax_node );
            plan.to_remove.nodes.push_back( close_circle_bracket );

            std::vector< ISyntaxNodeSP > arguments;
            for( const auto& argument : *function_call_or_definition_syntax_node )
               arguments.push_back( argument );
            const auto& function_call = std::make_shared< FunctionCallSyntaxNode >( function_call_or_definition_syntax_node->name(), arguments );

            plan.to_add.nodes.push_back( function_call );
            plan.to_add.nodes.push_back( close_circle_bracket );
            return plan;
         } );
   }
};

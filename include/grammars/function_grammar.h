#pragma once

#include "i_grammar.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
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
         CONDITION,
         CLOSE_CIRCLE_BRACKET,
         COMMA,
         SCOPE_STATMENT,
         FUNCTION_CALL
      };

      // NAME OPEN_CIRCLE_BRACKET (NAME|COMPUTATIONAL_EXPRESSION COMMA?)+ CLOSE_CIRCLE_BRACKET SCOPE
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NameSyntaxNodeSP name;
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            std::vector< ISyntaxNodeSP > arguments;
            std::vector< ISyntaxNodeSP > commas;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
            ScopeSyntaxNodeSP scope_statment;
            bool is_open_circle_bracket_found = false;
            bool is_close_circle_bracket_found = false;
            size_t distance_between_open_close_circle_bracket = 0;

            State state = State::START;

            auto it = stack.rbegin();
            SyntaxNodeEmptyVisitor::Handlers close_circle_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               close_circle_bracket_handler.close_circle_bracket_syntax_node = [ &is_close_circle_bracket_found ]( const CloseCircleBracketSyntaxNodeSP& /* node */ )
               { is_close_circle_bracket_found = true; };
               const auto& close_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_circle_bracket_handler );
               ( *it )->accept( close_circle_bracket_visitor );
               if( is_close_circle_bracket_found )
               {
                  break;
               }
            }

            if( !is_close_circle_bracket_found )
               return {};

            SyntaxNodeEmptyVisitor::Handlers open_circle_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               open_circle_bracket_handler.open_circle_bracket_syntax_node = [ &is_open_circle_bracket_found ]( const OpenCircleBracketSyntaxNodeSP& /* node */ )
               { is_open_circle_bracket_found = true; };
               const auto& open_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_circle_bracket_handler );
               ( *it )->accept( open_circle_bracket_visitor );
               if( is_open_circle_bracket_found )
               {
                  distance_between_open_close_circle_bracket = std::distance( stack.rbegin(), it ) + 1;
                  break;
               }
            }

            if( !is_open_circle_bracket_found || !is_close_circle_bracket_found )
               return {};

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.name_syntax_node = [ &name, &arguments, &state ]( const NameSyntaxNodeSP& node )
            {
               auto s = state;
               (void) s;
               if( state == State::START )
               {
                  name = node;
                  state = State::NAME;
               }
               else if( state == State::OPEN_CIRCLE_BRACKET || state == State::COMMA )
               {
                  arguments.emplace_back( node );
                  state = State::ARGUMENT;
               }
            };
            handlers.computational_expression_syntax_node = [ /*  &name, */ &arguments, &state ]( const ComputationalExpressionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET || state == State::COMMA )
               {
                  arguments.emplace_back( node );
                  state = State::ARGUMENT;
               }
            };
            handlers.comma_syntax_node = [ &commas, &state ]( const CommaSyntaxNodeSP& node )
            {
               auto s = state;
               (void) s;
               if( state == State::ARGUMENT )
               {
                  commas.emplace_back( node );
                  state = State::COMMA;
               }
            };
            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               auto s = state;
               (void) s;
               if( state == State::NAME )
               {
                  open_circle_bracket = node;
                  state = State::OPEN_CIRCLE_BRACKET;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               auto s = state;
               (void) s;
               if( state == State::ARGUMENT )
               {
                  close_circle_bracket = node;
                  state = State::CLOSE_CIRCLE_BRACKET;
               }
            };
            handlers.scope_statment_syntax_node = [ &scope_statment, &state ]( const ScopeSyntaxNodeSP& node )
            {
               auto s = state;
               (void) s;
               if( state == State::CLOSE_CIRCLE_BRACKET )
               {
                  scope_statment = node;
                  state = State::SCOPE_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, distance_between_open_close_circle_bracket + 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( name );
            plan.to_remove.nodes.push_back( open_circle_bracket );
            for( const auto& argument : arguments )
               plan.to_remove.nodes.push_back( argument );
            for( const auto& comma : commas )
               plan.to_remove.nodes.push_back( comma );
            plan.to_remove.nodes.push_back( close_circle_bracket );
            plan.to_remove.nodes.push_back( scope_statment );

            const auto& function_node = std::make_shared< FunctionStatmentSyntaxNode >( name->value(), arguments, scope_statment );
            plan.to_add.nodes.push_back( function_node );
            return plan;
         } );
   }
};

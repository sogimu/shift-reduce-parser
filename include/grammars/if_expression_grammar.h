#pragma once

#include "nonterminals/conditional_expression_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/if_expression_syntax_node.h"
#include "nonterminals/scope_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class If : public IGrammar
{
public:
   If()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         IF,
         OPEN_CIRCLE_BRACKET,
         CONDITION,
         CLOSE_CIRCLE_BRACKET,
         SCOPE,
      };

      // IF CONDITION SCOPE
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            IfSyntaxNodeSP if_node;
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            ConditionalExpressionSyntaxNodeSP conditional_expression;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
            ScopeSyntaxNodeSP scope_expression;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.if_syntax_node = [ &if_node, &state ]( const IfSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if_node = node;
                  state = State::IF;
               }
            };
            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::IF )
               {
                  open_circle_bracket = node;
                  state = State::OPEN_CIRCLE_BRACKET;
               }
            };
            handlers.conditional_expression_syntax_node = [ &conditional_expression, &state ]( const ConditionalExpressionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  conditional_expression = node;
                  state = State::CONDITION;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::CONDITION )
               {
                  close_circle_bracket = node;
                  state = State::CLOSE_CIRCLE_BRACKET;
               }
            };

            handlers.scope_syntax_node = [ &scope_expression, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::CLOSE_CIRCLE_BRACKET )
               {
                  scope_expression = node;
                  state = State::SCOPE;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 5, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( if_node );
            plan.to_remove.nodes.push_back( open_circle_bracket );
            plan.to_remove.nodes.push_back( conditional_expression );
            plan.to_remove.nodes.push_back( close_circle_bracket );
            plan.to_remove.nodes.push_back( scope_expression );

            const auto& if_expression_node = std::make_shared< IfExpressionSyntaxNode >( conditional_expression, scope_expression );
            plan.to_add.nodes.push_back( if_expression_node );
            return plan;
         } );
   }
};

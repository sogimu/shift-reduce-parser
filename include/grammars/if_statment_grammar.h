#pragma once

#include "i_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
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
         SCOPE_STATMENT,
      };

      // IF OPEN_CIRCLE_BRACKET F|BIN_EXPR|UN_EXPR|FUNCTION_CALL|NAME CLOSE_CIRCLE_BRACKET SCOPE
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            IfSyntaxNodeSP if_node;
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            ISyntaxNodeSP condition;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
            ScopeSyntaxNodeSP scope_statment;

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
            handlers.f_syntax_node = [ &condition, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  condition = node;
                  state = State::CONDITION;
               }
            };
            handlers.bin_expr_syntax_node = [ &condition, &state ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  condition = node;
                  state = State::CONDITION;
               }
            };
            handlers.un_expr_syntax_node = [ &condition, &state ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  condition = node;
                  state = State::CONDITION;
               }
            };
            handlers.name_syntax_node = [ &condition, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  condition = node;
                  state = State::CONDITION;
               }
            };
            handlers.function_call_syntax_node = [ &condition, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  condition = node;
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

            handlers.scope_statment_syntax_node = [ &scope_statment, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::CLOSE_CIRCLE_BRACKET )
               {
                  scope_statment = node;
                  state = State::SCOPE_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 5, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( if_node );
            plan.to_remove.nodes.push_back( open_circle_bracket );
            plan.to_remove.nodes.push_back( condition );
            plan.to_remove.nodes.push_back( close_circle_bracket );
            plan.to_remove.nodes.push_back( scope_statment );

            const auto& if_statment_node = std::make_shared< IfStatmentSyntaxNode >( condition, scope_statment );
            plan.to_add.nodes.push_back( if_statment_node );
            return plan;
         } );
   }
};

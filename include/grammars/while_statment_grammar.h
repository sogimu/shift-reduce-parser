#pragma once

#include "i_syntax_node.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class While : public IGrammar
{
public:
   While()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         WHILE,
         OPEN_CIRCLE_BRACKET,
         CONDITION,
         CLOSE_CIRCLE_BRACKET,
         SCOPE_STATMENT,
      };

      // WHILE OPEN_CIRCLE_BRACKET F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL CLOSE_CIRCLE_BRACKET SCOPE
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            WhileSyntaxNodeSP while_node;
            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
            ISyntaxNodeSP conditional_expression;
            CloseCircleBracketSyntaxNodeSP close_circle_bracket;
            ScopeSyntaxNodeSP scope_statment;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.while_syntax_node = [ &while_node, &state ]( const WhileSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  while_node = node;
                  state = State::WHILE;
               }
            };
            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::WHILE )
               {
                  open_circle_bracket = node;
                  state = State::OPEN_CIRCLE_BRACKET;
               }
            };
            handlers.f_syntax_node = [ &conditional_expression, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  conditional_expression = node;
                  state = State::CONDITION;
               }
            };
            handlers.bin_expr_syntax_node = [ &conditional_expression, &state ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  conditional_expression = node;
                  state = State::CONDITION;
               }
            };
            handlers.un_expr_syntax_node = [ &conditional_expression, &state ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  conditional_expression = node;
                  state = State::CONDITION;
               }
            };
            handlers.name_syntax_node = [ &conditional_expression, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  conditional_expression = node;
                  state = State::CONDITION;
               }
            };
            handlers.function_call_syntax_node = [ &conditional_expression, &state ]( const FunctionCallSyntaxNodeSP& node )
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
            plan.to_remove.nodes.push_back( while_node );
            plan.to_remove.nodes.push_back( open_circle_bracket );
            plan.to_remove.nodes.push_back( conditional_expression );
            plan.to_remove.nodes.push_back( close_circle_bracket );
            plan.to_remove.nodes.push_back( scope_statment );

            const auto& while_statment_node = std::make_shared< WhileStatmentSyntaxNode >( conditional_expression, scope_statment );
            plan.to_add.nodes.push_back( while_statment_node );
            return plan;
         } );
   }
};

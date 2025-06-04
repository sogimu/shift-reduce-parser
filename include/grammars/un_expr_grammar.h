#pragma once

#include "i_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/bol_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/number_syntax_node.h"
#include "terminals/plus_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/slash_syntax_node.h"
#include "utils.h"

#include <vector>

class UnExpr : public IGrammar
{
public:
   UnExpr()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         BOL,
         EOL,
         MINUS,
         NUMBER,
         F,
         ALLOWED,
         NOT_ALLOWED
      };

      // !F&&!BIN_EXPR|!UN_EXPR|!NAME|!FUNCTION_CALL MINUS F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL
      mProductions.emplace_back(
         [  ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            MinusSyntaxNodeSP minus;
            ISyntaxNodeSP f;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& )
                                                 { state = State::ALLOWED; };

           handlers.minus_syntax_node =
              [ &minus, &f, &state ]( const MinusSyntaxNodeSP& node )
           {
              if( state == State::START )
              {
                 state = State::ALLOWED;
                 minus = node;
              }
              else if( state == State::ALLOWED )
              {
                 state = State::MINUS;
                 minus = node;
              }
           };
           handlers.f_syntax_node =
              [ &f, &state, &lookahead ]( const FSyntaxNodeSP& node )
           {
              if( state == State::START )
              {
                 f = node;
                 state = State::NOT_ALLOWED;
              }
              else if( state == State::MINUS )
              {
                 state = State::F;
                 f = node;
                 state = State::FINISH;
              }
           };
           handlers.bin_expr_syntax_node =
              [ &f, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
           {
              if( state == State::START )
              {
                 f = node;
                 state = State::NOT_ALLOWED;
              }
              else if( state == State::MINUS )
              {
                 state = State::F;
                 f = node;
                 state = State::FINISH;
              }
           };
           handlers.name_syntax_node =
              [ &f, &state, &lookahead ]( const NameSyntaxNodeSP& node )
           {
              if( state == State::START )
              {
                 f = node;
                 state = State::NOT_ALLOWED;
              }
              else if( state == State::MINUS )
              {
                 state = State::F;
                 f = node;
                 state = State::FINISH;
              }
           };
           handlers.function_call_syntax_node =
              [ &f, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
           {
              if( state == State::START )
              {
                 f = node;
                 state = State::NOT_ALLOWED;
              }
              else if( state == State::MINUS )
              {
                 state = State::F;
                 f = node;
                 state = State::FINISH;
              }
           };
            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( minus );
            plan.to_remove.nodes.push_back( f );

            const auto& un_expr_node = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f );
            plan.to_add.nodes.push_back( un_expr_node );
            return plan;
         } );
   }
};

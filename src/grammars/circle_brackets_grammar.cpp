#include "circle_brackets_grammar.h"

#include "terminals/equal_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "i_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/open_curly_bracket_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>
 
CircleBrackets::CircleBrackets()
 {
    enum class State
    {
       START,
       FINISH,
       ERROR,
       ADDITION,
       SUBTRACTION,
       MULTIPLY,
       DIVISION,
       PLUS,
       MINUS,
       F,
       BIN_EXPR,
       UN_EXPR,
       OPEN_CIRCLE_BRACKET,
       NAME,
       CLOSE_CIRCLE_BRACKET,
       COMPUTATIONAL_EXPRESSION
    };

    // !NAME|!IF|!PRINT OPEN_CIRCLE_BRACKET F|BIN_EXPR|UN_EXPR CLOSE_CIRCLE_BRACKET 
    mProductions.emplace_back(
       [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
       {
          OpenCircleBracketSyntaxNodeSP open_circle_bracket;
          ISyntaxNodeSP expression;
          CloseCircleBracketSyntaxNodeSP close_circle_bracket;

          State state = State::START;

          Plan plan;
          SyntaxNodeEmptyVisitor::Handlers handlers;
          handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::START; };
          handlers.name_syntax_node = [ &state ]( const NameSyntaxNodeSP& node )
          {
              state = State::ERROR;
          };
          handlers.if_syntax_node = [ &state ]( const IfSyntaxNodeSP& node )
          {
              state = State::ERROR;
          };
          handlers.print_syntax_node = [ &state ]( const PrintSyntaxNodeSP& node )
          {
              state = State::ERROR;
          };
          handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
          {
             auto s = state;
             (void) s;
             if( state == State::START )
             {
                open_circle_bracket = node;
                state = State::OPEN_CIRCLE_BRACKET;
             }
          };
          handlers.f_syntax_node = [ &expression, &state ]( const FSyntaxNodeSP& node )
          {
             if( state == State::OPEN_CIRCLE_BRACKET )
             {
                expression = node;
                state = State::F;
             }
          };
          handlers.bin_expr_syntax_node = [ &expression, &state ]( const BinExprSyntaxNodeSP& node )
          {
             if( state == State::OPEN_CIRCLE_BRACKET )
             {
                expression = node;
                state = State::F;
             }
          };
          handlers.un_expr_syntax_node = [ &expression, &state ]( const UnExprSyntaxNodeSP& node )
          {
             if( state == State::OPEN_CIRCLE_BRACKET )
             {
                expression = node;
                state = State::F;
             }
          };
          handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state, &lookahead ]( const CloseCircleBracketSyntaxNodeSP& node )
          {
             if( state == State::F )
             {
               if( lookahead && !check_type<OpenCurlyBracketSyntaxNode>( lookahead ) )
               {
                  close_circle_bracket = node;
                  state = State::FINISH;
                }
             }
          };
          iterate_over_last_n_nodes( stack, 4, handlers );

          if( state != State::FINISH )
             return {};

          plan.to_remove.nodes.push_back( open_circle_bracket );
          plan.to_remove.nodes.push_back( expression );
          plan.to_remove.nodes.push_back( close_circle_bracket );

          plan.to_add.nodes.push_back( expression );
          return plan;
       } );
 }

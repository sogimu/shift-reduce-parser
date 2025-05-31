#pragma once

#include "terminals/asterisk_syntax_node.h"
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

class E;
class T;
class P;

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
         NOT_F
      };

      // !F MINUS F
      mProductions.emplace_back(
         [  ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            MinusSyntaxNodeSP minus;
            FSyntaxNodeSP f;

            State state = State::START;

            iterate_over_last_n_nodes(
               stack, 3,
               SyntaxNodeEmptyVisitor::Handlers{ .default_handler = [ &state ]( const ISyntaxNodeSP& )
                                                 { state = State::NOT_F; },
                                                 .minus_syntax_node =
                                                    [ &minus, &f, &state ]( const MinusSyntaxNodeSP& node )
                                                 {
                                                    if( state == State::START )
                                                    {
                                                       state = State::NOT_F;
                                                    }
                                                    else if( state == State::NOT_F )
                                                    {
                                                       state = State::MINUS;
                                                       minus = node;
                                                    }
                                                 },
                                                 .f_syntax_node =
                                                    [ &f, &state, &lookahead ]( const FSyntaxNodeSP& node )
                                                 {
                                                    if( state == State::START )
                                                    {
                                                       state = State::ERROR;
                                                    }
                                                    else if( state == State::MINUS )
                                                    {
                                                       state = State::F;
                                                       f = node;
                                                       state = State::FINISH;
                                                    }
                                                 }
               } );

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

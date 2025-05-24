#pragma once

#include "terminals/f_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/number_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <vector>

class E;
class T;
class P;

class F : public IGrammar
{
public:
   F()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         BOL,
         EOL,
         FIRST_MINUS,
         SECOND_MINUS,
         NUMBER,
         F
      };

      // NUMBER [PLUS,MINUS,MULTIPLY,DIVISION,SEMICOLON,CLOSE_CIRCLE_BRACKET]
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            NumberSyntaxNodeSP number;

            State state = State::START;

            iterate_over_last_n_nodes( stack, 1,
                                       SyntaxNodeEmptyVisitor::Handlers{ .default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; },
                                                                         .number_syntax_node =
                                                                            [ &number, &state, &lookahead ]( const NumberSyntaxNodeSP& node )
                                                                         {
                                                                            if( state == State::START )
                                                                            {
                                                                               state = State::NUMBER;

                                                                               if( lookahead && ( 
                                                                                    check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<MinusSyntaxNode>( lookahead ) || 
                                                                                    check_type<PlusSyntaxNode>( lookahead ) || 
                                                                                    check_type<AsteriskSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                                                                    check_type<SlashSyntaxNode>( lookahead ) ) )
                                                                               {
                                                                                 number = node;
                                                                                 state = State::FINISH;
                                                                               }
                                                                            }
                                                                         } } );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( number );

            const auto& f_node = std::make_shared< FSyntaxNode >( number );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );

      // // MINUS MINUS NUMBER
      // mProductions.emplace_back(
      //    []( const Stack& stack ) -> std::optional< Plan >
      //    {
      //       MinusSyntaxNodeSP first_minus;
      //       MinusSyntaxNodeSP second_minus;
      //       NumberSyntaxNodeSP number;
      //
      //       State state = State::START;
      //
      //       iterate_over_last_n_nodes( stack, 3,
      //                                  SyntaxNodeEmptyVisitor::Handlers{ .default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; },
      //                                                                    .minus_syntax_node =
      //                                                                       [ &first_minus, &second_minus, /* &number,  */ &state ]( const MinusSyntaxNodeSP& node )
      //                                                                    {
      //                                                                       if( state == State::START )
      //                                                                       {
      //                                                                          state = State::FIRST_MINUS;
      //                                                                          first_minus = node;
      //                                                                       }
      //                                                                       else if( state == State::FIRST_MINUS )
      //                                                                       {
      //                                                                          state = State::SECOND_MINUS;
      //                                                                          second_minus = node;
      //                                                                       }
      //                                                                    },
      //                                                                    .number_syntax_node =
      //                                                                       [ &number, &state ]( const NumberSyntaxNodeSP& node )
      //                                                                    {
      //                                                                       if( state == State::SECOND_MINUS )
      //                                                                       {
      //                                                                          state = State::NUMBER;
      //                                                                          number = node;
      //                                                                          state = State::FINISH;
      //                                                                       }
      //                                                                    }
      //
      //                                  } );
      //
      //       if( state != State::FINISH )
      //          return {};
      //
      //       Plan plan;
      //       plan.to_remove.nodes.push_back( first_minus );
      //       plan.to_remove.nodes.push_back( second_minus );
      //       plan.to_remove.nodes.push_back( number );
      //
      //       const auto& f_node = std::make_shared< FSyntaxNode >( second_minus, number );
      //       plan.to_add.nodes.push_back( first_minus );
      //       plan.to_add.nodes.push_back( f_node );
      //       return plan;
      //    } );
      //
   }
};

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
         CORRECT_FIRST_NODE,
         INCORRECT_FIRST_NODE
      };

      // !F&&!BIN_EXPR | !UN_EXPR | !NAME | !FUNCTION_CALL MINUS F | BIN_EXPR | UN_EXPR | NAME | FUNCTION_CALL
      mProductions.emplace_back(
         [  ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 3;
            const size_t minimal_steps_number = 3;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number]( size_t n )->PlanOrProgress
                                                            {
                                                            MinusSyntaxNodeSP minus;
                                                            ISyntaxNodeSP f;

                                                            const Stack& s = stack;
                                                            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                            using HandlerReturn = Handlers::HandlerReturn;
                                                            using Impact = Handlers::Impact;

                                                             handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                             { 
                                                                if( state == State::START )
                                                                {
                                                                  return { State::CORRECT_FIRST_NODE, Impact::NO_MOVE };
                                                                }
                                                                return { State::ERROR, Impact::ERROR };
                                                             };

                                                             handlers.minus_syntax_node =
                                                                [ &minus ]( const State& state, const MinusSyntaxNodeSP& node ) -> HandlerReturn
                                                             {
                                                                if( state == State::START )
                                                                {
                                                                   minus = node;
                                                                  return { State::CORRECT_FIRST_NODE, Impact::MOVE };
                                                                }
                                                                else if( state == State::CORRECT_FIRST_NODE )
                                                                {
                                                                   minus = node;
                                                                  return { State::MINUS, Impact::MOVE };
                                                                }
                                                               return { state, Impact::ERROR };
                                                             };
                                                             handlers.f_syntax_node =
                                                                [ &f ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                                                             {
                                                                if( state == State::START )
                                                                {
                                                                  return { State::INCORRECT_FIRST_NODE, Impact::ERROR };
                                                                }
                                                                else if( state == State::MINUS )
                                                                {
                                                                  f = node;
                                                                  return { State::FINISH, Impact::MOVE };
                                                                }
                                                                return { state, Impact::ERROR };
                                                             };
                                                             handlers.bin_expr_syntax_node =
                                                                [ &f ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                                                             {
                                                                if( state == State::START )
                                                                {
                                                                  return { State::INCORRECT_FIRST_NODE, Impact::ERROR };
                                                                }
                                                                else if( state == State::MINUS )
                                                                {
                                                                  f = node;
                                                                  return { State::FINISH, Impact::MOVE };
                                                                }
                                                                 return { state, Impact::ERROR };
                                                             };
                                                             handlers.name_syntax_node =
                                                                [ &f ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                             {
                                                                if( state == State::START )
                                                                {
                                                                  return { State::INCORRECT_FIRST_NODE, Impact::ERROR };
                                                                }
                                                                else if( state == State::MINUS )
                                                                {
                                                                  f = node;
                                                                  return { State::FINISH, Impact::MOVE };
                                                                }
                                                                 return { state, Impact::ERROR };
                                                             };
                                                             handlers.function_call_syntax_node =
                                                                [ &f ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                                                             {
                                                                if( state == State::START )
                                                                {
                                                                  return { State::INCORRECT_FIRST_NODE, Impact::ERROR };
                                                                }
                                                                else if( state == State::MINUS )
                                                                {
                                                                  f = node;
                                                                  return { State::FINISH, Impact::MOVE };
                                                                }
                                                                return { state, Impact::ERROR };
                                                              };

                                                            auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );

                                                            PlanOrProgress plan_or_progress;
                                                            if( iteration_result.state == State::ERROR )
                                                            {
                                                                plan_or_progress = Progress{ .readiness = 0 };
                                                            }  
                                                            else if( iteration_result.state == State::FINISH )
                                                            {
                                                                Plan plan;
                                                                plan.to_remove.nodes.push_back( minus );
                                                                plan.to_remove.nodes.push_back( f );

                                                                const auto& un_expr_node = std::make_shared< UnExprSyntaxNode >( UnExprSyntaxNode::Type::Negation, f, minus->lexical_tokens() );
                                                                plan.to_add.nodes.push_back( un_expr_node );
                                                                plan_or_progress = plan;
                                                            }
                                                            else {
                                                                plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                            }
                                                            return plan_or_progress;
                                                            });
         } );
   }
};

#include "circle_brackets_grammar.h"

#include "i_grammar.h"
#include "terminals/equal_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "i_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
// #include "syntax_node_empty_visitor.h"
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
       []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
       {
          const size_t minimal_size = 4;
          size_t minimal_steps_number = 4;
          return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                          {
                                                            OpenCircleBracketSyntaxNodeSP open_circle_bracket;
                                                            ISyntaxNodeSP expression;
                                                            CloseCircleBracketSyntaxNodeSP close_circle_bracket;

                                                            const Stack& s = stack;
                                                            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                            using HandlerReturn = Handlers::HandlerReturn;
                                                            using Impact = Handlers::Impact;

                                                            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                            { 
                                                               return { State::ERROR, Impact::ERROR };
                                                            };

                                                            handlers.name_syntax_node = [ &expression ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::OPEN_CIRCLE_BRACKET )
                                                               {
                                                                  expression = node;
                                                                  return { State::F, Impact::MOVE };
                                                               }
                                                               else if( state == State::START )
                                                               {
                                                                  return { State::ERROR, Impact::ERROR };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.if_syntax_node = []( const State& state, const IfSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               return { State::ERROR, Impact::ERROR };
                                                            };
                                                            handlers.print_syntax_node = []( const State& state, const PrintSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               return { State::ERROR, Impact::ERROR };
                                                            };
                                                            handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::START )
                                                               {
                                                                  open_circle_bracket = node;
                                                                  return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.f_syntax_node = [ &expression ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::OPEN_CIRCLE_BRACKET )
                                                               {
                                                                  expression = node;
                                                                    return { State::F, Impact::MOVE };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.bin_expr_syntax_node = [ &expression ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::OPEN_CIRCLE_BRACKET )
                                                               {
                                                                  expression = node;
                                                                  return { State::F, Impact::MOVE };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.un_expr_syntax_node = [ &expression ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::OPEN_CIRCLE_BRACKET )
                                                               {
                                                                  expression = node;
                                                                  return { State::F, Impact::MOVE };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.function_call_syntax_node = [ &expression ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::OPEN_CIRCLE_BRACKET )
                                                               {
                                                                  expression = node;
                                                                  return { State::F, Impact::MOVE };
                                                               }
                                                               return { state, Impact::NO_MOVE };
                                                            };
                                                            handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &lookahead ]( const State& state, const CloseCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::F )
                                                               {
                                                                 if( lookahead && !check_type<OpenCurlyBracketSyntaxNode>( lookahead ) )
                                                                 {
                                                                    close_circle_bracket = node;
                                                                    return { State::FINISH, Impact::MOVE };
                                                                 }
                                                               }
                                                               return { state, Impact::NO_MOVE };
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
                                                                plan.to_remove.nodes.push_back( open_circle_bracket );
                                                                plan.to_remove.nodes.push_back( expression );
                                                                plan.to_remove.nodes.push_back( close_circle_bracket );

                                                                plan.to_add.nodes.push_back( expression );
                                                                  plan_or_progress = plan;
                                                            }
                                                            else {
                                                                plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                            }
                                                            return plan_or_progress;
                                                          });
       } );
 }

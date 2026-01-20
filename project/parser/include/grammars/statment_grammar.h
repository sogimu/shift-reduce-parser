#pragma once

#include "nonterminals/statment_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "syntax_node_progress_visitor.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "utils.h"
#include "progress_counter.h"

class Statment : public IGrammar
{
public:
   Statment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         F,
         CONDITIONAL_EXPRESSION,
         IF_STATMENT,
         WHILE_STATMENT,
         FUNCTION_STATMENT,
         FUNCTION_CALL,
         PRINT_STATMENT,
         VARIBLE_ASSIGMENT_STATMENT,
         EQUAL,
         SEMICOLON,
         RETURN_STATMENT,
         CLOSE_CURLY_BRACKET,
         BOL,
         EOL,
         STATMENT
      };

      // IF_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 1;
            const size_t minimal_steps_number = 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &lookahead, &minimal_size]( size_t n )->PlanOrProgress
            {
                IfStatmentSyntaxNodeSP if_statment_syntax_node;

                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;
                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
                { 
                    return { State::ERROR, Impact::ERROR };
                };
                handlers.if_statment_syntax_node = [ &if_statment_syntax_node, &lookahead ]( const State& state, const IfStatmentSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      if_statment_syntax_node = node;
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
                    plan.to_remove.nodes.push_back( if_statment_syntax_node );

                    const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( if_statment_syntax_node );
                    plan.to_add.nodes.push_back( statment_syntax_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
            });
         } );


      // WHILE_STATMENT
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 1;
            const size_t minimal_steps_number = 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &lookahead, &minimal_size]( size_t n )->PlanOrProgress
            {
                WhileStatmentSyntaxNodeSP while_statment_syntax_node;

                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;
                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
                { 
                    return { State::ERROR, Impact::ERROR };
                };
                handlers.while_statment_syntax_node = [ &while_statment_syntax_node ]( const State& state, const WhileStatmentSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      while_statment_syntax_node = node;
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
                    plan.to_remove.nodes.push_back( while_statment_syntax_node );

                    const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( while_statment_syntax_node );
                    plan.to_add.nodes.push_back( statment_syntax_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
            });
         } );

      // // FUNCTION_STATMENT
      // mProductions.emplace_back(
      //    []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
      //    {
      //       const size_t minimal_size = 1;
      //       const size_t minimal_steps_number = 1;
      //       return find_grammar_matching_progress( stack, minimal_size, [ &stack, &lookahead, &minimal_size ]( size_t n ) -> PlanOrProgress
      //       {
      //           FunctionStatmentSyntaxNodeSP function_syntax_node;
      //
      //           SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
      //           using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
      //           using HandlerReturn = Handlers::HandlerReturn;
      //           using Impact = Handlers::Impact;
      //           handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
      //           { 
      //               return { State::ERROR, Impact::ERROR };
      //           };
      //
      //           handlers.function_statment_syntax_node = [ &function_syntax_node ]( const State& state, const FunctionStatmentSyntaxNodeSP& node ) -> HandlerReturn
      //           {
      //               if( state == State::START )
      //               {
      //                   function_syntax_node = node;
      //                   return { State::FINISH, Impact::MOVE };
      //               }
      //               return { state, Impact::ERROR };
      //           };
      //
      //           auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );
      //
      //           PlanOrProgress plan_or_progress;
      //           if( iteration_result.state == State::ERROR )
      //           {
      //               plan_or_progress = Progress{ .readiness = 0 };
      //           }  
      //           else if( iteration_result.state == State::FINISH )
      //           {
      //               Plan plan;
      //               plan.to_remove.nodes.push_back( function_syntax_node );
      //
      //               const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( function_syntax_node );
      //               plan.to_add.nodes.push_back( statment_syntax_node );
      //               plan_or_progress = plan;
      //           }
      //           else
      //           {
      //               plan_or_progress = Progress{ .readiness = iteration_result.readiness };
      //           }
      //           return plan_or_progress;
      //       });
      //    } );

      // // FUNCTION_CALL
      // mProductions.emplace_back(
      //    [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
      //    {
      //       const size_t minimal_size = 1;
      //       const size_t minimal_steps_number = 1;
      //       return find_grammar_matching_progress(stack, minimal_size, [&stack, &lookahead, &minimal_size]( size_t n )->PlanOrProgress
      //       {
      //           FunctionCallSyntaxNodeSP function_call_syntax_node;
      //
      //           SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
      //           using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
      //           using HandlerReturn = Handlers::HandlerReturn;
      //           using Impact = Handlers::Impact;
      //           handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
      //           { 
      //               return { State::ERROR, Impact::ERROR };
      //           };
      //
      //           handlers.function_call_syntax_node = [ &function_call_syntax_node ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
      //           {
      //               if( state == State::START )
      //               {
      //                   function_call_syntax_node = node;
      //                   return { State::FINISH, Impact::MOVE };
      //               }
      //               return { state, Impact::ERROR };
      //           };
      //
      //           auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );
      //
      //           PlanOrProgress plan_or_progress;
      //           if( iteration_result.state == State::ERROR )
      //           {
      //               plan_or_progress = Progress{ .readiness = 0 };
      //           }  
      //           else if( iteration_result.state == State::FINISH )
      //           {
      //               Plan plan;
      //               plan.to_remove.nodes.push_back( function_call_syntax_node );
      //
      //               const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( function_call_syntax_node );
      //               plan.to_add.nodes.push_back( statment_syntax_node );
      //               plan_or_progress = plan;
      //           }
      //           else
      //           {
      //               plan_or_progress = Progress{ .readiness = iteration_result.readiness };
      //           }
      //           return plan_or_progress;
      //       });
      //
      //    } );

      // PRINT_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 1;
            const size_t minimal_steps_number = 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
            {
                PrintStatmentSyntaxNodeSP print_statment_syntax_node;

                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;
                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
                { 
                    return { State::ERROR, Impact::ERROR };
                };
                handlers.print_statment_syntax_node = [ &print_statment_syntax_node ]( const State& state, const PrintStatmentSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      print_statment_syntax_node = node;
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
                    plan.to_remove.nodes.push_back( print_statment_syntax_node );

                    const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( print_statment_syntax_node );
                    plan.to_add.nodes.push_back( statment_syntax_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
            });
         } );

      // // ARRAY
      // mProductions.emplace_back(
      //    [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
      //    {
      //       const size_t minimal_size = 1;
      //       const size_t minimal_steps_number = 1;
      //       return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
      //       {
      //           ArraySyntaxNodeSP array_syntax_node;
      //
      //           SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
      //           using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
      //           using HandlerReturn = Handlers::HandlerReturn;
      //           using Impact = Handlers::Impact;
      //           handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
      //           { 
      //               return { State::ERROR, Impact::ERROR };
      //           };
      //           handlers.array_syntax_node = [ &array_syntax_node ]( const State& state, const ArraySyntaxNodeSP& node ) -> HandlerReturn
      //           {
      //              if( state == State::START )
      //              {
      //                 array_syntax_node = node;
      //                 return { State::FINISH, Impact::MOVE };
      //              }
      //              return { state, Impact::ERROR };
      //           };
      //
      //           auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );
      //
      //           PlanOrProgress plan_or_progress;
      //           if( iteration_result.state == State::ERROR )
      //           {
      //               plan_or_progress = Progress{ .readiness = 0 };
      //           }  
      //           else if( iteration_result.state == State::FINISH )
      //           {
      //               Plan plan;
      //               plan.to_remove.nodes.push_back( array_syntax_node );
      //
      //               const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( array_syntax_node );
      //               plan.to_add.nodes.push_back( statment_syntax_node );
      //               plan_or_progress = plan;
      //           }
      //           else
      //           {
      //               plan_or_progress = Progress{ .readiness = iteration_result.readiness };
      //           }
      //           return plan_or_progress;
      //       });
      //    } );

      // RETURN_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 1;
            const size_t minimal_steps_number = 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
            {
                ReturnStatmentSyntaxNodeSP return_statment_syntax_node;

                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;
                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
                { 
                    return { State::ERROR, Impact::ERROR };
                };

                handlers.return_statment_syntax_node = [ &return_statment_syntax_node ]( const State& state,  const ReturnStatmentSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      return_statment_syntax_node = node;
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
                    plan.to_remove.nodes.push_back( return_statment_syntax_node );

                    const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( return_statment_syntax_node );
                    plan.to_add.nodes.push_back( statment_syntax_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
            });

         } );

      // // F|BIN_EXPR|UN_EXPR|NAME [SEMICOLON, CLOSE_CURLY_BRACKET]
      // mProductions.emplace_back(
      //    [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
      //    {
      //       ProgressCounter progress_counter{1};
      //       ISyntaxNodeSP f;
      //       SemicolonSyntaxNodeSP semicolon;
      //
      //       State state = State::START;
      //
      //       SyntaxNodeEmptyVisitor::Handlers handlers;
      //       handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) 
      //       { 
      //           state = State::ERROR;
      //       };
      //       handlers.f_syntax_node = [ &f, &state, &lookahead, &progress_counter ]( const FSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //          )
      //             {
      //                 f = node;
      //                 state = State::F;
      //                 state = State::FINISH;
      //                progress_counter.Step();
      //             }
      //          }
      //       };
      //       handlers.bin_expr_syntax_node = [ &f, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //            {
      //                f = node;
      //                state = State::F;
      //                state = State::FINISH;
      //            }
      //          }
      //       };
      //       handlers.un_expr_syntax_node = [ &f, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //              {
      //                  f = node;
      //                  state = State::F;
      //                  state = State::FINISH;
      //              }
      //          }
      //       };
      //       handlers.name_syntax_node = [ &f, &state, &lookahead ]( const NameSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //             {
      //                 f = node;
      //                 state = State::F;
      //                 state = State::FINISH;
      //             }
      //          }
      //       };
      //       handlers.function_call_syntax_node = [ &f, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //             {
      //                 f = node;
      //                 state = State::F;
      //                 state = State::FINISH;
      //             }
      //          }
      //       };
      //       handlers.object_syntax_node = [ &f, &state, &lookahead ]( const ObjectSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //             {
      //                 f = node;
      //                 state = State::F;
      //                 state = State::FINISH;
      //             }
      //          }
      //       };
      //       handlers.array_syntax_node = [ &f, &state, &lookahead ]( const ArraySyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) //||
      //                              // check_type< CloseCurlyBracketSyntaxNode >( lookahead ) 
      //         ) 
      //             {
      //                 f = node;
      //                 state = State::F;
      //                 state = State::FINISH;
      //             }
      //          }
      //       };
      //
      //
      //       iterate_over_last_n_nodes( stack, 1, handlers );
      //
      //       if( state == State::ERROR )
      //       {
      //           return Progress{ .readiness = 0.0 };
      //       }  
      //       else if( state != State::FINISH )
      //       {
      //          return Progress{ .readiness = progress_counter.Status() };
      //       }
      //
      //       Plan plan;
      //       plan.to_remove.nodes.push_back( f );
      //
      //       const auto& statment_node = std::make_shared< StatmentSyntaxNode >( f );
      //       plan.to_add.nodes.push_back( statment_node );
      //       return plan;
      //    } );

      // // VARIBLE_ASSIGMENT_STATMENT
      // mProductions.emplace_back(
      //    []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
      //    {
      //       const size_t minimal_size = 1;
      //       const size_t minimal_steps_number = 1;
      //       return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
      //                                                   {
      //                                                       VaribleAssigmentStatmentSyntaxNodeSP varible_assigment_statment_syntax_node;
      //
      //                                                       SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
      //                                                       using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
      //                                                       using HandlerReturn = Handlers::HandlerReturn;
      //                                                       using Impact = Handlers::Impact;
      //                                                       handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn 
      //                                                       { 
      //                                                           return { State::ERROR, Impact::ERROR };
      //                                                       };
      //                                                       handlers.varible_assigment_statment_syntax_node = [ &varible_assigment_statment_syntax_node ]( const State& state, const VaribleAssigmentStatmentSyntaxNodeSP& node ) -> HandlerReturn
      //                                                       {
      //                                                           if( state == State::START )
      //                                                           {
      //                                                               varible_assigment_statment_syntax_node = node;
      //                                                               return { State::FINISH, Impact::MOVE };
      //                                                           }
      //                                                           return { state, Impact::ERROR };
      //                                                       };
      //
      //                                                       auto iteration_result = iterate_over_last_n_nodesv2< State >( stack, n, handlers );
      //
      //                                                       PlanOrProgress plan_or_progress;
      //                                                       if( iteration_result.state == State::ERROR )
      //                                                       {
      //                                                           plan_or_progress = Progress{ .readiness = 0 };
      //                                                       }  
      //                                                       else if( iteration_result.state == State::FINISH )
      //                                                       {
      //                                                           Plan plan;
      //                                                           plan.to_remove.nodes.push_back( varible_assigment_statment_syntax_node );
      //
      //                                                           const auto& statment_syntax_node = std::make_shared< StatmentSyntaxNode >( varible_assigment_statment_syntax_node );
      //                                                           plan.to_add.nodes.push_back( statment_syntax_node );
      //                                                           plan_or_progress = plan;
      //                                                       }
      //                                                       else
      //                                                       {
      //                                                           plan_or_progress = Progress{ .readiness = iteration_result.readiness };
      //                                                       }
      //                                                       return plan_or_progress;
      //                                                   });
      //    } );
      //
      // STATMENT SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 2;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
                                                            {
                                                            StatmentSyntaxNodeSP statment;
                                                            SemicolonSyntaxNodeSP semicolon;    

                                                            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                                                            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                            using HandlerReturn = Handlers::HandlerReturn;
                                                            using Impact = Handlers::Impact;
                                                            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn { return { state, Impact::ERROR }; };
                                                            handlers.statment_syntax_node = [ &statment ]( const State& state, const StatmentSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::START )
                                                               {
                                                                  statment = node;
                                                                  return {State::STATMENT, Impact::MOVE};
                                                               }
                                                               return {state, Impact::NO_MOVE};
                                                            };
                                                            
                                                            handlers.semicolon_syntax_node = [ &semicolon ]( const State& state, const SemicolonSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::STATMENT )
                                                               {
                                                                  semicolon = node;
                                                                  return { State::FINISH, Impact::MOVE };
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
                                                                plan.to_remove.nodes.push_back( statment );
                                                                plan.to_remove.nodes.push_back( semicolon );
                                                                statment->add_lexical_token( semicolon->lexical_tokens().at(0) );

                                                                plan.to_add.nodes.push_back( statment );
                                                                plan_or_progress = plan;
                                                            }
                                                            else {
                                                                plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                                                            }
                                                            return plan_or_progress;
                                                            });
         } );

      // BOL STATMENT EOL
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            BolSyntaxNodeSP bol;
            StatmentSyntaxNodeSP statment;
            EolSyntaxNodeSP eol;
            
            const size_t minimal_size = 3;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_size]( size_t n )->PlanOrProgress
                                                            {
                                                            BolSyntaxNodeSP bol;
                                                            StatmentSyntaxNodeSP statment;
                                                            EolSyntaxNodeSP eol;

                                                            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_size, State::START};
                                                            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                            using HandlerReturn = Handlers::HandlerReturn;
                                                            using Impact = Handlers::Impact;
                                                            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn { return { state, Impact::ERROR }; };
                                                            handlers.bol_syntax_node = [ &bol ]( const State& state, const BolSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::START )
                                                               {
                                                                  bol = node;
                                                                  return {State::BOL, Impact::MOVE};
                                                               }
                                                               return {state, Impact::ERROR};
                                                            };
                                                            handlers.statment_syntax_node = [ &statment ]( const State& state, const StatmentSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::BOL )
                                                               {
                                                                  statment = node;
                                                                  return {State::STATMENT, Impact::MOVE};
                                                               }
                                                               return {state, Impact::ERROR};
                                                            };
                                                            handlers.eol_syntax_node = [ &eol ]( const State& state, const EolSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::STATMENT )
                                                               {
                                                                  eol = node;
                                                                  return {State::FINISH, Impact::MOVE};
                                                               }
                                                               return {state, Impact::ERROR};
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
                                                                plan.to_remove.nodes.push_back( bol );
                                                                plan.to_remove.nodes.push_back( statment );
                                                                plan.to_remove.nodes.push_back( eol );

                                                                plan.to_add.nodes.push_back( statment );
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

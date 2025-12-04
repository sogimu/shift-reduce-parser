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
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 5;
            size_t minimal_steps_number = 5;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            
            {
                IfSyntaxNodeSP if_node;
                OpenCircleBracketSyntaxNodeSP open_circle_bracket;
                ISyntaxNodeSP condition;
                CloseCircleBracketSyntaxNodeSP close_circle_bracket;
                ScopeSyntaxNodeSP scope_statment;


                const Stack& s = stack;
                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;

                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                { 
                   return { State::ERROR, Impact::ERROR };
                };
                handlers.if_syntax_node = [ &if_node ]( const State& state, const IfSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      if_node = node;
                       return { State::IF, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::IF )
                   {
                      open_circle_bracket = node;
                       return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.f_syntax_node = [ &condition ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      condition = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.bin_expr_syntax_node = [ &condition ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      condition = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.un_expr_syntax_node = [ &condition ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      condition = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.name_syntax_node = [ &condition ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      condition = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.function_call_syntax_node = [ &condition ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      condition = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket ]( const State& state, const CloseCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::CONDITION )
                   {
                      close_circle_bracket = node;
                       return { State::CLOSE_CIRCLE_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };

                handlers.scope_statment_syntax_node = [ &scope_statment ]( const State& state, const ScopeSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::CLOSE_CIRCLE_BRACKET )
                   {
                      scope_statment = node;
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
                    plan.to_remove.nodes.push_back( if_node );
                    plan.to_remove.nodes.push_back( open_circle_bracket );
                    plan.to_remove.nodes.push_back( condition );
                    plan.to_remove.nodes.push_back( close_circle_bracket );
                    plan.to_remove.nodes.push_back( scope_statment );

                    const auto& if_statment_node = std::make_shared< IfStatmentSyntaxNode >( condition, scope_statment, std::vector< LexicalTokens::LexicalToken >{ if_node->lexical_tokens().at(0) } );
                    plan.to_add.nodes.push_back( if_statment_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
              });
         } );
   }
};

#pragma once

#include "i_grammar.h"
#include "terminals/function_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class FunctionStatment : public IGrammar
{
public:
   FunctionStatment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         FUNCTION,
         NAME,
         ARGUMENT,
         OPEN_CIRCLE_BRACKET,
         CONDITION,
         CLOSE_CIRCLE_BRACKET,
         COMMA,
         SCOPE_STATMENT,
         FUNCTION_CALL
      };

      // FUNCTION NAME OPEN_CIRCLE_BRACKET (NAME|F|BIN_EXPR|UN_EXPR|FUNC_CALL COMMA?)+ CLOSE_CIRCLE_BRACKET SCOPE
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            bool is_open_circle_bracket_found = false;
            bool is_close_circle_bracket_found = false;
            size_t distance_between_open_close_circle_bracket = 0;

            auto it = stack.rbegin();

            SyntaxNodeEmptyVisitor::Handlers open_circle_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               open_circle_bracket_handler.open_circle_bracket_syntax_node = [ &is_open_circle_bracket_found ]( const OpenCircleBracketSyntaxNodeSP& /* node */ )
               { is_open_circle_bracket_found = true; };
               const auto& open_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_circle_bracket_handler );
               ( *it )->accept( open_circle_bracket_visitor );
               if( is_open_circle_bracket_found )
               {
                  distance_between_open_close_circle_bracket = std::distance( stack.rbegin(), it ) + 1;
                  break;
               }
            }
            
            if( !is_open_circle_bracket_found )
                return Progress{ .readiness = 0.0 };


            SyntaxNodeEmptyVisitor::Handlers close_circle_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               close_circle_bracket_handler.close_circle_bracket_syntax_node = [ &is_close_circle_bracket_found ]( const CloseCircleBracketSyntaxNodeSP& /* node */ )
               { is_close_circle_bracket_found = true; };
               const auto& close_circle_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_circle_bracket_handler );
               ( *it )->accept( close_circle_bracket_visitor );
               if( is_close_circle_bracket_found )
               {
                  break;
               }
            }
            
            const size_t minimal_size = distance_between_open_close_circle_bracket + 2;
            size_t minimal_steps_number = 0;
            if( is_open_circle_bracket_found && !is_close_circle_bracket_found )
                minimal_steps_number = minimal_size + 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            
            {

                FunctionSyntaxNodeSP function;
                NameSyntaxNodeSP name;
                OpenCircleBracketSyntaxNodeSP open_circle_bracket;
                std::vector< ISyntaxNodeSP > arguments;
                std::vector< ISyntaxNodeSP > commas;
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
                handlers.function_syntax_node = [ &function, &arguments ]( const State& state, const FunctionSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      function = node;
                       return { State::FUNCTION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.name_syntax_node = [ &name, &arguments ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::FUNCTION )
                   {
                      name = node;
                       return { State::NAME, Impact::MOVE };
                   }
                   else if( state == State::OPEN_CIRCLE_BRACKET || state == State::COMMA )
                   {
                      arguments.emplace_back( node );
                       return { State::ARGUMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.comma_syntax_node = [ &commas ]( const State& state, const CommaSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::ARGUMENT )
                   {
                      commas.emplace_back( node );
                       return { State::COMMA, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::NAME )
                   {
                      open_circle_bracket = node;
                       return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket ]( const State& state, const CloseCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::ARGUMENT || state == State::OPEN_CIRCLE_BRACKET )
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
                    plan.to_remove.nodes.push_back( function );
                    plan.to_remove.nodes.push_back( name );
                    plan.to_remove.nodes.push_back( open_circle_bracket );
                    for( const auto& argument : arguments )
                       plan.to_remove.nodes.push_back( argument );
                    for( const auto& comma : commas )
                       plan.to_remove.nodes.push_back( comma );
                    plan.to_remove.nodes.push_back( close_circle_bracket );
                    plan.to_remove.nodes.push_back( scope_statment );

                    const auto& function_node = std::make_shared< FunctionStatmentSyntaxNode >( name->value(), arguments, scope_statment );
                    plan.to_add.nodes.push_back( function_node );
                    plan_or_progress = plan;
                }
                else
                {
                    plan_or_progress = Progress{ .readiness = iteration_result.readiness };
                }
                return plan_or_progress;
             });
        });
      }
};

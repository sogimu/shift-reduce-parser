#pragma once

#include "nonterminals/statment_syntax_node.h"
#include "terminals/close_circle_bracket_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/open_circle_bracket_syntax_node.h"
#include "terminals/print_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Print : public IGrammar
{
public:
   Print()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         PRINT,
         OPEN_CIRCLE_BRACKET,
         ARGUMENT,
         CLOSE_CIRCLE_BRACKET,
      };

      // PRINT OPEN_CIRCLE_BRACKET F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL CLOSE_CIRCLE_BRACKET SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 4;
            size_t minimal_steps_number = 4;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            
            {
              PrintSyntaxNodeSP print;
              OpenCircleBracketSyntaxNodeSP open;
              ISyntaxNodeSP argument;
              CloseCircleBracketSyntaxNodeSP close;

              const Stack& s = stack;
              SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
              using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
              using HandlerReturn = Handlers::HandlerReturn;
              using Impact = Handlers::Impact;

              handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
              { 
                 return { State::ERROR, Impact::ERROR };
              };
              handlers.print_syntax_node = [ &print ]( const State& state, const PrintSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::START )
                 {
                    print = node;
                    return { State::PRINT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.open_circle_bracket_syntax_node = [ &open ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::PRINT )
                 {
                    open = node;
                    return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.name_syntax_node = [ &argument ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::OPEN_CIRCLE_BRACKET )
                 {
                    argument = node;
                    return { State::ARGUMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.f_syntax_node = [ &argument ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::OPEN_CIRCLE_BRACKET )
                 {
                    argument = node;
                    return { State::ARGUMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.bin_expr_syntax_node = [ &argument ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::OPEN_CIRCLE_BRACKET )
                 {
                    argument = node;
                    return { State::ARGUMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.un_expr_syntax_node = [ &argument ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::OPEN_CIRCLE_BRACKET )
                 {
                    argument = node;
                    return { State::ARGUMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.function_call_syntax_node = [ &argument ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::OPEN_CIRCLE_BRACKET )
                 {
                    argument = node;
                    return { State::ARGUMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.close_circle_bracket_syntax_node = [ &close ]( const State& state, const CloseCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::ARGUMENT )
                 {
                    close = node;
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
                  plan.to_remove.nodes.push_back( print );
                  plan.to_remove.nodes.push_back( open );
                  plan.to_remove.nodes.push_back( argument );
                  plan.to_remove.nodes.push_back( close );

                  const auto& print_statment_node = std::make_shared< PrintStatmentSyntaxNode >( argument );
                  plan.to_add.nodes.push_back( print_statment_node );
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

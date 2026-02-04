
#include "return_statment_grammar.h"

#include "lexical_tokens.h"
#include "nonterminals/member_expression_syntax_node.h"
#include "terminals/return_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

Return::Return()
{
  enum class State
  {
     START,
     FINISH,
     ERROR,
     RETURN,
     ARGUMENT,
     SEMICOLON,
     RETURN_STATMENT
  };

  // RETURN F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL|MEMBER_EXPRESSION [SEMICOLON]
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 2;
        size_t minimal_steps_number = 2;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        
        {
            ReturnSyntaxNodeSP return_node;
            ISyntaxNodeSP argument;

            const Stack& s = stack;
            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
            using HandlerReturn = Handlers::HandlerReturn;
            using Impact = Handlers::Impact;

            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
            { 
               return { State::ERROR, Impact::ERROR };
            };

            handlers.return_syntax_node = [ &return_node ]( const State& state, const ReturnSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::START )
               {
                  return_node = node;
                   return { State::RETURN, Impact::MOVE };
               }
                 return { state, Impact::ERROR };
            };
            handlers.f_syntax_node = [ &argument, &lookahead ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
               }
                 return { state, Impact::ERROR };
            };
            handlers.bin_expr_syntax_node = [ &argument, &lookahead ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
               }
                 return { state, Impact::ERROR };
            };
            handlers.un_expr_syntax_node = [ &argument, &lookahead ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
               }
                 return { state, Impact::ERROR };
            };
            handlers.name_syntax_node = [ &argument, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
               }
                 return { state, Impact::ERROR };
            };
            handlers.function_call_syntax_node = [ &argument, &lookahead ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
               }
                 return { state, Impact::ERROR };
            };
            handlers.member_expression_syntax_node = [ &argument, &lookahead ]( const State& state, const MemberExpressionSyntaxNodeSP& node ) -> HandlerReturn
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                     return { State::FINISH, Impact::MOVE };
                  }
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
                plan.to_remove.nodes.push_back( return_node );
                plan.to_remove.nodes.push_back( argument );

                const auto& return_statment_node = std::make_shared< ReturnStatmentSyntaxNode >( argument, return_node->lexical_tokens().at(0) );
                plan.to_add.nodes.push_back( return_statment_node );
                plan_or_progress = plan;
            }
            else
            {
                plan_or_progress = Progress{ .readiness = iteration_result.readiness };
            }
            return plan_or_progress;
        });

     } );
  
  // RETURN_STATMENT SEMICOLON
  mProductions.emplace_back(
     []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
     {
        const size_t minimal_size = 2;
        size_t minimal_steps_number = 2;
        return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                        
        {
          ReturnStatmentSyntaxNodeSP return_statment;
          SemicolonSyntaxNodeSP semicolon;

          const Stack& s = stack;
          SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
          using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
          using HandlerReturn = Handlers::HandlerReturn;
          using Impact = Handlers::Impact;

          handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
          { 
             return { State::ERROR, Impact::ERROR };
          };
          handlers.return_statment_syntax_node = [ &return_statment ]( const State& state, const ReturnStatmentSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::START )
             {
                return_statment = node;
                return { State::RETURN_STATMENT, Impact::MOVE };
             }
             return { state, Impact::ERROR };
          };
          handlers.semicolon_syntax_node = [ &semicolon ]( const State& state, const SemicolonSyntaxNodeSP& node ) -> HandlerReturn
          {
             if( state == State::RETURN_STATMENT )
             {
                semicolon = node;
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
              plan.to_remove.nodes.push_back( return_statment );
              plan.to_remove.nodes.push_back( semicolon );

              plan.to_add.nodes.push_back( return_statment );
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

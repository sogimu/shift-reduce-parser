#pragma once

#include "i_syntax_node.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/member_expression_syntax_node.h"
#include "nonterminals/un_expr_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class While : public IGrammar
{
public:
   While()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         WHILE,
         OPEN_CIRCLE_BRACKET,
         CONDITION,
         CLOSE_CIRCLE_BRACKET,
         SCOPE_STATMENT,
         WHILE_STATMENT
      };

      // WHILE OPEN_CIRCLE_BRACKET F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL|MEMBER_EXPRESSION CLOSE_CIRCLE_BRACKET SCOPE
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 5;
            size_t minimal_steps_number = 5;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            
            {
                WhileSyntaxNodeSP while_node;
                OpenCircleBracketSyntaxNodeSP open_circle_bracket;
                ISyntaxNodeSP conditional_expression;
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
                handlers.while_syntax_node = [ &while_node ]( const State& state, const WhileSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      while_node = node;
                       return { State::WHILE, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket ]( const State& state, const OpenCircleBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::WHILE )
                   {
                      open_circle_bracket = node;
                       return { State::OPEN_CIRCLE_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.f_syntax_node = [ &conditional_expression ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.bin_expr_syntax_node = [ &conditional_expression ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.un_expr_syntax_node = [ &conditional_expression ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.name_syntax_node = [ &conditional_expression ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.function_call_syntax_node = [ &conditional_expression ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
                       return { State::CONDITION, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.member_expression_syntax_node = [ &conditional_expression ]( const State& state, const MemberExpressionSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CIRCLE_BRACKET )
                   {
                      conditional_expression = node;
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
                handlers.object_syntax_node = [ &scope_statment ]( const State& state, const ObjectSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::CLOSE_CIRCLE_BRACKET )
                   {
                       if( !node->Children().empty() )
                           return { state, Impact::ERROR };
                       scope_statment = std::make_shared< ScopeSyntaxNode >( std::vector<ISyntaxNodeSP>{}, node->lexical_tokens() );
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
                  plan.to_remove.nodes.push_back( while_node );
                  plan.to_remove.nodes.push_back( open_circle_bracket );
                  plan.to_remove.nodes.push_back( conditional_expression );
                  plan.to_remove.nodes.push_back( close_circle_bracket );
                  plan.to_remove.nodes.push_back( scope_statment );

                  const auto& while_statment_node = std::make_shared< WhileStatmentSyntaxNode >( conditional_expression, scope_statment, std::vector< LexicalTokens::LexicalToken >{ while_node->lexical_tokens().at(0) } );
                  plan.to_add.nodes.push_back( while_statment_node );
                  plan_or_progress = plan;
              }
              else
              {
                  plan_or_progress = Progress{ .readiness = iteration_result.readiness };
              }
              return plan_or_progress;
            });
         } );
      
      // WHILE_STATMENT SEMICOLON
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 2;
            size_t minimal_steps_number = 2;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            
            {
              WhileStatmentSyntaxNodeSP while_statment;
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
              handlers.while_statment_syntax_node = [ &while_statment ]( const State& state, const WhileStatmentSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::START )
                 {
                    while_statment = node;
                    return { State::WHILE_STATMENT, Impact::MOVE };
                 }
                 return { state, Impact::ERROR };
              };
              handlers.semicolon_syntax_node = [ &semicolon ]( const State& state, const SemicolonSyntaxNodeSP& node ) -> HandlerReturn
              {
                 if( state == State::WHILE_STATMENT )
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
                  plan.to_remove.nodes.push_back( while_statment );
                  plan.to_remove.nodes.push_back( semicolon );

                  plan.to_add.nodes.push_back( while_statment );
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

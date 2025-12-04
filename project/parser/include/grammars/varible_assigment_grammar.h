#pragma once

#include "nonterminals/function_call_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"

#include <vector>

class VaribleAssigment : public IGrammar
{
public:
   VaribleAssigment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         EQUAL,
         VALUE,
         SEMICOLON,
         NAME
      };

      // NAME EQUAL F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL [SEMICOLON|CLOSE_CURLY_BRACKET]
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            const size_t minimal_size = 3;
            const size_t minimal_steps_number = 3;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &minimal_steps_number, &lookahead]( size_t n )->PlanOrProgress
                                                            {
                                                            NameSyntaxNodeSP name;
                                                            EqualSyntaxNodeSP equal;
                                                            ISyntaxNodeSP value;

                                                            const Stack& s = stack;
                                                            SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                                                            using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                                                            using HandlerReturn = Handlers::HandlerReturn;
                                                            using Impact = Handlers::Impact;

                                                            handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                                                            { 
                                                               return { State::ERROR, Impact::ERROR };
                                                            };

                                                            handlers.name_syntax_node = [ &name, &value, &lookahead ]( const State& state, const NameSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::START )
                                                               {
                                                                   name = node;
                                                                   return { State::NAME, Impact::MOVE };
                                                               }
                                                               else if( state == State::EQUAL )
                                                               {
                                                                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                                   {
                                                                       value = node;
                                                                       return { State::FINISH, Impact::MOVE };
                                                                   }
                                                               }
                                                               return { state, Impact::ERROR };
                                                            };
                                                            handlers.equal_syntax_node = [ &equal ]( const State& state, const EqualSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::NAME )
                                                               {
                                                                   equal = node;
                                                                   return { State::EQUAL, Impact::MOVE };
                                                               }
                                                               return { state, Impact::ERROR };
                                                            };
                                                            handlers.f_syntax_node = [ &value, &lookahead ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::EQUAL )
                                                               {
                                                                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                                   {
                                                                       value = node;
                                                                       return { State::FINISH, Impact::MOVE };
                                                                   }
                                                               }
                                                               return { state, Impact::ERROR };
                                                            };
                                                            handlers.bin_expr_syntax_node = [ &value, &lookahead ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::EQUAL )
                                                               {
                                                                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                                   {
                                                                       value = node;
                                                                       return { State::FINISH, Impact::MOVE };
                                                                   }
                                                               }
                                                               return { state, Impact::ERROR };
                                                            };
                                                            handlers.un_expr_syntax_node = [ &value, &lookahead ]( const State& state, const UnExprSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::EQUAL )
                                                               {
                                                                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                                   {
                                                                       value = node;
                                                                       return { State::FINISH, Impact::MOVE };
                                                                   }
                                                               }
                                                               return { state, Impact::ERROR };
                                                            };
                                                            handlers.function_call_syntax_node = [ &value, &lookahead ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                                                            {
                                                               if( state == State::EQUAL )
                                                               {
                                                                   if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                                                                    check_type<CloseCurlyBracketSyntaxNode>( lookahead ) )
                                                                   {
                                                                       value = node;
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
                                                                plan.to_remove.nodes.push_back( name );
                                                                plan.to_remove.nodes.push_back( equal );
                                                                plan.to_remove.nodes.push_back( value );

                                                                const auto& varible_assigment_statment_syntax_node = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, value, equal->lexical_tokens().at(0) );
                                                                // varible_assigment_statment_syntax_node->add_back( name );
                                                                // varible_assigment_statment_syntax_node->add_back( value );
                                                                plan.to_add.nodes.push_back( varible_assigment_statment_syntax_node );
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

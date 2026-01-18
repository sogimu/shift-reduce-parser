#pragma once

#include "i_grammar.h"
#include "nonterminals/array_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/open_square_bracket_syntax_node.h"
#include "terminals/close_square_bracket_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Array : public IGrammar
{
public:
   Array()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         OPEN_SQUARE_BRACKET,
         CLOSE_SQUARE_BRACKET,
         ELEMENT,
         COMMA,
      };

      // OPEN_SQUARE_BRACKET (F COMMA?)+ CLOSE_SQUARE_BRACKET 
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            bool is_open_square_bracket_found = false;
            bool is_close_square_bracket_found = false;
            size_t distance_between_open_close_square_bracket = 0;
            
            auto it = stack.rbegin();
            SyntaxNodeEmptyVisitor::Handlers open_square_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               open_square_bracket_handler.open_square_bracket_syntax_node = [ &is_open_square_bracket_found ]( const OpenSquareBracketSyntaxNodeSP& /* node */ )
               { is_open_square_bracket_found = true; };
               const auto& open_square_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_square_bracket_handler );
               ( *it )->accept( open_square_bracket_visitor );
               if( is_open_square_bracket_found )
               {
                  distance_between_open_close_square_bracket = std::distance( stack.rbegin(), it ) + 1;
                  break;
               }
            }
            
            if( !is_open_square_bracket_found )
                return Progress{ .readiness = 0.0 };
            
            SyntaxNodeEmptyVisitor::Handlers close_square_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               close_square_bracket_handler.close_square_bracket_syntax_node = [ &is_close_square_bracket_found ]( const CloseSquareBracketSyntaxNodeSP& /* node */ )
               { is_close_square_bracket_found = true; };
               const auto& close_square_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_square_bracket_handler );
               ( *it )->accept( close_square_bracket_visitor );
               if( is_close_square_bracket_found )
               {
                  break;
               }
            }

            const size_t minimal_size = distance_between_open_close_square_bracket + 1;
            size_t minimal_steps_number = 0;
            if( is_open_square_bracket_found && !is_close_square_bracket_found )
                minimal_steps_number = minimal_size + 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &lookahead, &minimal_steps_number]( size_t n ) -> PlanOrProgress
            {
                NameSyntaxNodeSP name;
                OpenSquareBracketSyntaxNodeSP open_square_bracket;
                std::vector< ISyntaxNodeSP > elements;
                std::vector< ISyntaxNodeSP > commas;
                CloseSquareBracketSyntaxNodeSP close_square_bracket;
                
                const Stack& s = stack;
                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;

                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& ) -> HandlerReturn
                { 
                   return { State::ERROR, Impact::ERROR };
                };
                handlers.f_syntax_node = [ &elements ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_SQUARE_BRACKET || state == State::COMMA )
                   {
                      elements.emplace_back( node );
                       return { State::ELEMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.array_syntax_node = [ &elements ]( const State& state, const ArraySyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_SQUARE_BRACKET || state == State::COMMA )
                   {
                       elements.emplace_back( node );
                       return { State::ELEMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.object_syntax_node = [ &elements ]( const State& state, const ObjectSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_SQUARE_BRACKET || state == State::COMMA )
                   {
                       elements.emplace_back( node );
                       return { State::ELEMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.bin_expr_syntax_node = [ &elements ]( const State& state, const BinExprSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_SQUARE_BRACKET || state == State::COMMA )
                   {
                      elements.emplace_back( node );
                       return { State::ELEMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.function_call_syntax_node = [ &elements ]( const State& state, const FunctionCallSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_SQUARE_BRACKET || state == State::COMMA )
                   {
                      elements.emplace_back( node );
                       return { State::ELEMENT, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.comma_syntax_node = [ &commas ]( const State& state, const CommaSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::ELEMENT )
                   {
                      commas.emplace_back( node );
                       return { State::COMMA, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.open_square_bracket_syntax_node = [ &open_square_bracket ]( const State& state, const OpenSquareBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      open_square_bracket = node;
                       return { State::OPEN_SQUARE_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.close_square_bracket_syntax_node = [ &close_square_bracket, &lookahead ]( const State& state, const CloseSquareBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::ELEMENT || state == State::OPEN_SQUARE_BRACKET )
                   {
                     if( lookahead && ( check_type<SemicolonSyntaxNode>( lookahead ) || 
                                        check_type<CloseSquareBracketSyntaxNode>( lookahead ) ||
                                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) ||
                                        check_type<CommaSyntaxNode>( lookahead ) ) )
                     {
                        close_square_bracket = node;
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
                    plan.to_remove.nodes.push_back( open_square_bracket );
                    for( const auto& element : elements )
                       plan.to_remove.nodes.push_back( element );
                    for( const auto& comma : commas )
                       plan.to_remove.nodes.push_back( comma );
                    plan.to_remove.nodes.push_back( close_square_bracket );

                    std::vector< LexicalTokens::LexicalToken > lexical_tokens { 
                                                  open_square_bracket->lexical_tokens().at(0),
                                                  close_square_bracket->lexical_tokens().at(0)
                                                  };
                    const auto& array = std::make_shared< ArraySyntaxNode >( elements, lexical_tokens );
                    plan.to_add.nodes.push_back( array );
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

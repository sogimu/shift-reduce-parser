#pragma once

#include "i_grammar.h"
#include "i_syntax_node.h"
#include "nonterminals/object_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/open_square_bracket_syntax_node.h"
#include "terminals/close_square_bracket_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/colon_syntax_node.h"
#include "terminals/string_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Object : public IGrammar
{
public:
   Object()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         OPEN_CURLY_BRACKET,
         CLOSE_CURLY_BRACKET,
         VALUE,
         COMMA,
         COLON,
         STRING,
      };

      // OPEN_CURLY_BRACKET (STRING COLON F COMMA?)+ CLOSE_CURLY_BRACKET 
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            bool is_open_curly_bracket_found = false;
            bool is_close_curly_bracket_found = false;
            size_t distance_between_open_close_curly_bracket = 0;
            
            auto it = stack.rbegin();
            SyntaxNodeEmptyVisitor::Handlers open_curly_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               open_curly_bracket_handler.open_curly_bracket_syntax_node = [ &is_open_curly_bracket_found ]( const OpenCurlyBracketSyntaxNodeSP& /* node */ )
               { is_open_curly_bracket_found = true; };
               const auto& open_curly_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_curly_bracket_handler );
               ( *it )->accept( open_curly_bracket_visitor );
               if( is_open_curly_bracket_found )
               {
                  distance_between_open_close_curly_bracket = std::distance( stack.rbegin(), it ) + 1;
                  break;
               }
            }
            
            if( !is_open_curly_bracket_found )
                return Progress{ .readiness = 0.0 };
            
            SyntaxNodeEmptyVisitor::Handlers close_curly_bracket_handler;
            for( ; it != stack.rend(); ++it )
            {
               close_curly_bracket_handler.close_curly_bracket_syntax_node = [ &is_close_curly_bracket_found ]( const CloseCurlyBracketSyntaxNodeSP& /* node */ )
               { is_close_curly_bracket_found = true; };
               const auto& close_curly_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_curly_bracket_handler );
               ( *it )->accept( close_curly_bracket_visitor );
               if( is_close_curly_bracket_found )
               {
                  break;
               }
            }

            const size_t minimal_size = distance_between_open_close_curly_bracket + 1;
            size_t minimal_steps_number = 0;
            if( is_open_curly_bracket_found && !is_close_curly_bracket_found )
                minimal_steps_number = minimal_size + 1;
            return find_grammar_matching_progress(stack, minimal_size, [&stack, &lookahead, &minimal_steps_number]( size_t n ) -> PlanOrProgress
            {
                OpenCurlyBracketSyntaxNodeSP open_curly_bracket;
                std::map< std::string, ISyntaxNodeSP > node_by_key;
                std::vector< ISyntaxNodeSP > commas;
                std::vector< ISyntaxNodeSP > colons;
                std::vector< ISyntaxNodeSP > strings;
                CloseCurlyBracketSyntaxNodeSP close_curly_bracket;

                std::string last_key;
                
                const Stack& s = stack;
                SyntaxNodeProgressVisitor< State >::Handlers handlers{ minimal_steps_number, State::START};
                using Handlers = SyntaxNodeProgressVisitor<State>::Handlers;
                using HandlerReturn = Handlers::HandlerReturn;
                using Impact = Handlers::Impact;

                handlers.default_handler = []( const State& state, const ISyntaxNodeSP& node ) -> HandlerReturn
                { 
                                                   (void) node;
                   return { State::ERROR, Impact::ERROR };
                };
                handlers.open_curly_bracket_syntax_node = [ &open_curly_bracket ]( const State& state, const OpenCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::START )
                   {
                      open_curly_bracket = node;
                       return { State::OPEN_CURLY_BRACKET, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.string_syntax_node = [ &strings, &last_key ]( const State& state, const StringSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::OPEN_CURLY_BRACKET || state == State::COMMA ) 
                   {
                       last_key = node->value();
                       strings.emplace_back( node );
                       return { State::STRING, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.colon_syntax_node = [ &commas ]( const State& state, const ColonSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::STRING )
                   {
                      commas.emplace_back( node );
                       return { State::COLON, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.f_syntax_node = [ &last_key, &node_by_key ]( const State& state, const FSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::COLON )
                   {
                       node_by_key[last_key] = node;
                       return { State::VALUE, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.comma_syntax_node = [ &commas ]( const State& state, const CommaSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::VALUE )
                   {
                       commas.emplace_back( node );
                       return { State::COMMA, Impact::MOVE };
                   }
                   return { state, Impact::ERROR };
                };
                handlers.close_curly_bracket_syntax_node = [ &close_curly_bracket, &lookahead ]( const State& state, const CloseCurlyBracketSyntaxNodeSP& node ) -> HandlerReturn
                {
                   if( state == State::VALUE || state == State::OPEN_CURLY_BRACKET )
                   {
                     if( lookahead && ( check_type<SemicolonSyntaxNode>( lookahead ) || 
                                        check_type<CloseSquareBracketSyntaxNode>( lookahead ) ||
                                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) ||
                                        check_type<CommaSyntaxNode>( lookahead ) ) )
                     {
                        close_curly_bracket = node;
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
                    plan.to_remove.nodes.push_back( open_curly_bracket );
                    for( const auto& [ key, node ] : node_by_key )
                       plan.to_remove.nodes.push_back( node );
                    for( const auto& comma : commas )
                       plan.to_remove.nodes.push_back( comma );
                    for( const auto& key : strings )
                       plan.to_remove.nodes.push_back( key );
                    for( const auto& colon : colons )
                       plan.to_remove.nodes.push_back( colon );
                    plan.to_remove.nodes.push_back( close_curly_bracket );

                    std::vector< LexicalTokens::LexicalToken > lexical_tokens { 
                                                  open_curly_bracket->lexical_tokens().at(0),
                                                  close_curly_bracket->lexical_tokens().at(0)
                                                  };
                    const auto& array = std::make_shared< ObjectSyntaxNode >( node_by_key, lexical_tokens );
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

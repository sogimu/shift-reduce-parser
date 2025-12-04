#pragma once

#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/number_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <vector>

class F : public IGrammar
{
public:
   F()
   {
      enum class State
      {
         ERROR,
         START,
         FINISH,
         BOL,
         EOL,
         FIRST_MINUS,
         SECOND_MINUS,
         NUMBER,
         F,
         OPEN_CIRCLE_BRACKET,
         CLOSE_CIRCLE_BRACKET
      };

      // NUMBER [PLUS,MINUS,MULTIPLY,DIVISION,SEMICOLON,CLOSE_CIRCLE_BRACKET,COMMA,EQUAL,LESS,MORE]
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            NumberSyntaxNodeSP number;

            ProgressCounter progress_counter{1};

            State state = State::START;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
             handlers.number_syntax_node =
                [ &number, &state, &lookahead, &progress_counter ]( const NumberSyntaxNodeSP& node )
             {
                if( state == State::START )
                {
                   state = State::NUMBER;

                   if( lookahead && ( 
                        check_type<SemicolonSyntaxNode>( lookahead ) || 
                        check_type<MinusSyntaxNode>( lookahead ) || 
                        check_type<PlusSyntaxNode>( lookahead ) || 
                        check_type<AsteriskSyntaxNode>( lookahead ) || 
                        check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) || 
                        check_type<SlashSyntaxNode>( lookahead ) || 
                        check_type<CommaSyntaxNode>( lookahead ) ||
                        check_type<EqualSyntaxNode>( lookahead ) ||
                        check_type<LessSyntaxNode>( lookahead ) ||
                        check_type<MoreSyntaxNode>( lookahead ) ) )
                   {
                     number = node;
                     progress_counter.Step();
                     state = State::FINISH;
                   }
                }
             };

            iterate_over_last_n_nodes( stack, 1, handlers );
            if( state != State::FINISH )
               return Progress{ .readiness = progress_counter.Status() };

            Plan plan;
            plan.to_remove.nodes.push_back( number );

            const auto& f_node = std::make_shared< FSyntaxNode >( number );
            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );
   }
};

#pragma once

#include <vector>

#include "i_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/double_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

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
         DOUBLE,
         INT,
         F,
         OPEN_CIRCLE_BRACKET,
         CLOSE_CIRCLE_BRACKET
      };

      // DOUBLE|INT [PLUS,MINUS,MULTIPLY,DIVISION,SEMICOLON,CLOSE_CIRCLE_BRACKET,COMMA,EQUAL,LESS,MORE]
      mProductions.emplace_back(
         []( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> PlanOrProgress
         {
            ISyntaxNodeSP number;
            FSyntaxNodeSP f_node;

            ProgressCounter progress_counter{1};

            State state = State::START;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.double_syntax_node =
                [ &f_node, &number, &state, &lookahead, &progress_counter ]( const DoubleSyntaxNodeSP& node )
             {
                if( state == State::START )
                {
                   state = State::DOUBLE;

                   if( lookahead && ( 
                        check_type<SemicolonSyntaxNode>( lookahead ) || 
                        check_type<MinusSyntaxNode>( lookahead ) || 
                        check_type<PlusSyntaxNode>( lookahead ) || 
                        check_type<AsteriskSyntaxNode>( lookahead ) || 
                        check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseSquareBracketSyntaxNode>( lookahead ) || 
                        check_type<SlashSyntaxNode>( lookahead ) || 
                        check_type<CommaSyntaxNode>( lookahead ) ||
                        check_type<EqualSyntaxNode>( lookahead ) ||
                        check_type<LessSyntaxNode>( lookahead ) ||
                        check_type<MoreSyntaxNode>( lookahead ) ) )
                   {
                     number = node;
                     f_node = std::make_shared< FSyntaxNode >( node );
                     progress_counter.Step();
                     state = State::FINISH;
                   }
                }
             };
             handlers.int_syntax_node =
                [ &f_node, &number, &state, &lookahead, &progress_counter ]( const IntSyntaxNodeSP& node )
             {
                if( state == State::START )
                {
                   state = State::INT;

                   if( lookahead && ( 
                        check_type<SemicolonSyntaxNode>( lookahead ) || 
                        check_type<MinusSyntaxNode>( lookahead ) || 
                        check_type<PlusSyntaxNode>( lookahead ) || 
                        check_type<AsteriskSyntaxNode>( lookahead ) || 
                        check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseSquareBracketSyntaxNode>( lookahead ) || 
                        check_type<SlashSyntaxNode>( lookahead ) || 
                        check_type<CommaSyntaxNode>( lookahead ) ||
                        check_type<EqualSyntaxNode>( lookahead ) ||
                        check_type<LessSyntaxNode>( lookahead ) ||
                        check_type<MoreSyntaxNode>( lookahead ) ) )
                   {
                     number = node;
                     f_node = std::make_shared< FSyntaxNode >( node );
                     progress_counter.Step();
                     state = State::FINISH;
                   }
                }
             };
             handlers.string_syntax_node =
                [ &f_node, &number, &state, &lookahead, &progress_counter ]( const StringSyntaxNodeSP& node )
             {
                if( state == State::START )
                {
                   state = State::INT;

                   if( lookahead && ( 
                        check_type<SemicolonSyntaxNode>( lookahead ) || 
                        check_type<MinusSyntaxNode>( lookahead ) || 
                        check_type<PlusSyntaxNode>( lookahead ) || 
                        check_type<AsteriskSyntaxNode>( lookahead ) || 
                        check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseCurlyBracketSyntaxNode>( lookahead ) || 
                        check_type<CloseSquareBracketSyntaxNode>( lookahead ) || 
                        check_type<SlashSyntaxNode>( lookahead ) || 
                        check_type<CommaSyntaxNode>( lookahead ) ||
                        check_type<EqualSyntaxNode>( lookahead ) ||
                        check_type<LessSyntaxNode>( lookahead ) ||
                        check_type<MoreSyntaxNode>( lookahead ) ) )
                   {
                     number = node;
                     f_node = std::make_shared< FSyntaxNode >( node );
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

            plan.to_add.nodes.push_back( f_node );
            return plan;
         } );
   }
};

#pragma once

#include "nonterminals/expression_syntax_node.h"
#include "i_grammar.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <vector>

class Scope : public IGrammar
{
public:
   Scope()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         BOL,
         EOL,
         OPEN_CURLY_BRACKET,
         EXPRESSION,
         CLOSE_CURLY_BRACKET,
         SCOPE
      };

      // OPEN_CURLY_BRACKET EXPRESSION+ CLOSE_CURLY_BRACKET
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            OpenCurlyBracketSyntaxNodeSP open_curly_bracket;
            std::vector< ISyntaxNodeSP > expressions;
            CloseCurlyBracketSyntaxNodeSP close_curly_bracket;

            bool is_open_curly_bracket_found = false;
            bool is_close_curly_bracket_found = false;
            size_t distance_between_open_close_curly_bracket = 0;

            SyntaxNodeEmptyVisitor::Handlers close_curly_bracket_handler;
            close_curly_bracket_handler.close_curly_bracket_syntax_node =
               [ &is_close_curly_bracket_found, &is_open_curly_bracket_found, &distance_between_open_close_curly_bracket,
                 &stack ]( const CloseCurlyBracketSyntaxNodeSP& node ) { is_close_curly_bracket_found = true; };
            const auto& close_curly_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( close_curly_bracket_handler );
            ( *stack.rbegin() )->accept( close_curly_bracket_visitor );

            if( !is_close_curly_bracket_found )
               return {};

            SyntaxNodeEmptyVisitor::Handlers open_curly_bracket_handler;
            for( auto it = stack.rbegin(); it != stack.rend(); ++it )
            {
               open_curly_bracket_handler.open_curly_bracket_syntax_node = [ &is_open_curly_bracket_found ]( const OpenCurlyBracketSyntaxNodeSP& node )
               { is_open_curly_bracket_found = true; };
               const auto& open_curly_bracket_visitor = std::make_shared< SyntaxNodeEmptyVisitor >( open_curly_bracket_handler );
               ( *it )->accept( open_curly_bracket_visitor );
               if( is_open_curly_bracket_found )
               {
                  distance_between_open_close_curly_bracket = std::distance( stack.rbegin(), it ) + 1;
                  break;
               }
            }

            if( !is_open_curly_bracket_found || !is_close_curly_bracket_found )
               return {};

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.open_curly_bracket_syntax_node = [ &open_curly_bracket, &state ]( const OpenCurlyBracketSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  open_curly_bracket = node;
                  state = State::OPEN_CURLY_BRACKET;
               }
            };
            handlers.expression_syntax_node = [ &expressions, &state ]( const ExpressionSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CURLY_BRACKET )
               {
                  expressions.emplace_back( node );
                  state = State::EXPRESSION;
               }
               else if( state == State::EXPRESSION )
               {
                  expressions.emplace_back( node );
                  state = State::EXPRESSION;
               }
               else if( state == State::SCOPE )
               {
                  expressions.emplace_back( node );
                  state = State::EXPRESSION;
               }
            };
            handlers.scope_syntax_node = [ &expressions, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CURLY_BRACKET )
               {
                  expressions.emplace_back( node );
                  state = State::EXPRESSION;
               }
               else if( state == State::EXPRESSION )
               {
                  expressions.emplace_back( node );
                  state = State::SCOPE;
               }
               else if( state == State::SCOPE )
               {
                  expressions.emplace_back( node );
                  state = State::SCOPE;
               }
            };

            handlers.close_curly_bracket_syntax_node = [ &close_curly_bracket, &state ]( const CloseCurlyBracketSyntaxNodeSP& node )
            {
               if( state == State::EXPRESSION )
               {
                  close_curly_bracket = node;
                  state = State::FINISH;
               }
               else if( state == State::SCOPE )
               {
                  close_curly_bracket = node;
                  state = State::FINISH;
               }
               else if( state == State::OPEN_CURLY_BRACKET )
               {
                  close_curly_bracket = node;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, distance_between_open_close_curly_bracket, handlers );

            if( state != State::FINISH )
               return {};

            std::reverse( expressions.begin(), expressions.end() );

            Plan plan;
            plan.to_remove.nodes.push_back( open_curly_bracket );
            for( const auto& expression : expressions )
               plan.to_remove.nodes.push_back( expression );
            plan.to_remove.nodes.push_back( close_curly_bracket );

            const auto& scope_node = std::make_shared< ScopeSyntaxNode >( expressions );
            plan.to_add.nodes.push_back( scope_node );
            return plan;
         } );

      // BOL SCOPE EOL
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            BolSyntaxNodeSP bol;
            ScopeSyntaxNodeSP scope;
            EolSyntaxNodeSP eol;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.bol_syntax_node = [ &bol, &state ]( const BolSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  bol = node;
                  state = State::BOL;
               }
            };
            handlers.scope_syntax_node = [ &scope, &state ]( const ScopeSyntaxNodeSP& node )
            {
               if( state == State::BOL )
               {
                  scope = node;
                  state = State::SCOPE;
               }
            };
            handlers.eol_syntax_node = [ &eol, &state ]( const EolSyntaxNodeSP& node )
            {
               if( state == State::SCOPE )
               {
                  eol = node;
                  state = State::EOL;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( bol );
            plan.to_remove.nodes.push_back( scope );
            plan.to_remove.nodes.push_back( eol );

            plan.to_add.nodes.push_back( scope );
            return plan;
         } );

      // BOL EXPRESSION EOL
      mProductions.emplace_back(
         [ this ]( const Stack& stack ) -> std::optional< Plan >
         {
            BolSyntaxNodeSP bol;
            ExpressionSyntaxNodeSP expression;
            EolSyntaxNodeSP eol;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.bol_syntax_node = [ &bol, &state ]( const BolSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  bol = node;
                  state = State::BOL;
               }
            };
            handlers.expression_syntax_node = [ &expression, &state ]( const ExpressionSyntaxNodeSP& node )
            {
               if( state == State::BOL )
               {
                  expression = node;
                  state = State::EXPRESSION;
               }
            };
            handlers.eol_syntax_node = [ &eol, &state ]( const EolSyntaxNodeSP& node )
            {
               if( state == State::EXPRESSION )
               {
                  eol = node;
                  state = State::EOL;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( bol );
            plan.to_remove.nodes.push_back( expression );
            plan.to_remove.nodes.push_back( eol );

            std::vector< ISyntaxNodeSP > expressions{ expression };
            const auto& scope_node = std::make_shared< ScopeSyntaxNode >( expressions );
            plan.to_add.nodes.push_back( scope_node );
            return plan;
         } );
   }
};

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

      // PRINT OPEN_CIRCLE_BRACKET COMPUTATIONAL_EXPRESSION|CONDITIONAL_EXPRESSION|FUNCTION_CALL_OR_DEFINITION CLOSE_CIRCLE_BRACKET SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            PrintSyntaxNodeSP print;
            OpenCircleBracketSyntaxNodeSP open;
            ISyntaxNodeSP argument;
            CloseCircleBracketSyntaxNodeSP close;
            SemicolonSyntaxNodeSP semiclon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.print_syntax_node = [ &print, &state ]( const PrintSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::PRINT;
                  print = node;
               }
            };
            handlers.open_circle_bracket_syntax_node = [ &open, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::PRINT )
               {
                  state = State::OPEN_CIRCLE_BRACKET;
                  open = node;
               }
            };
            handlers.name_syntax_node = [ &argument, &state ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  state = State::ARGUMENT;
                  argument = node;
               }
            };
            handlers.f_syntax_node = [ &argument, &state ]( const FSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  argument = node;
                  state = State::ARGUMENT;
               }
            };
            handlers.bin_expr_syntax_node = [ &argument, &state ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  argument = node;
                  state = State::ARGUMENT;
               }
            };
            handlers.un_expr_syntax_node = [ &argument, &state ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  argument = node;
                  state = State::ARGUMENT;
               }
            };
            handlers.function_call_syntax_node = [ &argument, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::OPEN_CIRCLE_BRACKET )
               {
                  state = State::ARGUMENT;
                  argument = node;
               }
            };
            handlers.close_circle_bracket_syntax_node = [ &close, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
            {
               if( state == State::ARGUMENT )
               {
                  state = State::CLOSE_CIRCLE_BRACKET;
                  state = State::FINISH;
                  close = node;
               }
            };

            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( print );
            plan.to_remove.nodes.push_back( open );
            plan.to_remove.nodes.push_back( argument );
            plan.to_remove.nodes.push_back( close );

            const auto& print_statment_node = std::make_shared< PrintStatmentSyntaxNode >( argument );
            plan.to_add.nodes.push_back( print_statment_node );
            return plan;
         } );
   }
};

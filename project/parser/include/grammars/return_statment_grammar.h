#pragma once

#include "terminals/return_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "utils.h"

#include <memory>
#include <vector>

class ISyntaxNodeVisitor;

class Return : public IGrammar
{
public:
   Return()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         RETURN,
         ARGUMENT,
         SEMICOLON,
      };

      // RETURN F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL [SEMICOLON]
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ReturnSyntaxNodeSP return_node;
            ISyntaxNodeSP argument;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.return_syntax_node = [ &return_node, &state ]( const ReturnSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  state = State::RETURN;
                  return_node = node;
               }
            };
            handlers.f_syntax_node = [ &argument, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                      state = State::ARGUMENT;
                      state = State::FINISH;
                  }
               }
            };
            handlers.bin_expr_syntax_node = [ &argument, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                      state = State::ARGUMENT;
                      state = State::FINISH;
                  }
               }
            };
            handlers.un_expr_syntax_node = [ &argument, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                      state = State::ARGUMENT;
                      state = State::FINISH;
                  }
               }
            };
            handlers.name_syntax_node = [ &argument, &state, &lookahead ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                      state = State::ARGUMENT;
                      state = State::FINISH;
                  }
               }
            };
            handlers.function_call_syntax_node = [ &argument, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::RETURN )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ) 
                  {
                      argument = node;
                      state = State::ARGUMENT;
                      state = State::FINISH;
                  }
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( return_node );
            plan.to_remove.nodes.push_back( argument );

            const auto& return_statment_node = std::make_shared< ReturnStatmentSyntaxNode >( argument );
            plan.to_add.nodes.push_back( return_statment_node );
            return plan;
         } );
   }
};

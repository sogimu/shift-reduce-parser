#pragma once

#include "nonterminals/statment_syntax_node.h"
#include "i_grammar.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/semicolon_syntax_node.h"
#include "utils.h"

class Statment : public IGrammar
{
public:
   Statment()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         F,
         CONDITIONAL_EXPRESSION,
         IF_STATMENT,
         WHILE_STATMENT,
         FUNCTION_STATMENT,
         FUNCTION_CALL,
         PRINT_STATMENT,
         VARIBLE_ASSIGMENT_STATMENT,
         EQUAL,
         SEMICOLON,
         RETURN_STATMENT,
         CLOSE_CURLY_BRACKET,
         BOL,
         EOL,
         STATMENT
      };

      // IF_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            IfStatmentSyntaxNodeSP if_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.if_statment_syntax_node = [ &if_statment_syntax_node, &state, &lookahead ]( const IfStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if_statment_syntax_node = node;
                  state = State::IF_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( if_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( if_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );
      

      // WHILE_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            WhileStatmentSyntaxNodeSP while_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.while_statment_syntax_node = [ &while_statment_syntax_node, &state ]( const WhileStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  while_statment_syntax_node = node;
                  state = State::WHILE_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( while_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( while_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // FUNCTION_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            FunctionStatmentSyntaxNodeSP function_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_statment_syntax_node = [ &function_syntax_node, &state ]( const FunctionStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function_syntax_node = node;
                  state = State::FUNCTION_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( function_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // FUNCTION_CALL
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            FunctionCallSyntaxNodeSP function_call_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.function_call_syntax_node = [ &function_call_syntax_node, &state ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  function_call_syntax_node = node;
                  state = State::FUNCTION_CALL;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( function_call_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( function_call_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // PRINT_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            PrintStatmentSyntaxNodeSP print_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.print_statment_syntax_node = [ &print_statment_syntax_node, &state ]( const PrintStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  print_statment_syntax_node = node;
                  state = State::PRINT_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( print_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( print_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // RETURN_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ReturnStatmentSyntaxNodeSP return_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.return_statment_syntax_node = [ &return_statment_syntax_node, &state ]( const ReturnStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  return_statment_syntax_node = node;
                  state = State::RETURN_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( return_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( return_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // F|BIN_EXPR|UN_EXPR|NAME [SEMICOLON, CLOSE_CURLY_BRACKET]
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP f;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &f, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ||
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) )
                  {
                      f = node;
                      state = State::F;
                      state = State::FINISH;
                  }
               }
            };
            handlers.bin_expr_syntax_node = [ &f, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ||
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) ) 
                 {
                     f = node;
                     state = State::F;
                     state = State::FINISH;
                 }
               }
            };
            handlers.un_expr_syntax_node = [ &f, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ||
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) ) 
                   {
                       f = node;
                       state = State::F;
                       state = State::FINISH;
                   }
               }
            };
            handlers.name_syntax_node = [ &f, &state, &lookahead ]( const NameSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ||
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) ) 
                  {
                      f = node;
                      state = State::F;
                      state = State::FINISH;
                  }
               }
            };
            handlers.function_call_syntax_node = [ &f, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) ||
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) ) 
                  {
                      f = node;
                      state = State::F;
                      state = State::FINISH;
                  }
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( f );

            const auto& expression_node = std::make_shared< StatmentSyntaxNode >();
            expression_node->add_back(f);
            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // VARIBLE_ASSIGMENT_STATMENT
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            VaribleAssigmentStatmentSyntaxNodeSP varible_assigment_statment_syntax_node;

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.varible_assigment_statment_syntax_node = [ &varible_assigment_statment_syntax_node, &state ]( const VaribleAssigmentStatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  varible_assigment_statment_syntax_node = node;
                  state = State::VARIBLE_ASSIGMENT_STATMENT;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( varible_assigment_statment_syntax_node );

            const auto& expression_syntax_node = std::make_shared< StatmentSyntaxNode >( varible_assigment_statment_syntax_node );
            plan.to_add.nodes.push_back( expression_syntax_node );
            return plan;
         } );

      // STATMENT SEMICOLON
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            StatmentSyntaxNodeSP statment;
            SemicolonSyntaxNodeSP semicolon;    

            State state = State::START;

            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.statment_syntax_node = [ &statment, &state ]( const StatmentSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  statment = node;
                  state = State::STATMENT;
               }
            };
            
            handlers.semicolon_syntax_node = [ &semicolon, &state ]( const SemicolonSyntaxNodeSP& node )
            {
               if( state == State::STATMENT )
               {
                  semicolon = node;
                  state = State::SEMICOLON;
                  state = State::FINISH;
               }
            };

            iterate_over_last_n_nodes( stack, 2, handlers );

            if( state != State::FINISH )
               return {};

            Plan plan;
            plan.to_remove.nodes.push_back( statment );
            plan.to_remove.nodes.push_back( semicolon );

            plan.to_add.nodes.push_back( statment );
            return plan;
         } );

      // BOL STATMENT EOL
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            BolSyntaxNodeSP bol;
            StatmentSyntaxNodeSP expression;
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
            handlers.statment_syntax_node = [ &expression, &state ]( const StatmentSyntaxNodeSP& node )
            {
               if( state == State::BOL )
               {
                  expression = node;
                  state = State::STATMENT;
               }
            };
            handlers.eol_syntax_node = [ &eol, &state ]( const EolSyntaxNodeSP& node )
            {
               if( state == State::STATMENT )
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

            // const auto& scope_node = std::make_shared< ScopeSyntaxNode >( expressions );
            plan.to_add.nodes.push_back( expression );
            return plan;
         } );
   }
};

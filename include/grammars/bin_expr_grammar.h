#pragma once

#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <memory>
#include <vector>

class BinExpr : public IGrammar
{
public:
   BinExpr()
   {
      enum class State
      {
         START,
         FINISH,
         ERROR,
         ADDITION,
         SUBTRACTION,
         MULTIPLY,
         DIVISION,
         PLUS,
         MINUS,
         F,
         BIN_EXPR,
         UN_EXPR,
         EQUAL_EXPRESSION0,
         EQUAL_EXPRESSION1,
         OPEN_CIRCLE_BRACKET,
         NAME,
         CLOSE_CIRCLE_BRACKET,
      };
      
      // F|BIN_EXPR|UN_EXPR +|-|*|/ F|BIN_EXPR|UN_EXPR 
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP a;
            ISyntaxNodeSP operation;
            ISyntaxNodeSP b;
            BinExprSyntaxNode::Type operation_type; 

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& node ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::PLUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Addition;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MINUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Substruction;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MULTIPLY )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Multiply;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::DIVISION )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Division;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
            };
            handlers.bin_expr_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::PLUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Addition;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead )  || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ))
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MINUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Substruction;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead )  || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ))
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MULTIPLY )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Multiply;
                  if( lookahead && ( check_type< SemicolonSyntaxNode >( lookahead )  || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::DIVISION )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Division;
                  if( lookahead && ( check_type< SemicolonSyntaxNode >( lookahead )  || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) ) )
                  {
                    state = State::FINISH;
                  }
               }
            };
            handlers.un_expr_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::PLUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Addition;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MINUS )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Substruction;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::MULTIPLY )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Multiply;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
               else if( state == State::DIVISION )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Division;
                  if( lookahead && check_type< SemicolonSyntaxNode >( lookahead ) || 
                                   check_type<CloseCircleBracketSyntaxNode>( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
            };
            handlers.plus_syntax_node = [ &operation, &state, &operation_type ]( const PlusSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  operation = node;
                  state = State::PLUS;
               }
            };
            handlers.minus_syntax_node = [ &operation, &state, &operation_type ]( const MinusSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  operation = node;
                  state = State::MINUS;
               }
            };
            handlers.asterisk_syntax_node = [ &operation, &state, &operation_type ]( const AsteriskSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  operation = node;
                  state = State::MULTIPLY;
               }
            };
            handlers.slash_syntax_node = [ &operation, &state, &operation_type ]( const SlashSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  operation = node;
                  state = State::DIVISION;
               }
            };
            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( a );
            plan.to_remove.nodes.push_back( operation );
            plan.to_remove.nodes.push_back( b );

            const auto& expression_node = std::make_shared< BinExprSyntaxNode >(operation_type, a, b );

            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // F|BIN_EXPR|UN_EXPR == F|BIN_EXPR|UN_EXPR 
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP a;
            EqualSyntaxNodeSP equal0;
            EqualSyntaxNodeSP equal1;
            ISyntaxNodeSP b;
            BinExprSyntaxNode::Type operation_type; 

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& node ) { state = State::ERROR; };
            handlers.f_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::EQUAL_EXPRESSION1 )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Equality;
                  state = State::FINISH;
               }
            };
            handlers.bin_expr_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::EQUAL_EXPRESSION1 )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Equality;
                  state = State::FINISH;
               }
            };
            handlers.un_expr_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                  a = node;
                  state = State::F;
               }
               else if( state == State::EQUAL_EXPRESSION1 )
               {
                  b = node;
                  state = State::F;
                  operation_type = BinExprSyntaxNode::Type::Equality;
                  state = State::FINISH;
               }
            };
            handlers.equal_syntax_node = [ &equal0, &equal1, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  equal0 = node;
                  state = State::EQUAL_EXPRESSION0;
               }
               else if( state == State::EQUAL_EXPRESSION0 )
               {
                  equal1 = node;
                  state = State::EQUAL_EXPRESSION1;
               }
            };
            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( a );
            plan.to_remove.nodes.push_back( equal0 );
            plan.to_remove.nodes.push_back( equal1 );
            plan.to_remove.nodes.push_back( b );

            const auto& expression_node = std::make_shared< BinExprSyntaxNode >(operation_type, a, b );

            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );
      // // OPEN_CIRCLE_BRACKET BIN_EXPR CLOSE_CIRCLE_BRACKET
      // mProductions.emplace_back(
      //    [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
      //    {
      //       OpenCircleBracketSyntaxNodeSP open_circle_bracket;
      //       ISyntaxNodeSP expression;
      //       CloseCircleBracketSyntaxNodeSP close_circle_bracket;
      //
      //       State state = State::START;
      //
      //       Plan plan;
      //       SyntaxNodeEmptyVisitor::Handlers handlers;
      //       handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
      //       handlers.open_circle_bracket_syntax_node = [ &open_circle_bracket, &state ]( const OpenCircleBracketSyntaxNodeSP& node )
      //       {
      //          if( state == State::START )
      //          {
      //             open_circle_bracket = node;
      //             state = State::OPEN_CIRCLE_BRACKET;
      //          }
      //       };
      //       handlers.bin_expr_syntax_node = [ &expression, &state ]( const BinExprSyntaxNodeSP& node )
      //       {
      //          if( state == State::OPEN_CIRCLE_BRACKET )
      //          {
      //             expression = node;
      //             state = State::BIN_EXPR;
      //          }
      //       };
      //       handlers.close_circle_bracket_syntax_node = [ &close_circle_bracket, &state ]( const CloseCircleBracketSyntaxNodeSP& node )
      //       {
      //          if( state == State::BIN_EXPR )
      //          {
      //             close_circle_bracket = node;
      //             state = State::FINISH;
      //          }
      //       };
      //       iterate_over_last_n_nodes( stack, 3, handlers );
      //
      //       if( state != State::FINISH )
      //          return {};
      //
      //       plan.to_remove.nodes.push_back( open_circle_bracket );
      //       plan.to_remove.nodes.push_back( expression );
      //       plan.to_remove.nodes.push_back( close_circle_bracket );
      //
      //       plan.to_add.nodes.push_back( expression );
      //       return plan;
      //    } );


   }
};

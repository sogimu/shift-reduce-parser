#pragma once

#include "terminals/equal_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

#include <memory>
#include <vector>

class ComputationalExpression : public IGrammar
{
public:
   ComputationalExpression()
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
         BIN_OP,
         OPEN_CIRCLE_BRACKET,
         NAME,
         CLOSE_CIRCLE_BRACKET,
      };

      // mProductions.emplace_back(
      //    [ /* this */ ]( const Stack& stack ) -> std::optional< Plan >
      //    {
      //       auto start_it = stack.end();
      //       for( auto it = stack.rbegin(); it != stack.rend(); ++it )
      //       {
      //          if( !is_argument_or_operation( *it ) )
      //             break;
      //          start_it = it.base() - 1;
      //       }
      //
      //       std::stack< ISyntaxNodeSP > operations;
      //       std::stack< ISyntaxNodeSP > arguments;
      //
      //       for( auto it = start_it; it != stack.end(); ++it )
      //       {
      //          const auto& node = *it;
      //          if( is_argument( node ) )
      //          {
      //             arguments.push( node );
      //          }
      //          else if( is_operation( node ) )
      //          {
      //             int current_op = operation_weight( node );
      //             int prev_op = -1;
      //             ISyntaxNodeSP prev_operation;
      //             if( !operations.empty() )
      //             {
      //                prev_operation = operations.top();
      //                prev_op = operation_weight( prev_operation );
      //             }
      //
      //             if( current_op < prev_op )
      //             {
      //                std::optional< Plan > plan_opt;
      //                SyntaxNodeEmptyVisitor::Handlers handlers;
      //                handlers.plus_syntax_node = [ &node, &plan_opt, &arguments ]( const PlusSyntaxNodeSP& prev_operation )
      //                {
      //                   const auto& f0 = arguments.top();
      //                   arguments.pop();
      //                   const auto& f1 = arguments.top();
      //                   arguments.pop();
      //
      //                   Plan plan;
      //                   plan.to_remove.nodes.push_back( f0 );
      //                   plan.to_remove.nodes.push_back( prev_operation );
      //                   plan.to_remove.nodes.push_back( f1 );
      //                   plan.to_remove.nodes.push_back( node );
      //
      //                   const auto& addition_node = std::make_shared< AdditionSyntaxNode >();
      //                   addition_node->add_back( f0 );
      //                   addition_node->add_back( f1 );
      //                   const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
      //                   expression_node->add_back( addition_node );
      //                   plan.to_add.nodes.push_back( expression_node );
      //                   plan.to_add.nodes.push_back( node );
      //                   plan_opt = plan;
      //                };
      //                handlers.minus_syntax_node = [ &node, &plan_opt, &arguments ]( const MinusSyntaxNodeSP& prev_operation )
      //                {
      //                   const auto& f0 = arguments.top();
      //                   arguments.pop();
      //                   const auto& f1 = arguments.top();
      //                   arguments.pop();
      //
      //                   Plan plan;
      //                   plan.to_remove.nodes.push_back( f0 );
      //                   plan.to_remove.nodes.push_back( prev_operation );
      //                   plan.to_remove.nodes.push_back( f1 );
      //                   plan.to_remove.nodes.push_back( node );
      //
      //                   const auto& subtraction_node = std::make_shared< SubtractionSyntaxNode >();
      //                   subtraction_node->add_back( f1 );
      //                   subtraction_node->add_back( f0 );
      //                   const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
      //                   expression_node->add_back( subtraction_node );
      //                   plan.to_add.nodes.push_back( expression_node );
      //                   plan.to_add.nodes.push_back( node );
      //                   plan_opt = plan;
      //                };
      //                handlers.asterisk_syntax_node = [ &node, &plan_opt, &arguments ]( const AsteriskSyntaxNodeSP& prev_operation )
      //                {
      //                   const auto& f0 = arguments.top();
      //                   arguments.pop();
      //                   const auto& f1 = arguments.top();
      //                   arguments.pop();
      //
      //                   Plan plan;
      //                   plan.to_remove.nodes.push_back( f0 );
      //                   plan.to_remove.nodes.push_back( prev_operation );
      //                   plan.to_remove.nodes.push_back( f1 );
      //                   plan.to_remove.nodes.push_back( node );
      //
      //                   const auto& multiply_node = std::make_shared< MultiplySyntaxNode >();
      //                   multiply_node->add_back( f0 );
      //                   multiply_node->add_back( f1 );
      //                   const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
      //                   expression_node->add_back( multiply_node );
      //                   plan.to_add.nodes.push_back( expression_node );
      //                   plan.to_add.nodes.push_back( node );
      //                   plan_opt = plan;
      //                };
      //                handlers.slash_syntax_node = [ &node, &plan_opt, &arguments ]( const SlashSyntaxNodeSP& prev_operation )
      //                {
      //                   const auto& f0 = arguments.top();
      //                   arguments.pop();
      //                   const auto& f1 = arguments.top();
      //                   arguments.pop();
      //
      //                   Plan plan;
      //                   plan.to_remove.nodes.push_back( f0 );
      //                   plan.to_remove.nodes.push_back( prev_operation );
      //                   plan.to_remove.nodes.push_back( f1 );
      //                   plan.to_remove.nodes.push_back( node );
      //
      //                   const auto& division_node = std::make_shared< DivisionSyntaxNode >();
      //                   division_node->add_back( f1 );
      //                   division_node->add_back( f0 );
      //                   const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
      //                   expression_node->add_back( division_node );
      //                   plan.to_add.nodes.push_back( expression_node );
      //                   plan.to_add.nodes.push_back( node );
      //                   plan_opt = plan;
      //                };
      //                const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
      //                prev_operation->accept( visitor );
      //                return plan_opt;
      //             }
      //             else if( current_op >= prev_op )
      //             {
      //                operations.push( node );
      //             }
      //          }
      //       }
      //
      //       return {};
      //    } );
   
      // BinExpr|UnExpr|F [SEMICOLON,EQUAL,CLOSE_CIRCLE_BRACKET] 
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP expression;
            SemicolonSyntaxNodeSP semicolon;

            State state = State::START;

            Plan plan;
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.default_handler = [ &state ]( const ISyntaxNodeSP& ) { state = State::ERROR; };
            handlers.bin_expr_syntax_node = [ &expression, &state, &lookahead ]( const BinExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                 if( lookahead && check_type<SemicolonSyntaxNode>( lookahead )  || 
                                  check_type<EqualSyntaxNode>( lookahead ))
                 {
                      expression = node;
                      // semicolon = node;
                      state = State::FINISH;
                  }
                  // state = State::F;
               }
            };
            handlers.un_expr_syntax_node = [ &expression, &state, &lookahead ]( const UnExprSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                 if( lookahead && check_type<SemicolonSyntaxNode>( lookahead )  || 
                                  check_type<EqualSyntaxNode>( lookahead ))
                 {
                      expression = node;
                      // semicolon = node;
                      state = State::FINISH;
                  }
                  // state = State::F;
               }
            };
            handlers.f_syntax_node = [ &expression, &state, &lookahead ]( const FSyntaxNodeSP& node )
            {
               if( state == State::START )
               {
                 if( lookahead && check_type<SemicolonSyntaxNode>( lookahead ) || 
                                  check_type<EqualSyntaxNode>( lookahead ) ||
                                  check_type<CloseCircleBracketSyntaxNode>( lookahead ) )
                 {
                      expression = node;
                      // semicolon = node;
                      state = State::FINISH;
                  }
                  // state = State::F;
               }
            };
            iterate_over_last_n_nodes( stack, 1, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( expression );
            // plan.to_remove.nodes.push_back( semicolon );

            const auto& expression_node = std::make_shared< ComputationalExpressionSyntaxNode >();
            expression_node->add_back( expression );
            plan.to_add.nodes.push_back( expression_node );
            // plan.to_add.nodes.push_back( semicolon );
            return plan;
         } );
   }
};

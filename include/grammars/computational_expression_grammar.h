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

#pragma once

#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/close_curly_bracket_syntax_node.h"
#include "terminals/comma_syntax_node.h"
#include "terminals/less_syntax_node.h"
#include "terminals/minus_syntax_node.h"
#include "terminals/more_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/plus_syntax_node.h"
#include "terminals/slash_syntax_node.h"
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
         EQUAL_EXPRESSION,
         MORE,
         MORE_EQUAL,
         LESS,
         LESS_EQUAL,
         OPEN_CIRCLE_BRACKET,
         NAME,
         CLOSE_CIRCLE_BRACKET,
      };
      
      // F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL +|-|*|/ F|BIN_EXPR|UN_EXPR|NAME|FUNCTION_CALL [SEMICOLON|CLOSE_CIRCLE_BRACKET,BIN_EXPR,COMMA,EQUAL] 
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ))
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ))
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ))
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< BinExprSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
            };
            handlers.name_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const NameSyntaxNodeSP& node )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
                  {
                    state = State::FINISH;
                  }
               }
            };
            handlers.function_call_syntax_node = [ &operation_type, &a, &b, &state, &lookahead ]( const FunctionCallSyntaxNodeSP& node )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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
                                   check_type< CloseCircleBracketSyntaxNode >( lookahead ) || 
                                   check_type< CloseCurlyBracketSyntaxNode >( lookahead ) || 
                                   check_type< PlusSyntaxNode >( lookahead ) || 
                                   check_type< MinusSyntaxNode >( lookahead ) || 
                                   check_type< CommaSyntaxNode >( lookahead ) || 
                                   check_type< EqualSyntaxNode >( lookahead ) || 
                                   check_type< LessSyntaxNode >( lookahead ) || 
                                   check_type< MoreSyntaxNode >( lookahead ) )
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

      // F|BIN_EXPR|UN_EXPR EQUAL EQUAL|LESS EQUAL|MORE EQUAL F|BIN_EXPR|UN_EXPR[!PLUS&&!MINUS&&!ASTERIX&&!SLASH] 
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP a;
            EqualSyntaxNodeSP equal0;
            EqualSyntaxNodeSP equal1;
            MoreSyntaxNodeSP more;
            LessSyntaxNodeSP less;
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
               else if( state == State::EQUAL_EXPRESSION )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Equal;
                    state = State::FINISH;
                  }
               }
               else if( state == State::MORE_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::MoreEqual;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::LessEqual;
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
               else if( state == State::EQUAL_EXPRESSION )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Equal;
                    state = State::FINISH;
                  }
               }
               else if( state == State::MORE_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::MoreEqual;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::LessEqual;
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
               else if( state == State::EQUAL_EXPRESSION )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Equal;
                    state = State::FINISH;
                  }
               }
               else if( state == State::MORE_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::MoreEqual;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS_EQUAL )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::LessEqual;
                    state = State::FINISH;
                  }
               }
            };
            handlers.equal_syntax_node = [ &equal0, &equal1, &state ]( const EqualSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  equal0 = node;
                  state = State::EQUAL_EXPRESSION;
               }
               else if( state == State::EQUAL_EXPRESSION )
               {
                  equal1 = node;
                  state = State::EQUAL_EXPRESSION;
               }
               else if( state == State::LESS )
               {
                  equal1 = node;
                  state = State::LESS_EQUAL;
               }
               else if( state == State::MORE )
               {
                  equal1 = node;
                  state = State::MORE_EQUAL;
               }
            };
            handlers.more_syntax_node = [ &more, &equal1, &state ]( const MoreSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  more = node;
                  state = State::MORE;
               }
            };
            handlers.less_syntax_node = [ &less, &equal1, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  less = node;
                  state = State::LESS;
               }
            };
            iterate_over_last_n_nodes( stack, 4, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( a );
            if( operation_type == BinExprSyntaxNode::Type::Equal )
            {
              plan.to_remove.nodes.push_back( equal0 );
              plan.to_remove.nodes.push_back( equal1 );
            }
            else if( operation_type == BinExprSyntaxNode::Type::LessEqual )
            {
              plan.to_remove.nodes.push_back( less );
              plan.to_remove.nodes.push_back( equal1 );
            }
            else if( operation_type == BinExprSyntaxNode::Type::MoreEqual )
            {
              plan.to_remove.nodes.push_back( more );
              plan.to_remove.nodes.push_back( equal1 );
            }
            plan.to_remove.nodes.push_back( b );

            const auto& expression_node = std::make_shared< BinExprSyntaxNode >(operation_type, a, b );

            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );

      // F|BIN_EXPR|UN_EXPR LESS|MORE F|BIN_EXPR|UN_EXPR[!PLUS&&!MINUS&&!ASTERIX&&!SLASH] 
      mProductions.emplace_back(
         [ /* this */ ]( const Stack& stack, const ISyntaxNodeSP& lookahead ) -> std::optional< Plan >
         {
            ISyntaxNodeSP a;
            MoreSyntaxNodeSP more;
            LessSyntaxNodeSP less;
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
               else if( state == State::MORE )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::More;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Less;
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
               else if( state == State::MORE )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::More;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Less;
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
               else if( state == State::MORE )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::More;
                    state = State::FINISH;
                  }
               }
               else if( state == State::LESS )
               {
                  if( lookahead && !check_type< PlusSyntaxNode >( lookahead ) && 
                                   !check_type< MinusSyntaxNode >( lookahead ) && 
                                   !check_type< AsteriskSyntaxNode >( lookahead ) && 
                                   !check_type< SlashSyntaxNode >( lookahead ) )
                  {
                    b = node;
                    state = State::F;
                    operation_type = BinExprSyntaxNode::Type::Less;
                    state = State::FINISH;
                  }
               }
            };
            handlers.more_syntax_node = [ &more, &state ]( const MoreSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  more = node;
                  state = State::MORE;
               }
            };
            handlers.less_syntax_node = [ &less, &state ]( const LessSyntaxNodeSP& node )
            {
               if( state == State::F )
               {
                  less = node;
                  state = State::LESS;
               }
            };
            iterate_over_last_n_nodes( stack, 3, handlers );

            if( state != State::FINISH )
               return {};

            plan.to_remove.nodes.push_back( a );
            if( operation_type == BinExprSyntaxNode::Type::Less )
            {
              plan.to_remove.nodes.push_back( less );
            }
            else if( operation_type == BinExprSyntaxNode::Type::More )
            {
              plan.to_remove.nodes.push_back( more );
            }
            plan.to_remove.nodes.push_back( b );

            const auto& expression_node = std::make_shared< BinExprSyntaxNode >(operation_type, a, b );

            plan.to_add.nodes.push_back( expression_node );
            return plan;
         } );
   }
};

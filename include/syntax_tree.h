#pragma once

#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/return_syntax_node.h"
#include "terminals/slash_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <functional>
#include <optional>
#include "enums.h"
#include "syntax_nodes/terminals/bol_syntax_node.h"
#include "syntax_nodes/terminals/close_curly_bracket_syntax_node.h"
#include "syntax_nodes/terminals/eol_syntax_node.h"
#include "syntax_nodes/terminals/if_syntax_node.h"
#include "syntax_nodes/terminals/while_syntax_node.h"
#include "syntax_nodes/terminals/minus_syntax_node.h"
#include "syntax_nodes/terminals/name_syntax_node.h"
#include "syntax_nodes/terminals/comma_syntax_node.h"
#include "syntax_nodes/terminals/number_syntax_node.h"
#include "syntax_nodes/terminals/open_curly_bracket_syntax_node.h"
#include "syntax_nodes/nonterminals/bin_expr_syntax_node.h"
#include "syntax_nodes/terminals/plus_syntax_node.h"
#include "syntax_nodes/terminals/semicolon_syntax_node.h"
#include "grammars/un_expr_grammar.h"
#include "grammars/bin_expr_grammar.h"
#include "grammars/computational_expression_grammar.h"
#include "grammars/conditional_expression_grammar.h"
#include "grammars/statment_grammar.h"
#include "grammars/f_grammar.h"
#include "grammars/if_statment_grammar.h"
#include "grammars/while_statment_grammar.h"
#include "grammars/function_grammar.h"
// #include "grammars/function_call_grammar.h"
#include "grammars/print_statment_grammar.h"
#include "grammars/scope_grammar.h"
#include "grammars/varible_assigment_grammar.h"
// #include "grammars/return_statment_grammar.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "utils/dfs_pre_order_range.h"

class SyntaxTree
{
public:
   SyntaxTree( const LexicalTokens& lexical_tokens )
   {
      std::vector< IGrammarSP > grammars{
         std::make_shared< F >(),
         std::make_shared< BinExpr >(),
         std::make_shared< UnExpr >(),
         std::make_shared< ComputationalExpression >(),
         std::make_shared< VaribleAssigment >(),
         std::make_shared< Print >(),
         std::make_shared< ConditionalExpression >(),
         std::make_shared< Statment >(),
         std::make_shared< Scope >(),
         std::make_shared< If >(),
         std::make_shared< While >(),
         // std::make_shared< Return >(),
         std::make_shared< Function >(),
         // std::make_shared< FunctionCall >(),
      };

      Stack stack;
      const auto& tokens = lexical_tokens.list();
      for( auto it = tokens.begin(); it != tokens.end(); ++it )
      {
         ISyntaxNodeSP lookahead_node;
         if( auto next_it = std::next( it ); next_it != tokens.end() )
         {
           lookahead_node = createSyntaxNodeFromToken( *next_it );
         }
         const auto& token = *it;
         const auto& node = createSyntaxNodeFromToken( token );
         stack.emplace_back( node );

         bool is_production_can_be = stack.size() >= 1;
         while( is_production_can_be )
         {
            is_production_can_be = false;
            for( const auto& grammar : grammars )
            {
              const auto& plan_opt = grammar->TryReduce( stack, lookahead_node );
              if( !plan_opt )
              {
                continue;
              }
              is_production_can_be = true;
              const auto& plan = plan_opt.value();

              for( size_t i = 0; i < plan.to_remove.nodes.size(); ++i )
                stack.pop_back();

              for( const auto& d : plan.to_add.nodes )
                stack.push_back( d );

              break;
            }
         }
      }

      if( stack.size() > 1 )
         throw std::runtime_error( "Not all nodes reduced" );

      if( stack.size() == 0 )
         throw std::runtime_error( "No final reduced node" );

      mRoot = stack.front();
   }

   SyntaxTree( const ISyntaxNodeSP& root )
      : mRoot{ root }
   {
   }

   ISyntaxNodeSP root() const
   {
      return mRoot;
   }

   ISyntaxNodeSP createSyntaxNodeFromToken( const LexicalTokens::LexicalToken& token ) const
   {
      ISyntaxNodeSP syntax_node;
      switch( token.type )
      {
      case Token_Type::BOL:
      {
         syntax_node = std::make_shared< BolSyntaxNode >();
      };
      break;
      case Token_Type::EOL:
      {
         syntax_node = std::make_shared< EolSyntaxNode >();
      };
      break;

      case Token_Type::PLUS:
      {
         syntax_node = std::make_shared< PlusSyntaxNode >();
      };
      break;

      case Token_Type::MINUS:
      {
         syntax_node = std::make_shared< MinusSyntaxNode >();
      };
      break;
      case Token_Type::ASTERISK:
      {
         syntax_node = std::make_shared< AsteriskSyntaxNode >();
      };
      break;
      case Token_Type::SLASH:
      {
         syntax_node = std::make_shared< SlashSyntaxNode >();
      };
      break;
      case Token_Type::INT:
      {
         syntax_node = std::make_shared< NumberSyntaxNode >( token.text );
      };
      break;
      case Token_Type::EQUAL:
      {
         syntax_node = std::make_shared< EqualSyntaxNode >();
      };
      break;
      case Token_Type::LESS:
      {
         syntax_node = std::make_shared< LessSyntaxNode >();
      };
      break;
      case Token_Type::MORE:
      {
         syntax_node = std::make_shared< MoreSyntaxNode >();
      };
      break;
      case Token_Type::SEMICOLON:
      {
         syntax_node = std::make_shared< SemicolonSyntaxNode >();
      };
      break;
      case Token_Type::OPEN_CURLY_BRACKET:
      {
         syntax_node = std::make_shared< OpenCurlyBracketSyntaxNode >();
      };
      break;
      case Token_Type::CLOSE_CURLY_BRACKET:
      {
         syntax_node = std::make_shared< CloseCurlyBracketSyntaxNode >();
      };
      break;
      case Token_Type::OPEN_CIRCLE_BRACKET:
      {
         syntax_node = std::make_shared< OpenCircleBracketSyntaxNode >();
      };
      break;
      case Token_Type::CLOSE_CIRCLE_BRACKET:
      {
         syntax_node = std::make_shared< CloseCircleBracketSyntaxNode >();
      };
      break;
      case Token_Type::PRINT:
      {
         syntax_node = std::make_shared< PrintSyntaxNode >();
      };
      break;
      case Token_Type::IF:
      {
         syntax_node = std::make_shared< IfSyntaxNode >();
      };
      break;
      case Token_Type::WHILE:
      {
         syntax_node = std::make_shared< WhileSyntaxNode >();
      };
      break;
      case Token_Type::NAME:
      {
         syntax_node = std::make_shared< NameSyntaxNode >( token.text );
      };
      break;
      case Token_Type::COMMA:
      {
         syntax_node = std::make_shared< CommaSyntaxNode >();
      };
      break;
      case Token_Type::RETURN:
      {
         syntax_node = std::make_shared< ReturnSyntaxNode >();
      };
      break;
      case Token_Type::FUNCTION:
      {
         syntax_node = std::make_shared< FunctionSyntaxNode >();
      };
      break;
      default:
      {
      }
      }
      return syntax_node;
   }

   bool operator==( const SyntaxTree& syntax_tree ) const
   {
      bool result = true;
      const auto& our_range = DfsRange< ISyntaxNodeSP >{ std::list< ISyntaxNodeSP >{ root() } };
      const auto& their_range = DfsRange< ISyntaxNodeSP >{ std::list< ISyntaxNodeSP >{ syntax_tree.root() } };
      for( const auto& [ a, b ] : zip( our_range, their_range ) )
      {
         if( !a || !b )
         {
            result = false;
            break;
         }
         if( *a.value() != *b.value() )
         {
            result = false;
            break;
         }
      }
      return result;
   }

   std::string to_string() const
   {
      std::string result;
      std::stringstream s{ result };

      std::unordered_set< ISyntaxNodeSP > visited;

      size_t n = 0;
      iterative_dfs(
         mRoot,
         [ &n, &s, &visited ]( const ISyntaxNodeSP& node ) -> bool
         {
            bool visited_node = visited.contains( node );
            if( !visited_node )
            {
               visited.insert( node );
            }
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.bol_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "BOL" << "}"; };
            handlers.plus_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PLUS" << "}"; };
            handlers.minus_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MINUS" << "}"; };
            handlers.asterisk_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "ASTERISK" << "}"; };
            handlers.slash_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SLASH" << "}"; };
            handlers.number_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "NUMBER" << "}"; };
            handlers.f_syntax_node = [ &s ]( const FSyntaxNodeSP& node ) { s << "{" << "F" << '(' << std::to_string( node->value() ) << ')' << "}"; };
            // handlers.addition_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "ADDITION" << "}"; };
            // handlers.subtraction_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SUBTRACTION" << "}"; };
            // handlers.multiply_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MULTIPLY" << "}"; };
            // handlers.division_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "DIVISION" << "}"; };
            handlers.bin_expr_syntax_node = [ &s ]( const BinExprSyntaxNodeSP& node )
            { 
               std::string type;
               switch( node->type() )
               {
               case BinExprSyntaxNode::Type::Addition:
               {
                  type = "Addition";
               };
               break;
               case BinExprSyntaxNode::Type::Substruction:
               {
                  type = "Substruction";
               };
               break;
               case BinExprSyntaxNode::Type::Multiply:
               {
                  type = "Multiply";
               };
               break;
               case BinExprSyntaxNode::Type::Division:
               {
                  type = "Division";
               };
               break;
               }

               s << "{" << "BIN_EXPR" << '(' << type << ')' << "}";
            };
            handlers.un_expr_syntax_node = [ &s ]( const UnExprSyntaxNodeSP& node )
            { 
               std::string type;
               switch( node->type() )
               {
               case UnExprSyntaxNode::Type::Negation:
               {
                  type = "Negation";
               };
               break;
               }

               s << "{" << "UN_EXPR" << '(' << type << ')' << "}";
            };
            handlers.eol_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EOL" << "}"; };
            handlers.semicolon_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SEMICOLON" << "}"; };
            handlers.return_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "RETURN" << "}"; };
            handlers.return_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "RETURN_STATMENT" << "}"; };
            handlers.comma_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "COMMA" << "}"; };
            handlers.statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "STATMENT" << "}"; };
            handlers.scope_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SCOPE" << "}"; };
            handlers.open_curly_bracket_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "OPEN_CURLY_BRACKET" << "}"; };
            handlers.close_curly_bracket_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "CLOSE_CURLY_BRACKET" << "}"; };
            handlers.computational_expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "COMPUTATIONAL_EXPRESSION" << "}"; };
            handlers.varible_syntax_node = [ &s ]( const VaribleSyntaxNodeSP& node ) { s << "{" << "VARIBLE" << '(' << node->name() << ')' << "}"; };
            handlers.conditional_expression_syntax_node = [ &s ]( const ConditionalExpressionSyntaxNodeSP& node )
            {
               std::string type;
               switch( node->type() )
               {
               case ConditionalExpressionSyntaxNode::Type::LESS:
               {
                  type = "LESS";
               };
               break;
               case ConditionalExpressionSyntaxNode::Type::MORE:
               {
                  type = "MORE";
               };
               break;
               case ConditionalExpressionSyntaxNode::Type::EQUAL:
               {
                  type = "EQUAL";
               };
               break;
               case ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL:
               {
                  type = "LESS_OR_EQUAL";
               };
               break;
               case ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL:
               {
                  type = "MORE_OR_EQUAL";
               };
               break;
               }
               s << "{" << "CONDITIONAL_EXPRESSION" << " (" << type << ")" << "}";
            };
            handlers.print_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PRINT_STATMENT" << "}"; };
            handlers.equal_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EQUAL" << "}"; };
            handlers.less_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "LESS" << "}"; };
            handlers.more_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MORE" << "}"; };
            handlers.if_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF" << "}"; };
            handlers.if_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF_STATMENT" << "}"; };
            handlers.while_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "WHILE" << "}"; };
            handlers.while_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "WHILE_STATMENT" << "}"; };
            handlers.function_syntax_node = [ &s ]( const FunctionSyntaxNodeSP& node ) { s << "{" << "FUNCTION" << " (" << node->name() << ")" << "}"; };
            handlers.function_call_syntax_node = [ &s ]( const FunctionCallSyntaxNodeSP& node ) { s << "{" << "FUNCTION_CALL" << " (" << node->name() << ")" << "}"; };
            handlers.function_statment_syntax_node = [ &s ]( const FunctionStatmentSyntaxNodeSP& node )
            { s << "{" << "FUNCTION_STATMENT" << " (" << node->name() << ")" << "}"; };
            handlers.print_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PRINT" << "}"; };
            handlers.varible_assigment_statment_syntax_node = [ &s ]( const VaribleAssigmentStatmentSyntaxNodeSP& node )
            {
               std::string context;
               switch( node->context() )
               {
               case VaribleAssigmentStatmentSyntaxNode::Context::GLOBAL:
               {
                  context = "GLOBAL";
               };
               break;
               case VaribleAssigmentStatmentSyntaxNode::Context::LOCAL:
               {
                  context = "LOCAL";
               };
               break;
               }
               s << "{" << "VARIBLE ASSIGMENT" << " (" << context << ")" << "}";
            };
            handlers.name_syntax_node = [ &s ]( const NameSyntaxNodeSP& node ) { s << "{" << "NAME" << " (" << node->value() << ')' << "}"; };
            for( size_t i = 0; i < n; ++i )
               s << "   ";

            const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
            node->accept( visitor );
            s << '\n';

            ++n;
            if( visited_node )
            {
               return true;
            }
            else
            {
               return false;
            }
         },
         [ &n ]( const ISyntaxNodeSP& /* node */ ) { --n; } );
      return s.str();
   }

private:
   ISyntaxNodeSP mRoot;
};

inline std::ostream& operator<<( std::ostream& o, const SyntaxTree& rhs )
{
   o << rhs.to_string();
   return o;
}

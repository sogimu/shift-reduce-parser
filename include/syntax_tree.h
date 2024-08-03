#pragma once

#include "base/asterisk_syntax_node.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <iostream>
#include <sstream>
#include <functional>
#include <optional>
#include "enums.h"
#include "grammars/base/bol_syntax_node.h"
#include "grammars/base/close_curly_bracket_syntax_node.h"
#include "grammars/base/eol_syntax_node.h"
#include "grammars/base/if_syntax_node.h"
#include "grammars/base/minus_syntax_node.h"
#include "grammars/base/name_syntax_node.h"
#include "grammars/base/number_syntax_node.h"
#include "grammars/base/open_curly_bracket_syntax_node.h"
#include "grammars/base/plus_syntax_node.h"
#include "grammars/base/semicolon_syntax_node.h"
#include "grammars/computational_expression_grammar.h"
#include "grammars/conditional_expression_grammar.h"
#include "grammars/expression_grammar.h"
#include "grammars/f_grammar.h"
#include "grammars/if_expression_grammar.h"
#include "grammars/print_expression_grammar.h"
#include "grammars/scope_grammar.h"
#include "grammars/varible_assigment_grammar.h"
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
      // E -> T + E | T - E | T
      // T -> F * T | F / T | F
      // F -> (E)   | -N    | N

      std::vector< IGrammarSP > grammars{
         std::make_shared< F >(),
         // std::make_shared< Sum >(),
         // std::make_shared< Diff >(),
         // std::make_shared< E >(),
         std::make_shared< ComputationalExpression >(), std::make_shared< VaribleAssigment >(), std::make_shared< Print >(), std::make_shared< ConditionalExpression >(),
         std::make_shared< Expression >(), std::make_shared< Scope >(), std::make_shared< If >(),
         //            std::make_shared<Mul>(),
         //            std::make_shared<Mul>(),
         //            std::make_shared<Div>(),
         //            std::make_shared<T>(),
         //            std::make_shared<E>(),
         //            std::make_shared<P>(),
         //            std::make_shared<Assigment>()
      };

      Stack stack;
      const auto& tokens = lexical_tokens.list();
      for( auto it = tokens.begin(); it != tokens.end(); ++it )
      {
         const auto& token = *it;
         //            const auto& node = std::make_shared<ISyntaxNode>(token.type);
         const auto& node = createSyntaxNodeFromToken( token );
         stack.emplace_back( node );

         bool is_production_can_be = stack.size() >= 1;
         while( is_production_can_be )
         {
            is_production_can_be = false;
            for( const auto& grammar : grammars )
            {
               auto plan_opt = grammar->TryReduce( stack );
               while( plan_opt )
               {
                  is_production_can_be = true;
                  auto plan = plan_opt.value();
                  //                        const auto& plan = production->make_plan();

                  for( size_t i = 0; i < plan.to_remove.nodes.size(); ++i )
                     stack.pop_back();

                  for( const auto& d : plan.to_add.nodes )
                     stack.push_back( d );

                  plan_opt = grammar->TryReduce( stack );
               }
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
      case Token_Type::NAME:
      {
         syntax_node = std::make_shared< NameSyntaxNode >( token.text );
      };
      break;
      }
      return syntax_node;
   }

   template< typename Func >
   double execute_ast( const ISyntaxNodeSP& root, Func func ) const
   {
      double result = 0.0;

      std::map< ISyntaxNodeSP, double > valueByASTNode;

      iterative_dfs(
         root, []( const ISyntaxNodeSP& node ) -> bool { return false; },
         [ &result, &valueByASTNode, &func ]( const ISyntaxNodeSP& node )
         {
            //            if( node->first && node->second )
            //            {
            //                double first_operand;
            //                if( valueByASTNode.count(node->first) )
            //                {
            //                    first_operand = valueByASTNode[node->first];
            //                }
            //                else
            //                {
            //                    first_operand = std::stod(node->first->token.text);
            //                }

            //                double second_operand;
            //                if( valueByASTNode.count(node->second) )
            //                {
            //                    second_operand = valueByASTNode[node->second];
            //                }
            //                else
            //                {
            //                    second_operand = std::stod(node->second->token.text);
            //                }

            //                double result_operand = 0.0;
            //                result_operand = func(first_operand, second_operand, node->token.text);

            //                valueByASTNode[node] = result_operand;
            //                result = result_operand;
            //            }
            //            else
            //            {
            //                result = std::stod(node->token.text);
            //            }
         } );

      return result;
   }

   bool operator==( const SyntaxTree& syntax_tree ) const
   {
      bool result = true;
      const auto& our_range = DfsRange< ISyntaxNodeSP >{ std::vector< ISyntaxNodeSP >{ root() } };
      const auto& their_range = DfsRange< ISyntaxNodeSP >{ std::vector< ISyntaxNodeSP >{ syntax_tree.root() } };
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

      size_t n = 0;
      iterative_dfs(
         mRoot,
         [ &n, &s ]( const ISyntaxNodeSP& node ) -> bool
         {
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.bol_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "BOL" << "}"; };
            handlers.plus_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PLUS" << "}"; };
            handlers.minus_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MINUS" << "}"; };
            handlers.asterisk_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "ASTERISK" << "}"; };
            handlers.number_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "NUMBER" << "}"; };
            handlers.f_syntax_node = [ &s ]( const FSyntaxNodeSP& node ) { s << "{" << "F" << '(' << std::to_string( node->value() ) << ')' << "}"; };
            handlers.addition_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "ADDITION" << "}"; };
            handlers.subtraction_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SUBTRACTION" << "}"; };
            handlers.multiply_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MULTIPLY" << "}"; };
            handlers.eol_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EOL" << "}"; };
            handlers.semicolon_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SEMICOLON" << "}"; };
            handlers.expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EXPRESSION" << "}"; };
            handlers.scope_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "SCOPE" << "}"; };
            handlers.open_curly_bracket_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "OPEN_CURLY_BRACKET" << "}"; };
            handlers.close_curly_bracket_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "CLOSE_CURLY_BRACKET" << "}"; };
            handlers.computational_expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "COMPUTATIONAL_EXPRESSION" << "}"; };
            handlers.conditional_expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "CONDITIONAL_EXPRESSION" << "}"; };
            handlers.print_expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PRINT_EXPRESSION" << "}"; };
            handlers.equal_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EQUAL" << "}"; };
            handlers.less_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "LESS" << "}"; };
            handlers.more_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MORE" << "}"; };
            handlers.if_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF" << "}"; };
            handlers.if_expression_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF_EXPRESSION" << "}"; };
            handlers.print_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PRINT" << "}"; };
            handlers.varible_assigment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "VARIBLE ASSIGMENT" << "}"; };
            handlers.name_syntax_node = [ &s ]( const NameSyntaxNodeSP& node ) { s << "{" << "NAME" << '(' << node->value() << ')' << "}"; };
            for( int i = 0; i < n; ++i )
               s << "   ";

            const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
            node->accept( visitor );
            s << '\n';

            ++n;
            return false;
         },
         [ &n ]( const ISyntaxNodeSP& node ) { --n; } );
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

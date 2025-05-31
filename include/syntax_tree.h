#pragma once

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
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "terminals/asterisk_syntax_node.h"
#include "terminals/return_syntax_node.h"
#include "terminals/slash_syntax_node.h"
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
#include "grammars/circle_brackets_grammar.h"
#include "grammars/statment_grammar.h"
#include "grammars/f_grammar.h"
#include "grammars/if_statment_grammar.h"
#include "grammars/while_statment_grammar.h"
#include "grammars/function_statment_grammar.h"
#include "grammars/function_call_grammar.h"
#include "grammars/print_statment_grammar.h"
#include "grammars/scope_grammar.h"
#include "grammars/varible_assigment_grammar.h"
#include "grammars/return_statment_grammar.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "utils/dfs_pre_order_range.h"

class SyntaxTree
{
public:
   SyntaxTree( const LexicalTokens& lexical_tokens );

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
      case Token_Type::FUNCTION:
      {
         syntax_node = std::make_shared< FunctionSyntaxNode >();
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

   std::string to_string() const;

private:
   ISyntaxNodeSP mRoot;
};

inline std::ostream& operator<<( std::ostream& o, const SyntaxTree& rhs )
{
   o << rhs.to_string();
   return o;
}

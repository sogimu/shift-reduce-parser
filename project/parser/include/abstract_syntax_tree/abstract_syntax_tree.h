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
#include "syntax_nodes/terminals/double_syntax_node.h"
#include "syntax_nodes/terminals/open_curly_bracket_syntax_node.h"
#include "syntax_nodes/nonterminals/bin_expr_syntax_node.h"
#include "syntax_nodes/terminals/plus_syntax_node.h"
#include "syntax_nodes/terminals/semicolon_syntax_node.h"
#include "syntax_nodes/terminals/var_syntax_node.h"
#include "syntax_nodes/terminals/string_syntax_node.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "utils/dfs_pre_order_range.h"
#include "i_grammar.h"

class AbstractSyntaxTree
{
public:
   AbstractSyntaxTree( const LexicalTokens& lexical_tokens );

   AbstractSyntaxTree( const ISyntaxNodeSP& root )
      : mRoot{ root }
   {
   }
    Stack stack;

   ISyntaxNodeSP root() const
   {
      return mRoot;
   }

   ISyntaxNodeSP createSyntaxNodeFromToken( const LexicalTokens::LexicalToken& lexical_token ) const
   {
      ISyntaxNodeSP syntax_node;
      switch( lexical_token.type )
      {
      case Token_Type::BOL:
      {
         syntax_node = std::make_shared< BolSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::EOL:
      {
         syntax_node = std::make_shared< EolSyntaxNode >( lexical_token );
      };
      break;

      case Token_Type::PLUS:
      {
         syntax_node = std::make_shared< PlusSyntaxNode >( lexical_token );
      };
      break;

      case Token_Type::MINUS:
      {
         syntax_node = std::make_shared< MinusSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::ASTERISK:
      {
         syntax_node = std::make_shared< AsteriskSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::SLASH:
      {
         syntax_node = std::make_shared< SlashSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::DOUBLE:
      {
         syntax_node = std::make_shared< DoubleSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::INT:
      {
         syntax_node = std::make_shared< IntSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::EQUAL:
      {
         syntax_node = std::make_shared< EqualSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::LESS:
      {
         syntax_node = std::make_shared< LessSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::MORE:
      {
         syntax_node = std::make_shared< MoreSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::SEMICOLON:
      {
         syntax_node = std::make_shared< SemicolonSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::COLON:
      {
         syntax_node = std::make_shared< ColonSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::VAR:
      {
         syntax_node = std::make_shared< VarSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::OPEN_CURLY_BRACKET:
      {
         syntax_node = std::make_shared< OpenCurlyBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::CLOSE_CURLY_BRACKET:
      {
         syntax_node = std::make_shared< CloseCurlyBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::OPEN_CIRCLE_BRACKET:
      {
         syntax_node = std::make_shared< OpenCircleBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::CLOSE_CIRCLE_BRACKET:
      {
         syntax_node = std::make_shared< CloseCircleBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::OPEN_SQUARE_BRACKET:
      {
         syntax_node = std::make_shared< OpenSquareBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::CLOSE_SQUARE_BRACKET:
      {
         syntax_node = std::make_shared< CloseSquareBracketSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::PRINT:
      {
         syntax_node = std::make_shared< PrintSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::IF:
      {
         syntax_node = std::make_shared< IfSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::WHILE:
      {
         syntax_node = std::make_shared< WhileSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::FUNCTION:
      {
         syntax_node = std::make_shared< FunctionSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::NAME:
      {
         syntax_node = std::make_shared< NameSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::COMMA:
      {
         syntax_node = std::make_shared< CommaSyntaxNode >( lexical_token);
      };
      break;
      case Token_Type::RETURN:
      {
         syntax_node = std::make_shared< ReturnSyntaxNode >( lexical_token );
      };
      break;
      case Token_Type::STRING:
      {
         syntax_node = std::make_shared< StringSyntaxNode >( lexical_token );
      };
      break;
      default:
      {
      }
      }
      return syntax_node;
   }

   bool operator==( const AbstractSyntaxTree& syntax_tree ) const
   {
    return ::equal( syntax_tree.mRoot, mRoot );
   }

   std::string to_string() const;

private:
   ISyntaxNodeSP mRoot;
};

inline std::ostream& operator<<( std::ostream& o, const AbstractSyntaxTree& rhs )
{
   o << rhs.to_string();
   return o;
}

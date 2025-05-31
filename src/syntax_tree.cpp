#include "syntax_tree.h"

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

SyntaxTree::SyntaxTree( const LexicalTokens& lexical_tokens )
 {
    std::vector< IGrammarSP > grammars{
       std::make_shared< F >(),
       std::make_shared< BinExpr >(),
       std::make_shared< UnExpr >(),
       std::make_shared< Print >(),
       std::make_shared< CircleBrackets >(),
       std::make_shared< VaribleAssigment >(),
       std::make_shared< Return >(),
       std::make_shared< Statment >(),
       std::make_shared< Scope >(),
       std::make_shared< If >(),
       std::make_shared< While >(),
       std::make_shared< FunctionStatment >(),
       std::make_shared< FunctionCall >()
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

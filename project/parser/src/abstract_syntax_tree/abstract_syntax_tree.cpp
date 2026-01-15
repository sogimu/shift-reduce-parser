#include "abstract_syntax_tree.h"

#include "syntax_exception.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
#include <memory>
#include <map>
#include <unordered_set>
#include <sstream>
#include <functional>
#include <optional>
#include "syntax_exception.hpp"
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
#include "syntax_nodes/terminals/open_square_bracket_syntax_node.h"
#include "syntax_nodes/terminals/close_square_bracket_syntax_node.h"
#include "syntax_nodes/nonterminals/bin_expr_syntax_node.h"
#include "syntax_nodes/terminals/plus_syntax_node.h"
#include "syntax_nodes/terminals/semicolon_syntax_node.h"
#include "syntax_nodes/terminals/colon_syntax_node.h"
#include "syntax_nodes/terminals/var_syntax_node.h"
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
#include "grammars/array_grammar.h"
#include "grammars/varible_assigment_grammar.h"
#include "grammars/return_statment_grammar.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"
#include "utils/dfs_pre_order_range.h"

AbstractSyntaxTree::AbstractSyntaxTree( const LexicalTokens& lexical_tokens )
 {
    std::vector< IGrammarSP > grammars{
       std::make_shared< Array >(),
       std::make_shared< FunctionCall >(),
       std::make_shared< Print >(),
       std::make_shared< Return >(),
       std::make_shared< CircleBrackets >(),
       std::make_shared< F >(),
       std::make_shared< BinExpr >(),
       std::make_shared< UnExpr >(),
       std::make_shared< VaribleAssigment >(),
       std::make_shared< Statment >(),
       std::make_shared< Scope >(),
       std::make_shared< If >(),
       std::make_shared< While >(),
       std::make_shared< FunctionStatment >()
    };

    // Stack stack;
    const auto& tokens = lexical_tokens.list();
    auto it = tokens.begin();
    do
    {
       std::optional<IGrammar::Progress> best_progress_opt;
       ISyntaxNodeSP lookahead_node;
       if( auto next_it = std::next( it ); next_it != tokens.end() )
       {
         lookahead_node = createSyntaxNodeFromToken( *next_it );
       }
       const auto& token = *it;
       const auto& node = createSyntaxNodeFromToken( token );
       stack.emplace_back( node );

       bool try_reduce = true;
       while( try_reduce )
       {
          try_reduce = false;
          for( const auto& grammar : grammars )
          {
            const auto& try_reduce_result = grammar->TryReduce( stack, lookahead_node );
            
            std::optional<IGrammar::Plan> plan_opt;
            std::visit([&try_reduce, &best_progress_opt, &plan_opt, this](auto&& arg)
            {
              using T = std::decay_t<decltype(arg)>;
              if constexpr (std::is_same_v<T, IGrammar::Progress>)
              {
                  if( !best_progress_opt || arg.readiness > best_progress_opt->readiness )
                      best_progress_opt = arg;
              } 
              else if constexpr (std::is_same_v<T, IGrammar::Plan>) 
              {
                  plan_opt = arg;
              }          
            }, try_reduce_result);
          
            if( plan_opt )
            {
              const auto& plan = plan_opt.value();

              for( size_t i = 0; i < plan.to_remove.nodes.size(); ++i )
                stack.pop_back();

              for( const auto& d : plan.to_add.nodes )
                stack.push_back( d );
              
              try_reduce = true;
              break;
            }
          }
       }
       
       if( best_progress_opt && best_progress_opt->readiness == 0.0 )
          if( stack.size() > 1 )
              throw SyntaxException( "Stack has more that on node and no one grammars may reduce current stack. It's seems that there is syntax error in program!", stack );
       
       ++it;
    }
    while( it != tokens.end() );

    if( stack.size() > 1 )
       throw std::runtime_error( "Not all nodes reduced" );

    if( stack.size() == 0 )
       throw std::runtime_error( "No final reduced node" );

    mRoot = stack.front();
 }

std::string AbstractSyntaxTree::to_string() const
{
  return ::to_string( mRoot );
}

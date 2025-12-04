#include "control_flow_graph.h"

#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "abstract_syntax_tree.h"

#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/if_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "abstract_syntax_tree.h"
#include "utils.h"
#include "i_syntax_node.h"
#include "make_deep_syntax_node_copy.h"
#include "make_shallow_syntax_node_copy.h"
#include "is_last_nodes.h"


ControlFlowGraph::ControlFlowGraph( const AbstractSyntaxTree& ast )
{
   const auto& transformed_tree = create_tree_from1< ISyntaxNodeSP, ISyntaxNodeSP >(
      ast.root(),
      []( const ISyntaxNodeSP& source_node ) -> ISyntaxNodeSP
      {
         const auto& target_node = make_shallow_copy( source_node );
         return target_node;
      },
      [ ]( const std::vector< ISyntaxNodeSP >& source_stack,
                                                                   const std::vector< std::pair<ISyntaxNodeSP, std::list<ISyntaxNodeSP>::iterator> >& target_stack )
      {
         bool is_node_added = false;   

         const auto& source_node = *source_stack.rbegin();
         const auto& [target_node_parent, it] = *target_stack.rbegin();
         
         const auto& target_node = make_shallow_copy( source_node );

         if( IsLastNodesIs< StatmentSyntaxNode >( source_stack ) ||
             IsLastNodesIs< ScopeSyntaxNode >( source_stack ) || 
             IsLastNodesIs< IfStatmentSyntaxNode >( source_stack ) ||
             IsLastNodesIs< WhileStatmentSyntaxNode >( source_stack ) ||
             IsLastNodesIs< FunctionStatmentSyntaxNode >( source_stack ) )
         {
           auto new_parent_target_node = target_node_parent->add_back( target_node );
            is_node_added = true;
           return std::make_tuple(new_parent_target_node, is_node_added, new_parent_target_node->end());
         }
         else if( IsLastNodesIs< IfStatmentSyntaxNode, BinExprSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< IfStatmentSyntaxNode, UnExprSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< IfStatmentSyntaxNode, FSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< IfStatmentSyntaxNode, NameSyntaxNode >( source_stack ) ||
                  IsLastNodesIs< IfStatmentSyntaxNode, FunctionCallSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            const auto& [if_statment, if_statment_it] = *it;
            std::advance( it, 1 );
            const auto& [parent_of_if_statment, parent_it] = *it;
            if( auto if_statment_it = std::find( parent_of_if_statment->begin(), parent_of_if_statment->end(), if_statment );
                if_statment_it != parent_of_if_statment->end() )
            {
               return std::make_tuple(parent_of_if_statment, false, if_statment_it);
            }
         }
         else if( IsLastNodesIs< WhileStatmentSyntaxNode, BinExprSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< WhileStatmentSyntaxNode, UnExprSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< WhileStatmentSyntaxNode, FSyntaxNode >( source_stack ) || 
                  IsLastNodesIs< WhileStatmentSyntaxNode, NameSyntaxNode >( source_stack ) ||
                  IsLastNodesIs< WhileStatmentSyntaxNode, FunctionCallSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            const auto& [if_statment, if_statment_it] = *it;
            std::advance( it, 1 );
            const auto& [parent_of_if_statment, parent_it] = *it;
            if( auto if_statment_it = std::find( parent_of_if_statment->begin(), parent_of_if_statment->end(), if_statment );
                if_statment_it != parent_of_if_statment->end() )
            {
               return std::make_tuple(parent_of_if_statment, false, if_statment_it);
            }
         }
         return std::make_tuple(target_node_parent, false, it);
      },
      []( const std::vector< ISyntaxNodeSP >& source_stack,
                                  const std::vector< std::pair<ISyntaxNodeSP, std::list<ISyntaxNodeSP>::iterator> >& target_stack )
      {
         const auto& source_node_wrapper = *source_stack.rbegin();
         const auto& [target_node_parent_wrapper, it] = *target_stack.rbegin();
         const auto& target_node = make_shallow_copy( source_node_wrapper );
         std::optional< ISyntaxNodeSP > new_parent_target_node = target_node_parent_wrapper;

         target_node_parent_wrapper->insert( it, target_node );
      },
      []( const ISyntaxNodeSP& node )
         -> std::pair< std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator >, std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator > >
      { return { node->rbegin(), node->rend() }; } );
  mRoot = transformed_tree;
}

ISyntaxNodeSP ControlFlowGraph::root() const
{
  return mRoot;
}

std::string ControlFlowGraph::to_string() const
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
           case BinExprSyntaxNode::Type::Equal:
           {
              type = "Equal";
           };
           break;
           case BinExprSyntaxNode::Type::Less:
           {
              type = "Less";
           };
           break;
           case BinExprSyntaxNode::Type::LessEqual:
           {
              type = "LessEqual";
           };
           break;
           case BinExprSyntaxNode::Type::More:
           {
              type = "More";
           };
           break;
           case BinExprSyntaxNode::Type::MoreEqual:
           {
              type = "MoreEqual";
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
        handlers.varible_syntax_node = [ &s ]( const VaribleSyntaxNodeSP& node ) { s << "{" << "VARIBLE" << '(' << node->name() << ')' << "}"; };
        handlers.print_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "PRINT_STATMENT" << "}"; };
        handlers.equal_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "EQUAL" << "}"; };
        handlers.less_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "LESS" << "}"; };
        handlers.more_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "MORE" << "}"; };
        handlers.if_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF" << "}"; };
        handlers.if_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "IF_STATMENT" << "}"; };
        handlers.while_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "WHILE" << "}"; };
        handlers.while_statment_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "WHILE_STATMENT" << "}"; };
        handlers.function_syntax_node = [ &s ]( const ISyntaxNodeSP& ) { s << "{" << "FUNCTION" << "}"; };
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


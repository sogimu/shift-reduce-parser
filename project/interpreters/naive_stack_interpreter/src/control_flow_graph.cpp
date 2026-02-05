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
#include "make_shallow_syntax_node_copy.h"
#include "is_last_nodes.h"
#include "function_store.h"

ControlFlowGraph::ControlFlowGraph( const ISyntaxNodeSP& cfg_root )
    : mRoot{ cfg_root }
{

}

ControlFlowGraph::ControlFlowGraph( const AbstractSyntaxTree& ast )
{
     auto create_root = []( const ISyntaxNodeSP& source_node ) -> ISyntaxNodeSP
      {
         const auto& target_node = make_shallow_copy( source_node );
         return target_node;
      };
   
     auto create_node_pre_func = [ ]( const std::vector< ISyntaxNodeSP >& source_stack,
                                                                   const std::vector< std::pair<ISyntaxNodeSP, std::list<ISyntaxNodeSP>::iterator> >& target_stack )
      {
         bool call_post_func = true;   

         const auto& source_node = *source_stack.rbegin();
         const auto& [target_node_parent, it] = *target_stack.rbegin();
         
         const auto& target_node = make_shallow_copy( source_node );
         if( IsLastNodesIs< StatmentSyntaxNode >( source_stack ) )
         {
           call_post_func = false;
           return std::make_tuple(target_node_parent, call_post_func, it);
             
         }

         auto new_parent_target_node = target_node_parent->add_back( target_node );
         call_post_func = false;
         return std::make_tuple(new_parent_target_node, call_post_func, new_parent_target_node->end());
      };
      
     auto create_node_on_post_func = []( const std::vector< ISyntaxNodeSP >& source_stack,
                                  const std::vector< std::pair<ISyntaxNodeSP, std::list<ISyntaxNodeSP>::iterator> >& target_stack )
     {
     };
  
     auto get_children_reverse_iterators = []( const ISyntaxNodeSP& node )
         -> std::pair< std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator >, std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator > >
      { return { node->rbegin(), node->rend() }; };

     const auto& transformed_tree = create_tree_from1< ISyntaxNodeSP, ISyntaxNodeSP >(
         ast.root(),
         create_root,
         create_node_pre_func,
         create_node_on_post_func,
         get_children_reverse_iterators
     );

     // Transform IfStatmentSyntaxNode, WhileStatmentSyntaxNode, FunctionCallSyntaxNode 
     FunctionStore function_store;
     iterative_dfs3<ISyntaxNodeSP>(
         transformed_tree,
         [ &function_store ]( const std::vector<ISyntaxNodeSP>& stack ) -> bool
         {
            auto it = stack.rbegin();
            const auto& node = *it;
            std::advance( it, 1 );
            const auto& parent_it = *it;
            const auto& parent_of_statment = *it;
            
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.scope_statment_syntax_node =
               [ &function_store ]( const ScopeSyntaxNodeSP& /* scope */ )
            {
               // create scope in a VaribleStore
               function_store.pushScope();
               // std::cout << "Scope begin" << std::endl;
            };
            handlers.function_statment_syntax_node =
               [ &function_store ]( const FunctionStatmentSyntaxNodeSP& function_statment )
            {
              const auto& function_name = function_statment->name();
              const auto& arguments_number = function_statment->Children().size() - 2;
              function_store.insert( { function_name, arguments_number }, function_statment );
            };
            const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
            node->accept( visitor );
            return false;
         },
         [ &function_store ]( [[maybe_unused]] const std::vector<ISyntaxNodeSP>& stack )
         {
            auto it = stack.rbegin();
            const auto& node = *it;
            std::advance( it, 1 );
            const auto& parent_it = *it;
            const auto& parent_of_statment = *it;
            
            SyntaxNodeEmptyVisitor::Handlers handlers;
            handlers.scope_statment_syntax_node =
               [ &function_store ]( const ScopeSyntaxNodeSP& /* scope */ )
            {
               function_store.popScope();
            };
            const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
            node->accept( visitor );
            
            if( IsNode< IfStatmentSyntaxNode >( node ) )
            {
               const auto& condition = node->operator[](0);
               
                if( auto if_statment_it = std::find( parent_of_statment->begin(), parent_of_statment->end(), node );
                    if_statment_it != parent_of_statment->end() )
                {
                   parent_of_statment->insert(if_statment_it, condition);          
                }
               node->remove(0);
            }
            else if( IsNode< WhileStatmentSyntaxNode >( node ) )
            {
               const auto& condition = node->operator[](0);
               const auto& scope = node->operator[](1);
               node->remove(1);
                std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens;
                std::vector<ISyntaxNodeSP> scope_expressions{ scope, node };
                const auto& scope_statment = std::make_shared<ScopeSyntaxNode>(scope_expressions, scope_lexical_tokens);
                std::vector< LexicalTokens::LexicalToken > if_lexical_tokens;
                const auto& if_statment = std::make_shared<IfStatmentSyntaxNode>(condition, scope_statment, if_lexical_tokens);
                if_statment->remove(0);
                node->add_back(if_statment);
            }
            else if( IsNode< FunctionCallSyntaxNode >( node ) )
            {
               const auto& function_call = std::dynamic_pointer_cast< FunctionCallSyntaxNode >(node);
               auto argument_index = node->Children().size()-1;
               
              std::vector< LexicalTokens::LexicalToken > scope_lexical_tokens;
              std::vector<ISyntaxNodeSP> scope_expressions;
        
              const auto& function_call_arguments = function_call->arguments();
              
              const auto& function_statment = function_store[ { function_call->name(), function_call_arguments.size() } ]; 
              
              const auto& function_statment_arguments = function_statment->arguments();
 
              for( auto index = 0; index < function_call_arguments.size(); ++index )
              {
                 const auto& function_argument = function_statment_arguments[ index ];
                 const auto& call_argument = function_call_arguments[ index ];
                  
                  LexicalTokens::LexicalToken argument_lexical_token;
                  const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( function_argument, call_argument, argument_lexical_token, VaribleAssigmentStatmentSyntaxNode::Context::LOCAL );
                  scope_expressions.push_back( varible_assigment );
              }

               // for( const auto& argument : function_call_arguments )
               // {
               //    std::vector< LexicalTokens::LexicalToken > argument_lexical_tokens;
               //    function_statment->
               //    const auto& varible_assigment = std::make_shared< VaribleAssigmentStatmentSyntaxNode >( name, argument, argument_lexical_tokens );
               //    scope_expressions.push_back( varible_assigment );
               // }
               for( int i=node->Children().size()-1; i>=0; --i )
               {
                  node->remove(i);
                  // --argument_index;
               }
                const auto& scope_statment = std::make_shared<ScopeSyntaxNode>(scope_expressions, scope_lexical_tokens);
               node->add_back(scope_statment) ;
            }
         },
         get_children_reverse_iterators );

     mRoot = transformed_tree;
}

ISyntaxNodeSP ControlFlowGraph::root() const
{
  return mRoot;
}

bool ControlFlowGraph::operator==( const ControlFlowGraph& cfg ) const
{
  return ::equal( cfg.mRoot, mRoot );
}

std::string ControlFlowGraph::to_string() const
{
  return ::to_string( mRoot );
}


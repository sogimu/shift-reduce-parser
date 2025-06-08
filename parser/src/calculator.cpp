#include "calculator.h"

#include "gmock/gmock.h"
#include "is_last_nodes.h"
// #include "nonterminals/division/division_syntax_node.h"
#include "nonterminals/bin_expr_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
// #include "nonterminals/multiply/multiply_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"
#include "nonterminals/scope_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "terminals/if_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "lexical_tokens.h"
#include "syntax_tree.h"
#include "utils.h"
#include "varible_store.h"
#include "function_store.h"
#include "i_syntax_node.h"
#include "make_deep_syntax_node_copy.h"
#include "make_shallow_syntax_node_copy.h"

#include <functional>
#include <iostream>
#include <iterator>
#include <memory>
#include <optional>
#include <string>
#include <vector>

struct FunctionCallMeta
{
   ISyntaxNodeSP function;
   std::vector< ISyntaxNodeSP > arguments;
};

double Calculator::solve( const std::string& expression ) const
{
   LexicalTokens lexical_tokens( expression );
   SyntaxTree syntax_tree( lexical_tokens );

   std::map< std::string, FunctionCallMeta > function_by_name;

   ISyntaxNodeSP pre_func_subtree_ignore = nullptr;
   std::list<ISyntaxNodeSP>::iterator insert_it;

   std::cout << syntax_tree.to_string() << std::endl;
   const auto& transformed_tree = create_tree_from1< ISyntaxNodeSP, ISyntaxNodeSP >(
      syntax_tree.root(),
      []( const ISyntaxNodeSP& source_node ) -> ISyntaxNodeSP
      {
         const auto& target_node = make_shallow_copy( source_node );
         return target_node;
      },
      [ &function_by_name, &pre_func_subtree_ignore, &insert_it ]( const std::vector< ISyntaxNodeSP >& source_stack,
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
      [&pre_func_subtree_ignore]( const std::vector< ISyntaxNodeSP >& source_stack,
                                  const std::vector< std::pair<ISyntaxNodeSP, std::list<ISyntaxNodeSP>::iterator> >& target_stack )
      {
         const auto& source_node_wrapper = *source_stack.rbegin();
         const auto& [target_node_parent_wrapper, it] = *target_stack.rbegin();
         const auto& target_node = make_shallow_copy( source_node_wrapper );
         std::optional< ISyntaxNodeSP > new_parent_target_node = target_node_parent_wrapper;

         // if( source_node_wrapper.get() == pre_func_subtree_ignore )
         //    pre_func_subtree_ignore = {};
         target_node_parent_wrapper->insert( it, target_node );
      },
      []( const ISyntaxNodeSP& node )
         -> std::pair< std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator >, std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator > >
      { return { node->rbegin(), node->rend() }; } );
   SyntaxTree cfg{ transformed_tree };
   std::cout << cfg.to_string() << std::endl;

   int result = 0;

   VaribleStore varible_store;
   FunctionStore function_store;
   std::deque< double > argument_stack;
   std::deque< FunctionCallSyntaxNodeSP > function_call_stack;

   iterative_managed_dfs(
      cfg.root(),
      [ &varible_store, &function_store, &function_call_stack, &argument_stack ]( const ISyntaxNodeSP& node, StackDFS< ISyntaxNodeSP >& stack_dfs )
      {
         auto children = node->Children();
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.scope_statment_syntax_node =
            [ &varible_store, &function_store ]( const ScopeSyntaxNodeSP& /* scope */ )
         {
            // create scope in a VaribleStore
            varible_store.pushScope();
            function_store.pushScope();
            // std::cout << "Scope begin" << std::endl;
         },
         handlers.if_statment_syntax_node = [ &children, &argument_stack ]( const IfStatmentSyntaxNodeSP& if_statment )
         {
            // const auto& condition = if_statment->conditional_expression();
            auto condition_result = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            if( condition_result )
            {
               const auto& true_scope = if_statment->true_scope();
               children = std::list< ISyntaxNodeSP >{ true_scope };
            }
            else
            {
               children = {};
            }
            // else
            // {
            //    const auto& false_scope = if_statment->false_scope();
            //    children = std::vector< ISyntaxNodeSP >{ false_scope };
            // }
         };
         handlers.while_statment_syntax_node = []( const WhileStatmentSyntaxNodeSP& /* while_expression */ )
         {
            // varible_store.print();
            // const auto& condition = while_expression->conditional_expression();
            // if( HandleConditionExpression( varible_store, condition ) )
            {
               //       const auto& scope = while_expression->scope();
               //       children = std::vector< ISyntaxNodeSP >{ scope, while_expression };
            }
            //    else
            //    {
            // children = {};
            //    }
         };
         handlers.function_statment_syntax_node = [ &children ]( const FunctionStatmentSyntaxNodeSP& /* function */ )
         {
            // const auto& function_name = function->name();
            // const auto& arguments_number = function->Children().size() - 2;
            // function_store.insert( { function_name, arguments_number }, function );
            children = {};
         };
         handlers.function_call_syntax_node = [ &function_call_stack ]( const FunctionCallSyntaxNodeSP& function_call )
         { function_call_stack.emplace_back( function_call ); };
         handlers.return_statment_syntax_node = [ &stack_dfs, &function_call_stack, &argument_stack ]( const ReturnStatmentSyntaxNodeSP& /* return_statment */ )
         {
            auto result = argument_stack.back();
            // argument_stack.pop_back();
            stack_dfs.popUntil( function_call_stack.back() );

            std::cout << "return: " << std::to_string( result ) << std::endl;
         };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
         stack_dfs.push( children );
         return children;
      },
      [ &varible_store, &function_store, &argument_stack, &function_call_stack ]( const ISyntaxNodeSP& node )
      {
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.f_syntax_node = [ &argument_stack ]( const FSyntaxNodeSP& node )
         {
            std::cout << "f = " << std::to_string( node->value() ) << std::endl;
            argument_stack.push_back( node->value() );
         };
         handlers.varible_syntax_node = [ &argument_stack, &varible_store ]( const VaribleSyntaxNodeSP& varible )
         {
            const auto& value = varible_store[ varible->name() ];
            std::cout << "Read " << varible->name() << " .Value is " << std::to_string( value ) << std::endl;
            varible_store.print();
            // std::cout << "varible " + varible->name() + "(" << std::to_string( value ) << ")" << std::endl;
            argument_stack.push_back( value );
         };
         handlers.bin_expr_syntax_node = [ &argument_stack ]( const BinExprSyntaxNodeSP& node )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            if( node->type() == BinExprSyntaxNode::Type::Addition )
            {
              auto result = lhs + rhs;
              std::cout << std::to_string( lhs ) << " + " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Substruction )
            {
              auto result = lhs - rhs;
              std::cout << std::to_string( lhs ) << " - " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Multiply )
            {
              auto result = lhs * rhs;
              std::cout << std::to_string( lhs ) << " * " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
            else if( node->type() == BinExprSyntaxNode::Type::Division )
            {
              auto result = lhs / rhs;
              std::cout << std::to_string( lhs ) << " / " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
              argument_stack.push_back( result );
            }
         };
         handlers.scope_statment_syntax_node = [ &varible_store, &function_store ]( const ScopeSyntaxNodeSP& /*  scope */ )
         {
            // delete scope in a VaribleStore
            varible_store.popScope();
            function_store.popScope();
            // argument_stack.clear();
            // std::cout << "Scope end" << std::endl;
         };
         handlers.print_statment_syntax_node = [ &argument_stack ]( const PrintStatmentSyntaxNodeSP& /* print_statment */ )
         {
            auto result = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            std::cout << "print: " << std::to_string( result ) << std::endl;
         };
         // handlers.conditional_expression_syntax_node = [ &argument_stack ]( const ConditionalExpressionSyntaxNodeSP& conditional_expression )
         // {
         //    auto rhs = argument_stack.back();
         //    if( !argument_stack.empty() )
         //       argument_stack.pop_back();
         //    auto lhs = argument_stack.back();
         //    if( !argument_stack.empty() )
         //       argument_stack.pop_back();
         //    // argument_stack.pop_back();
         //
         //    switch( conditional_expression->type() )
         //    {
         //    case ConditionalExpressionSyntaxNode::Type::LESS:
         //    {
         //       argument_stack.push_back( static_cast< int >( lhs < rhs ) );
         //    };
         //    break;
         //    case ConditionalExpressionSyntaxNode::Type::MORE:
         //    {
         //       argument_stack.push_back( static_cast< int >( lhs > rhs ) );
         //    };
         //    break;
         //    case ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL:
         //    {
         //       argument_stack.push_back( static_cast< int >( lhs <= rhs ) );
         //    };
         //    break;
         //    case ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL:
         //    {
         //       argument_stack.push_back( static_cast< int >( lhs >= rhs ) );
         //    };
         //    break;
         //    case ConditionalExpressionSyntaxNode::Type::EQUAL:
         //    {
         //       argument_stack.push_back( static_cast< int >( lhs == rhs ) );
         //    };
         //    break;
         //    }
         // };
         handlers.varible_assigment_statment_syntax_node = [ &varible_store, &argument_stack ]( const VaribleAssigmentStatmentSyntaxNodeSP& varible_assigment )
         {
            // const auto& source = varible_assigment->source();
            const auto& target = varible_assigment->target();
            const auto& target_name = target->value();
            const auto& value = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            std::string context;
            if( varible_assigment->context() == VaribleAssigmentStatmentSyntaxNode::Context::GLOBAL )
            {
               varible_store[ target_name ] = value;
               context = "Global";
            }
            else if( varible_assigment->context() == VaribleAssigmentStatmentSyntaxNode::Context::LOCAL )
            {
               varible_store.writeValueToLocalVarible( target_name, value );
               context = "Local";
            }
            std::cout << "Write " << target_name << " .Value is " << std::to_string( value ) << ". Context: " << context << std::endl;
            varible_store.print();
         };
         handlers.function_call_syntax_node = [ &function_call_stack ]( const FunctionCallSyntaxNodeSP& /* function_call */ ) { function_call_stack.pop_back(); };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
      } );

   return result;
}

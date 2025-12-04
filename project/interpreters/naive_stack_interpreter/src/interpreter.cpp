#include "interpreter.h"

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
#include "stack_machine.h"
#include "terminals/f_syntax_node.h"
#include "terminals/if_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "lexical_tokens.h"
#include "abstract_syntax_tree.h"
#include "control_flow_graph.h"
#include "utils.h"
#include "varible_store.h"
#include "function_store.h"
#include "i_syntax_node.h"

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "syntax_exception.hpp"

struct FunctionCallMeta
{
   ISyntaxNodeSP function;
   std::vector< ISyntaxNodeSP > arguments;
};

double Interpreter::eval( const std::string& expression ) const
{
   LexicalTokens lexical_tokens( expression );
   AbstractSyntaxTree ast( lexical_tokens );
   std::cout << "== AST ==" << std::endl;
   std::cout << ast << std::endl;

   ControlFlowGraph cfg{ ast };
   std::cout << "== CFG ==" << std::endl;
   std::cout << cfg << std::endl;

   std::cout << "== Execution ==" << std::endl;
   int result = 0;
   
   StackMachine stack_machine{ cfg };

   std::map< std::string, FunctionCallMeta > function_by_name;

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
            auto s = argument_stack;
            (void) s;
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
         handlers.name_syntax_node = [ &argument_stack, &varible_store ]( const NameSyntaxNodeSP& varible )
         {
            const auto& value = varible_store[ varible->value() ];
            std::cout << "Read " << varible->value() << " .Value is " << std::to_string( value ) << std::endl;
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
            else if( node->type() == BinExprSyntaxNode::Type::Equal )
            {
              auto result = lhs == rhs;
              std::cout << std::to_string( lhs ) << " == " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
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
            auto s = argument_stack;
            (void) s;
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

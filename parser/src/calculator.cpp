#include "calculator.h"

#include "gmock/gmock.h"
#include "is_last_nodes.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/division/division_syntax_node.h"
#include "nonterminals/expression_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/multiply/multiply_syntax_node.h"
#include "nonterminals/return_expression_syntax_node.h"
#include "nonterminals/scope_syntax_node.h"
#include "nonterminals/varible_assigment_syntax_node.h"
#include "nonterminals/varible_syntax_node.h"
#include "nonterminals/while_expression_syntax_node.h"
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

// int HandleComputationalExpression( const VaribleStore& varible_store, const ComputationalExpressionSyntaxNodeSP& expression )
// {
//    std::unordered_map< ISyntaxNodeSP, int > syntax_node_value_by_syntax_node;
//    iterative_dfs< ISyntaxNodeSP >(
//       expression, [ /* &varible_store, &syntax_node_value_by_syntax_node */ ]( const ISyntaxNodeSP& /* node */ ) -> bool { return false; },
//       [ &varible_store, &syntax_node_value_by_syntax_node ]( const ISyntaxNodeSP& node )
//       {
//          match( node,
//                 {
//                    .f_syntax_node = [ &syntax_node_value_by_syntax_node ]( const FSyntaxNodeSP& node ) { syntax_node_value_by_syntax_node[ node ] = node->value(); },
//                    .addition_syntax_node =
//                       [ &syntax_node_value_by_syntax_node ]( const AdditionSyntaxNodeSP& node )
//                    {
//                       const auto& children = node->Children();
//                       auto it = children.begin();
//                       int result = syntax_node_value_by_syntax_node[ *it ];
//                       ++it;
//                       for( ; it != children.end(); ++it )
//                       {
//                          result += syntax_node_value_by_syntax_node[ *it ];
//                       }
//                       syntax_node_value_by_syntax_node[ node ] = result;
//                    },
//                    .subtraction_syntax_node =
//                       [ &syntax_node_value_by_syntax_node ]( const SubtractionSyntaxNodeSP& node )
//                    {
//                       const auto& children = node->Children();
//                       auto it = children.begin();
//                       int result = syntax_node_value_by_syntax_node[ *it ];
//                       ++it;
//                       for( ; it != children.end(); ++it )
//                       {
//                          result -= syntax_node_value_by_syntax_node[ *it ];
//                       }
//                       syntax_node_value_by_syntax_node[ node ] = result;
//                    },
//                    .multiply_syntax_node =
//                       [ &syntax_node_value_by_syntax_node ]( const MultiplySyntaxNodeSP& node )
//                    {
//                       const auto& children = node->Children();
//                       auto it = children.begin();
//                       int result = syntax_node_value_by_syntax_node[ *it ];
//                       ++it;
//                       for( ; it != children.end(); ++it )
//                       {
//                          result *= syntax_node_value_by_syntax_node[ *it ];
//                       }
//                       syntax_node_value_by_syntax_node[ node ] = result;
//                    },
//                    .division_syntax_node =
//                       [ &syntax_node_value_by_syntax_node ]( const DivisionSyntaxNodeSP& node )
//                    {
//                       const auto& children = node->Children();
//                       auto it = children.begin();
//                       int result = syntax_node_value_by_syntax_node[ *it ];
//                       ++it;
//                       for( ; it != children.end(); ++it )
//                       {
//                          result /= syntax_node_value_by_syntax_node[ *it ];
//                       }
//                       syntax_node_value_by_syntax_node[ node ] = result;
//                    },
//                    .computational_expression_syntax_node =
//                       [ &syntax_node_value_by_syntax_node ]( const ComputationalExpressionSyntaxNodeSP& node )
//                    {
//                       const auto& children = node->Children();
//                       auto it = children.begin();
//                       int result = syntax_node_value_by_syntax_node[ *it ];
//                       syntax_node_value_by_syntax_node[ node ] = result;
//                    },
//                    .name_syntax_node =
//                       [ &varible_store, &syntax_node_value_by_syntax_node ]( const NameSyntaxNodeSP& name )
//                    {
//                       const auto& value = varible_store[ name->value() ];
//                       syntax_node_value_by_syntax_node[ name ] = value;
//                    },
//                 } );
//       } );
//
//    int result = 0;
//
//    bool is_result_found = false;
//    iterative_dfs< ISyntaxNodeSP >( expression,
//                                    [ &is_result_found, &syntax_node_value_by_syntax_node, &result ]( const ISyntaxNodeSP& node ) -> bool
//                                    {
//                                       if( is_result_found == false && syntax_node_value_by_syntax_node.contains( node ) )
//                                       {
//                                          result = syntax_node_value_by_syntax_node[ node ];
//                                          is_result_found = true;
//                                          return true;
//                                       }
//
//                                       return false;
//                                    } );
//    return result;
// }

// bool HandleConditionExpression( const VaribleStore& varible_store, const ConditionalExpressionSyntaxNodeSP& condition )
// {
//    bool result;
//
//    const auto& first_apperand = condition->first_apperand();
//    const auto& second_apperand = condition->second_apperand();
//    const auto& type = condition->type();
//
//    const auto& first_apperand_value = HandleComputationalExpression( varible_store, first_apperand );
//    const auto& second_apperand_value = HandleComputationalExpression( varible_store, second_apperand );
//
//    switch( type )
//    {
//    case ConditionalExpressionSyntaxNode::Type::EQUAL:
//    {
//       result = first_apperand_value == second_apperand_value;
//    };
//    break;
//    case ConditionalExpressionSyntaxNode::Type::LESS:
//    {
//       result = first_apperand_value < second_apperand_value;
//    };
//    break;
//    case ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL:
//    {
//       result = first_apperand_value <= second_apperand_value;
//    };
//    break;
//    case ConditionalExpressionSyntaxNode::Type::MORE:
//    {
//       result = first_apperand_value > second_apperand_value;
//    };
//    break;
//    case ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL:
//    {
//       result = first_apperand_value >= second_apperand_value;
//    };
//    break;
//    }
//    return result;
// }

// void HandleExpression( const VaribleStore& varible_store, const ExpressionSyntaxNodeSP& expression )
// {
//    match( expression, { .computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& node )
//                         { /* int result =  */HandleComputationalExpression( varible_store, node ); } } );
// }

struct FunctionCallMeta
{
   ISyntaxNodeSP function;
   std::vector< ISyntaxNodeSP > arguments;
};

double Calculator::solve1( const std::string& expression ) const
{
   LexicalTokens lexical_tokens( expression );
   SyntaxTree syntax_tree( lexical_tokens );

   std::map< std::string, FunctionCallMeta > function_by_name;

   std::cout << syntax_tree.to_string() << std::endl;
   const auto& transformed_tree = create_tree_from1< ISyntaxNodeSP, ISyntaxNodeSP >(
      syntax_tree.root(),
      []( const ISyntaxNodeSP& source_node ) -> ISyntaxNodeSP
      {
         const auto& target_node = make_shallow_copy( source_node );
         return target_node;
      },
      [ &function_by_name ]( const std::vector< std::reference_wrapper< const ISyntaxNodeSP > >& source_stack,
                             const std::vector< std::reference_wrapper< ISyntaxNodeSP > >& target_stack ) -> std::optional< std::reference_wrapper< ISyntaxNodeSP > >
      {
         std::optional< std::reference_wrapper< ISyntaxNodeSP > > new_parent_target_node;
         const auto& source_node = *source_stack.rbegin();
         auto& taget_node_parent = target_stack.rbegin()->get();
         const auto& target_node = make_shallow_copy( source_node );

         if( IsLastNodesIs< VaribleAssigmentSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            // std::advance( it, 1 );
            new_parent_target_node = it->get()->add_back( target_node );
         }
         else if( IsLastNodesIs< VaribleAssigmentSyntaxNode, VaribleSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            const auto& varible_assigment = it->get();
            std::advance( it, 1 );
            auto& parent_of_varible_assigment = it->get();
            if( auto varible_assigment_it = std::find( parent_of_varible_assigment->begin(), parent_of_varible_assigment->end(), varible_assigment );
                varible_assigment_it != parent_of_varible_assigment->end() )
            {
               if( auto inserted_node_it = parent_of_varible_assigment->insert( varible_assigment_it, target_node );
                   inserted_node_it != parent_of_varible_assigment->end() )
               {
                  new_parent_target_node = *inserted_node_it;
               }
            }
         }
         else if( IsLastNodesIs< VaribleAssigmentSyntaxNode, ComputationalExpressionSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            const auto& varible_assigment = it->get();
            std::advance( it, 1 );
            auto& parent_of_varible_assigment = it->get();
            if( auto varible_assigment_it = std::find( parent_of_varible_assigment->begin(), parent_of_varible_assigment->end(), varible_assigment );
                varible_assigment_it != parent_of_varible_assigment->end() )
            {
               if( auto inserted_node_it = parent_of_varible_assigment->insert( varible_assigment_it, target_node );
                   inserted_node_it != parent_of_varible_assigment->end() )
               {
                  new_parent_target_node = *inserted_node_it;
               }
            }
         }
         else if( IsLastNodesIs< IfExpressionSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            // std::advance( it, 1 );
            new_parent_target_node = it->get()->add_back( target_node );
         }
         else if( IsLastNodesIs< IfExpressionSyntaxNode, ConditionalExpressionSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            const auto& if_node = it->get();
            std::advance( it, 1 );
            auto& parent_of_if = it->get();
            if( auto if_it = std::find( parent_of_if->begin(), parent_of_if->end(), if_node ); if_it != parent_of_if->end() )
            {
               auto it = parent_of_if->insert( if_it, target_node );
               new_parent_target_node = *it;
            }
         }
         else if( IsLastNodesIs< WhileExpressionSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            // std::advance( it, 1 );
            new_parent_target_node = it->get()->add_back( target_node );
         }
         else if( IsLastNodesIs< WhileExpressionSyntaxNode, ScopeSyntaxNode >( source_stack ) )
         {
            const auto& if_expression = std::make_shared< IfExpressionSyntaxNode >();
            const auto& new_if_expression = taget_node_parent->add_back( if_expression );
            const auto& scope_expression = std::make_shared< ScopeSyntaxNode >();
            const auto& new_scope_expression = new_if_expression->add_back( scope_expression );
            new_parent_target_node = new_scope_expression->add_back( target_node );
            const auto& while_expression = taget_node_parent;
            scope_expression->add_back( while_expression );
         }
         else if( IsLastNodesIs< ScopeSyntaxNode >( source_stack ) )
         {
            auto it = target_stack.rbegin();
            // std::advance( it, 1 );
            new_parent_target_node = it->get()->add_back( target_node );
         }
         else if( IsLastNodesIs< FunctionSyntaxNode >( source_stack ) )
         {
            const auto& function_syntax_node = std::dynamic_pointer_cast< FunctionSyntaxNode >( target_node );
            function_by_name[ function_syntax_node->name() ] = FunctionCallMeta{ function_syntax_node, {} };
            new_parent_target_node = taget_node_parent->add_back( target_node );
         }
         else if( IsLastNodesIs< FunctionSyntaxNode, NameSyntaxNode >( source_stack ) )
         {
            const auto& name_syntax_node = std::dynamic_pointer_cast< NameSyntaxNode >( target_node );
            auto target_it = target_stack.rbegin();
            const auto& function_node = std::dynamic_pointer_cast< FunctionSyntaxNode >( target_it->get() );
            auto& meta = function_by_name[ function_node->name() ];
            meta.arguments.push_back( name_syntax_node );
            new_parent_target_node = taget_node_parent->add_back( target_node );
            // new_parent_target_node = {};
         }
         else if( IsLastNodesIs< FunctionCallSyntaxNode >( source_stack ) )
         {
            auto& function_call = target_node;
            new_parent_target_node = taget_node_parent->add_back( function_call );
            const auto& scope_expression = std::make_shared< ScopeSyntaxNode >();
            new_parent_target_node = function_call->add_back( scope_expression );
            // new_parent_target_node = taget_node_parent->add_back( scope_expression );
            const auto& function_call_syntax_node = std::dynamic_pointer_cast< FunctionCallSyntaxNode >( function_call );
            if( const auto& function_info_it = function_by_name.find( function_call_syntax_node->name() ); function_info_it != function_by_name.end() )
            {
               const auto& function = std::dynamic_pointer_cast< FunctionSyntaxNode >( function_info_it->second.function );
               scope_expression->add_back( function->scope() );
            }
         }
         else if( IsLastNodesIs< FunctionCallSyntaxNode, VaribleSyntaxNode >( source_stack ) ||
                  IsLastNodesIs< FunctionCallSyntaxNode, ComputationalExpressionSyntaxNode >( source_stack ) )
         {
            auto source_it = source_stack.rbegin();
            std::advance( source_it, 1 );
            const auto& function_call_node = std::dynamic_pointer_cast< FunctionCallSyntaxNode >( source_it->get() );
            if( auto argument_it = std::find( function_call_node->begin(), function_call_node->end(), source_node.get() ); argument_it != function_call_node->end() )
            {
               auto call_argument_index = std::distance( function_call_node->begin(), argument_it );
               if( auto function_info_it = function_by_name.find( function_call_node->name() ); function_info_it != function_by_name.end() )
               {
                  const auto& function = std::dynamic_pointer_cast< FunctionSyntaxNode >( function_info_it->second.function );
                  auto function_argument_name_it = function->begin();
                  std::advance( function_argument_name_it, call_argument_index );
                  const auto& argument_name_node = std::dynamic_pointer_cast< NameSyntaxNode >( *function_argument_name_it );
                  const auto& varible_assigment_syntax_node =
                     std::make_shared< VaribleAssigmentSyntaxNode >( VaribleAssigmentSyntaxNode( VaribleAssigmentSyntaxNode::Context::LOCAL ) );
                  varible_assigment_syntax_node->add_back( argument_name_node );
                  auto scope_it = taget_node_parent->end();
                  std::advance( scope_it, 1 );
                  new_parent_target_node = *taget_node_parent->insert( scope_it, target_node );
                  taget_node_parent->insert( scope_it, varible_assigment_syntax_node );
                  *scope_it;
               }
            }
         }

         return new_parent_target_node;
      },
      []( const std::vector< std::reference_wrapper< const ISyntaxNodeSP > >& source_stack,
          const std::vector< std::reference_wrapper< ISyntaxNodeSP > >& target_stack ) -> std::optional< std::reference_wrapper< ISyntaxNodeSP > >
      {
         std::optional< std::reference_wrapper< ISyntaxNodeSP > > new_parent_target_node;
         const auto& source_node = *source_stack.rbegin();
         const auto& taget_node_parent = target_stack.rbegin()->get();
         const auto& target_node = make_shallow_copy( source_node );

         if( IsLastNodesIs< ExpressionSyntaxNode >( source_stack ) )
         {
            return new_parent_target_node;
         }
         else if( IsLastNodesIs< ComputationalExpressionSyntaxNode >( source_stack ) )
         {
            return new_parent_target_node;
         }
         new_parent_target_node = taget_node_parent->add_back( target_node );

         return new_parent_target_node;
      },
      []( const ISyntaxNodeSP& node )
         -> std::pair< std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator >, std::reverse_iterator< std::list< ISyntaxNodeSP >::iterator > >
      { return { node->rbegin(), node->rend() }; } /* } */ );
   SyntaxTree cfg{ transformed_tree };
   std::cout << cfg.to_string() << std::endl;

   // return 0.0;

   int result = 0;

   VaribleStore varible_store;
   FunctionStore function_store;
   std::deque< double > argument_stack;
   std::deque< FunctionCallSyntaxNodeSP > function_call_stack;

   iterative_managed_dfs(
      /* syntax_tree */
      cfg.root(),
      [ &varible_store, &function_store, &function_call_stack, &argument_stack ]( const ISyntaxNodeSP& node, StackDFS< ISyntaxNodeSP >& stack_dfs )
      {
         auto children = node->Children();
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.scope_syntax_node =
            [ &varible_store, &function_store /* , &node */ ]( const ScopeSyntaxNodeSP& /* scope */ )
         {
            // create scope in a VaribleStore
            varible_store.pushScope();
            function_store.pushScope();
            // std::cout << "Scope begin" << std::endl;
         },
         handlers.if_expression_syntax_node = [ /* &varible_store,  */ &children, /* &node,  */ &argument_stack ]( const IfExpressionSyntaxNodeSP& if_expression )
         {
            // const auto& condition = if_expression->conditional_expression();
            auto condition_result = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            if( condition_result )
            {
               const auto& true_scope = if_expression->true_scope();
               children = std::list< ISyntaxNodeSP >{ true_scope };
            }
            else
            {
               children = {};
            }
            // else
            // {
            //    const auto& false_scope = if_expression->false_scope();
            //    children = std::vector< ISyntaxNodeSP >{ false_scope };
            // }
         };
         handlers.while_expression_syntax_node = [ &varible_store, &children, &node ]( const WhileExpressionSyntaxNodeSP& while_expression )
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
         handlers.function_syntax_node = [ /* &varible_store,  */ &function_store, /* &node,  */ &children ]( const FunctionSyntaxNodeSP& function )
         {
            // const auto& function_name = function->name();
            // const auto& arguments_number = function->Children().size() - 2;
            // function_store.insert( { function_name, arguments_number }, function );
            children = {};
         };
         handlers.function_call_syntax_node = [ /* &varible_store,  */ &function_store, &children, &function_call_stack ]( const FunctionCallSyntaxNodeSP& function_call )
         { function_call_stack.emplace_back( function_call ); };
         handlers.return_expression_syntax_node = [ &stack_dfs, &argument_stack, &function_call_stack ]( const ReturnExpressionSyntaxNodeSP& return_expression )
         {
            const auto& d = argument_stack;
            auto result = argument_stack.back();
            // argument_stack.pop_back();
            stack_dfs.popUntil( function_call_stack.back() );

            // std::cout << "return: " << std::to_string( result ) << std::endl;
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
            // std::cout << "f = " << std::to_string( node->value() ) << std::endl;
            argument_stack.push_back( node->value() );
         };
         handlers.varible_syntax_node = [ &argument_stack, &varible_store ]( const VaribleSyntaxNodeSP& varible )
         {
            const auto& value = varible_store[ varible->name() ];
            // std::cout << "Read " << varible->name() << " .Value is " << std::to_string( value ) << std::endl;
            // varible_store.print();
            // std::cout << "varible " + varible->name() + "(" << std::to_string( value ) << ")" << std::endl;
            argument_stack.push_back( value );
         };
         handlers.addition_syntax_node = [ &argument_stack ]( const AdditionSyntaxNodeSP& node )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto result = lhs + rhs;
            // std::cout << std::to_string( lhs ) << " + " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
            argument_stack.push_back( result );
         };
         handlers.subtraction_syntax_node = [ &argument_stack ]( const SubtractionSyntaxNodeSP& node )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto result = lhs - rhs;
            // std::cout << std::to_string( lhs ) << " - " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
            argument_stack.push_back( result );
         };
         handlers.multiply_syntax_node = [ &argument_stack ]( const MultiplySyntaxNodeSP& node )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto result = lhs * rhs;
            // std::cout << std::to_string( lhs ) << " * " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
            argument_stack.push_back( result );
         };
         handlers.division_syntax_node = [ &argument_stack ]( const DivisionSyntaxNodeSP& node )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto result = lhs / rhs;
            // std::cout << std::to_string( lhs ) << " / " << std::to_string( rhs ) << " = " << std::to_string( result ) << std::endl;
            argument_stack.push_back( result );
         };
         handlers.scope_syntax_node = [ &varible_store, &function_store, &argument_stack /* , &node */ ]( const ScopeSyntaxNodeSP& /*  scope */ )
         {
            // delete scope in a VaribleStore
            varible_store.popScope();
            function_store.popScope();
            // argument_stack.clear();
            // std::cout << "Scope end" << std::endl;
         };
         handlers.print_expression_syntax_node = [ /* &varible_store, &node,  */ &argument_stack ]( const PrintExpressionSyntaxNodeSP& /* print_expression */ )
         {
            auto result = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            std::cout << "print: " << std::to_string( result ) << std::endl;
         };
         handlers.conditional_expression_syntax_node =
            [ /* &varible_store, &node,  */ &argument_stack ]( const ConditionalExpressionSyntaxNodeSP& conditional_expression )
         {
            auto rhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            auto lhs = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            // argument_stack.pop_back();

            switch( conditional_expression->type() )
            {
            case ConditionalExpressionSyntaxNode::Type::LESS:
            {
               argument_stack.push_back( static_cast< int >( lhs < rhs ) );
            };
            break;
            case ConditionalExpressionSyntaxNode::Type::MORE:
            {
               argument_stack.push_back( static_cast< int >( lhs > rhs ) );
            };
            break;
            case ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL:
            {
               argument_stack.push_back( static_cast< int >( lhs <= rhs ) );
            };
            break;
            case ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL:
            {
               argument_stack.push_back( static_cast< int >( lhs >= rhs ) );
            };
            break;
            case ConditionalExpressionSyntaxNode::Type::EQUAL:
            {
               argument_stack.push_back( static_cast< int >( lhs == rhs ) );
            };
            break;
            }
            // std::cout << "condition: " << ;std::to_string( argument_stack.back() ) << std::endl;
         };
         handlers.varible_assigment_syntax_node = [ &varible_store, /* &node,  */ &argument_stack ]( const VaribleAssigmentSyntaxNodeSP& varible_assigment )
         {
            // const auto& source = varible_assigment->source();
            const auto& target = varible_assigment->target();
            const auto& target_name = target->value();
            const auto& value = argument_stack.back();
            if( !argument_stack.empty() )
               argument_stack.pop_back();
            std::string context;
            if( varible_assigment->context() == VaribleAssigmentSyntaxNode::Context::GLOBAL )
            {
               varible_store[ target_name ] = value;
               context = "Global";
            }
            else if( varible_assigment->context() == VaribleAssigmentSyntaxNode::Context::LOCAL )
            {
               varible_store.writeValueToLocalVarible( target_name, value );
               context = "Local";
            }
            // std::cout << "Write " << target_name << " .Value is " << std::to_string( value ) << ". Context: " << context << std::endl;
            // varible_store.print();
            // std::cout << "varible " + target_name + " = " << std::to_string( value ) << std::endl;
         };
         handlers.function_call_syntax_node = [ &function_call_stack ]( const FunctionCallSyntaxNodeSP& function_call ) { function_call_stack.pop_back(); };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
      } );

   return result;
}

// double Calculator::solve( const std::string& /* expression */ ) const
// {
//    return 0;
//    // LexicalTokens lexical_tokens( expression );
//    // SyntaxTree syntax_tree( lexical_tokens );
//    //
//    // std::cout << syntax_tree.to_string() << std::endl;
//    //
//    // int result = 0;
//    //
//    // VaribleStore varible_store;
//    // FunctionStore function_store;
//    //
//    // iterative_managed_dfs(
//    //    syntax_tree.root(),
//    //    [ &varible_store, &function_store ]( const ISyntaxNodeSP& node ) -> std::optional< std::vector< ISyntaxNodeSP > >
//    //    {
//    //       std::optional< std::vector< ISyntaxNodeSP > > children = node->Children();
//    //
//    //       match( node, { .scope_syntax_node =
//    //                         [ &varible_store, &function_store, &node ]( const ScopeSyntaxNodeSP& scope )
//    //                      {
//    //                         // create scope in a VaribleStore
//    //                         auto& s = varible_store;
//    //                         varible_store.pushScope();
//    //                         function_store.pushScope();
//    //                      },
//    //                      .computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
//    //                      { int result = HandleComputationalExpression( varible_store, computational_expression ); },
//    //                      .print_expression_syntax_node =
//    //                         [ &varible_store, &node ]( const PrintExpressionSyntaxNodeSP& print_expression )
//    //                      {
//    //                         ISyntaxNodeSP next_scope;
//    //                         const auto& computational_expression = print_expression->computational_expression();
//    //                         const auto& result = HandleComputationalExpression( varible_store, computational_expression );
//    //                         std::cout << std::to_string( result ) << std::endl;
//    //                         return std::optional< std::vector< ISyntaxNodeSP > >{};
//    //                      },
//    //                      .varible_assigment_syntax_node =
//    //                         [ &varible_store, &node ]( const VaribleAssigmentSyntaxNodeSP& varible_assigment )
//    //                      {
//    //                         const auto& value_node = varible_assigment->operator[]( 1 );
//    //                         match( value_node, { .computational_expression_syntax_node =
//    //                                                 [ &varible_store, &varible_assigment ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
//    //                                              {
//    //                                                 const auto& value = HandleComputationalExpression( varible_store, computational_expression );
//    //                                                 varible_store[ varible_assigment->target()->value() ] = value;
//    //                                              },
//    //                                              .name_syntax_node = [ &varible_store, &varible_assigment ]( const NameSyntaxNodeSP& name )
//    //                                              { varible_store[ varible_assigment->target()->value() ] = varible_store[ name->value() ]; } } );
//    //                      },
//    //                      .if_expression_syntax_node =
//    //                         [ &varible_store, &children, &node ]( const IfExpressionSyntaxNodeSP& if_expression )
//    //                      {
//    //                         const auto& condition = if_expression->conditional_expression();
//    //                         if( HandleConditionExpression( varible_store, condition ) )
//    //                         {
//    //                            const auto& true_scope = if_expression->true_scope();
//    //                            children = std::vector< ISyntaxNodeSP >{ true_scope };
//    //                         }
//    //                         // else
//    //                         // {
//    //                         //    const auto& false_scope = if_expression->false_scope();
//    //                         //    children = std::vector< ISyntaxNodeSP >{ false_scope };
//    //                         // }
//    //                      },
//    //                      .while_expression_syntax_node =
//    //                         [ &varible_store, &children, &node ]( const WhileExpressionSyntaxNodeSP& while_expression )
//    //                      {
//    //                         const auto& condition = while_expression->conditional_expression();
//    //                         if( HandleConditionExpression( varible_store, condition ) )
//    //                         {
//    //                            const auto& scope = while_expression->scope();
//    //                            children = std::vector< ISyntaxNodeSP >{ scope, while_expression };
//    //                         }
//    //                         else
//    //                         {
//    //                            children = {};
//    //                         }
//    //                      },
//    //                      .function_syntax_node =
//    //                         [ &varible_store, &function_store, &node, &children ]( const FunctionSyntaxNodeSP& function )
//    //                      {
//    //                         const auto& function_name = std::dynamic_pointer_cast< NameSyntaxNode >( function->operator[]( 0 ) );
//    //                         const auto& arguments_number = function->Children().size() - 2;
//    //                         const auto& name = function_name->value();
//    //                         const auto& s = function_store;
//    //                         function_store.insert( { name, arguments_number }, function );
//    //                         children = {};
//    //                      },
//    //                      .function_call_syntax_node =
//    //                         [ &varible_store, &function_store, &children ]( const FunctionCallSyntaxNodeSP& function_call )
//    //                      {
//    //                         const auto& function_name = std::dynamic_pointer_cast< NameSyntaxNode >( function_call->operator[]( 0 ) );
//    //                         const auto& arguments_number = function_call->Children().size() - 1;
//    //                         const auto& name = function_name->value();
//    //                         const auto& function = function_store[ { name, arguments_number } ];
//    //                         if( !function )
//    //                         {
//    //                            throw std::runtime_error( "Can't call function '" + name + "'. There is no function definition!" );
//    //                         }
//    //                         std::vector< ISyntaxNodeSP > expressions;
//    //                         for( int i = 0; i < arguments_number; ++i )
//    //                         {
//    //                            const auto& argument_name = function->operator[]( i + 2 );
//    //                            const auto& argument_value = function_call->operator[]( i + 1 );
//    //                            const auto& an = std::dynamic_pointer_cast< NameSyntaxNode >( argument_name );
//    //                            const auto& av = std::dynamic_pointer_cast< NameSyntaxNode >( argument_value );
//    //                            const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >( av );
//    //                            const auto& varible_assigment_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( an, computational_expression );
//    //                            expressions.push_back( varible_assigment_syntax_node );
//    //                         }
//    //                         const auto& scope_for_arguments_assigments = std::make_shared< ScopeSyntaxNode >( expressions );
//    //                         children = std::vector< ISyntaxNodeSP >{ scope_for_arguments_assigments };
//    //                      } } );
//    //       return children;
//    //    },
//    //    [ &varible_store, &function_store ]( const ISyntaxNodeSP& node )
//    //    {
//    //       match( node, { .scope_syntax_node = [ &varible_store, &function_store, &node ]( const ScopeSyntaxNodeSP& scope )
//    //                      {
//    //                         // delete scope in a VaribleStore
//    //                         auto& s = varible_store;
//    //                         varible_store.popScope();
//    //                         function_store.popScope();
//    //                      } } );
//    //    } );
//    //
//    // return result;
// }

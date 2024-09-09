#include "calculator.h"

#include "division/division_syntax_node.h"
#include "multiply/multiply_syntax_node.h"
#include "syntax_node_empty_visitor.h"
#include "lexical_tokens.h"
#include "syntax_tree.h"
#include "utils.h"
#include "varible_store.h"
#include "function_store.h"

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

int HandleComputationalExpression( const VaribleStore& varible_store, const ComputationalExpressionSyntaxNodeSP& expression )
{
   std::unordered_map< ISyntaxNodeSP, int > syntax_node_value_by_syntax_node;
   iterative_dfs< ISyntaxNodeSP >(
      expression, [ &varible_store, &syntax_node_value_by_syntax_node ]( const ISyntaxNodeSP& node ) -> bool { return false; },
      [ &varible_store, &syntax_node_value_by_syntax_node ]( const ISyntaxNodeSP& node )
      {
         match( node,
                {
                   .f_syntax_node = [ &syntax_node_value_by_syntax_node ]( const FSyntaxNodeSP& node ) { syntax_node_value_by_syntax_node[ node ] = node->value(); },
                   .addition_syntax_node =
                      [ &syntax_node_value_by_syntax_node ]( const AdditionSyntaxNodeSP& node )
                   {
                      const auto& children = node->Children();
                      auto it = children.begin();
                      int result = syntax_node_value_by_syntax_node[ *it ];
                      ++it;
                      for( ; it != children.end(); ++it )
                      {
                         result += syntax_node_value_by_syntax_node[ *it ];
                      }
                      syntax_node_value_by_syntax_node[ node ] = result;
                   },
                   .subtraction_syntax_node =
                      [ &syntax_node_value_by_syntax_node ]( const SubtractionSyntaxNodeSP& node )
                   {
                      const auto& children = node->Children();
                      auto it = children.begin();
                      int result = syntax_node_value_by_syntax_node[ *it ];
                      ++it;
                      for( ; it != children.end(); ++it )
                      {
                         result -= syntax_node_value_by_syntax_node[ *it ];
                      }
                      syntax_node_value_by_syntax_node[ node ] = result;
                   },
                   .multiply_syntax_node =
                      [ &syntax_node_value_by_syntax_node ]( const MultiplySyntaxNodeSP& node )
                   {
                      const auto& children = node->Children();
                      auto it = children.begin();
                      int result = syntax_node_value_by_syntax_node[ *it ];
                      ++it;
                      for( ; it != children.end(); ++it )
                      {
                         result *= syntax_node_value_by_syntax_node[ *it ];
                      }
                      syntax_node_value_by_syntax_node[ node ] = result;
                   },
                   .division_syntax_node =
                      [ &syntax_node_value_by_syntax_node ]( const DivisionSyntaxNodeSP& node )
                   {
                      const auto& children = node->Children();
                      auto it = children.begin();
                      int result = syntax_node_value_by_syntax_node[ *it ];
                      ++it;
                      for( ; it != children.end(); ++it )
                      {
                         result /= syntax_node_value_by_syntax_node[ *it ];
                      }
                      syntax_node_value_by_syntax_node[ node ] = result;
                   },
                   .computational_expression_syntax_node =
                      [ &syntax_node_value_by_syntax_node ]( const ComputationalExpressionSyntaxNodeSP& node )
                   {
                      const auto& children = node->Children();
                      auto it = children.begin();
                      int result = syntax_node_value_by_syntax_node[ *it ];
                      syntax_node_value_by_syntax_node[ node ] = result;
                   },
                   .name_syntax_node =
                      [ &varible_store, &syntax_node_value_by_syntax_node ]( const NameSyntaxNodeSP& name )
                   {
                      const auto& value = varible_store[ name->value() ];
                      syntax_node_value_by_syntax_node[ name ] = value;
                   },
                } );
      } );

   int result = 0;

   bool is_result_found = false;
   iterative_dfs< ISyntaxNodeSP >( expression,
                                   [ &is_result_found, &syntax_node_value_by_syntax_node, &result ]( const ISyntaxNodeSP& node ) -> bool
                                   {
                                      if( is_result_found == false && syntax_node_value_by_syntax_node.contains( node ) )
                                      {
                                         result = syntax_node_value_by_syntax_node[ node ];
                                         is_result_found = true;
                                         return true;
                                      }

                                      return false;
                                   } );
   return result;
}

bool HandleConditionExpression( const VaribleStore& varible_store, const ConditionalExpressionSyntaxNodeSP& condition )
{
   bool result;

   const auto& first_apperand = condition->first_apperand();
   const auto& second_apperand = condition->second_apperand();
   const auto& type = condition->type();

   const auto& first_apperand_value = HandleComputationalExpression( varible_store, first_apperand );
   const auto& second_apperand_value = HandleComputationalExpression( varible_store, second_apperand );

   switch( type )
   {
   case ConditionalExpressionSyntaxNode::Type::EQUAL:
   {
      result = first_apperand_value == second_apperand_value;
   };
   break;
   case ConditionalExpressionSyntaxNode::Type::LESS:
   {
      result = first_apperand_value < second_apperand_value;
   };
   break;
   case ConditionalExpressionSyntaxNode::Type::LESS_OR_EQUAL:
   {
      result = first_apperand_value <= second_apperand_value;
   };
   break;
   case ConditionalExpressionSyntaxNode::Type::MORE:
   {
      result = first_apperand_value > second_apperand_value;
   };
   break;
   case ConditionalExpressionSyntaxNode::Type::MORE_OR_EQUAL:
   {
      result = first_apperand_value >= second_apperand_value;
   };
   break;
   }
   return result;
}

void HandleExpression( const VaribleStore& varible_store, const ExpressionSyntaxNodeSP& expression )
{
   match( expression, { .computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& node )
                        { int result = HandleComputationalExpression( varible_store, node ); } } );
}

double Calculator::solve( const std::string& expression ) const
{
   LexicalTokens lexical_tokens( expression );
   SyntaxTree syntax_tree( lexical_tokens );

   std::cout << syntax_tree.to_string() << std::endl;

   int result = 0;

   VaribleStore varible_store;
   FunctionStore function_store;

   iterative_managed_dfs(
      syntax_tree.root(),
      [ &varible_store, &function_store ]( const ISyntaxNodeSP& node ) -> std::optional< std::vector< ISyntaxNodeSP > >
      {
         std::optional< std::vector< ISyntaxNodeSP > > children = node->Children();

         match( node, { .scope_syntax_node =
                           [ &varible_store, &function_store, &node ]( const ScopeSyntaxNodeSP& scope )
                        {
                           // create scope in a VaribleStore
                           auto& s = varible_store;
                           varible_store.pushScope();
                           function_store.pushScope();
                        },
                        .computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
                        { int result = HandleComputationalExpression( varible_store, computational_expression ); },
                        .print_expression_syntax_node =
                           [ &varible_store, &node ]( const PrintExpressionSyntaxNodeSP& print_expression )
                        {
                           ISyntaxNodeSP next_scope;
                           const auto& computational_expression = print_expression->computational_expression();
                           const auto& result = HandleComputationalExpression( varible_store, computational_expression );
                           std::cout << std::to_string( result ) << std::endl;
                           return std::optional< std::vector< ISyntaxNodeSP > >{};
                        },
                        .varible_assigment_syntax_node =
                           [ &varible_store, &node ]( const VaribleAssigmentSyntaxNodeSP& varible_assigment )
                        {
                           const auto& value_node = varible_assigment->operator[]( 1 );
                           match( value_node, { .computational_expression_syntax_node =
                                                   [ &varible_store, &varible_assigment ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
                                                {
                                                   const auto& value = HandleComputationalExpression( varible_store, computational_expression );
                                                   varible_store[ varible_assigment->name() ] = value;
                                                },
                                                .name_syntax_node = [ &varible_store, &varible_assigment ]( const NameSyntaxNodeSP& name )
                                                { varible_store[ varible_assigment->name() ] = varible_store[ name->value() ]; } } );
                        },
                        .if_expression_syntax_node =
                           [ &varible_store, &children, &node ]( const IfExpressionSyntaxNodeSP& if_expression )
                        {
                           const auto& condition = if_expression->conditional_expression();
                           if( HandleConditionExpression( varible_store, condition ) )
                           {
                              const auto& true_scope = if_expression->true_scope();
                              children = std::vector< ISyntaxNodeSP >{ true_scope };
                           }
                           // else
                           // {
                           //    const auto& false_scope = if_expression->false_scope();
                           //    children = std::vector< ISyntaxNodeSP >{ false_scope };
                           // }
                        },
                        .while_expression_syntax_node =
                           [ &varible_store, &children, &node ]( const WhileExpressionSyntaxNodeSP& while_expression )
                        {
                           const auto& condition = while_expression->conditional_expression();
                           if( HandleConditionExpression( varible_store, condition ) )
                           {
                              const auto& scope = while_expression->scope();
                              children = std::vector< ISyntaxNodeSP >{ while_expression, scope };
                           }
                           else
                           {
                              children = {};
                           }
                        },
                        .function_syntax_node =
                           [ &varible_store, &function_store, &node, &children ]( const FunctionSyntaxNodeSP& function )
                        {
                           const auto& function_name = std::dynamic_pointer_cast< NameSyntaxNode >( function->operator[]( 0 ) );
                           const auto& arguments_number = function->Children().size() - 2;
                           const auto& name = function_name->value();
                           const auto& s = function_store;
                           function_store.insert( { name, arguments_number }, function );
                           children = {};
                        },
                        .function_call_syntax_node =
                           [ &varible_store, &function_store, &children ]( const FunctionCallSyntaxNodeSP& function_call )
                        {
                           const auto& function_name = std::dynamic_pointer_cast< NameSyntaxNode >( function_call->operator[]( 0 ) );
                           const auto& arguments_number = function_call->Children().size() - 1;
                           const auto& name = function_name->value();
                           const auto& function = function_store[ { name, arguments_number } ];

                           std::vector< ISyntaxNodeSP > expressions;
                           const auto& function_scope = function->scope();
                           expressions.push_back( function_scope );
                           for( int i = 0; i < arguments_number; ++i )
                           {
                              const auto& argument_name = function->operator[]( i + 2 );
                              const auto& argument_value = function_call->operator[]( i + 1 );
                              const auto& an = std::dynamic_pointer_cast< NameSyntaxNode >( argument_name );
                              const auto& av = std::dynamic_pointer_cast< NameSyntaxNode >( argument_value );
                              const auto& computational_expression = std::make_shared< ComputationalExpressionSyntaxNode >( av );
                              const auto& varible_assigment_syntax_node = std::make_shared< VaribleAssigmentSyntaxNode >( an, computational_expression );
                              expressions.push_back( varible_assigment_syntax_node );
                           }
                           const auto& scope_for_arguments_assigments = std::make_shared< ScopeSyntaxNode >( expressions );
                           children = std::vector< ISyntaxNodeSP >{ scope_for_arguments_assigments };
                        } } );
         return children;
      },
      [ &varible_store, &function_store ]( const ISyntaxNodeSP& node )
      {
         match( node, { .scope_syntax_node = [ &varible_store, &function_store, &node ]( const ScopeSyntaxNodeSP& scope )
                        {
                           // delete scope in a VaribleStore
                           auto& s = varible_store;
                           varible_store.popScope();
                           function_store.popScope();
                        } } );
      } );

   return result;
}

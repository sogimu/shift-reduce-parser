#include "calculator.h"

#include "lexical_tokens.h"
#include "syntax_node_empty_visitor.h"
#include "syntax_tree.h"
#include "utils.h"
#include "varible_store.h"

#include <functional>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <vector>

int HandleComputationalExpression( const VaribleStore& varible_store, const ComputationalExpressionSyntaxNodeSP& expression )
{
   int result = 0;

   std::unordered_map< ISyntaxNodeSP, int > syntax_node_value_by_syntax_node;
   iterative_dfs< ISyntaxNodeSP >(
      expression,
      [ &varible_store, &syntax_node_value_by_syntax_node ]( const ISyntaxNodeSP& node ) -> bool
      {
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.f_syntax_node = [ &syntax_node_value_by_syntax_node ]( const FSyntaxNodeSP& node ) { syntax_node_value_by_syntax_node[ node ] = node->value(); };
         handlers.name_syntax_node = [ &varible_store, &syntax_node_value_by_syntax_node ]( const NameSyntaxNodeSP& name )
         {
            const auto& value = varible_store[ name->value() ];
            syntax_node_value_by_syntax_node[ name ] = value;
         };

         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );

         return false;
      },
      [ &result, &syntax_node_value_by_syntax_node ]( const ISyntaxNodeSP& node )
      {
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.addition_syntax_node = [ &result, &syntax_node_value_by_syntax_node ]( const AdditionSyntaxNodeSP& node )
         {
            for( const auto& argument : node->Children() )
            {
               result += syntax_node_value_by_syntax_node[ argument ];
            }
         };
         handlers.subtraction_syntax_node = [ &result, &syntax_node_value_by_syntax_node ]( const SubtractionSyntaxNodeSP& node )
         {
            for( const auto& argument : node->Children() )
            {
               result -= syntax_node_value_by_syntax_node[ argument ];
            }
         };

         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
      } );

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
   case ConditionalExpressionSyntaxNode::Type::MORE:
   {
      result = first_apperand_value > second_apperand_value;
   };
   break;
   }
   return result;
}

void HandleExpression( const VaribleStore& varible_store, const ExpressionSyntaxNodeSP& expression )
{
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& node )
   { int result = HandleComputationalExpression( varible_store, node ); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   expression->accept( visitor );
}

double Calculator::solve( const std::string& expression ) const
{
   LexicalTokens lexical_tokens( expression );
   SyntaxTree syntax_tree( lexical_tokens );

   std::cout << syntax_tree.to_string() << std::endl;

   int result = 0;

   VaribleStore varible_store;

   iterative_managed_dfs(
      syntax_tree.root(),
      [ &varible_store ]( const ISyntaxNodeSP& node ) -> std::optional< std::vector< ISyntaxNodeSP > >
      {
         std::optional< std::vector< ISyntaxNodeSP > > children = node->Children();

         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.scope_syntax_node = [ &varible_store, &node ]( const ScopeSyntaxNodeSP& scope )
         {
            // create scope in a VaribleStore
            varible_store.pushScope();
         };

         handlers.computational_expression_syntax_node = [ &varible_store ]( const ComputationalExpressionSyntaxNodeSP& computational_expression )
         { int result = HandleComputationalExpression( varible_store, computational_expression ); };

         handlers.print_expression_syntax_node = [ &varible_store, &node ]( const PrintExpressionSyntaxNodeSP& print_expression )
         {
            ISyntaxNodeSP next_scope;
            const auto& computational_expression = print_expression->computational_expression();
            const auto& result = HandleComputationalExpression( varible_store, computational_expression );
            std::cout << std::to_string( result ) << std::endl;
            return std::optional< std::vector< ISyntaxNodeSP > >{};
         };

         handlers.if_expression_syntax_node = [ &varible_store, &children, &node ]( const IfExpressionSyntaxNodeSP& if_expression )
         {
            ISyntaxNodeSP next_scope;
            const auto& condition = if_expression->conditional_expression();
            if( HandleConditionExpression( varible_store, condition ) )
            {
               next_scope = if_expression->true_scope();
            }
            else
            {
               next_scope = if_expression->false_scope();
            }
            children = {};

            if( next_scope )
            {
               children = std::vector< ISyntaxNodeSP >{ next_scope };
            }
         };
         handlers.varible_assigment_syntax_node = [ &varible_store, &node ]( const VaribleAssigmentSyntaxNodeSP& varible_assigment )
         {
            const auto& computational_expression = varible_assigment->computational_expression();
            const auto& value = HandleComputationalExpression( varible_store, computational_expression );
            varible_store[ varible_assigment->name() ] = value;
         };

         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );

         return children;
      },
      [ &varible_store ]( const ISyntaxNodeSP& node )
      {
         SyntaxNodeEmptyVisitor::Handlers handlers;
         handlers.scope_syntax_node = [ &varible_store, &node ]( const ScopeSyntaxNodeSP& scope )
         {
            // delete scope in a VaribleStore
            varible_store.popScope();
         };
         const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
         node->accept( visitor );
      } );

   return result;
}

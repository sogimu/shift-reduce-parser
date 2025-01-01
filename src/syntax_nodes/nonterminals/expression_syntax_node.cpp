#include "nonterminals/expression_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/if_expression_syntax_node.h"
#include "nonterminals/while_expression_syntax_node.h"
#include "nonterminals/function_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/print_expression_syntax_node.h"
#include "nonterminals/varible_assigment_syntax_node.h"
#include "nonterminals/return_expression_syntax_node.h"

#include <vector>

ExpressionSyntaxNode::ExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( computational_expression_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( conditional_expression_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const IfExpressionSyntaxNodeSP& if_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( if_expression_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const WhileExpressionSyntaxNodeSP& while_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( while_expression_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const FunctionSyntaxNodeSP& function_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( function_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const FunctionCallSyntaxNodeSP& function_call_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( function_call_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const PrintExpressionSyntaxNodeSP& print_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( print_expression_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const VaribleAssigmentSyntaxNodeSP& varible_assigment_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( varible_assigment_syntax_node );
}
ExpressionSyntaxNode::ExpressionSyntaxNode( const ReturnExpressionSyntaxNodeSP& return_expression_syntax_node )
   : ISyntaxNode{ Token_Type::EXPRESSION }
{
   add_back( return_expression_syntax_node );
}

void ExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.expression_syntax_node = [ this, &is_equal ]( const ExpressionSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      for( size_t i = 0; i < Children().size(); ++i )
      {
         const auto& lft_child = ( *this )[ i ];
         const auto& rht_child = ( *node )[ i ];
         if( !lft_child->compare( *rht_child ) )
         {
            return;
         }
      }
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

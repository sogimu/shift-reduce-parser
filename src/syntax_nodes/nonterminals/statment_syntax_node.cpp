#include "nonterminals/statment_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/if_statment_syntax_node.h"
#include "nonterminals/while_statment_syntax_node.h"
#include "nonterminals/function_statment_syntax_node.h"
#include "nonterminals/function_call_syntax_node.h"
#include "nonterminals/print_statment_syntax_node.h"
#include "nonterminals/varible_assigment_statment_syntax_node.h"
#include "nonterminals/return_statment_syntax_node.h"

#include <vector>

StatmentSyntaxNode::StatmentSyntaxNode()
   : ISyntaxNode{ Token_Type::STATMENT }
{
}
StatmentSyntaxNode::StatmentSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( computational_expression_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( conditional_expression_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const IfStatmentSyntaxNodeSP& if_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( if_statment_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const WhileStatmentSyntaxNodeSP& while_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( while_statment_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const FunctionStatmentSyntaxNodeSP& function_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( function_statment_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const FunctionCallSyntaxNodeSP& function_call_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( function_call_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const PrintStatmentSyntaxNodeSP& print_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( print_statment_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const VaribleAssigmentStatmentSyntaxNodeSP& varible_assigment_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( varible_assigment_statment_syntax_node );
}
StatmentSyntaxNode::StatmentSyntaxNode( const ReturnStatmentSyntaxNodeSP& return_statment_syntax_node )
   : ISyntaxNode{ Token_Type::STATMENT }
{
   add_back( return_statment_syntax_node );
}

void StatmentSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool StatmentSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.statment_syntax_node = [ this, &is_equal ]( const StatmentSyntaxNodeSP& node )
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

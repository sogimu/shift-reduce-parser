#include "nonterminals/computational_expression_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "terminals/f_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "nonterminals/conditional_expression_syntax_node.h"
#include "nonterminals/multiply/multiply_syntax_node.h"
#include "nonterminals/addition/addition_syntax_node.h"

#include <vector>

ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode()
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
}
ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const AdditionSyntaxNodeSP& e )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( e );
}
ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const MultiplySyntaxNodeSP& e )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( e );
}
ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const FSyntaxNodeSP& e )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( e );
}

ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( conditional_expression_syntax_node );
}

ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const NameSyntaxNodeSP& name_syntax_node )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( name_syntax_node );
}

ComputationalExpressionSyntaxNode::ComputationalExpressionSyntaxNode( const ISyntaxNodeSP& node )
   : ISyntaxNode{ Token_Type::COMPUTATIONAL_EXPRESSION }
{
   Add( node );
}

void ComputationalExpressionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ComputationalExpressionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.computational_expression_syntax_node = [ this, &is_equal ]( const ComputationalExpressionSyntaxNodeSP& node )
   {
      if( node->Children().size() == this->Children().size() )
      {
         is_equal = true;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   // node.accept( visitor );
   return is_equal;
}

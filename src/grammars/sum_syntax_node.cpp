#include "e/sum/sum_syntax_node.h"

#include "base/f_syntax_node.h"
#include "computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>
#include <vector>

SumSyntaxNode::SumSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 )
   : ISyntaxNode{ Token_Type::SUM }
{
   Add( f0 );
   Add( f1 );
}

SumSyntaxNode::SumSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0,
                              const ComputationalExpressionSyntaxNodeSP& computational_expression1 )
   : ISyntaxNode{ Token_Type::SUM }
{
   Add( computational_expression0 );
   Add( computational_expression1 );
}

std::vector< FSyntaxNodeSP > SumSyntaxNode::Arguments() const
{
   std::vector< FSyntaxNodeSP > result;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& node ) { result.emplace_back( node ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   for( const auto& child : this->Children() )
   {
      child->accept( visitor );
   }
   return result;
}

void SumSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

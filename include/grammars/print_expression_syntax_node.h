#pragma once

#include "base/f_syntax_node.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class PrintExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< PrintExpressionSyntaxNode >
{
public:
   PrintExpressionSyntaxNode();
   PrintExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
   ComputationalExpressionSyntaxNodeSP computational_expression() const;
};

using PrintExpressionSyntaxNodeSP = std::shared_ptr< PrintExpressionSyntaxNode >;
using PrintExpressionSyntaxNodeCSP = std::shared_ptr< const PrintExpressionSyntaxNode >;

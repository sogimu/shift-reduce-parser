#pragma once

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ReturnExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ReturnExpressionSyntaxNode >
{
public:
   ReturnExpressionSyntaxNode();
   ReturnExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression );
   ReturnExpressionSyntaxNode( const NameSyntaxNodeSP& name_syntax_node );
   ReturnExpressionSyntaxNode( const ISyntaxNodeSP& argument );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
   ComputationalExpressionSyntaxNodeSP computational_expression() const;
};

using ReturnExpressionSyntaxNodeSP = std::shared_ptr< ReturnExpressionSyntaxNode >;

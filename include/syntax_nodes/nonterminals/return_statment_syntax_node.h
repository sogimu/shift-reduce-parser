#pragma once

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ReturnStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ReturnStatmentSyntaxNode >
{
public:
   ReturnStatmentSyntaxNode();
   ReturnStatmentSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression );
   ReturnStatmentSyntaxNode( const ISyntaxNodeSP& argument );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
   ComputationalExpressionSyntaxNodeSP computational_expression() const;
};

using ReturnStatmentSyntaxNodeSP = std::shared_ptr< ReturnStatmentSyntaxNode >;

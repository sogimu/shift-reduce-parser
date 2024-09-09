#pragma once

#include <string>

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class VaribleAssigmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< VaribleAssigmentSyntaxNode >
{
public:
   VaribleAssigmentSyntaxNode();
   VaribleAssigmentSyntaxNode( const NameSyntaxNodeSP& name, const ComputationalExpressionSyntaxNodeSP& node );

   std::string name() const;
   ComputationalExpressionSyntaxNodeSP computational_expression() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
};

using VaribleAssigmentSyntaxNodeSP = std::shared_ptr< VaribleAssigmentSyntaxNode >;

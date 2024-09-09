#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ScopeSyntaxNode;
using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class IfExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< IfExpressionSyntaxNode >
{
public:
   IfExpressionSyntaxNode();
   IfExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   ConditionalExpressionSyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP true_scope() const;
   ScopeSyntaxNodeSP false_scope() const;
};

using IfExpressionSyntaxNodeSP = std::shared_ptr< IfExpressionSyntaxNode >;

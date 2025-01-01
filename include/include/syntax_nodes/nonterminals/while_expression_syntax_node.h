#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class ScopeSyntaxNode;
using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

class WhileExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< WhileExpressionSyntaxNode >
{
public:
   WhileExpressionSyntaxNode();
   WhileExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   ConditionalExpressionSyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP scope() const;
};

using WhileExpressionSyntaxNodeSP = std::shared_ptr< WhileExpressionSyntaxNode >;

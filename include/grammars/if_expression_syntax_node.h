#pragma once

#include "conditional_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "scope_syntax_node.h"

class ISyntaxNodeVisitor;

class IfExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< IfExpressionSyntaxNode >
{
public:
   IfExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression,
                           const ScopeSyntaxNodeSP& scope )
      : ISyntaxNode{ Token_Type::IF_EXPRESSION }
   {
      Add( conditional_expression );
      Add( scope );
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   ConditionalExpressionSyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP true_scope() const;
   ScopeSyntaxNodeSP false_scope() const;
};

using IfExpressionSyntaxNodeSP = std::shared_ptr< IfExpressionSyntaxNode >;
using IfExpressionSyntaxNodeCSP = std::shared_ptr< const IfExpressionSyntaxNode >;

#pragma once

#include "conditional_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "scope_syntax_node.h"

class ISyntaxNodeVisitor;

class WhileExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< WhileExpressionSyntaxNode >
{
public:
   WhileExpressionSyntaxNode()
      : ISyntaxNode{ Token_Type::WHILE_EXPRESSION }
   {
   }
   WhileExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope )
      : ISyntaxNode{ Token_Type::WHILE_EXPRESSION }
   {
      Add( conditional_expression );
      Add( scope );
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   ConditionalExpressionSyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP scope() const;
};

using WhileExpressionSyntaxNodeSP = std::shared_ptr< WhileExpressionSyntaxNode >;

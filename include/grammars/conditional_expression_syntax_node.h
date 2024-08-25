#pragma once

#include "base/name_syntax_node.h"
#include "grammars/print_expression_syntax_node.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class ConditionalExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ConditionalExpressionSyntaxNode >
{
public:
   enum class Type
   {
      LESS,
      LESS_OR_EQUAL,
      MORE,
      MORE_OR_EQUAL,
      EQUAL
   };

   ConditionalExpressionSyntaxNode()
      : ISyntaxNode{ Token_Type::CONDITIONAL_EXPRESSION }
   {
   }

   //    ConditionalExpressionSyntaxNode(const MoreExpressionSyntaxNodeSP& more_expression_syntax_node)
   //        : ISyntaxNode{Token_Type::CONDITIONAL_EXPRESSION}
   //    {
   //        Add(more_expression_syntax_node);
   //    }

   ConditionalExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& f0, const ComputationalExpressionSyntaxNodeSP& f1, Type type );
   ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& f0, const ComputationalExpressionSyntaxNodeSP& f1, Type type );
   ConditionalExpressionSyntaxNode( const NameSyntaxNodeSP& f0, const NameSyntaxNodeSP& f1, Type type );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   Type type() const;

   ComputationalExpressionSyntaxNodeSP first_apperand() const;

   ComputationalExpressionSyntaxNodeSP second_apperand() const;

private:
   Type mType;
};

using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;
using ConditionalExpressionSyntaxNodeCSP = std::shared_ptr< const ConditionalExpressionSyntaxNode >;

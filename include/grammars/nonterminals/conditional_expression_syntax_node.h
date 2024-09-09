#pragma once

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

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

   ConditionalExpressionSyntaxNode();
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

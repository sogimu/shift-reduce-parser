#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ScopeSyntaxNode;
using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class IfStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< IfStatmentSyntaxNode >
{
public:
   IfStatmentSyntaxNode( const IfStatmentSyntaxNode& if_statment_syntax_node );
   IfStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& true_scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   IfStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& true_scope, const ScopeSyntaxNodeSP& false_scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   ISyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP true_scope() const;
   ScopeSyntaxNodeSP false_scope() const;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
  ISyntaxNodeSP mConditionalExpression;
};

using IfStatmentSyntaxNodeSP = std::shared_ptr< IfStatmentSyntaxNode >;

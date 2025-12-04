#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class ScopeSyntaxNode;
using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

class WhileStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< WhileStatmentSyntaxNode >
{
public:
   WhileStatmentSyntaxNode( const WhileStatmentSyntaxNode& while_statment_syntax_node );

   WhileStatmentSyntaxNode( const ISyntaxNodeSP& conditional_expression, const ScopeSyntaxNodeSP& scope, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   // ConditionalExpressionSyntaxNodeSP conditional_expression() const;
   ScopeSyntaxNodeSP scope() const;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};

using WhileStatmentSyntaxNodeSP = std::shared_ptr< WhileStatmentSyntaxNode >;

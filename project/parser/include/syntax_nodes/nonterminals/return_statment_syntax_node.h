#pragma once

#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ReturnStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ReturnStatmentSyntaxNode >
{
public:
   ReturnStatmentSyntaxNode( const ReturnStatmentSyntaxNode& return_statment_syntax_node );
   ReturnStatmentSyntaxNode( const ISyntaxNodeSP& return_statment_syntax_node, const LexicalTokens::LexicalToken& lexical_tokens );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};

using ReturnStatmentSyntaxNodeSP = std::shared_ptr< ReturnStatmentSyntaxNode >;

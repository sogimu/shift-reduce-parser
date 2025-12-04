#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;

class ScopeSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ScopeSyntaxNode >

{
public:
   ScopeSyntaxNode( const ScopeSyntaxNode& scope );
   ScopeSyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   ScopeSyntaxNode( const std::vector< ISyntaxNodeSP >& expressions, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};

using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;

class ArraySyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ArraySyntaxNode >

{
public:
   ArraySyntaxNode( const ArraySyntaxNode& array );
   ArraySyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   ArraySyntaxNode( const std::vector< ISyntaxNodeSP >& expressions, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
  std::vector< LexicalTokens::LexicalToken > mTokens;
};

using ArraySyntaxNodeSP = std::shared_ptr< ArraySyntaxNode >;

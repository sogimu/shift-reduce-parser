#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class VaribleSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< VaribleSyntaxNode >

{
public:
   VaribleSyntaxNode( const NameSyntaxNodeSP& name_syntax_node, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   std::string name() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
   std::vector< LexicalTokens::LexicalToken > mTokens;
   std::string mName;
};

using VaribleSyntaxNodeSP = std::shared_ptr< VaribleSyntaxNode >;

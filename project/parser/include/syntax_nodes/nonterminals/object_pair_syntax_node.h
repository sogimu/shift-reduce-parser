#pragma once

#include "lexical_tokens.h"
#include <string>

#include "i_syntax_node.h"
#include "terminals/string_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ObjectPairSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ObjectPairSyntaxNode >
{
public:
   ObjectPairSyntaxNode( const ObjectPairSyntaxNode& node );
   ObjectPairSyntaxNode( const StringSyntaxNodeSP& key_syntax_node, const ISyntaxNodeSP& value_syntax_node, const std::vector< LexicalTokens::LexicalToken >& tokens);

   StringSyntaxNodeSP key_syntax_node() const;
   ISyntaxNodeSP value_syntax_node() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
   void add_lexical_token(const LexicalTokens::LexicalToken& token);

private:
    std::vector< LexicalTokens::LexicalToken > mTokens;
};

using ObjectPairSyntaxNodeSP = std::shared_ptr< ObjectPairSyntaxNode >;

#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>
#include <map>

class ISyntaxNodeVisitor;

class ObjectSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ObjectSyntaxNode >

{
public:
   ObjectSyntaxNode( const ObjectSyntaxNode& array );
   ObjectSyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   ObjectSyntaxNode( const std::map< std::string, ISyntaxNodeSP >& expressions, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
   std::map<std::string, ISyntaxNodeSP> values() const;
private:
   std::vector< LexicalTokens::LexicalToken > mTokens;
   std::map< std::string, ISyntaxNodeSP > mNodeByKey;
};

using ObjectSyntaxNodeSP = std::shared_ptr< ObjectSyntaxNode >;

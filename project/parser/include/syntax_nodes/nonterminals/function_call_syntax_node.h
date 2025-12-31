#pragma once

#include <string>
#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class FunctionCallSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FunctionCallSyntaxNode >
{
public:
   FunctionCallSyntaxNode( const FunctionCallSyntaxNode& function_call_syntax_node );
   FunctionCallSyntaxNode( const std::string& name );
   FunctionCallSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments );
   FunctionCallSyntaxNode( const NameSyntaxNodeSP& name_syntax_node, const std::vector< ISyntaxNodeSP >& arguments_syntax_nodes );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::string name() const;
   std::vector< ISyntaxNodeSP > arguments() const;

   std::pair<std::string, size_t> signature() const;

   std::vector< LexicalTokens::LexicalToken > lexical_tokens() const override;
private:
    std::vector< LexicalTokens::LexicalToken > mTokens;
    std::string mName;
    size_t mArgumentsNumber;
    std::pair<std::string, size_t> mSignature;
};

using FunctionCallSyntaxNodeSP = std::shared_ptr< FunctionCallSyntaxNode >;

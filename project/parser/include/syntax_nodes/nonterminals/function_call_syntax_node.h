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
   FunctionCallSyntaxNode( const std::string& name );
   FunctionCallSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments );
   FunctionCallSyntaxNode( const NameSyntaxNodeSP& name_syntax_node, const std::vector< ISyntaxNodeSP >& arguments_syntax_nodes );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::string name() const;
   std::vector< NameSyntaxNodeSP > arguments() const;

private:
   std::string mName;
};

using FunctionCallSyntaxNodeSP = std::shared_ptr< FunctionCallSyntaxNode >;

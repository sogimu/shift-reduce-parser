#pragma once

#include <string>
#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class FunctionCallOrDefinitionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FunctionCallOrDefinitionSyntaxNode >
{
public:
   FunctionCallOrDefinitionSyntaxNode();
   FunctionCallOrDefinitionSyntaxNode( const std::string& name );
   FunctionCallOrDefinitionSyntaxNode( const std::string& name, const std::vector< ISyntaxNodeSP >& arguments );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::string name() const;
   std::vector< NameSyntaxNodeSP > arguments() const;

private:
   std::string mName;
};

using FunctionCallOrDefinitionSyntaxNodeSP = std::shared_ptr< FunctionCallOrDefinitionSyntaxNode >;

#pragma once

#include <string>
#include <vector>
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ScopeSyntaxNode;
using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

class FunctionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FunctionSyntaxNode >
{
public:
   FunctionSyntaxNode();
   FunctionSyntaxNode( const std::string& name );
   FunctionSyntaxNode( const std::string& name, const ScopeSyntaxNodeSP& scope );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   std::string name() const;
   ScopeSyntaxNodeSP scope() const;
   std::vector< NameSyntaxNodeSP > arguments() const;

private:
   std::string mName;
};

using FunctionSyntaxNodeSP = std::shared_ptr< FunctionSyntaxNode >;

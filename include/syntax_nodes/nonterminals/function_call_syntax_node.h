#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class FunctionCallSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FunctionCallSyntaxNode >
{
public:
   FunctionCallSyntaxNode();
   FunctionCallSyntaxNode( const NameSyntaxNodeSP& name );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   NameSyntaxNodeSP name() const;
   std::vector< NameSyntaxNodeSP > arguments() const;
};

using FunctionCallSyntaxNodeSP = std::shared_ptr< FunctionCallSyntaxNode >;

#pragma once

#include "base/name_syntax_node.h"
#include "conditional_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "scope_syntax_node.h"

class ISyntaxNodeVisitor;

class FunctionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FunctionSyntaxNode >
{
public:
   FunctionSyntaxNode();
   FunctionSyntaxNode( const NameSyntaxNodeSP& name, const ScopeSyntaxNodeSP& scope );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

   NameSyntaxNodeSP name() const;
   ScopeSyntaxNodeSP scope() const;
   std::vector< NameSyntaxNodeSP > arguments() const;
};

using FunctionSyntaxNodeSP = std::shared_ptr< FunctionSyntaxNode >;

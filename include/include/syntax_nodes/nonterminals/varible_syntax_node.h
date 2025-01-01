#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class VaribleSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< VaribleSyntaxNode >

{
public:
   VaribleSyntaxNode();
   VaribleSyntaxNode( const NameSyntaxNodeSP& name_syntax_node );
   std::string name() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;

private:
   std::string mName;
};

using VaribleSyntaxNodeSP = std::shared_ptr< VaribleSyntaxNode >;

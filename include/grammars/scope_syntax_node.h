#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;

class ScopeSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ScopeSyntaxNode >

{
public:
   ScopeSyntaxNode();
   ScopeSyntaxNode( const ISyntaxNodeSP& expression );
   ScopeSyntaxNode( const std::vector< ISyntaxNodeSP >& expressions );
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
};

using ScopeSyntaxNodeSP = std::shared_ptr< ScopeSyntaxNode >;

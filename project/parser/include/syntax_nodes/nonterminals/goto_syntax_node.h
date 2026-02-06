#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class GotoSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< GotoSyntaxNode >
{
public:
   GotoSyntaxNode( const GotoSyntaxNode& nodes );
   GotoSyntaxNode( const ISyntaxNodeSP& node );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
   ISyntaxNodeSP target() const;
private:
   ISyntaxNodeSP mNode;
};

using GotoSyntaxNodeSP = std::shared_ptr< GotoSyntaxNode >;

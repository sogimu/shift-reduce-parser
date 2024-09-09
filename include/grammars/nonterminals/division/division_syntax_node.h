#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class DivisionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< DivisionSyntaxNode >
{
public:
   DivisionSyntaxNode();
   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};
using DivisionSyntaxNodeSP = std::shared_ptr< DivisionSyntaxNode >;
using DivisionSyntaxNodeCSP = std::shared_ptr< const DivisionSyntaxNode >;

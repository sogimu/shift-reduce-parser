#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class AsteriskSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< AsteriskSyntaxNode >
{
public:
   AsteriskSyntaxNode();

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using AsteriskSyntaxNodeSP = std::shared_ptr< AsteriskSyntaxNode >;
using AsteriskSyntaxNodeCSP = std::shared_ptr< const AsteriskSyntaxNode >;

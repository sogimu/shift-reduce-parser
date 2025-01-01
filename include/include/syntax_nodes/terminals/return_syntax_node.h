#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class ReturnSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ReturnSyntaxNode >
{
public:
   ReturnSyntaxNode();

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using ReturnSyntaxNodeSP = std::shared_ptr< ReturnSyntaxNode >;

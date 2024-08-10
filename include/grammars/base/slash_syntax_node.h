#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class SlashSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< SlashSyntaxNode >
{
public:
   SlashSyntaxNode();

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using SlashSyntaxNodeSP = std::shared_ptr< SlashSyntaxNode >;
using SlashSyntaxNodeCSP = std::shared_ptr< const SlashSyntaxNode >;

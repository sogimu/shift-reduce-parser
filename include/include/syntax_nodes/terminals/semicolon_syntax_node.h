#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class SemicolonSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< SemicolonSyntaxNode >
{
public:
   SemicolonSyntaxNode();

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using SemicolonSyntaxNodeSP = std::shared_ptr< SemicolonSyntaxNode >;

#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class CommaSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< CommaSyntaxNode >
{
public:
   CommaSyntaxNode();

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using CommaSyntaxNodeSP = std::shared_ptr< CommaSyntaxNode >;

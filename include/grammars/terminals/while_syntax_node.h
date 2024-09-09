#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class WhileSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< WhileSyntaxNode >
{
public:
   WhileSyntaxNode()
      : ISyntaxNode( Token_Type::WHILE )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using WhileSyntaxNodeSP = std::shared_ptr< WhileSyntaxNode >;

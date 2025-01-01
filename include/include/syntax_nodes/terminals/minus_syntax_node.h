#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class MinusSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< MinusSyntaxNode >
{
public:
   MinusSyntaxNode()
      : ISyntaxNode( Token_Type::MINUS )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using MinusSyntaxNodeSP = std::shared_ptr< MinusSyntaxNode >;

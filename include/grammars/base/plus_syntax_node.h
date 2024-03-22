#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>
#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class PlusSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< PlusSyntaxNode >
{
public:
   PlusSyntaxNode()
      : ISyntaxNode( Token_Type::PLUS )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using PlusSyntaxNodeSP = std::shared_ptr< PlusSyntaxNode >;
using PlusSyntaxNodeCSP = std::shared_ptr< const PlusSyntaxNode >;

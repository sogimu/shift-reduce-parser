#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>
#include <string>
#include <vector>

class ISyntaxNodeVisitor;

class SemicolonSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< SemicolonSyntaxNode >
{
public:
   SemicolonSyntaxNode()
      : ISyntaxNode( Token_Type::SEMICOLON )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using SemicolonSyntaxNodeSP = std::shared_ptr< SemicolonSyntaxNode >;
using SemicolonSyntaxNodeCSP = std::shared_ptr< const SemicolonSyntaxNode >;

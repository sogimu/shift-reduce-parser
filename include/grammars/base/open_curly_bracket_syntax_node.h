#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class OpenCurlyBracketSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< OpenCurlyBracketSyntaxNode >
{
public:
   OpenCurlyBracketSyntaxNode()
      : ISyntaxNode( Token_Type::OPEN_CURLY_BRACKET )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using OpenCurlyBracketSyntaxNodeSP = std::shared_ptr< OpenCurlyBracketSyntaxNode >;
using OpenCurlyBracketSyntaxNodeCSP = std::shared_ptr< const OpenCurlyBracketSyntaxNode >;

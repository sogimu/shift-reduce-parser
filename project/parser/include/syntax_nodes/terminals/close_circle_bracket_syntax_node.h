#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class CloseCircleBracketSyntaxNode : public ISyntaxNode,
                                     public std::enable_shared_from_this< CloseCircleBracketSyntaxNode >
{
public:
   CloseCircleBracketSyntaxNode()
      : ISyntaxNode( Token_Type::CLOSE_CIRCLE_BRACKET )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using CloseCircleBracketSyntaxNodeSP = std::shared_ptr< CloseCircleBracketSyntaxNode >;

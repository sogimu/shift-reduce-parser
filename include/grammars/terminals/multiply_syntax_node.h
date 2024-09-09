#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class MultiplySyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< MultiplySyntaxNode >
{
public:
   MultiplySyntaxNode()
      : ISyntaxNode( Token_Type::ASTERISK )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using MultiplySyntaxNodeSP = std::shared_ptr< MultiplySyntaxNode >;

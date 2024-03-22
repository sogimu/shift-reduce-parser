#pragma once

#include "enums.h"
#include "wrapped_syntax_node.h"

#include <vector>

class SyntaxNodeT : public WrappedSyntaxNode
{
public:
   SyntaxNodeT( const ISyntaxNodeSP& node )
      : WrappedSyntaxNode( Token_Type::E, node )
   {
   }
};

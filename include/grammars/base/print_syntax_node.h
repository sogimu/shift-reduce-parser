#pragma once

#include "enums.h"
#include "i_syntax_node.h"

#include <memory>

class ISyntaxNodeVisitor;

class PrintSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< PrintSyntaxNode >
{
public:
   PrintSyntaxNode()
      : ISyntaxNode( Token_Type::PRINT )
   {
   }

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
};

using PrintSyntaxNodeSP = std::shared_ptr< PrintSyntaxNode >;
using PrintSyntaxNodeCSP = std::shared_ptr< const PrintSyntaxNode >;

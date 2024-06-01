#pragma once

#include "e/diff/diff_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "sum/sum_syntax_node.h"

class ISyntaxNodeVisitor;

class ESyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ESyntaxNode >

{
public:
   ESyntaxNode()
      : ISyntaxNode{ Token_Type::E }
   {
   }
   ESyntaxNode( const SumSyntaxNodeSP& sum )
      : ISyntaxNode{ Token_Type::E }
   {
      Add( sum );
   }

   ESyntaxNode( const DiffSyntaxNodeSP& diff )
      : ISyntaxNode{ Token_Type::E }
   {
      Add( diff );
   }
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
};

using ESyntaxNodeSP = std::shared_ptr< ESyntaxNode >;
using ESyntaxNodeCSP = std::shared_ptr< const ESyntaxNode >;

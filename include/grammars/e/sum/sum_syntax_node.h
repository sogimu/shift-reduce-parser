#pragma once

#include "base/f_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

#include <string>
#include <vector>

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class SumSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< SumSyntaxNode >

{
public:
   SumSyntaxNode();
   SumSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 );
   SumSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0,
                  const ComputationalExpressionSyntaxNodeSP& computational_expression1 );

   std::vector< FSyntaxNodeSP > Arguments() const;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using SumSyntaxNodeSP = std::shared_ptr< SumSyntaxNode >;
using SumSyntaxNodeCSP = std::shared_ptr< const SumSyntaxNode >;

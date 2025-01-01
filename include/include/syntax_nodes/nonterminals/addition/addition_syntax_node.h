#pragma once

#include "terminals/f_syntax_node.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class AdditionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< AdditionSyntaxNode >

{
public:
   AdditionSyntaxNode();
   AdditionSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 );
   AdditionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0, const ComputationalExpressionSyntaxNodeSP& computational_expression1 );

   std::vector< FSyntaxNodeSP > Arguments() const;
   void Add( const ISyntaxNodeSP& child ) override;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using AdditionSyntaxNodeSP = std::shared_ptr< AdditionSyntaxNode >;

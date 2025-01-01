#pragma once

#include "terminals/f_syntax_node.h"
#include "i_syntax_node.h"

#include <vector>

class ISyntaxNodeVisitor;
class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class SubtractionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< SubtractionSyntaxNode >

{
public:
   SubtractionSyntaxNode();
   SubtractionSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 );
   SubtractionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0, const ComputationalExpressionSyntaxNodeSP& computational_expression1 );

   ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child ) override;
   std::vector< FSyntaxNodeSP > Arguments() const;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using SubtractionSyntaxNodeSP = std::shared_ptr< SubtractionSyntaxNode >;

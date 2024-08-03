#pragma once

#include "base/f_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

#include "print_expression_syntax_node.h"
#include <vector>

class ISyntaxNodeVisitor;

class DiffSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< DiffSyntaxNode >

{
public:
   DiffSyntaxNode();
   DiffSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 );

   DiffSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0,
                   const ComputationalExpressionSyntaxNodeSP& computational_expression1 );
   std::vector< FSyntaxNodeSP > Arguments() const;

   bool compare( const ISyntaxNode& node ) const override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
};

using DiffSyntaxNodeSP = std::shared_ptr< DiffSyntaxNode >;
using DiffSyntaxNodeCSP = std::shared_ptr< const DiffSyntaxNode >;

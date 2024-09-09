#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class AdditionSyntaxNode;
using AdditionSyntaxNodeSP = std::shared_ptr< AdditionSyntaxNode >;

class MultiplySyntaxNode;
using MultiplySyntaxNodeSP = std::shared_ptr< MultiplySyntaxNode >;

class FSyntaxNode;
using FSyntaxNodeSP = std::shared_ptr< FSyntaxNode >;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class ComputationalExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ComputationalExpressionSyntaxNode >

{
public:
   ComputationalExpressionSyntaxNode();
   ComputationalExpressionSyntaxNode( const AdditionSyntaxNodeSP& e );
   ComputationalExpressionSyntaxNode( const MultiplySyntaxNodeSP& e );
   ComputationalExpressionSyntaxNode( const FSyntaxNodeSP& e );
   ComputationalExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node );
   ComputationalExpressionSyntaxNode( const NameSyntaxNodeSP& name_syntax_node );
   ComputationalExpressionSyntaxNode( const ISyntaxNodeSP& node );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;
   bool compare( const ISyntaxNode& node ) const override;
};

using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

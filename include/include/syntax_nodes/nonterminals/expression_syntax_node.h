#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class ComputationalExpressionSyntaxNode;
using ComputationalExpressionSyntaxNodeSP = std::shared_ptr< ComputationalExpressionSyntaxNode >;

class ConditionalExpressionSyntaxNode;
using ConditionalExpressionSyntaxNodeSP = std::shared_ptr< ConditionalExpressionSyntaxNode >;

class IfExpressionSyntaxNode;
using IfExpressionSyntaxNodeSP = std::shared_ptr< IfExpressionSyntaxNode >;

class WhileExpressionSyntaxNode;
using WhileExpressionSyntaxNodeSP = std::shared_ptr< WhileExpressionSyntaxNode >;

class FunctionSyntaxNode;
using FunctionSyntaxNodeSP = std::shared_ptr< FunctionSyntaxNode >;

class FunctionCallSyntaxNode;
using FunctionCallSyntaxNodeSP = std::shared_ptr< FunctionCallSyntaxNode >;

class PrintExpressionSyntaxNode;
using PrintExpressionSyntaxNodeSP = std::shared_ptr< PrintExpressionSyntaxNode >;

class ReturnExpressionSyntaxNode;
using ReturnExpressionSyntaxNodeSP = std::shared_ptr< ReturnExpressionSyntaxNode >;

class VaribleAssigmentSyntaxNode;
using VaribleAssigmentSyntaxNodeSP = std::shared_ptr< VaribleAssigmentSyntaxNode >;

class ExpressionSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< ExpressionSyntaxNode >
{
public:
   ExpressionSyntaxNode();
   ExpressionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression_syntax_node );
   ExpressionSyntaxNode( const ConditionalExpressionSyntaxNodeSP& conditional_expression_syntax_node );
   ExpressionSyntaxNode( const IfExpressionSyntaxNodeSP& if_expression_syntax_node );
   ExpressionSyntaxNode( const WhileExpressionSyntaxNodeSP& while_expression_syntax_node );
   ExpressionSyntaxNode( const FunctionSyntaxNodeSP& function_syntax_node );
   ExpressionSyntaxNode( const FunctionCallSyntaxNodeSP& function_call_syntax_node );
   ExpressionSyntaxNode( const PrintExpressionSyntaxNodeSP& print_expression_syntax_node );
   ExpressionSyntaxNode( const VaribleAssigmentSyntaxNodeSP& varible_assigment_syntax_node );
   ExpressionSyntaxNode( const ReturnExpressionSyntaxNodeSP& return_expression_syntax_node );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
};

using ExpressionSyntaxNodeSP = std::shared_ptr< ExpressionSyntaxNode >;

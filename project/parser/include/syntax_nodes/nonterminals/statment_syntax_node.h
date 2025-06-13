#pragma once

#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class FSyntaxNode;
using FSyntaxNodeSP = std::shared_ptr< FSyntaxNode >;

class IfStatmentSyntaxNode;
using IfStatmentSyntaxNodeSP = std::shared_ptr< IfStatmentSyntaxNode >;

class WhileStatmentSyntaxNode;
using WhileStatmentSyntaxNodeSP = std::shared_ptr< WhileStatmentSyntaxNode >;

class FunctionStatmentSyntaxNode;
using FunctionStatmentSyntaxNodeSP = std::shared_ptr< FunctionStatmentSyntaxNode >;

class FunctionCallSyntaxNode;
using FunctionCallSyntaxNodeSP = std::shared_ptr< FunctionCallSyntaxNode >;

class PrintStatmentSyntaxNode;
using PrintStatmentSyntaxNodeSP = std::shared_ptr< PrintStatmentSyntaxNode >;

class ReturnStatmentSyntaxNode;
using ReturnStatmentSyntaxNodeSP = std::shared_ptr< ReturnStatmentSyntaxNode >;

class VaribleAssigmentStatmentSyntaxNode;
using VaribleAssigmentStatmentSyntaxNodeSP = std::shared_ptr< VaribleAssigmentStatmentSyntaxNode >;

class StatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< StatmentSyntaxNode >
{
public:
   StatmentSyntaxNode();
   StatmentSyntaxNode( const FSyntaxNodeSP& f_syntax_node );
   StatmentSyntaxNode( const IfStatmentSyntaxNodeSP& if_statment_syntax_node );
   StatmentSyntaxNode( const WhileStatmentSyntaxNodeSP& while_statment_syntax_node );
   StatmentSyntaxNode( const FunctionStatmentSyntaxNodeSP& function_statment_syntax_node );
   StatmentSyntaxNode( const FunctionCallSyntaxNodeSP& function_call_syntax_node );
   StatmentSyntaxNode( const PrintStatmentSyntaxNodeSP& print_expression_syntax_node );
   StatmentSyntaxNode( const VaribleAssigmentStatmentSyntaxNodeSP& varible_assigment_statment_syntax_node );
   StatmentSyntaxNode( const ReturnStatmentSyntaxNodeSP& return_expression_syntax_node );

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
};

using StatmentSyntaxNodeSP = std::shared_ptr< StatmentSyntaxNode >;

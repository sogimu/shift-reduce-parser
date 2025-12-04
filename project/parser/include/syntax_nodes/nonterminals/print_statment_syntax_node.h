#pragma once

#include "terminals/f_syntax_node.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class NameSyntaxNode;
using NameSyntaxNodeSP = std::shared_ptr< NameSyntaxNode >;

class PrintStatmentSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< PrintStatmentSyntaxNode >
{
public:
   PrintStatmentSyntaxNode( const NameSyntaxNodeSP& name_syntax_node );
   PrintStatmentSyntaxNode( const ISyntaxNodeSP& argument );

   ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child ) override;
   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;
};

using PrintStatmentSyntaxNodeSP = std::shared_ptr< PrintStatmentSyntaxNode >;

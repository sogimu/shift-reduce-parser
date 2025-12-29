#pragma once

#include "terminals/minus_syntax_node.h"
#include "terminals/number_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class FSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FSyntaxNode >

{
public:
   FSyntaxNode( const FSyntaxNode& f_syntax_node );
   FSyntaxNode( const int& number );
   FSyntaxNode( const MinusSyntaxNodeSP& minus, const NumberSyntaxNodeSP& number );
   FSyntaxNode( const NumberSyntaxNodeSP& number );

   int value() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;

private:
   int mValue;
};

using FSyntaxNodeSP = std::shared_ptr< FSyntaxNode >;

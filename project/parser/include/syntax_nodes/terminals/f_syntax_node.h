#pragma once

#include "terminals/minus_syntax_node.h"
#include "terminals/double_syntax_node.h"
#include "terminals/int_syntax_node.h"
#include "terminals/string_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"

class ISyntaxNodeVisitor;

class FSyntaxNode : public ISyntaxNode, public std::enable_shared_from_this< FSyntaxNode >
{
public:
   FSyntaxNode( const FSyntaxNode& f_syntax_node );
   FSyntaxNode( const MinusSyntaxNodeSP& minus, const DoubleSyntaxNodeSP& number );
   FSyntaxNode( const DoubleSyntaxNodeSP& number );
   FSyntaxNode( const MinusSyntaxNodeSP& minus, const IntSyntaxNodeSP& number );
   FSyntaxNode( const IntSyntaxNodeSP& number );
   FSyntaxNode( const StringSyntaxNodeSP& string );

   double value() const;

   void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) override;

   bool compare( const ISyntaxNode& node ) const override;

private:
   double mValue;
};

using FSyntaxNodeSP = std::shared_ptr< FSyntaxNode >;

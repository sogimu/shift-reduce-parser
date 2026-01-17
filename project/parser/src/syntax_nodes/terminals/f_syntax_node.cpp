#include "terminals/f_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "make_shallow_syntax_node_copy.h"
#include "syntax_node_empty_visitor.h"

FSyntaxNode::FSyntaxNode( const FSyntaxNode& f_syntax_node )
  : ISyntaxNode{ Token_Type::F }
  , mValue{ f_syntax_node.mValue }
{
  for( const auto& child : mChildren )
  {
    add_back( make_shallow_copy(child));
  }
}

FSyntaxNode::FSyntaxNode( const MinusSyntaxNodeSP& minus, const DoubleSyntaxNodeSP& number )
  : ISyntaxNode{ Token_Type::F }
{
  add_back( minus );
  add_back( number );
}

FSyntaxNode::FSyntaxNode( const IntSyntaxNodeSP& number )
  : ISyntaxNode{ Token_Type::F }
  , mValue{ static_cast< double >( number->value() ) }
{
  add_back( number );
}

FSyntaxNode::FSyntaxNode( const MinusSyntaxNodeSP& minus, const IntSyntaxNodeSP& number )
  : ISyntaxNode{ Token_Type::F }
{
  add_back( minus );
  add_back( number );
}

FSyntaxNode::FSyntaxNode( const DoubleSyntaxNodeSP& number )
  : ISyntaxNode{ Token_Type::F }
  , mValue{ number->value() }
{
  add_back( number );
}

FSyntaxNode::FSyntaxNode( const StringSyntaxNodeSP& string )
  : ISyntaxNode{ Token_Type::F }
  // , mValue{ string->value() }
{
  add_back( string );
}

double FSyntaxNode::value() const
{
  return mValue;
}
void FSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool FSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.f_syntax_node = [ this, &is_equal ]( const FSyntaxNodeSP& node ) { is_equal = node->value() == this->value(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

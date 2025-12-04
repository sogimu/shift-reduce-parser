#include "terminals/minus_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

MinusSyntaxNode::MinusSyntaxNode( const MinusSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::MINUS, node.lexical_tokens() }
{
}

MinusSyntaxNode::MinusSyntaxNode( LexicalTokens::LexicalToken token )
  : ITerminalSyntaxNode{ Token_Type::MINUS, token }
{
}

void MinusSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool MinusSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.minus_syntax_node = [ this, &is_equal ]( const MinusSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

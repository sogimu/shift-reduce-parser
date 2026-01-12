#include "terminals/int_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

IntSyntaxNode::IntSyntaxNode( const IntSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::INT, node.lexical_tokens() }
  , mValue{ node.mValue }
{
}

IntSyntaxNode::IntSyntaxNode( const LexicalTokens::LexicalToken& token )
  : ITerminalSyntaxNode{ Token_Type::INT, token }
{
  mValue = std::stoi( token.text );
}

int IntSyntaxNode::value() const
{
  return mValue;
}

void IntSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool IntSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.int_syntax_node = [ this, &is_equal ]( const IntSyntaxNodeSP& node ) { is_equal = node->value() == this->value(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

#include "terminals/double_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

DoubleSyntaxNode::DoubleSyntaxNode( const DoubleSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::DOUBLE, node.lexical_tokens() }
  , mValue{ node.mValue }
{
}

DoubleSyntaxNode::DoubleSyntaxNode( const LexicalTokens::LexicalToken& token )
  : ITerminalSyntaxNode{ Token_Type::DOUBLE, token }
{
  mValue = std::stod( token.text );
}

double DoubleSyntaxNode::value() const
{
  return mValue;
}

void DoubleSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool DoubleSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.double_syntax_node = [ this, &is_equal ]( const DoubleSyntaxNodeSP& node ) { is_equal = node->value() == this->value(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

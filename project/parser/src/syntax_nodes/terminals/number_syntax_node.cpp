#include "terminals/number_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

NumberSyntaxNode::NumberSyntaxNode( const NumberSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::INT, node.lexical_tokens() }
  , mValue{ node.mValue }
{
}

NumberSyntaxNode::NumberSyntaxNode( const LexicalTokens::LexicalToken& token )
  : ITerminalSyntaxNode{ Token_Type::INT, token }
{
  mValue = std::stod( token.text );
}

int NumberSyntaxNode::value() const
{
  return mValue;
}

void NumberSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool NumberSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.number_syntax_node = [ this, &is_equal ]( const NumberSyntaxNodeSP& node ) { is_equal = node->value() == this->value(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

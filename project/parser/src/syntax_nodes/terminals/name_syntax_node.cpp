#include "terminals/name_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>

NameSyntaxNode::NameSyntaxNode( const NameSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::NAME, node.lexical_tokens() }
   , mValue{ node.lexical_tokens()[0].text }
{
}

NameSyntaxNode::NameSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::NAME, token }
   , mValue{ token.text }
{
}

void NameSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool NameSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.name_syntax_node = [ this, &is_equal ]( const NameSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

std::string NameSyntaxNode::value() const
{
   return mValue;
}

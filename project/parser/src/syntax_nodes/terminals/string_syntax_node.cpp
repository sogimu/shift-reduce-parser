#include "terminals/string_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <string>

StringSyntaxNode::StringSyntaxNode( const StringSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::STRING, node.lexical_tokens() }
   , mValue{ node.lexical_tokens()[0].text }
{
}

StringSyntaxNode::StringSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::STRING, token }
   , mValue{ token.text }
{
}

void StringSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool StringSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.string_syntax_node = [ this, &is_equal ]( const StringSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

std::string StringSyntaxNode::value() const
{
   return mValue;
}

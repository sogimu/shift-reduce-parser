#include "terminals/colon_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

ColonSyntaxNode::ColonSyntaxNode( const ColonSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::COLON, node.lexical_tokens() }
{
}

ColonSyntaxNode::ColonSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::COLON, token }
{
}

void ColonSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ColonSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.colon_syntax_node = [ this, &is_equal ]( const ColonSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

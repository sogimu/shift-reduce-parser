#include "terminals/open_square_bracket_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

OpenSquareBracketSyntaxNode::OpenSquareBracketSyntaxNode( const OpenSquareBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::OPEN_SQUARE_BRACKET, node.lexical_tokens() }
{
}

OpenSquareBracketSyntaxNode::OpenSquareBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::OPEN_SQUARE_BRACKET, token }
{
}

void OpenSquareBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool OpenSquareBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.open_square_bracket_syntax_node = [ this, &is_equal ]( const OpenSquareBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

#include "terminals/close_square_bracket_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

CloseSquareBracketSyntaxNode::CloseSquareBracketSyntaxNode( const CloseSquareBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::CLOSE_SQUARE_BRACKET, node.lexical_tokens() }
{
}

CloseSquareBracketSyntaxNode::CloseSquareBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::CLOSE_SQUARE_BRACKET, token }
{
}

void CloseSquareBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool CloseSquareBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.close_square_bracket_syntax_node = [ this, &is_equal ]( const CloseSquareBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}


#include "terminals/close_curly_bracket_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

CloseCurlyBracketSyntaxNode::CloseCurlyBracketSyntaxNode( const CloseCurlyBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::CLOSE_CURLY_BRACKET, node.lexical_tokens() }
{
}

CloseCurlyBracketSyntaxNode::CloseCurlyBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::CLOSE_CURLY_BRACKET, token }
{
}

void CloseCurlyBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool CloseCurlyBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.close_curly_bracket_syntax_node = [ this, &is_equal ]( const CloseCurlyBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}


#include "terminals/open_curly_bracket_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

OpenCurlyBracketSyntaxNode::OpenCurlyBracketSyntaxNode( const OpenCurlyBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CURLY_BRACKET, node.lexical_tokens() }
{
}

OpenCurlyBracketSyntaxNode::OpenCurlyBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CURLY_BRACKET, token }
{
}

void OpenCurlyBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool OpenCurlyBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.open_curly_bracket_syntax_node = [ this, &is_equal ]( const OpenCurlyBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

#include "terminals/open_circle_bracket_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

OpenCircleBracketSyntaxNode::OpenCircleBracketSyntaxNode( const OpenCircleBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CIRCLE_BRACKET, node.lexical_tokens() }
{
}

OpenCircleBracketSyntaxNode::OpenCircleBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CIRCLE_BRACKET, token }
{
}

void OpenCircleBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool OpenCircleBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.open_circle_bracket_syntax_node = [ this, &is_equal ]( const OpenCircleBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

#include "terminals/close_circle_bracket_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

CloseCircleBracketSyntaxNode::CloseCircleBracketSyntaxNode( const CloseCircleBracketSyntaxNode& node )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CIRCLE_BRACKET, node.lexical_tokens() }
{
}

CloseCircleBracketSyntaxNode::CloseCircleBracketSyntaxNode( const LexicalTokens::LexicalToken& token )
   : ITerminalSyntaxNode{ Token_Type::OPEN_CIRCLE_BRACKET, token }
{
}

void CloseCircleBracketSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool CloseCircleBracketSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.close_curly_bracket_syntax_node = [ this, &is_equal ]( const CloseCurlyBracketSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

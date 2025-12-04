#include "terminals/asterisk_syntax_node.h"

#include "terminals/f_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

AsteriskSyntaxNode::AsteriskSyntaxNode( const AsteriskSyntaxNode& node )
  : ITerminalSyntaxNode{ Token_Type::ASTERISK, node.lexical_tokens() }
{
}
AsteriskSyntaxNode::AsteriskSyntaxNode( const LexicalTokens::LexicalToken& token )
    : ITerminalSyntaxNode{ Token_Type::ASTERISK, token }
{
}

void AsteriskSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool AsteriskSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.asterisk_syntax_node = [ this, &is_equal ]( const AsteriskSyntaxNodeSP& node ) { is_equal = node->lexical_tokens() == this->lexical_tokens(); };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );
   return is_equal;
}

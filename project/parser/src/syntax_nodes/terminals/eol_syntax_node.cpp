#include "terminals/eol_syntax_node.h"

#include "i_syntax_node_visitor.h"

EolSyntaxNode::EolSyntaxNode( const EolSyntaxNode& node )
      : ITerminalSyntaxNode{ Token_Type::BOL, node.lexical_tokens() }
{
}

EolSyntaxNode::EolSyntaxNode( LexicalTokens::LexicalToken token )
  : ITerminalSyntaxNode{ Token_Type::EOL, token }
{
}

void EolSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

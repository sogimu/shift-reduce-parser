#include "terminals/slash_syntax_node.h"

#include "terminals/f_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

SlashSyntaxNode::SlashSyntaxNode()
   : ISyntaxNode{ Token_Type::ASTERISK }
{
}

void SlashSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

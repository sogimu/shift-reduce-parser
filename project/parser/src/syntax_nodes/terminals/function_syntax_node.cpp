#include "terminals/function_syntax_node.h"

#include "i_syntax_node_visitor.h"

FunctionSyntaxNode::FunctionSyntaxNode()
  : ISyntaxNode( Token_Type::FUNCTION )
{

}
void FunctionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

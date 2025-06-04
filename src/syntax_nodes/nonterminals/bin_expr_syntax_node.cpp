#include "nonterminals/bin_expr_syntax_node.h"

#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

BinExprSyntaxNode::BinExprSyntaxNode()
   : ISyntaxNode{ Token_Type::BinExpr }
{
}
BinExprSyntaxNode::BinExprSyntaxNode( const Type& type, const ISyntaxNodeSP& f0, const ISyntaxNodeSP& f1 )
   : ISyntaxNode{ Token_Type::BinExpr }
   , mType{ type }
{
   add_back( f0 );
   add_back( f1 );
}
BinExprSyntaxNode::Type BinExprSyntaxNode::type() const
{
  return mType;
}

// ISyntaxNodeSP& BinExprSyntaxNode::add_back( const ISyntaxNodeSP& child )
// {
//    ISyntaxNodeSP node = child;
//    SyntaxNodeEmptyVisitor::Handlers handlers;
//    handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };
//
//    const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
//    child->accept( visitor );
//
//    return ISyntaxNode::add_back( node );
// }
bool BinExprSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.bin_expr_syntax_node = [ this, &is_equal ]( const BinExprSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      for( size_t i = 0; i < Children().size(); ++i )
      {
         const auto& lft_child = ( *this )[ i ];
         const auto& rht_child = ( *node )[ i ];
         if( !lft_child->compare( *rht_child ) )
         {
            return;
         }
      }
      if( node->type() != this->type() )
        return;
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

void BinExprSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

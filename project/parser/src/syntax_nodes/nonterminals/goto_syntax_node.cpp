#include "nonterminals/goto_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include <cstddef>

GotoSyntaxNode::GotoSyntaxNode( const GotoSyntaxNode& nodes )
   : ISyntaxNode{ Token_Type::GOTO }
{

}

GotoSyntaxNode::GotoSyntaxNode( const ISyntaxNodeSP& node )
   : ISyntaxNode{ Token_Type::GOTO }
   , mNode{ node }
{
}

ISyntaxNodeSP GotoSyntaxNode::target() const
{
    return mNode.lock();
}

void GotoSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool GotoSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.goto_syntax_node = [ this, &is_equal ]( const GotoSyntaxNodeSP& node )
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
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

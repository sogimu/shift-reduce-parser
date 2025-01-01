#include "nonterminals/multiply/multiply_syntax_node.h"

#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

MultiplySyntaxNode::MultiplySyntaxNode()
   : ISyntaxNode{ Token_Type::MULTIPLY }
{
}

ISyntaxNodeSP& MultiplySyntaxNode::add_back( const ISyntaxNodeSP& child )
{
   ISyntaxNodeSP node = child;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   child->accept( visitor );

   return ISyntaxNode::add_back( node );
}
bool MultiplySyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.multiply_syntax_node = [ this, &is_equal ]( const MultiplySyntaxNodeSP& node )
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

void MultiplySyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

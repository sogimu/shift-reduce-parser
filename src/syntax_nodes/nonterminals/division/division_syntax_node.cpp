#include "nonterminals/division/division_syntax_node.h"

#include "terminals/f_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

DivisionSyntaxNode::DivisionSyntaxNode()
   : ISyntaxNode{ Token_Type::DIVISION }
{
}

ISyntaxNodeSP& DivisionSyntaxNode::add_back( const ISyntaxNodeSP& child )
{
   ISyntaxNodeSP node = child;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   child->accept( visitor );

   return ISyntaxNode::add_back( node );
}

bool DivisionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.division_syntax_node = [ this, &is_equal ]( const DivisionSyntaxNodeSP& node )
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

void DivisionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

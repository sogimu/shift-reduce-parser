#include "nonterminals/subtraction/subtraction_syntax_node.h"

#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <vector>

SubtractionSyntaxNode::SubtractionSyntaxNode()
   : ISyntaxNode{ Token_Type::SUBTRACTION }
{
}
SubtractionSyntaxNode::SubtractionSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 )
   : ISyntaxNode{ Token_Type::SUBTRACTION }
{
   add_back( f0 );
   add_back( f1 );
}

SubtractionSyntaxNode::SubtractionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0,
                                              const ComputationalExpressionSyntaxNodeSP& computational_expression1 )
   : ISyntaxNode{ Token_Type::SUBTRACTION }
{
   add_back( computational_expression0 );
   add_back( computational_expression1 );
}

ISyntaxNodeSP& SubtractionSyntaxNode::add_back( const ISyntaxNodeSP& child )
{
   ISyntaxNodeSP node = child;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   child->accept( visitor );

   return ISyntaxNode::add_back( node );
}
std::vector< FSyntaxNodeSP > SubtractionSyntaxNode::Arguments() const
{
   std::vector< FSyntaxNodeSP > result;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& node ) { result.emplace_back( node ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   for( const auto& child : this->Children() )
   {
      child->accept( visitor );
   }
   return result;
}

bool SubtractionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.subtraction_syntax_node = [ this, &is_equal ]( const SubtractionSyntaxNodeSP& node )
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
void SubtractionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

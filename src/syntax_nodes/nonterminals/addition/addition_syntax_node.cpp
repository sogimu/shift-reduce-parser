#include "nonterminals/addition/addition_syntax_node.h"

#include "nonterminals/varible_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "nonterminals/computational_expression_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

#include <cstddef>
#include <vector>

AdditionSyntaxNode::AdditionSyntaxNode()
   : ISyntaxNode{ Token_Type::ADDITION }
{
}

AdditionSyntaxNode::AdditionSyntaxNode( const FSyntaxNodeSP& f0, const FSyntaxNodeSP& f1 )
   : ISyntaxNode{ Token_Type::ADDITION }
{
   add_back( f0 );
   add_back( f1 );
}

AdditionSyntaxNode::AdditionSyntaxNode( const ComputationalExpressionSyntaxNodeSP& computational_expression0,
                                        const ComputationalExpressionSyntaxNodeSP& computational_expression1 )
   : ISyntaxNode{ Token_Type::ADDITION }
{
   add_back( computational_expression0 );
   add_back( computational_expression1 );
}

std::vector< FSyntaxNodeSP > AdditionSyntaxNode::Arguments() const
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

ISyntaxNodeSP& AdditionSyntaxNode::add_back( const ISyntaxNodeSP& child )
{
   ISyntaxNodeSP node = child;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.name_syntax_node = [ &node ]( const NameSyntaxNodeSP& name ) { node = std::make_shared< VaribleSyntaxNode >( name ); };

   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   child->accept( visitor );

   return ISyntaxNode::add_back( node );
}

bool AdditionSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.addition_syntax_node = [ this, &is_equal ]( const AdditionSyntaxNodeSP& node )
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

void AdditionSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

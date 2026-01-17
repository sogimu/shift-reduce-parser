#include "nonterminals/un_expr_syntax_node.h"

#include <cstddef>
#include <vector>

#include "make_shallow_syntax_node_copy.h"
#include "nonterminals/varible_syntax_node.h"
#include "terminals/f_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"


UnExprSyntaxNode::UnExprSyntaxNode( const UnExprSyntaxNode& un_expr_syntax_node )
   : ISyntaxNode{ Token_Type::UnExpr }
   , mType{ un_expr_syntax_node.type() }
{
   mTokens = un_expr_syntax_node.lexical_tokens();
}

UnExprSyntaxNode::UnExprSyntaxNode( const Type& type, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::UnExpr }
   , mType{ type }
{
   mTokens = lexical_tokens;
}

UnExprSyntaxNode::UnExprSyntaxNode( const Type& type, const ISyntaxNodeSP& argument, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::UnExpr }
   , mType{ type }
{
   mTokens = lexical_tokens;
   add_back( argument );
}

UnExprSyntaxNode::Type UnExprSyntaxNode::type() const
{
  return mType;
}

// std::vector< FSyntaxNodeSP > UnExprSyntaxNode::Arguments() const
// {
//    std::vector< FSyntaxNodeSP > result;
//    SyntaxNodeEmptyVisitor::Handlers handlers;
//    handlers.f_syntax_node = [ &result ]( const FSyntaxNodeSP& node ) { result.emplace_back( node ); };
//
//    const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
//    for( const auto& child : this->Children() )
//    {
//       child->accept( visitor );
//    }
//    return result;
// }

// ISyntaxNodeSP& UnExprSyntaxNode::add_back( const ISyntaxNodeSP& child )
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

bool UnExprSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = false;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.un_expr_syntax_node = [ this, &is_equal ]( const UnExprSyntaxNodeSP& node )
   {
      if( node->Children().size() != this->Children().size() )
         return;
      if( node->lexical_tokens() != this->lexical_tokens() )
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

void UnExprSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

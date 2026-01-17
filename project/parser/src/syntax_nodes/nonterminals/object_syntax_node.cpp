#include "nonterminals/object_syntax_node.h"

#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"

ObjectSyntaxNode::ObjectSyntaxNode( const ObjectSyntaxNode& object )
   : ISyntaxNode{ Token_Type::OBJECT }
{
   mTokens = object.lexical_tokens();
}

ObjectSyntaxNode::ObjectSyntaxNode( const ISyntaxNodeSP& expression, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::OBJECT }
{
   mTokens = lexical_tokens;
   add_back( expression );
}

ObjectSyntaxNode::ObjectSyntaxNode( const std::map< std::string, ISyntaxNodeSP >& node_by_key, const std::vector< LexicalTokens::LexicalToken >& lexical_tokens )
   : ISyntaxNode{ Token_Type::OBJECT }
   , mNodeByKey{ node_by_key }
{
   mTokens = lexical_tokens;
   for( const auto& [ key, node ] : mNodeByKey )
   {
       add_back( node );
   }
}
void ObjectSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

std::vector< LexicalTokens::LexicalToken > ObjectSyntaxNode::lexical_tokens() const
{ 
    return mTokens; 
}

std::map<std::string, ISyntaxNodeSP> ObjectSyntaxNode::values() const
{
    return mNodeByKey; 
}

bool ObjectSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.object_syntax_node = [ this, &is_equal ]( const ObjectSyntaxNodeSP& node )
   {
      // if( node->values() != this->values() )
      //    return;
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
      is_equal = true;
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

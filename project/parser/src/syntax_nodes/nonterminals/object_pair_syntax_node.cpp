#include "nonterminals/object_pair_syntax_node.h"
#include "terminals/name_syntax_node.h"
#include "enums.h"
#include "i_syntax_node.h"
#include "i_syntax_node_visitor.h"
#include "syntax_node_empty_visitor.h"
#include "utils.h"

ObjectPairSyntaxNode::ObjectPairSyntaxNode( const ObjectPairSyntaxNode& node )
   : ISyntaxNode{ Token_Type::OBJECT_PAIR }
   , mTokens{ node.mTokens }
{

}

ObjectPairSyntaxNode::ObjectPairSyntaxNode( const StringSyntaxNodeSP& key_syntax_node, const ISyntaxNodeSP& value_syntax_node, const std::vector< LexicalTokens::LexicalToken >& tokens )
   : ISyntaxNode{ Token_Type::OBJECT_PAIR }
{
    mTokens = tokens;
    add_back( key_syntax_node );
    add_back( value_syntax_node );
}

StringSyntaxNodeSP ObjectPairSyntaxNode::key_syntax_node() const
{
   return std::dynamic_pointer_cast< StringSyntaxNode >( this->operator[]( 0 ) );
}

ISyntaxNodeSP ObjectPairSyntaxNode::value_syntax_node() const
{
   return this->operator[]( 1 );
}

void ObjectPairSyntaxNode::accept( const ISyntaxNodeVisitorSP& visitor )
{
   visitor->visit( shared_from_this() );
}

bool ObjectPairSyntaxNode::compare( const ISyntaxNode& node ) const
{
   bool is_equal = true;
   SyntaxNodeEmptyVisitor::Handlers handlers;
   handlers.object_pair_syntax_node = [ this, &is_equal ]( const ObjectPairSyntaxNodeSP& node )
   {
      if( node->lexical_tokens() != this->lexical_tokens() )
      {
         is_equal = false;
         return;
      }
      if( node->Children().size() != this->Children().size() )
      {
         is_equal = false;
         return;
      }
   };
   const auto& visitor = std::make_shared< SyntaxNodeEmptyVisitor >( handlers );
   const_cast< ISyntaxNode& >( node ).accept( visitor );

   return is_equal;
}

std::vector< LexicalTokens::LexicalToken > ObjectPairSyntaxNode::lexical_tokens() const
{ 
    return { mTokens }; 
}

void ObjectPairSyntaxNode::add_lexical_token(const LexicalTokens::LexicalToken& token)
{
  mTokens.push_back( token );
}

#pragma once

#include <string>
#include <list>
#include <memory>

#include "enums.h"

class ISyntaxNodeVisitor;

struct ISyntaxNode;
using ISyntaxNodeSP = std::shared_ptr< ISyntaxNode >;
using ISyntaxNodeCSP = std::shared_ptr< const ISyntaxNode >;

struct ISyntaxNode
{
   // using iterator = decltype( ISyntaxNode::mChildren )::iterator;
   // using const_iterator = decltype( mChildren )::const_iterator;
   ISyntaxNode() = default;

   ISyntaxNode( const Token_Type& type )
      : mType{ type }
   {
   }

   virtual ~ISyntaxNode() {};

   virtual void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) = 0;

   Token_Type type() const
   {
      return mType;
   }

   const std::string& text() const
   {
      return mText;
   }

   virtual ISyntaxNodeSP& add_back( const ISyntaxNodeSP& child )
   {
      return mChildren.emplace_back( child );
   }

   virtual ISyntaxNodeSP& add_front( const ISyntaxNodeSP& child )
   {
      return mChildren.emplace_front( child );
   }

   auto insert( const auto& pos, const ISyntaxNodeSP& value )
   {
      return mChildren.insert( pos, value );
   }

   virtual ISyntaxNodeSP operator[]( size_t index ) const
   {
      if( index >= mChildren.size() )
         return {};
      auto it = mChildren.begin();
      std::advance( it, index );
      return *it;
   }

   virtual ISyntaxNodeSP operator[]( size_t index )
   {
      if( index >= mChildren.size() )
         return {};
      auto it = mChildren.begin();
      std::advance( it, index );
      return *it;
   }

   auto Children() const
   {
      return mChildren;
   }

   bool operator==( const ISyntaxNode& node ) const
   {
      return compare( node );
      ( void )node;
   }

   virtual bool compare( const ISyntaxNode& node ) const
   {
      return false;
      ( void )node;
   }

   auto begin()
   {
      return mChildren.begin();
   }

   auto begin() const
   {
      return mChildren.begin();
   }

   auto end()
   {
      return mChildren.end();
   }

   auto end() const
   {
      return mChildren.end();
   }

   auto rbegin()
   {
      return mChildren.rbegin();
   }

   auto rbegin() const
   {
      return mChildren.rbegin();
   }

   auto rend()
   {
      return mChildren.rend();
   }

   auto rend() const
   {
      return mChildren.rend();
   }

private:
   Token_Type mType;
   std::string mText;
   std::list< ISyntaxNodeSP > mChildren;
};

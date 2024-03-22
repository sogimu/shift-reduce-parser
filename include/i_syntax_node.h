#pragma once

// #include <iostream>
#include <string>
#include <vector>
// #include <set>
#include <memory>
// #include <stack>
// #include <map>
// #include <iomanip>
// #include <functional>
// #include <optional>

#include "enums.h"
#include "i_feature.h"
#include "lexical_tokens.h"

class ISyntaxNodeVisitor;

struct ISyntaxNode;
using ISyntaxNodeSP = std::shared_ptr< ISyntaxNode >;
using ISyntaxNodeCSP = std::shared_ptr< const ISyntaxNode >;

struct ISyntaxNode
{
   ISyntaxNode() = default;

   ISyntaxNode( const Token_Type& type )
      : mType{ type }
   {
   }

   virtual ~ISyntaxNode(){};

   virtual void accept( const std::shared_ptr< ISyntaxNodeVisitor >& visitor ) = 0;

   Token_Type type() const
   {
      return mType;
   }

   const std::string& text() const
   {
      return mText;
   }

   virtual void Add( const ISyntaxNodeSP& child )
   {
      mChildren.emplace_back( child );
   }

   virtual ISyntaxNodeSP operator[]( size_t index ) const
   {
      if( index >= mChildren.size() )
         return {};
      return mChildren.at( index );
   }

   virtual ISyntaxNodeSP operator[]( size_t index )
   {
      if( index >= mChildren.size() )
         return {};
      return mChildren.at( index );
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

private:
   Token_Type mType;
   std::string mText;
   std::vector< ISyntaxNodeSP > mChildren;
};

// inline bool operator==( const ISyntaxNodeSP& a, const ISyntaxNodeSP& b ) { return !(

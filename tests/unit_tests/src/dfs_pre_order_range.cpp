#include "utils/dfs_pre_order_range.h"

#include "catch2/catch_all.hpp"
#include "catch2/catch_test_macros.hpp"
#include "utils.h"

#include <memory>
#include <string>
#include <vector>

class Entity;
using EntitySP = std::shared_ptr< Entity >;

class Entity
{
public:
   Entity( const std::string& name )
      : mName( name )
   {
   }
   std::vector< EntitySP >::iterator begin()
   {
      return mChildren.begin();
   }
   std::vector< EntitySP >::iterator end()
   {
      return mChildren.end();
   }

   std::string Name() const
   {
      return mName;
   }

   void Append( const EntitySP& entity )
   {
      mChildren.push_back( entity );
   }

private:
   std::string mName;
   std::vector< EntitySP > mChildren;
};

std::ostream& operator<<( std::ostream& o, const EntitySP& entity )
{
   o << entity->Name();
   return o;
}

TEST_CASE( "DFS pre-order range", "[wef]" )
{

   const size_t BRANCH_LENGTH = 3;

   const auto& root0 = std::make_shared< Entity >( "root0" );
   auto last_entity = root0;
   for( size_t i = 0; i < BRANCH_LENGTH; ++i )
   {
      const auto& entity = std::make_shared< Entity >( std::to_string( i ) );
      last_entity->Append( entity );
   }

   const auto& root1 = std::make_shared< Entity >( "root1" );
   last_entity = root1;
   for( size_t i = 0; i < BRANCH_LENGTH + 2; ++i )
   {
      const auto& entity = std::make_shared< Entity >( std::to_string( i ) );
      last_entity->Append( entity );
   }

   // Act
   const auto& range0 = DfsRange< EntitySP >{ std::vector< EntitySP >{ root0 } };
   const auto& range1 = DfsRange< EntitySP >{ std::vector< EntitySP >{ root1 } };

   zip_container c( range0, range1 );
   for( const auto& [ a, b ] : c )
   {
      //        if( a )
      //            std::cout << a.value();
      //        else
      //            std::cout << "nil";

      //        if( b )
      //            std::cout << b.value();
      //        else
      //            std::cout << "nil";

      //        if( a != b )
      //            std::cout << " <- differs";
      // std::cout << std::endl;
   }

   const auto& r = std::mismatch( range0.begin(), range0.end(), range1.begin(), range1.end(),
                                  []( const auto& a, const auto& b ) -> bool { return a->Name() == b->Name(); } );
   //    std::cout << *r.first << *r.second << std::endl;
   REQUIRE( 1 == 1 );
}

#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <stack>
#include <string>
#include <vector>

template< typename Node >
struct DfsRange
{
   class Iterator
   {
   public:
      using iterator_category = std::input_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Node;
      using reference = value_type&;
      using pointer = value_type*;

      Iterator( const std::vector< Node >& roots )
      {
         mTiers.emplace( Tier{ roots.begin(), roots.end() } );
      }

      Node operator*() const noexcept
      {
         const auto& current_tier = mTiers.top();
         if( current_tier.current != current_tier.end )
            return *current_tier.current;
         return nullptr;
      }

      Iterator operator++()
      {
         if( mTiers.empty() )
            return *this;
         auto& current_tier = mTiers.top();
         if( current_tier.current != current_tier.end )
         {
            const auto& entity = *current_tier.current;
            if( entity->begin() != entity->end() )
            {
               mTiers.emplace( Tier{ entity->begin(), entity->end() } );
            }
            else
            {
               bool is_step_satisfied = false;
               while( !is_step_satisfied && !mTiers.empty() )
               {
                  auto& tier = mTiers.top();
                  ++tier.current;
                  if( tier.current != tier.end )
                  {
                     is_step_satisfied = true;
                  }
                  else
                  {
                     mTiers.pop();
                  }
               }
            }
         }

         return *this;
      }

      bool operator!=( const Iterator& iterator ) const noexcept
      {
         if( !iterator.mTiers.empty() && !mTiers.empty() )
         {
            const auto& our_tier = mTiers.top();
            const auto& his_tier = iterator.mTiers.top();
            return our_tier.current != his_tier.current;
         }
         return false;
      }

   private:
      struct Tier
      {
         std::vector< Node >::const_iterator current;
         const std::vector< Node >::const_iterator end;
      };

   private:
      std::stack< Tier > mTiers;
   };
   const std::vector< Node >& roots;

   Iterator begin() const noexcept
   {
      return Iterator{ roots };
   }
   Iterator end() const noexcept
   {
      return Iterator{ std::vector< Node >{} };
   }
};

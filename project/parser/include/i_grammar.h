#pragma once

#include "i_syntax_node.h"

#include <functional>
#include <memory>
#include <optional>
#include <vector>
#include <deque>

using Stack = std::deque< ISyntaxNodeSP >;
using Nodes = std::vector< ISyntaxNodeSP >;

class IGrammar
{
public:
   struct AdditionPlan
   {
      Nodes nodes;
   };
   struct RemovePlan
   {
      Nodes nodes;
   };
   struct Plan
   {
      RemovePlan to_remove;
      AdditionPlan to_add;
   };

   std::optional< Plan > TryReduce( const Stack& stack, const ISyntaxNodeSP& look_ahead ) const
   {
      for( const auto& production : mProductions )
      {
         const auto& plan_opt = production( stack, look_ahead );
         if( !plan_opt )
            continue;

         return plan_opt.value();
      }

      return {};
   }

protected:
   std::vector< std::function< std::optional< Plan >( const Stack&, const ISyntaxNodeSP& ) > > mProductions;
};
using IGrammarSP = std::shared_ptr< IGrammar >;

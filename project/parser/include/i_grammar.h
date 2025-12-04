#pragma once

#include "i_syntax_node.h"

// #include "utils.h"
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <optional>
#include <vector>
#include <deque>
#include <variant>
#include <type_traits>
#include <map>

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

   // Plan or Progress
   using Readiness = double;
   using Similarity = double;
   struct Progress
   {
     Readiness readiness = 0.0;
     // Similarity similarity;
   };
   using PlanOrProgress = std::variant< Plan, Progress >;

   PlanOrProgress TryReduce( const Stack& stack, const ISyntaxNodeSP& look_ahead ) const
   {
      Progress result_progress;
      std::optional<IGrammar::Plan> plan_opt;
      for( const auto& production : mProductions )
      {
         const auto& plan_or_progress = production( stack, look_ahead );
          std::visit([&result_progress, &plan_opt](auto&& arg)
          {
            using T = std::decay_t<decltype(arg)>;
            if constexpr (std::is_same_v<T, IGrammar::Progress>)
            {
              if( arg.readiness > result_progress.readiness )
                result_progress = arg;
            } 
            else if constexpr (std::is_same_v<T, IGrammar::Plan>) 
            {
                plan_opt = arg;
            }          
          }, plan_or_progress);

          if( plan_opt )
              break;
      }

      if( plan_opt )
        return *plan_opt;

      return result_progress;
   }

protected:
   std::vector< std::function< PlanOrProgress( const Stack&, const ISyntaxNodeSP& ) > > mProductions;
};
using IGrammarSP = std::shared_ptr< IGrammar >;

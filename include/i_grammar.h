#pragma once

#include "base/f_syntax_node.h"
#include "base/minus_syntax_node.h"
#include "base/number_syntax_node.h"
#include "base/plus_syntax_node.h"
#include "i_feature.h"
#include "i_grammar.h"
#include "i_syntax_node.h"
#include "lexical_tokens.h"

#include <functional>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <optional>
#include <set>
#include <stack>
#include <string>
#include <variant>
#include <vector>

using Stack = std::deque< ISyntaxNodeSP >;
using Nodes = std::vector< ISyntaxNodeSP >;

// class Production
//{
// public:
//     struct AdditionPlan
//     {
//         Nodes nodes;
//     };
//     struct RemovePlan
//     {
//         Nodes nodes;
//     };
//     struct Plan
//     {
//         RemovePlan to_remove;
//         AdditionPlan to_add;
//     };

//    Production(const Plan& plan)
//        : mPlan{ plan }
//    {
//    }

//    Plan make_plan() const
//    {
//        return mPlan;
//    }

// private:
//     Plan mPlan;
// };

class IGrammar
{
public:
   //    using Features = std::vector<IFeatureSP>;
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

   std::optional< Plan > TryReduce( const Stack& stack ) const
   {
      //        for(const auto&[feature, production] : mProductionByFeature)
      //        {
      //            if( feature.size() > stack.size() )
      //                continue;

      //            auto stack_it = stack.begin();
      //            std::advance(stack_it, stack.size() - feature.size());

      //            auto template_it = feature.begin();

      //            bool is_fit = true;
      //            while(stack_it != stack.end() || template_it != feature.end() )
      //            {
      //                if( template_it == feature.end() )
      //                {
      //                    is_fit = true;
      //                    break;
      //                }
      //                if( stack_it == stack.end() )
      //                {
      //                    is_fit = false;
      //                    break;
      //                }

      //                const auto& stack_token_type = (*stack_it)->type();

      //                bool if_fitted = (*template_it)->IsFit(stack_token_type);
      //                if( !if_fitted )
      //                {
      //                    is_fit = false;
      //                    break;
      //                }

      //                ++template_it;
      //                ++stack_it;
      //            }
      //            if( is_fit )
      //                return production(stack);
      //        }

      for( const auto& production : mProductions )
      {
         const auto& plan_opt = production( stack );
         if( !plan_opt )
            continue;

         return plan_opt.value();
      }

      return {};
   }

protected:
   //    std::vector<std::pair<Features, std::function<Production(const Stack&)>>> mProductionByFeature;
   std::vector< std::function< std::optional< Plan >( const Stack& ) > > mProductions;
};
using IGrammarSP = std::shared_ptr< IGrammar >;

// static Production planAOpB(const Stack& stack, const std::string& operation_text, Token_Type token_type)
//{
//     auto it = stack.begin();
//     std::advance(it, stack.size() - 3);
//     const auto& f0 = *(it);
//     const auto& plus = *(++it);
//     const auto& f1 = *(++it);

//    Production::Plan plan;
//    plan.to_remove.nodes.push_back(f0);
//    plan.to_remove.nodes.push_back(plus);
//    plan.to_remove.nodes.push_back(f1);

//    const auto& d = std::make_shared<ISyntaxNode>(token_type);
//    d->Add(f0);
//    d->Add(f1);
////    d->token = {operation_text, token_type};
////    d->first = f0;
////    d->second = f1;
//    plan.to_add.nodes.push_back(d);
//    return Production{plan};
//}

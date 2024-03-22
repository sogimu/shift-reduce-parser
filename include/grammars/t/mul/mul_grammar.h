#pragma once

#include "enums.h"
#include "features/many_of.h"
#include "i_grammar.h"
#include "syntax_node.h"

#include <vector>

class E;
class T;
class P;

class Mul : public IGrammar
{
public:
   Mul()
   {
      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::MULTIPLY),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::MULTIPLY),
      //        one(Token_Type::E)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      ////        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::MULTIPLY),
      /// one(Token_Type::F)}, [this](const Stack& stack) -> Production /        { /            auto it =
      /// stack.begin(); /            std::advance(it, stack.size() - 3); /            const auto& e = *(it); / const
      /// auto& multiply = *(++it); /            const auto& f = *(++it);

      ////            Production::Plan plan;
      ////            plan.to_remove.nodes.push_back(e);
      ////            plan.to_remove.nodes.push_back(multiply);
      ////            plan.to_remove.nodes.push_back(f);

      ////            plan.to_add.nodes.push_back(e->first);
      ////            const auto& d = std::make_shared<SyntaxNode>();
      ////            d->token = {e->token.text, (e->token.text == "+" ? Token_Type::PLUS : Token_Type::MINUS) };
      ////            plan.to_add.nodes.push_back(d);

      ////            plan.to_add.nodes.push_back(e->second);
      ////            plan.to_add.nodes.push_back(multiply);
      ////            plan.to_add.nodes.push_back(f);

      ////            return Production{plan};
      ////        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::MULTIPLY),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::MULTIPLY),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::MULTIPLY),
      //        one(Token_Type::E)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::MULTIPLY),
      //        one(Token_Type::F)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::MULTIPLY),
      //        one(Token_Type::T)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::E), one(Token_Type::MULTIPLY),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::F), one(Token_Type::MULTIPLY),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::T), one(Token_Type::MULTIPLY),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::P), one(Token_Type::MULTIPLY),
      //        one(Token_Type::P)}, [this](const Stack& stack) -> Production
      //        {
      //            return planAOpB(stack);
      //        });
   }
   // private:
   //     Production planAOpB(const Stack& stack)
   //     {
   //         auto it = stack.begin();
   //         std::advance(it, stack.size() - 3);
   //         const auto& f0 = *(it);
   //         const auto& minus = *(++it);
   //         const auto& f1 = *(++it);

   //        Production::Plan plan;
   //        plan.to_remove.nodes.push_back(f0);
   //        plan.to_remove.nodes.push_back(minus);
   //        plan.to_remove.nodes.push_back(f1);

   //        const auto& d = std::make_shared<SyntaxNodeMul>(f0, f1);
   //        plan.to_add.nodes.push_back(d);
   //        return Production{plan};
   //    }
};

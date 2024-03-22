#pragma once

#include "div/syntax_node.h"
#include "enums.h"
#include "features/many_of.h"
#include "i_grammar.h"
#include "mul/syntax_node.h"
#include "syntax_node.h"

#include <vector>

class E;
class T;
class P;

class T : public IGrammar
{
public:
   T()
   {
      //        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::T),
      //        one(Token_Type::EOL)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& bol = *it;
      //            const auto& t = *(++it);
      //            const auto& eol = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(bol);
      //            plan.to_remove.nodes.push_back(t);
      //            plan.to_remove.nodes.push_back(eol);

      //            plan.to_add.nodes.push_back(t);

      //            return Production{plan};
      //        });
   }
};

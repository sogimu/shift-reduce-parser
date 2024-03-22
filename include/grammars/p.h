#pragma once

#include "enums.h"
#include "features/many_of.h"
#include "i_grammar.h"

#include <vector>

class E;
class T;
class P;

class P : public IGrammar
{
public:
   P()
   {
      //        mProductionByFeature.emplace_back(Features{one(Token_Type::OPEN_CIRCLE_BRACKET), one(Token_Type::F),
      //        one(Token_Type::CLOSE_CIRCLE_BRACKET)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& open_bracket = *(it);
      //            const auto& f = *(++it);
      //            const auto& close_bracket = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(open_bracket);
      //            plan.to_remove.nodes.push_back(f);
      //            plan.to_remove.nodes.push_back(close_bracket);

      //            const auto& d = std::make_shared<ISyntaxNode>();
      //            d->token = {f->token.text, Token_Type::P };
      //            d->first = f->first;
      //            d->second = f->second;
      //            plan.to_add.nodes.push_back(d);
      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::OPEN_CIRCLE_BRACKET), one(Token_Type::E),
      //        one(Token_Type::CLOSE_CIRCLE_BRACKET)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& open_bracket = *(it);
      //            const auto& e = *(++it);
      //            const auto& close_bracket = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(open_bracket);
      //            plan.to_remove.nodes.push_back(e);
      //            plan.to_remove.nodes.push_back(close_bracket);

      //            const auto& d = std::make_shared<ISyntaxNode>();
      //            d->token = {e->token.text, Token_Type::P };
      //            d->first = e->first;
      //            d->second = e->second;
      //            plan.to_add.nodes.push_back(d);
      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::OPEN_CIRCLE_BRACKET), one(Token_Type::T),
      //        one(Token_Type::CLOSE_CIRCLE_BRACKET)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& open_bracket = *(it);
      //            const auto& t = *(++it);
      //            const auto& close_bracket = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(open_bracket);
      //            plan.to_remove.nodes.push_back(t);
      //            plan.to_remove.nodes.push_back(close_bracket);

      //            const auto& d = std::make_shared<ISyntaxNode>();
      //            d->token = {t->token.text, Token_Type::P };
      //            d->first = t->first;
      //            d->second = t->second;
      //            plan.to_add.nodes.push_back(d);
      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::OPEN_CIRCLE_BRACKET), one(Token_Type::P),
      //        one(Token_Type::CLOSE_CIRCLE_BRACKET)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& open_bracket = *(it);
      //            const auto& p = *(++it);
      //            const auto& close_bracket = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(open_bracket);
      //            plan.to_remove.nodes.push_back(p);
      //            plan.to_remove.nodes.push_back(close_bracket);

      //            const auto& d = std::make_shared<ISyntaxNode>();
      //            d->token = {p->token.text, Token_Type::P };
      //            d->first = p->first;
      //            d->second = p->second;
      //            plan.to_add.nodes.push_back(d);
      //            return Production{plan};
      //        });

      //        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::P),
      //        one(Token_Type::EOL)}, [](const Stack& stack) -> Production
      //        {
      //            auto it = stack.begin();
      //            std::advance(it, stack.size() - 3);
      //            const auto& bol = *it;
      //            const auto& p = *(++it);
      //            const auto& eol = *(++it);

      //            Production::Plan plan;
      //            plan.to_remove.nodes.push_back(bol);
      //            plan.to_remove.nodes.push_back(p);
      //            plan.to_remove.nodes.push_back(eol);

      //            plan.to_add.nodes.push_back(p);

      //            return Production{plan};
      //        });
   }
};

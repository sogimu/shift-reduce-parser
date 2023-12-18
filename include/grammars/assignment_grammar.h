#pragma once

#include <vector>
#include "enums.h"
#include "i_grammar.h"
#include "features/many_of.h"

class F;
class E;
class T;
class P;

class Assigment : public IGrammar
{
public:
    Assigment()
    {
//        mProductionByFeature.emplace_back(Features{one(Token_Type::NAME), one(Token_Type::EQUAL), one(Token_Type::F), one(Token_Type::SEMICOLON)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 4);
//            const auto& name = *it;
//            const auto& equal = *(++it);
//            const auto& f = *(++it);
//            const auto& semicolon = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(name);
//            plan.to_remove.nodes.push_back(equal);
//            plan.to_remove.nodes.push_back(f);
//            plan.to_remove.nodes.push_back(semicolon);

//            const auto& assigment = std::make_shared<ISyntaxNode>();
//            assigment->token = {"=", Token_Type::ASSIGMENT};
//            assigment->first = name;
//            assigment->second = f;

//            plan.to_add.nodes.push_back(assigment);

//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::NAME), one(Token_Type::EQUAL), one(Token_Type::E), one(Token_Type::SEMICOLON)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 4);
//            const auto& name = *it;
//            const auto& equal = *(++it);
//            const auto& e = *(++it);
//            const auto& semicolon = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(name);
//            plan.to_remove.nodes.push_back(equal);
//            plan.to_remove.nodes.push_back(e);
//            plan.to_remove.nodes.push_back(semicolon);

//            const auto& assigment = std::make_shared<ISyntaxNode>();
//            assigment->token = {"=", Token_Type::ASSIGMENT};
//            assigment->first = name;
//            assigment->second = e;

//            plan.to_add.nodes.push_back(assigment);

//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::NAME), one(Token_Type::EQUAL), one(Token_Type::T), one(Token_Type::SEMICOLON)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 4);
//            const auto& name = *it;
//            const auto& equal = *(++it);
//            const auto& t = *(++it);
//            const auto& semicolon = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(name);
//            plan.to_remove.nodes.push_back(equal);
//            plan.to_remove.nodes.push_back(t);
//            plan.to_remove.nodes.push_back(semicolon);

//            const auto& assigment = std::make_shared<ISyntaxNode>();
//            assigment->token = {"=", Token_Type::ASSIGMENT};
//            assigment->first = name;
//            assigment->second = t;

//            plan.to_add.nodes.push_back(assigment);

//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::NAME), one(Token_Type::EQUAL), one(Token_Type::P), one(Token_Type::SEMICOLON)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 4);
//            const auto& name = *it;
//            const auto& equal = *(++it);
//            const auto& p = *(++it);
//            const auto& semicolon = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(name);
//            plan.to_remove.nodes.push_back(equal);
//            plan.to_remove.nodes.push_back(p);
//            plan.to_remove.nodes.push_back(semicolon);

//            const auto& assigment = std::make_shared<ISyntaxNode>();
//            assigment->token = {"=", Token_Type::ASSIGMENT};
//            assigment->first = name;
//            assigment->second = p;

//            plan.to_add.nodes.push_back(assigment);

//            return Production{plan};
//        });

//        mProductionByFeature.emplace_back(Features{one(Token_Type::BOL), one(Token_Type::ASSIGMENT), one(Token_Type::EOL)}, [](const Stack& stack) -> Production
//        {
//            auto it = stack.begin();
//            std::advance(it, stack.size() - 3);
//            const auto& bol = *it;
//            const auto& assigment = *(++it);
//            const auto& eol = *(++it);

//            Production::Plan plan;
//            plan.to_remove.nodes.push_back(bol);
//            plan.to_remove.nodes.push_back(assigment);
//            plan.to_remove.nodes.push_back(eol);

//            plan.to_add.nodes.push_back(assigment);

//            return Production{plan};
//        });

    }

};

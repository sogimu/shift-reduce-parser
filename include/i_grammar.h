#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <memory>
#include <stack>
#include <map>
#include <iomanip>
#include <functional>
#include <optional>

#include "lexical_tokens.h"

struct SyntaxNode;
using SyntaxNodeSP = std::shared_ptr<SyntaxNode>;
struct SyntaxNode
{
    LexicalTokens::LexicalToken token;
    SyntaxNodeSP first;
    SyntaxNodeSP second;
};

using Nodes = std::vector<SyntaxNodeSP>;
using Stack = std::deque<SyntaxNodeSP>;

class Production
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

    Production(const Plan& plan)
        : mPlan{ plan }
    {
    }

    Plan make_plan() const
    {
        return mPlan;
    }

private:
    Plan mPlan;
};

class IGrammar
{
public:
    using Feature = std::vector<Token_Type>;

    std::optional<Production> TryFindProduction(const Stack& stack) const
    {
        for(const auto&[feature, production] : mProductionByFeature)
        {
            if( feature.size() > stack.size() )
                continue;

            auto stack_it = stack.begin();
            std::advance(stack_it, stack.size() - feature.size());

            auto template_it = feature.begin();

            bool is_fit = true;
            while(stack_it != stack.end() || template_it != feature.end() )
            {
                if( template_it == feature.end() )
                {
                    is_fit = true;
                    break;
                }
                if( stack_it == stack.end() )
                {
                    is_fit = false;
                    break;
                }

                const auto& stack_token_type = (*stack_it)->token.type;
                const auto& template_token_type = (*template_it);

                if( stack_token_type != template_token_type )
                {
                    is_fit = false;
                    break;
                }

                ++template_it;
                ++stack_it;
            }
            if( is_fit )
                return production(stack);
        }

        return {};
    }
protected:
    std::vector<std::pair<Feature, std::function<Production(const Stack&)>>> mProductionByFeature;
};
using IGrammarSP = std::shared_ptr<IGrammar>;

static Production planAOpB(const Stack& stack, const std::string& operation_text, Token_Type token_type)
{
    auto it = stack.begin();
    std::advance(it, stack.size() - 3);
    const auto& f0 = *(it);
    const auto& plus = *(++it);
    const auto& f1 = *(++it);

    Production::Plan plan;
    plan.to_remove.nodes.push_back(f0);
    plan.to_remove.nodes.push_back(plus);
    plan.to_remove.nodes.push_back(f1);


    const auto& d = std::make_shared<SyntaxNode>();
    d->token = {operation_text, token_type};
    d->first = f0;
    d->second = f1;
    plan.to_add.nodes.push_back(d);
    return Production{plan};
}

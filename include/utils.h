#pragma once

#include <stack>

template <typename Node, typename PreFunc, typename PostFunc>
void iterative_dfs(const Node& start, PreFunc pre_func, PostFunc post_func)
{
    std::stack<std::pair<Node, bool>> stack;
    stack.push({start, true});

    while(!stack.empty())
    {
        const auto& [node, is_pre_order] = stack.top();
        stack.pop();

        if( is_pre_order )
        {
            bool is_found = pre_func(node);
            stack.push({node, false});

            if( !is_found )
            {
                if( node->first )
                    stack.push({node->first, true});

                if( node->second )
                    stack.push({node->second, true});
            }
        }
        else
        {
            post_func(node);
        }
    }

}

template <typename Node, typename PreFunc>
void iterative_dfs(const Node& start, PreFunc pre_func)
{
    iterative_dfs(start, pre_func, [](const auto&) {});
}

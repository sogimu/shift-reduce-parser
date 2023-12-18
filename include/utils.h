#pragma once

#include <stack>
#include <vector>
#include "i_syntax_node.h"
#include "syntax_node_empty_visitor.h"

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
                for( const auto& child : node->Children() )
                    stack.emplace(child, true);
//                if( node->first )
//                    stack.push({node->first, true});

//                if( node->second )
//                    stack.push({node->second, true});
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


template <typename Node, typename PreFunc, typename PostFunc>
void iterative_managed_dfs(const Node& start, PreFunc pre_func, PostFunc post_func)
{
    std::stack<std::pair<Node, bool>> stack;
    stack.push({start, true});

    while(!stack.empty())
    {
        const auto& [node, is_pre_order] = stack.top();
        stack.pop();

        if( is_pre_order )
        {
            const auto& children = pre_func(node);
            stack.push({node, false});

            if( !children )
                continue;

            for( const auto& child : children.value() )
                stack.emplace(child, true);
        }
        else
        {
            post_func(node);
        }
    }

}

template <typename Node, typename PreFunc>
void iterative_managed_dfs(const Node& start, PreFunc pre_func)
{
    iterative_managed_dfs(start, pre_func, [](const auto&) {});
}

// helper type for the visitor #4
template<class... Ts>
struct overloaded : Ts... { using Ts::operator()...; };
// explicit deduction guide (not needed as of C++20)
template<class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

using Stack = std::deque<ISyntaxNodeSP>;
static Stack last_n_syntax_nodes(const Stack& stack, size_t n)
{
    if( stack.size() < n )
        return {};

    auto it = stack.begin();
    std::advance(it, stack.size() - n);

    return Stack{ it, stack.end() };
}

static void iterate_over_last_n_nodes(const Stack& stack, size_t n, const SyntaxNodeEmptyVisitor::Handlers& handlers)
{
    const auto& visitor = std::make_shared<SyntaxNodeEmptyVisitor>( handlers );
    const auto& nodes = last_n_syntax_nodes(stack, n);
    for( const auto& node : nodes )
    {
        node->accept(visitor);
    }
}

template <typename Range>
class zip_container
{
    Range c1;
    Range c2;
public:
    zip_container(const Range& c1, const Range& c2) : c1(c1), c2(c2) {}

    class Iterator
    {
    public:
        using iterator_category = std::input_iterator_tag;
        using difference_type   = std::ptrdiff_t;
        using value_type = std::pair<std::optional<typename Range::Iterator::value_type>, std::optional<typename Range::Iterator::value_type>>;
        using reference = value_type&;
        using pointer = value_type*;

        Iterator( const auto& c1, const auto& c1end, const auto& c2, const auto& c2end)
            : mC1{ c1 }
            , mC1End{ c1end }
            , mC2( c2 )
            , mC2End{ c2end }
        {
        }

        value_type operator*() const noexcept
        {
            std::optional<typename Range::Iterator::value_type> a;
            if( mC1 != mC1End )
                a = *mC1;
            std::optional<typename Range::Iterator::value_type> b;
            if( mC2 != mC2End )
                b = *mC2;
            return { a, b };
        }

        Iterator operator++()
        {
            ++mC1;
            ++mC2;
            return *this;
        }

        bool operator!=(const Iterator& iterator) const noexcept
        {
            return mC1 != iterator.mC1 || mC2 != iterator.mC2;
            return false;
        }

        typename Range::Iterator mC1;
        typename Range::Iterator mC1End;
        typename Range::Iterator mC2;
        typename Range::Iterator mC2End;
    };

    auto begin() const
    {
         return Iterator(std::begin(c1), std::end(c1), std::begin(c2), std::end(c2));
    }

    auto end() const
    {
         return Iterator(std::end(c1), std::end(c1), std::end(c2), std::end(c2));
    }
};

template <typename C1>
zip_container<C1> zip(C1& c1, C1& c2)
{
    return zip_container<C1>(c1, c2);
}

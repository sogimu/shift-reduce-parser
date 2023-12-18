#include "doctest.h"

#include <memory>
#include <string>
#include <vector>
#include <initializer_list>
#include <optional>
#include "utils/dfs_pre_order_range.h"

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

class Entity;
using EntitySP = std::shared_ptr<Entity>;


class Entity
{
public:
    Entity(const std::string& name)
        : mName(name)
    {

    }
    std::vector<EntitySP>::iterator begin()
    {
        return mChildren.begin();
    }
    std::vector<EntitySP>::iterator end()
    {
        return mChildren.end();
    }

    std::string Name() const
    {
        return mName;
    }

    void Append(const EntitySP& entity )
    {
        mChildren.push_back(entity);
    }

private:
    std::string mName;
    std::vector<EntitySP> mChildren;
};

std::ostream& operator<<(std::ostream& o, const EntitySP& entity)
{
    o << entity->Name();
    return o;
}

TEST_CASE("DFS pre-order range")
{

    const size_t BRANCH_LENGTH = 3;

    const auto& root0 = std::make_shared<Entity>("root0");
    auto last_entity = root0;
    for (size_t i=0; i<BRANCH_LENGTH; ++i)
    {
        const auto& entity = std::make_shared<Entity>(std::to_string(i));
        last_entity->Append(entity);
    }

    const auto& root1 = std::make_shared<Entity>("root1");
    last_entity = root1;
    for (size_t i=0; i<BRANCH_LENGTH+2; ++i)
    {
        const auto& entity = std::make_shared<Entity>(std::to_string(i));
        last_entity->Append(entity);
    }

    // Act
        const auto& range0 = DfsRange<EntitySP>{std::vector<EntitySP> {root0} };
        for (const auto& entity : range0 )
        {
            std::cout << entity->Name() << std::endl;
        }

        const auto& range1 = DfsRange<EntitySP>{std::vector<EntitySP> {root1} };
        for (const auto& entity : range1 )
        {
            std::cout << entity->Name() << std::endl;
        }
    //CHECK(bank0[0]->Name() == "root");
    //CHECK(bank0[1]->Name() == "0");
    //CHECK(bank0[2]->Name() == "1");
    //CHECK(bank0[3]->Name() == "2");

    zip_container c(range0, range1);
    for( const auto& [a, b] : c)
    {
        if( a )
            std::cout << a.value();
        else
            std::cout << "nil";

        if( b )
            std::cout << b.value();
        else
            std::cout << "nil";

        if( a != b )
            std::cout << " <- differs";
        std::cout << std::endl;
    }

    const auto& r = std::mismatch(range0.begin(), range0.end(), range1.begin(), range1.end(), [](const auto& a, const auto& b)-> bool {
        return a->Name() == b->Name();
    });
    std::cout << *r.first << *r.second << std::endl;
}

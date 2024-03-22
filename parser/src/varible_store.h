#pragma once

#include <map>
#include <string>

using namespace std;

class VaribleStore
{
        public:
    void pushScope() { mScope.emplace_back( std::map<std::string, int>{} ); }

    void popScope() { mScope.pop_back(); }

    int& operator[]( const std::string& name ) { return mScope.back()[name]; }

    const int& operator[]( const std::string& name ) const { return mScope.back()[name]; }

        private:
    mutable std::deque<std::map<std::string, int>> mScope;
};

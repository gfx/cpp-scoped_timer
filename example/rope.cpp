#include <iostream>
#include <string>
#ifdef STLP_ROPE
#include <rope>
#else
#include <ext/rope>
#endif
#include "scoped_timer.hpp"

#ifdef STLP_ROPE
typedef std::rope<char> rope;
#else
typedef __gnu_cxx::rope<char> rope;
#endif

template <typename Rope>
void doit(const int N) {
    Rope s;
    for(int i = 0; i < N; ++i) {
        s.append("foo bar baz\n");
    }
}



int main() {
    using namespace gfx;

    const int N = 1000*1000;
    gfx::scoped_timer_cputime::elapsed_type e = 0.0;

    {
        gfx::scoped_timer_cputime t(e, "rope");
        doit<rope>(N);
    }
    {
        gfx::scoped_timer_cputime t(e, "rope");
        doit<rope>(N);
    }
    {
        gfx::scoped_timer_cputime t(e, "string");
        doit<std::string>(N);
    }
    {
        gfx::scoped_timer_cputime t(e, "string");
        doit<std::string>(N);
    }

    return 0;
}


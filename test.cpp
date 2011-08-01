#include "scoped_timer.hpp"

int main() {
    
    {
        gfx::scoped_timer_cputime::elapsed_type e = 0.0;

        {
            gfx::scoped_timer_cputime t(e, "cpu 1st");
            
            for(int i = 0; i < (10000 * 100); i++) {
                std::string s("foo");
            }
        }
        {
            gfx::scoped_timer_cputime t(e, "cpu 2nd");
            
            for(int i = 0; i < (10000 * 100); i++) {
                std::string s("foo");
            }
        }
    }

    {
        gfx::scoped_timer_wallclock::elapsed_type e = 0.0;
        {
            gfx::scoped_timer_wallclock t(e, "wallclock 1st");
            
            for(int i = 0; i < (10000 * 100); i++) {
                std::string s("foo");
            }
        }
        {
            gfx::scoped_timer_wallclock t(e, "wallclock 2nd");
            
            for(int i = 0; i < (10000 * 100); i++) {
                std::string s("foo");
            }
        }
    }

    return 0;
}


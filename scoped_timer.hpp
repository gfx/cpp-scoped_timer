#ifndef GFX_SCOPED_TIMER_
#define GFX_SCOPED_TIMER_

#include <cmath>
#include <iostream>
#include <boost/format.hpp>
#include <sys/time.h>

namespace gfx {

    template <class Derived, typename ElapsedType>
    class scoped_timer_base {
        public:
        typedef ElapsedType elapsed_type;

        scoped_timer_base(elapsed_type& e, const char* const name)
            : elapsed_(e),
              name_(name),
              t0_( static_cast<Derived*>(this)->gettime() ) { }

        ~scoped_timer_base() {
            const elapsed_type t1 = static_cast<Derived*>(this)->gettime();
            const elapsed_type e  = t1 - t0_;
            elapsed_ += e;

            this->report(e);
        }

        // [abstract] elapsed_type gettime();

        void report(const elapsed_type& e) {
            std::cout
                << boost::format("elapsed %.03f (%.03f) sec (%p:%s)")
                    % e % elapsed_ % &elapsed_ % name_
                << std::endl;
        }

        const std::string& name() { return name_; }
        
        private:
        elapsed_type& elapsed_;
        const std::string name_;
        elapsed_type const t0_;
    };

    class scoped_timer_cputime
            : public scoped_timer_base<scoped_timer_cputime, long double> {
        typedef scoped_timer_base<scoped_timer_cputime, long double> base;

        public:

        scoped_timer_cputime(elapsed_type& storage, const char* const name)
            : base(storage, name) { }

        elapsed_type gettime() {
            const std::clock_t t = std::clock();
            const std::clock_t p = CLOCKS_PER_SEC;
            return static_cast<elapsed_type>(t) / static_cast<elapsed_type>(p);
        }
    };

    class scoped_timer_wallclock
            : public scoped_timer_base<scoped_timer_wallclock, long double> {
        typedef scoped_timer_base<scoped_timer_wallclock, long double> base;

        public:

        scoped_timer_wallclock(elapsed_type& storage, const char* const name)
            : base(storage, name) { }

        elapsed_type gettime() {
            timeval tv;
            gettimeofday(&tv, NULL);
            const elapsed_type sec  = static_cast<elapsed_type>(tv.tv_sec);
            const elapsed_type usec = static_cast<elapsed_type>(tv.tv_usec);
            return sec + (usec / static_cast<elapsed_type>(100 * 10000));
        }
    };

} // namespace gfx

#endif // GFX_SCOPED_TIMER_


#ifndef FSDICT_STOPWATCH_H
#define FSDICT_STOPWATCH_H FSDICT_STOPWATCH_H


#include<sys/timeb.h>

namespace fsdict {
    class Stopwatch {
    public:
	Stopwatch();
	inline void start();
	inline unsigned long long readSeconds() const;
	inline unsigned long long readMilliseconds() const;

    private:
	timeb start_;
    };

    inline Stopwatch::Stopwatch() {
	start();
    }

    inline void Stopwatch::start() {
	ftime( &start_ );
    }

    inline unsigned long long Stopwatch::readSeconds() const {
	timeb now;
	ftime( &now );
	return now.time - start_.time;
    }

    inline unsigned long long Stopwatch::readMilliseconds() const {
	timeb now;
	ftime( &now );
	return ( now.time - start_.time ) * 1000 + ( now.millitm - start_.millitm );
    }

} // ns csl

#endif

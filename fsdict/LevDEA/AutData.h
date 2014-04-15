#ifndef AUTDATA_H
#define AUTDATA_H AUTDATA_H

#include<cstddef>
#include<fsdict/Global.h>

namespace fsdict {

    template< int k >
    class AutData;

    template<>
    class AutData< 0 > {
    public:
	static const size_t bitVectorLength;

	// The number of states per transition is 2^bitVectorLength . So, to retrieve the for state i and label n, use transitions[i* 2^bitVectorLength + n]
	static const int transitions[];

	// There are bitVectorLength values per state. So, to retrieve the n-th value for state i, use finalInfo[bitVectorLength*i + n]
	static const int finalInfo[];

	// There's one value (to be interpreted as bit-vector) per state. So, to retrieve the suffixMatch value for state i, use suffixMatch[i]
	static const bits64 suffixMatch[];
    };

    template<>
    class AutData< 1 > {
    public:
	static const size_t bitVectorLength;
	static const int transitions[];
	static const int finalInfo[];
	static const bits64 suffixMatch[];
    };

    template<>
    class AutData< 2 > {
    public:
	static const size_t bitVectorLength;
	static const int transitions[];
	static const int finalInfo[];
	static const bits64 suffixMatch[];
    };

} // ns fsdict

#endif

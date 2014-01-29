#ifndef FSDICT_TRANSTABLE_H
#define FSDICT_TRANSTABLE_H FSDICT_TRANSTABLE_H

#include "../Global.h"

namespace fsdict {
    typedef enum {
	TT_STANDARD,
	TT_PERFHASH
    } TransTableType;

    template< TransTableType tttype = TT_PERFHASH, typename InternalCharType__ = wchar_t, typename SizeType__ = uint32_t >
    class TransTable;
}

#include "./TransTable_standard.h"
#include "./TransTable_perfHash.h"

#endif

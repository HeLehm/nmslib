#include <stdint.h>

#ifndef MYLINGUA_CONSTANTS_H
#define MYLINGUA_CONSTANTS_H

namespace mylingua_constants {
    const uint32_t MYLINGUA_CHAR_VOCAB_LENGTH = 180; // * 32 = 5760
    const uint32_t MYLINGUA_WORD_VOCAB_LENGTH = 5000; // * 32 = 160k
    const uint32_t MYLINGUA_INTEREST_EMBEDDING_VEC_LEN = 768; // bert embeddings

    //should add up to 1
    const float MYLINGUA_CHAR_WEIGHT = 0.2;
    const float MYLINGUA_WORD_WEIGHT = 0.8;


    const float MYLINGUA_FREQ_WEIGHT = 0.2; // weighting in skill calculation
}

#endif


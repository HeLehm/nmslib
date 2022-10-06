/**
 * Non-metric Space Library
 *
 * Main developers: Bilegsaikhan Naidan, Leonid Boytsov, Yury Malkov, Ben Frederickson, David Novak
 *
 * For the complete list of contributors and further details see:
 * https://github.com/nmslib/nmslib
 *
 * Copyright (c) 2013-2018
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */
#ifndef _SPACE_MYLINGUA_DISTANCE_WORDS_FREQ_H_
#define _SPACE_MYLINGUA_DISTANCE_WORDS_FREQ_H_

#include <string>
#include <map>
#include <stdexcept>

#include "mylingua_constants.h"

#include <portable_popcount.h>
#include <string.h>
#include "global.h"
#include "object.h"
#include "utils.h"
#include "space.h"
#include "distcomp.h"
#include "space_bit_vector.h"
#include "my_isnan_isinf.h"

#define SPACE_MYLINGUA_DISTANCE_WORDS_FREQ "mylingua_distance_words_freq"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceMyLinguaDistanceWordsFreq : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceMyLinguaDistanceWordsFreq() {}
  virtual ~SpaceMyLinguaDistanceWordsFreq() {}

  virtual std::string StrDesc() const { return "Mylingua skill and interest weighted score"; }

  //PLAN:
  //TODO: EDIT PYTHON ENCODING STUFF
  //TODO: USE CONSTANTS AND ADD PYTHON BINDINGS
  //

  // sturcture:
  // 32bit filter | MYLINGUA_CHAR_VOCAB_LENGTH * 32 bits of char bits | MYLINGUA_WORD_VOCAB_LENGTH * 32 bits of word bits | MYLINGUA_INTEREST_EMBEDDING_VEC_LEN  * 32 bits of bert embedding vec | 32 bit uint count

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    
    /*
    CHECK(
      obj1->datalength() 
      > (sizeof(dist_uint_t) * (
        mylingua_constants::MYLINGUA_CHAR_VOCAB_LENGTH
        + mylingua_constants::MYLINGUA_WORD_VOCAB_LENGTH
        + 1
      )) // plus one for the filter uint
      + (sizeof(dist_t) * mylingua_constants::MYLINGUA_INTEREST_EMBEDDING_VEC_LEN)
    );
    +*/
    CHECK(obj1->datalength() == obj2->datalength());


    // x(obj1) = article , y(obj2) = user (query input)

    const dist_uint_t* x_int = reinterpret_cast<const dist_uint_t*>(obj1->data());
    const dist_uint_t* y_int = reinterpret_cast<const dist_uint_t*>(obj2->data());

    // compare topic filters 
    const dist_uint_t topic_x = *x_int; // article
    const dist_uint_t topic_y = *y_int; // user

    if (__builtin_popcount(topic_x & topic_y) == 0) {
      // topic mismatch so return highest distance possible
      return 2.0;
    }



    // shift x_int and y_int to the next dist_uint32_t
    x_int++;
    y_int++;


    //get char freqmedian of user
    

    //assuming sizeof(dist_t) == sizeof(dist_uint_t)
    x_int++;
    y_int++;

    
    // move pointers
    x_int += mylingua_constants::MYLINGUA_CHAR_VOCAB_LENGTH;
    y_int += mylingua_constants::MYLINGUA_CHAR_VOCAB_LENGTH;

  
    //get word freqmedian of user
    const dist_t userWordFreqMedian = *reinterpret_cast<const dist_t*>(y_int);
    //assuming sizeof(dist_t) == sizeof(dist_uint_t)
    x_int++;
    y_int++;

    std::cout << "[NMSLIB DEBUG] userWordFreqMedian = " << userWordFreqMedian << "\n";
    std::cout.flush();

    // get word dist 
    dist_t word_dist = BitFreqOnly<dist_t,dist_uint_t>(x_int, y_int, userWordFreqMedian,mylingua_constants::MYLINGUA_WORD_VOCAB_LENGTH);
    return word_dist;
  }

  DISABLE_COPY_AND_ASSIGN(SpaceMyLinguaDistanceWordsFreq);
};

}  // namespace similarity

#endif

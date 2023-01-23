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
#ifndef _SPACE_MYLINGUA_H_
#define _SPACE_MYLINGUA_H_

#include <string>
#include <map>
#include <stdexcept>


#include <portable_popcount.h>
#include <string.h>
#include "global.h"
#include "object.h"
#include "utils.h"
#include "space.h"
#include "distcomp.h"
#include "space_bit_vector.h"
#include "my_isnan_isinf.h"

#define SPACE_MYLINGUA "mylingua"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceMyLingua : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceMyLingua(dist_t wordWeight, dist_uint_t wordLength) :
    SpaceBitVector<dist_t,dist_uint_t>(), wordWeight_(wordWeight), wordLength_(wordLength) {} 
  virtual ~SpaceMyLingua() {}

  virtual std::string StrDesc() const {
    return "MyLingua Score, wordWeight=" + ConvertToString(wordWeight_) + ", wordLength=" + ConvertToString(wordLength_);
  }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());
    const size_t length = obj1->datalength() / sizeof(dist_uint_t)
                          - 1; // the last integer is an original number of elements
    CHECK(length >= wordLength_);
    const size_t charLength = length - wordLength_;

    // x(obj1) = article , y(obj2) = user (query input)
    const dist_uint_t* x_int = reinterpret_cast<const dist_uint_t*>(obj1->data()); // article
    const dist_uint_t* y_int = reinterpret_cast<const dist_uint_t*>(obj2->data()); // user

    dist_t word_dist = BitAndNorm<dist_t,dist_uint_t>(x_int, y_int, wordLength_);

    if (charLength == 0){
        return word_dist; // no char
    }

    dist_t char_dist = BitAndNorm<dist_t,dist_uint_t>(x_int + wordLength_, y_int + wordLength_, charLength);

    return (wordWeight_ * word_dist) + ((1 - wordWeight_) * char_dist);
  }

  private:
  dist_t wordWeight_;
  size_t wordLength_; 

  DISABLE_COPY_AND_ASSIGN(SpaceMyLingua);
};

}  // namespace similarity

#endif

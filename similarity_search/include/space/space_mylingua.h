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
  explicit SpaceMyLingua() {}
  virtual ~SpaceMyLingua() {}

  virtual std::string StrDesc() const { return "Mylingua skill and interest weighted score"; }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());
    // x(obj1) = article , y(obj2) = user (query input)

    const dist_uint_t* x_int = reinterpret_cast<const dist_uint_t*>(obj1->data());
    const dist_uint_t* y_int = reinterpret_cast<const dist_uint_t*>(obj2->data());

    // compare topic filters 
    const dist_uint_t topic_x = *x_int; // article
    const dist_uint_t topic_y = *y_int; // user

    if (__builtin_popcount(topic_x & topic_y) == 0) {
      // topic missmatch so rreturn highets distance possible
      return 1.0;
    }

    // shift x_int and y_int to the next dist_uint32_t
    x_int++;
    y_int++;

    // get vector_size (first dist_uint32_t)
    const dist_uint_t vector_size = *x_int;

    //std::cout<< "float vec size: " << vector_size << std::endl;

    // shift x_int and y_int to the next dist_uint32_t
    x_int++;
    y_int++;

    // check if data input is valid
    CHECK(obj1->datalength() > vector_size * sizeof(dist_t));

    const size_t length_int = (((obj1->datalength() - (vector_size * sizeof(dist_t))) / sizeof(dist_uint_t) - 3)); // minus 3 because: last is uint count and first is topic filter and second is vector size

    const dist_t* x_float = reinterpret_cast<const dist_t*>(x_int + length_int);
    const dist_t* y_float = reinterpret_cast<const dist_t*>(y_int + length_int);

    const size_t length_float = vector_size;

    dist_t interest_score = CosineSimilarity(x_float, y_float, length_float);

    // shoudl never happen but we still copy  it  from the original code
    if (my_isnan(interest_score)) throw runtime_error("Bug: NAN dist! (SpaceCosineSimilarity (Bit norm version varvec ))");
    dist_t skill_score = BitAndNorm<dist_t,dist_uint_t>(x_int, y_int, length_int);
    
    // compute interest weight
    dist_t fx = (1.0f - skill_score) * 0.55f;
    fx = (fx * fx) + 0.1f;

    return (skill_score * (1.0f - fx)) + (interest_score * fx);
  }

  DISABLE_COPY_AND_ASSIGN(SpaceMyLingua);
};

}  // namespace similarity

#endif

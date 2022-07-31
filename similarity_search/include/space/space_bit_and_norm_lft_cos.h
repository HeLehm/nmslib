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
#ifndef _SPACE_BIT_AND_NORM_LFT_COS_H_
#define _SPACE_BIT_AND_NORM_LFT_COS_H_

#include <string>
#include <map>
#include <stdexcept>

#include <string.h>
#include "global.h"
#include "object.h"
#include "utils.h"
#include "space.h"
#include "distcomp.h"
#include "space_bit_vector.h"
#include "my_isnan_isinf.h"

#define SPACE_BIT_AND_NORM_LFT_COS "bit_and_norm_lft_cos"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceBitAndNormLftCos : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceBitAndNormLftCos() {}
  virtual ~SpaceBitAndNormLftCos() {}

  virtual std::string StrDesc() const { return "Left normalized bit and distance with cosine simulatity fr last 768 floats"; }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 768 * sizeof(dist_t));
    CHECK(obj1->datalength() == obj2->datalength());

    const dist_uint_t* x_int = reinterpret_cast<const dist_uint_t*>(obj1->data());
    const dist_uint_t* y_int = reinterpret_cast<const dist_uint_t*>(obj2->data());

    const size_t length_int = (((obj1->datalength() - (768 * sizeof(dist_t))) / sizeof(dist_uint_t) - 1));

    
    const dist_t* x_float = reinterpret_cast<const dist_t*>(x_int + length_int);
    const dist_t* y_float = reinterpret_cast<const dist_t*>(y_int + length_int);
    const size_t length_float = 768;

    dist_t val = 1.0 - CosineSimilarity(x_float, y_float, length_float);


    // shoudl never happen but we still copy  it  from the original code
    if (my_isnan(val)) throw runtime_error("Bug: NAN dist! (SpaceCosineSimilarity (Bit norm version))");

    return BitAndNorm<dist_t,dist_uint_t>(x_int, y_int, length_int) +  val;
  }

  DISABLE_COPY_AND_ASSIGN(SpaceBitAndNormLftCos);
};

}  // namespace similarity

#endif

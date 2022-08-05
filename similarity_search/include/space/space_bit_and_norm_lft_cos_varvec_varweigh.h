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
#ifndef _SPACE_BIT_AND_NORM_LFT_COS_VARVEC_VARWEIGH_H_
#define _SPACE_BIT_AND_NORM_LFT_COS_VARVEC_VARWEIGH_H_

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

#define SPACE_BIT_AND_NORM_LFT_COS_VARVEC_VARWEIGH "bit_and_norm_lft_cos_varvec_varweigh"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceBitAndNormLftCosVarvecVarweigh : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceBitAndNormLftCosVarvecVarweigh() {}
  virtual ~SpaceBitAndNormLftCosVarvecVarweigh() {}

  virtual std::string StrDesc() const { return "Left normalized bit and distance with cosine simulatity fr last x floats weighted by another float"; }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(sizeof(dist_t) == sizeof(dist_uint_t))
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());
    // x(obj1) = article , y(obj2) = user (query input)

    const dist_uint_t* x_int = reinterpret_cast<const dist_uint_t*>(obj1->data());
    const dist_uint_t* y_int = reinterpret_cast<const dist_uint_t*>(obj2->data());

    // get vector_size (first dist_uint32_t)
    const dist_uint_t float_vector_size = *x_int;
    
    // shift x_int and y_int to the next dist_uint32_t
    x_int += 1;
    y_int += 1;

    const size_t datalength = obj1->datalength() - (2 * sizeof(dist_uint_t));
    const size_t length_int_and_one_float = datalength - (float_vector_size * sizeof(dist_t));
    const size_t length_int = (length_int_and_one_float / sizeof(dist_uint_t)) - 1; //  because of that one float and we checked if floaz size = unint size


    const dist_t* x_float = reinterpret_cast<const dist_t*>(x_int + length_int);
    const dist_t* y_float = reinterpret_cast<const dist_t*>(y_int + length_int);

    const dist_t weight = *y_float;

    //std::cout<< "weight" << weight << std::endl;

    y_float += 1;
    x_float += 1;

    const dist_t cosVal = CosineSimilarity(x_float, y_float, float_vector_size) * (1. - weight);

    // shoudl never happen but we still copy  it  from the original code
    if (my_isnan(cosVal)) throw runtime_error("Bug: NAN dist! (SpaceCosineSimilarity (Bit norm version varvec ))");

    const dist_t bitnormVal = BitAndNorm<dist_t,dist_uint_t>(x_int, y_int, length_int) * weight;

    return cosVal + bitnormVal;
    
  }

  DISABLE_COPY_AND_ASSIGN(SpaceBitAndNormLftCosVarvecVarweigh);
};

}  // namespace similarity

#endif

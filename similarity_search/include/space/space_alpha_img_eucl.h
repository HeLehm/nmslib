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
#ifndef _SPACE_ALPHA_IMG_EUCL_H_
#define _SPACE_ALPHA_IMG_EUCL_H_

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

#define SPACE_ALPHA_IMG_EUCL "alpha_img_eucl"

namespace similarity {

template <typename dist_t>
class SpaceAlphaImgEucl : public VectorSpaceSimpleStorage<dist_t> {
public:
  SpaceAlphaImgEucl() {}
  virtual std::string StrDesc() const {
    return "Euclidian distance for alpha images. Input data is expencted as: channel1(0,0), channel2(0,0), channel3(0,0), alpha(0,0), chnnel1(0,1), channel2(0,1), channel3(0,1), alpha(0,1), ...";
  }
  protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());

    dist_t res = 0, diff = 0;

    const dist_t* x = reinterpret_cast<const dist_t*>(obj1->data());
    const dist_t* y = reinterpret_cast<const dist_t*>(obj2->data());
    const size_t length = obj1->datalength() / sizeof(dist_t);
    
    CHECK(length % 4 == 0);

    for (size_t i = 0; i < length / 4; ++i) {
      dist_t alpha_x = x[i * 4 + 3];
      dist_t alpha_y = y[i * 4 + 3];

      for (size_t u = 0; u < 3; ++u) {
        diff = x[i * 4 + u] - y[i * 4 + u];
        diff *= alpha_x * alpha_y;
        res += diff * diff;
      }

    }

    return res;
  }

  DISABLE_COPY_AND_ASSIGN(SpaceAlphaImgEucl);
};

}  // namespace similarity

#endif

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
#ifndef FACTORY_SPACE_ALPHAIMG_EUCL_H
#define FACTORY_SPACE_ALPHAIMG_EUCL_H

#include <space/space_alpha_img_eucl.h>

namespace similarity {

template <typename dist_t>
Space<dist_t>* CreateAplhaImgEucl(const AnyParams& AllParams) {
  return new SpaceAlphaImgEucl<dist_t>();
}

/*
 * End of creating functions.
 */

}

#endif

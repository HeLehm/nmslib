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
#ifndef FACTORY_SPACE_BIT_AND_NORM_LFT_H
#define FACTORY_SPACE_BIT_AND_NORM_LFT_H

#include <space/space_bit_and_norm_lft.h>

namespace similarity {

/*
 * Creating functions.
 */

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateBitAndNormLft(const AnyParams& /* ignoring params */) {
  return new SpaceBitAndNormLft<dist_t,dist_uint_t>();
}

/*
 * End of creating functions.
 */
}

#endif
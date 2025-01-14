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
#ifndef FACTORY_SPACE_TEST_ENCODE_FLOAT_H
#define FACTORY_SPACE_TEST_ENCODE_FLOAT_H

#include <space/space_test_encode_float.h>

namespace similarity {

/*
 * Creating functions.
 */

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateTestEncodeFloat(const AnyParams& /* ignoring params */) {
  return new SpaceTestEncodeFloat<dist_t,dist_uint_t>();
}

/*
 * End of creating functions.
 */
}

#endif
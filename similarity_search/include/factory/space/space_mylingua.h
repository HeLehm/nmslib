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
#ifndef FACTORY_SPACE_MYLINGUA_H
#define FACTORY_SPACE_MYLINGUA_H

#include <space/space_mylingua.h>

namespace similarity {

/*
 * Creating functions.
 */

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLingua(const AnyParams& AllParams) {
  AnyParamManager pmgr(AllParams);

  dist_t wordWeight;
  dist_uint_t wordLength;

  pmgr.GetParamRequired("wordWeight",  wordWeight);
  pmgr.GetParamRequired("wordLength",  wordLength);

  pmgr.CheckUnused();

  return new SpaceMyLingua<dist_t,dist_uint_t>(wordWeight, wordLength);
}

/*
 * End of creating functions.
 */
}

#endif
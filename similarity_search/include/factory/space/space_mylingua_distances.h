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
#ifndef FACTORY_SPACE_MYLINGUA_DISTANCES_H
#define FACTORY_SPACE_MYLINGUA_DISTANCES_H

#include <space/space_mylingua_distance_char_freq.h>
#include <space/space_mylingua_distance_char_known.h>
#include <space/space_mylingua_distance_words_freq.h>
#include <space/space_mylingua_distance_words_known.h>
#include <space/space_mylingua_distance_semantic.h>

#include <space/space_mylingua_just_skill.h>

namespace similarity {

/*
 * Creating functions.
 */

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaDistanceCharFreq(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaDistanceCharFreq<dist_t,dist_uint_t>();
}

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaDistanceCharKnown(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaDistanceCharKnown<dist_t,dist_uint_t>();
}

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaDistanceWordsFreq(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaDistanceWordsFreq<dist_t,dist_uint_t>();
}

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaDistanceWordsKnown(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaDistanceWordsKnown<dist_t,dist_uint_t>();
}

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaDistanceSemantic(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaDistanceSemantic<dist_t,dist_uint_t>();
}

template <typename dist_t, typename dist_uint_t>
inline Space<dist_t>* CreateMyLinguaJustSkill(const AnyParams& /* ignoring params */) {
  return new SpaceMyLinguaJustSkill<dist_t,dist_uint_t>();
}


/*
 * End of creating functions.
 */
}

#endif
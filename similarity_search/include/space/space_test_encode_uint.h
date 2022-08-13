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
#ifndef _SPACE_TEST_ENCODE_UNIT_H_
#define _SPACE_TEST_ENCODE_UNIT_H_

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

#define SPACE_TEST_ENCODE_UINT "test_encode_uint"

namespace similarity {

template <typename dist_t, typename dist_uint_t>
class SpaceTestEncodeUint : public SpaceBitVector<dist_t,dist_uint_t> {
 public:
  explicit SpaceTestEncodeUint() {}
  virtual ~SpaceTestEncodeUint() {}

  virtual std::string StrDesc() const { return "returns the obj as  uint32"; }

 protected:
  virtual dist_t HiddenDistance(const Object* obj1, const Object* obj2) const {
    CHECK(obj1->datalength() > 0);
    CHECK(obj1->datalength() == obj2->datalength());
    
    const dist_uint_t* y = reinterpret_cast<const dist_uint_t*>(obj2->data());

    return *y;
  }

  DISABLE_COPY_AND_ASSIGN(SpaceTestEncodeUint);
};

}  // namespace similarity

#endif

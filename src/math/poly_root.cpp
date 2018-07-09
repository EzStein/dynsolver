#include "poly_root.h"

#include "math/complex.h"

namespace dynsolver {
namespace math {

poly_root::poly_root(const complex& root, size_t multiplicity)
  : root(root), multiplicity(multiplicity) { }

const complex& poly_root::get_root() const {
  return root;
}

size_t poly_root::get_multiplicity() const {
  return multiplicity;
}

} // namespace math
} // namespace dynsolver

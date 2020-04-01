#ifndef MODEL_H
#define MODEL_H

#include <memory>

#include "mp/problem.h"

namespace mp {

/// class Model extends Problem to store custom constraints
template <class Allocator>
class BasicModel : public BasicProblem<Allocator> {
protected:
  using PConstraint = std::unique_ptr<BasicConstraint>;

private:
  std::vector<PConstraint> custom_constr_;

public:

  /** Returns the number of custom constraints. */
  int num_custom_cons() const { return static_cast<int>(custom_constr_.size()); }

  /** Returns custom constraint i */
  const BasicConstraint* custom_con(int i) const {
    internal::CheckIndex(i, num_custom_cons());
    return custom_constr_[i].get();
  }

  /// Add custom constraint. Takes ownership
  void AddConstraint(BasicConstraint* pbc) {
    PConstraint pc;
    pc.reset(pbc);
    AddConstraint(std::move(pc));
  }
  void AddConstraint(PConstraint&& pc) {
    custom_constr_.push_back(std::move(pc));
  }
};

} // namespace mp

#endif // MODEL_H

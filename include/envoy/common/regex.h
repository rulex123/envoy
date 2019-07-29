#pragma once

#include <memory>

#include "envoy/common/pure.h"

#include "absl/strings/string_view.h"

namespace Envoy {
namespace Regex {

/**
 * fixfix
 */
class CompiledMatcher {
public:
  virtual ~CompiledMatcher() = default;

  /**
   * fixfix
   */
  virtual bool match(absl::string_view value) const PURE;
};

using CompiledMatcherPtr = std::unique_ptr<const CompiledMatcher>;

} // namespace Regex
} // namespace Envoy

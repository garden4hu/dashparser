#pragma once

#include <memory>

namespace dash {
/**
 * This is a helper that wraps C style API objects that need to be deleted with
 * a smart pointer. Inspired by Envoy. Thanks.
 */
template <class T, void (*deleter)(T*)>
class CSmartPtr : public std::unique_ptr<T, void (*)(T*)> {
  public:
    CSmartPtr() : std::unique_ptr<T, void (*)(T*)>(nullptr, deleter) {}
    CSmartPtr(T* object) : std::unique_ptr<T, void (*)(T*)>(object, deleter) {}
};
}  // namespace dash

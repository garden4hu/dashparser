#pragma once

#ifndef DASH_C_SMART_PTR_H_
#define DASH_C_SMART_PTR_H_

#include <memory>

namespace dash
{
/**
 * This is a helper that wraps C style API objects that need to be deleted with a smart pointer.
 * Inspired by Envoy. Thanks.
 */
	template <class T, void (*deleter)(T*)>
	class CSmartPtr : public std::unique_ptr<T, void (*)(T*)> {
	public:
		CSmartPtr() : std::unique_ptr<T, void (*)(T*)>(nullptr, deleter) {}
		CSmartPtr(T* object) : std::unique_ptr<T, void (*)(T*)>(object, deleter) {}
	};
}

#endif // !DASH_C_SMART_PTR_H_

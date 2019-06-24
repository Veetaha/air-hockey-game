#pragma once

/**
 * Represents a default constructible functor that calls the specified `finalize` function
 * when it gets invoked. It is meant to be default constructed so that it could be used
 * as a deleter argument for `std::unique_ptr` without having to specify the `finalize`
 * function as the second parameter at its construction.
 *
 * TODO: convert to lambda with C++20, as it brings default constructible lambdas and
 * lambdas in unevaluated contexts.
 */
template <typename TInstance, void (*finalize)(TInstance* self)>
struct Finalizer {
	inline void operator()(TInstance* self) noexcept(noexcept(finalize(self))) {
		finalize(self);
	}
};
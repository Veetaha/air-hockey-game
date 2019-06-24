#pragma once

#include "Errors.h"

class Utils {
public:
	template <typename TErr, typename T>
	static T* notNullOrThrow(T* ptr) {
		if (!ptr) throw TErr("Null pointer check failed");
		return ptr;
	}

};


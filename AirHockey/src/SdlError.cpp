#include "SdlError.h"

using namespace std::string_literals;

SdlError::SdlError(std::string&& messagePrefix):
	m_errMessage(std::move(messagePrefix) + ": "s + SDL_GetError())
	{}

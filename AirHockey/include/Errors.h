#pragma once

#include <exception>	

struct Error : public std::exception {
	explicit Error(std::string&& message) noexcept : m_errMessage(std::move(message)) {}

	const char* what() const override {
		return m_errMessage.c_str();
	}

private:
	const std::string m_errMessage;
};

struct SdlError : public Error {
	explicit SdlError(std::string&& message): 
		Error(message + std::string(": ") + SDL_GetError())  
	{}
};

struct SdlImgError : public Error {
	explicit SdlImgError(std::string&& message):
		Error(message + std::string(": ") + IMG_GetError()) 
	{}
};
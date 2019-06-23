#pragma once

#include <exception>

class SdlError: std::exception {
public:
	SdlError(std::string&& message);

	const char* what() const override {
		return m_errMessage.c_str(); 
	}

private:
	const std::string m_errMessage;
};


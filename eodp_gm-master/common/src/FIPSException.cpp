#include "FIPSException.hpp"

//! @param function Function or method that throws the exception.
//! @param customMessage Message describing the exception.
FIPSException::FIPSException(const std::string& customMessage,
    const std::string& function, const std::string& moduleName) :
    customMessage(function + std::string("@") + moduleName + std::string(": ") + customMessage)
{
  // Construct
}

FIPSException::~FIPSException()
{
	// Destroy
}


//! @return Message telling the method that throws the exception and the cause.
const char* FIPSException::what () const throw ()
{
    const char *auxMess = this->customMessage.c_str();
    return auxMess;
}


#ifndef COMMON_SRC_FIPSEXCEPTION_HPP_
#define COMMON_SRC_FIPSEXCEPTION_HPP_

#include <string>
#include <exception>
#include "Common.hpp"

class FIPSException : public std::exception
{
	public:

		// Constructor
		FIPSException(const std::string& customMessage, const std::string& function,
		    const std::string& moduleName = GEOMETRY_MODULE_NAME);

		// Destructor
		virtual ~FIPSException();

    virtual const char* what() const throw();

private:
    // Description of exception
    std::string customMessage;
};

#endif /* COMMON_SRC_FIPSEXCEPTION_HPP_ */

#include "GMException.hpp"

GMException::GMException(const std::string& customMessage, const std::string& function) :
    FIPSException(customMessage, function, GEOMETRY_MODULE_NAME)
{
  // Construct
}

GMException::~GMException()
{
  // Destroy
}


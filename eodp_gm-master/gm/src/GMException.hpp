#ifndef GM_SRC_GMEXCEPTION_HPP_
#define GM_SRC_GMEXCEPTION_HPP_

#include "Common.hpp"
#include "FIPSException.hpp"

class GMException: public FIPSException
{

  public:

    // Constructor
    GMException(const std::string& customMessage, const std::string& function);

    // Destructor
    virtual ~GMException();
};

#endif /* GM_SRC_GMEXCEPTION_HPP_ */

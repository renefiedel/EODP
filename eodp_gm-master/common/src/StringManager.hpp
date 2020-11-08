#ifndef COMMON_SRC_STRINGMANAGER_HPP_
#define COMMON_SRC_STRINGMANAGER_HPP_

#include <algorithm>
#include <iostream>
#include <istream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <array>

#include <boost/current_function.hpp>

using namespace std;

// class StringManager: This class formats input strings into meaningful
// information
class StringManager
{
  public:

    //! Constructor
    StringManager();

    //! Destructor
    virtual ~StringManager();

    //! Split function
    //! @param str input string
    //! @param delimiter delimiter
    //! @return vector of strings
    static vector<string> split(string str, char delimiter);

    //! String vector to char array
    //! @param stringVector vector of strings
    //! @param stringArray string array
    static void copyStringVectorToStringArray(vector<string>& stringVector, char*** stringArray);

    //! Frees the memory of the string array
    //! @param numString number of strings
    //! @param stringArray string array
    static void freeStringArray(int numString, char*** stringArray);

    //! Frees the memory of the string array
    //! @param array array
    static void freeArray(void** array);

  private:
};

#endif /* COMMON_SRC_STRINGMANAGER_HPP_ */

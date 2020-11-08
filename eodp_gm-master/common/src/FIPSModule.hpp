#ifndef COMMON_SRC_FIPSMODULE_HPP_
#define COMMON_SRC_FIPSMODULE_HPP_

#include "Common.hpp"
#include "StringManager.hpp"
#include "configuration.hh"
#include "FIPSException.hpp"

using dms::config::Configuration;

// class FIPSModule: This class implements the functions that
// are common to all the FIPS modules
class FIPSModule
{
  public:

    // Constructor
    FIPSModule();

    // Destructor
    virtual ~FIPSModule();

    // Initialize module
    void initModule(const string &module_name, int argc, char **argv);

    // Get the local configuration
    shared_ptr<Configuration>& getConfigLocal();

    // Process the module - all the operations of each module
    // are encapsulated from here
    virtual void processModule()
    {
      // empty
    };


    // Loads an ASCII file with two columns
    template <typename T>
    inline void loadAsciiTwoColumns(const string filename,
        std::vector<T> &v1, std::vector<T> &v2)
    {
      fileExists(filename);
      std::ifstream f(filename);
      std::string line;

      while (std::getline(f, line))
      {
        T col1 = 0.0, col2 = 0.0;
        std::istringstream ss(line);
        ss >> col1 >> col2;
        v1.push_back(col1);
        v2.push_back(col2);
      }

      if (v1.size() == 0)
      {
        throw(FIPSException(
            "No lines found in " + filename,
            BOOST_CURRENT_FUNCTION));
      }

      std::cout << "[D] Finished reading "
          << filename << endl;
    }

  protected:

    //! Local configuration. Map from the file
    shared_ptr<Configuration> configLocalMap;

    //! Folder containing the output files
    string outputFolderName;

    //! Application absolute path
    std::string app_directory;

  private:

    inline std::string getDirectoryFromPath(const std::string &spath)
    {
      static const std::string separator = "/\\";

      std::vector <std::string> v;
      std::string::size_type npos = 0;

      // Breaks spath in its sub-directory elements.
      while ((npos = spath.find_first_of(separator, npos)) != std::string::npos)
        v.push_back(spath.substr(0, ++npos));

      return v.empty() ? "" : *v.rbegin();
    }

};

#endif /* COMMON_SRC_FIPSMODULE_HPP_ */

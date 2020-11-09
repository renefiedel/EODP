#include "FIPSModule.hpp"
#include <boost/current_function.hpp>
#include <boost/filesystem.hpp>

FIPSModule::FIPSModule()
{
}

FIPSModule::~FIPSModule()
{
  // Destroy
}

void FIPSModule::initModule(const string &module_name, int argc, char **argv)

{
  std::cout << "[I] bin directory " << argv[0] << std::endl;
  // Get the directory where the executable (argv[0]) is located.
  app_directory = getDirectoryFromPath(argv[0]);
  std::cout << "[I] Application directory " << app_directory << std::endl;

  // Load local configurations
  configLocalMap = make_shared<Configuration>(true, std::cout);

  std::cout << "[I] Reading local configuration file '" << argv[1] << " "
      << endl;

  if (configLocalMap->read(argv[1]) != 0)
  {
    throw FIPSException("Error reading local configuration file",
    BOOST_CURRENT_FUNCTION);
  }

  // Load the output folder's name
  if (strlen(argv[2]) > 0)
  {
    std::string output_parameter = argv[2];

    if (!boost::filesystem::is_directory(output_parameter))
    {
      // Create output directory
      boost::filesystem::path dir(output_parameter.c_str());
      boost::filesystem::create_directory(dir);
    }

    outputFolderName = output_parameter;
  }
}


shared_ptr<Configuration>& FIPSModule::getConfigLocal()
{
  return configLocalMap;
}





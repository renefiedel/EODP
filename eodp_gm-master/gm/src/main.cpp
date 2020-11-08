#include "GeometryModule.hpp"

int main(int argc, char* argv[])
{
  try
  {
    // Declare processor
    shared_ptr<GeometryModule> processor = make_shared<GeometryModule>();

    // Initialize module if it is not been initialized yet
    processor->initModule(GEOMETRY_MODULE_NAME, argc, argv);

    // Run the processor
    processor->processModule();
  }
  catch(GMException& e)
  {
    cerr << "Error " << e.what() << endl;
  }

  return 0;
}

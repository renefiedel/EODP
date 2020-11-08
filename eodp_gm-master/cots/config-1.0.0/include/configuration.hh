// 2016 Copyright DEIMOS SPACE SLU

#ifndef DMS_CONFIGFILES_H_
#define DMS_CONFIGFILES_H_

#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <boost/algorithm/string/predicate.hpp>

namespace dms {

namespace config {

/// \class Configuration
///
/// Configuration is a library to read configuration files in XML
/// format.
///
/// Usage (works with most types):
///
/// if(config.get(group, param_name, &result) != 0) { error; }
///
class Configuration {
public:
  /// Constructor
  explicit Configuration(bool log_everything_ = true,
                         std::ostream &log_ = std::cerr)
      : log_everything{log_everything_}, log{log_} {};

  /// Reads the configuration file.
  int read(const std::string &filepath);

  /*******************************/
  /******* READ OPERATIONS *******/
  /*******************************/

  /// Gets the value of an element
  template <typename T>
  int get(const std::string &group, const std::string &keyword,
          T *value, const std::string &app_path = "") const {
    // Find keyword in store
    std::string path{group + "/" + keyword};
    auto d = store.find(path);
    if (d != store.end()) {
      // Convert to any type using a stringstream
      std::stringstream ss;
      if (!app_path.empty())
      {
        ss << app_path;
        if (!boost::algorithm::ends_with(app_path, "/"))
        {
          ss << "/";
        }
      }
      ss << d->second;
      ss >> (*value);
      if (log_everything) {
        log << "[I] Configuration: '" << path << "' = '" << (*value) << "'.\n";
      }
      return 0;
    }
    log << "[E] Configuration: '" << path << "' not found in config file.\n";
    return -1;
  }

  /*******************************/
  /**** READ ARRAY OPERATIONS ****/
  /*******************************/

  /// Gets the value of an array
  template <typename T>
  int get(const std::string &group, const std::string &keyword,
          std::vector<T> *values) const {
    // Find keyword in store
    std::string path{group + "/" + keyword};
    auto d = store.find(path);
    if (d != store.end()) {
      // Convert to any type using a stringstream
      T v;
      std::istringstream iss(d->second);
      std::stringstream msg{};
      // Loop on the space-separated values
      while (iss >> v) {
        values->push_back(v);
        if (values->size() < 4) {
          msg << values->back() << " ";
        }
      }
      if (log_everything) {
        log << "[I] Configuration: '" << path << "' = array[" << values->size()
            << "] = {" << msg.str() << "etc}'.\n";
      }
      return 0;
    }
    log << "[E] Configuration: '" << path << "' not found in config file.\n";
    return -1;
  }

  /// Destructor
  ~Configuration() {}

private:
  bool log_everything;
  std::ostream &log;
  std::string filepath;
  std::string xml_root;
  std::map<std::string, std::string> store;
};
} // end namespace config
} // end namespace dms

#endif

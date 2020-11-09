// Copyright 2016 DEIMOS SPACE

#ifndef DMS_NCMAP_NCMAP_H_
#define DMS_NCMAP_NCMAP_H_

#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "ncmap_structs.hh"

namespace dms {

namespace ncmap {

using std::string;

/// \class NetCDFMap
///
/// NCMAPS is a library to support the production of NetCDF files (the
/// "product" files).
///
/// Normally, the structure, variable names and data types of the
/// NetCDF files are hardcoded in the source code. The NCMAP library
/// allows this structure to be controlled by an XML configuration
/// file. It other words, is makes the structure (including the names
/// of the variables, dimensions and attributes, and also the data
/// types) of the output files configurable.
///
/// Each variable/dimension/group/attribute that can be
/// accessed/modified from the client code has a "keyword" tag. These
/// keywords are hardcoded in the source code but they are independent
/// from the actual name that the element has in the netcdf file.
///
/// The NCMAP file can have an arbitrary number of files. Also,
/// elements can be given a default value that can be changed from
/// within the code. If an element does not have a "keyword" tag, then
/// this element will be written to the netcdf files but it cannot be
/// inspected or changed from within the client code.
///
/// Attributes and dimensions must be modified using the NetCDFMap
/// API.
///
/// Variables, on the other hand, shall be written by the client
/// code using the NetCDF library API. The client code can obtain the
/// necessary ncid and varid from the NetCDFMap API.
///
/// Variables must have unique keywords, but several attributes and
/// dimensions can have the same keyword. In that case, setting the
/// value for the keyword (through the NetCDFMap API) will change all
/// the netcdf elements associated to it.
///
/// The following is an example of a NCMAP XML file (see the "tests"
/// to find a more complete example):
///
/// <productFileMap>
/// <netcdfFile name="output_01.nc" keyword="measurements1">
///
///   <attribute name="product_name" type="NC_STRING"
///   keyword="product_name">Product Name</attribute>
///
///   <attribute name="creation_time" type="NC_STRING"
///   keyword="creation_time">2000/01/01</attribute>
///
///   <dimension name="rows" keyword="product_rows"/>
///   <dimension name="columns" keyword="product_columns"/>
///   <group name="Channel1" keyword="CHAN01">
///     <attribute name="comment" type="NC_STRING">Comment</attribute>
///     <variable name="BT" type="NC_USHORT" dimensions="rows columns"
///     keyword="BT01">
///       <attribute name="standard_name" type="NC_STRING">BT 01</attribute>
///       <attribute name="units" type="NC_STRING">K</attribute>
///       <attribute name="valid_min" type="NC_USHORT">0</attribute>
///       <attribute name="valid_max" type="NC_USHORT">65534</attribute>
///       <attribute name="_FillValue" type="NC_USHORT"
///       keyword="BT_fillValue">65535</attribute>
///       <attribute name="scale_factor" type="NC_FLOAT"
///       keyword="BT_scale">1</attribute>
///       <attribute name="add_offset" type="NC_FLOAT"
///       keyword="BT_offset">0</attribute>
///     </variable>
///   </group>
/// </productFileMap>
/// </netcdfFile>
///
/// It is possible to re-use the attributes from another variable using the
/// "clone_attributes_from" tag:
///
///  <variable name="BT" type="NC_USHORT" clone_attributes_from="BT01"
///  dimensions="rows columns" keyword="BT04">

class NetCDFMap {
public:
  explicit NetCDFMap(std::ostream &log_ = std::cerr) : log{log_} {}

  /// Destructor.
  ~NetCDFMap() { close_netcdf_files(); }

  /// Reads an XML product file map. It is possible to do this
  /// repeatedly before opening the files.
  int load_map(const string &filepath);

  /// Creates the NetCDF files described in the NCMAP(s). This
  /// function will return an error if any of the "configurable"
  /// dimensions is still undefined.
  int create_netcdf_files(const string &directory_path);

  /// Opens the NetCDF files described in the map file(s).
  int open_netcdf_files(const string &directory_path, bool readonly=false);

  /// Closes all the NetCDF files.
  int close_netcdf_files();

  /// Sync all the NetCDF files.
  int sync_netcdf_files();

  /// Disable all elements linked to a given keyword. The elements
  /// will not be created in the NetCDF files.
  int disable_elements(const string &keyword);
  int disable_elements(const std::vector<string> &keywords);

  /// This function forces the files to be blown up to their maximum
  /// size. This is to be used in the stub mode only. By default, the
  /// netcdf files will be small when they are created, and they will
  /// grow when you write data in them. This function will inflate the
  /// files to their maximum size even if there is no data stored in
  /// them.
  int inflate_netcdf_files();

  /// Obtain the netcdf ids to access a variable using the netcdf
  /// interface.
  int get_variable_netcdf_info(const string &keyword, int *ncid, int *varid);

  /// Set filename to netCDF file
  int set_netcdf_filename(const string &keyword, const string &name);

  /// Sets the value of an element (dim or att). Note that in this
  /// function we use streams to be able to convert from any type to
  /// int and string
  template <typename T> int set_element(const string &keyword, const T &value) {
    int status = 0;
    int updated = 0;
    // Update associated dimensions
    auto dims = ncmap.dimensions.equal_range(keyword);
    for (auto it = dims.first; it != dims.second; it++) {
      try {
        std::stringstream ss;
        ss << value;
        ss >> it->second->value;
        ++updated;
      } catch (...) {
        log << "[E] NCMAP: Error setting dimension '" << it->second->netcdf_name
            << "' associated to keyword '" << keyword << "' with value '"
            << value << "'.\n";
        status = -1;
      }
    }
    // Update associated attributes.
    auto atts = ncmap.attributes.equal_range(keyword);
    for (auto it = atts.first; it != atts.second; it++) {
      std::shared_ptr<Attribute> att = it->second;
      std::stringstream ss;
      ss << value;
      att->value = ss.str();
      // If the NetCDF has already been created, then update the
      // attribute in the file. Note that we use "create_attribute"
      // because creating an attribute involves the same steps as
      // updating it.
      if (att->ncid >= 0 && create_attribute(att.get()) != 0) {
        log << "[E] NCMAP: Error updating attribute '" << att->netcdf_name
            << "' associated to keyword '" << keyword << "'\n";
        status = -1;
      }
      ++updated;
    }
    if (updated == 0) {
      log << "[E] NCMAP: Error setting element '" << keyword
          << "': unknown keyword.\n";
      status = -1;
    }
    return status;
  }

  /// Gets the value of an element
  template <typename T> int get_element(const string &keyword, T *value) {
    // Look for element within the dimensions
    auto d = ncmap.dimensions.find(keyword);

    if (d != ncmap.dimensions.end()) {
      // These three lines of code convert from int to any basic type
      // using a string as intermediate step
      std::stringstream ss;
      ss << (d->second->value);
      ss >> (*value);
      return 0;
    }
    // Look for element within the attributes
    auto a = ncmap.attributes.find(keyword);
    if (a != ncmap.attributes.end()) {
      std::istringstream ss(a->second->value);
      ss >> (*value);
      return 0;
    }
    return -1;
  }

private:
  std::ostream &log;

  NCMAP ncmap;

  static const std::map<string, int> netcdf_types;

  /// Creates a NetCDF group. Uses the parent_ncid stored inside the
  /// group. Use "-1" for group.parent_ncid if this is a root group.
  int create_group(Group *group);

  /// Creates a NetCDF attribute. Uses the ncid and var id stored
  /// inside the attribute.
  int create_attribute(Attribute *attribute);

  /// Creates a NetCDF dimension. Uses the ncid stored inside the
  /// dimension.
  int create_dimension(Dimension *dimension);

  /// Creates a NetCDF variable. Uses the ncid stored inside the
  /// variable.
  int create_variable(Variable *variable);

  /// Opens a NetCDF file
  int open_file(Group *group);

  /// Opens a NetCDF group
  int open_group(Group *group);

  /// Opens a NetCDF attribute
  int open_attribute(Attribute *attribute);

  /// Opens a NetCDF dimension
  int open_dimension(Dimension *dimension);

  /// Opens a NetCDF variable
  int open_variable(Variable *variable);

  /// Converts a string label to the corresponding netcdf
  /// type. Returns -1 on error.
  int netcdf_type_string2int(const string &type_str);

  /// Returns TRUE if the netcdf type is INTEGER
  bool netcdf_type_is_integer(int nctype);

  /// Returns TRUE if the netcdf type is FLOAT/DOUBLE
  bool netcdf_type_is_float(int nctype);

  /// Inflate the variables of a group and resource on sub-groups.
  int inflate_group(const Group &group);
};
} // namespace ncmap
} // namespace dms

#endif

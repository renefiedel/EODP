// Copyright 2016 DEIMOS SPACE
#ifndef DMS_NCMAP_NCMAP_PARSER_H_
#define DMS_NCMAP_NCMAP_PARSER_H_

#include <libxml/parser.h>
#include <libxml/tree.h>

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "ncmap_structs.hh"

namespace dms {

namespace ncmap {
using std::string;

/// This class parses an xml file that describes a collection of
/// NetCDF files. All methods return <0 in case of error.
class NetCDFMapParser {
public:
  /// Constructor. Accepts a stream to output the log
  explicit NetCDFMapParser(std::ostream &log_ = std::cerr) : log{log_} {};

  /// Parses a NCMAP xml file.
  /// \param[in] filepath Path to the NCMAP file.
  /// \param[out] ncmap The parsed NCMAP structure.
  int parse_ncmap(const string &filepath, NCMAP *ncmap);

private:
  /// Adds a group and its elements to the NCMAP lookup tables.
  /// \param root Reference to the group to be parsed.
  /// \param root ncmap Contains the lookup tables.
  int build_lookup_tables_for_group(std::shared_ptr<Group> root, NCMAP *ncmap);

  /// Fills the attributes of all the variables or groups with the tag
  /// "clone_attributes_from". This operation must be performed after
  /// the lookup tables have been created with
  /// "build_lookup_tables_for_group".
  /// \param[in] collection: a lookup of groups or variables.
  template <typename T> int clone_attributes(T *collection, NCMAP *ncmap);

  /// Parses an xml node that describes a netcdf group.
  /// \param[in] mode Pointer to the XML root node that describes the NetCDF
  /// group/file.
  /// \param[in] scope Dimensions "in scope" inherited from the parent group.
  /// \param[out] group The parsed group.
  int parse_group_node(const xmlNode *node,
                       const std::vector<std::shared_ptr<Dimension>> &scope,
                       Group *group);

  /// Parses an xml node that describes a netcdf attribute.
  int parse_attribute_node(const xmlNode *node, Attribute *attribute);

  /// Parses an xml node that describes a netcdf variable.
  /// \param[in] scope This are the dimensions that are in the scope of the
  /// variable.
  int parse_variable_node(const xmlNode *node, Variable *variable,
                          const std::vector<std::shared_ptr<Dimension>> &scope);

  /// Parses an xml node that describes a netcdf dimension.
  int parse_dimension_node(const xmlNode *node, Dimension *dimension);

  /// Stream to output the log
  std::ostream &log;
};
} // namespace ncmap
} // namespace dms

#endif

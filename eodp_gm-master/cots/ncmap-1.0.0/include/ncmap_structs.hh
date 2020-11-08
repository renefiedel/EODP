// Copyright 2016 DEIMOS SPACE

#ifndef DMS_NCMAP_NCMAP_STRUCT_H_
#define DMS_NCMAP_NCMAP_STRUCT_H_

#include <map>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace dms {

namespace ncmap {

using std::string;

/// NetCDF attribute in the NCMAP.
struct Attribute {
  string netcdf_name;
  string netcdf_type;
  string keyword;
  string value;
  std::map<string, string> tags;
  int ncid;
  int varid;
  bool disabled;
  Attribute() : ncid(-1), varid(-1), disabled(false) {}
};

/// NetCDF dimension in the NCMAP.
struct Dimension {
  string netcdf_name;
  string keyword;
  int value;
  int ncid;
  int dimid;
  Dimension() : value{0}, ncid(-1), dimid{-1} {}
};

/// NetCDF variable in the NCMAP.
struct Variable {
  string netcdf_name;
  string netcdf_type;
  string keyword;
  std::vector<std::shared_ptr<Attribute>> attributes;
  std::vector<std::shared_ptr<Dimension>> dimensions;
  std::map<string, string> tags;
  int ncid;
  int varid;
  int type;
  bool disabled;
  string vlen_typeid;
  string vlen_basic_type;
  Variable() : ncid{-1}, varid{-1}, disabled(false) {}
};

/// NetCDF group in the NCMAP. All the elements are stored in the
/// heap so that the lookup table (see further down) remains valid
/// when the vectors are reallocated or the Group is copied around.
struct Group {
  string netcdf_name;
  string keyword;
  std::vector<std::shared_ptr<Dimension>> dimensions;
  std::vector<std::shared_ptr<Attribute>> attributes;
  std::vector<std::shared_ptr<Variable>> variables;
  std::vector<std::shared_ptr<Group>> groups;
  std::map<string, string> tags;
  int parent_ncid;
  int ncid;
  bool disabled;
  Group() : parent_ncid{-1}, ncid{-1}, disabled(false) {}
};

/// NCMAP structure that contains a tree-like structure of the
/// NetCDF files defined in the map, and a set of lookup tables to
/// be able to access the elements in the trees directly.
struct NCMAP {
  /// Files (top level groups).
  std::vector<std::shared_ptr<Group>> files;

  /// Lookup table of groups, indexed by "dataSource" tag.
  std::unordered_multimap<string, std::shared_ptr<Group>> groups;

  /// Lookup table of dimensions, indexed by "dataSource" tag.
  std::unordered_multimap<string, std::shared_ptr<Dimension>> dimensions;

  /// Lookup table of attributes, indexed by "dataSource" tag.
  std::unordered_multimap<string, std::shared_ptr<Attribute>> attributes;

  /// Lookup table of variables, indexed by "dataSource" tag.
  std::unordered_map<string, std::shared_ptr<Variable>> variables;
};
} // namespace ncmap
} // namespace dms

#endif

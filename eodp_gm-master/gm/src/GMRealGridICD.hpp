#ifndef GM_SRC_GMREALGRIDICD_HPP_
#define GM_SRC_GMREALGRIDICD_HPP_

#include "ncmap.hh"
#include <netcdf>
#include "GeometryModule.hpp"

#include <map>

using dms::ncmap::NetCDFMap;
using dms::config::Configuration;

// Define NC keywords
typedef enum
{
	PROJECTION_LAT,
	PROJECTION_LON,
	PROJECTION_ALT,
	REAL_GRID_N_KEYS
} realGrid_info;

// Define NC variables names
const map<realGrid_info, string> realGrid_map_key
{
	{realGrid_info::PROJECTION_LAT, "latitude"},
	{realGrid_info::PROJECTION_LON, "longitude"},
	{realGrid_info::PROJECTION_ALT, "altitude"},
};

typedef boost::multi_array<double,2> array_t;

class GMRealGridICD
{
public:

	// Constructor
	GMRealGridICD(const shared_ptr<NetCDFMap>& gridNcMap);

	// Destructor
	~GMRealGridICD();

	// Set LR CCD information
	void setGrid(const array_t& lat, const array_t& lon, const array_t& alt);

	// Write LR CCD information
	void writeGrid();

	// Set NC identifier
	void setNcID(int ncid[REAL_GRID_N_KEYS])
	{
		copy(ncid, ncid+REAL_GRID_N_KEYS, ncid_);
	}

	// Set variable identifier
	void setVarID(int varid[REAL_GRID_N_KEYS])
	{
		copy(varid, varid+REAL_GRID_N_KEYS, varid_);
	}

private:

	// ncmap "ncid" for netCDF writing
	int ncid_[REAL_GRID_N_KEYS];
	// ncmap "varid" for netCDF writing
	int varid_[REAL_GRID_N_KEYS];

	array_t lat;
	array_t lon;
	array_t alt;
};

#endif /* GM_SRC_GMREALGRIDICD_HPP_ */

#include "GMRealGridICD.hpp"
#include <boost/current_function.hpp>

GMRealGridICD::GMRealGridICD(const shared_ptr<NetCDFMap>& gridNcMap)
{
  int ncid[realGrid_info::REAL_GRID_N_KEYS];
  int varid[realGrid_info::REAL_GRID_N_KEYS];

  // Get ncid and varid info
  for (int i = 0; i < realGrid_info::REAL_GRID_N_KEYS; ++i)
  {
    if (gridNcMap->get_variable_netcdf_info(realGrid_map_key.at((realGrid_info) i),
        &ncid[i], &varid[i]) != 0)
    {
      std::cout << "[E] Error getting var info " << realGrid_map_key.at((realGrid_info) i)
          << endl;
    }
  }

  // Set ncif and vaid info on realGeo: writting purposes
  setNcID(ncid);
  setVarID(varid);
}

GMRealGridICD::~GMRealGridICD()
{
  // Destroy
}

void GMRealGridICD::setGrid(const array_t& lat, const array_t& lon, const array_t& alt)
{
	std::size_t nr = lat.shape()[0];
	std::size_t nc = lat.shape()[1];
	this->lat.resize(boost::extents[nr][nc]);
	this->lon.resize(boost::extents[nr][nc]);
	this->alt.resize(boost::extents[nr][nc]);
	this->lat = lat;
	this->lon = lon;
	this->alt = alt;
}

void GMRealGridICD::writeGrid()
{
  std::cout << "[D] Writing the CCD info" << endl;

  std::cout << "[D] Grid shape: [" << lat.shape()[0] << "]["
      << lat.shape()[1] << "]" << endl;

  size_t start_m[] = {0, 0};
  size_t count_m[] = {lat.shape()[0], lat.shape()[1]};

  // Write latitude
  int ncerr = nc_put_vara_double(ncid_[PROJECTION_LAT],
      varid_[PROJECTION_LAT], start_m, count_m, lat.data());
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing latitude. Error " << ncerr
        << endl;
    throw GMException("Error writing latitude", BOOST_CURRENT_FUNCTION);
  }

  const string units = "degrees";
  const char * units_c = units.c_str();
  ncerr = nc_put_att_text(ncid_[PROJECTION_LAT],
      varid_[PROJECTION_LAT], "units",
      strlen(units_c), units_c);
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing units. Error " << ncerr
        << endl;
    throw GMException("Error writing units", BOOST_CURRENT_FUNCTION);
  }

  // Write longitude
  ncerr = nc_put_vara_double(ncid_[PROJECTION_LON],
      varid_[PROJECTION_LON], start_m, count_m, lon.data());
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing longitude. Error " << ncerr
        << endl;
    throw GMException("Error writing longitude", BOOST_CURRENT_FUNCTION);
  }

  ncerr = nc_put_att_text(ncid_[PROJECTION_LON],
      varid_[PROJECTION_LON], "units",
      strlen(units_c), units_c);
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing units. Error " << ncerr
        << endl;
    throw GMException("Error writing units", BOOST_CURRENT_FUNCTION);
  }

  // Write altitude
  ncerr = nc_put_vara_double(ncid_[PROJECTION_ALT],
      varid_[PROJECTION_ALT], start_m, count_m, alt.data());
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing altitude. Error " << ncerr
        << endl;
    throw GMException("Error writing altitude", BOOST_CURRENT_FUNCTION);
  }

  const string units1 = "meters";
  const char * units_c1 = units1.c_str();
  ncerr = nc_put_att_text(ncid_[PROJECTION_ALT],
      varid_[PROJECTION_ALT], "units",
      strlen(units_c1), units_c1);
  if (ncerr != NC_NOERR)
  {
    std::cout << "[E] Error writing units. Error " << ncerr
        << endl;
    throw GMException("Error writing units", BOOST_CURRENT_FUNCTION);
  }
}


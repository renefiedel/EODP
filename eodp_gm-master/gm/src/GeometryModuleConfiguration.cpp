#include "GeometryModuleConfiguration.hpp"

GeometryModuleConfiguration::GeometryModuleConfiguration(
    shared_ptr<dms::config::Configuration> &configLocal,
    const std::string &app_directory = "")
{
  // Application absolute path
  app_directory_ = app_directory;

  loadOrbitSceneParameters(configLocal);

  loadAuxiliaryDataFiles(configLocal);

  loadOutputFilenames(configLocal);

  loadNcmapFilenames(configLocal);
}

GeometryModuleConfiguration::~GeometryModuleConfiguration()
{
}

void GeometryModuleConfiguration::loadAuxiliaryDataFiles(
    shared_ptr<dms::config::Configuration> &configLocal)
{

  if (configLocal->get("auxiliary_data_files", "dem_config_file",
      &dem_config) != 0)
  {
    throw(GMException("Error reading dem_config file name.",
    BOOST_CURRENT_FUNCTION));
  }
  if (!fileExists(dem_config))
  {
    throw(GMException("Error reading dem_config file name.",
    BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("auxiliary_data_files", "iers_bulletin",
      &iers_bulletin, app_directory_) != 0)
  {
    throw(GMException("Error reading iersbBulletin file name.",
    BOOST_CURRENT_FUNCTION));
  }
  if (!fileExists(iers_bulletin))
  {
    throw(GMException("Error reading iersbBulletin file name.",
    BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("auxiliary_data_files", "orbit_config",
      &orbit_config, app_directory_) != 0)
  {
    throw(GMException("Error reading orbit_config file name.",
    BOOST_CURRENT_FUNCTION));
  }
  if (!fileExists(orbit_config))
  {
    throw(GMException("Error reading orbit_config file name.",
    BOOST_CURRENT_FUNCTION));
  }
}

void GeometryModuleConfiguration::loadOutputFilenames(
    shared_ptr<dms::config::Configuration> &configLocal)
{
  if (configLocal->get("output_filenames", "real_orbit_file",
      &realOrbitFiles_) != 0)
  {
    throw(GMException(
        "Error reading real_orbit_file in the geometry local configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("output_filenames", "real_attitude_file",
      &realAttitudeFiles_) != 0)
  {
    throw(GMException(
        "Error reading real_attitude_file in the geometry local configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("output_filenames", "grid_file",
      &grid_file_) != 0)
  {
    throw(GMException(
        "Error reading grid_file in the geometry local configuration file.",
        BOOST_CURRENT_FUNCTION));
  }
}

void GeometryModuleConfiguration::loadNcmapFilenames(
    shared_ptr<dms::config::Configuration> &configLocal)
{
  if (configLocal->get("ncmap_filenames", "real_grid_ncmap_file",
      &realGridNcMapFile_, app_directory_) != 0)
  {
    throw(GMException("Error reading estimated geo ncMap file name.",
    BOOST_CURRENT_FUNCTION));
  }
}

const string& GeometryModuleConfiguration::getIersBulletin() const
{
  return iers_bulletin;
}

const string& GeometryModuleConfiguration::getGridFile() const
{
  return grid_file_;
}

const string& GeometryModuleConfiguration::getRealAttitudeFiles() const
{
  return realAttitudeFiles_;
}

const string& GeometryModuleConfiguration::getRealOrbitFiles() const
{
  return realOrbitFiles_;
}

const string& GeometryModuleConfiguration::getRealGridNcMapFile() const
{
return realGridNcMapFile_;
}

const string& GeometryModuleConfiguration::getDemConfig() const
{
  return dem_config;
}

const string& GeometryModuleConfiguration::getOrbitConfig() const
{
  return orbit_config;
}

double GeometryModuleConfiguration::getSampl() const {
	return t_sampl;
}

double GeometryModuleConfiguration::getFocalPlaneAlt() const {
	return focal_plane_alt;
}

int GeometryModuleConfiguration::getPix() const {
	return n_pix;
}

double GeometryModuleConfiguration::getPixSize() const {
	return pix_size;
}

void GeometryModuleConfiguration::loadOrbitSceneParameters(
    shared_ptr<dms::config::Configuration> &configLocal)
{
  std::vector<string>str;
  // Reading the Global parameters
  if (configLocal->get("Global", "simulation_epoch", &str) != 0)
  {
    throw(GMException("Error reading configuration file simulation_epoch",
    BOOST_CURRENT_FUNCTION));
  }
  simulation_epoch = str[0]+'_'+str[1];

  if (configLocal->get("Global", "orbit_propag_time", &orbit_propag_time)
      != 0)
  {
    throw(GMException(
        "Error reading orbit_propag_time in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("Global", "t_sampl", &t_sampl)
      != 0)
  {
    throw(GMException(
        "Error reading t_sampl in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("Global", "focal_length", &focal_length)
      != 0)
  {
    throw(GMException(
        "Error reading focal_length in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("Global", "n_pix", &n_pix)
      != 0)
  {
    throw(GMException(
        "Error reading n_pix in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("Global", "focal_plane_alt", &focal_plane_alt)
      != 0)
  {
    throw(GMException(
        "Error reading focal_plane_alt in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }

  if (configLocal->get("Global", "pix_size", &pix_size)
      != 0)
  {
    throw(GMException(
        "Error reading pix_size in the configuration file.",
        BOOST_CURRENT_FUNCTION));
  }



}


const std::string& GeometryModuleConfiguration::getSimulationEpoch() const
{
  // We receive a string in this format:
  // NEW: "2015-09-22 10:21:04.350000"
  // And the EOCFIs work with this format:
  // XL_ASCII_STD_MICROSEC “yyyy-mm-dd_hh:nn:ss.uuuuuu“
  return simulation_epoch;
}

double GeometryModuleConfiguration::getOrbitPropagTime() const
{
  return orbit_propag_time;
}

double GeometryModuleConfiguration::getFocalLength() const {
	return focal_length;
}

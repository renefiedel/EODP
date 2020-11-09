#ifndef GM_SRC_GEOMETRYMODULECONFIGURATION_HPP_
#define GM_SRC_GEOMETRYMODULECONFIGURATION_HPP_

#include "configuration.hh"
#include "GMException.hpp"

#include <boost/current_function.hpp>
#include <explorer_lib.h>
#include <explorer_pointing.h>
#include <memory>

class GeometryModuleConfiguration
{
  public:

    //! Constructor
    GeometryModuleConfiguration(
        shared_ptr<dms::config::Configuration> &configLocalMap,
        const std::string &app_directory);

    //! Destructor
    virtual ~GeometryModuleConfiguration();
    const string& getRealGeoNcMapFile() const;
    const string& getRealGridNcMapFile() const;
    const vector<double>& getTimeDeltas() const;
    const vector<string>& getTimeFiles() const;

    const string& getIersBulletin() const;
    const string& getDemConfig() const;
    const string& getOrbitConfig() const;

    const string& getGridFile() const;
    const string& getRealAttitudeFiles() const;
    const string& getRealOrbitFiles() const;

    const std::string& getSimulationEpoch() const;
    double getOrbitPropagTime() const;
	double getSampl() const;
	double getFocalLength() const;
	double getFocalPlaneAlt() const;
	int getPix() const;
	double getPixSize() const;

  private:

    //! Application directory
    std::string app_directory_;

    // *******************************
    // Orbit and Scene Parameters
    // *******************************

    // Simulation epoch
    std::string simulation_epoch;
    //! Orbit propagation time for the time-driven case
    double orbit_propag_time; // seconds
    double t_sampl; // seconds
    double focal_length; // seconds
    int n_pix; // number of pixels
    double focal_plane_alt; // [m] Position on the focal plane in the ALT
    double pix_size; // [m] Pixel size

    // *******************************
    // Auxiliary Data File
    // *******************************
    //! DEM configuration file according to the EO-CFIs
    string dem_config;

    //! OSF or OSV file according to the EO-CFIs
    string orbit_config;
    //! IERS-A bulletin
    string iers_bulletin;

    // *******************************
    // Input files to the GM
    // *******************************
    //! List of real orbit files.
    string realOrbitFiles_;
    //! List of real attitude files.
    string realAttitudeFiles_;
    //! Grid files
    string grid_file_;
    //! List of real grid ncMap files.
    string realGridNcMapFile_;

    // *******************************
    // Auxiliary functions
    // *******************************
    void loadOrbitSceneParameters(shared_ptr<dms::config::Configuration> &configLocal);

    // Load real orb&att errors
    void loadAuxiliaryDataFiles(
        shared_ptr<dms::config::Configuration> &configLocal);

    // Load output filenames
    void loadOutputFilenames(
        shared_ptr<dms::config::Configuration> &configLocal);

    // Load ncmap filenames
    void loadNcmapFilenames(
        shared_ptr<dms::config::Configuration> &configLocalMap);
};

#endif /* GM_SRC_GEOMETRYMODULECONFIGURATION_HPP_ */

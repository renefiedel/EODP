#ifndef GM_SRC_GEOMETRYMODULE_HPP_
#define GM_SRC_GEOMETRYMODULE_HPP_

#include "FIPSModule.hpp"
#include "GMException.hpp"
#include "GeometryModuleConfiguration.hpp"

#include <boost/current_function.hpp>

#include <explorer_lib.h>
#include <explorer_orbit.h>
#include <explorer_pointing.h>

//! class GeometryModule: This class implements the functions concerning
//! the FIPS Geometry Module
class GeometryModule: public FIPSModule
{
    typedef boost::multi_array<double, 4> mat4d;
    typedef boost::multi_array<double, 2> mat2d;
    typedef double sat_mat[3][3];
    typedef double v3[3];
    const string RealGridKeyword = "RealGrd";

  public:

    //! Constructor
    GeometryModule();

    //! Destructor
    ~GeometryModule();

    //! Function from the parent class
    void processModule();

  protected:

    //! Function to load the input files for the GM module
    //! @param inputDirs vector of strings with input files
    void loadInputParams(vector<string> &inputDirs);

  private:

    //! Structure with the geodetic coordinates of the grid in
    //! sensor geometry
    struct GridInfo
    {
        mat2d proj_lon;
        mat2d proj_lat;
        mat2d proj_alt;
    };

    //! Computes the real orbit and applies the orbit perturbations
    //! @param orbitId EOCFI OrbitId class
    //! @param mjd in MJD2000
    //! @param pos vector with the satellite position in ECEF in meters
    //! @param vel vector with the satellite velocity in ECEF in meters/second
    //! @param acc vector with the satellite acceleration in ECEF in meters/second^2
    //! @param orbit_data EOCFI orbit data structure used to write to file
    //! @param apply_orb_perturbations index of the orbit position
    void orbitComputation(xo_orbit_id &orbitId, double &mjd, double *pos,
        double *vel, double *acc, xd_orbit_file &orbit_data,
        const unsigned int orbpos);

    //! Computes the real attitude, including perturbations and thermoelastic errors
    //! @param detector detector identification (HR1, HR2 or LR)
    //! @param mjd in MJD2000
    //! @param pos vector with the satellite position in ECEF in meters
    //! @param vel vector with the satellite velocity in ECEF in meters/second
    //! @param acc vector with the satellite acceleration in ECEF in meters/second^2
    //! @param att_data EOCFI attitude data structure used to write to file
    //! @param ii orbit position
    //! @param misalig_iop_mat Matrix with the misalignments in the IOP frame for each detector
    //! @param att_mat instrument to ECEF rotation
    void attitudeComputation(double &mjd,
        double *pos, double *vel, double *acc, xd_att_file &att_data,
        std::size_t &ii);

    //! Compute Earth intersection
    //! @param losInfo tructure that contains information of the line-of-sight
    //! @param gridInfo structure wit information of the geoloation of each pixel
    //! @param detector detector identification (HR1, HR2 or LR)
    //! @param ii orbit position
    //! @param inst_data EOCFI structure with the position in the focal plane of each pixel and the director angles
    void intersectionWithTerrain(GridInfo &gridInfo,
        std::size_t &ii,
        xp_instrument_data &inst_data);

    //! Initialize geometry module
    void initGeometryModule();

    //! Initialize satellite id.
    void initSatId();

    //! Initialize model id.
    void initModelId();

    //! Close model id.
    //! @param modelId EOCFI ModelId class
    void closeModelId(xl_model_id &modelId);

    //! Initialize time id.
    void initTimeId();

    //! Close time id.
    //! @param modelId EOCFI TimelId class
    void closeTimeId(xl_time_id &timeId);

    //! Initialize orbit id.
    void initOrbitId();

    //! Close orbit id.
    //! @param modelId EOCFI ModelId class
    void closeOrbitId(xo_orbit_id &orbitId);

    //! Initialize satellite nominal attitude id.
    void initSatNominalAttitudeId();

    //! Close satellite nominal attitude id.
    //! @param satNomTransId EOCFI SatNomTransId class
    void closeSatNominalAttitudeId(xp_sat_nom_trans_id &satNomTransId);

    //! Initialize satellite attitude id.
    void initSatAttitudeId();

    //! Close satellite attitude id.
    //! @param satTransId EOCFI SatTransId class
    void closeSatAttitudeId(xp_sat_trans_id &satTransId);

    //! Initialize instrument ids. It can depend on time, due to rotor.
    //! @param detector detector identification (HR1, HR2 or LR)
    void initInstrAttitudeId();

    //! Close instrument ids. It can depend on time, due to rotor.
    //! @param instrTransId EOCFI InstrTransId class
    void closeInstrAttitudeId(xp_instr_trans_id &instrTransId);

    //! Initialize full attitude ids.
    //! @param detector detector identification (HR1, HR2 or LR)
    void initAttitudeId();

    //! Close full attitude ids.
    //! @param attId EOCFI AttitudeId class
    void closeAttitudeId(xp_attitude_id &attId);

    //! Initialize atmosphere id. Dummy in current implementation.
    void initAtmosId();

    //! Close atmosphere id. Dummy in current implementation.
    //! @param atmosId EOCFI AtmosphereId class
    void closeAtmosId(xp_atmos_id &atmosId);

    //! Initialize DEM id.
    void initDemId();

    //! Close DEM id.
    //! @param demId EOCFI DEMId class
    void closeDemId(xp_dem_id &demId);

    //! Initialize Target id.
    void initTargetId();

    //! Close Target id.
    //! @param targetId EOCFI TargetId class
    void closeTargetId(xp_target_id &targetId);

    //! Function to set pointers to EOCFI ids to NULL (used in constructors).
    void setPointersToNull();

    //! function to write the GRID product
    //! @param gridInfo structure wit information of the geoloation of each pixel
    //! @param detector detector identification (HR1, HR2 or LR)
    void writeRealGridFile(GridInfo &gridInfo);

    //! Function to write the orbit output file.
    //! @param orbit xd_orbit_file EOCFI structure
    //! @param detector detector identification (HR1, HR2 or LR)
    void writeOrbitFile(xd_orbit_file &orbit);

    //! Function to write the orbit output file.
    //! @param att xd_att_file EOCFI structure
    //! @param detector detector identification (HR1, HR2 or LR)
    void writeAttitudeFile(xd_att_file &att);

    //! Function to calculate the orbit times
    //! @param detector detector identification (HR1, HR2 or LR)
    //! @param dur_s duration of the acquisition for a time-driven mode in seconds
    //! @param t_end_mjd2000 end time of the acquisition in MJD2000 (UTC)
    //! @param propag_mjd orbit times in MJD2000 (UTC)
    //! @param n_acq number of orbit positions
    //! @param t_sampl sampling time in seconds
    void calculateOrbitTimes(const double dur_s,
        const double t_end_mjd2000, std::vector<double> &propag_mjd,
        std::size_t &n_acq, double &t_sampl);

    //! Get the vector of times given the initial MJD2000, sampling and duration
    //! @param t_ini_mjd2000 start time of the acquisition in MJD2000 (UTC)
    //! @param t_end_mjd2000 end time of the acquisition in MJD2000 (UTC)
    //! @param t_sampl_sec sampling time in seconds
    //! @param n_acq number of orbit positions
    //! @param propag_mjd orbit times in MJD2000 (UTC)
    void getVectorOfTimes(const double &t_ini_mjd2000,
        const double &t_end_mjd2000, const double &t_sampl_sec,
        std::size_t &n_acq, std::vector<double> &propag_mjd);

    //! Function to calculate the TAI and UTC values of an UTC calculation
    //! @param time_utc time in MJD2000 in UTC
    //! @param time_tai time in MJD2000 in TAI
    //! @param time_ut1 time in MJD2000 in UT1
    void caculateTimeTaiUt1FromUtc(double &time_utc, double &time_tai,
        double &time_ut1);

    //! Function to set the initial time of the acquisition in MJD2000
    void setInitialTimeOfAcquisition();

    //! * Free allocated memory referenced by pointer.
    //! If pointer content is not NULL, memory is freed.
    //! @param array Pointer to allocated memory.
    void freeArray(void **array);

    //! Calculates the viewing geometry according to the EOCFI and CCDB
    //! @param inst_data EOCFI structure for the instrument data.
    void configureFocalPlane(xp_instrument_data &inst_data);

    //! Function to calculate the azimuth and elevation from the LOS
    //! @param dir vector direction of the line-of-sight
    //! @param azimuth_deg azimuth angle in degrees according to the EOCFI convention
    //! @param elevation_deg elevation angle in degrees according to the EOCFI convention
    void getAzElDegFromPointingVector(double dir[3], double &azimuth_deg,
        double &elevation_deg);

    //! Function to retrieve and print the mean orbital parameters
    //! @param mjd time in MJD2000
    //! @param pos vector with the satellite position in ECEF in meters
    //! @param vel vector with the satellite velocity in ECEF in meters/second
    //! @param acc vector with the satellite acceleration in ECEF in meters/second^2
    //! @param kepl Keplerian Orbital parameters in True of Date Coordiate System
    //!             {sma [m], ecc [-], inc [deg], raan [deg], arg. perigee [deg], mean anomaly [deg]}
    void printMeanOrbitalElements(double *mjd, double *pos, double *vel,
        double *acc);

    //! Configuration of the geometry module.
    shared_ptr<GeometryModuleConfiguration> configLocal;

    //! Check that the times requested in the simulation are withing the
    //! Validity times of the Orbit initialisation
    //! @param propag_mjd times in MJD2000
    void checkValidityOfTimes(std::vector<double> &propag_mjd);

    //! Satellite id.
    long satId;
    //! Pointer to xl_model_id internal pointer.
    xl_model_id modelId;
    //! Pointer to xl_time_id internal pointer.
    xl_time_id timeId;
    //! Pointer to xl_orbit_id internal pointer.
    xo_orbit_id orbitId;
    //! Pointer to xp_sat_nom_trans_id internal pointer.
    xp_sat_nom_trans_id satNomTransId;
    //! Pointer to xp_sat_trans_id internal pointer.
    xp_sat_trans_id satTransId;
    //! List of pointers to xp_instr_trans_id internal pointers. We can have one per pixel.
    xp_instr_trans_id instrTransId;
    //! List of pointers to xp_attitude_id internal pointers. We can have one per pixel.
    xp_attitude_id attId;
    //! Pointer to xp_atmos_id internal pointer. Dummy in current implementation.
    xp_atmos_id atmosId;
    //! Pointer to xp_dem_id internal pointer.
    xp_dem_id demId;
    //! Pointer to xp_target_id
    xp_target_id targetId;
    //! Initial time in MJD2000
    double t0_mjd2000;
    //! Final time in MJD2000
    double t_end_mdj2000;
    //! Orbit initialisation initial and end times
    double val_time0, val_time1;

    // Define the configuration of the EOCFI
    long ASCII_ID = XL_ASCII_STD_MICROSEC; // “yyyy-mm-dd_hh:nn:ss.uuuuuu“
    long PROC_ID = XL_PROC;
    long TIME_REF = XL_TIME_UTC;

    // Auxiliary variables used in the GM
    long ierr[XL_NUM_ERR_ASCII_PROC];
    long status;
    char ascii_out[XL_MAX_STR];

};

#endif /* GM_SRC_GEOMETRYMODULE_HPP_ */

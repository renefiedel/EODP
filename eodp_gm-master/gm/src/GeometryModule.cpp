#include <stdio.h>
#include <string.h>
#include <iomanip>
#include "GeometryModule.hpp"
#include "GMRealGridICD.hpp"

// This function initializes the GeometryModule class
GeometryModule::GeometryModule() :
FIPSModule()
{
	setPointersToNull();
}

GeometryModule::~GeometryModule()
{
	// Destroy
	std::cout << "[D] GeometryModule destructor." << endl;

	// Free target id
	closeTargetId(targetId);

	// Free atmos id
	closeAtmosId(atmosId);

	// Free dem id
	closeDemId(demId);

	// Free attitude id
	closeAttitudeId(attId);

	// Free satellite nominal attitude id
	closeSatNominalAttitudeId(satNomTransId);

	// Free satellite attitude id
	closeSatAttitudeId(satTransId);

	// Free instrument attitude id
	closeInstrAttitudeId(instrTransId);

	// Free orbit id
	closeOrbitId(orbitId);

	// Free time id
	closeTimeId(timeId);

	// Free model id
	closeModelId(modelId);

	std::cout << "[D] End of the GeometryModule destructor." << endl;
}

void GeometryModule::initGeometryModule()
{
	// Initialize satId
	std::cout << "[D] Initialise the Satellite ID." << endl;
	initSatId();

	// Initialize modelId
	std::cout << "[D] Initialise the Model ID." << endl;
	initModelId();

	// Initialize timeId
	std::cout << "[D] Initialise the Time ID." << endl;
	initTimeId();

	// Initialize orbit id
	std::cout << "[D] Initialise the Orbit ID." << endl;
	initOrbitId();

	// Initialize Satellite nominal attitude
	std::cout << "[D] Initialise the Satellite Nominal Attitude ID." << endl;
	initSatNominalAttitudeId();

	// Initialize Satellite attitude
	std::cout << "[D] Initialise the Satellite Attitude ID." << endl;
	initSatAttitudeId();

	std::cout << "[D] Initialise the Instrument Attitude ID." << endl;
	initInstrAttitudeId();

	// Initialize atmos id
	std::cout << "[D] Initialise the Atmosphere ID." << endl;
	initAtmosId();

	// Initialize dem id
	std::cout << "[D] Initialise the DEM ID." << endl;
	initDemId();

	// Initialize target id
	std::cout << "[D] Initialise the Target ID." << endl;
	initTargetId();

	// Set T-0
	setInitialTimeOfAcquisition();

}


void GeometryModule::processModule()
{
	std::cout << "[I] Start processing of the Geometry Module" << endl;
	std::cout << "[D] GeometryModule::processModule" << endl;

	// Load the Local configuration into the GeometryModuleConfiguration pointer
	std::cout << "[I] Load the Geometry Module Configuration" << endl;
	configLocal = make_shared<GeometryModuleConfiguration>(configLocalMap, app_directory);

	// Initialise the Module
	std::cout << "[I] Initialise the EOCFI classes" << endl;
	initGeometryModule();

	// Calculate the duration of the acquisition
	double dur_s = configLocal->getOrbitPropagTime(); // [s] acquisition duration in sec
	double t_end_mjd2000 = t0_mjd2000 + dur_s / SECINDAY; // [days] Last time in MJD2000

	// Calculate the orbit times
	std::vector<double> propag_mjd;
	std::size_t n_acq_times = 0;
	double t_sampl = 0.0;
	calculateOrbitTimes(dur_s, t_end_mjd2000, propag_mjd,
			n_acq_times, t_sampl);

	// Set last instant of time of the acquisition
	t_end_mdj2000 = propag_mjd[n_acq_times-1];

	checkValidityOfTimes(propag_mjd);

	// Initialise the focal plane
	// ------------------------------------------------
	xp_instrument_data inst_data;
	configureFocalPlane(inst_data);

	// Initialisation or the orbit and attitude data
	// ------------------------------------------------
	xd_orbit_file orbit_data;
	orbit_data.num_rec = n_acq_times;
	orbit_data.osv_rec = (xd_osv_rec*) calloc(n_acq_times, sizeof(xd_osv_rec));

	xd_att_file att_data;
	att_data.num_rec = n_acq_times;
	att_data.sat_ref = XD_INSTR_ATT;
	att_data.source_ref = XL_EF; // Origin reference frame for the rotation or maybe XL_EF
	att_data.data_type = XD_ATT_QUATERNIONS;
	att_data.max_gap = t_sampl * 1.5; // [s] 1.5 times the acquisition sampling time. EOCFI will check that the
	// SV are spaced less than this value.
	att_data.att_rec = (xd_att_rec*) calloc(n_acq_times, sizeof(xd_att_rec));

	// Declare output info
	GridInfo gridInfo;

	// Initialize grid info structure
	std::size_t n_pix = inst_data.azimuth_elevation_input_union.azimuth_elevation_list.num_rec;
	gridInfo.proj_lon.resize(boost::extents[n_acq_times][n_pix]);
	gridInfo.proj_lat.resize(boost::extents[n_acq_times][n_pix]);
	gridInfo.proj_alt.resize(boost::extents[n_acq_times][n_pix]);

	// Loop for each instant of acquisition time:
	// ------------------------------------------------
	for (std::size_t ii = 0; ii < n_acq_times; ++ii)
	{
		double pos[3] = {0}, vel[3] = {0}, acc[3] = {0}, sun_vel[3] = {0};
		double time_ii = propag_mjd[ii]; // [mjd2000]

		// necessary to re-initialise the attitude each time
		initAttitudeId();

		// Real orbit computation
		orbitComputation(orbitId, time_ii, pos, vel, acc, orbit_data, ii);

		// Real attitude computation
		attitudeComputation(time_ii, pos, vel, acc, att_data, ii);

		// Geolocation
		intersectionWithTerrain(gridInfo, ii, inst_data);

		// Free attitude id
		closeAttitudeId(attId);
	}

	// Write real grid file
	writeRealGridFile(gridInfo);

	// Write orbit file
	writeOrbitFile(orbit_data);

	// Write attitude file
	writeAttitudeFile(att_data);

	// free instrument data
	freeArray(
			(void**) &(inst_data.azimuth_elevation_input_union.azimuth_elevation_list.az_el_list));


	std::cout << "[I] End processing of the Geometry Module" << endl;

}

void GeometryModule::checkValidityOfTimes(std::vector<double> &propag_mjd)
{
	// Check that the times requested in the simulation are withing the
	// Validity times of the Orbit initialisation
	if( (propag_mjd[0]<val_time0)||
			(propag_mjd[propag_mjd.size()-1]>val_time1) )
	{
		string msg = "Check the orbit initialisation. The current validity times are val_time0 " +
				std::to_string(val_time0) + " to val_time1 " + std::to_string(val_time1)
		+ ". The simulation start and end times are in MJD2000 "
		+ std::to_string(propag_mjd[0]) + " to "
		+ std::to_string(propag_mjd[propag_mjd.size()-1]);
		throw(GMException(msg,
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::initModelId()
{
	// Default model id
	long mode = XL_MODEL_DEFAULT;
	long models[XL_NUM_MODEL_TYPES_ENUM];

	status = xl_model_init(&mode, models, &modelId, ierr);
	if (status == XL_ERR)
	{
		throw(GMException("Error initialising EOCFI model id",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeModelId(xl_model_id &modelId)
{
	if (modelId.ee_id != NULL)
	{
		long xl_model_close_ierr[XL_NUM_ERR_MODEL_CLOSE];
		status = xl_model_close(&modelId, xl_model_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI model id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::loadInputParams(vector<string> &inputDirs)
{
	// The GM is the first module and doesn't have any inputs
}

void GeometryModule::initSatId()
{
	satId = XL_SAT_FLEX;
}

void GeometryModule::initTimeId()
{
	// Initialize with time files. We use full file
	vector<string> timeFiles = {configLocal->getIersBulletin()}; // Reading the IERS-B Bulletin
	long n_files = timeFiles.size();
	long time_model = XL_TIMEMOD_AUTO;
	long time_init_mode = XL_SEL_FILE;
	double time0 = 0.0, time1 = 0.0; // dummies
	long orbit0 = 0, orbit1 = 0; // dummies
	double val_time0 = 0.0, val_time1 = 0.0;
	char **time_files = NULL;
	StringManager::copyStringVectorToStringArray(timeFiles, &time_files);

	status = xl_time_ref_init_file(&time_model, &n_files, time_files,
			&time_init_mode, &TIME_REF, &time0, &time1, &orbit0, &orbit1, &val_time0,
			&val_time1, &timeId, ierr);

	if (status == XL_ERR)
	{
		throw(GMException("Error initialising EOCFI time id with files",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeTimeId(xl_time_id &timeId)
{
	if (timeId.ee_id != NULL)
	{
		long xl_time_close_ierr[XL_NUM_ERR_TIME_CLOSE];
		status = xl_time_close(&timeId, xl_time_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI time id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initOrbitId()
{
	// Initialize with orbit files. We use full file
	vector<string> orbitFiles = {configLocal->getOrbitConfig()};
	long orbit_mode = XO_ORBIT_INIT_AUTO;
	long n_files = orbitFiles.size();
	long time_init_mode = XL_SEL_FILE;
	double time0, time1; // dummies
	long orbit0, orbit1; // dummies
	char **orbit_files = NULL;
	StringManager::copyStringVectorToStringArray(orbitFiles, &orbit_files);

	std::cout << "[D] N files: " << n_files << endl;
	std::cout << "[D] Orbit file: " << orbitFiles.at(0) << endl;

	status = xo_orbit_init_file(&satId, &modelId, &timeId, &orbit_mode, &n_files,
			orbit_files, &time_init_mode, &TIME_REF, &time0, &time1, &orbit0, &orbit1,
			&val_time0, &val_time1, &orbitId, ierr);
	if (status == XO_ERR)
	{
		throw(GMException("Error initialising EOCFI orbit id",
				BOOST_CURRENT_FUNCTION));
	}

	std::cout << "[D] OrbitId validity times val_time0: " << val_time0
			<< " val_time1 " << val_time1 << endl;

	StringManager::freeStringArray(n_files, &orbit_files);

}

void GeometryModule::closeOrbitId(xo_orbit_id &orbitId)
{
	if (orbitId.ee_id != NULL)
	{
		long xo_orbit_close_ierr[XO_NUM_ERR_ORBIT_CLOSE];
		status = xo_orbit_close(&orbitId, xo_orbit_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI orbit id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initSatNominalAttitudeId()
{
	// Initialize with the attitude law.
	long mode = XP_AOCS_YSM;

	status = xp_sat_nominal_att_init(&mode, &satNomTransId, ierr);
	if (status == XP_ERR)
	{
		throw(GMException("Error initialising EOCFI satellite nominal attitude id",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeSatNominalAttitudeId(
		xp_sat_nom_trans_id &satNomTransId)
{
	if (satNomTransId.ee_id != NULL)
	{
		long xp_sat_nom_att_close_ierr[XP_NUM_ERR_SAT_NOM_ATT_CLOSE];
		status = xp_sat_nominal_att_close(&satNomTransId,
				xp_sat_nom_att_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI satellite nominal attitude id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initSatAttitudeId()
{
	double ang[3] = {0., 0., 0.};
	// Not default initialization
	ang[0] = 0.0;  // satAngles[1]; // Pitch -Y
	ang[1] = 0.0;  // satAngles[0]; // Roll - X
	ang[2] = 0.0;  // satAngles[2]; // Yaw - Z

	status = xp_sat_att_angle_init(ang, &satTransId, ierr);
	if (status == XP_ERR)
	{
		throw(GMException(
				"Error initialising EOCFI satellite attitude id with euler angles",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeSatAttitudeId(xp_sat_trans_id &satTransId)
{
	if (satTransId.ee_id != NULL)
	{
		long xp_sat_att_close_ierr[XP_NUM_ERR_SAT_ATT_CLOSE];
		status = xp_sat_att_close(&satTransId, xp_sat_att_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI satellite attitude id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initInstrAttitudeId()
{
	// EOCFI's particular orbital frame convention (MCD section 5.2.1):
	//  - The Zs axis points along the radial satellite direction vector, positive from the centre of the TOD reference
	//  frame towards the satellite
	//  - The Ys axis points along the transversal direction vector within the osculating
	//  orbital plane (i.e the plane defined by the position and velocity vectors of the satellite), orthogonal to the Zs
	//  axis and opposed to the direction of the orbital motion of the satellite.
	//  - The Xs axis points towards the out-of-plane direction vector completing the right hand reference frame.
	//  Z=r/|r|       (geocentric zenith)
	//  X=(r^v)/|r^v| (right-hand trihedral)
	//  Y=Z^X         (-1*dir_velocity (aprox))

	// [FLX-IF-TAS-SY-0058] Local Orbital Frame (LOF)
	//  O_ORB = OLOF is the satellite centre of mass.
	//  Z_ORB = ZLOF is oriented towards Earth’s centre of mass. It is included in the orbital plane.
	//  Y_ORB = YLOF is collinear to ZLOF ^ VSAT, where VSAT is the inertial velocity of the satellite.
	//      YLOF is perpendicular to the orbital plane and oriented in the opposite
	//      direction than the angular momentum.
	//  X_ORB = XLOF completes the right-handed orthogonal reference frame.

	double att_offset[3] = {0, 0, 0};
	double euler[3] = {0, 0, 0};

	status = xp_instr_att_angle_init(euler, att_offset, &instrTransId, ierr);

	if (status == XP_ERR)
	{
		throw(GMException("Error initialising EOCFI instrument attitude id",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeInstrAttitudeId(xp_instr_trans_id &instrTransId)
{
	if (instrTransId.ee_id != NULL)
	{
		long xp_instr_att_close_ierr[XP_NUM_ERR_INSTR_ATT_CLOSE];
		status = xp_instr_att_close(&instrTransId, xp_instr_att_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI instrument attitude id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initAttitudeId()
{
	status = xp_attitude_init(&attId, ierr);

	if (status == XP_ERR)
	{
		throw(GMException("Error initialising EOCFI attitude id",
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::closeAttitudeId(xp_attitude_id &attId)
{
	if (attId.ee_id != NULL)
	{
		long xp_att_close_ierr[XP_NUM_ERR_ATTITUDE_CLOSE];
		status = xp_attitude_close(&attId, xp_att_close_ierr);
		if (status == XL_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI attitude id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initAtmosId()
{
	atmosId.ee_id = NULL;
}

void GeometryModule::closeAtmosId(xp_atmos_id &atmosId)
{
	if (atmosId.ee_id != NULL)
	{
		long xp_atmos_close_ierr[XP_NUM_ERR_ATMOS_CLOSE];
		status = xp_atmos_close(&atmosId, xp_atmos_close_ierr);
		if (status == XP_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI atmosphere id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initDemId()
{
	string demConfiFile = configLocal->getDemConfig();

	if (!demConfiFile.empty())
	{
		long mode = 0; // Can be set as dummy, a warning will be raised if value does not coincide with DEM config file, but does not affect computations.
		long model = 0; // dummy parameter

		status = xp_dem_init(&mode, &model, (char*) demConfiFile.c_str(), &demId,
				ierr);
		if (status == XP_ERR)
		{
			throw(GMException("Error initialising DEM id with file " + demConfiFile,
					BOOST_CURRENT_FUNCTION));
		}
	}
}

void GeometryModule::closeDemId(xp_dem_id &demId)
{
	if (demId.ee_id != NULL)
	{
		long xp_dem_close_ierr[XP_NUM_ERR_DEM_CLOSE];
		status = xp_dem_close(&demId, xp_dem_close_ierr);
		if (status == XP_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI DEM id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::initTargetId()
{
	targetId.ee_id = NULL;
}

void GeometryModule::closeTargetId(xp_target_id &targetId)
{
	if (targetId.ee_id != NULL)
	{
		long xp_target_ierr[XP_NUM_ERR_TARGET_CLOSE];
		status = xp_target_close(&targetId, xp_target_ierr);
		if (status == XP_ERR)
		{
			std::cout
			<< "[E] Error freeing EOCFI target id in the GeometryModule destructor."
			<< endl;
		}
	}
}

void GeometryModule::orbitComputation(xo_orbit_id &orbitId, double &time,
		double *pos, double *vel, double *acc, xd_orbit_file &orbit_data,
		const unsigned int orbpos)
{
	// Get position and velocity of satellite with current configuration
	long mode = XO_INTERPOL_MODEL_DEFAULT; // There's only one interpolation method (SLERP)
	status = xo_osv_compute(&orbitId, &mode, &TIME_REF, &time, pos, vel, acc, ierr);
	if (status == XO_ERR)
	{
		throw(GMException("Error computing OSV record", BOOST_CURRENT_FUNCTION));
	}

	// Print the mean keplerian elements as a sanity check
	if (orbpos == 0)
	{ // First orbit position only
		printMeanOrbitalElements(&time, pos, vel, acc);
	}

	// Fill the output structure
	double time_tai = 0.0, time_ut1 = 0.0;
	caculateTimeTaiUt1FromUtc(time, time_tai, time_ut1);

	orbit_data.osv_rec[orbpos].tai_time = time_tai; // Set TAI time
	orbit_data.osv_rec[orbpos].ut1_time = time_ut1; // Set UT1 time
	orbit_data.osv_rec[orbpos].utc_time = time; // Set UTC time
	orbit_data.osv_rec[orbpos].time_ref_of = TIME_REF;
	orbit_data.osv_rec[orbpos].abs_orbit = 1;
	orbit_data.osv_rec[orbpos].quality = 0.0;
	orbit_data.osv_rec[orbpos].ref_frame = EARTH_FIXED;

	orbit_data.osv_rec[orbpos].pos[0] = pos[0];
	orbit_data.osv_rec[orbpos].pos[1] = pos[1];
	orbit_data.osv_rec[orbpos].pos[2] = pos[2];
	orbit_data.osv_rec[orbpos].vel[0] = vel[0];
	orbit_data.osv_rec[orbpos].vel[1] = vel[1];
	orbit_data.osv_rec[orbpos].vel[2] = vel[2];

}

void GeometryModule::printMeanOrbitalElements(double *mjd, double *pos,
		double *vel, double *acc)
{
	// Convert the state vector to True of Date Coordiate System
	double pos_tod[3] = {0, 0, 0}, vel_tod[3] = {0, 0, 0}, acc_tod[3] = {0, 0, 0};
	long cs_in = XL_EF; // ECEF
	long cs_out = XL_TOD; // True of Date
	long mode = XL_CALC_POS_VEL; // Calculation mode - Bowring direct method (faster)

	status = xl_change_cart_cs(&modelId, &timeId, &mode, &cs_in, &cs_out,
			&TIME_REF, mjd, pos, vel, acc, pos_tod, vel_tod, acc_tod);

	// Orbital parameters:
	//  {sma [m], ecc [-], inc [deg], raan [deg], arg. perigee [deg], mean anomaly [deg]}
	long kepl_mode = XL_KEPLER_MEAN;
	double kepl_tod[6] = {0, 0, 0, 0, 0, 0};
	status = xl_cart_to_kepl(&modelId, pos_tod, vel_tod, &kepl_mode, kepl_tod,
			ierr);

	std::cout << "[D] Calculation of the mean orbital parameters." << endl;
	std::cout << "[D] pos/vel ECEF: [ " << setprecision(15) << pos[0] << ", "
			<< pos[1] << ", " << pos[2] << ", " << vel[0] << ", " << vel[1] << ", "
			<< vel[2] << " ]" << endl;
	std::cout << "[D] pos/vel TOD: [ " << setprecision(15) << pos_tod[0] << ", "
			<< pos_tod[1] << ", " << pos_tod[2] << ", " << vel_tod[0] << ", "
			<< vel_tod[1] << ", " << vel_tod[2] << " ]" << endl;
	std::cout << "[I] Mean Keplerian Parameters TOD [m,-,deg^4]: [ "
			<< setprecision(15) << kepl_tod[0] << ", " << kepl_tod[1] << ", "
			<< kepl_tod[2] << ", " << kepl_tod[3] << ", " << kepl_tod[4] << ", "
			<< kepl_tod[5] << " ]" << endl;

}

void GeometryModule::attitudeComputation(
		double &mjd, double *pos, double *vel, double *acc, xd_att_file &att_data,
		std::size_t &ii)
{
	long target_frame = XP_INSTR_ATT;

	status = xp_attitude_compute(&modelId, &timeId, &satNomTransId, &satTransId,
			&instrTransId, &attId, &TIME_REF, &mjd, pos, vel, acc, &target_frame,
			ierr);
	if (status == XP_ERR)
	{
		throw(GMException("Error computing attitude for mjd: " + to_string(mjd),
				BOOST_CURRENT_FUNCTION));
	}

	// Get attitude data
	long source_ref_type = XP_FRAME_FLAG_EXT; // Source reference type: External or Satellite
	status = xp_get_attitude_data(&attId, &att_data.data_type, &source_ref_type,
			&att_data.source_ref, &att_data.att_rec[ii], ierr);
	if (status == XP_ERR)
	{
		throw(GMException("Error getting quaternion attitude data from id",
				BOOST_CURRENT_FUNCTION));
	}

}

void GeometryModule::intersectionWithTerrain(
		GridInfo &gridInfo, std::size_t &ii,
		xp_instrument_data &inst_data)
{
	// Geolocate a list of points
	// ------------------------------------------------------
	long deriv = XP_NO_DER;
	long inter_flag = XP_INTER_1ST;
	double altitude = 0;
	xp_target_output target_num = {0, NULL};

	// Call to EOCFI function
	status = xp_target_list_inter(&satId, &attId, &atmosId, &demId, &deriv,
			&inter_flag, &inst_data, &altitude, &target_num, &targetId, ierr);

	freeArray((void**) &(target_num.num_los_target));

	if (status == XP_ERR)
	{
		std::cout << "[E] Error in xp_target_list_inter." << endl;
	}

	// Get the data Target position in ECEF
	// ------------------------------------------------------
	long target_type = XP_DEM_TARGET_TYPE; // intersection with DEM
	long choice = deriv; //XP_NO_DER;

	// Get the data Target position in Geodetic coordinates
	// ------------------------------------------------------
	choice = XP_TARG_EXTRA_MAIN_ALL;
	xp_target_extra_main_results_list main_list;
	status = xp_target_list_extra_main(&targetId, &choice, &target_type,
			&main_list, ierr);
	if (status == XP_ERR)
	{
		throw(GMException(
				"Error computing target geolocation with parallel processing",
				BOOST_CURRENT_FUNCTION));
	}

	// NOTE ON THE EOCFIS. From the POINTING LIBRARY C doc:
	// main_results:
	//  [0] Target geocentric longitude (Earth Fixed CS)  [deg]
	//  [1] Target geocentric latitude (Earth Fixed CS)   [deg]
	//  [2] Target geodetic latitude (Earth Fixed CS)     [deg]
	//  [3] Target geodetic altitude (Earth Fixed CS)     [m]
	//  [4] Satellite to target azimuth (Topocentric CS)  [deg]
	//  [5] Satellite to target elevation (Topocentric CS)          [deg]
	//  [6] Satellite to target pointing: Azimuth (attitude frame)  [deg]
	//  [7] Satellite to target pointing: Elevation (attitude frame)[deg]
	//  [8] Target to satellite pointing: Azimuth (Topocentric)     [deg]
	//  [9] Target to satellite pointing: Elevation (Topocentric)   [deg]
	//  [10] Target to source Satellite Pointing: Azimuth (attitude frame). ote: this value is only meaningful when target has been computed with xp_target_sc   [deg]
	//  [11] Target to source Satellite Pointing: Elevation (attitude frame) Note: this value is only meaningful when target has been computed with xp_target_sc   [deg]
	//  [12:XP_SIZE_TARGET_RESULT_MAIN](dummy)

	// Store the information to the output structure
	for (int tar_i = 0; tar_i < main_list.num_rec; tar_i++)
	{
		gridInfo.proj_lat[ii][tar_i] =
				main_list.extra_main_results[tar_i].main_results[2]; // LAT
		double lon = main_list.extra_main_results[tar_i].main_results[0]; // LON
		checkBoundsLongitude(lon); // Lon [-180,180]
		gridInfo.proj_lon[ii][tar_i] = lon;
		gridInfo.proj_alt[ii][tar_i] =
				main_list.extra_main_results[tar_i].main_results[3]; // ALT [m]
	}

	// free memory
	freeArray((void**) &(main_list.extra_main_results));


	// Free target id
	// ------------------------------------------------------
	closeTargetId(targetId);
}

void GeometryModule::setPointersToNull()
{
	modelId.ee_id = NULL;
	timeId.ee_id = NULL;
	orbitId.ee_id = NULL;
	satNomTransId.ee_id = NULL;
	satTransId.ee_id = NULL;
	atmosId.ee_id = NULL;
	demId.ee_id = NULL;
	targetId.ee_id = NULL;
	instrTransId.ee_id = NULL;
	attId.ee_id = NULL;
}


void GeometryModule::writeRealGridFile(GridInfo &gridInfo)
{
	// Setup ncMap
	// -----------------------------------------
	shared_ptr<NetCDFMap> ncMap = make_shared<NetCDFMap>(std::cout);
	if (ncMap->load_map(configLocal->getRealGridNcMapFile()) != 0)
	{
		std::cout << "[E] Error reading ncmap file '"
				<< configLocal->getRealGridNcMapFile() << "'." << endl;
	}

	// Retrieve output name
	string product_name = configLocal->getGridFile()+
			+ NC_FILE_EXTENSION;

	if (ncMap->set_netcdf_filename(RealGridKeyword, product_name) != 0)
	{
		throw(GMException("Error setting filename " + product_name,
				BOOST_CURRENT_FUNCTION));
	}

	if (ncMap->set_element("n_lines", gridInfo.proj_lat.shape()[0]) != 0)
	{

		throw(GMException("Error writing n_lines dimension",
				BOOST_CURRENT_FUNCTION));
	}

	if (ncMap->set_element("n_columns", gridInfo.proj_lat.shape()[1]) != 0)
	{

		throw(GMException("Error writing n_columns dimension",
				BOOST_CURRENT_FUNCTION));
	}

	if (ncMap->create_netcdf_files(outputFolderName) != 0)
	{
		throw(GMException("Error creating product files",
				BOOST_CURRENT_FUNCTION));
	}

	// Fill real geometry NC file
	// -----------------------------------------
	shared_ptr<GMRealGridICD> realGridICD = make_shared<GMRealGridICD>(ncMap);
	realGridICD->setGrid(gridInfo.proj_lat, gridInfo.proj_lon, gridInfo.proj_alt);
	realGridICD->writeGrid();

	// Synchronize real geometry NC file
	if (ncMap->sync_netcdf_files() != 0)
	{
		throw(GMException("Error synchronizing product files",
				BOOST_CURRENT_FUNCTION));
	}

	// Close real geometry NC file
	if (ncMap->close_netcdf_files() != 0)
	{
		throw(GMException("Error closing product files",
				BOOST_CURRENT_FUNCTION));
	}

	std::cout << "[D] Finished writing to file the RealGridFile product" << endl;
}

void GeometryModule::writeOrbitFile(xd_orbit_file &orbit)
{
	if (outputFolderName.length() == 0)
	{
		throw GMException("Missing output directory",
				BOOST_CURRENT_FUNCTION);
	}

	char output_file[XD_MAX_STR];
	long func_id, n;

	xd_fhr fhr;
	strcpy(fhr.file_name,
			"real_orbit.xml");
	strcpy(fhr.file_description, "Predicted Orbit File");
	strcpy(fhr.mission, "EODP");
	strcpy(fhr.schema, "");
	strcpy(fhr.file_class, "Orbit");
	strcpy(fhr.file_type, "Orbit");
	strcpy(fhr.eoffs_version, "1.0");
	strcpy(fhr.val_start_date, "UTC=2000-01-01T00:00:00");
	strcpy(fhr.val_stop_date, "UTC=2999-01-01T00:00:00");
	fhr.version = 1;
	strcpy(fhr.system, "");
	strcpy(fhr.creator, "EXPLORER_GEN_FILES: xg_gen_pof");
	strcpy(fhr.creation_date, "UTC=2000-01-01T00:00:00");
	strcpy(fhr.creator_version, "1.0");

	string outputFile = outputFolderName + "/"
			+ configLocal->getRealOrbitFiles()
			+ XML_FILE_EXTENSION;
	strcpy(output_file, outputFile.c_str());

	status = xd_write_orbit_file(output_file, &fhr, &orbit, ierr);

	if (status != XD_OK)
	{
		char msg[XD_MAX_COD][XD_MAX_STR];
		func_id = XD_WRITE_ORBIT_FILE_ID;
		xd_get_msg(&func_id, ierr, &n, msg);
		xd_print_msg(&n, msg);

		throw(GMException( "Error writing orbit file",
				BOOST_CURRENT_FUNCTION));
	}

	xd_free_orbit_file(&orbit);

	std::cout << "[D] Finished writing to file the Real Orbit file " << endl;
}

void GeometryModule::writeAttitudeFile(xd_att_file &att)
{
	if (outputFolderName.length() == 0)
	{
		throw GMException("Missing output directory",
				BOOST_CURRENT_FUNCTION);
	}

	char output_file[XD_MAX_STR];
	long func_id, n;

	xd_fhr fhr;
	strcpy(fhr.file_name,
			"real_attitude.xml");
	strcpy(fhr.file_description, "Predicted Attitude File");
	strcpy(fhr.mission, "EODP");
	strcpy(fhr.schema, "");
	strcpy(fhr.file_class, "Attitude");
	strcpy(fhr.file_type, "");
	strcpy(fhr.eoffs_version, "1.0");
	strcpy(fhr.val_start_date, "UTC=2000-01-01T00:00:00");
	strcpy(fhr.val_stop_date, "UTC=2999-09-01-01T00:00:00");
	fhr.version = 1;
	strcpy(fhr.system, "");
	strcpy(fhr.creator, "EXPLORER_GEN_FILES: xg_gen_pof");
	strcpy(fhr.creation_date, "UTC=2000-01-01T00:00:00");
	strcpy(fhr.creator_version, "1.0");

	string outputFile = outputFolderName + "/"
			+ configLocal->getRealAttitudeFiles()
			+ XML_FILE_EXTENSION;
	strcpy(output_file, outputFile.c_str());

	status = xd_write_att(output_file, &fhr, &att, ierr);

	if (status != XD_OK)
	{
		char msg[XD_MAX_COD][XD_MAX_STR];
		func_id = XD_WRITE_ATT_ID;
		xd_get_msg(&func_id, ierr, &n, msg);
		xd_print_msg(&n, msg);

		throw(GMException("Error writing attitude file",
				BOOST_CURRENT_FUNCTION));
	}

	xd_free_att(&att);

	std::cout << "[D] Finished writing to file the Real Attitude file "<< endl;
}


void GeometryModule::calculateOrbitTimes(
		const double dur_s, const double t_end_mjd2000,
		std::vector<double> &propag_mjd, std::size_t &n_acq_times, double &t_sampl)
{

	// Initialisation for the calculation of the times and state vectors
	t_sampl = configLocal->getSampl(); // [s]
	std::cout << "[D] Sampling time in seconds " << t_sampl << endl;

	// Calculate the number of acquisition samples
	// Retrieve the vector of times and plot the results
	getVectorOfTimes(t0_mjd2000, t_end_mjd2000, t_sampl, n_acq_times, propag_mjd);

	std::cout << "[I] Number of times " << setprecision(15) << ": " << n_acq_times
			  << ". (Detector sampling time= " << t_sampl
			  << " and acquisition duration in sec=" << dur_s << endl;

	// Print the initial and end propagation times
	status = xl_time_processing_to_ascii(&timeId, &PROC_ID, &TIME_REF,
			&propag_mjd[n_acq_times - 1], &ASCII_ID, &TIME_REF, ascii_out, ierr);

	std::cout << "[D] Start of the acquisition " << setprecision(15)
    		  << configLocal->getSimulationEpoch() << ". In MJD2000 " << propag_mjd[0]
																					<< endl;
	std::cout << "[D] End of the acquisition " << ascii_out << ". In MJD2000 "
			<< setprecision(15) << propag_mjd[n_acq_times - 1] << endl;
}

void GeometryModule::caculateTimeTaiUt1FromUtc(double &time_utc,
		double &time_tai, double &time_ut1)
{
	// Convert to TAI
	long time_ref_out = XL_TIME_TAI;
	status = xl_time_processing_to_processing(&timeId, &PROC_ID, &TIME_REF,
			&time_utc, &PROC_ID, &time_ref_out, &time_tai, ierr);

	if (status == XP_ERR)
	{
		throw(GMException(
				"Error in mjd conversion from UTC to TAI of " + to_string(time_utc),
				BOOST_CURRENT_FUNCTION));
	}

	// Convert to UT1
	time_ref_out = XL_TIME_UT1;
	status = xl_time_processing_to_processing(&timeId, &PROC_ID, &TIME_REF,
			&time_utc, &PROC_ID, &time_ref_out, &time_ut1, ierr);

	if (status == XP_ERR)
	{
		throw(GMException(
				"Error in mjd conversion from UTC to UT1 of " + to_string(time_utc),
				BOOST_CURRENT_FUNCTION));
	}
}

void GeometryModule::getVectorOfTimes(const double &t_ini_mjd2000,
		const double &t_end_mjd2000, const double &t_sampl_sec,
		std::size_t &n_acq_times, std::vector<double> &propag_mjd)
{
	double dur_s_sec = (t_end_mjd2000 - t_ini_mjd2000); // [days]
	n_acq_times = static_cast<unsigned long>(floor(
			dur_s_sec / (t_sampl_sec / SECINDAY)));

	// Calculate the vector of time in MJD2000
	propag_mjd.resize(n_acq_times);
	for (std::size_t ii = 0; ii < n_acq_times; ++ii)
	{
		propag_mjd[ii] = t_ini_mjd2000 + ii * t_sampl_sec / SECINDAY; // [days]
	}
}

void GeometryModule::setInitialTimeOfAcquisition()
{
	//! Function to set the initial time of the acquisition in MJD2000
	// Calculation of the initial reference time in UTC MJD2000
	status = xl_time_ascii_to_processing(&timeId, &ASCII_ID, &TIME_REF,
			(char*) configLocal->getSimulationEpoch().c_str(), &PROC_ID, &TIME_REF,
			&t0_mjd2000, ierr);
	if (status == XP_ERR)
	{
		throw(GMException("Error in time conversion of the reference date",
				BOOST_CURRENT_FUNCTION));
	}

	std::cout << "[D] simulation_epoch " << setprecision(15)
    		  << configLocal->getSimulationEpoch() << " in MJD2000 (UTC) " << t0_mjd2000
			  << endl;
}

/**
 * @param dir Pointing direction vector.
 * @return Azimuth (first element, degrees) and elevation (second element, degrees) corresponding to input direction.
 */
void GeometryModule::getAzElDegFromPointingVector(double dir[3],
		double &azimuth_deg, double &elevation_deg)
{
	// The implement the target inter with lists

	// Results - Initialise with nadir pointing
	double azimuth = 0;

	// Unit vectors pointing to reference axis
	double az90[3]   = {-1,  0, 0}; // -X
	double az0[3]    = { 0, -1, 0}; // -Y (simmetrical anyway as there is one pix)
	double el90[3]   = { 0,  0, 1}; // +Z

	// Azimuth is the 90-angle with elevation90Vect0r
	double elevation = 90. - angleDeg(dir, el90);

	// If elevation is 90 deg or -90 deg, azimuth is ambiguous. We set 0 in that case
	if (fabs(elevation - 90.) < 1e-10 || fabs(elevation + 90.) < 1e-10){
		azimuth = 0.;
	}
	else
	{
		// Get projection of dir in azimuth plane and compute angles with respect to azimuth axis
		double dirElAxis[3], dirAz[3];
		for (std::size_t ii=0; ii<3; ++ii){
			dirElAxis[ii] = el90[ii] * dir[ii] * el90[ii];
			dirAz[ii] = dir[ii] - dirElAxis[ii];
		}


		double angleWithAz0 = angleDeg(dirAz,az0);
		double angleWithAz90 = angleDeg(dirAz,az90);

		// We have 4 sectors:
		// - Sector 1: az90 axis / minus az0
		// - Sector 2: minus az90 / minus az0
		// - Sector 3: minus az90 / az0
		// - Sector 4: az90 / minus az0
		// In Sectors 1 and 4, the value of the azimuth is the same as the angle of the projection with Az0
		// In Sectors 2 and 3, the value of the azimuth is 360. minus the angle of the projection with Az0
		int sector = -1;
		bool conditionAz0 = (angleWithAz0 + 90.) > 180.;
		bool conditionAz90 = (angleWithAz90 + 90.) > 180.;
		if (conditionAz90 && conditionAz0)
			sector = 2;
		else if (!conditionAz90 && conditionAz0)
			sector = 1;
		else if (conditionAz90 && !conditionAz0)
			sector = 3;
		else
			sector = 4;

		azimuth = angleWithAz0;
		if (sector == 2 || sector == 3)
			azimuth = 360. - azimuth;

		// Azimuth == 360 transform to zero
		if (fabs(azimuth - 360.) < 1e-10)
			azimuth = 0.;
	}

	azimuth_deg = azimuth;
	elevation_deg = elevation;

}

//! * Free allocated memory referenced by pointer.
//!If pointer content is not NULL, memory is freed.
//! @param array Pointer to allocated memory.
void GeometryModule::freeArray(void **array)
{
	if ((*array) != NULL)
	{
		free((*array));
		(*array) = NULL;
	}
}

void GeometryModule::configureFocalPlane(xp_instrument_data &inst_data)
{
	// Init
	// ---------------------------------------------------------------------------------
	// focal length
	double f = configLocal->getFocalLength(); // [m] f= 0.2345 m
	std::size_t n_pix = configLocal->getPix(); // 1000
	double pix_size = configLocal->getPixSize(); // [m]
	double alt = configLocal->getFocalPlaneAlt(); // [m]

	// Calculate LOS for binned pixels
	// ---------------------------------------------------------------------------------
	//  std::size_t n_pix = act.size();

	// Initialise the EOCFI data structure xp_instrument_data
	inst_data.type = XP_AZ_EL_LIST;
	inst_data.signal_frequency = 1.e10;

	xp_azimuth_elevation *az_el = (xp_azimuth_elevation*) calloc(n_pix,
			sizeof(xp_azimuth_elevation));
	if (az_el == NULL)
	{
		throw(GMException("Error getting azimuth/elevation EOCFI list",
				BOOST_CURRENT_FUNCTION));
	}

	// Calculate the X position on the focal plane
	ofstream myfile;
	string filename = outputFolderName + "/focal_plane" + TXT_FILE_EXTENSION;
	myfile.open(filename);
	myfile
	<< "Pixel index: ipix; Position in the focal plane: x[m]  y[m]  f[m]; Line of Sight: dir_x dir_y dirz; "
	"Azimuth [deg]; Elevation [deg];\n";

	for (unsigned short ipix = 0; ipix < n_pix; ++ipix)
	{
		// ACT in the focal plane
		// -------------------------------------------
		double act = pix_size*(-static_cast<double>(n_pix)/2.0 +0.5 + ipix);

		// 4. Calculate the Line of Sight in instrument frame
		// of [act, alt, f]
		// -------------------------------------------
	    // Operator modulus
	    double mod= sqrt(act*act+alt*alt+f*f);
	    double dir[3] = {act/mod,alt/mod,f/mod};


		getAzElDegFromPointingVector(dir, az_el[ipix].azimuth,
				az_el[ipix].elevation);

		az_el[ipix].azimuth_rate = 0.0;
		az_el[ipix].elevation_rate = 0.0;

		// write to file
		myfile << setprecision(15) << ipix << "  " << act << "  "
				<< alt << "  " << f << "  " << dir[0] << "  "
				<< dir[1] << "  " << dir[2] << "  " << az_el[ipix].azimuth
				<< "  " << az_el[ipix].elevation << "\n";
	}
	myfile.close();
	std::cout << "[D] Auxiliary file for debug written " << filename << endl;

	// Particular instrument data
	// Pointing directions in azimuth/elevation computed using the regular or irregular grid.
	inst_data.azimuth_elevation_input_union.azimuth_elevation_list.num_rec =
			n_pix;
	inst_data.azimuth_elevation_input_union.azimuth_elevation_list.az_el_list =
			az_el;

}




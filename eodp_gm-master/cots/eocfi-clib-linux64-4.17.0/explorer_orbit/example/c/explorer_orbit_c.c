 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Module      : explorer_orbit_c.c
 *
 * Functions   : main program (EXPLORER_ORBIT example) to call:
 *
 *                  o Time initialization functions *                    - xl_time_ref_init
 *                    - xl_time_ref_init_file
 *                  o Orbit initialization functions
 *                    - xo_orbit_cart_init
 *                    - xo_orbit_init_def
 *                    - xo_orbit_init_file
 *                    - xo_orbit_init_geo
 *                    - xo_orbit_close
 *                  o Propagation/Interpolation functions
 *                    - xo_osv_compute
 *                    - xo_osv_compute_extra
 *                  o other
 *                    - xo_orbit_to_time
 *                    - xo_time_to_orbit
 *                    - xo_orbit_info
 *                    - xo_orbit_rel_from_abs
 *                    - xo_orbit_abs_from_rel
 *                    - xo_orbit_abs_from_phase
 *                    - xo_orbit_changes_close
 *                  o Id. Accessors
 *                  o Gen file functions
 *                    - xo_gen_osf_create
 *                    - xo_gen_osf_append_orbit_change
 *                    - xo_gen_osf_change_repeat_cycle
 *                    - xo_gen_osf_add_drift_cycle
 *                    - xo_gen_pof
 *                    - xo_gen_rof
 *                    - xo_gen_dnf
 *                    - xo_gen_oef
 *                    - xo_gen_tle
 *                  o Check file functions
 *                    - xo_check_osf
 *                    - xo_check_oef
 *                  o Data Filter functions
 *                    - xo_orbit_data_filter
 *
 * Purpose     : Example program to show the way to call the previous functions.
 *
 * Reference   : Based on Envisat Mission CFI Software
 *
 * History:      +----------------------------------------------------------------------------------+
 *               | Version |   Date   |       Name        | Change                                  |
 *               |----------------------------------------------------------------------------------|
 *               |    1.1  | 23/05/02 | DEIMOS Space S.L. | First version from                      |
 *               |         |          |                   | Envisat CFI                             |
 *               |----------------------------------------------------------------------------------|
 *               |    1.2  | 19/07/02 | DEIMOS Space S.L. | New functions from                      |
 *               |         |          |                   | Envisat Visibility                      |
 *               +----------------------------------------------------------------------------------+
 *               |    2.0  | 29/11/02 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    2.1  | 13/05/03 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | MAC OS Version                          |
 *               |         |          |                   | Support for EE DORIS                    |
 *               |         |          |                   | Nav. files                              |
 *               |         |          |                   | Incorporate upgrades                    |
 *               |         |          |                   | from ENVISAT to                         |
 *               |         |          |                   | interpol                                |
 *               +----------------------------------------------------------------------------------+
 *               |    2.2  |30/09/03  | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New options for                         |
 *               |         |          |                   | xo_propag_init_file                     |
 *               |         |          |                   | xo_interpol_init_file                   |
 *               +----------------------------------------------------------------------------------+
 *               |   2.2.2 | 26/04/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   |* Abs orbit returned by                  |
 *               |         |          |                   |  xo_propag_extra                        |
 *               |         |          |                   |  xo_interpol_extra                      |
 *               |         |          |                   |* New flag to use                        |
 *               |         |          |                   |  simplified model in                    |
 *               |         |          |                   |  xo_propag_init_def                     |
 *               |         |          |                   |* Use of enumerations                    |
 *               |         |          |                   |  for array sizing                       |
 *               +----------------------------------------------------------------------------------+
 *               |    3.0  | 21/07/04 | DEIMOS Space S.L. | New initialisation                      |
 *               |         |          |                   | strategy                                |
 *               |         |          |                   | New interfaces                          |
 *               +----------------------------------------------------------------------------------+
 *               |    3.1  | 13/10/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    3.2  | 15/11/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    3.3  | 11/07/05 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   | + explorer_data_handling                |
 *               |         |          |                   |   support                               |
 *               |         |          |                   | + Id. Accessors                         |
 *               |         |          |                   | + ENVISAT support removed               |
 *               +----------------------------------------------------------------------------------+
 *               |    3.4  | 18/11/05 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   | + Routines for orbit file               |
 *               |         |          |                   |   generation                            |
 *               +----------------------------------------------------------------------------------+
 *               |    3.5  | 26/05/06 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Thread safe library                  |
 *               |         |          |                   |  + C99 compliant                        |
 *               |         |          |                   |  + Optimized libray                     |
 *               |         |          |                   |  + 64-Bits library for MACOS,           |
 *               |         |          |                   |    LINUX and SOLARIS                    |
 *               |         |          |                   |  + New satellites: SWARM & EARTHCARE    |
 *               |         |          |                   |  + New time<->orbit executables         |
 *               +----------------------------------------------------------------------------------+
 *               |    3.6  | 24/11/06 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + xo_gen_oef                           |
 *               |         |          |                   |  + xo_check_osf and xo_check_oef        |
 *               |         |          |                   |  + New DORIS TM format                  |
 *               |         |          |                   |  + New satellite: SENTINEL-1            |
 *               +----------------------------------------------------------------------------------+
 *               |    3.7  | 13/07/07 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + expcfi_check_libs                    |
 *               |         |          |                   |  + library version for Mac OS X         |
 *               |         |          |                   |    on Intel (32 and 64 bits)            |
 *               +----------------------------------------------------------------------------------+
 *               |  3.7.2  | 31/07/08 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Orbit operations/Propagation with    |
 *               |         |          |                   |    TLE.                                 |
 *               |         |          |                   |  + New satellites: Sentinel 2 & 3,      |
 *               |         |          |                   |    Seosat and Generic.                  |
 *               |         |          |                   |  + xo_gen_oef function                  |
 *               +----------------------------------------------------------------------------------+
 *               |    4.0  | 19/01/09 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Numerical propagator.                |
 *               |         |          |                   |  + xo_osv_compute replaces xo_propag and|
 *               |         |          |                   |    xo_interpol.                         |
 *               |         |          |                   |  + xo_osv_compute_extra replaces        |
 *               |         |          |                   |    xo_propag_extra and xo_interpol_extra|
 *               |         |          |                   |  + xo_gen_oef function                  |
 *               +----------------------------------------------------------------------------------+
 *               |    4.1  | 07/05/10 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Time correlation compatibility check |
 *               |         |          |                   |    between time_id and orbit file data  |
 *               +----------------------------------------------------------------------------------+
 *               |    4.2  | 31/01/11 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Support for curved MLST              |
 *               +----------------------------------------------------------------------------------+
 *               |    4.3  | 06/02/12 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New init. funciton xo_orbit_id_init  |
 *               +----------------------------------------------------------------------------------+
 *               |    4.4  | 05/07/12 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Support for GEO orbits. New functions|
 *               |         |          |                   |    - xo_orbit_init_geo                  |
 *               |         |          |                   |    - xo_orbit_(get/set)_geo_orbit_info  |
 *               |         |          |                   |  + xo_position_on_orbit_to_time         |
 *               +----------------------------------------------------------------------------------+
 *               |    4.5  | 01/03/13 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New function xo_orbit_data_filter    |
 *               |         |          |                   |  + Acceleration vector is computed for  |
 *               |         |          |                   |    TLE and numeric propagators.         |
 *               +----------------------------------------------------------------------------------+
 *               |    4.6  | 03/10/13 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + SDP4 TLE propagator        .         |
 *               |         |          |                   |  + Executable to generate TLE files     |
 *               |         |          |                   |  + Fitting method to comptue TLE in     |
 *               |         |          |                   |    xo_osv_to_tle function               |
 *               +----------------------------------------------------------------------------------+
 *               |    4.7  | 28/03/14 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Spacecraft Midnight computed by      |
 *               |         |          |                   |    xo_orbit_info function               |
 *               |         |          |                   |  + New function xo_orbit_id_change      |
 *               +----------------------------------------------------------------------------------+
 *               |    4.8  | 29/10/14 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    4.9  | 23/04/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Support for Orbit Ephemeris          |
 *               |         |          |                   |    Message files                        |
 *               +----------------------------------------------------------------------------------+
 *               |  4.9.1  | 05/06/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.10  | 29/10/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.11  | 15/04/16 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.12  | 03/11/16 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New function xo_osv_check            |
 *               +----------------------------------------------------------------------------------+
 *               |   4.13  | 05/04/17 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.14  | 16/11/17 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.15  | 20/04/18 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.16  | 09/11/18 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + TLE support for Sentinel-5P,         |
 *               |         |          |                   |    Sentinel-3B, Aeolus                  |
 *               |         |          |                   |  + New function: xo_orbit_id_check      |
 *               +----------------------------------------------------------------------------------+
 *               |   4.17  | 10/05/19 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *
 *****************************************************************************/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <explorer_orbit.h>

#define XO_MAX_STR_LENGTH        256

/* Main program */
/* ------------ */

int main (int argc, char *argv[])
{
  /* Earth Explorer Ids.: They should be initialized to NULL allways!!!! */
  xl_model_id    model_id    = {NULL};
  xl_time_id     time_id     = {NULL};
  xo_orbit_id    orbit_id    = {NULL};

  xl_time_id_init_data  time_id_init_data;
  xo_orbit_id_init_data orbit_id_init_data;
  xd_eocfi_file         eocfi_file_array[4];

  xd_osf_file osf_data;

  /* Accessors data */
  long num_rec; 
  xo_osf_records *osf;
  xo_validity_time val_time;

  xo_propag_id_data   propag_data;
  xo_interpol_id_data interpol_data;

  xo_geo_orbit_init_data geo_init_data;
  
  long i, j;

  /* error handling */
  long status,
       ierr[XO_ERR_VECTOR_MAX_LENGTH],
       n = 0,
       func_id,
       code[XO_MAX_COD]; /* Error codes vector */

  char msg[XO_MAX_COD][XO_MAX_STR]; /* Error messages vector */

  long xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];
  long xo_ierr[XO_ERR_VECTOR_MAX_LENGTH];

  /* common variables */
  long sat_id = XO_SAT_CRYOSAT;
  long sat_id_geo = XO_SAT_GENERIC_GEO;
  long propag_model = XO_PROPAG_MODEL_MEAN_KEPL;
  long time_ref_utc = XO_TIME_UTC, time_ref_ut1 = XO_TIME_UT1;

  double pos[3];
  double vel[3];
  double acc[3];

  double pos_ini[3];
  double vel_ini[3];

  double time0,
         time,  
         val_time0,
         val_time1;

  long irep,
       icyc,
       iorb0,
       iorb;

  double ascmlst,
         rlong;

  long time_init_mode,
       drift_mode;
  long time_model;

  double ascmlst_drift,
         inclination;

  char   *input_files[3];
  long orbit0, orbit1, n_files, num, i_loop;
  long ascii_id_in,
       proc_id_out;
  char utce0[30],
       utce1[30];

  char oef_name[256] = "";
  
  char precise_conf_file[256] = "";
  
#ifndef XL_WINDOWS

  char   file1[] = "../data/EARTH_EXPLORER_FPO_2000";
  char   file2[] = "../data/CRYOSAT_DORIS_NAV_2000";
  char   file3[] = "../data/EARTH_EXPLORER_FRO";
  char   file4[] = "../data/EARTH_EXPLORER_FPO_18_OSV_PART1";
  char   file5[] = "../data/EARTH_EXPLORER_FPO_18_OSV_PART2";
  char   file6[] = "../data/EARTH_EXPLORER_FPO_18_OSV_PART3";
  char   file7[] = "../data/CS_TEST_DOR_NAV_0__20#5163F.DBL";
  char   file8[] = "../data/ROF_FILE_OUTLIER";

#else

  char   file1[] = "..\\data\\EARTH_EXPLORER_FPO_2000";
  char   file2[] = "..\\data\\CRYOSAT_DORIS_NAV_2000";
  char   file3[] = "..\\data\\EARTH_EXPLORER_FRO";
  char   file4[] = "..\\data\\EARTH_EXPLORER_FPO_18_OSV_PART1";
  char   file5[] = "..\\data\\EARTH_EXPLORER_FPO_18_OSV_PART2";
  char   file6[] = "..\\data\\EARTH_EXPLORER_FPO_18_OSV_PART3";
  char   file7[] = "..\\data\\CS_TEST_DOR_NAV_0__20#5163F.DBL";
  char   file8[] = "..\\data\\ROF_FILE_OUTLIER";

#endif

  double time1;

  /* variables for xo_interpol_init */

  long interpol_model;

  /* variables for xo_osv_compute_extra */

  long extra_choice;
  double orbit_model_out[XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS], 
         orbit_extra_out[XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS];

  /* xo_time_to_orbit & xo_orbit_to_time variables */

  long orbit_t, second_t, microsec_t;
  double time_t;
  char orbit_scenario_file_t[XO_MAX_STR_LENGTH];
  long time_ref;

  /* variables for xo_orbit_info_from_... */
  
  long abs_orbit, rel_orbit, cycle, phase;
  double result_vector[XO_ORBIT_INFO_EXTRA_NUM_ELEMENTS];

  /* Other variables */
  
  double time_since_anx, time_anx, time_ini, dt;
  long k, wrong_sat_id;

  /* xl_time_ref_init_file */
  long   trif_time_model, trif_n_files, trif_time_init_mode, trif_time_ref ;
  char   *trif_time_file[1];
  double trif_time0, trif_time1, trif_val_time0, trif_val_time1;
  long   trif_orbit0, trif_orbit1;


  /* xl_time_ref_init variable declaration */
  /* ------------------------------------- */
  long tri_sat_id, tri_orbit_num;
  double tri_anx_time, tri_orbit_duration;
  double tri_time[XL_TIME_TRANS_DIM_MAX];
  long tri_ierr[XL_NUM_ERR_TIME_REF_INIT];

  /* orbit initilization */
  /* ------------------- */
  long time_mode, orbit_mode;
  char* files[1];

  /* xo_gen_osf_create variables */
  /*-----------------------------*/
  long repeat_cycle, cycle_length;
  double anx_long, mlst_drift, mlst,
    date, date2, date3;
  char output_dir[256] = "./";
  char output_file_1[64] = "";
  char date_string[]  = "2004-07-01_09:29:00.000000";
  char date_string2[] = "2004-07-04_00:00:00.000000";
  char date_string3[] = "2004-07-04_23:59:59.999999";
  
  long proc_out = XL_PROC;
  long ascii_in = XL_ASCII_STD_MICROSEC;
  long osf_version;

  /* xo_gen_osf_append_orbit_change variables */
  /*------------------------------------------*/
  long phase_inc;
  char input_file_2[64];
  char output_file_2[64] = "";
  double old_nodal_period;
  /* xo_gen_osf_change_repeat_cycle variables */
  /*------------------------------------------*/
  long search_direction = XO_SEARCH_FORWARD;
  char input_file_3[64];
  char output_file_3[64] = "";
  
  /* xo_gen_osf_add_drift_cycle variables */
  /*--------------------------------------*/
  long drift_start_orbit;
  long drift_stop_orbit;
  long drift_start_ph_inc;
  long drift_stop_ph_inc;
  double max_delta_alt;
  char input_file_4[64];
  char output_file_4[64] = "";
  

  /* xo_orbit_init_file variables */
  /* ---------------------------- */
  
  static char *file_class = "TEST";
  long         version_number = 11;
  static char *fh_system = "CFI Example";
  
  /* xo_gen_rof_prototype variables */
  /* ------------------------------ */

  long start_orbit, stop_orbit;
  double start_time, stop_time;
  double osv_interval;

  char output_directory[XD_MAX_STR], rof_filename[XD_MAX_STR];


  /* xo_gen_rof variables */
  /* -------------------- */
  
  long osv_precise;
  long ref_filetype;
  char reference_file[XD_MAX_STR];
  long rof_filetype;

  /* xo_gen_pof variables */
  /* -------------------- */
  double osv_location;

  char pof_filename[XD_MAX_STR];

  long pof_filetype;


  /* xo_gen_dnf variables */
  /* -------------------- */
  long dnf_filetype;
  long dtai;
  char control_file[256],
    doris_nav[256],
    rof_file[256];

  long fit_mode;
  char tle_filename[256];

  /* xo_check_osf and xo_check_oef variables */
  /* --------------------------------------- */
  double check_osf_thr[6];
  double check_oef_thr[6];
  char *osf_file;
  long transition_number;
  double max_diffs[XO_NUM_CHECK_PARAMS],
         rms[XO_NUM_CHECK_PARAMS],
         diffs[XO_NUM_CHECK_PARAMS];

  /* Variables for xl_model_init */
   long mode;
   long models[XL_NUM_MODEL_TYPES_ENUM];
   long xl_ierr[XL_ERR_VECTOR_MAX_LENGTH];
   
   /* Variables for xo_position_on_orbit_to_time */
   long abs_orbit_number,
        angle_type,
        deriv;
   double angle,
          angle_rate,
          angle_rate_rate;
  
  /* Variables for xo_orbit_data_filter */
  char          orbit_filename[XO_MAX_STR];
  long          reading_osv_flag,
                extend_osv_flag;
  double        range0,
                range1;
  xd_orbit_file orbit_file[4];
  xo_orbit_id_init_data    orbit_data_in;
  xo_orbit_filter_settings filter_settings;
  xo_orbit_id_init_data    orbit_data_out;
  xo_orbit_filter_report   report;
  
  
  /* xo_orbit_id_change */
  /* ------------------ */
  xl_model_id  model_id_pof = {NULL},
               model_id_osf = {NULL};
  xl_time_id   time_id_pof  = {NULL},
               time_id_osf  = {NULL};
  xo_orbit_id  orbit_id_pof = {NULL}, /* orbit_id POF */
               orbit_id_osf = {NULL}, /* orbit_id OSF */
               orbit_id1    = {NULL}, /* OSF+POF */
               orbit_id2    = {NULL}, /* Change        OSF mode */
               orbit_id3    = {NULL}, /* Change        TIME/ORBIT MODE */
               orbit_id4    = {NULL}, /* orbit_id_init OSF MODE */
               orbit_id5    = {NULL}; /* orbit_id_init TIME/ORBIT MODE */
  
  xd_osf_file   osf_file_527;
  xd_orbit_file orbit_file_527;
  
  xd_eocfi_file           eocfi_file_array_527;
  xo_orbit_id_init_data   orbit_id_init_data_527;
  xl_time_id_init_data    time_id_init_data_527;
  xo_orbit_id_change_data change_data;
  
  long local_status,
       orbit_file_mode,
       change_mode,
       change_orbit,
       osv_i,
       aux_orbit,
       new_orbit,
       second,
       microsec;
  
  double start_valtime,
         stop_valtime,
         change_time;

#ifndef XL_WINDOWS
  char osf_file1[] = "../data/CRYOSAT_XML_OSF_ANR_527";
  char pof_file1[] = "../data/EARTH_EXPLORER_FPO_ANR_527";
#else
  char osf_file1[] = "..\\data\\CRYOSAT_XML_OSF_ANR_527";
  char pof_file1[] = "..\\data\\EARTH_EXPLORER_FPO_ANR_527";
#endif
  
  /* xo_orbit_id_change end */
  /* ---------------------- */
  
  /* Set error handling mode to SILENT */
  /* ---------------------------------- */

   xl_silent();
   xo_silent();

  /* Dummy Test of Logging feature */
  /* ----------------------------- */

  fprintf(stdout,"This is the first user's log message\n");
  fflush(stdout);
  fprintf(stdout,"This is the second user's log message\n");
  fflush(stdout);
  fprintf(stdout, "\n\n\tTIME INITIALIZATION\n");

  /******************************************************************************/
  /* Initializing Time Reference: Used for the first and second example         */
  /******************************************************************************/

  printf("\n\n\nXL_MODEL_INIT\n");
  /* Model id initialization */
  /* Default model */
  mode = XL_MODEL_DEFAULT;
  
  status = xl_model_init( &mode, models, &model_id, ierr );
  
  /* Set input values */
  /* ---------------- */
  tri_sat_id    = XO_SAT_CRYOSAT;

  tri_time[0]   = -1100.100000000;   /* TAI time [days] */ 
  tri_time[1]   = -1100.100405092;   /* UTC time [days] (= TAI - 35.0 s)     */ 
  tri_time[2]   = -1100.100408564;   /* UT1 time [days] (= TAI - 35.3 s)     */ 
  tri_time[3]   = -1100.100219907;   /* GPS time [days] (= TAI - 19.0 s)     */
  tri_orbit_num = 10;
  tri_anx_time  = 5245.123456;
  tri_orbit_duration = 6035.928144;

  /* Call xl_time_ref_init function */
  /* ------------------------------ */
  xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                   &tri_orbit_duration, &time_id, tri_ierr);

  /******************************************************************************/
   /*====================================================*/
   /*  First example: xo_orbit_init_def use              */
   /*====================================================*/


   /* Calling xo_orbit_init_def */
   /* ------------------------- */

   irep = 369;           /* Repeat cycle of the reference orbit [days] */
   icyc = 5344;          /* Cycle length of the reference orbit [orbits] */
   ascmlst = 8.6667;     /* Mean local solar time at ANX [hours] */
   rlong = -36.2788;     /* Geocentric longitude of the ANX [deg] */
   iorb0 = 0;            /* Absolute orbit number of the reference orbit */
   iorb = 43;            /* Absolute orbit number of the requested orbit */
   ascmlst_drift = -179.208556;
   inclination = 0.0;

   time_init_mode = XO_SEL_ORBIT;
   drift_mode = XO_NOSUNSYNC_DRIFT;

   time0 = -2456.0;       /* UTC time in MJD2000 (1993-04-11  00:00:00) [days] */
   time =  0.0;           /* Dummy */

   /* Calling to xo_orbit_init_def */
   /* ---------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_INIT_DEF - XO_OSV_COMPUTE\n");

   status = xo_orbit_init_def(&sat_id, &model_id, &time_id, &time_ref_utc, &time0,
                              &iorb0, &drift_mode, &ascmlst_drift, &inclination, 
                              &irep, &icyc, &rlong, &ascmlst, 
                              &val_time0, &val_time1, &orbit_id, ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_DEF_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* Calling xo_osv_compute_extra */
   /* -------------------------- */
   extra_choice = XO_ORBIT_EXTRA_DEP_ANX_TIMING;

   fprintf(stdout, "\n\n\tXO_OSV_COMPUTE_EXTRA");

   status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                                 orbit_model_out, orbit_extra_out, ierr);
   if (status != XO_OK)
   {
     func_id = XO_OSV_COMPUTE_EXTRA_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* save time at ANX */
   time_anx = orbit_model_out[XO_ORBIT_EXTRA_DEP_UTC_CURRENT_ANX]; /* UTC */

   fprintf(stdout, "\n\t- time at ANX = %lf ", time_anx );

   /* Absolute orbit number and time since anx*/

   abs_orbit      = orbit_model_out[XO_ORBIT_EXTRA_DEP_ORBIT_NUMBER];
   time_since_anx = orbit_model_out[XO_ORBIT_EXTRA_DEP_SEC_SINCE_ANX];

   fprintf(stdout, "\n\t- absolute orbit = %ld Time since anx = %lf",  abs_orbit, time_since_anx);

   /* Calling xo_osv_compute */
   /* --------------------- */

   /* propagating every minute for 5 minutes since ascending node */

   for ( dt = 0; dt < 5.; dt += 1. )
   {

     fprintf(stdout, "\n\n\tXO_OSV_COMPUTE # %li", (long) dt);

     time = time_anx + dt/(24.*60.); /* UTC in processing format*/

     status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time,
                             /* outputs */
                             pos, vel, acc, ierr);
     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );
   }


   /* Calling to xo_osv_compute_extra */
   /* ----------------------------- */

   extra_choice = XO_ORBIT_EXTRA_ALL_RESULTS;

   fprintf(stdout, "\n\n\tXO_ORBIT_EXTRA");

   status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                                 orbit_model_out, orbit_extra_out, ierr);
   if (status != XO_OK)
   {
     func_id = XO_OSV_COMPUTE_EXTRA_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   for (n=0; n<XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_extra_out[%ld] = %lf", n, orbit_extra_out[n] );
   }

   fprintf(stdout, "\n");

   for (n=0; n<XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_model_out[%ld] = %lf", n, orbit_model_out[n] );
   }

   fprintf(stdout, "\n");


   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /*===================================================*/
   /*  Second example: xo_orbit_cart_init use           */
   /*===================================================*/

    time = -2452.569; /* UT1 time */

    pos_ini[0] = 6427293.5314;
    pos_ini[1] = -3019463.3246;
    pos_ini[2] = 0;

    vel_ini[0] = -681.1285;
    vel_ini[1] = -1449.8649;
    vel_ini[2] = 7419.5081;

   /* Calling to xo_orbit_cart_init */
   /* ----------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_CART_INIT... an error example... \n");

   wrong_sat_id = 16;

   status = xo_orbit_cart_init(&wrong_sat_id, &model_id, &time_id,
                               &time_ref_ut1, &time,
                               pos_ini, vel_ini, &abs_orbit,
                               &val_time0, &val_time1, &orbit_id, 
                               ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CART_INIT_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);

     /* example of handling of error codes */

     xo_get_code(&func_id, ierr, &n, code);
     for (k=0; k<n; k++)
     {
        if (code[k] == XO_CFI_ORBIT_CART_INIT_SAT_ERR)
        {
           fprintf(stdout,"\n\t... This is what happens when a wrong satellite flag is set as input");
        }
     }
   }


   fprintf(stdout, "\n\n\tXO_ORBIT_CART_INIT - XO_OSV_COMPUTE\n");

   status = xo_orbit_cart_init(&sat_id, &model_id, &time_id,
                               &time_ref_ut1, &time,
                               pos_ini, vel_ini, &abs_orbit,
                               &val_time0, &val_time1, &orbit_id, 
                               ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CART_INIT_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* propagating every minute for 3 minutes since time = -2452.569 (in UT1 time) */

   time_ini = -2452.569; /* UT1 time */

   for ( dt = 0; dt < 3.; dt += 1. )
   {

     fprintf(stdout, "\n\n\tXO_OSV_COMPUTE # %li", (long) dt);

     time = time_ini + dt/(24.*60.); /* UTC in processing format*/

     status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_ut1, &time,
                             /* outputs */
                             pos, vel, acc, ierr);

     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );

   }

   fprintf(stdout, "\n");

   /* Calling to xo_orbit_close */
   /* ------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_CLOSE");

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n");

   /* close time reference */
   /* -------------------- */
   status = xl_time_close(&time_id, ierr);
   
   /*==================================================*/
   /*  Third example: xo_orbit_init_file use           */
   /*==================================================*/

   /* Time Initialization */
   /* ------------------- */

   /* Important note: In order to have consistent set of data, the time correlations should be 
      the same in all files. For that reason, in the following examples the time reference
      and the orbit will be initialized using the same file.*/
   
   trif_time_model     = XL_TIMEMOD_FOS_PREDICTED;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_TIME;
   trif_time_ref       = XL_TIME_TAI;
   trif_time0          = 0.8260;  /* < 01-01-2000 19:50:00 TAI */
   trif_time1          = 0.9167;  /* > 01-01-2000 22:00:00 TAI */
   trif_orbit0         = 0;
   trif_orbit1         = 100;
   
   trif_time_file[0] = file1;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

   /* Orbit initialization */
   /* -------------------- */

   time_init_mode = XO_SEL_TIME;

   time0 = 0.826388888889;  /*01-01-2000 19:50:00 TAI*/
   time1 = 0.916666666667;  /*01-01-2000 22:00:00 TAI*/


   input_files[0] = file1;
   input_files[1] = file2;
   n_files = 2;

   fprintf(stdout, "\n\n\tXO_ORBIT_INIT_FILE - XO_OSV_COMPUTE \n");

   orbit_mode = XO_ORBIT_INIT_AUTO;
   
   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }
   
   status = xo_orbit_get_osv_compute_validity(&orbit_id, &val_time);
   
   val_time0 = val_time.start;
   val_time1 = val_time.stop;

   fprintf(stdout, "\n\t- validity times = ( %lf , %lf )", val_time0, val_time1 );

   /* propagating within the validity range (in UTC time) */

   num = 10;
   for (i_loop = 1; i_loop < num; i_loop++)
   {
     time = val_time0 + ((val_time1-val_time0)*((double)i_loop/((double)num)));

     fprintf(stdout, "\n\n\tXO_OSV_COMPUTE # %li", (long) i_loop);

     status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time,
                             /* outputs */
                             pos, vel, acc, ierr);

     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );

     extra_choice = XO_ORBIT_EXTRA_NO_RESULTS;
     
     status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                                 orbit_model_out, orbit_extra_out, ierr);
     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_EXTRA_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     /* Absolute orbit number and time since anx*/
     
     abs_orbit = orbit_model_out[XO_ORBIT_EXTRA_DEP_ORBIT_NUMBER];
     time_since_anx = orbit_model_out[XO_ORBIT_EXTRA_DEP_SEC_SINCE_ANX];
     
     fprintf(stdout, "\n\t- absolute orbit = %ld Time since anx = %lf",  abs_orbit, time_since_anx);
   }

   fprintf(stdout, "\n");

   /* Calling to xo_orbit_close */
   /* ------------------------- */

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);

   fprintf(stdout, "\n");


   /*==========================================================================*/
   /*  Third example (second part): xo_orbit_init_file use with multiple files */
   /*==========================================================================*/

   /* Time Initialization */
   /* ------------------- */

   trif_time_model     = XL_TIMEMOD_FOS_PREDICTED;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_TIME;
   trif_time_ref       = XL_TIME_TAI;
   trif_time0          = -500;
   trif_time1          = 1000;
   trif_orbit0         = 0;
   trif_orbit1         = 100;

   trif_time_file[0] = file4;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

   /* Orbit initialization */
   /* -------------------- */

   time_init_mode = XO_SEL_FILE;
   propag_model = XO_PROPAG_MODEL_MEAN_KEPL + XO_PROPAG_MODEL_AUTO + XO_PROPAG_MODEL_DOUBLE;
   n_files = 3;

   input_files[0]= file4;
   input_files[1]= file5;
   input_files[2]= file6;


   fprintf(stdout, "\n\n\tXO_ORBIT_INIT_FILE - XO_OSV_COMPUTE (second part)\n");

   orbit_mode = XO_ORBIT_INIT_AUTO;
   
   status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, input_files,
                               &time_init_mode, &time_ref_utc,
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1, &orbit_id,
                               ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   status = xo_orbit_get_propag_config(&orbit_id, &propag_data); 

   val_time0 = propag_data.propag_osv.val_time.start;
   val_time1 = propag_data.propag_osv.val_time.stop;


   fprintf(stdout, "\n\t- validity times = ( %lf , %lf )", val_time0, val_time1 );

   /* propagating within the validity range (in UTC time) */

   num = 10;
   for (i_loop = 1; i_loop < num; i_loop++)
   {
     time = val_time0 + ((val_time1-val_time0)*((double)i_loop/((double)num)));

     fprintf(stdout, "\n\n\tXO_OSV_COMPUTE # %li", (long) i_loop);

     status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time,
                             /* outputs */
                             pos, vel, acc, ierr);

     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );

   }

   fprintf(stdout, "\n");

   /* Calling to xo_orbit_close */
   /* ------------------------- */

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);

   fprintf(stdout, "\n");


   /*=============================================== */
   /*  Third example (third part): xo_orbit_init_geo */
   /*=============================================== */
   tri_time[0]   = -1100.100000000;   /* TAI time [days] */ 
   tri_time[1]   = -1100.100405092;   /* UTC time [days] (= TAI - 35.0 s)     */ 
   tri_time[2]   = -1100.100408564;   /* UT1 time [days] (= TAI - 35.3 s)     */ 
   tri_time[3]   = -1100.100219907;   /* GPS time [days] (= TAI - 19.0 s)     */
   tri_orbit_num = 10;
   tri_anx_time  = 5245.123456;
   tri_orbit_duration = 6035.928144;
   
   status = xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                             &tri_orbit_duration, &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }
   
   fprintf(stdout, "\n\n\tXO_ORBIT_INIT_GEO - XO_OSV_COMPUTE\n");
   
   /* Orbit initialization */
   /* -------------------- */
   geo_init_data.init_type = XO_GC_LONGITUDE_ONLY;
   geo_init_data.geo_orbit_info.geod_coord.gc_longitude = 21.4;
   geo_init_data.geo_orbit_info.geod_coord.gd_latitude  = 0.; /* Dummy */
   geo_init_data.geo_orbit_info.geod_coord.gd_altitude  = 0.; /* Dummy */
   
   status =  xo_orbit_init_geo(&sat_id_geo, &model_id, &time_id,
                               &geo_init_data,
                               &val_time0, &val_time1, &orbit_id,
                               ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_GEO_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }
   
   time = 5000.;
   status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time,
                           /* outputs */
                           pos, vel, acc, ierr);
   
   if (status != XO_OK)
   {
     func_id = XO_OSV_COMPUTE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }
   
   fprintf(stdout, "\n\t-    time = %lf", time );
   fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
   fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
   fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
   fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
   fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
   fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
   fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
   fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
   fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );
   
   fprintf(stdout, "\n");

   /* Calling to xo_orbit_close */
   /* ------------------------- */

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);

   fprintf(stdout, "\n");
   
   /*===================================================================================*/
   /*  Fourth example: xo_orbit_init_file, xo_interpol and xo_interpol_extra use        */
   /*===================================================================================*/

   /* Time Initialization */
   /* ------------------- */

   trif_time_model     = XL_TIMEMOD_FOS_RESTITUTED;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_TIME;
   trif_time_ref       = XL_TIME_TAI;
   trif_time0          = -500;
   trif_time1          = 1000;
   trif_orbit0         = 0;
   trif_orbit1         = 100;

   trif_time_file[0] = file3;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }


   /* Orbit initialization */
   /* -------------------- */

   interpol_model = XO_INTERPOL_MODEL_DEFAULT;

   time_init_mode = XO_SEL_TIME;
   time0 = -284.995;
   time1 = -284.9895;

   input_files[0]=file3;
   n_files = 1;


   fprintf(stdout, "\n\n\tXO_INTERPOL_INIT\n");

   orbit_mode = XO_ORBIT_INIT_AUTO;

   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* Calling to xo_interpol_data */
   /* --------------------------- */

   status = xo_orbit_get_interpol_config(&orbit_id, &interpol_data); 

   val_time0 = interpol_data.val_time.start;
   val_time1 = interpol_data.val_time.stop;

   fprintf(stdout, "\n\t- validity times = ( %lf , %lf )", val_time0, val_time1 );

   /* interpolating within the validity range (in UTC time) */

   num = 10;
   for (i_loop = 1; i_loop < num; i_loop++)
   {
     time = val_time0 + ((val_time1-val_time0)*((double)i_loop/((double)num)));

     fprintf(stdout, "\n\n\tXO_INTERPOL # %li", (long) i_loop);

     status = xo_osv_compute(&orbit_id, &interpol_model, &time_ref_utc, &time,
                            /* outputs */
                            pos, vel, acc, ierr);

     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );

   }

   fprintf(stdout, "\n");

   extra_choice = XO_ORBIT_EXTRA_ALL_RESULTS;

   status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                               orbit_model_out, orbit_extra_out, ierr);
   if (status != XO_OK)
   {
     func_id = XO_OSV_COMPUTE_EXTRA_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   for (n=0; n < XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_extra_out[%ld] = %lf", n, orbit_extra_out[n] );
   }

   fprintf(stdout, "\n");

   for (n=0; n<XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_model_out[%ld] = %lf", n, orbit_model_out[n] );
   }

   fprintf(stdout, "\n");


   /* Calling to xo_orbit_close */
   /* ------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_CLOSE");

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }
   
   xl_time_close(&time_id, ierr);

   fprintf(stdout, "\n");

   /*==========================================================================================*/
   /*  Fourth example (second part): xo_orbit_init_file, xo_interpol with a real DORIS file */
   /*==========================================================================================*/

   /* Time Initialization */
   /* ------------------- */

   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_TAI;

   trif_time_file[0] = file7;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

   /* Orbit initialization */
   /* -------------------- */

   interpol_model = XO_INTERPOL_MODEL_DEFAULT;

   time_init_mode = XO_SEL_TIME;
   strcpy(utce0,"04-JUL-2004 11:23:30.000000");
   strcpy(utce1,"04-JUL-2004 16:00:30.000000");
   ascii_id_in = XL_ASCII_ENVI_MICROSEC;
   proc_id_out = XL_PROC;

   status = xl_time_ascii_to_processing(&time_id, 
                                        &ascii_id_in, &time_ref_utc, utce0,
                                        &proc_id_out, &time_ref_utc, &time0,
                                        ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_ASCII_TO_PROCESSING_ID;
     xl_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

   status = xl_time_ascii_to_processing(&time_id, 
                                        &ascii_id_in, &time_ref_utc, utce1,
                                        &proc_id_out, &time_ref_utc, &time1, 
                                        ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_ASCII_TO_PROCESSING_ID;
     xl_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }


   input_files[0]=file7;
   n_files = 1;

   fprintf(stdout, "\n\n\tXO_INTERPOL_INIT_FILE (second example)\n");

   orbit_mode = XO_ORBIT_INIT_AUTO;

   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* Calling to xo_interpol_data */
   /* --------------------------- */

   status = xo_orbit_get_interpol_config(&orbit_id, &interpol_data); 

   val_time0 = interpol_data.val_time.start;
   val_time1 = interpol_data.val_time.stop;

   fprintf(stdout, "\n\t- validity times = ( %lf , %lf )", val_time0, val_time1 );

   /* interpolating within the validity range (in UTC time) */

   num = 10;
   for (i_loop = 1; i_loop < num; i_loop++)
   {
     time = val_time0 + ((val_time1-val_time0)*((double)i_loop/((double)num)));

     fprintf(stdout, "\n\n\tXO_OSV_COMPUTE # %li", (long) i_loop);

     status = xo_osv_compute(&orbit_id, &interpol_model, &time_ref_utc, &time,
                          /* outputs */
                          pos, vel, acc, ierr);

     if (status != XO_OK)
     {
       func_id = XO_OSV_COMPUTE_ID;
       xo_get_msg(&func_id, ierr, &n, msg);
       xo_print_msg(&n, msg);
     }

     fprintf(stdout, "\n\t-    time = %lf", time );
     fprintf(stdout, "\n\t-  pos[0] = %lf", pos[0] );
     fprintf(stdout, "\n\t-  pos[1] = %lf", pos[1] );
     fprintf(stdout, "\n\t-  pos[2] = %lf", pos[2] );
     fprintf(stdout, "\n\t-  vel[0] = %lf", vel[0] );
     fprintf(stdout, "\n\t-  vel[1] = %lf", vel[1] );
     fprintf(stdout, "\n\t-  vel[2] = %lf", vel[2] );
     fprintf(stdout, "\n\t-  acc[0] = %lf", acc[0] );
     fprintf(stdout, "\n\t-  acc[1] = %lf", acc[1] );
     fprintf(stdout, "\n\t-  acc[2] = %lf", acc[2] );

   }

   fprintf(stdout, "\n");

   extra_choice = XO_ORBIT_EXTRA_ALL_RESULTS;

   status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                               orbit_model_out, orbit_extra_out, ierr);
   if (status != XO_OK)
   {
     func_id = XO_OSV_COMPUTE_EXTRA_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   for (n=0; n<XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_extra_out[%ld] = %lf", n, orbit_extra_out[n] );
   }

   fprintf(stdout, "\n");

   for (n=0; n<XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS; n++)
   {
      fprintf(stdout, "\n\t- orbit_model_out[%ld] = %lf", n, orbit_model_out[n] );
   }

   fprintf(stdout, "\n");


   /* Calling to xo_orbit_close */
   /* ------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_CLOSE");

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);


   fprintf(stdout, "\n");

   /*=======================================================*/
   /*  Fifth example: xo_time_to_orbit and xo_orbit_to_time */
   /*=======================================================*/

   /* Set input values */
   /* ---------------- */

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\data\\CRYOSAT_XML_OSF");
#endif

   sat_id = XO_SAT_CRYOSAT;
   time_ref = XO_TIME_UT1;

   /* Time initialization with an OSF */
   /* ------------------------------- */
   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_TAI;

   trif_time_file[0] = orbit_scenario_file_t;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }
   
   /* orbit initialization with an OSF */
   /* -------------------------------- */
   n_files    = 1;
   time_mode  = XO_SEL_FILE;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   files[0]   = orbit_scenario_file_t;

   status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, files,
                               &time_mode, &time_ref, 
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1,
                               &orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }


   /* Calling xo_orbit_to_time */
   /* ------------------------ */

   orbit_t= 1034;
   second_t= 3000;
   microsec_t= 50;

   fprintf(stdout, "\n\n\tXO_ORBIT_TO_TIME\n");

   status=xo_orbit_to_time(&orbit_id, &orbit_t, 
                           &second_t, &microsec_t, &time_ref,
                           /* output */
                           &time_t, ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_TO_TIME_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n\t-    orbit = %ld", orbit_t );
   fprintf(stdout, "\n\t-   second = %ld", second_t );
   fprintf(stdout, "\n\t- microsec = %ld", microsec_t );
   fprintf(stdout, "\n\t-     time = %lf\n", time_t );

   /* Calling xo_time_to_orbit */
   /* ------------------------ */
   
   fprintf(stdout, "\n\n\tXO_TIME_TO_ORBIT\n");

   status=xo_time_to_orbit(&orbit_id, &time_ref, &time_t,
                           /* output */
                           &orbit_t, &second_t, &microsec_t, ierr);

   /* The output must be the input of "xv_anxutc" in the above call. */
   if (status != XO_OK)
   {
     func_id = XO_TIME_TO_ORBIT_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n\t-     time = %lf", time_t );
   fprintf(stdout, "\n\t-    orbit = %ld", orbit_t );
   fprintf(stdout, "\n\t-   second = %ld", second_t );
   fprintf(stdout, "\n\t- microsec = %ld\n", microsec_t );

   /* Call to xo_orbit_rel_from_abs */
   /* ----------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_INFO_FROM_ABS\n");

   abs_orbit = 2800;

   status = xo_orbit_rel_from_abs (&orbit_id, &abs_orbit,
                                    &rel_orbit, &cycle, &phase, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_REL_FROM_ABS_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   status = xo_orbit_info (&orbit_id, &abs_orbit, result_vector, ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INFO_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n\t-                  Absolute orbit = %ld",abs_orbit);
   fprintf(stdout, "\n\t-                  Relative orbit = %ld",rel_orbit);
   fprintf(stdout, "\n\t-                    Cycle number = %ld",cycle);
   fprintf(stdout, "\n\t-                    Phase number = %ld",phase);
   fprintf(stdout, "\n\t-                    Repeat cycle = %lf",result_vector[0]);
   fprintf(stdout, "\n\t-                    Cycle length = %lf",result_vector[1]);
   fprintf(stdout, "\n\t-                      MLST drift = %lf",result_vector[2]);
   fprintf(stdout, "\n\t-                            MLST = %lf",result_vector[3]);
   fprintf(stdout, "\n\t-                         Phasing = %lf",result_vector[4]);
   fprintf(stdout, "\n\t-                 UTC time at ANX = %lf",result_vector[5]);
   fprintf(stdout, "\n\t-               X position at ANX = %lf",result_vector[6]);
   fprintf(stdout, "\n\t-               Y position at ANX = %lf",result_vector[7]);
   fprintf(stdout, "\n\t-               Z position at ANX = %lf",result_vector[8]);
   fprintf(stdout, "\n\t-               X velocity at ANX = %lf",result_vector[9]);
   fprintf(stdout, "\n\t-               Y velocity at ANX = %lf",result_vector[10]);
   fprintf(stdout, "\n\t-               Z velocity at ANX = %lf",result_vector[11]);
   fprintf(stdout, "\n\t-     Mean semi-major axis at ANX = %lf",result_vector[12]);
   fprintf(stdout, "\n\t-        Mean eccentricity at ANX = %lf",result_vector[13]);
   fprintf(stdout, "\n\t-         Mean inclination at ANX = %lf",result_vector[14]);
   fprintf(stdout, "\n\t-     Mean right ascension at ANX = %lf",result_vector[15]);
   fprintf(stdout, "\n\t- Mean argument of perigee at ANX = %lf",result_vector[16]);
   fprintf(stdout, "\n\t-      Mean (mean) anomaly at ANX = %lf",result_vector[17]);
   fprintf(stdout, "\n\t-     Osc. semi-major axis at ANX = %lf",result_vector[18]);
   fprintf(stdout, "\n\t-        Osc. eccentricity at ANX = %lf",result_vector[19]);
   fprintf(stdout, "\n\t-         Osc. inclination at ANX = %lf",result_vector[20]);
   fprintf(stdout, "\n\t-     Osc. right ascension at ANX = %lf",result_vector[21]);
   fprintf(stdout, "\n\t- Osc. argument of perigee at ANX = %lf",result_vector[22]);
   fprintf(stdout, "\n\t-        Osc. mean anomaly at ANX = %lf",result_vector[23]);
   fprintf(stdout, "\n\t-                    Nodal Period = %lf",result_vector[24]);

   /* Call to xo_orbit_abs_from_rel */
   /* ----------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_ABS_FROM_REL\n");

   status = xo_orbit_abs_from_rel (&orbit_id, &rel_orbit, &cycle,
                                   &abs_orbit,  &phase, ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_ABS_FROM_REL_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n\t-                  Absolute orbit = %ld",abs_orbit);
   fprintf(stdout, "\n\t-                  Relative orbit = %ld",rel_orbit);
   fprintf(stdout, "\n\t-                    Cycle number = %ld",cycle);
   fprintf(stdout, "\n\t-                    Phase number = %ld",phase);

   /* Call to xo_orbit_abs_from_phase */
   /* -------------------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_INFO_FROM_PHASE\n");

   status = xo_orbit_abs_from_phase (&orbit_id, &phase,
                                     &abs_orbit, &rel_orbit, &cycle, 
                                     ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_ABS_FROM_PHASE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   fprintf(stdout, "\n\t-                  Absolute orbit = %ld",abs_orbit);
   fprintf(stdout, "\n\t-                  Relative orbit = %ld",rel_orbit);
   fprintf(stdout, "\n\t-                    Cycle number = %ld",cycle);
   fprintf(stdout, "\n\t-                    Phase number = %ld",phase);


   /* Call to xo_orbit_init_status */
   /* ---------------------------- */
   fprintf(stdout, "\n\n\tXO_ORBIT ID ACCESSORS (with OSF)\n");

   status = xo_orbit_init_status(&orbit_id);
   if (status)
     fprintf(stdout, "\n\t- Orbit Id is initialized");
   else
     fprintf(stdout, "\n\t- Orbit Id is not initialized");

   /* Call to xo_orbit_get_sat_id */
   /* --------------------------- */
   sat_id = xo_orbit_get_sat_id(&orbit_id);
   fprintf(stdout, "\n\t- Satellite Id = %ld", sat_id);

   /* Call to xo_orbit_get_mode */
   /* ------------------------- */
   orbit_mode = xo_orbit_get_mode(&orbit_id);
   fprintf(stdout, "\n\t- Orbit Mode = %ld", orbit_mode);

   /* Call to xo_orbit_get_osf_rec */
   /* ---------------------------- */
   status = xo_orbit_get_osf_rec(&orbit_id, &num_rec, &osf);

   fprintf(stdout, "\n\t- List of %ld orbital changes:", num_rec);
   for (i = 0; i < num_rec; i++)
   {
     fprintf(stdout, "\n\t-    Orbital Change %ld", i+1);
     fprintf(stdout, "\n\t-      Absolute Orbit  = %ld", osf[i].mission_info.abs_orbit);
     fprintf(stdout, "\n\t-      Relative Orbit  = %ld", osf[i].mission_info.rel_orbit);
     fprintf(stdout, "\n\t-      Cycle Number    = %ld", osf[i].mission_info.cycle_num);
     fprintf(stdout, "\n\t-      Phase           = %ld", osf[i].mission_info.phase_num);
     fprintf(stdout, "\n\t-      Drift mode      = %ld", osf[i].ref_orbit_info.drift_mode);
     fprintf(stdout, "\n\t-      Inclination     = %lf", osf[i].ref_orbit_info.inclination);
     fprintf(stdout, "\n\t-      Repeat Cycle    = %ld", osf[i].ref_orbit_info.rep_cycle);
     fprintf(stdout, "\n\t-      Cycle Length    = %ld", osf[i].ref_orbit_info.cycle_len);
     fprintf(stdout, "\n\t-      ANX Longitude   = %lf", osf[i].ref_orbit_info.ANX_long);
     fprintf(stdout, "\n\t-      MLST            = %lf", osf[i].ref_orbit_info.mlst);
     fprintf(stdout, "\n\t-      MLST Drift      = %lf", osf[i].ref_orbit_info.mlst_drift);
     fprintf(stdout, "\n\t-      ANX TAI         = %lf", osf[i].anx_info.anx_tai);
     fprintf(stdout, "\n\t-      ANX UTC         = %lf", osf[i].anx_info.anx_utc);
     fprintf(stdout, "\n\t-      ANX UT1         = %lf", osf[i].anx_info.anx_ut1);
     fprintf(stdout, "\n\t-      ANX Position    = {");
     for (j = 0; j < 3; j++)
       fprintf(stdout, "%f, ", osf[i].anx_info.anx_pos[j]);
     fprintf(stdout, "}");
     fprintf(stdout, "\n\t-      ANX Velocity    = {");
     for (j = 0; j < 3; j++)
       fprintf(stdout, "%f, ", osf[i].anx_info.anx_vel[j]);
     fprintf(stdout, "}");
     fprintf(stdout, "\n\t-      Nodal Period    = %f", osf[i].anx_info.tnod);
     fprintf(stdout, "\n\t-      Keplerian Elem. = {");
     for (j = 0; j < 6; j++)
       fprintf(stdout, "%f, ", osf[i].anx_info.kepl[j]);
     fprintf(stdout, "}");
   }

   /* Call to xo_orbit_set_osf_rec */
   /* ---------------------------- */
   status = xo_orbit_set_osf_rec(&orbit_id,  &num_rec, osf);
   
   /* Call to xo_orbit_get_val_time */
   /* ---------------------------- */
   status = xo_orbit_get_val_time(&orbit_id, &val_time);
   fprintf(stdout, "\n\t- Validity Period = {%f, %f} (time ref = %ld)", 
           val_time.start, val_time.stop, val_time.time_ref);

   status = xo_orbit_set_val_time(&orbit_id, &val_time);
   
   free (osf);


   /* Get propagation configuration data */
   /* ---------------------------------- */
   fprintf(stdout, "\n\n\tXO_PROPAG ID ACCESSORS\n");


   status = xo_orbit_get_propag_config(&orbit_id, &propag_data);
   fprintf(stdout, "\n\t- Double propagation = %s", 
           (propag_data.double_propag_flag? "Yes" : "No"));

   fprintf(stdout, "\n\t- Propagation data:");
   fprintf(stdout, "\n\t-   Validity period: (%f, %f)  (time ref = %ld)", 
           propag_data.propag_osv.val_time.start, propag_data.propag_osv.val_time.stop, 
           propag_data.propag_osv.val_time.time_ref);
   fprintf(stdout, "\n\t-   Absolute Orbit = %ld", propag_data.propag_osv.abs_orbit);
   fprintf(stdout, "\n\t-   Time since ANX = %f s", propag_data.propag_osv.time_since_anx);
   fprintf(stdout, "\n\t-   Time           = %f (time ref = %ld)", propag_data.propag_osv.time, propag_data.propag_osv.time_ref);

   fprintf(stdout, "\n\t-   Position       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", propag_data.propag_osv.pos[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Velocity       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", propag_data.propag_osv.vel[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Acceleration   = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", propag_data.propag_osv.acc[j]);
   fprintf(stdout, "}");

    fprintf(stdout, "\n\t-   Osculating Kepler. Elem. = {");
    for (j = 0; j < 6; j++)
      fprintf(stdout, "%f, ", propag_data.propag_osv.x[j]);
    fprintf(stdout, "}");

   status = xo_orbit_close(&orbit_id, ierr);


   fprintf(stdout, "\n\n\tXO_INTERPOL ID ACCESSORS\n");

   status = xl_time_close(&time_id, ierr);
   
   /* Time initialization */
   /* ------------------- */
   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_TAI;

   trif_time_file[0] = file3;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }
   
   /* orbit initialization with a ROF file */
   /* ------------------------------------ */
   n_files = 1;
   input_files[0]=file3;

   time_init_mode = XO_SEL_TIME;
   time0 = -284.995;
   time1 = -284.9895;

   orbit_mode = XO_ORBIT_INIT_AUTO;

   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                ierr);

   status = xo_orbit_get_interpol_config(&orbit_id, &interpol_data);

   fprintf(stdout, "\n\t- Interpolation data:");;
   fprintf(stdout, "\n\t-   Absolute Orbit = %ld", interpol_data.abs_orbit);
   fprintf(stdout, "\n\t-   Time since ANX = %f s", interpol_data.time_since_anx);
   fprintf(stdout, "\n\t-   Time           = %f (time ref = %ld)", interpol_data.time, interpol_data.time_ref);

   fprintf(stdout, "\n\t-   Position       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", interpol_data.pos[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Velocity       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", interpol_data.vel[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Acceleration   = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", interpol_data.acc[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Osculating Kepler. Elem. = {");
   for (j = 0; j < 6; j++)
     fprintf(stdout, "%f, ", interpol_data.kep[j]);
   fprintf(stdout, "}");


   /* Calling xo_orbit_close */
   /* ---------------------- */

   fprintf(stdout, "\n\n\tXO_ORBIT_CLOSE\n");

   status=xo_orbit_close(&orbit_id, ierr);

   status = xl_time_close(&time_id, ierr);  


   /*============================================================== */
   /*  Sixth example: Time and Orbit initialization with structures */
   /*============================================================== */

   fprintf(stdout, "\n\n\tXL_TIME_ID_INIT - XO_ORBIT_ID_INIT \n");

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\data\\CRYOSAT_XML_OSF");
#endif

   /* orbit initialization with data read from OSF */
   /* -------------------------------------------- */
   status = xd_read_osf (orbit_scenario_file_t,
                         &osf_data, xd_ierr);
   if (status != XO_OK)
   {
     func_id = XD_READ_OSF_ID;
     xd_get_msg(&func_id, xd_ierr, &n, msg);
     xd_print_msg(&n, msg);
   }

   sat_id     = XO_SAT_CRYOSAT;
   n_files    = 1;
   time_mode  = XO_SEL_FILE;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   time_ref   = XL_TIME_UTC;

   time_model = XL_TIMEMOD_OSF;


   /* store read data */
   eocfi_file_array[0].file_type           = XD_OSF_FILE;
   eocfi_file_array[0].eocfi_file.osf_file = osf_data;

   time_id_init_data.data_type = XL_FILE_DATA;
   time_id_init_data.time_id_init_data.file_set.num_files = n_files;
   time_id_init_data.time_id_init_data.file_set.eocfi_file_array = eocfi_file_array;

   /* Call xl_time_id_init function */
   /* ----------------------------- */
   status = xl_time_id_init(&time_model, 
                            &time_id_init_data,
                            &time_mode, &time_ref,
                            &time0, &time1,
                            &orbit0, &orbit1,
                            &val_time0, &val_time1, 
                            &time_id, xl_ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_ID_INIT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

   orbit_id_init_data.data_type = XL_FILE_DATA;
   orbit_id_init_data.orbit_id_init_data.file_set.num_files = n_files;
   orbit_id_init_data.orbit_id_init_data.file_set.eocfi_file_array = eocfi_file_array;
   
   status = xo_orbit_id_init(&sat_id, &model_id, &time_id,
                             &orbit_mode, &orbit_id_init_data,
                             &time_mode, &time_ref,
                             &time0, &time1, &orbit0, &orbit1,
                             &val_time0, &val_time1,
                             &orbit_id,
                             ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_ID_INIT_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   /* free osf data */
   xd_free_osf (&osf_data);

   status = xo_orbit_close(&orbit_id, ierr);
   if (status != XO_OK)
   {
     func_id = XO_ORBIT_CLOSE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }



   /*=================================*/
   /*  Seventh example: GEN_OSF_CREATE  */
   /*=================================*/

   time_ref = XL_TIME_UTC;
   sat_id = XL_SAT_CRYOSAT;
   status = xl_time_ascii_to_processing(&time_id,
                                        &ascii_in, &time_ref,
                                        date_string,
                                        &proc_out, &time_ref,
                                        &date,
                                        ierr);
   abs_orbit = 1;
   cycle = 1;
   phase = 1;
   repeat_cycle = 369;
   cycle_length = 5344;
   drift_mode = XO_NOSUNSYNC_DRIFT;
   mlst_drift = -179.208556;
   mlst = 12.0;
   anx_long = 37.684960;
   osf_version = 1;

   printf("\n\n\nxo_gen_osf_create\n");
   status = xo_gen_osf_create(&sat_id, &model_id, &time_id,
                              &abs_orbit,
                              &cycle, &phase,
                              &repeat_cycle, &cycle_length,
                              &anx_long,
                              &drift_mode,
                              &inclination, &mlst_drift,
                              &mlst, &date,
                              output_dir, output_file_1,
                              file_class, &osf_version,
                              fh_system,
                              ierr);

   if (status != XO_OK)
   {
      func_id = XO_GEN_OSF_CREATE_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }

   /*===================================*/
   /*  Eighth example: GEN_OSF_APPEND  */
   /*===================================*/

   old_nodal_period = 86400.0*(1+mlst_drift/86400.0)*
                          (double)repeat_cycle/(double)cycle_length;

   strcpy(input_file_2, output_file_1);
   osf_version++;
   abs_orbit = 5345;
   phase_inc = XO_NO_PHASE_INCREMENT;
   repeat_cycle = 369;
   cycle_length = 5344;

   /* small change wrt to nominal to check tolerances */
   anx_long = 37.68497;
   mlst = mlst + 
          mlst_drift*(5345-1)*old_nodal_period/(3600.0*86400.0) +
          24.0;
   printf("\n\n\nxo_gen_osf_append_orbit_change\n");

   status = xo_gen_osf_append_orbit_change(&sat_id, 
                                           &model_id,
                                           &time_id, 
                                           input_file_2,
                                           &abs_orbit,
                                           &repeat_cycle, &cycle_length,
                                           &anx_long,
                                           &drift_mode,
                                           &inclination, &mlst_drift,
                                           &mlst,
                                           &phase_inc,
                                           output_dir, output_file_2,
                                           file_class, &osf_version,
                                           fh_system,
                                           ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_OSF_APPEND_ORBIT_CHANGE_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }


   /*===============================================*/
   /*  Nineth example: GEN_OSF_CHANGE_REPEAT_CYCLE  */
   /*===============================================*/

   strcpy(input_file_3, output_file_1);
   osf_version++;
   abs_orbit = 5000;
   phase_inc = XO_PHASE_INCREMENT;
   repeat_cycle =2;
   cycle_length = 29;
   anx_long = 37.68497;
   drift_mode = XO_NOSUNSYNC_INCLINATION;
   inclination = 92.0;

   printf("\n\n\nxo_gen_osf_change_repeat_cycle\n");

   status = xo_gen_osf_change_repeat_cycle(&sat_id,
                                           &model_id, 
                                           &time_id,
                                           input_file_3,
                                           &abs_orbit, &search_direction,
                                           &repeat_cycle, &cycle_length,
                                           &anx_long,
                                           &drift_mode,
                                           &inclination, &mlst_drift,
                                           &phase_inc,
                                           output_dir, output_file_3,
                                           file_class, &osf_version,
                                           fh_system,
                                           ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_OSF_CHANGE_REPEAT_CYCLE_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }


   /*===========================================*/
   /*   Tenth example: GEN_OSF_ADD_DRIFT_CYCLE  */
   /*===========================================*/

   strcpy(input_file_4, output_file_1);
   osf_version++;
   drift_start_orbit = 30;
   drift_stop_orbit = 100;
   drift_start_ph_inc = XO_NO_PHASE_INCREMENT;
   drift_stop_ph_inc = XO_PHASE_INCREMENT;
   anx_long = 98.87;
   max_delta_alt = 10000.0000;

   printf("\n\n\nxo_gen_osf_add_drift_cycle\n");

   status = xo_gen_osf_add_drift_cycle(&sat_id, 
                                       &model_id, 
                                       &time_id,
                                       input_file_4,
                                       &drift_start_orbit,
                                       &drift_stop_orbit,
                                       &anx_long,
                                       &max_delta_alt,
                                       &drift_start_ph_inc,
                                       &drift_stop_ph_inc,
                                       output_dir,
                                       output_file_4,
                                       file_class, &osf_version,
                                       fh_system,
                                       ierr);

   if (status != XO_OK)
   {
      func_id = XO_GEN_OSF_ADD_DRIFT_CYCLE_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }


   status = xl_time_ascii_to_processing(&time_id,
                                        &ascii_in, &time_ref,
                                        date_string2,
                                        &proc_out, &time_ref,
                                        &date2,
                                        ierr);
   if (status != XO_OK)
   {
      func_id = XL_TIME_ASCII_TO_PROCESSING_ID;
      xl_get_msg(&func_id, ierr, &n, msg);
      xl_print_msg(&n, msg);
   }

   status = xl_time_ascii_to_processing(&time_id,
                                        &ascii_in, &time_ref,
                                        date_string3,
                                        &proc_out, &time_ref,
                                        &date3,
                                        ierr);
   if (status != XO_OK)
   {
      func_id = XL_TIME_ASCII_TO_PROCESSING_ID;
      xl_get_msg(&func_id, ierr, &n, msg);
      xl_print_msg(&n, msg);
   }


   /*=============================*/
   /*  Eleventh example: GEN_ROF  */
   /*=============================*/

   time_mode = XO_SEL_TIME;
   time_ref = XO_TIME_UTC;

   start_time = date2;
   stop_time  = date3-0.8;

   osv_interval = 60;
   osv_precise  = XO_OSV_PRECISE_MINUTE;

   ref_filetype = XO_REF_FILETYPE_OSF;
   rof_filetype = XO_REF_FILETYPE_ROF;

   strcpy(reference_file,output_file_1);
   strcpy(rof_filename,"FRO_FILE_with_OSF");

   strcpy(output_directory,"./");

   printf("\n\n\nxo_gen_rof\n");

   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref,
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise, &ref_filetype,
                       reference_file, precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename, file_class, &version_number, fh_system,
                       ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_ROF_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }

   time_mode = XO_SEL_ORBIT;
   start_orbit = 1000;
   stop_orbit  = 1001;
   osv_precise  = XO_OSV_PRECISE_NO;

   ref_filetype = XO_REF_FILETYPE_POF;
   strcpy(reference_file,"../data/EARTH_EXPLORER_FPO");

   strcpy(rof_filename,"FRO_FILE_with_FPO");
   strcpy(output_directory,"./");


   printf("\n\n\nxo_gen_rof\n");

   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref, 
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise, &ref_filetype,
                       reference_file, precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename, file_class, &version_number, fh_system,
                       ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_ROF_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }

   time_mode = XO_SEL_TIME;
   time_ref = XO_TIME_UTC;

   start_time = -284.9951;
   stop_time  = -284.9895;

   osv_interval = 60;
   osv_precise  = XO_OSV_PRECISE_NO;

   ref_filetype = XO_REF_FILETYPE_ROF;
   strcpy(reference_file,"../data/EARTH_EXPLORER_FRO");

   strcpy(rof_filename,"FRO_FILE_with_FRO");
   strcpy(output_directory,"./");


   printf("\n\n\nxo_gen_rof\n");

   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref,
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise, &ref_filetype,
                       reference_file, precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename, file_class, &version_number, fh_system,
                       ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_ROF_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }

   /*============================*/
   /*  Twelfth example: GEN_POF  */
   /*============================*/

   time_mode = XO_SEL_TIME;
   time_ref = XO_TIME_UTC;

   start_time = date2;
   stop_time  = date3;

   osv_location = 0.0;

   ref_filetype = XO_REF_FILETYPE_OSF;

   strcpy(reference_file,output_file_1);
   strcpy(pof_filename,""); /* "FPO_FILE_with_OSF" */

   strcpy(output_directory,"./");

   printf("\n\n\nxo_gen_pof\n");

   status = xo_gen_pof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref,
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_location, &ref_filetype,
                       reference_file, precise_conf_file,
                       &pof_filetype, output_directory,
                       pof_filename, file_class, &version_number, fh_system, ierr);
   if (status != XO_OK)
   {
      func_id = XO_GEN_POF_ID;
      xo_get_msg(&func_id, ierr, &n, msg);
      xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);

   
   /*==============================*/
   /*  Thirteenth example: GEN_DNF */
   /*==============================*/

   printf("\n\n\nxo_gen_dnf\n");
   
   tri_time[0]   =  0.0000000000000;   /* TAI time [days] */
   tri_time[1]   =  tri_time[0]-35.0/86400;   /* UTC time [days] (= TAI - 35.0 s) */
   tri_time[2]   =  tri_time[0]-35.8/86400;   /* UT1 time [days] (= TAI - 35.3 s) */
   tri_time[3]   =  tri_time[0]-19/86400;     /* GPS time [days] (= TAI - 19.0 s) */

   tri_orbit_num = 10;
   tri_anx_time  = 5245.123456;
   tri_orbit_duration = 6035.928144;
    
   /* Call xl_time_ref_init function */
   /* ------------------------------ */
   status= xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                            &tri_orbit_duration, &time_id, tri_ierr);

   sat_id=XO_SAT_CRYOSAT;

   time_mode= XL_SEL_TIME;
   start_orbit=0;/*dummy*/
   stop_orbit=0;/*dummy*/  
   
   osv_interval = 20;
   osv_precise  = XO_OSV_PRECISE_NO;
   
   ref_filetype=XO_REF_FILETYPE_ROF;

   dnf_filetype=XO_REF_FILETYPE_DORIS_NAV;

   dtai = 0;

#ifndef WINDOWS
   /*input*/
   strcpy(output_directory,"./");
   strcpy(control_file,"../data/CONTROL_FILE.xml");
   strcpy(reference_file,"../data/EARTH_EXPLORER_FRO_TO_DORIS_2000");
   /*output*/
   strcpy(doris_nav,"DORIS_NAVIGATOR_FILE_CRYOSAT.N1");
   strcpy(rof_file,"./EARTH_EXPLORER_FRO_FROM_DORIS_CRYO");
#else
   /*input*/
   strcpy(output_directory,".\\");
   strcpy(control_file,"..\\data\\CONTROL_FILE.xml");
   strcpy(reference_file,"..\\data\\EARTH_EXPLORER_FRO_TO_DORIS_2000");
   /*output*/
   strcpy(doris_nav,"DORIS_NAVIGATOR_FILE_CRYOSAT.N1");
   strcpy(rof_file,".\\EARTH_EXPLORER_FRO_FROM_DORIS_CRYO");
#endif

   strcpy(utce0,"01-JAN-2000 23:54:58.000000");
   strcpy(utce1,"02-JAN-2000 00:19:58.000000");

   time_ref = XL_TIME_UTC;

   ascii_id_in=XL_ASCII_ENVI_MICROSEC;
   proc_id_out=XL_PROC;
   
   status = xl_time_ascii_to_processing(&time_id, &ascii_id_in,
                                        &time_ref, utce0, &proc_id_out,
                                        &time_ref, &start_time, ierr);
   
   status = xl_time_ascii_to_processing(&time_id, &ascii_id_in,
                                        &time_ref, utce1, &proc_id_out,
                                        &time_ref, &stop_time, ierr);
   
   /* CREATE DNF FILE FROM ROF FILE */
   status = xo_gen_dnf(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref, 
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise,
                       &ref_filetype, reference_file, control_file,
                       precise_conf_file,
                       &dnf_filetype, output_directory, doris_nav,
                       file_class, &version_number, fh_system, ierr);

   if (status != XO_OK)
   {
     func_id = XO_GEN_DNF_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }


    xl_time_close(&time_id, ierr);


   /*===============================*/
   /*  Fourteenth example: GEN_OEF  */
   /*===============================*/

   printf("\n\n\nxo_gen_oef\n");
   
   status = xo_gen_oef(oef_name, output_file_1, pof_filename,
                       file_class, &version_number, fh_system,
                       ierr);

   if (status != XO_OK)
   {
     func_id = XO_GEN_OEF_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   xl_time_close(&time_id, ierr);
   
   /*====================================*/
   /*  Fifteenth example: XO_CHECK_OSF  */
   /*====================================*/

   osf_file =output_file_2;
   sat_id = XL_SAT_CRYOSAT;

   /* Time initialization */
   /* ------------------- */
   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_TAI;

   trif_time_file[0] = osf_file;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }
   
   check_osf_thr[0] = 1.;
   check_osf_thr[1] = 1.e-3;
   check_osf_thr[2] = 1.;
   check_osf_thr[3] = 5000.;
   check_osf_thr[4] = 1.e-5;
   check_osf_thr[5] = 1.;

   transition_number = 0;

   status = xo_check_osf(&sat_id, &model_id, &time_id,
                         osf_file, &transition_number,
                         check_osf_thr, diffs, ierr);

   if (status != XO_OK)
   {
     func_id = XO_CHECK_OSF_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

   printf("\n\t- xo_check_osf outputs. Differences in transition number %ld:", transition_number);
   printf("\n\t-   UTC at ANX                 = %.10f", diffs[0]);
   printf("\n\t-   ANX Longitude              = %.10f", diffs[1]);
   printf("\n\t-   MLST at ANX                = %.10f", diffs[2]);
   printf("\n\t-   Osculating semi-major axis = %.10f", diffs[3]);
   printf("\n\t-   Osculating inclination     = %.10f", diffs[4]);
   printf("\n\t-   Nodal Period               = %.10f", diffs[5]);

   xl_time_close(&time_id, ierr);
   
   /*===================================*/
   /*  Sixteenth example: XO_CHECK_OEF  */
   /*===================================*/

   /* Time initialization */
   /* ------------------- */
   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_TAI;

   trif_time_file[0] = oef_name;

   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, ierr);
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xl_print_msg(&n, msg);
   }
   
   printf("\n\n\nxo_check_oef");
   
   sat_id = XL_SAT_CRYOSAT;

   check_oef_thr[0] = 1.;
   check_oef_thr[1] = 1.e-3;
   check_oef_thr[2] = 1.;
   check_oef_thr[3] = 5000.;
   check_oef_thr[4] = 1.e-5;
   check_oef_thr[5] = 1.;

   time_mode = XO_SEL_FILE;
   time_ref = XL_TIME_UTC;

   status = xo_check_oef(&sat_id, &model_id, &time_id,
                         &time_mode, &time_ref,
                         &start_time, &stop_time,
                         &start_orbit, &stop_orbit,
                         oef_name, check_oef_thr,
                         /*output*/
                         max_diffs, rms,
                         ierr);
   if (status != XO_OK)
   {
     func_id = XO_CHECK_OEF_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
   }
   printf("\n\t- xo_check_oef outputs. Differences and standard deviation");
   printf("\n\t-   UTC at ANX                 maximum diferences = %f  rms = %.6f", max_diffs[0], rms[0]);
   printf("\n\t-   ANX Longitude              maximum diferences = %f  rms = %.6f", max_diffs[1], rms[1]);
   printf("\n\t-   MLST at ANX                maximum diferences = %f  rms = %.6f", max_diffs[2], rms[2]);
   printf("\n\t-   Osculating semi-major axis maximum diferences = %f  rms = %.6f", max_diffs[3], rms[3]);
   printf("\n\t-   Osculating inclination     maximum diferences = %f  rms = %.6f", max_diffs[4], rms[4]);
   printf("\n\t-   Nodal Period               maximum diferences = %f  rms = %.6f", max_diffs[5], rms[5]);
   printf("\n");

   /*================================*/
   /*  Seventeenth example: GEN_TLE  */
   /*================================*/

   printf("\n\n\nxo_gen_tle\n");

#ifndef WINDOWS
   /*input*/
   strcpy(reference_file,"../data/EARTH_EXPLORER_FPO_18_OSV");
#else
   /*input*/
   strcpy(reference_file,"..\\data\\EARTH_EXPLORER_FPO_18_OSV");
#endif

  sat_id = XD_SAT_CRYOSAT;
  strcpy(tle_filename,"OUTPUT_TLE_FILE");
  fit_mode = XO_ONE_TLE_PER_OSV;

  status = xo_gen_tle(&sat_id, &fit_mode,
                      &time_mode, &time_ref, &start_time,
                      &stop_time, &start_orbit, &stop_orbit,
                      reference_file,
                      tle_filename,
                      ierr);

  if (status != XO_OK)
  {
    func_id = XO_GEN_TLE_ID;
    xo_get_msg(&func_id, ierr, &n, msg);
    xo_print_msg(&n, msg);
  }
  
  /*=================================================*/
  /*  Eighteenth example: POSITION_ON_ORBIT_TO_TIME  */
  /*=================================================*/
  
  printf("\n\n\nxo_position_on_orbit_to_time\n");
  
  
#ifndef XL_WINDOWS
  input_files[0] = "../data/EARTH_EXPLORER_FPO";
#else
  input_files[0] = "..\\data\\EARTH_EXPLORER_FPO";
#endif  
  
  sat_id         = XL_SAT_CRYOSAT;
  orbit_mode     = XO_ORBIT_INIT_AUTO;
  n_files        = 1;
  
  time_init_mode = XO_SEL_FILE; /* XO_SEL_TIME(time0 time1) XO_SEL_ORBIT(orbit0 orbit1) XO_SEL_FILE(all) */
  time_ref       = XL_TIME_UTC;
  time0          = 0;   /* dummy */
  time1          = 1;   /* dummy */
  orbit0         = 0;   /* dummy */
  orbit1         = 100; /* dummy */
  
  status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                              &orbit_mode, &n_files, input_files,
                              &time_init_mode, &time_ref,
                              &time0, &time1, &orbit0, &orbit1,
                              &val_time0, &val_time1, &orbit_id,
                              ierr);
  if (status != XO_OK)
  {
    func_id = XO_ORBIT_INIT_FILE_ID;
    xo_get_msg(&func_id, ierr, &n, msg);
    xo_print_msg(&n, msg);
  }
  
  abs_orbit_number = 1001;
  angle_type       = XL_ANGLE_TYPE_TRUE_LAT_TOD;
  angle            = 13.961817;
  angle_rate       = 0.059176;
  angle_rate_rate  = 0.000000;
  deriv            = XL_DER_2ND;
    
  /* xo_position_on_orbit_to_time */
  propag_model = XO_PROPAG_MODEL_MEAN_KEPL;
  
  status = xo_position_on_orbit_to_time(&orbit_id, &abs_orbit_number, &angle_type,
                                        &angle, &angle_rate, &angle_rate_rate,
                                        &deriv, &time_ref,
                                        /* output */
                                        &time, pos, vel, acc,
                                        ierr);
  if (status != XO_OK)
  {
    func_id = XO_POSITION_ON_ORBIT_TO_TIME_ID;
    xo_get_msg(&func_id, ierr, &n, msg);
    xo_print_msg(&n, msg);
  }
  
  fprintf(stdout, "\n\t-   Time           = %f", time);
  fprintf(stdout, "\n\t-   Position       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", pos[j]);
   fprintf(stdout, "}");
  
  fprintf(stdout, "\n\t-   Velocity       = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", vel[j]);
   fprintf(stdout, "}");

   fprintf(stdout, "\n\t-   Acceleration   = {");
   for (j = 0; j < 3; j++)
     fprintf(stdout, "%f, ", acc[j]);
   fprintf(stdout, "}");


  status = xo_orbit_close(&orbit_id, ierr);
  if (status != XL_OK)
  {
    func_id = XO_ORBIT_CLOSE_ID;
    xo_get_msg(&func_id, ierr, &n, msg);
    xo_print_msg(&n, msg);
  }
  
  /*=================================================*/
  /*  Nineteenth example: ORBIT_DATA_FILTER          */
  /*=================================================*/
  
  printf("\n\n\n xo_orbit_data_filter\n");
  
  input_files[0] = file8;
  n_files = 1;

  /* ------------------------- */
  /* ----- orbit_data_in ----- */
  
  extend_osv_flag  = XL_FALSE;
  reading_osv_flag = XL_TRUE;
  time_init_mode   = XL_SEL_FILE;
  time_ref         = XL_TIME_UTC;
  
  status = xd_read_orbit_file (input_files[0],   &extend_osv_flag, 
                               &time_init_mode,  &time_ref,
                               &range0, &range1, &reading_osv_flag, 
                               &(orbit_file[0]),
                               ierr);
  if (status != XD_OK)
  {
    func_id = XD_READ_ORBIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* store read data */
  eocfi_file_array[0].file_type             = XD_ORBIT_FILE;
  eocfi_file_array[0].eocfi_file.orbit_file = orbit_file[0];
  
  orbit_data_in.data_type = XL_FILE_DATA;
  orbit_data_in.orbit_id_init_data.file_set.num_files = n_files;
  orbit_data_in.orbit_id_init_data.file_set.eocfi_file_array = eocfi_file_array;
  
  
  /* ---------------------------- */
  /* ----- filter_settings ------ */
  /* xo_orbit_filter_outliers_cfg */
  
  filter_settings.type = XO_FILTER_OUTLIERS;
  filter_settings.filter_cfg.outliers_cfg.threshold_pos = 300.0;
  filter_settings.filter_cfg.outliers_cfg.threshold_vel = 10.0;
  filter_settings.filter_cfg.outliers_cfg.action        = XO_REMOVE;
  
  
  status = xo_orbit_data_filter(&orbit_data_in, &filter_settings, &orbit_data_out, &report, ierr);
  
  printf("##############################################\n");
  printf("                OUTPUT REPORT                 \n\n");
  
  printf("> NUM_FILES: %ld\n", orbit_data_out.orbit_id_init_data.file_set.num_files);
  
  for(j = 0; j < orbit_data_out.orbit_id_init_data.file_set.num_files; j++)
    printf("  > FILE[%d] Num_rec: %ld\n", j, orbit_data_out.orbit_id_init_data.file_set.eocfi_file_array[j].eocfi_file.orbit_file.num_rec );
  
  printf("> nof_OSV_in      : %ld\n"  , report.filter_report.outliers_report.nof_OSV_in);
  printf("> nof_OSV_filtered: %ld\n"  , report.filter_report.outliers_report.nof_OSV_filtered);
  printf("> min_time_gap    : %.6f\n", report.filter_report.outliers_report.min_time_gap);
  printf("> max_time_gap    : %.6f\n", report.filter_report.outliers_report.max_time_gap);
  printf("> min_RMS_pos     : %.6f\n", report.filter_report.outliers_report.min_RMS_pos);
  printf("> max_RMS_pos     : %.6f\n", report.filter_report.outliers_report.max_RMS_pos);
  printf("> min_RMS_vel     : %.6f\n", report.filter_report.outliers_report.min_RMS_vel);
  printf("> max_RMS_vel     : %.6f\n", report.filter_report.outliers_report.max_RMS_vel);
  
  status = xo_orbit_id_init_data_close(&orbit_data_out, ierr);
  
  xd_free_orbit_file(&orbit_file[0]);
  printf("\n##############################################\n");
  
  /*==============================================*/
  /*  Twentieth example: ORBIT_ID_CHANGE          */
  /*==============================================*/
  xd_silent();
  printf("\n\n\n xo_orbit_id_change\n");
  
//===================================================================================================
//printf("\n TEST 1 - Call xo_orbit_init_file with OSF and POF\n");
//===================================================================================================
  /* 1.1. Time Id initialization POF only */
  /* ------------------------------------ */
  orbit_file_mode = XO_ORBIT_INIT_POF_MODE;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  local_status    = xl_time_ref_init_file(&orbit_file_mode, &n_files, input_files,
                                          &time_init_mode, &time_ref,
                                          &start_time, &stop_time, &start_orbit, &stop_orbit,
                                          &start_valtime, &stop_valtime,
                                          &time_id_pof, xl_ierr);
  if (local_status != XD_OK)
  {
    func_id = XL_TIME_REF_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }

  /* 1.2. Orbit Id initialization OSF+POF */
  /* ------------------------------------ */  
  sat_id          = XL_SAT_CRYOSAT;
  orbit_file_mode = XO_ORBIT_INIT_AUTO;
  n_files         = 2;
  input_files[0]  = osf_file1;
  input_files[1]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  local_status    = xo_orbit_init_file(&sat_id, &model_id_pof, &time_id_pof,
                                       &orbit_file_mode, &n_files, input_files,
                                       &time_init_mode, &time_ref,
                                       &start_time, &stop_time, &start_orbit, &stop_orbit,
                                       &start_valtime, &stop_valtime, &orbit_id1,
                                       xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 1.3. Clean */
  /* ---------- */
  local_status = xo_orbit_close(&orbit_id1, xo_ierr);
  local_status = xl_time_close(&time_id_pof, xo_ierr);


//===================================================================================================
//printf("\n TEST 2 - Call xo_orbit_id_change using OSF change mode\n");
//===================================================================================================
  /* 2.1. Time Id initialization POF only */
  /* ------------------------------------ */
  orbit_file_mode = XO_ORBIT_INIT_POF_MODE;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  local_status    = xl_time_ref_init_file(&orbit_file_mode, &n_files, input_files,
                                          &time_init_mode, &time_ref,
                                          &start_time, &stop_time, &start_orbit, &stop_orbit,
                                          &start_valtime, &stop_valtime,
                                          &time_id_pof, xl_ierr);
  if (local_status != XD_OK)
  {
    func_id = XL_TIME_REF_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 2.2. Orbit Id initialization POF */
  /* -------------------------------- */  
  sat_id          = XL_SAT_CRYOSAT;
  orbit_file_mode = XO_ORBIT_INIT_AUTO;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  local_status    = xo_orbit_init_file(&sat_id, &model_id_pof, &time_id_pof,
                                       &orbit_file_mode, &n_files, input_files,
                                       &time_init_mode, &time_ref,
                                       &start_time, &stop_time, &start_orbit, &stop_orbit,
                                       &start_valtime, &stop_valtime, &orbit_id2,
                                       xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 2.3. Read OSF File */
  /* ------------------ */
  input_files[0] = osf_file1;
  local_status   = xd_read_osf (input_files[0], &osf_file_527, xd_ierr);
  if (local_status != XD_OK)
  {
    func_id = XD_READ_OSF_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  
  /* 2.4. call xo_orbit_id_change with OSF MODE */
  /* ------------------------------------------ */
  time_ref = XO_TIME_UT1;
  
  change_data.change_mode  = XO_ORBIT_ID_CHANGE_OSF;
  change_data.eocfi_file.file_type = XD_OSF_FILE;
  change_data.eocfi_file.eocfi_file.osf_file     = osf_file_527;
  change_data.change_time_ref = time_ref;
  change_data.change_time  = 0;
  change_data.change_orbit = 0;
  
  local_status = xo_orbit_id_change(&orbit_id2,
                                    &change_data,
                                    xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_ID_CHANGE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 2.5. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  local_status = xo_orbit_close(&orbit_id2, xo_ierr);
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  

//===================================================================================================
//printf("\n TEST 3 - Call xo_orbit_id_change using Time/Orbit change mode\n");
//===================================================================================================
  /* 3.1. Time Id initialization POF only */
  /* ------------------------------------ */
  orbit_file_mode = XO_ORBIT_INIT_POF_MODE;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  local_status    = xl_time_ref_init_file(&orbit_file_mode, &n_files, input_files,
                                          &time_init_mode, &time_ref,
                                          &start_time, &stop_time, &start_orbit, &stop_orbit,
                                          &start_valtime, &stop_valtime,
                                          &time_id_pof, xl_ierr);
  if (local_status != XD_OK)
  {
    func_id = XL_TIME_REF_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 3.2. Orbit Id initialization POF */
  /* -------------------------------- */  
  sat_id          = XL_SAT_CRYOSAT;
  orbit_file_mode = XO_ORBIT_INIT_AUTO;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  local_status    = xo_orbit_init_file(&sat_id, &model_id_pof, &time_id_pof,
                                       &orbit_file_mode, &n_files, input_files,
                                       &time_init_mode, &time_ref,
                                       &start_time, &stop_time, &start_orbit, &stop_orbit,
                                       &start_valtime, &stop_valtime, &orbit_id3,
                                       xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 3.3. call xo_orbit_id_change with OSF MODE */
  /* ------------------------------------------ */
  change_data.change_mode  = XO_ORBIT_ID_CHANGE_TIME_ORBIT;
  change_data.change_time_ref = time_ref;
  change_data.change_time  = 1642.821194;
  change_data.change_orbit = 25876;
  local_status = xo_orbit_id_change(&orbit_id3,
                                    &change_data,
                                    xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_ID_CHANGE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 3.4. Clean */
  /* ---------- */
  local_status = xo_orbit_close(&orbit_id3, xo_ierr);
  local_status = xl_time_close(&time_id_pof, xo_ierr);

/*===================================================================================================*/
printf("\n TEST 4 - Call xo_orbit_id_init with OSF change mode\n");
/*===================================================================================================*/
  /* 4.1. Time Id initialization POF only */
  /* ------------------------------------ */
  orbit_file_mode = XO_ORBIT_INIT_POF_MODE;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  local_status    = xl_time_ref_init_file(&orbit_file_mode, &n_files, input_files,
                                          &time_init_mode, &time_ref,
                                          &start_time, &stop_time, &start_orbit, &stop_orbit,
                                          &start_valtime, &stop_valtime,
                                          &time_id_pof, xl_ierr);
  if (local_status != XD_OK)
  {
    func_id = XL_TIME_REF_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 4.2. Read OSF */
  /* ------------- */
  input_files[0] = osf_file1;
  local_status   = xd_read_osf (input_files[0], &osf_file_527, xd_ierr);
  if (local_status != XD_OK)
  {
    func_id = XD_READ_OSF_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 4.3. Read POF */
  /* ------------- */
  n_files = 1;
  extend_osv_flag  = XL_FALSE;
  time_init_mode   = XL_SEL_FILE;
  time_ref         = XL_TIME_UT1;
  start_time       = 0;
  stop_time        = 0;
  reading_osv_flag = XL_TRUE;
  
  local_status = xd_read_orbit_file (pof_file1, &extend_osv_flag, 
                                     &time_init_mode, &time_ref,
                                     &start_time, &stop_time, &reading_osv_flag, 
                                     &orbit_file_527,
                                     xd_ierr);
  if (local_status != XD_OK)
  {
    func_id = XD_READ_ORBIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  
  /* 4.4. Call xo_orbit_id_init (OSF CHANGE MODE) */
  /* -------------------------------------------- */
  sat_id          = XL_SAT_CRYOSAT;
  orbit_file_mode = XO_ORBIT_INIT_POF_ORBNUM_ADJ_MODE;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XL_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  n_files         = 1;
  
  eocfi_file_array_527.file_type = XD_ORBIT_FILE;
  eocfi_file_array_527.eocfi_file.orbit_file = orbit_file_527;    
    
  orbit_id_init_data_527.data_type = XL_FILE_DATA;
  orbit_id_init_data_527.orbit_id_init_data.file_set.num_files        = n_files;
  orbit_id_init_data_527.orbit_id_init_data.file_set.eocfi_file_array = &eocfi_file_array_527;
  
  orbit_id_init_data_527.change_data.change_mode  = XO_ORBIT_ID_CHANGE_OSF;
  orbit_id_init_data_527.change_data.eocfi_file.file_type = XD_OSF_FILE;
  orbit_id_init_data_527.change_data.eocfi_file.eocfi_file.osf_file     = osf_file_527;
  orbit_id_init_data_527.change_data.change_time_ref  = time_ref;
  orbit_id_init_data_527.change_data.change_time  = 0;
  orbit_id_init_data_527.change_data.change_orbit = 0;
  
  local_status = xo_orbit_id_init(&sat_id,
                                  &model_id_pof,
                                  &time_id_pof,
                                  &orbit_file_mode, &orbit_id_init_data_527,
                                  &time_init_mode, &time_ref,
                                  &start_time, &stop_time, &start_orbit, &stop_orbit,
                                  &start_valtime, &stop_valtime,
                                  &orbit_id2,
                                  xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_ID_INIT_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }

  /* 4.5. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  xd_free_orbit_file (&orbit_file_527);
  local_status = xo_orbit_close(&orbit_id2, xo_ierr);
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  

/*===================================================================================================*/
printf("\n TEST 5 - Call xo_orbit_id_init with Time/Orbit change mode\n");
/*===================================================================================================*/
  /* 5.1. Time Id initialization POF only */
  /* ------------------------------------ */
  orbit_file_mode = XO_ORBIT_INIT_POF_MODE;
  n_files         = 1;
  input_files[0]  = pof_file1;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XO_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  local_status    = xl_time_ref_init_file(&orbit_file_mode, &n_files, input_files,
                                          &time_init_mode, &time_ref,
                                          &start_time, &stop_time, &start_orbit, &stop_orbit,
                                          &start_valtime, &stop_valtime,
                                          &time_id_pof, xl_ierr);
  if (local_status != XD_OK)
  {
    func_id = XL_TIME_REF_INIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 5.2. Read POF */
  /* ------------- */
  n_files = 1;
  extend_osv_flag  = XL_FALSE;
  time_init_mode   = XL_SEL_FILE;
  time_ref         = XL_TIME_UT1;
  start_time       = 0;
  stop_time        = 0;
  reading_osv_flag = XL_TRUE;
  
  local_status = xd_read_orbit_file (pof_file1, &extend_osv_flag, 
                                     &time_init_mode, &time_ref,
                                     &start_time, &stop_time, &reading_osv_flag, 
                                     &orbit_file_527,
                                     xd_ierr);
  if (local_status != XD_OK)
  {
    func_id = XD_READ_ORBIT_FILE_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }
  
  /* 4.4. Call xo_orbit_id_init (Time/Orbit Change Mode) */
  /* --------------------------------------------------- */
  sat_id          = XL_SAT_CRYOSAT;
  orbit_file_mode = XO_ORBIT_INIT_POF_ORBNUM_ADJ_MODE;
  time_init_mode  = XO_SEL_FILE;
  time_ref        = XL_TIME_UT1;
  start_time      = 0;
  stop_time       = 0;
  start_orbit     = 0;
  stop_orbit      = 0;
  start_valtime   = 0;
  stop_valtime    = 0;
  n_files         = 1;
  
  eocfi_file_array_527.file_type = XD_ORBIT_FILE;
  eocfi_file_array_527.eocfi_file.orbit_file = orbit_file_527;    
    
  orbit_id_init_data_527.data_type = XL_FILE_DATA;
  orbit_id_init_data_527.orbit_id_init_data.file_set.num_files        = n_files;
  orbit_id_init_data_527.orbit_id_init_data.file_set.eocfi_file_array = &eocfi_file_array_527;
  
  orbit_id_init_data_527.change_data.change_mode  = XO_ORBIT_ID_CHANGE_TIME_ORBIT;
  orbit_id_init_data_527.change_data.change_time_ref = time_ref;
  orbit_id_init_data_527.change_data.change_time  = 1642.821194;
  orbit_id_init_data_527.change_data.change_orbit = 25876;
  
  local_status = xo_orbit_id_init(&sat_id,
                                  &model_id_pof,
                                  &time_id_pof,
                                  &orbit_file_mode, &orbit_id_init_data_527,
                                  &time_init_mode, &time_ref,
                                  &start_time, &stop_time, &start_orbit, &stop_orbit,
                                  &start_valtime, &stop_valtime,
                                  &orbit_id3,
                                  xo_ierr);
  if (local_status != XD_OK)
  {
    func_id = XO_ORBIT_ID_INIT_ID;
    xd_get_msg(&func_id, ierr, &n, msg);
    xd_print_msg(&n, msg);
  }

  /* 4.5. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  xd_free_orbit_file (&orbit_file_527);
  local_status = xo_orbit_close(&orbit_id3, xo_ierr);
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  
  
  
  
  
  
  printf("\n");
  printf("==================================\n");
  printf("=      EXAMPLE RUN FINISHED      =\n");
  printf("==================================\n");
  
  /* Close time reference */
  status = xl_time_close(&time_id, ierr);
  if (status != XL_OK)
  {
    func_id = XL_TIME_CLOSE_ID;
    xl_get_msg(&func_id, ierr, &n, msg);
    xl_print_msg(&n, msg);
  }

  status = xl_model_close(&model_id, xl_ierr);
  if (status != XL_OK)
  {
    func_id = XL_MODEL_CLOSE_ID;
    xl_get_msg(&func_id, ierr, &n, msg);
    xl_print_msg(&n, msg);
  }

  printf("\nEOCFI_ORBIT EXAMPLE COMPLETED SUCCESSFULLY\n"); 

  return(0);

}

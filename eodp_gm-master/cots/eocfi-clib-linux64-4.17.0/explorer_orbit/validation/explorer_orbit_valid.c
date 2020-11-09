
 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Test level  : VALIDATION
 *
 * Module      : explorer_orbit_valid.c
 * Purpose     : It runs validation tests of EXPLORER_ORBIT
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

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <explorer_orbit.h>
#include <explorer_data_handling.h>

/* Macro definition */
/* ---------------- */

#define MAX_CONDITION                   1000    /* Maximum number of checks pertest case */

#define START_VALIDATION                int main(int argc, char *argv[]){ \
                                        double di,th,ta,tb,sinta,costa,sintb,costb;\
                                        double di_l,di_r,th_l,th_r; \
                                        int i,j; \
                                        int checks; \
                                        XO_Boolean condition[MAX_CONDITION]; \
                                        XO_Boolean result;

#define START_CHECK(msg)                printf(" *** %s\n",msg); \
                                        checks = 0;

#define END_CHECK                       result = XO_TRUE; \
                                        for (i = 0 ; i < checks ; i++) \
                                          { \
                                          if (condition[i] == XO_FALSE) \
                                            { \
                                            result = XO_FALSE; \
                                            break; \
                                            } \
                                          } \
                                        if (result == XO_TRUE) \
                                          { \
                                          printf(" *** RESULT = PASS ***\n\n"); \
                                          } \
                                        else \
                                          { \
                                          printf(" *** RESULT = FAIL ***\n\n"); \
                                          }


#define CHECK_STATUS(msg,stat)          if (stat < XO_OK ) { \
                                          condition[checks] = XO_FALSE; \
                                          printf("\n ...\t%s (XO_FALSE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XO_TRUE; \
                                          printf("\n ...\t%s (XO_TRUE)\n",msg); \
                                        } \
                                        checks++;
#define CHECK_PAR(msg,p,p0,dp)          if((di=fabs(p-p0)) <= (th=dp)){ \
                                          condition[checks] = XO_TRUE; \
                                          printf(" ...\t%s (XO_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XO_FALSE; \
                                          printf(" ...\t%s (XO_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Threshold  : %g\n",th); \
                                        printf("\t\t Difference : %g\n",di); \
                                        checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)    for(i=im;i<=iM;++i){ \
                                          CHECK_PAR(msg,v[i],v0[i],dp); \
                                        }
#define END_VALIDATION                  return(0); \
                                        }

#define XO_MAX_STR_LENGTH        256

typedef enum
{
  XO_FALSE = 0,      /* False variable */
  XO_TRUE = 1        /* True variable */

} XO_Boolean;

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Validation for EXPLORER_ORBIT                                             */
/*                                                                           */
/* ------------------------------------------------------------------------- */

START_VALIDATION
  
  /* External variable declaration (time reference initialization) */
  /* ------------------------------------------------------------- */

  extern long   xl_time_init_flag;
  extern double xl_delta_tai_utc, xl_delta_tai_ut1, xl_delta_tai_gps;


  /* Nominal acceptance values */
  /* ------------------------- */
  double mjdr = -730.0;
  long irep = 369;
  long icyc = 5344;
  double rlong = 323.8212;
  double ascmlst = 8.6667;
  long iorb0 = 0;
  long iorb = 43;

  double ascmlst_drift = 0.784;
  double inclination = 92.0;
  double mlst_drift;

  double mjdp = -2452.569; /* UT1 time */
  double pos_ini[] = { 6427293.5314 , -3019463.3246 , 0.000 };
  double vel_ini[] = { -681.1285 , -1449.8649 , 7419.5081 };

  long sat_id = XO_SAT_CRYOSAT;


  /* Local variables definition */
  /* -------------------------- */

  long time_mode, orbit_mode;
  char* files[1];
  xo_orbit_id    orbit_id    = {NULL};

  long propag_model;
  long interpol_model;
  long time_init_mode;
  long time_model;
  long drift_mode;
  long extra_choice;
  long init_mode;

  long time_ref_utc = XO_TIME_UTC,
       time_ref_ut1 = XO_TIME_UT1;

  long status,ierr[XO_ERR_VECTOR_MAX_LENGTH];
  long xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];
  long xl_ierr[XL_ERR_VECTOR_MAX_LENGTH];
  long xo_ierr[XL_ERR_VECTOR_MAX_LENGTH];

  double val_time0, val_time1;
  double time_anx, time_anx1;
  double time, time0, time1;


  double pos[3],vel[3],acc[3];
  double pos1[3],vel1[3],acc1[3];

  double propag_model_out[XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS], 
         propag_extra_out[XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS];
  double interpol_model_out[XO_ORBIT_EXTRA_NUM_DEP_ELEMENTS],
         interpol_extra_out[XO_ORBIT_EXTRA_NUM_INDEP_ELEMENTS];

  char   *input_files[3];
  long orbit0, orbit1, n_files;

  long orbit_t, second_t, microsec_t;
  long time_ref;
  double time_t;
  char orbit_scenario_file_t[XO_MAX_STR_LENGTH];

  long abs_orbit, rel_orbit, cycle, phase;
  double result_vector[XO_ORBIT_INFO_EXTRA_NUM_ELEMENTS];

  long num_rec;
  xo_osv_rec *osv;
  xo_osf_records *osf;
  xo_validity_time val_time;
  xo_anx_extra_info *extra_info;

  xo_propag_id_data propag_data;
  xo_interpol_id_data interpol_data;

#ifndef XL_WINDOWS
  char   file1[] = "../example/data/EARTH_EXPLORER_FPO_2000";
  char   file2[] = "../example/data/CRYOSAT_DORIS_NAV_2000";
  char   file3[] = "../example/data/EARTH_EXPLORER_FRO";
  char   file4[] = "../example/data/EARTH_EXPLORER_FPO";
  char   file5[] = "../example/data/ROF_FILE_OUTLIER";
#else
  char   file1[] = "..\\example\\data\\EARTH_EXPLORER_FPO_2000";
  char   file2[] = "..\\example\\data\\CRYOSAT_DORIS_NAV_2000";
  char   file3[] = "..\\example\\data\\EARTH_EXPLORER_FRO";
  char   file4[] = "..\\example\\data\\EARTH_EXPLORER_FPO";
  char   file5[] = "..\\example\\data\\ROF_FILE_OUTLIER";
#endif

  /* xg_gen_osf_create variables */
  /*-----------------------------*/
  long repeat_cycle, cycle_length;
  double anx_long, mlst,
         date;
  char output_dir[XD_MAX_STR] = ".",
       output_file_1[XD_MAX_STR] = "mpl_orb_sc.create.xml",
       date_string[XD_MAX_STR] = "2002-03-01_00:00:00.000000";
   
  long proc_out = XL_PROC,
       ascii_in = XL_ASCII_STD_MICROSEC;

   /* xo_gen_osf_append_orbit_change variables */
  /*------------------------------------------*/
  long phase_inc;
  char input_file_2[XD_MAX_STR] = "./mpl_orb_sc.create.xml",
       output_file_2[XD_MAX_STR] = "mpl_orb_sc.append.xml";
   
  /* xo_gen_osf_change_repeat_cycle variables */
  /*------------------------------------------*/
  long search_direction = XO_SEARCH_FORWARD;
  char input_file_3[XD_MAX_STR] = "./mpl_orb_sc.create.xml",
       output_file_3[XD_MAX_STR] = "mpl_orb_sc.change.xml";
        
  /* xo_gen_osf_add_drift_cycle variables */
  /*--------------------------------------*/
  long drift_start_orbit,
       drift_stop_orbit,
       drift_start_ph_inc,
       drift_stop_ph_inc;
  double max_delta_alt;
  char input_file_4[XD_MAX_STR] = "./mpl_orb_sc.create.xml",
       output_file_4[XD_MAX_STR] = "mpl_orb_sc.drift.xml";

  /* xo_gen_rof_prototype variables */
  /* ------------------------------ */

  long start_orbit, stop_orbit;
  
  double start_time, stop_time;
  
  double osv_interval;
  
  char output_directory[XD_MAX_STR], rof_filename[XD_MAX_STR];

  static char *file_class = "TEST";
  long         version_number = 11;
  static char *fh_system = "CFI Validation";

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
  char oef_filename[XD_MAX_STR];

  long pof_filetype;

  /* xo_gen_dnf variables */
  /* -------------------- */
  long dnf_filetype;
  long dtai,
       ascii_id_in,
       proc_id_out;
  char control_file[256],
       doris_nav[256],
       rof_file[256],
       utce0[28],
       utce1[28];

  long fit_mode;
  char tle_filename[256];

  /* Precise propagator configuration file */
  /* ------------------------------------- */
  char precise_conf_file[XO_MAX_STR_LENGTH] = "";
  
  /* xo_check_osf and xo_check_oef variables */
  /* --------------------------------------- */
  double check_osf_thr[6];
  double check_oef_thr[6];
  char *osf_file;
  long transition_number;
  double max_diffs[XO_NUM_CHECK_PARAMS],
         rms[XO_NUM_CHECK_PARAMS],
         diffs[XO_NUM_CHECK_PARAMS];

  
  /* Initializing Time Reference */
  /* --------------------------- */

  /* xl_time_ref_init variable declaration */
  /* ------------------------------------- */
  long   tri_orbit_num;
  double tri_anx_time, tri_orbit_duration;
  double tri_time[XL_TIME_TRANS_DIM_MAX];
  long   tri_ierr[XL_NUM_ERR_TIME_REF_INIT];

  xl_model_id model_id = {NULL};
  xl_time_id time_id   = {NULL};

  xl_time_id_init_data  time_id_init_data;
  xo_orbit_id_init_data orbit_id_init_data;

  xd_osf_file osf_data;
  xo_geo_orbit_init_data geo_init_data;
  
  /* position_on_orbit_to_time */
  long   abs_orbit_number,
         angle_type,
         deriv,
         mode;
  double angle,
         angle_rate,
         angle_rate_rate;
  long   models[XL_NUM_MODEL_TYPES_ENUM];


  /* xo_orbit_data_filter */
  /* -------------------- */
  xo_orbit_id_init_data    orbit_data_in;
  xo_orbit_filter_settings filter_settings;
  xo_orbit_id_init_data    orbit_data_out;
  xo_orbit_filter_report   report;
  xd_eocfi_file            eocfi_file_array[4];
  
  xd_orbit_file            orbit_file[4];
  long                     reading_osv_flag,
                           extend_osv_flag;
  double                   range0,
                           range1;
  char                     orbit_filename[XO_MAX_STR];
  
  
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
  xo_orbit_id_change_data change_data;
  
  long local_status,
       orbit_file_mode;
  
  double start_valtime,
         stop_valtime;

#ifndef XL_WINDOWS
  char osf_file1[] = "../example/data/CRYOSAT_XML_OSF_ANR_527";
  char pof_file1[] = "../example/data/EARTH_EXPLORER_FPO_ANR_527";
#else
  char osf_file1[] = "..\\example\\data\\CRYOSAT_XML_OSF_ANR_527";
  char pof_file1[] = "..\\example\\data\\EARTH_EXPLORER_FPO_ANR_527";
#endif
  
  /* xo_orbit_id_change end */
  /* ---------------------- */
  
  
  
  /* Set input values */
  /* ---------------- */
  tri_time[0]   = -1100.1000000000000;   /* TAI time [days] */
  tri_time[1]   = -1100.0995949074074;   /* UTC time [days] (= TAI + 35.0 s) */
  tri_time[2]   = -1100.0995914351852;   /* UT1 time [days] (= TAI + 35.3 s) */
  tri_time[3]   = -1100.099780092;       /* GPS time [days] (= TAI + 19.0 s) */
  tri_orbit_num = 10;
  tri_anx_time  = 5245.123456;
  tri_orbit_duration = 6035.928144;

  /* Call xl_time_ref_init function */
  /* ------------------------------ */
  xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
		   &tri_orbit_duration, &time_id, tri_ierr);

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-0
 *
 ****************************************************************************************/

START_CHECK("Check the libraries' versions")

   status = expcfi_check_libs();
   if (status != XO_OK)
   {
     printf("Library incompatibility.\n");
     CHECK_STATUS("Compatibility test (expcfi_check_libs)", status);
   }

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case    xo_orbit_init_def and xo_osv_compute validation
 * ---------
 *
 * Test number: VT-1
 *
 ****************************************************************************************/

START_CHECK("xo_orbit_init_def and xo_osv_compute")

  time_init_mode = XO_SEL_ORBIT;
  drift_mode     = XO_NOSUNSYNC_DRIFT;
  extra_choice   = XO_ORBIT_EXTRA_DEP_ANX_TIMING;

  time = mjdr;

  status = xo_orbit_init_def(&sat_id, &model_id, &time_id, &time_ref_utc, &time,
                             &iorb0, &drift_mode, &ascmlst_drift, &inclination, 
                             &irep, &icyc, &rlong, &ascmlst, 
                             &val_time0, &val_time1, &orbit_id, ierr);

  CHECK_STATUS("STATUS of xo_orbit_init_def",status);


  status = xo_osv_compute_extra(&orbit_id, &extra_choice,
                              propag_model_out, propag_extra_out, ierr);
  CHECK_STATUS("xo_osv_compute_extra",status);

  /* save time at ANX */
  time_anx = propag_model_out[XO_ORBIT_EXTRA_DEP_UTC_CURRENT_ANX]; /* UTC */

  status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time_anx,
                         /* outputs */
                         pos, vel, acc, ierr);

  CHECK_STATUS("xo_osv_compute",status);

  status = xo_orbit_close(&orbit_id, ierr);

  CHECK_STATUS("xo_orbit_close",status);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case    xo_orbit_cart_init and xo_osv_compute validation
 * ---------
 *
 * Test number: VT-2
 *
 ****************************************************************************************/

START_CHECK("xo_orbit_cart_init and xo_osv_compute")

  extra_choice = XO_ORBIT_EXTRA_DEP_ANX_TIMING;

  time = mjdp;

  status = xo_orbit_cart_init(&sat_id, &model_id, &time_id,
                              &time_ref_ut1, &time,
                              pos_ini, vel_ini, &abs_orbit,
                              &val_time0, &val_time1, &orbit_id, 
                              ierr);
  CHECK_STATUS("STATUS of orbit_cart_init",status);

  init_mode = XO_SEL_DEFAULT;


  status = xo_osv_compute_extra(&orbit_id, &extra_choice, propag_model_out, propag_extra_out, ierr);

  CHECK_STATUS("xo_osv_compute_extra",status)

  /* save time at ANX */
  time_anx1 = propag_model_out[XO_ORBIT_EXTRA_DEP_UTC_CURRENT_ANX]; /* UTC */

  status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time_anx1,
                         /* outputs */
                         pos1, vel1, acc1, ierr);

  CHECK_STATUS("xo_osv_compute",status)

  status = xo_orbit_close(&orbit_id, ierr);

  CHECK_STATUS("xo_orbit_close",status);

  /* Close time_id, since a different one will be used in following tests */
  status = xl_time_close(&time_id, ierr);
  
  CHECK_STATUS("xl_time_close",status);
  
END_CHECK

   
/*****************************************************************************************
 *
 * ---------
 * Test case    xo_orbit_init_file (POF+DORIS) and xo_osv_compute validation
 * ---------
 *
 * Test number: VT-3
 *
 ****************************************************************************************/

START_CHECK("xo_orbit_init_file and xo_osv_compute (POF+DORIS)")

  time_init_mode = XO_SEL_TIME;
  time_ref = XO_TIME_TAI;
  
  time0 = 0.826388888889;  /*01-01-2000 19:50:00 TAI*/
  time1 = 0.916666666667;  /*01-01-2000 22:00:00 TAI*/

  input_files[0] = file1;
  input_files[1] = file2;
  n_files = 2;

  orbit_mode = XO_ORBIT_INIT_AUTO;
  
  /* Initialise time_id with file so there are no conflicts in time correlations */
  time_init_mode = XO_SEL_FILE;
  time_model = XL_TIMEMOD_AUTO;
  n_files = 1;
  status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_init_mode,
                                  &time_ref, &time0, &time1, &orbit0, &orbit1,
                                  &val_time0, &val_time1, &time_id,
                                  tri_ierr );
  CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
  
  n_files = 2;
  time_init_mode = XO_SEL_TIME;
  status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, input_files,
                               &time_init_mode, &time_ref_utc,
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1, &orbit_id,
                               ierr);

  CHECK_STATUS("STATUS of xo_orbit_init_file", status);

  /* propagating within the validity range (in UTC time) */
  status = xo_orbit_get_propag_config(&orbit_id, &propag_data);
  CHECK_STATUS("xo_propag_get_id_data", status);

  val_time0 = propag_data.propag_osv.val_time.start;
  val_time1 = propag_data.propag_osv.val_time.stop;

  time = (val_time0 + val_time1)/2.0;

  status = xo_osv_compute(&orbit_id, &propag_model, &time_ref_utc, &time,
                         /* outputs */
                         pos, vel, acc, ierr);
  CHECK_STATUS("xo_osv_compute",status)

  status = xo_orbit_close(&orbit_id, ierr);

  CHECK_STATUS("xo_orbit_close",status);

  status = xl_time_close(&time_id, ierr);
  
  CHECK_STATUS("xl_time_close",status);
  
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case    xo_orbit_init_file (ROF), xo_osv_compute and xo_osv_compute_extra
 * ---------
 *
 * Test number: VT-4
 *
 ****************************************************************************************/

START_CHECK("xo_orbit_init_file (ROF), xo_osv_compute and xo_osv_compute_extra")

  time_init_mode = XO_SEL_TIME;
  extra_choice   = XO_ORBIT_EXTRA_ALL_RESULTS;

  time0 = -284.995;
  time1 = -284.9895;

  input_files[0] = file3;
  n_files = 1;

  orbit_mode = XO_ORBIT_INIT_AUTO;

  /* Initialise time_id with file so there are no conflicts in time correlations */
  time_init_mode = XO_SEL_FILE;
  time_model = XL_TIMEMOD_AUTO;
  status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_init_mode,
                                  &time_ref, &time0, &time1, &orbit0, &orbit1,
                                  &val_time0, &val_time1, &time_id,
                                  tri_ierr );
  CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
  
  time_init_mode = XO_SEL_TIME;
  status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, input_files,
                               &time_init_mode, &time_ref_utc,
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1, &orbit_id,
                               ierr);

  CHECK_STATUS("STATUS of xo_orbit_init_file", status);
  /* interpolating within the validity range (in UTC time) */

  time = (val_time0 + val_time1)/2.0;

  status = xo_osv_compute(&orbit_id, &interpol_model, &time_ref_utc, &time,
                         /* outputs */
                         pos, vel, acc, ierr);

  CHECK_STATUS("xo_osv_compute",status)

  status = xo_osv_compute_extra(&orbit_id, &extra_choice, 
                              interpol_model_out, interpol_extra_out, ierr);
  CHECK_STATUS("xo_osv_compute_extra",status);


  status = xo_orbit_close(&orbit_id, ierr);

  CHECK_STATUS("xo_orbit_close",status);

  status = xl_time_close(&time_id, ierr);
  
  CHECK_STATUS("xl_time_close",status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-4
 *
 ****************************************************************************************/

/*---------- xo_time_to_orbit and xo_orbit_to_time validation -------------*/
/*-------------------------------------------------------------------------*/
START_CHECK("xo_time_to_orbit and xo_orbit_to_time")


#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../example/data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\example\\data\\CRYOSAT_XML_OSF");
#endif

   /* orbit initialization with an OSF */
   /* -------------------------------- */

   sat_id = XO_SAT_CRYOSAT;
   time_ref = XO_TIME_UT1;
   sat_id = XO_SAT_CRYOSAT;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   files[0] = orbit_scenario_file_t;

   /* Initialise time_id with file so there are no conflicts in time correlations */
  time_model = XL_TIMEMOD_AUTO;
  status = xl_time_ref_init_file( &time_model, &n_files, files, &time_mode,
                                  &time_ref, &time0, &time1, &orbit0, &orbit1,
                                  &val_time0, &val_time1, &time_id,
                                  tri_ierr );
  CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
  
   status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, files,
                               &time_mode, &time_ref, 
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1,
                               &orbit_id, ierr);

   CHECK_STATUS("xo_orbit_init_file",status);


   orbit_t= 1034;
   second_t= 3000;
   microsec_t= 50;

   status = xo_orbit_to_time(&orbit_id, &orbit_t,
                             &second_t, &microsec_t, &time_ref,
   			     /* output */
                  	     &time_t, ierr);

   CHECK_STATUS("xo_orbit_to_time",status);


   status = xo_time_to_orbit(&orbit_id, &time_ref, &time_t,
   			     /* output */
			     &orbit_t, &second_t, &microsec_t, ierr);

   CHECK_STATUS("xo_time_to_orbit",status);

   status = xo_orbit_close(&orbit_id, ierr);

   CHECK_STATUS("xo_orbit_close",status);

   status = xl_time_close(&time_id, ierr);
  
  CHECK_STATUS("xl_time_close",status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-5
 *
 ****************************************************************************************/

/*---------- xo_orbit_rel_from_abs, abs_from_rel, abs_from_phase ---------------*/
/*------------------------------------------------------------------------------*/
START_CHECK("xo_orbit_rel_from_abs, xo_orbit_abs_from_rel, xo_orbit_abs_from_phase")

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../example/data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\example\\data\\CRYOSAT_XML_OSF");
#endif

   /* orbit initialization with an OSF */
   /* -------------------------------- */
   sat_id = XO_SAT_CRYOSAT;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   files[0] = orbit_scenario_file_t;

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   status = xl_time_ref_init_file( &time_model, &n_files, files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
   
   status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, files,
                               &time_mode, &time_ref, 
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1,
                               &orbit_id, ierr);

   CHECK_STATUS("xo_orbit_init_file",status);

   abs_orbit = 270;

   status = xo_orbit_rel_from_abs (&orbit_id, &abs_orbit,
                                    /* output */
                                    &rel_orbit, &cycle, &phase, ierr);

   CHECK_STATUS("xo_orbit_rel_from_abs",status);

   status = xo_orbit_info (&orbit_id, &abs_orbit, 
                           result_vector, ierr);

   CHECK_STATUS("xo_orbit_info",status);

   status = xo_orbit_abs_from_rel (&orbit_id, &rel_orbit, &cycle,
                                    /* output */
                                    &abs_orbit, &phase, ierr);

   CHECK_STATUS("xo_orbit_abs_from_rel",status);

   status = xo_orbit_abs_from_phase (&orbit_id, &phase,
                                     /* output */
                                     &abs_orbit, &rel_orbit, &cycle, ierr);

   CHECK_STATUS("xo_orbit_abs_from_phase",status);

   status = xo_orbit_info (&orbit_id, &abs_orbit, 
                           result_vector, ierr);

   CHECK_STATUS("xo_orbit_info",status);

   status = xo_orbit_close(&orbit_id,
   			   /* output */
                           ierr);

   CHECK_STATUS("xo_orbit_close",status);

   status = xl_time_close(&time_id, ierr);
  
  CHECK_STATUS("xl_time_close",status);
END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-6
 *
 ****************************************************************************************/

/*---------- orbit accessors ---------------*/
/*------------------------------------------*/
START_CHECK("Orbit Accessors")

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../example/data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\example\\data\\CRYOSAT_XML_OSF");
#endif

   /* orbit initialization with an OSF */
   /* -------------------------------- */
   sat_id = XO_SAT_CRYOSAT;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   files[0] = orbit_scenario_file_t;
   time_ref = XL_TIME_UTC;

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   status = xl_time_ref_init_file( &time_model, &n_files, files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
  
   status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                               &orbit_mode, &n_files, files,
                               &time_mode, &time_ref, 
                               &time0, &time1, &orbit0, &orbit1,
                               &val_time0, &val_time1,
                               &orbit_id, ierr);

   CHECK_STATUS("xo_orbit_init_file",status);

   status = xo_orbit_init_status(&orbit_id);
   CHECK_STATUS("xo_orbit_init_status", status);

   sat_id = xo_orbit_get_sat_id(&orbit_id);
   status = (sat_id == XO_SAT_CRYOSAT ? XO_OK : XO_ERR);
   CHECK_STATUS("xo_orbit_get_sat_id", status);

   orbit_mode = xo_orbit_get_mode(&orbit_id);
   status = (orbit_mode == XO_ORBIT_INIT_OSF_MODE ? XO_OK : XO_ERR);
   CHECK_STATUS("xo_orbit_get_mode", status);

   status = xo_orbit_get_osf_rec(&orbit_id, &num_rec, &osf);
   CHECK_STATUS("xo_orbit_get_osv", status);

   status = xo_orbit_set_osf_rec(&orbit_id,  &num_rec, osf);
   CHECK_STATUS("xo_orbit_set_osv", status);
   
   status = xo_orbit_get_val_time(&orbit_id, &val_time);
   CHECK_STATUS("xo_orbit_get_val_time", status);
   
   status = xo_orbit_set_val_time(&orbit_id, &val_time);
   CHECK_STATUS("xo_orbit_set_val_time", status);
   
   free (osf);

   status = xo_orbit_get_propag_config(&orbit_id, &propag_data);
   CHECK_STATUS("xo_propag_get_id_data", status);


   status = xo_orbit_close(&orbit_id, ierr);
   CHECK_STATUS("xo_orbit_close",status);

   
   /* orbit initialization with a ROF file */
   /* ------------------------------------ */
   time_init_mode = XO_SEL_TIME;
   time0 = -284.995;
   time1 = -284.9895;
   input_files[0] = file3;
   n_files = 1;

   orbit_mode = XO_ORBIT_INIT_AUTO;
   time_init_mode = XO_SEL_TIME;
   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                ierr);
   CHECK_STATUS("STATUS of xo_orbit_init_file", status);

   status = xo_orbit_get_osv(&orbit_id, 
                             &num_rec, &osv);
   CHECK_STATUS("STATUS of xo_orbit_get_osv", status);

   status = xo_orbit_set_osv(&orbit_id, &num_rec, osv);
   CHECK_STATUS("STATUS of xo_orbit_set_osv", status);

   status = xo_orbit_get_anx(&orbit_id, 
                             &num_rec, &extra_info);
   CHECK_STATUS("STATUS of xo_orbit_get_anx", status);

   status = xo_orbit_set_anx(&orbit_id, 
                             &num_rec, extra_info);
   CHECK_STATUS("STATUS of xo_orbit_set_anx", status);

   /* interpol initialization */
   status = xo_orbit_get_interpol_config(&orbit_id, &interpol_data);
   CHECK_STATUS("xo_interpol_get_id_data", status);

   status = xo_orbit_close(&orbit_id, ierr);
   CHECK_STATUS("xo_orbit_close",status);

   status = xl_time_close(&time_id, ierr);  
   CHECK_STATUS("xl_time_close",status);

  
   free (osv);
   osv = NULL;
   free (extra_info);
   extra_info = NULL;

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-7
 *
 ****************************************************************************************/

/*---------- orbit accessors ---------------*/
/*------------------------------------------*/
START_CHECK("xo_orbit_id_init")

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file_t,"../example/data/CRYOSAT_XML_OSF");
#else
   strcpy(orbit_scenario_file_t,"..\\example\\data\\CRYOSAT_XML_OSF");
#endif

   /* orbit initialization with data read from OSF */
   /* -------------------------------------------- */
   status = xd_read_osf (orbit_scenario_file_t,
                         &osf_data, xd_ierr);
   CHECK_STATUS( "xd_read_osf status", status);

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

   CHECK_STATUS("xl_time_id_init",status);

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
   CHECK_STATUS("xo_orbit_id_init status", status);

   /* free osf data */
   xd_free_osf (&osf_data);

   status = xo_orbit_close(&orbit_id, ierr);
   CHECK_STATUS("xo_orbit_close",status);

   /* Do not close time_id, it will be used in following tests */

END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-8
 *
 ******************************************************************************/
START_CHECK("Check XO_GEN_OSF_CREATE status is OK")

   /* GEN OSF_CREATE */
   sat_id = XL_SAT_ENVISAT;
   status = xl_time_ascii_to_processing(&time_id,
                                        &ascii_in, &time_ref, 
                                        date_string,
                                        &proc_out, &time_ref,
                                        &date,
                                        ierr);
   
   abs_orbit = 1;
   cycle = 1;
   phase = 1;
   repeat_cycle = 35;
   cycle_length = 501;
   drift_mode = XO_NOSUNSYNC_DRIFT;
   mlst_drift = 0.0;
   mlst = 22.0;
   anx_long = 286.525113;
      
   printf("\n\nXO_GEN_OSF_CREATE\n");     

   status = xo_gen_osf_create(&sat_id, &model_id, &time_id, 
                              &abs_orbit, &cycle, &phase,
                              &repeat_cycle, &cycle_length,
                              &anx_long,
                              &drift_mode,
                              &inclination, &mlst_drift,
                              &mlst, &date,
                              output_dir, output_file_1,
                              file_class, &version_number,
                              fh_system,
                              ierr);
   CHECK_STATUS("xo_gen_osf_create status", status)

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-9
 *
 ******************************************************************************/
START_CHECK("Check XO_GEN_OSF_APPEND_ORBIT_CHANGE status is OK")

   abs_orbit = 502;
   phase_inc = 1;
   repeat_cycle = 3;
   cycle_length = 43;
   anx_long = 286.524398;

   printf("\n\nXO_GEN_OSF_APPEND_ORBIT_CHANGE\n");     

   status = xo_gen_osf_append_orbit_change(&sat_id, &model_id, 
                                           &time_id, input_file_2,
                                           &abs_orbit,
                                           &repeat_cycle, &cycle_length,
                                           &anx_long,
                                           &drift_mode,
                                           &inclination, &mlst_drift,
                                           &mlst,
                                           &phase_inc,
                                           output_dir, output_file_2,
                                           file_class, &version_number,
                                           fh_system,
                                           ierr);

   CHECK_STATUS("xo_gen_osf_append_orbit_change status", status)

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-10
 *
 ******************************************************************************/
START_CHECK("Check XO_GEN_OSF_CHANGE_REPEAT_CYCLE status is OK")

   abs_orbit = 2;
   phase_inc = XO_NO_PHASE_INCREMENT;
   repeat_cycle =194;
   cycle_length = 2775;
   anx_long = 168.680802;

   printf("\n\nXO_GEN_OSF_CHANGE_REPEAT_CYCLE\n");     

   status = xo_gen_osf_change_repeat_cycle(&sat_id, &model_id, &time_id,
                                           input_file_3,
                                           &abs_orbit, &search_direction,
                                           &repeat_cycle, &cycle_length,
                                           &anx_long,
                                           &drift_mode,
                                           &inclination, &mlst_drift,
                                           &phase_inc,
                                           output_dir, output_file_3,
                                           file_class, &version_number,
                                           fh_system,
                                           ierr);

   CHECK_STATUS("xo_gen_osf_change_repeat_cycle status", status)

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-11
 *
 ******************************************************************************/
START_CHECK("Check XO_GEN_OSF_ADD_DRIFT_CYCLE status is OK")

   drift_start_orbit = 20;
   drift_stop_orbit = 486;
   drift_start_ph_inc = XO_NO_PHASE_INCREMENT;
   drift_stop_ph_inc = XO_PHASE_INCREMENT;
   anx_long = 320.612542;
   max_delta_alt = 10000.0000;

   printf("\n\nXO_GEN_OSF_ADD_DRIFT_CYCLE\n");     

   status = xo_gen_osf_add_drift_cycle(&sat_id, 
                                       &model_id,
                                       &time_id, input_file_4,
                                       &drift_start_orbit,
                                       &drift_stop_orbit,
                                       &anx_long,
                                       &max_delta_alt,
                                       &drift_start_ph_inc,
                                       &drift_stop_ph_inc,
                                       output_dir,
                                       output_file_4,
				       file_class, &version_number,
				       fh_system,
				       ierr);

   CHECK_STATUS("xo_gen_osf_add_drift_cycle status", status)

   /*A different time_id will be used in following tests */
   status = xl_time_close(&time_id, ierr);
   CHECK_STATUS("xl_time_close",status);
  
END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-12
 *
 ******************************************************************************/
START_CHECK("Check XO_GEN_ROF (1) status is OK")
   
   sat_id = XL_SAT_CRYOSAT;
   /* calling GEN_ROF */
   time_mode = XO_SEL_ORBIT;
   start_orbit = 343;
   stop_orbit  = 344;

   osv_interval = 300;
   osv_precise  = XO_OSV_PRECISE_NO;

   ref_filetype = XO_REF_FILETYPE_OSF;
   rof_filetype = XO_REF_FILETYPE_ROF;
   strcpy(reference_file,output_file_1);

   strcpy(rof_filename,"");
   strcpy(output_directory,"./");

   printf("\n\nXO_GEN_ROF (1)\n");     

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   input_files[0] = reference_file;
   status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
   
   time_mode = XO_SEL_ORBIT;
   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref,
                       &start_time, &stop_time,
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise,
                       &ref_filetype, reference_file,
                       precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename, file_class, &version_number, fh_system,
                       ierr);

   CHECK_STATUS("xo_gen_rof status", status)

   status = xl_time_close(&time_id, ierr);
   CHECK_STATUS("xl_time_close",status);
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-13
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_ROF (2) status is OK")

   sat_id = XL_SAT_CRYOSAT;
   time_mode = XO_SEL_ORBIT;
   start_orbit = 1000;
   stop_orbit  = 1001;
   osv_precise  = XO_OSV_PRECISE_NO;

   ref_filetype = XO_REF_FILETYPE_POF;
   rof_filetype = XO_REF_FILETYPE_ROF;
   strcpy(reference_file,"../example/data/EARTH_EXPLORER_FPO");

   strcpy(rof_filename,"");
   strcpy(output_directory,"./");

   printf("\n\nXO_GEN_ROF (2)\n");     

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   input_files[0] = reference_file;
   status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
   
   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref, 
                       &start_time, &stop_time, 
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise,
                       &ref_filetype, reference_file, 
                       precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename,
                       file_class, &version_number, fh_system,
                       ierr);
   CHECK_STATUS("xo_gen_rof status", status)

   status = xl_time_close(&time_id, ierr);
   CHECK_STATUS("xl_time_close",status);
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-14
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_ROF (3) status is OK")
   sat_id=XO_SAT_CRYOSAT;
   time_mode = XO_SEL_TIME;
   time_ref = XO_TIME_UTC;

   start_time = -284.9951;
   stop_time  = -284.9895;

   osv_interval = 60;
   osv_precise  = XO_OSV_PRECISE_NO;

   ref_filetype = XO_REF_FILETYPE_ROF;
   rof_filetype = XO_REF_FILETYPE_ROF;
   strcpy(reference_file,"../example/data/EARTH_EXPLORER_FRO");

   strcpy(rof_filename,"");
   strcpy(output_directory,"./");

   printf("\n\nXO_GEN_ROF (3)\n");     

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   input_files[0] = reference_file;
   status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
   
   time_mode = XO_SEL_TIME;
   status = xo_gen_rof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref, 
                       &start_time, &stop_time, 
                       &start_orbit, &stop_orbit,
                       &osv_interval, &osv_precise,
                       &ref_filetype, reference_file, 
                       precise_conf_file,
                       &rof_filetype, output_directory,
                       rof_filename,
                       file_class, &version_number, fh_system,
                       ierr);
   CHECK_STATUS("xo_gen_rof status", status)

   status = xl_time_close(&time_id, ierr);
   CHECK_STATUS("xl_time_close",status);
END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-15
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_POF (1) status is OK")

   time_mode = XO_SEL_ORBIT;
   start_orbit = 13;
   stop_orbit  = 14;
   osv_location = 0.0;

   ref_filetype = XO_REF_FILETYPE_OSF;
   strcpy(reference_file,output_file_1);

   strcpy(pof_filename,"");
   strcpy(output_directory,"./");

   printf("\n\nXO_GEN_POF \n");     

   /* Initialise time_id with file so there are no conflicts in time correlations */
   time_model = XL_TIMEMOD_AUTO;
   n_files = 1;
   time_mode = XO_SEL_FILE;
   input_files[0] = reference_file;
   status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_mode,
                                   &time_ref, &time0, &time1, &orbit0, &orbit1,
                                   &val_time0, &val_time1, &time_id,
                                   tri_ierr );
   CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
   
   time_mode = XO_SEL_ORBIT;
   status = xo_gen_pof(&sat_id, &model_id, &time_id,
                       &time_mode, &time_ref, &start_time,
                       &stop_time, &start_orbit, &stop_orbit,
                       &osv_location, &ref_filetype,
                       reference_file, precise_conf_file,
                       &pof_filetype, output_directory, pof_filename,
                       file_class, &version_number, fh_system,
                       ierr);
   CHECK_STATUS("xo_gen_pof status", status)

  /* Close time reference */
  status = xl_time_close(&time_id, ierr);
  CHECK_STATUS("xl_time_close",status);

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-16
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_DNF (1) status is OK")

     /* Set input values */
     /* ---------------- */
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
     strcpy(output_directory,".");
     strcpy(control_file,"../example/data/CONTROL_FILE.xml");
     strcpy(reference_file,"../example/data/EARTH_EXPLORER_FRO_TO_DORIS_2000");
     /*output*/
     strcpy(doris_nav,"DORIS_NAVIGATOR_FILE_CRYOSAT.N1");
     strcpy(rof_file,"./EARTH_EXPLORER_FRO_FROM_DORIS_CRYO");
#else
     /*input*/
     strcpy(output_directory,".");
     strcpy(control_file,"..\\example\\data\\CONTROL_FILE.xml");
     strcpy(reference_file,"..\\example\\data\\EARTH_EXPLORER_FRO_TO_DORIS_2000");
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
     CHECK_STATUS("xl_time_ascii_to_processing status",status);

     printf("\n\nXO_GEN_DNF\n");     

     /* CREATE DNF FILE FROM ROF FILE */
     status = xo_gen_dnf(&sat_id, &model_id, &time_id, &time_mode, &time_ref, 
                         &start_time, &stop_time, &start_orbit, &stop_orbit,
                         &osv_interval, &osv_precise,
                         &ref_filetype, reference_file, control_file,
                         precise_conf_file,
                         &dnf_filetype, output_directory, doris_nav,
                         file_class, &version_number, fh_system, ierr);
     
     CHECK_STATUS("xo_gen_dnf status",status);

     /* Close time reference */
     xl_time_close(&time_id, ierr);

END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-17
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_OEF status is OK")

     printf("\n\nXO_GEN_OEF \n");     

     strcpy(oef_filename, "");

     status = xo_gen_oef(oef_filename, output_file_4, pof_filename,
                         file_class, &version_number, fh_system,
                         ierr);
     CHECK_STATUS("xo_gen_oef status", status);

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-18
 *
 ******************************************************************************/
START_CHECK ("Check XO_CHECK_OSF status is OK")

     tri_time[0]   =  0.0000000000000;          /* TAI time [days] */
     tri_time[1]   =  tri_time[0]+35.0/86400;   /* UTC time [days] (= TAI + 35.0 s) */
     tri_time[2]   =  tri_time[0]+35.8/86400;   /* UT1 time [days] (= TAI + 35.3 s) */
     tri_time[3]   =  tri_time[0]-19/86400;     /* GPS time [days] (= TAI - 19.0 s) */

     tri_orbit_num = 10;
     tri_anx_time  = 5245.123456;
     tri_orbit_duration = 6035.928144;

     /* Call xl_time_ref_init function */
     /* ------------------------------ */
     status= xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                              &tri_orbit_duration, &time_id, tri_ierr);

     printf("\n\nXO_CHECK_OSF \n");

     osf_file =output_file_2;
     sat_id = XL_SAT_CRYOSAT;

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
     CHECK_STATUS("xo_check_osf status", status);

     /* Close time reference */
     status = xl_time_close(&time_id, ierr);
     CHECK_STATUS("xl_time_close",status);
     
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-19
 *
 ******************************************************************************/
START_CHECK ("Check XO_CHECK_OEF status is OK")

     printf("\n\nXO_CHECK_OEF \n");

     sat_id = XL_SAT_CRYOSAT;

     check_oef_thr[0] = 1.;
     check_oef_thr[1] = 1.e-3;
     check_oef_thr[2] = 1.;
     check_oef_thr[3] = 5000.;
     check_oef_thr[4] = 1.e-5;
     check_oef_thr[5] = 1.;

     time_mode = XO_SEL_FILE;
     time_ref = XL_TIME_UTC;

     /* Initialise time_id with file so there are no conflicts in time correlations. */
     time_model = XL_TIMEMOD_OSF;
     n_files = 1;
     input_files[0] = oef_filename;
     status = xl_time_ref_init_file( &time_model, &n_files, input_files, &time_mode,
                                     &time_ref, &time0, &time1, &orbit0, &orbit1,
                                     &val_time0, &val_time1, &time_id,
                                     tri_ierr );
     CHECK_STATUS("EARTH EXPLORER xl_time_ref_init_file STATUS", status);
     
     status = xo_check_oef(&sat_id, &model_id, &time_id,
                           &time_mode, &time_ref,
                           &start_time, &stop_time,
                           &start_orbit, &stop_orbit,
                           oef_filename, check_oef_thr,
                           /*output*/
                           max_diffs, rms,
                           ierr);
     CHECK_STATUS("xo_check_oef status", status);

END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-20
 *
 ******************************************************************************/
START_CHECK ("Check XO_GEN_TLE status is OK")

     printf("\n\nXO_GEN_TLE \n");

#ifndef WINDOWS
   /*input*/
   strcpy(reference_file,"../example/data/EARTH_EXPLORER_FPO_18_OSV");
#else
   strcpy(reference_file,"..\\example\\data\\EARTH_EXPLORER_FPO_18_OSV");
#endif

   sat_id = XD_SAT_CRYOSAT;
   strcpy(tle_filename,"OUTPUT_TLE_FILE");
   fit_mode = XO_ONE_TLE_PER_OSV;
   time_mode = XO_SEL_FILE;
   time_ref = XO_TIME_UTC;
   
   status = xo_gen_tle(&sat_id, &fit_mode,
                       &time_mode, &time_ref, &start_time,
                       &stop_time, &start_orbit, &stop_orbit,
                       reference_file,
                       tle_filename,
                       ierr);
   CHECK_STATUS("xo_gen_tle status", status);

END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-21
 *
 ******************************************************************************/
START_CHECK ("Check XO_ORBIT_INIT_GEO status is OK")

   printf("\n\nXO_ORBIT_INIT_GEO \n");

   sat_id = XL_SAT_GENERIC_GEO; 
   geo_init_data.init_type = XO_GC_LONGITUDE_ONLY;
   geo_init_data.geo_orbit_info.geod_coord.gc_longitude = 21.4;
   geo_init_data.geo_orbit_info.geod_coord.gd_latitude  = 0.; /* Dummy */
   geo_init_data.geo_orbit_info.geod_coord.gd_altitude  = 0.; /* Dummy */
   
   status =  xo_orbit_init_geo(&sat_id, &model_id, &time_id,
                               &geo_init_data,
                               &val_time0, &val_time1, &orbit_id,
                               ierr);
   CHECK_STATUS("xo_orbit_init_geo status", status);

   status = xo_orbit_close(&orbit_id, ierr);

  CHECK_STATUS("xo_orbit_close",status);
  
   /* Close time reference */
  xl_time_close(&time_id, ierr);
  CHECK_STATUS("xl_time_close",status);
  
END_CHECK


/*******************************************************************************
 *
 * ---------
 * Test case xo_position_on_orbit_to_time validation
 * ---------
 *
 * Test number          : VT-22
 *
 ******************************************************************************/
START_CHECK ("Check XO_POSITION_ON_ORBIT_TO_TIME status is OK")

  printf("\n\nXO_POSITION_ON_ORBIT_TO_TIME \n");
  
  /* ---------------------- */
  /* START xl_time_ref_init */
  /* ---------------------- */
  
  tri_time[2]   = -2010.1788055555555;      /* UT1 time [days] (= TAI - 29.16 s) */
  tri_time[0]   = tri_time[2]+35.80/86400.; /* TAI time [days]                  */
  tri_time[1]   = tri_time[0]-35.00/86400.; /* UTC time [days] (= TAI - 35.00 s) */
  tri_time[3]   = tri_time[0]+19/86400.;    /* GPS time [days] (= TAI + 19.0 s) */
  
  tri_orbit_num = 10;               /* dummy */
  tri_anx_time  = 5245.123456;      /* dummy */
  tri_orbit_duration = 6035.928144; /* dummy */
  
  status = xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                            &tri_orbit_duration, &time_id, tri_ierr);
  CHECK_STATUS("xl_time_ref_init status", status);
  
  mode = XL_MODEL_DEFAULT;
  status = xl_model_init( &mode, models, &model_id, ierr );
  
  input_files[0] = file4;

  
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
  
  CHECK_STATUS("xo_orbit_init_file status", status);
  
  
  
  abs_orbit_number = 1001;
  angle_type       = XL_ANGLE_TYPE_TRUE_LAT_TOD;
  angle            = 13.961817;
  angle_rate       = 0.059176;
  angle_rate_rate  = 0.000000;
  deriv            = XL_DER_2ND;
    
  /* xo_osv_compute */
  propag_model = XO_PROPAG_MODEL_MEAN_KEPL;
  
  
  status = xo_position_on_orbit_to_time(&orbit_id, &abs_orbit_number, &angle_type,
                                        &angle, &angle_rate, &angle_rate_rate,
                                        &deriv, &time_ref,
                                        /* output */
                                        &time, pos, vel, acc,
                                        ierr);
  
  
  CHECK_STATUS("xo_position_on_orbit_to_time status", status);

  status = xo_orbit_close(&orbit_id, ierr);
  
  /* Close time reference */
  xl_time_close(&time_id, ierr);
  CHECK_STATUS("xl_time_close",status);
  
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case xo_orbit_data_filter validation
 * ---------
 *
 * Test number          : VT-23
 *
 ******************************************************************************/
START_CHECK ("Check XO_ORBIT_DATA_FILTER status is OK")

  printf("\n\nXO_ORBIT_DATA_FILTER\n");     
  
  n_files = 1;
  
  strcpy(orbit_filename, file5);
  
  /* ------------------------- */
  /* ----- orbit_data_in ----- */
  
  extend_osv_flag  = XL_FALSE;
  reading_osv_flag = XL_TRUE;
  time_init_mode   = XL_SEL_FILE;
  time_ref         = XL_TIME_UTC;
  
  status = xd_read_orbit_file (orbit_filename, &extend_osv_flag, 
                               &time_init_mode, &time_ref,
                               &range0, &range1, &reading_osv_flag, 
                               &(orbit_file[0]),
                               ierr);
  CHECK_STATUS( "xd_read_orbit_file status", status);
  
  
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
  CHECK_STATUS("xo_orbit_data_filter status", status);
  
  status = xo_orbit_id_init_data_close(&orbit_data_out, ierr);
  CHECK_STATUS("xo_orbit_id_init_data_close status", status);
  
  xd_free_orbit_file(&orbit_file[0]);
  
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case xo_orbit_id_change validation
 * ---------
 *
 * Test number          : VT-24
 *
 ******************************************************************************/
START_CHECK ("Check XO_ORBIT_ID_CHANGE status is OK")

  printf("\n\nXO_ORBIT_ID_CHANGE\n");     

/*
TEST 1 - Call xo_orbit_init_file with OSF and POF
TEST 2 - Call xo_orbit_id_change using OSF change mode
TEST 3 - Call xo_orbit_id_change using Time/Orbit change mode
TEST 4 - Call xo_orbit_id_init with OSF change mode
TEST 5 - Call xo_orbit_id_init with Time/Orbit change mode
*/


/*===================================================================================================*/
printf("\n TEST 1 - Call xo_orbit_init_file with OSF and POF\n");
/*===================================================================================================*/
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
  CHECK_STATUS("STATUS of xl_time_ref_init_file time_id_pof     (POF)", local_status);

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
  CHECK_STATUS("STATUS of xo_orbit_init_file    orbit_id1   (OSF+POF)", local_status);
  
  /* 1.3. Clean */
  /* ---------- */
  local_status = xo_orbit_close(&orbit_id1, xo_ierr);
  CHECK_STATUS("STATUS of orbit_close           orbit_id1   (OSF+POF)", local_status);
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  CHECK_STATUS("STATUS of time_close            time_id_pof     (POF)", local_status);


/*===================================================================================================*/
printf("\n TEST 2 - Call xo_orbit_id_change using OSF change mode\n");
/*===================================================================================================*/
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
  CHECK_STATUS("STATUS of xl_time_ref_init_file time_id_pof     (POF)", local_status);
  
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
  CHECK_STATUS("STATUS of xo_orbit_init_file    orbit_id2       (POF)", local_status);
  
  /* 2.3. Read OSF File */
  /* ------------------ */
  input_files[0] = osf_file1;
  local_status   = xd_read_osf (input_files[0], &osf_file_527, xd_ierr);
  CHECK_STATUS("STATUS of xd_read_osf                                ", local_status);
  
  /* 2.4. call xo_orbit_id_change with OSF MODE */
  /* ------------------------------------------ */
  time_ref = XO_TIME_UT1;
  
  change_data.change_mode     = XO_ORBIT_ID_CHANGE_OSF;
  change_data.eocfi_file.file_type = XD_OSF_FILE;
  change_data.eocfi_file.eocfi_file.osf_file  = osf_file_527;
  change_data.change_time_ref = time_ref;
  change_data.change_time     = 0.;
  change_data.change_orbit    = 0;
  
  local_status = xo_orbit_id_change(&orbit_id2,
                                    &change_data,
                                    xo_ierr);
  CHECK_STATUS("STATUS of xo_orbit_id_change                    (OSF)", local_status);
  /* 2.5. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  CHECK_STATUS("STATUS of xd_free_osf                                ", local_status)
  local_status = xo_orbit_close(&orbit_id2, xo_ierr);
  CHECK_STATUS("STATUS of orbit_close orbit_id2            (Modified)", local_status)
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  CHECK_STATUS("STATUS of time_close time_id_pof                (POF)", local_status);

/*===================================================================================================*/
printf("\n TEST 3 - Call xo_orbit_id_change using Time/Orbit change mode\n");
/*===================================================================================================*/
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
  CHECK_STATUS("STATUS of xl_time_ref_init_file time_id_pof     (POF)", local_status);
  
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
  CHECK_STATUS("STATUS of xo_orbit_init_file    orbit_id3       (POF)", local_status);
  
  /* 3.3. call xo_orbit_id_change with OSF MODE */
  /* ------------------------------------------ */
  change_data.change_mode  = XO_ORBIT_ID_CHANGE_TIME_ORBIT;
  change_data.change_time_ref = time_ref;
  change_data.change_time  = 1642.821194;
  change_data.change_orbit = 25876;
  local_status = xo_orbit_id_change(&orbit_id3,
                                    &change_data,
                                    xo_ierr);
  CHECK_STATUS("STATUS of xo_orbit_id_change             (TIME_ORBIT)", local_status);
  
  
  /* 3.4. Clean */
  /* ---------- */
  local_status = xo_orbit_close(&orbit_id3, xo_ierr);
  CHECK_STATUS("STATUS of orbit_close orbit_id3            (Modified)", local_status)
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  CHECK_STATUS("STATUS of time_close time_id_pof                (POF)", local_status);

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
  CHECK_STATUS("STATUS of xl_time_ref_init_file time_id_pof     (POF)", local_status);
  
  /* 4.2. Read OSF */
  /* ------------- */
  input_files[0] = osf_file1;
  local_status   = xd_read_osf (input_files[0], &osf_file_527, xd_ierr);
  CHECK_STATUS("STATUS of xd_read_osf", local_status);
  
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
  CHECK_STATUS( "STATUS of xd_read_orbit_file", local_status);
  
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
  orbit_id_init_data_527.change_data.eocfi_file.eocfi_file.osf_file = osf_file_527;
  orbit_id_init_data_527.change_data.change_time_ref = time_ref;
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
  CHECK_STATUS("STATUS of xo_orbit_id_init orbit_id2        (POF+OSF)", local_status);

  /* 4.5. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  CHECK_STATUS("STATUS of xd_free_osf                                ", local_status)
  xd_free_orbit_file (&orbit_file_527);
  CHECK_STATUS("STATUS of xd_free_orbit_file                         ", local_status)
  local_status = xo_orbit_close(&orbit_id2, xo_ierr);
  CHECK_STATUS("STATUS of orbit_close orbit_id2            (Modified)", local_status)
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  CHECK_STATUS("STATUS of time_close time_id_pof                (POF)", local_status);


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
  CHECK_STATUS("STATUS of xl_time_ref_init_file time_id_pof     (POF)", local_status);
  
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
  CHECK_STATUS( "STATUS of xd_read_orbit_file", local_status);
  
  /* 5.3. Call xo_orbit_id_init (Time/Orbit Change Mode) */
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
  orbit_id_init_data_527.change_data.change_time_ref = XL_TIME_UT1;
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
  CHECK_STATUS("STATUS of xo_orbit_id_init orbit_id3 (POF+Time/Orbit)", local_status);

  /* 5.4. Clean */
  /* ---------- */
  xd_free_osf (&osf_file_527);
  CHECK_STATUS("STATUS of xd_free_osf                                ", local_status)
  xd_free_orbit_file (&orbit_file_527);
  CHECK_STATUS("STATUS of xd_free_orbit_file                         ", local_status)
  local_status = xo_orbit_close(&orbit_id3, xo_ierr);
  CHECK_STATUS("STATUS of orbit_close orbit_id3            (Modified)", local_status)
  local_status = xl_time_close(&time_id_pof, xo_ierr);
  CHECK_STATUS("STATUS of time_close time_id_pof                (POF)", local_status);
  
END_CHECK

printf("\nEOCFI_ORBIT VALIDATION COMPLETED SUCCESSFULLY\n");

END_VALIDATION

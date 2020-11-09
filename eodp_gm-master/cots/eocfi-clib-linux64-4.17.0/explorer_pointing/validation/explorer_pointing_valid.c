 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Test level  : VALIDATION
 *
 * Module      : explorer_pointing_valid.c
 * Purpose     : It runs validation tests of EXPLORER_POINTING
 *
 * Reference   : Based on Envisat Mission CFI Software
 *
 * History:      +--------------------------------------------------------------------------------+
 *               | Version |  Date  |       Name        | Change                                  |
 *               |--------------------------------------------------------------------------------|
 *               |    1.0  |19/07/02| DEIMOS Space S.L. | First version from                      |
 *               |         |        |                   | Envisat CFI                             |
 *               +--------------------------------------------------------------------------------+
 *               |    2.0  |29/11/02| DEIMOS Space S.L. | Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |    2.1  |13/05/03| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | MAC OS Version                          |
 *               +--------------------------------------------------------------------------------+
 *               |    2.2  |13/08/03| DEIMOS Space S.L. | Pre-release                             |
 *               +--------------------------------------------------------------------------------+
 *               |    2.2  |30/09/03| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New Functions:                          |
 *               |         |        |                   | xp_target_extra_target_to_sun           |
 *               |         |        |                   | xp_target_extra_ef_target               |
 *               |         |        |                   | xp_target_extra_aux                     |
 *               |         |        |                   | xp_converter                            |
 *               +--------------------------------------------------------------------------------+
 *               |   2.2.2 |26/04/04| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | Added TERRASAR S/C                      |
 *               +--------------------------------------------------------------------------------+
 *               |    3.0  |21/07/04| DEIMOS Space S.L. | New Interfaces                          |
 *               |         |        |                   |                                         |
 *               +--------------------------------------------------------------------------------+
 *               |    3.1  |13/10/04| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Attitude models                      |
 *               |         |        |                   |  + Multitarget functions                |
 *               +--------------------------------------------------------------------------------+
 *               |    3.2  |15/11/04| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + DEM model                            |
 *               +--------------------------------------------------------------------------------+
 *               |    3.3  |11/07/05| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   | + xp_target_travel_time                 |
 *               |         |        |                   | + Attitude models (Cryosat YSM,         |
 *               |         |        |                   |   ADM model)                            |
 *               |         |        |                   | + New attitude files for                |
 *               |         |        |                   |   initialisation                        |
 *               |         |        |                   | + Id. Accessors                         |
 *               |         |        |                   | + ENVISAT support removed               |
 *               +--------------------------------------------------------------------------------+
 *               |    3.4  |18/11/05| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   | + New Attitude model for ADM            |
 *               |         |        |                   | + Routine xp_dem_compute                |
 *               |         |        |                   | + Interfaces for specular               |
 *               |         |        |                   |   reflection target routines            |
 *               |         |        |                   | + New axis attitude computation         |
 *               +--------------------------------------------------------------------------------+
 *               |    3.5  |26/05/06| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Thread safe library                  |
 *               |         |        |                   |  + C99 compliant                        |
 *               |         |        |                   |  + Optimized libray                     |
 *               |         |        |                   |  + 64-Bits library for MACOS,           |
 *               |         |        |                   |    LINUX and SOLARIS                    |
 *               |         |        |                   |  + Aberration correction for CryoSat    |
 *               |         |        |                   |    attitude determination               |
 *               +--------------------------------------------------------------------------------+
 *               |    3.6  |24/11/06| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + xp_target_extra_specular_reflection  |
 *               |         |        |                   |  + xp_target_reflected                  |
 *               +--------------------------------------------------------------------------------+
 *               |    3.7  |13/07/07| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + expcfi_check_libs                    |
 *               |         |        |                   |  + library version for Mac OS X         |
 *               |         |        |                   |    on Intel (32 and 64 bits)            |
 *               +--------------------------------------------------------------------------------+
 *               |  3.7.2  |31/07/08| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for misaligment or           |
 *               |         |        |                   |    configuration matrices at attitude   |
 *               |         |        |                   |    frame level                          |
 *               |         |        |                   |  + Azimuth/elevation definitions        |
 *               +--------------------------------------------------------------------------------+
 *               |    4.0  |19/01/09| DEIMOS Space S.L. | Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |    4.1  |07/05/10| DEIMOS Space S.L. | Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + DEM GETASSEv2 supported              |
 *               |         |        |                   |  + Sentinel-1 att model (roll steering) |
 *               +--------------------------------------------------------------------------------+
 *               |    4.2  |31/01/11| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + New DEM model: ACE2 9secs            |
 *               +--------------------------------------------------------------------------------+
 *               |    4.3  |06/02/12| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Raytracing model in target fucntions |
 *               |         |        |                   |    determined by input atmos_id         |
 *               |         |        |                   |  + New attitude model for SENTINEL2     |
 *               |         |        |                   |    (XP_MODEL_SENTINEL2)                 |
 *               +--------------------------------------------------------------------------------+
 *               |    4.4  |05/07/12| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + GEO satellites:                      |
 *               |         |        |                   |    - New Yaw flip attitude              |
 *               |         |        |                   |    - xp_target_sc                       |
 *               |         |        |                   |  + xp_target_list_inter                 |
 *               |         |        |                   |  + DEM computation using memory cache   |
 *               +--------------------------------------------------------------------------------+
 *               |    4.5  |01/03/13| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + New functions xp_target_list_extra   |
 *               |         |        |                   |    to compute extra results for targets |
 *               |         |        |                   |    computed with xp_target_list_inter   |
 *               |         |        |                   |  + New DEM algorithm of maximum heights |
 *               +--------------------------------------------------------------------------------+
 *               |    4.6  |03/10/13| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + New function xp_attitude_define      |
 *               |         |        |                   |  + Internal improvements to improve     |
 *               |         |        |                   |    runtime performance in DEM           |
 *               |         |        |                   |    computations                         |
 *               +--------------------------------------------------------------------------------+
 *               |    4.7  |28/03/14| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |    4.8  |29/10/14| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for Earth Fixed input in     |
 *               |         |        |                   |    satellite nominal attitude           |
 *               |         |        |                   |    initialization with harmonics.       |
 *               |         |        |                   |  + Support for DEM GETASSE v3.0         |
 *               |         |        |                   |  + Support for GDEM v2                  |
 *               +--------------------------------------------------------------------------------+
 *               |    4.9  |23/04/15| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |  4.9.1  |05/06/15| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |   4.10  |29/10/15| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for DEM ACE2 30 secs         |
 *               |         |        |                   |  + Target functions: possibility of     |
 *               |         |        |                   |    considering light travel time in     |
 *               |         |        |                   |    target computation                   |
 *               |         |        |                   |  + Run-time improvements in target      |
 *               |         |        |                   |    functions                            |
 *               +--------------------------------------------------------------------------------+
 *               |   4.11  |15/04/16| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for DEM ACE2 3 secs          |
 *               |         |        |                   |  + New functions xp_gen_attiude_data    |
 *               |         |        |                   |    and xp_gen_attitude_file             |
 *               +--------------------------------------------------------------------------------+
 *               |   4.12  |03/11/16| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |   4.13  |05/04/17| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |   4.14  |16/11/17| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for MetOp-SG attitude law    |
 *               |         |        |                   |  + New function xp_free_target_id_data  |
 *               +--------------------------------------------------------------------------------+
 *               |   4.15  |20/04/18| DEIMOS Space S.L.U| Maintenance release                     |
 *               +--------------------------------------------------------------------------------+
 *               |   4.16  |09/11/18| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + Support for DEM ACE2 5 minutes       |
 *               +--------------------------------------------------------------------------------+
 *               |   4.17  |10/05/19| DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |        |                   | New features:                           |
 *               |         |        |                   |  + DEM configurable raster              |
 *               |         |        |                   |  + functions xp_dem_get_cell_value and  |
 *               |         |        |                   |    xp_dem_get_cell_geod                 |
 *               +--------------------------------------------------------------------------------+
 *
 *****************************************************************************/
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <explorer_orbit.h>
#include <explorer_pointing.h>
/* Macro definition */
/* ---------------- */

#define MAX_CONDITION                   1000        /* Maximum number of checks per test case */

#define START_VALIDATION                int main(int argc, char *argv[]){ \
                                        double di,th,ta,tb,sinta,costa,sintb,costb; \
                                        double di_l,di_r,th_l,th_r; \
                                        int i,j; \
                                        int checks; \
                                        XL_Boolean condition[MAX_CONDITION]; \
                                        XL_Boolean result;

#define START_CHECK(msg)                printf(" *** %s\n",msg); \
                                        checks = 0;

#define END_CHECK                       result = XL_TRUE; \
                                        for (i = 0 ; i < checks ; i++) \
                                          { \
                                          if (condition[i] == XL_FALSE) \
                                            { \
                                            result = XL_FALSE; \
                                            break; \
                                            } \
                                          } \
                                        if (result == XL_TRUE) \
                                          { \
                                          printf(" *** RESULT = PASS ***\n\n"); \
                                          } \
                                        else \
                                           { \
                                          printf(" *** RESULT = FAIL ***\n\n"); \
                                          }

#define CHECK_STATUS(msg,stat)                if (stat < XP_OK ) { \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        } \
                                        checks++;


#define CHECK_PAR(msg,p,p0,dp)                if((di=fabs(p-p0)) <= (th=dp)){ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Threshold  : %g\n",th); \
                                        printf("\t\t Difference : %g\n",di); \
                                        checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)        for(i=im;i<=iM;++i){ \
                                          CHECK_PAR(msg,v[i],v0[i],dp); \
                                        }


#define END_VALIDATION                        return(0); \
                                        }

/* Nominal validation values */
/* ------------------------- */

double mjdp[] = { -2456.0 , 0.3 };
double pos[] = { 4859964.138 , -5265612.059 , 0.002 };
double vel[] = { -1203.303801, -1098.845511 , 7377.224410 };
double acc[] = { 0.0 , 0.0 , 0.0 };
double att[] = { 0.1 , -0.1 , 0.15 };
double datt[] = { 0.0 , 0.0 , 0.0 };

double longdrs = 15.4;

double mjdrs[] = { -2456.0 , 0.3};
double posdrs[] = { 40652295. , 11197507.0 , -844.0 };
double veldrs[] = { 0.06 , -0.22 , 0.078 };
double sta[] = {0.,0.,0.,0.};

/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Validation for EXPLORER_POINTING                                          */
/*                                                                           */
/* ------------------------------------------------------------------------- */

START_VALIDATION

/* Local variables definition */
/* -------------------------- */

   /* Error handling and message visualization */
   long   status;               /* (Normal) status flag */
   long   n;				                  /* Number of error messages */
   long   func_id;                            /* CFI function ID */
   char   msg[XL_MAX_COD][XL_MAX_STR];        /* Error messages vector */
   long   xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];  /* Error vector for DH functions */
   long   lib_err[XL_ERR_VECTOR_MAX_LENGTH];  /* Error vector for LIB functions */
   long   poi_err[XP_ERR_VECTOR_MAX_LENGTH];  /* Error vector for POINTING functions */
   long   ierr[XP_ERR_VECTOR_MAX_LENGTH];  /* Error vector for POINTING functions */

   /* IDs */
   xl_time_id  time_id  = {NULL};
   xl_model_id model_id = {NULL};
   xo_orbit_id orbit_id = {NULL};
      
   xp_sat_nom_trans_id sat_nom_trans_id = {NULL};
   xp_sat_nom_trans_id sat_nom_trans_id1= {NULL};
   xp_sat_nom_trans_id sat_nom_trans_id2= {NULL};
   xp_sat_trans_id     sat_trans_id     = {NULL};
   xp_instr_trans_id   instr_trans_id   = {NULL};

   xp_attitude_id      attitude_id      = {NULL};
   xp_attitude_id      attitude_id_2    = {NULL};
 
   xp_atmos_id         atmos_id         = {NULL};
   xp_dem_id           dem_id           = {NULL};
   xp_target_id        target_id        = {NULL};

   /* Accessors */
   xp_param_model_str    param_model;
   xp_angle_model_str    angle_model;
   xp_atmos_id_data      atmos_data;
   xp_attitude_id_data   attitude_data;
   xp_target_id_data     target_data;

   /* xl_time_ref_init */
   long   tri_sat_id, tri_orbit_num;
   double tri_anx_time, tri_orbit_duration;
   double tri_time[4];

   /* xl_time_ref_init_file */
   char   **trif_time_file;

   /* xl_time_ref_init_close */

   long   sat_id, sat_id2;

   /* xo_orbit_init_file */
   long orbit_mode;
   char *input_files[1];
   char osf[500]="";
   double val_time0, val_time1;
   long   n_files;
   long   time_init_mode;
   double time0,  time1;
   long   orbit0, orbit1;

   /* xp_sat_att_init */
   double att[3];
   long model_enum;
   double model_param[XP_NUM_MODEL_PARAM];

   /* xp_attitude */
   long   target_frame;
   long data_type;
   long source_ref_type;
   long source_ref;
   double time_step;
   char output_dir[500] = "";
   char file_class[] = "TEST";
   long version_number = 1;
   char fh_system[] = ""; 
   char out_att_file[500] = "";
  
   xo_time_interval time_interval;
   xd_att_rec  att_rec;
   xd_att_file quat_file;
   xp_attitude_def  att_def;

   /* xp_atmos_init */
   long   atmos_mode, atmos_model;
   char   atmos_file[XL_MAX_STR];

   /* xp_target */
   long num_user_target;
   long num_los_target;

   /* xp_target_inter */
   long   time_ref, deriv, inter_flag, iray;
   double pos[3], vel[3], acc[3];
   double time, los_az, los_el, geod_alt, los_az_rate, los_el_rate, freq;

   /* xp_target_ground_range */
   double distance;

   /* xp_target_incidence_angle */
   double inc_angle;

   /* xp_target_range */
   double range, range_rate;

   /* xp_target_range_rate */
   double ef_range_rate, ef_range_rate_rate;

   /* xp_target_star */
   double star_ra, star_dec, star_ra_rate, star_dec_rate;

   /* xp_target_station */
   double geoc_long, geod_lat, min_link_el;

   /* xp_target_extra_vector */
   long target_type;
   long target_number; 
   double vector_results[XP_SIZE_TARGET_RESULT_VECTOR];
   double vector_results_rate[XP_SIZE_TARGET_RESULT_VECTOR];
   double vector_results_rate_rate[XP_SIZE_TARGET_RESULT_VECTOR];
   double vector_results2[XP_SIZE_TARGET_RESULT_VECTOR];
   double vector_results_rate2[XP_SIZE_TARGET_RESULT_VECTOR];
   double vector_results_rate_rate2[XP_SIZE_TARGET_RESULT_VECTOR];

   /* xp_target_extra_main */
   long   choice;
   double main_results[XP_SIZE_TARGET_RESULT_MAIN]; 
   double main_results_rate[XP_SIZE_TARGET_RESULT_MAIN];
   double main_results_rate_rate[XP_SIZE_TARGET_RESULT_MAIN];

   /* xp_target_extra_target_aux */
   double aux_results[XP_SIZE_TARGET_RESULT_AUX];
   double aux_results_rate[XP_SIZE_TARGET_RESULT_AUX];
   double aux_results_rate_rate[XP_SIZE_TARGET_RESULT_AUX];
                         
   /* xp_target_extra_target_to_sun */
   double sun_results[XP_SIZE_SUN_RESULT];
   double sun_results_rate[XP_SIZE_SUN_RESULT];
   double sun_results_rate_rate[XP_SIZE_SUN_RESULT];

   /* xp_target_extra_target_to_moon */
   double moon_results[XP_SIZE_MOON_RESULT];
   double moon_results_rate[XP_SIZE_MOON_RESULT];
   double moon_results_rate_rate[XP_SIZE_MOON_RESULT];

   /* xp_target_extra_ef_target */
   double ef_target_results_rate[XP_SIZE_EF_TARGET_RESULT];
   double ef_target_results_rate_rate[XP_SIZE_EF_TARGET_RESULT];

   /* xp_converter */
   char atm_var[200];
   int put;

   /* xp_change_frame */
   int cf_i;
   long cf_mode;
   long frame_flag_input;
   long frame_flag_output;
   long frame_id_input;
   long frame_id_output;
   double vec_input[3], vec_rate_input[3], vec_rate_rate_input[3];
   double vec_output[3], vec_rate_output[3], vec_rate_rate_output[3];
   double vec_aux[3], vec_rate_aux[3], vec_rate_rate_aux[3];
   long cf_err[XP_NUM_ERR_CHANGE_FRAME];

   char **lut_names_aux2;
   double target_out_pred[14], target_out_lut[14];
   long instrument_id;

   xp_instrument_data inst_data;
   xp_target_output target_num;
   
   xp_target_extra_vector_results_list             vector_list;
   xp_target_extra_main_results_list               main_list;
   xp_target_extra_aux_results_list                aux_list;
   xp_target_extra_ef_target_results_list          ef_target_list;
   xp_target_extra_spec_reflec_target_results_list spec_reflec_list;
   xp_target_extra_moon_target_results_list        moon_list;
   xp_target_extra_sun_target_results_list         sun_list;
   
   double defl_north, defl_east;
   
   char attitude_definition_aocs_file[XD_MAX_STR];
   xd_attitude_definition_data att_file;
   
   /* Set error handling mode (either Silent or Verbose) */
   /* -------------------------------------------------- */

   xp_silent();     /* Set error handling mode to SILENT */
/* xp_verbose();*/    /* Set error handling mode to VERBOSE */


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : Initialization
 *
 ****************************************************************************************/

START_CHECK("Initialization")

  /******************************************************************************/
  /* Initializing Time Reference                                                */
  /******************************************************************************/

  /* Set input values */
  /* ---------------- */
  tri_sat_id    = XP_SAT_ENVISAT;
  tri_time[0]   = -1100.1000000000000;   /* TAI time [days] */
  tri_time[1]   = -1100.0995949074074;   /* UTC time [days] (= TAI + 35.0 s) */
  tri_time[2]   = -1100.0995914351852;   /* UT1 time [days] (= TAI + 35.3 s) */
  tri_time[3]   = -1100.099780092;       /* GPS time [days] (= TAI + 19.0 s) */
  tri_orbit_num = 10;
  tri_anx_time  = 5245.123456;
  tri_orbit_duration = 6035.928144;

  /* Call xl_time_ref_init function */
  status = xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                            &tri_orbit_duration, &time_id, lib_err);

  CHECK_STATUS("xl_time_ref_init", status)

  /****************************************************************************/
  /* Oribt  initialization                                                    */
  /****************************************************************************/
  printf("\n\n\nXO_ORBIT_INIT_FILE\n");

#ifdef XL_WINDOWS
  strcpy(osf, "..\\example\\data\\AE__MPL_ORBSCT_20071001T180002_99999999T999999_0000.EEF");
#else
  strcpy(osf, "../example/data/AE__MPL_ORBSCT_20071001T180002_99999999T999999_0000.EEF");
#endif

  orbit_mode     = XO_ORBIT_INIT_AUTO;
  n_files        = 1;
  input_files[0] = osf;
  
  time_init_mode = XO_SEL_FILE;
  time_ref       = XL_TIME_UTC;
  sat_id         = XL_SAT_GENERIC;
  status = xo_orbit_init_file(&sat_id, &model_id, &time_id,
                              &orbit_mode, &n_files, input_files,
                              &time_init_mode, &time_ref,
                              &time0, &time1, &orbit0, &orbit1,
                              &val_time0, &val_time1, &orbit_id,
                              ierr);
  if (status != XL_OK)
  {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, ierr, &n, msg);
     xo_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }
  else
  {
     printf("Orbit correctly initialized\n");
  }

  /******************************************************************************/
  /* Satellite Nominal Att and Satellite Att ref. frames init                   */
  /******************************************************************************/

  /* AOCS user and MISP ANGLE */
  model_enum       = XP_MODEL_ENVISAT;
  model_param[0]   =  -0.1671;
  model_param[1]   =   0.0501;
  model_param[2]   =   3.9130;

  att[0]= 0.1;
  att[1]= 0.2;
  att[2]=-0.3;

  /* Call xp_sat_nominal_att_init_model function */
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         /* output */
                                         &sat_nom_trans_id, ierr);

  CHECK_STATUS("xp_sat_nominal_att_init_model", status);

  /* Check accessor functions */
  status = xp_sat_nominal_att_init_status(&sat_nom_trans_id);
  CHECK_STATUS("xp_sat_nominal_att_init_status", status)

  sat_id = xp_sat_nominal_att_get_sat_id(&sat_nom_trans_id);

  status = xp_sat_nominal_att_get_param(&sat_nom_trans_id, &param_model);
  CHECK_STATUS("xp_sat_nominal_att_get_param", status)

  status = xp_sat_nominal_att_set_param(&sat_nom_trans_id, &param_model);
  CHECK_STATUS("xp_sat_nominal_att_set_param", status)


  /* Call xp_sat_att_angle_init  function */
  status = xp_sat_att_angle_init(att, &sat_trans_id, ierr); 
  CHECK_STATUS("xp_sat_att_angle_init", status)

  /* Check accessor functions */
  status = xp_sat_att_init_status(&sat_trans_id);
  CHECK_STATUS("xp_sat_att_init_status", status)

  sat_id = xp_sat_att_get_sat_id(&sat_trans_id);

  status = xp_sat_att_get_angles(&sat_trans_id, &angle_model);
  CHECK_STATUS("xp_sat_att_get_angles", status)

  status = xp_sat_att_set_angles(&sat_trans_id, &angle_model);
  CHECK_STATUS("xp_sat_att_set_angles", status)


  /******************************************************************************/
  /* Initializing Atmospheric Model                                             */
  /******************************************************************************/

  atmos_mode = XP_LUT_INIT;
  atmos_model = 0; /*dummy*/
  strcpy (atmos_file, "../example/data/xp_atmo_converter_coefs.out");

  /* Call xp_atmos_init function */
  status = xp_atmos_init(&atmos_mode, &atmos_model, atmos_file,
                         &atmos_id, ierr);

  CHECK_STATUS("xp_atmos_init", status);

 /* Check accessor functions */
  status = xp_atmos_init_status(&atmos_id);
  CHECK_STATUS("xp_sat_att_init_status", status)

  sat_id = xp_atmos_get_sat_id(&atmos_id);

  status = xp_atmos_get_id_data(&atmos_id, &atmos_data);
  CHECK_STATUS("xp_atmos_get_id_data", status);

  status = xp_atmos_close(&atmos_id, ierr);
  CHECK_STATUS("xl_atmos_close", status);

END_CHECK

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
   if (status != XP_OK)
   {
     printf("Library incompatibility.\n");
     CHECK_STATUS("Compatibility test (expcfi_check_libs)", status);
   }

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-01
 *
 ****************************************************************************************/

START_CHECK("VT-01: xp_target_inter")

  /* Set input values */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  time_ref      = XL_TIME_UTC;
  inter_flag    = XP_INTER_1ST;
  deriv         = XL_NO_DER;
  time          = 255.3456;
  pos[0]        =  6997887.57;
  pos[1]        = -1536046.83;
  pos[2]        =    99534.18;
  vel[0]        =     -240.99;
  vel[1]        =    -1616.85;
  vel[2]        =    -7376.65;
  acc[0]        =       -7.79104;
  acc[1]        =        1.69353;
  acc[2]        =       -0.10826;
  los_az        =       50.0;
  los_el        =       85.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  los_el_rate   =        1.0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_attitude_init & attitude compute function */
  /* ------------------------------------------------- */
  target_frame = XP_SAT_ATT;
  status = xp_attitude_init (&attitude_id, ierr);
  CHECK_STATUS("xp_attitude_init", status);

  status = xp_attitude_compute(&model_id, &time_id,
                               &sat_nom_trans_id,
                               &sat_trans_id,
                               &instr_trans_id,
                               &attitude_id,
                               &time_ref, &time,
                               pos, vel, acc, 
                               &target_frame,
                               /* output */
                               ierr);
  CHECK_STATUS("xp_attitude_compute", status);

  /* Check accessor functions */
  status = xp_attitude_init_status(&attitude_id);
  CHECK_STATUS("xp_sat_att_init_status", status)

  sat_id = xp_attitude_get_sat_id(&attitude_id);
  printf("sat_id = %ld\n", sat_id);

  status = xp_attitude_get_id_data(&attitude_id, &attitude_data);
  CHECK_STATUS("xp_attitude_get_id_data", status)

  status = xp_attitude_set_id_data(&attitude_id, &attitude_data);
  CHECK_STATUS("xp_attitude_get_id_data", status)


  /* Call xp_target_inter function */
  /* ----------------------------- */

  sat_id        = XP_SAT_ENVISAT;

  status = xp_target_inter(&sat_id, &attitude_id,
                           &atmos_id, &dem_id,
                           &deriv, &inter_flag, &los_az, &los_el,
                           &geod_alt, &los_az_rate, &los_el_rate,
                           &iray, &freq,
                           /* output */
                           &num_user_target, &num_los_target,
                           &target_id,
                           ierr);

  CHECK_STATUS("xp_target_inter", status);

  /* Check accessor functions */
  status = xp_target_status(&target_id);
  CHECK_STATUS("xp_target_init_status", status)

  sat_id = xp_target_get_sat_id(&target_id);
  printf("sat_id = %ld\n", sat_id);

  status = xp_target_get_id_data(&target_id, &target_data);
  CHECK_STATUS("xp_target_get_id_data", status)

  if (target_data.user.target != NULL)
    free(target_data.user.target);

  if (target_data.los.target != NULL)
   free(target_data.los.target);

  if (target_data.earth.target != NULL)
    free(target_data.earth.target);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-02
 *
 ****************************************************************************************/

START_CHECK("VT-02: xp_target_ground_range")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  los_az        =       20.0;
  los_el        =       80.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  los_el_rate   =        1.0;
  distance      =     1000.0;

  /* Call xp_target_ground_range function */
  /* ------------------------------------ */
  status = xp_target_ground_range(&sat_id, &attitude_id, &dem_id,
                                  &deriv, &los_az,
                                  &los_el, &geod_alt, &distance, &los_az_rate, &los_el_rate,
                                  /* output */
                                  &num_user_target, &num_los_target,
                                  &target_id,
                                  ierr);

  CHECK_STATUS("xp_target_ground_range", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-03
 *
 ****************************************************************************************/

START_CHECK("VT-03: xp_target_incidence_angle")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  inc_angle     =       40.0;

  /* Call xp_target_incidence_angle function */
  /* --------------------------------------- */
  status = xp_target_incidence_angle(&sat_id, &attitude_id, &dem_id,
                                     &deriv, &los_az, &inc_angle, &geod_alt, &los_az_rate,
                                     /* output */
                                     &num_user_target, &num_los_target,
                                     &target_id,
                                     ierr);

  CHECK_STATUS("xp_target_incidence_angle", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-04
 *
 ****************************************************************************************/

START_CHECK("VT-04: xp_target_range")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  range         =   900000.0;
  range_rate    =       40.0;

  /* Call xp_target_range function */
  /* ----------------------------- */
  status = xp_target_range(&sat_id, &attitude_id, &dem_id,
                           &deriv, &los_az,
                           &range, &geod_alt, &los_az_rate, &range_rate,
                           /* output */
                           &num_user_target, &num_los_target,
                           &target_id,
                           ierr);

  CHECK_STATUS("xp_target_range", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-05
 *
 ****************************************************************************************/

START_CHECK("VT-05: xp_target_range_rate")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  geod_alt      =      100.0;
  range         =   900000.0;
  range_rate    =       40.0;
  ef_range_rate =       40.0;
  ef_range_rate_rate =   0.0;

  /* Call xp_target_range_rate function */
  /* ---------------------------------- */
  status = xp_target_range_rate(&sat_id, &attitude_id, &dem_id,
                                &deriv, &ef_range_rate,
                                &range, &geod_alt, &ef_range_rate_rate, &range_rate,
                                /* output */
                                &num_user_target, &num_los_target,
                                &target_id,
                                ierr);

  CHECK_STATUS("xp_target_range_rate", status)


END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-06
 *
 ****************************************************************************************/

START_CHECK("VT-06: xp_target_tangent")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_NO_DER;
  los_az        =       20.0;
  los_el        =       85.0;
  los_az_rate   =        1.0;
  los_el_rate   =        1.0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_tangent function */
  /* ------------------------------- */
  status = xp_target_tangent(&sat_id, &attitude_id,
                             &atmos_id, &dem_id,
                             &deriv, &los_az,
                             &los_el, &los_az_rate, &los_el_rate, &iray, &freq,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);

  CHECK_STATUS("xp_target_tangent", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-07
 *
 ****************************************************************************************/

START_CHECK("VT-07: xp_target_altitude")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_NO_DER;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  freq          =        1.e10;

  /* Call xp_target_altitude function */
  /* -------------------------------- */
  status = xp_target_altitude(&sat_id, &attitude_id,
                              &atmos_id, &dem_id,
                              &deriv, &los_az,
                              &geod_alt, &los_az_rate, &iray, &freq,
                              /* output */
                              &num_user_target, &num_los_target,
                              &target_id,
                              ierr);

  CHECK_STATUS("xp_target_altitude", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-08
 *
 ****************************************************************************************/

START_CHECK("VT-08: xp_target_star")

  /* Set input values */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  deriv         =     XL_NO_DER;
  star_ra       =      272.0;
  star_dec      =      -23.0;
  star_ra_rate  =        0.0;
  star_dec_rate =        0.0;
  freq          =        1.e10;

  /* Call xp_target_star function */
  /* ---------------------------- */
  status = xp_target_star(&sat_id, &attitude_id,
                          &atmos_id, &dem_id,
                          &deriv, &star_ra, &star_dec,
                          &star_ra_rate, &star_dec_rate, &iray, &freq,
                          /* output */
                          &num_user_target, &num_los_target,
                          &target_id,
                          ierr);

  CHECK_STATUS("xp_target_star", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-09
 *
 ****************************************************************************************/

START_CHECK("VT-09: xp_target_station")

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;
  geoc_long     =      315.0;
  geod_lat      =        5.0;
  geod_alt      =        0.0;
  min_link_el   =        0.0;

  /* Call xp_target_station function */
  /* ------------------------------- */
  status = xp_target_station(&sat_id, &attitude_id, &dem_id,
                             &deriv, &geoc_long,
                             &geod_lat, &geod_alt, &min_link_el,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);

  CHECK_STATUS("xp_target_station", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-10
 *                        Note: this test has been removed since xp_target_drs has become obsolete
 *
 ****************************************************************************************/


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-11
 *
 ****************************************************************************************/

START_CHECK("VT-11: xp_target_extra_main")


  /* Set input values */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  choice        = XP_TARG_EXTRA_MAIN_ALL;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_main function */
  /* ---------------------------------- */
  status = xp_target_extra_main(&target_id,
                                &choice, &target_type, &target_number,
                                /* output */
                                main_results, main_results_rate, 
                                main_results_rate_rate, ierr);

  CHECK_STATUS("xp_target_extra_main", status)


END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-12
 *
 ****************************************************************************************/

START_CHECK("VT-12: xp_target_tangent_sun")

  /* Set input values */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  time_ref      = XL_TIME_UTC;
  deriv         = XL_NO_DER;
  time          = 655.3456;
  pos[0]        =  6997887.57;
  pos[1]        = -1536046.83;
  pos[2]        =    99534.18;
  vel[0]        =     -240.99;
  vel[1]        =    -1616.85;
  vel[2]        =    -7376.65;
  acc[0]        =       -7.79104;
  acc[1]        =        1.69353;
  acc[2]        =       -0.10826;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* call to attitude_compute */
  /* ------------------------ */
  status = xp_target_close(&target_id, ierr);
  CHECK_STATUS("STATUS of xp_target_close ", status);

  status = xp_attitude_compute(&model_id, &time_id, &sat_nom_trans_id,
                               &sat_trans_id, &instr_trans_id,
                               &attitude_id, &time_ref, &time,
                               pos, vel, acc, &target_frame,
                               /* output */
                               ierr);
  CHECK_STATUS("xp_attitude_compute", status);

  /* Call xp_sun function */
  /* -------------------- */
  status = xp_target_tangent_sun(&sat_id, &attitude_id,
                                 &atmos_id, &dem_id,
                                 &deriv, &iray, &freq,
                                 /* output */
                                 &num_user_target, &num_los_target,
                                 &target_id, ierr);

  CHECK_STATUS("xp_target_tangent_sun", status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-13
 *
 ****************************************************************************************/

START_CHECK("VT-13: xp_target_tangent_moon")

  /* Set input values */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  time_ref      = XL_TIME_UTC;
  deriv         = XL_NO_DER;
  time          = 255.3456;
  pos[0]        =  6997887.57;
  pos[1]        = -1536046.83;
  pos[2]        =    99534.18;
  vel[0]        =     -240.99;
  vel[1]        =    -1616.85;
  vel[2]        =    -7376.65;
  acc[0]        =       -7.79104;
  acc[1]        =        1.69353;
  acc[2]        =       -0.10826;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* call to attitude_compute */
  /* ------------------------ */
  status = xp_target_close(&target_id, ierr);
  CHECK_STATUS("STATUS of xp_target_close ", status);

  status = xp_attitude_compute(&model_id, &time_id, &sat_nom_trans_id,
                               &sat_trans_id, &instr_trans_id,
                               &attitude_id, &time_ref, &time,
                               pos, vel, acc, &target_frame,
                               /* output */
                               ierr);
  CHECK_STATUS("xp_attitude_compute", status);

  /* Call xp_moon function */
  /* --------------------- */
  status = xp_target_tangent_moon(&sat_id, &attitude_id,
                                  &atmos_id, &dem_id,
                                  &deriv, &iray, &freq,
                                  /* output */
                                  &num_user_target, &num_los_target,
                                  &target_id, ierr);

  CHECK_STATUS("xp_target_tangent_moon", status)

END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-14
 *
 ****************************************************************************************/

START_CHECK("VT-14: Cross check between xp_target_inter and xp_target_station")

  freq = 1e14;

  pos[2] = 500;

  /* Input parameters */
  /* ---------------- */
  sat_id        = XP_SAT_ENVISAT;
  time_ref      = XL_TIME_UTC;
  inter_flag    = XP_INTER_1ST;
  deriv         = XL_DER_1ST;
  time          = -2456.0;
  pos[0]        =  4859964.138;
  pos[1]        = -5265612.059;
  pos[2]        =        0.002;
  vel[0]        =    -1203.303801;
  vel[1]        =    -1098.845511;
  vel[2]        =     7377.224410;
  acc[0]        =        0.000;
  acc[1]        =        0.000;
  acc[2]        =        0.000;
  los_az        =      102.6883323274972;
  los_el        =       35.51035544761065;
  geod_alt      =        0.0;
  los_az_rate   =       -0.04221457543826715;
  los_el_rate   =        0.01311451967490482;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* In EF it would be direction (0.21,1,0) */

  /* Call xp_attitude_init & attitude compute function */
  /* ------------------------------------------------- */
  status = xp_target_close(&target_id, ierr);
  CHECK_STATUS("STATUS of xp_target_close ", status);

  status = xp_attitude_compute(&model_id, &time_id,
                               &sat_nom_trans_id,
                               &sat_trans_id,
                               &instr_trans_id,
                               &attitude_id,
                               &time_ref, &time,
                               pos, vel, acc, 
                               &target_frame,
                               /* output */
                               ierr);
  CHECK_STATUS("xp_attitude_compute", status);


  /* Call xp_target_inter */
  /* -------------------- */
  status = xp_target_inter(&sat_id, &attitude_id,
                           &atmos_id, &dem_id,
                           &deriv, &inter_flag, &los_az,
                           &los_el, &geod_alt, &los_az_rate, &los_el_rate, &iray, &freq,                     
                           &num_user_target, &num_los_target,
                           /* output */
                           &target_id, ierr);

  CHECK_STATUS("xp_target_inter", status);

  choice        = XL_NO_DER;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  CHECK_STATUS("xp_target_extra_vector", status);


  /* Call xp_target_extra_main */
  /* ------------------------- */
  choice        = XP_TARG_EXTRA_AUX_ALL;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  status = xp_target_extra_main(&target_id,
                                &choice, &target_type, &target_number,
                                /* output */
                                main_results, main_results_rate, 
                                main_results_rate_rate, ierr);

  CHECK_STATUS("xp_target_extra_main", status);

  /* Input parameters for xp_target_station */
  /* -------------------------------------- */

  deriv         = XL_DER_2ND;
  geoc_long     = main_results[0];
  geod_lat      = main_results[2];
  geod_alt      = main_results[3];
  min_link_el   = 10.0;

  /* Call xp_target_station function */
  /* ------------------------------- */
  status = xp_target_station(&sat_id, &attitude_id, &dem_id,
                             &deriv, &geoc_long,
                             &geod_lat, &geod_alt, &min_link_el,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);

  CHECK_STATUS("xp_target_station", status);
  

  choice        = XL_NO_DER;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results2,
                                  vector_results_rate2,
                                  vector_results_rate_rate2,
                                  ierr);

  CHECK_STATUS("xp_target_extra_vector", status);

  /* Compare results */
  /* --------------- */

  printf("\n");
  printf(" ...\tComparison between xp_target_inter and xp_target_station:\n");
  printf("\n");
  printf("\tOUTPUT from xp_target_inter\n");
  printf("\tTarget Position  : [%12.3lf,%12.3lf,%12.3lf]\n",vector_results[0], vector_results[1], vector_results[2]);
/*printf("\tTarget Velocity  : [%12.3lf,%12.3lf,%12.3lf]\n",vector_results[3], vector_results[4], vector_results[5]);
*/printf("\tRange            : %lf\n",vector_results[6]);
/*printf("\tRange Rate       : %lf\n",vector_results[7]);
*/printf("\tSat-Tar LOS      : [%12.9lf,%12.9lf,%12.9lf]\n",vector_results[3], vector_results[4], vector_results[5]);
  printf("\tSat-Tar LOS.Rate : [%12.9lf,%12.9lf,%12.9lf]\n",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);
  printf("\n");
  printf("\tOUTPUT from xp_target_station\n");
  printf("\tTarget Position  : [%12.3lf,%12.3lf,%12.3lf]\n",vector_results2[0], vector_results2[1], vector_results2[2]);
  printf("\tRange            : %lf\n",vector_results2[6]);
  printf("\tSat-Tar LOS      : [%12.9lf,%12.9lf,%12.9lf]\n",vector_results2[3],vector_results2[4],vector_results2[5]);
  printf("\tSat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]\n",vector_results_rate2[3],vector_results_rate2[4],vector_results_rate2[5]);
  printf("\n");

  CHECK_PAR("Cartesian position of target/station [x]  .", vector_results[0], vector_results2[0],  0.1)
  CHECK_PAR("Cartesian position of target/station [y]  .", vector_results[1], vector_results2[1],  0.1)
  CHECK_PAR("Cartesian position of target/station [z]  .", vector_results[2], vector_results2[2],  0.1)
/*CHECK_PAR("Cartesian velocity of target/station [x]  .", vector_results[3], vector_results2[3],  0.1)
  CHECK_PAR("Cartesian velocity of target/station [y]  .", vector_results[4], vector_results2[4],  0.1)
  CHECK_PAR("Cartesian velocity of target/station [z]  .", vector_results[5], vector_results2[5],  0.1)
*/CHECK_PAR("Target/station to satellite range         .", vector_results[6], vector_results2[6],  0.1)
/*CHECK_PAR("Target/station to satellite range rate    .", vector_results[7], vector_results2[6], 0.1)
*/CHECK_PAR("Satellite LOS x                       .", vector_results[3], vector_results2[3], 0.1)
  CHECK_PAR("Satellite LOS y                       .", vector_results[4], vector_results2[4], 0.1)
  CHECK_PAR("Satellite LOS z                       .", vector_results[5], vector_results2[5], 0.1)
  CHECK_PAR("Satellite LOS x rate                  .", vector_results_rate[3],vector_results_rate2[3], 0.1)
  CHECK_PAR("Satellite LOS y rate                  .", vector_results_rate[4],vector_results_rate2[4], 0.1)
  CHECK_PAR("Satellite LOS z rate                  .", vector_results_rate[5],vector_results_rate2[5], 0.1)

END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-15
 *
 ****************************************************************************************/

START_CHECK("VT-15: xp_target_extra_aux")


  /* Set input values */
  /* ---------------- */
  choice        = XP_TARG_EXTRA_AUX_ALL; 
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_main function */
  /* ---------------------------------- */
  status = xp_target_extra_aux(&target_id,
                               &choice, &target_type, &target_number, 
                               /* output */
                               aux_results, aux_results_rate, aux_results_rate_rate, ierr);
  CHECK_STATUS("xp_target_extra_aux", status);


END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-16
 *
 ****************************************************************************************/
START_CHECK("VT-16: xp_target_extra_ef_target")


  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  freq          =        1.e10;

  /* Call xp_target_extra_ef_target function */
  /* --------------------------------------- */

  status = xp_target_extra_ef_target(&target_id,
                                     &choice, &target_type, &target_number, &freq,
                                     /* output */
                                     ef_target_results_rate, ef_target_results_rate_rate, ierr);

  CHECK_STATUS("xp_target_extra_ef_target", status);


END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-17
 *
 ****************************************************************************************/
START_CHECK("VT-17: xp_target_extra_target_to_sun / xp_target_extra_target_to_moon")


  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_extra_target_to_sun function */
  /* ------------------------------------------- */
  status = xp_target_extra_target_to_sun(&target_id,
                                         &choice, &target_type, &target_number, 
                                         &iray, &freq,
                                         sun_results, sun_results_rate, sun_results_rate_rate, ierr);

  CHECK_STATUS("xp_target_extra_target_to_sun", status)

  /* Call xp_target_extra_target_to_moon function */
  /* -------------------------------------------- */
  status = xp_target_extra_target_to_moon(&target_id,
                                          &choice, &target_type, &target_number, 
                                          &iray, &freq,
                                          moon_results, moon_results_rate, moon_results_rate_rate, ierr);

  CHECK_STATUS("xp_target_extra_target_to_moon", status)

END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-18
 *
 ****************************************************************************************/
#ifdef xxx
START_CHECK("Cross check between target with ray-tracing mode = XP_PRED_REF and XP_LUT_REF")

  /* Input parameters */
  /* ---------------- */

  time_ref       = XL_TIME_UTC;
  instrument_id  = 0;
  time           = mjdp[0];
  deriv          = XL_DER_1ST;
  los_az         = 180;
  los_el         = 15.0;
  los_az_rate    = 0;
  los_el_rate    = 0;
  iray           = XP_US76_REF;
  freq           = 3.0e14;

  /* Set enviroment variable for defining output converter filename */
  /* -------------------------------------------------------------- */
  strcpy(atm_var,"XP_USER_REF_CONV_FILE_NAME=");

#ifndef XL_WINDOWS
  strcat(atm_var,"./REFRACT_1976.OUT_conv");
#else
  strcat(atm_var,".\\REFRACT_1976.OUT_conv");
#endif
	
  if ((put=putenv(atm_var))!=0)
    {
      printf("ERROR in setting enviroment variable");
      return(XP_ERR);
    }


  /* System call for running converter */
  /* --------------------------------- */
  
  printf("-----------------------------------------------------------------------\n");
  printf("Converter execution in progress. It will take about one hour and a half\n");
  printf("-----------------------------------------------------------------------\n");


#ifdef SOLARIS
  system("../lib/SOLARIS/xp_converter -sat 21 -cif ../example/data/REFRACT_1976.DAT_conv -min_az 160.0 -max_az 200.0 -min_freq 2.05e7 -max_freq 1.25e9 -mlst_dr 0.0");
#elif LINUX32_LEGACY
  system("../lib/LINUX32_LEGACY/xp_converter -sat 21 -cif ../example/data/REFRACT_1976.DAT_conv -min_az 160.0 -max_az 200.0 -min_freq 2.05e7 -max_freq 1.25e9 -mlst_dr 0.0");
#elif MACOS
  system("./xp_converter -sat 21 -cif ../example/data/REFRACT_1976.DAT_conv -min_az 160.0 -max_az 200.0 -min_freq 2.05e7 -max_freq 1.25e9 -mlst_dr 0.0");
#elif WINDOWS
  system("xp_converter.exe -sat 21 -cif .\\..\\example\\data\\REFRACT_1976.DAT_conv -min_az 160.0 -max_az 200.0 -min_freq 2.05e7 -max_freq 1.25e9  -mlst_dr 0.0");
#endif


  /* Initializing Atmospheric Model */
  /*------------------------------- */
  atmos_mode = XP_LUT_INIT;
  atmos_model = 0; /*dummy*/
  strcpy (atmos_file, "REFRACT_1976.OUT_conv");

  status = xp_atmos_init(&sat_id, &atmos_mode, &atmos_model, atmos_file, poi_err);

  CHECK_STATUS("xp_atmos_init", status);


  /* Call xp_target_tangent with iray=XP_PRED_REF(US76_REF) */
  /* ------------------------------------------------------ */

  status = xp_target_tangent(&sat_id, &instrument_id, &time_ref,
                             &time, pos, vel, acc, &deriv, &los_az, &los_el,
                             &los_az_rate, &los_el_rate, &iray, &freq,
                             target_out_pred, poi_err);

  CHECK_STATUS("target status XP_US76_REF", status);


  /* Call xp_target_tangent with iray = XP_LUT_REF */
  /* --------------------------------------------- */
  iray = XP_LUT_REF;
  status = xp_target_tangent(&sat_id, &instrument_id, &time_ref,
                             &time, pos, vel, acc, &deriv, &los_az, &los_el,
                             &los_az_rate, &los_el_rate, &iray, &freq,
                             target_out_lut, poi_err);

  CHECK_STATUS("target status XP_LUT_REF", status);


  /* Results comparation */
  /* ------------------- */
  CHECK_VEC("results vector", target_out_pred, target_out_lut, 0, 13, 1.e-3);


END_CHECK 
#endif

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-19
 *
 ****************************************************************************************/
START_CHECK("VT-19: xp_change_frame")


  /* Set input values */
  /* ---------------- */
  time_ref      = XL_TIME_UT1;
  time          = 255.3456;
  
  cf_mode = XP_MODE_FLAG_LOCATION;
  frame_flag_input = XP_FRAME_FLAG_SAT;
  frame_flag_output = XP_FRAME_FLAG_EXT;
  frame_id_input = XP_SAT_ATT;
  frame_id_output = XL_EF;
  deriv = XP_DER_2ND;

  vec_input[0]             =   6296843.841;
  vec_input[1]             =   -1397383.429;
  vec_input[2]             =   -10319300.710;
  vec_rate_input[0]        =   -152.260779;
  vec_rate_input[1]        =   -3217.355126;
  vec_rate_input[2]        =   939.545695;
  vec_rate_rate_input[0]   =   0.176318842;
  vec_rate_rate_input[1]   =   0.886385019;
  vec_rate_rate_input[2]   =   -0.762658393;

  /* Call xp_change_frame function */
  /* ----------------------------- */
  status = xp_change_frame (&sat_id, &model_id, &time_id,
                            &sat_nom_trans_id,&sat_trans_id,&instr_trans_id,
                            &cf_mode,
                            &frame_flag_input,&frame_id_input,
                            &frame_flag_output,&frame_id_output,
                            &time_ref,&time,
                            pos,vel,acc,&deriv,
                            vec_input,vec_rate_input,vec_rate_rate_input,
                            vec_output,vec_rate_output,vec_rate_rate_output,
                            cf_err);

  CHECK_STATUS("xp_change_frame", status);

  for (cf_i=0 ; cf_i<3 ; cf_i++)
  {
    vec_aux[cf_i]           = vec_output[cf_i];
    vec_rate_aux[cf_i]      = vec_rate_output[cf_i];
    vec_rate_rate_aux[cf_i] = vec_rate_rate_output[cf_i];
  }
  frame_flag_input = XP_FRAME_FLAG_EXT;
  frame_flag_output = XP_FRAME_FLAG_SAT;
  frame_id_input = XL_EF;
  frame_id_output = XP_SAT_ATT;

  status = xp_change_frame (&sat_id, &model_id, &time_id,
                            &sat_nom_trans_id,&sat_trans_id,&instr_trans_id,
                            &cf_mode,
                            &frame_flag_input,&frame_id_input,
                            &frame_flag_output,&frame_id_output,
                            &time_ref,&time,
                            pos,vel,acc,&deriv,
                            vec_aux,vec_rate_aux,vec_rate_rate_aux,
                            vec_output,vec_rate_output,vec_rate_rate_output,
                            cf_err);

  CHECK_STATUS("xp_change_frame", status);

  CHECK_VEC("Checking output vectors: position    :" ,vec_output,vec_input,0,2,1e-6);
  CHECK_VEC("Checking output vectors: velocity    :" ,vec_rate_output,vec_rate_input,0,2,1e-9);
  CHECK_VEC("Checking output vectors: acceleration:" ,vec_rate_rate_output,vec_rate_rate_input,0,2,1e-12);

END_CHECK

/*****************************************************************************************
 *
 * CLOSE ID
 *
 ****************************************************************************************/
START_CHECK("Closing Ids:")
  status = xp_target_close(&target_id, ierr);
  CHECK_STATUS("xp_attitude_close", status);

  status = xp_attitude_close(&attitude_id, ierr);
  CHECK_STATUS("xp_attitude_close", status);

  xp_sat_nominal_att_close(&sat_nom_trans_id, ierr);
  CHECK_STATUS("xp_sat_nominal_att_close", status);

  xp_sat_att_close(&sat_trans_id, ierr);
  CHECK_STATUS("xp_sat_att_close", status);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-20
 *
 ****************************************************************************************/
START_CHECK("VT-20: xp_target_sc")
  /* ENVISAT attitude */
  model_enum = XP_MODEL_ENVISAT;
  model_param[0] = -0.1671;        
  model_param[1] =  0.0501;         
  model_param[2] =  3.9130;  
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id1, poi_err);
  CHECK_STATUS("xp_sat_nominal_att_init_model", status);
  
  /* Initialize GEO AUTO attitude */
  model_enum = XP_MODEL_GEO;
  model_param[0] = 0;        
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id2, poi_err);
  
  CHECK_STATUS("xp_sat_nominal_att_init_model", status);
  
  /* Initialize attitudes */
  status = xp_attitude_init(&attitude_id, poi_err);
  CHECK_STATUS("xp_attitude_init", status);
  
  status = xp_attitude_init(&attitude_id_2, poi_err);
  CHECK_STATUS("xp_attitude_init", status);
  
  time          = 4096.9639261080838;
  pos[0]        =  4859964.138;
  pos[1]        = -5265612.059;
  pos[2]        =        0.002;
  vel[0]        =    -1203.303801;
  vel[1]        =    -1098.845511;
  vel[2]        =     7377.224410;
  acc[0]        =        0.0;
  acc[1]        =        0.0;
  acc[2]        =        0.0;
  
  target_frame = XP_SAT_NOMINAL_ATT;
  
  /* ENVISAT attitude */
  status = xp_attitude_compute(&model_id, &time_id, &sat_nom_trans_id1,
                               &sat_trans_id, &instr_trans_id,
                               &attitude_id, &time_ref, &time,
                               pos, vel, acc, &target_frame, poi_err);
  CHECK_STATUS("xp_attitude_compute", status);
  
  /* Automatic Yaw-flip */
  pos[0] = 39257164.974674419;
  pos[1] = 15384714.722930847;
  pos[2] = 0.;
  
  vel[0] = 0.;
  vel[1] = 0.;
  vel[2] = 0.;
  
  acc[0] = 0.;
  acc[1] = 0.;
  acc[2] = 0.;
  status = xp_attitude_compute(&model_id, &time_id, &sat_nom_trans_id2,
                               &sat_trans_id, &instr_trans_id,
                               &attitude_id_2, &time_ref, &time,
                               pos, vel, acc, &target_frame, poi_err);
  CHECK_STATUS("xp_attitude_compute", status);
  
  deriv = XL_DER_1ST;
  sat_id2 = XP_SAT_GENERIC_GEO;
  status = xp_target_sc(&sat_id, &attitude_id, &sat_id2, &attitude_id_2,
                        &deriv,
                        &num_user_target, &num_los_target,
                        &target_id, poi_err);
  CHECK_STATUS("xp_target_sc", status);
  
  /* Call xp_target_close function */
  status = xp_target_close(&target_id,
                           /* output */
                           poi_err);
  CHECK_STATUS("xp_target_close", status);
  
  status = xp_attitude_close(&attitude_id,
                             /* output */
                             poi_err);
  CHECK_STATUS("xp_attitude_close", status);
  
  status = xp_attitude_close(&attitude_id_2,
                             /* output */
                             poi_err);
  CHECK_STATUS("xp_attitude_close", status);
  
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id1,
                                    /* output */
                                    poi_err);
  CHECK_STATUS("xp_sat_nominal_att_close", status);
  
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id2,
                                    /* output */
                                    poi_err);
  CHECK_STATUS("xp_sat_nominal_att_close", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-21
 *
 ****************************************************************************************/
START_CHECK("VT-21: xp_target_list_inter")
  /* ENVISAT attitude */
  model_enum = XP_MODEL_ENVISAT;
  model_param[0] = -0.1671;        
  model_param[1] =  0.0501;         
  model_param[2] =  3.9130;  
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id1, poi_err);
  CHECK_STATUS("xp_sat_nominal_att_init_model", status);
  
  /* Initialize attitudes */
  status = xp_attitude_init(&attitude_id, ierr);
  CHECK_STATUS("xp_attitude_init", status);
  
  time          = 4096.9639261080838;
  pos[0]        =  4859964.138;
  pos[1]        = -5265612.059;
  pos[2]        =        0.002;
  vel[0]        =    -1203.303801;
  vel[1]        =    -1098.845511;
  vel[2]        =     7377.224410;
  acc[0]        =        0.0;
  acc[1]        =        0.0;
  acc[2]        =        0.0;
  
  target_frame = XP_SAT_NOMINAL_ATT;
  
  /* ENVISAT attitude */
  status = xp_attitude_compute(&model_id, &time_id, &sat_nom_trans_id1,
                               &sat_trans_id, &instr_trans_id,
                               &attitude_id, &time_ref, &time,
                               pos, vel, acc, &target_frame, poi_err);
  CHECK_STATUS("xp_attitude_compute", status);
  
  deriv      = XP_DER_2ND;
  sat_id     = XP_SAT_CRYOSAT;
  inter_flag = XP_INTER_1ST;
  inst_data.type = XP_AZ_EL_STRIP;
  inst_data.azimuth_elevation_input_union.azimuth_elevation_strip.azimuth = 270.;
  inst_data.azimuth_elevation_input_union.azimuth_elevation_strip.min_elevation  = 50.;
  inst_data.azimuth_elevation_input_union.azimuth_elevation_strip.max_elevation  = 70.;
  inst_data.azimuth_elevation_input_union.azimuth_elevation_strip.step_elevation = 10.;
  inst_data.signal_frequency = 1.e+10;
  geod_alt = 0.;
  status = xp_target_list_inter(&sat_id, &attitude_id, &atmos_id, &dem_id,
                                &deriv, &inter_flag, &inst_data, &geod_alt,
                                /* output */
                                &target_num, &target_id, poi_err);
  CHECK_STATUS("Status of xp_target_list_inter", status);
  free(target_num.num_los_target);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-22
 *
 ****************************************************************************************/
START_CHECK("VT-22: xp_target_list_extra_vector")
  choice      = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_vector(&target_id, &choice, &target_type,
                                       &vector_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_vector", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-23
 *
 ****************************************************************************************/
START_CHECK("VT-23: xp_target_list_extra_main")
  choice = XP_TARG_EXTRA_MAIN_ALL;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_main(&target_id, &choice, &target_type,
                                     &main_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_main", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-24
 *
 ****************************************************************************************/
START_CHECK("VT-24: xp_target_list_extra_aux")
  choice = XP_TARG_EXTRA_AUX_ALL;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_aux(&target_id, &choice, &target_type,
                                    &aux_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_aux", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-25
 *
 ****************************************************************************************/
START_CHECK("VT-25: xp_target_list_extra_ef_target")
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  status = xp_target_list_extra_ef_target(&target_id, &choice, &target_type,
                                          &freq, &ef_target_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_ef_target", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-26
 *
 ****************************************************************************************/
START_CHECK("VT-26: xp_target_list_extra_specular_reflection")
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  defl_north = 0; 
  defl_east  = 0;
  status = xp_target_list_extra_specular_reflection(&target_id, &choice, &target_type,
                                                    &defl_north, &defl_east,
                                                    &spec_reflec_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_specular_reflection", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-27
 *
 ****************************************************************************************/
START_CHECK("VT-27: xp_target_list_extra_target_to_moon")
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  iray = 0; /* dummy */
  status = xp_target_list_extra_target_to_moon(&target_id, &choice, &target_type,
                                               &iray, &freq,
                                               &moon_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_target_to_moon", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-28
 *
 ****************************************************************************************/
START_CHECK("VT-28: xp_target_list_extra_target_to_sun")
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  iray = 0; /* dummy */
  status = xp_target_list_extra_target_to_sun(&target_id, &choice, &target_type,
                                              &iray, &freq,
                                              &sun_list, poi_err);
  CHECK_STATUS("Status of xp_target_list_extra_target_to_sun", status);
  
  /* Call xp_target_close function */
  status = xp_target_close(&target_id,
                           /* output */
                           poi_err);
  CHECK_STATUS("xp_target_close", status);
  
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-29
 *
 ****************************************************************************************/
START_CHECK("VT-29: xp_attitude_define")
#ifdef XL_WINDOWS
  strcpy(attitude_definition_aocs_file, "..\\example\\data\\ATT_DEF_AOCS.XML");
#else
  strcpy(attitude_definition_aocs_file, "../example/data/ATT_DEF_AOCS.XML");
#endif

  status = xd_read_att_def(attitude_definition_aocs_file, &att_file, xd_ierr);
  CHECK_STATUS("Status of xd_read_att_def", status); 
	
	/* Call xp_attitude_define function */
	/* ------------------------------ */
	status = xp_attitude_define(&att_file,
	                            /*outputs*/	
	                            &sat_nom_trans_id,
	                            &sat_trans_id,
	                            &instr_trans_id,
	                            xd_ierr);
	CHECK_STATUS("Status of xp_attitude_define", status);
  
	xd_free_att_def(&att_file);
	
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id,
                                    /* output */
                                    poi_err);
  CHECK_STATUS("xp_sat_nominal_att_close", status);
END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-30
 *
 ****************************************************************************************/
START_CHECK("VT-30: xp_get_attitude_data")

	/* Call xp_get_attitude_data function */
  data_type       = XD_ATT_ANGLES;
  source_ref_type = XP_FRAME_FLAG_EXT;
  source_ref      = XL_GM2000;  
  status = xp_get_attitude_data(&attitude_id, 
                                &data_type,
                                &source_ref_type,
                                &source_ref,
                                &att_rec,
                                ierr);

	CHECK_STATUS("Status of xp_get_attitude_data", status);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-31
 *
 ****************************************************************************************/
START_CHECK("VT-31: xp_gen_attitude_data")

	/* Call xp_gen_attitude_data function */
  att_def.type = XP_SAT_NOMINAL_ATT;
  att_def.sat_nom_trans_id     = sat_nom_trans_id1;
  att_def.sat_trans_id.ee_id   = NULL;
  att_def.instr_trans_id.ee_id = NULL;
  
  time_step = 10;
  time_interval.tstart.type     = XO_TIME_TYPE;
  time_interval.tstart.time_ref = XO_TIME_UTC;
  time_interval.tstart.time     = 3000;
  time_interval.tstop.type      = XO_TIME_TYPE;
  time_interval.tstop.time_ref  = XO_TIME_UTC;
  time_interval.tstop.time      = 3000.14;
  data_type = XD_ATT_QUATERNIONS;
  source_ref_type = XP_FRAME_FLAG_EXT;
  source_ref      = XL_GM2000;  

  status = xp_gen_attitude_data(&orbit_id, 
                                &att_def,
                                &time_interval,
                                &time_step,
                                &data_type, 
                                &source_ref_type,
                                &source_ref,
                                &quat_file,
                                ierr);

	CHECK_STATUS("Status of xp_gen_attitude_data", status);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-32
 *
 ****************************************************************************************/
START_CHECK("VT-32: xp_gen_attitude_file")

  /* Get attitude file with quaternions */
  status = xp_gen_attitude_file(&orbit_id, 
                                &att_def,
                                &time_interval,
                                &time_step,
                                &data_type, 
                                &source_ref_type,
                                &source_ref,
                                output_dir,
                                file_class, 
                                &version_number,
                                fh_system,
                                /* input/output */
                                out_att_file,
                                ierr);

	CHECK_STATUS("Status of xp_gen_attitude_file", status);

END_CHECK

/*****************************************************************************************
 *
 * CLOSE ID
 *
 ****************************************************************************************/
START_CHECK("Closing Ids:")
  status = xp_attitude_close(&attitude_id,
                             /* output */
                             poi_err);
  CHECK_STATUS("xp_attitude_close", status);
  
  status = xp_sat_nominal_att_close(&sat_nom_trans_id1,
                                    poi_err);
  CHECK_STATUS("xp_sat_nominal_att_close", status);


  status = xo_orbit_close(&orbit_id, ierr);
  CHECK_STATUS("xo_orbit_close", status);

  status = xl_time_close(&time_id, ierr);
  CHECK_STATUS("xl_time_close", status);

END_CHECK

/****************************************************************************************/
printf("\nEOCFI_POINTING VALIDATION COMPLETED SUCCESSFULLY\n");

END_VALIDATION

 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Module      : explorer_pointing_c.c
 *
 * Functions   : main program (EXPLORER_POINTING example) to call:
 *
 *                  o Sat Nominal Transformation initialization functions
 *                    - xp_sat_nominal_att_init
 *                    - xp_sat_nominal_att_init_model
 *                    - xp_sat_nominal_att_init_harmonic
 *                    - xp_sat_nominal_att_init_file
 *                    - xp_sat_nominal_att_close
 *                    - xp_sat_nominal_att_init_status
 *                    - xp_sat_nominal_att_get_mode
 *                  o Sat Transformation initialization functions
 *                    - xp_sat_att_angle_init
 *                    - xp_sat_att_matrix_init
 *                    - xp_sat_att_init_harmonic
 *                    - xp_sat_att_init_file
 *                    - xp_sat_att_close
 *                    - xp_sat_att_init_status
 *                    - xp_sat_att_get_mode
 *                  o Instrument Transformation initialization functions
 *                    - xp_instr_att_angle_init
 *                    - xp_instr_att_matrix_init
 *                    - xp_instr_att_init_harmonic
 *                    - xp_instr_att_init_file
 *                    - xp_instr_att_close
 *                    - xp_instr_att_init_status
 *                    - xp_instr_att_get_mode
 *                  o Attitude calculation functions
 *                    - xp_attitude_init
 *                    - xp_attitude_compute
 *                    - xp_attitude_user_set
 *                    - xp_attitude_close
 *                    - xp_attitude_init_status
 *                    - xp_attitude_get_mode
 *                    - xp_get_attitude_data
 *                    - xp_gen_attitude_data
 *                    - xp_gen_attitude_file
 *                  o Atmosphere and DEM initialization functions
 *                    - xp_atmos_init
 *                    - xp_dem_init
 *                  o Target pointing functions
 *                    - xp_target_inter
 *                    - xp_target_ground_range
 *                    - xp_target_incidence_angle
 *                    - xp_target_range
 *                    - xp_target_range_rate
 *                    - xp_target_tangent
 *                    - xp_target_altitude
 *                    - xp_target_star
 *                    - xp_target_tangent_sun
 *                    - xp_target_tangent_moon
 *                    - xp_target_generic
 *                    - xp_target_station
 *                    - xp_target_sc
 *                    - xp_target_list_inter
 *                    - xp_target_extra_vector
 *                    - xp_target_extra_main
 *                    - xp_target_extra_aux
 *                    - xp_target_extra_ef_target
 *                    - xp_target_extra_target_to_sun
 *                    - xp_target_extra_target_to_moon
 *                    - xp_target_list_inter
 *                    - xp_target_list_extra_main
 *                    - xp_target_list_extra_aux
 *                    - xp_target_list_extra_vector
 *                    - xp_target_list_extra_ef_target
 *                    - xp_target_list_extra_specular_reflection
 *                    - xp_target_list_extra_target_to_moon
 *                    - xp_target_list_extra_target_to_sun
 *                  o System reference transformation functions
 *                    - xp_change_frame
 *
 *
 * Purpose     : Example program to show the way to call the previous functions.
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
#include <stdlib.h>
#include <string.h>

#include <explorer_file_handling.h>	/* EXPLORER_FILE_HANDLING header file */
#include <explorer_data_handling.h>	/* EXPLORER_DATA_HANDLING header file */

#include <explorer_lib.h>		/* EXPLORER_LIB header file */

#include <explorer_orbit.h>		/* EXPLORER_ORBIT header file */

#include <explorer_pointing.h>		/* EXPLORER_POINTING header file */

/* Main program */
/* ------------ */

int main (int argc, char *argv[])
{

   /* Local variables declaration */
   /* --------------------------- */

   /* Error handling and message visualization */
   long   status;                             /* (Normal) status flag */
   long   ext_status;                         /* (Extended) status flag */
   long   n;				                  /* Number of error messages */
   long   func_id;                            /* CFI function ID */
   char   msg[XL_MAX_COD][XL_MAX_STR];        /* Error messages vector */
   long   xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];  /* Error vector for DH functions */
   long   lib_err[XL_ERR_VECTOR_MAX_LENGTH];  /* Error vector for LIB functions */
   long   ierr[XP_ERR_VECTOR_MAX_LENGTH];  /* Error vector for POINTING functions */

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
   xp_param_model_str            param_model;
   xp_sat_nom_att_file_model_str sat_nom_file_model;
   xp_angle_model_str            angle_model;
   xp_harmonic_model_str         harmo_model;
   xp_atmos_id_data              atmos_data;
   xp_attitude_id_data           attitude_data;
   xp_target_id_data             target_data;

   /* xl_time_ref_init */
   long   tri_orbit_num;
   double tri_anx_time, tri_orbit_duration;
   double tri_time[4];

   /* xl_time_ref_init_file */
   long   trif_time_model, trif_n_files, trif_time_init_mode, trif_time_ref ;
   char   **trif_time_file;
   double trif_time0, trif_time1, trif_val_time0, trif_val_time1;
   long   trif_orbit0, trif_orbit1;
   long   i, imax;

   /* xo_orbit_init_file */
   long orbit_mode;
   char *input_files[1];
   char osf[500]="";
   double val_time0, val_time1;
     
   char attitude_definition_aocs_file[XD_MAX_STR];
   xd_attitude_definition_data att;
   
  /* xp_sat_nominal_att_init_model */
   long model_enum;
   double model_param[XP_NUM_MODEL_PARAM];

   /* xp_sat_att_angle_init */
   double ang[3];

   /* xp_sat_att_matrix_init */
   double att_matrix[3][3];

   /* xp_sat_nominal_att_init_file */
   long   n_files;
   char   **attitude_file;
   long   time_init_mode;
   double time0,  time1;
   long   orbit0, orbit1;
   double val0,  val1;

   /* xp_instr_att_init_harmonic */
   long angle_type;
   long num_terms[3];
   long harmonic_type_pitch[XP_MAX_NUM_HARMONIC];
   long harmonic_type_roll[XP_MAX_NUM_HARMONIC];
   long harmonic_type_yaw[XP_MAX_NUM_HARMONIC];
   double harmonic_coef_pitch[XP_MAX_NUM_HARMONIC];
   double harmonic_coef_roll[XP_MAX_NUM_HARMONIC];
   double harmonic_coef_yaw[XP_MAX_NUM_HARMONIC];
   double offset[3];

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
   xd_att_file att_file;
   xp_attitude_def  att_def;

   /* xp_atmos_init */
   long   atmos_mode, atmos_model;
   char   atmos_file[XL_MAX_STR];

   /* xp_dem_init */
   long   dem_mode, dem_model;
   char   dem_file[XL_MAX_STR];

   /* xp_target */
   long sat_id, sat_id2;
   long num_user_target;
   long num_los_target;

   /* xp_target_inter */
   long   time_ref, deriv, inter_flag, iray, i_der;
   double pos[3], vel[3], acc[3];
   double pos_2[3], vel_2[3], acc_2[3];
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

   /* xp_target_extra_main */
   long   choice;
   double main_results[XP_SIZE_TARGET_RESULT_MAIN]; 
   double main_results_rate[XP_SIZE_TARGET_RESULT_MAIN];
   double main_results_rate_rate[XP_SIZE_TARGET_RESULT_MAIN];

   /* xp_target_extra_target_aux */
   long   aux_choice;
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

   /* xp_change_frame */
   long cf_mode;
   long frame_flag_input;
   long frame_flag_output;
   long frame_id_input;
   long frame_id_output;
   double cf_time;
   double cf_pos[3], cf_vel[3], cf_acc[3];
   double vec_input[3], vec_rate_input[3], vec_rate_rate_input[3];
   double vec_output[3], vec_rate_output[3], vec_rate_rate_output[3];

   /* Variables for xl_model_init */
   long mode;
   long models[XL_NUM_MODEL_TYPES_ENUM];
   long xl_ierr[XL_ERR_VECTOR_MAX_LENGTH];
   
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
   
   /* Set error handling mode (either Silent or Verbose) */
   /* -------------------------------------------------- */

   xp_silent();     /* Set error handling mode to SILENT */
/*   xp_verbose();    /* Set error handling mode to VERBOSE */

   /* Dummy Test of Logging feature */
   /* ----------------------------- */

/* n = 0;
   strcpy(msg[n++],"This is the first user's log message");
   strcpy(msg[n++],"This is the second user's log message");
   xp_print_msg(&n,msg);

/******************************************************************************/
/*                                                                            */
/* Time initialization functions                                              */
/*                                                                            */
/******************************************************************************/

  printf("\n\n\nXL_MODEL_INIT\n");
  /* Model id initialization */
  /* Default model */
  mode = XL_MODEL_DEFAULT;
  
  status = xl_model_init( &mode, models, &model_id, ierr );
   
  /* ------------------------------------------------------------------------ */
  /* Time references initialization                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ref_init_file                                       */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_REF_INIT_FILE\n");

  /* Set input values */
  /* ---------------- */
  trif_time_model     = XL_TIMEMOD_IERS_B_PREDICTED;
  trif_n_files        = 1;
  trif_time_init_mode = XL_SEL_TIME;
  trif_time_ref       = XL_TIME_TAI;
  trif_time0          = 742.0;
  trif_time1          = 762.0;
  trif_orbit0         = 0;
  trif_orbit1         = 100;

  trif_time_file=(char **) calloc(5,sizeof(char*));
  trif_time_file[0]=(char *) malloc((size_t)(200*sizeof(char*)));
  strcpy (trif_time_file[0], "../data/bulb.dat");

  /* Call xl_time_ref_init_file function */
  /* ----------------------------------- */
  status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                 &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                 &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1,
                                 &time_id, lib_err);

  /* Free memory */
  /* ----------- */

  free((char *)(trif_time_file[0]));
  free((char **)(trif_time_file));

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xl_get_msg(&func_id, lib_err, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTime correctly initialized");
  }

  /* ------------------------------------------------------------------------ */
  /* Time references initialization                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ref_close                                           */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_REF_CLOSE\n");

  /* Call xl_time_close function */
  /* --------------------------- */
  ext_status = xl_time_close(&time_id, ierr);


  /* Print output values */
  /* ------------------- */

  if (ext_status != XL_OK)
  {
      func_id = XL_TIME_CLOSE_ID;
      xl_get_msg(&func_id, &ext_status, &n, msg);
      xl_print_msg(&n, msg);
      if (ext_status <= XL_ERR) return(XL_ERR);    /* CAREFUL: extended status */

  } else {
     printf("\nMemory freed successfully");
  }


  /* ------------------------------------------------------------------------ */
  /* Time references initialization                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ref_init                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_REF_INIT\n");

  /* Set input values */
  /* ---------------- */
  tri_time[0]   = -245.1000000000000000;   /* TAI time [days] */
  tri_time[1]   = -245.0995949074074074;   /* UTC time [days] (= TAI - 35.0 s) */
  tri_time[2]   = -245.0995879629629630;   /* UT1 time [days] (= TAI - 35.6 s) */
  tri_time[3]   = -245.0997800925925926;   /* GPS time [days] (= TAI - 19.0 s) */

  tri_orbit_num = 10;
  tri_anx_time  = 5245.123456;
  tri_orbit_duration = 6035.928144;

  /* Call xl_time_ref_init function */
  /* ------------------------------ */
  status = xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                            &tri_orbit_duration, &time_id, lib_err);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_REF_INIT_ID;
     xl_get_msg(&func_id, lib_err, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTime correctly initialized");
  }

  /* ------------------------------------------------------------------------ */
  /* Oribt  initialization                                                    */
  /* ------------------------------------------------------------------------ */
  printf("\n\n\nXO_ORBIT_INIT_FILE\n");

#ifdef XL_WINDOWS
  strcpy(osf, "..\\data\\AE__MPL_ORBSCT_20071001T180002_99999999T999999_0000.EEF");
#else
  strcpy(osf, "../data/AE__MPL_ORBSCT_20071001T180002_99999999T999999_0000.EEF");
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
/*                                                                            */
/* Attitude initialization functions                                          */
/*                                                                            */
/******************************************************************************/
#ifdef XL_WINDOWS
  strcpy(attitude_definition_aocs_file, "..\\data\\ATT_DEF_AOCS.XML");
#else
  strcpy(attitude_definition_aocs_file, "../data/ATT_DEF_AOCS.XML");
#endif
  
  /* ------------------------------------------------------------------------ */
  /* Satellite Nominal. Satellite and Instrument Transformations              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_attitude_define                                */
  /* ------------------------------------------------------------------------ */
	status = xd_read_att_def(attitude_definition_aocs_file, &att, xd_ierr);
  if (status != XP_OK)
  {
     func_id = XD_READ_ATT_DEF_ID;
     xd_get_msg(&func_id, xd_ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } 
	
	/* Call xp_attitude_define function */
	/* ------------------------------ */
	status = xp_attitude_define(&att,
	                                  /*outputs*/	
	                                  &sat_nom_trans_id,
	                                  &sat_trans_id,
	                                  &instr_trans_id,
	                                  ierr);
	if (status != XP_OK)
  {
     func_id = XP_ATTITUDE_DEFINE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\n\nXP_ATITTUDE_DEFINE: Satellite Nominal, Satellite and Instrument Attitude Transformatiom correctly initialised");
  }
  
  xd_free_att_def(&att);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_nominal_att_close                                    */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_nominal_att_close\n");

  /* Call xp_sat_nominal_att_close function */
  /* -------------------------------------- */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id,
                                    /* output */
                                    ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  
  /* ------------------------------------------------------------------------ */
  /* Satellite Nominal Transformations                                        */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_nominal_att_init_file                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_nominal_att_init_file\n");

  /* Set input values */
  /* ---------------- */
  n_files     = 1;
  time0       = 6034.1;  /* time0 is used to store the nodal period */
  time_init_mode = XP_SEL_FILE;
  time_ref = XL_TIME_TAI;

  attitude_file=(char **) calloc(1,sizeof(char*));
  attitude_file[0]=(char *) malloc((size_t)(200*sizeof(char*)));

#ifdef XL_WINDOWS
  strcpy(attitude_file[0], "..\\data\\cryosat_quaternions_att_file.xml");
#else
  strcpy(attitude_file[0], "../data/cryosat_quaternions_att_file.xml");
#endif

  /* Call xp_sat_nominal_att_init_file function */
  /* ------------------------------------------ */
  status = xp_sat_nominal_att_init_file(&time_id,
                                        &n_files, attitude_file,
                                        &time_init_mode, &time_ref, &time0, &time1, 
                                        /* output */
                                        &val0, &val1,
                                        &sat_nom_trans_id, ierr);

  /* Free memory */
  /* ----------- */
  free((char *)(attitude_file[0]));
  free((char **)(attitude_file));

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_INIT_FILE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nSatellite Nominal Attitude Transformatiom correctly initialised");
  }

  /* Accessor functions */
  status = xp_sat_nominal_att_get_file(&sat_nom_trans_id, &sat_nom_file_model);
  if (status <= XP_ERR) return(XP_ERR);

  status = xp_sat_nominal_att_set_file(&sat_nom_trans_id, &sat_nom_file_model);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status      : %li", xp_sat_nominal_att_init_status(&sat_nom_trans_id));
  printf("\n- Init Mode        : %li", xp_sat_nominal_att_get_mode(&sat_nom_trans_id));
  printf("\n- File Model       : %li", sat_nom_file_model.file_model);
  printf("\n- Validity Start   : %f", sat_nom_file_model.val_time0);
  printf("\n- Validity Stop    : %f", sat_nom_file_model.val_time1);
  printf("\n- Data Type        : %li", sat_nom_file_model.data_type);
  printf("\n- Inertial Frame   : %li", sat_nom_file_model.inertial_frame);
  printf("\n- Maximum Gap      : %f", sat_nom_file_model.max_gap);
  printf("\n- Number of lines  : %li", sat_nom_file_model.lines);
  printf("\n- First line       :");
  printf("\n-     Time   = %f (time ref = %ld)",
          sat_nom_file_model.att_data[0].time, 
          sat_nom_file_model.att_data[0].time_ref);
  if (sat_nom_file_model.data_type == XD_ATT_QUATERNIONS)
  {
    printf("\n-     Quaternions  : {%f, %f, %f, %f}", 
            sat_nom_file_model.att_data[0].quaternion[0], 
            sat_nom_file_model.att_data[0].quaternion[1], 
            sat_nom_file_model.att_data[0].quaternion[2], 
            sat_nom_file_model.att_data[0].quaternion[3]);
  }
  else
  {
    printf("\n-     Angles  : {%f, %f, %f}", 
            sat_nom_file_model.att_data[0].angles[0], 
            sat_nom_file_model.att_data[0].angles[1], 
            sat_nom_file_model.att_data[0].angles[2]);
  }

  /* free memory in the Id accessor */
  free(sat_nom_file_model.att_data);


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_nominal_att_close                                    */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_nominal_att_close\n");

  /* Call xp_sat_nominal_att_close function */
  /* -------------------------------------- */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id,
                                    /* output */
                                    ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_sat_nominal_att_init_status(&sat_nom_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_nominal_att_init_model                               */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_nominal_att_init_model\n");

  /* Set input values */
  /* ---------------- */
  model_enum       = XP_MODEL_ENVISAT;
  model_param[0]   =  -0.1671;
  model_param[1]   =   0.0501;
  model_param[2]   =   3.9130;

  /* Call xp_sat_nominal_att_init_model function */
  /* ------------------------------------------- */
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         /* output */
                                         &sat_nom_trans_id, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id =  XP_SAT_NOMINAL_ATT_INIT_MODEL_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nSatellite Nominal Attitude Transformatiom correctly initialised");
  }

  /* Accessor functions */
 status = xp_sat_nominal_att_get_param(&sat_nom_trans_id, &param_model);
  if (status <= XP_ERR) return(XP_ERR);

  status = xp_sat_nominal_att_set_param(&sat_nom_trans_id, &param_model);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status      : %li", xp_sat_nominal_att_init_status(&sat_nom_trans_id));
  printf("\n- Init Mode        : %li", xp_sat_nominal_att_get_mode(&sat_nom_trans_id));
  printf("\n- Model Enum       : %li", param_model.model_enum);
  printf("\n- Model Param      : [%12.9lf,%12.9lf,%12.9lf]",
          param_model.model_param[0], 
          param_model.model_param[1],
          param_model.model_param[2]);


  /* ------------------------------------------------------------------------ */
  /* Satellite Transformations                                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_att_matrix_init                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_att_matrix_init\n");

  /* Set input values */
  /* ---------------- */
  att_matrix[0][0] =  1.0;
  att_matrix[0][1] =  0.0;
  att_matrix[0][2] =  0.0;
  att_matrix[1][0] =  0.0;
  att_matrix[1][1] =  1.0;
  att_matrix[1][2] =  0.0;
  att_matrix[2][0] =  0.0;
  att_matrix[2][1] =  0.0;
  att_matrix[2][2] =  1.0;

  /* Call xp_sat_att_matrix_init  function */
  /* ------------------------------------- */
  status = xp_sat_att_matrix_init(att_matrix,
                                  /* output */
                                  &sat_trans_id,
                                  ierr); 

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_SAT_ATT_MATRIX_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nSatellite Attitude Transformatiom correctly initialised");
  }

  printf("\n- Init Status      : %li",xp_sat_att_init_status(&sat_trans_id));
  printf("\n- Init Mode        : %li",xp_sat_att_get_mode(&sat_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_att_close                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_att_close\n");

  /* Call xp_sat_att_close function */
  /* ------------------------------ */
  status = xp_sat_att_close(&sat_trans_id,
                            /* output */
                            ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_SAT_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_sat_att_init_status(&sat_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_att_angle_init                                       */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_att_angle_init\n");

  /* Set input values */
  /* ---------------- */
  ang[0] =  0.1;
  ang[1] =  0.2;
  ang[2] = -0.3;

  /* Call xp_sat_att_angle_init  function */
  /* ------------------------------------ */
  status = xp_sat_att_angle_init(ang,
                                 /* output */
                                 &sat_trans_id,
                                 ierr); 

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_SAT_ATT_ANGLE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nSatellite Attitude Transformatiom correctly initialised");
  }

  /* Accessor functions */
  status = xp_sat_att_get_angles(&sat_trans_id, &angle_model);
  if (status <= XP_ERR) return(XP_ERR);

  status = xp_sat_att_set_angles(&sat_trans_id, &angle_model);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status    : %li", xp_sat_att_init_status(&sat_trans_id));
  printf("\n- Init Mode      : %li", xp_sat_att_get_mode(&sat_trans_id));
  printf("\n- Angles         : Pitch = %12.9lf, Roll = %12.9lf, Yaw = %12.9lf]",
          angle_model.pitch, angle_model.roll, angle_model.yaw);


  /* ------------------------------------------------------------------------ */
  /* Instrument Transformations                                               */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_instr_att_init_harmonic                                  */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_instr_att_init_harmonic\n");

  /* Set input values */
  /* ---------------- */
  angle_type = XP_ANGLE_TYPE_TRUE_LAT_TOD;
  num_terms[0]  = 2;
  num_terms[1]  = 2;
  num_terms[2]  = 2;
  harmonic_type_pitch[0]=0;
  harmonic_type_pitch[1]=0;
  harmonic_type_roll[0]=0;
  harmonic_type_roll[1]=0;
  harmonic_type_yaw[0]=0;
  harmonic_type_yaw[1]=0;
  harmonic_coef_pitch[0]=0.0;
  harmonic_coef_pitch[1]=0.0;
  harmonic_coef_roll[0]=0.0;
  harmonic_coef_roll[1]=0.0;
  harmonic_coef_yaw[0]=0.0;
  harmonic_coef_yaw[1]=0.0;
  offset[0] = 1.0;
  offset[1] = -1.0;
  offset[2] = 0.0;

  /* Call xp_instr_att_init_harmonic function */
  /* ---------------------------------------- */
  status = xp_instr_att_init_harmonic(&angle_type, num_terms,
                                      harmonic_type_pitch,
                                      harmonic_type_roll,
                                      harmonic_type_yaw,
                                      harmonic_coef_pitch,
                                      harmonic_coef_roll,
                                      harmonic_coef_yaw,
                                      offset,
                                      /* output */
                                      &instr_trans_id,
                                      ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_INSTR_ATT_INIT_HARMONIC_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nInstrument Attitude Transformatiom correctly initialised");
  }

  /* Accessor functions */
  status = xp_instr_att_get_harmonic(&instr_trans_id, &harmo_model);
  if (status <= XP_ERR) return(XP_ERR);

  status = xp_instr_att_set_harmonic(&instr_trans_id, &harmo_model);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status      : %li",xp_instr_att_init_status(&instr_trans_id));
  printf("\n- Init Mode        : %li",xp_instr_att_get_mode(&instr_trans_id));
  printf("\n- Angle Type       : %li", harmo_model.angle_type);
  for (i = 0; i < harmo_model.harmonic.num_terms[0]; i++)
  {
    printf("\n- Pitch Type       : %li", harmo_model.harmonic.harmonic_type_pitch[i]);
    printf("\n- Pitch Coef       : %lf", harmo_model.harmonic.harmonic_coef_pitch[i]);
  }
  for (i = 0; i < harmo_model.harmonic.num_terms[1]; i++)
  {
    printf("\n- Roll Type       : %li", harmo_model.harmonic.harmonic_type_roll[i]);
    printf("\n- Roll Coef       : %lf", harmo_model.harmonic.harmonic_coef_roll[i]);
  }
  for (i = 0; i < harmo_model.harmonic.num_terms[2]; i++)
  {
    printf("\n- Yaw Type       : %li", harmo_model.harmonic.harmonic_type_yaw[i]);
    printf("\n- Yaw Coef       : %lf", harmo_model.harmonic.harmonic_coef_yaw[i]);
  }

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_instr_att_close                                          */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_instr_att_close\n");

  /* Call xp_instr_att_close function */
  /* -------------------------------- */
  status = xp_instr_att_close(&instr_trans_id,
                              /* output */
                              ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_INSTR_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_instr_att_init_status(&instr_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_instr_att_angle_init                                       */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_instr_att_angle_init\n");

  /* Set input values */
  /* ---------------- */
  ang[0] =  0.0;
  ang[1] =  0.0;
  ang[2] =  0.0;

  offset[0] = 0.0;
  offset[1] = 0.0;
  offset[2] = 0.0;

  /* Call xp_instr_att_angle_init  function */
  /* -------------------------------------- */
  status = xp_instr_att_angle_init(ang, offset,
                                   /* output */
                                   &instr_trans_id,
                                   ierr); 

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_INSTR_ATT_ANGLE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nInstrument Attitude Transformation correctly initialised");
  }

  /* Accessor functions */
  status = xp_instr_att_get_angles(&instr_trans_id, &angle_model);
  if (status <= XP_ERR) return(XP_ERR);

  status = xp_instr_att_set_angles(&instr_trans_id, &angle_model);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status    : %li", xp_instr_att_init_status(&instr_trans_id));
  printf("\n- Init Mode      : %li", xp_instr_att_get_mode(&instr_trans_id));
  printf("\n- Angles         : Pitch = %12.9lf, Roll = %12.9lf, Yaw = %12.9lf]",
          angle_model.pitch, angle_model.roll, angle_model.yaw);



/******************************************************************************/
/*                                                                            */
/* Attitude calculation functions                                             */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_attitude_init                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_attitude_init\n");

  /* Call xp_attitude_init function */
  /* ------------------------------ */
  status = xp_attitude_init (/* output */
                             &attitude_id_2,
                             ierr);
  
  /* Print output values */
  /* ------------------- */
  
  if (status != XP_OK)
    {
     func_id = XP_ATTITUDE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nAttitude correctly initialised");
  }

  printf("\n- Init Status      : %li",xp_attitude_init_status(&attitude_id_2));
  printf("\n- Init Mode        : %li",xp_attitude_get_mode(&attitude_id_2));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_attitude_compute                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_attitude_compute\n");

  /* Set input values */
  /* ---------------- */
  time_ref      = XL_TIME_UT1;
  time          = 255.3456;
  pos_2[0]        =  4859964.138;
  pos_2[1]        = -5265612.059;
  pos_2[2]        =        0.002;
  vel_2[0]        =    -1203.303801;
  vel_2[1]        =    -1098.845511;
  vel_2[2]        =     7377.224410;
  acc_2[0]        =        0.0;
  acc_2[1]        =        0.0;
  acc_2[2]        =        0.0;

  target_frame  = XP_INSTR_ATT;

  /* Call xp_attitude_compute function */
  /* ----------------------------- */
  status = xp_attitude_compute(&model_id, &time_id,
                               &sat_nom_trans_id,
                               &sat_trans_id,
                               &instr_trans_id,
                               &attitude_id_2,
                               &time_ref, &time,
                               pos_2, vel_2, acc_2, 
                               &target_frame,
                               /* output */
                               ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_ATTITUDE_COMPUTE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }else {
     printf("\nAttitude correctly calculated");
  }


  /* Call to accessor functions */
  status = xp_attitude_get_id_data(&attitude_id_2, &attitude_data);
  printf("\n- Init Status      : %li",xp_attitude_init_status(&attitude_id_2));
  printf("\n- Init Mode        : %li",xp_attitude_get_mode(&attitude_id_2));
  printf("\n- Model            : %li", attitude_data.model);
  printf("\n- Time Reference   : %li", attitude_data.time_ref);
  printf("\n- Time             : %lf", attitude_data.time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]", 
          attitude_data.sat_vector.v[0], 
          attitude_data.sat_vector.v[1], 
          attitude_data.sat_vector.v[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",
          attitude_data.sat_vector.vd[0], 
          attitude_data.sat_vector.vd[1], 
          attitude_data.sat_vector.vd[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",
          attitude_data.sat_vector.v2d[0], 
          attitude_data.sat_vector.v2d[1], 
          attitude_data.sat_vector.v2d[2]);
  printf("\n- Source frame     : %lf", attitude_data.source_frame);  
  printf("\n- Target frame     : %lf", attitude_data.target_frame);
  printf("\n- Attitude Matrix  : %lf\t%lf%lf", 
          attitude_data.sat_mat.m[0][0], 
          attitude_data.sat_mat.m[0][1], 
          attitude_data.sat_mat.m[0][2]);
  printf("\n                     %lf\t%lf%lf", 
          attitude_data.sat_mat.m[1][0], 
          attitude_data.sat_mat.m[1][1], 
          attitude_data.sat_mat.m[1][2]);
  printf("\n                     %lf\t%lf%lf", 
          attitude_data.sat_mat.m[2][0], 
          attitude_data.sat_mat.m[2][1], 
          attitude_data.sat_mat.m[2][2]);


  /* Attitude data generation: quaternions/angles */
  /*----------------------------------------------*/
  
  /* Get attitude angles */
  data_type       = XD_ATT_ANGLES;
  source_ref_type = XP_FRAME_FLAG_EXT;
  source_ref      = XL_GM2000;  
  status = xp_get_attitude_data(&attitude_id_2, 
                                &data_type,
                                &source_ref_type,
                                &source_ref,
                                &att_rec,
                                ierr);
  if (status != XP_OK)
  {
     func_id = XP_GET_ATTITUDE_DATA_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);
  }
  else 
  {
     printf("\nAttitude angles correctly calculated:\n");
     printf("   - time   = %lf\n", att_rec.time);
     printf("   - angles = %lf, %lf, %lf\n", 
            att_rec.data[0], att_rec.data[1], att_rec.data[2]);
  }

  /* Get attitude quaternions along an interval */
  att_def.type = XP_SAT_ATT;
  att_def.sat_nom_trans_id     = sat_nom_trans_id;
  att_def.sat_trans_id         = sat_trans_id;
  att_def.instr_trans_id.ee_id = NULL;
  
  time_step = 10;
  time_interval.tstart.type     = XO_TIME_TYPE;
  time_interval.tstart.time_ref = XO_TIME_UTC;
  time_interval.tstart.time     = 3000;
  time_interval.tstop.type      = XO_TIME_TYPE;
  time_interval.tstop.time_ref  = XO_TIME_UTC;
  time_interval.tstop.time      = 3000.14;
  data_type = XD_ATT_QUATERNIONS;

  status = xp_gen_attitude_data(&orbit_id, 
                                &att_def,
                                &time_interval,
                                &time_step,
                                &data_type, 
                                &source_ref_type,
                                &source_ref,
                                &att_file,
                                ierr);
  if (status != XP_OK)
  {
     func_id = XP_GEN_ATTITUDE_DATA_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);
  }
  else 
  {
     printf("\nAttitude Quaternions correctly calculated. Number of records = %ld:\n",
            att_file.num_rec);
  }


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
  if (status != XP_OK)
  {
     func_id = XP_GEN_ATTITUDE_FILE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);
  }
  else 
  {
     printf("\nAttitude Quaternion file created correctly in: %s:\n",
            out_att_file);
  }

  
  
/******************************************************************************/
/*                                                                            */
/* Atmosphere and DEM initialization functions                                */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Atmosphere initialization                                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_atmos_init                                               */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_ATMOS_INIT\n");

  /* Set input values */
  /* ---------------- */
  atmos_mode  =  XP_LUT_INIT;
  atmos_model =  0;             /*dummy*/
  strcpy (atmos_file, "../data/xp_atmo_converter_coefs.out");

  /* Call xp_atmos_init function */
  /* --------------------------- */
  status = xp_atmos_init(&atmos_mode, &atmos_model, atmos_file,
                         &atmos_id, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_ATMOS_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }{
     printf("\nAtmospheric model correctly initialised");
  }

  /* Call to accessor functions */
  status = xp_atmos_get_id_data(&atmos_id, &atmos_data);

  printf("\n- Init Status      : %li",xp_atmos_init_status(&atmos_id));
  printf("\n- Init Mode        : %li",xp_atmos_get_mode(&atmos_id));
  printf("\n- Std. Atm. geometric altitude: %f", atmos_data.atm_max_alt_std);
  printf("\n- user.Atm. geometric altitude: %f", atmos_data.atm_max_alt_user);

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_atmos_close                                              */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_atmos_close\n");

  /* Call xp_atmos_close function */
  /* ---------------------------- */
  status = xp_atmos_close(&atmos_id,
                          /* output */
                          ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_ATMOS_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_atmos_init_status(&atmos_id));

/******************************************************************************/
/*                                                                            */
/* Target pointing functions                                                  */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_inter                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_INTER\n");

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_attitude_init                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_attitude_init\n");

  /* Call xp_attitude_init function */
  /* ------------------------------ */
  status = xp_attitude_init (/* output */
                             &attitude_id,
                             ierr);
  
  /* Print output values */
  /* ------------------- */
  
  if (status != XP_OK)
    {
     func_id = XP_ATTITUDE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nAttitude correctly initialised");
  }

  printf("\n- Init Status      : %li",xp_attitude_init_status(&attitude_id));
  printf("\n- Init Mode        : %li",xp_attitude_get_mode(&attitude_id));

  /* Set input values */
  /* ---------------- */
  time_ref      = XL_TIME_UTC;
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

  target_frame  = XP_INSTR_ATT;

  /* Call xp_attitude_compute function */
  /* ----------------------------- */
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

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_ATTITUDE_COMPUTE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nAttitude correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_attitude_init_status(&attitude_id));
  printf("\n- Init Mode        : %li",xp_attitude_get_mode(&attitude_id));

  sat_id        = XP_SAT_ENVISAT;
  inter_flag    = XP_INTER_1ST;
  deriv         = XL_NO_DER;
  los_az        =       50.0;
  los_el        =       85.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  los_el_rate   =        1.0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_inter function */
  /* ----------------------------- */
  status =  xp_target_inter(&sat_id,
                            &attitude_id,
                            &atmos_id,
                            &dem_id,
                            &deriv, &inter_flag, &los_az, &los_el,
                            &geod_alt, &los_az_rate, &los_el_rate,
                            &iray, &freq,
                            /* output */
                            &num_user_target, &num_los_target,
                            &target_id,
                            ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_INTER_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Inter correctly calculated");
  }

  /* Get the Id. Accesor */
  status = xp_target_get_id_data(&target_id, &target_data);
  if (status <= XP_ERR) return(XP_ERR);

  printf("\n- Init Status      : %li", xp_target_status(&target_id));
  printf("\n- Init Mode        : %li", xp_target_get_mode(&target_id));
  printf("\n- Time             : %f (time ref. = %ld)", target_data.generic_data.time, target_data.generic_data.time_ref);
  printf("\n- User Target:");
  printf("\n-      Target Vector    = {%f, %f, %f} ", 
          target_data.user.target[0].tar_vector.v[0], 
          target_data.user.target[0].tar_vector.v[1],
          target_data.user.target[0].tar_vector.v[2]);
  printf("\n-      Tangent Altitude = %f ", target_data.user.target[0].z_tan.p);
  printf("\n-      Range            = %f ", target_data.user.target[0].range.p);
  printf("\n-      Target-Satellite Vector    = {%f, %f, %f} ", 
          target_data.user.target[0].tar_sat_vector.v[0], 
          target_data.user.target[0].tar_sat_vector.v[1],
          target_data.user.target[0].tar_sat_vector.v[2]);
  printf("\n-      Satellite-Target Vector    = {%f, %f, %f} ", 
          target_data.user.target[0].sat_tar_vector.v[0], 
          target_data.user.target[0].sat_tar_vector.v[1],
          target_data.user.target[0].sat_tar_vector.v[2]);
  printf("\n- Atmosphere crossed = %li ", target_data.atm_crossed);
  printf("\n- Atmos. Exit vector = {%f, %f, %f} ",
          target_data.exit_atm_vector.v[0], 
          target_data.exit_atm_vector.v[1], 
          target_data.exit_atm_vector.v[2]);

  /* free accessor */
  if (target_data.user.target != NULL)
    free(target_data.user.target);

  if (target_data.los.target != NULL)
   free(target_data.los.target);

  if (target_data.earth.target != NULL)
    free(target_data.earth.target);


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_NO_DER;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Intersection Flag: %li",inter_flag);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- LOS Elevation    : %lf",los_el);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- LOS Elev. Rate   : %lf",los_el_rate);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_ground_range                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_GROUND_RANGE\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;
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

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_GROUND_RANGE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Ground Range correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }


  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- LOS Elevation    : %lf",los_el);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- LOS Elev. Rate   : %lf",los_el_rate);
  printf("\n- Distance         : %lf",distance);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_incidence_angle                                   */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_INCIDENCE_ANGLE\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  inc_angle     =       40.0;

  /* Call xp_target_incidence_angle function */
  /* --------------------------------------- */
  status = xp_target_incidence_angle(&sat_id,
                                     &attitude_id,
                                     &dem_id,
                                     &deriv, &los_az, &inc_angle, &geod_alt, &los_az_rate,
                                     /* output */
                                     &num_user_target, &num_los_target,
                                     &target_id,
                                     ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_INCIDENCE_ANGLE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Incidence Angle correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }


  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- Incidence Angle  : %lf",inc_angle);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_range                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_RANGE\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  range         =   900000.0;
  range_rate    =       40.0;

  /* Call xp_target_range function */
  /* ----------------------------- */
  status = xp_target_range(&sat_id, 
                           &attitude_id,
                           &dem_id,
                           &deriv, &los_az,
                           &range, &geod_alt, &los_az_rate, &range_rate,
                           /* output */
                           &num_user_target, &num_los_target,
                           &target_id,
                           ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_RANGE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Range correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }


  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- Range            : %lf",range);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- Range Rate       : %lf",range_rate);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_range_rate                                        */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_RANGE_RATE\n");

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

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_RANGE_RATE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Range Rate correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }


  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- EF Range Rate    : %lf",ef_range_rate);
  printf("\n- Range            : %lf",range);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- EF Range RateRate: %lf",ef_range_rate_rate);
  printf("\n- Range Rate       : %lf",range_rate);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_tangent                                           */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_TANGENT\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  los_az        =       20.0;
  los_el        =       85.0;
  los_az_rate   =        1.0;
  los_el_rate   =        1.0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_tangent function */
  /* ------------------------------- */
  status = xp_target_tangent(&sat_id,
                             &attitude_id,
                             &atmos_id,
                             &dem_id,
                             &deriv, &los_az,
                             &los_el, &los_az_rate, &los_el_rate, &iray, &freq,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_TANGENT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Tangent correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- LOS Elevation    : %lf",los_el);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- LOS Elev. Rate   : %lf",los_el_rate);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_altitude                                          */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_ALTITUDE\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  los_az        =       20.0;
  geod_alt      =      100.0;
  los_az_rate   =        1.0;
  freq          =        1.e10;

  /* Call xp_target_altitude function */
  /* -------------------------------- */
  status = xp_target_altitude(&sat_id,
                              &attitude_id,
                              &atmos_id,
                              &dem_id,
                              &deriv, &los_az,
                              &geod_alt, &los_az_rate, &iray, &freq,
                              /* output */
                              &num_user_target, &num_los_target,
                              &target_id,
                              ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_ALTITUDE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Altitude correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- LOS Azimuth      : %lf",los_az);
  printf("\n- Geodetic Altitude: %lf",geod_alt);
  printf("\n- LOS Azimuth Rate : %lf",los_az_rate);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_star                                              */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_STAR\n");

  /* Set input values */
  /* ---------------- */
  deriv         =     XL_DER_1ST;
  star_ra       =      272.0;
  star_dec      =      -73.0;
  star_ra_rate  =        0.0;
  star_dec_rate =        0.0;
  freq          =        1.e10;

  /* Call xp_target_star function */
  /* ---------------------------- */
  status = xp_target_star(&sat_id,
                          &attitude_id_2,
                          &atmos_id,
                          &dem_id,
                          &deriv, &star_ra, &star_dec,
                          &star_ra_rate, &star_dec_rate, &iray, &freq,
                          /* output */
                          &num_user_target, &num_los_target,
                          &target_id,
                          ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_STAR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Star correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos_2[0], pos_2[1], pos_2[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel_2[0], vel_2[1], vel_2[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc_2[0], acc_2[1], acc_2[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Star R.A.        : %lf",star_ra);
  printf("\n- Star Declination : %lf",star_dec);
  printf("\n- Star R.A. Rate   : %lf",star_ra_rate);
  printf("\n- Star Declin. Rate: %lf",star_dec_rate);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Sun pointing parameters                                                  */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_tangent_sun                                                    */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_TANGENT_SUN\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_tangent_sun function */
  /* ----------------------------------- */
  status = xp_target_tangent_sun(&sat_id, 
                                 &attitude_id,
                                 &atmos_id,
                                 &dem_id,
                                 &deriv, &iray, &freq,
                                 /* output */
                                 &num_user_target, &num_los_target,
                                 &target_id,
                                 ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_TANGENT_SUN_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Tangent Sun correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Moon pointing parameters                                                 */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_tangent_moon                                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_TANGENT_MOON\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_1ST;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_moon function */
  /* --------------------- */
  status = xp_target_tangent_moon(&sat_id, 
                                  &attitude_id,
                                  &atmos_id,
                                  &dem_id,
                                  &deriv, &iray, &freq,
                                  /* output */
                                  &num_user_target, &num_los_target,
                                  &target_id,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_TANGENT_MOON_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Tangent Moon correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_1ST;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Ray Tracing Model: %li",iray);
  printf("\n- Frequency        : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);

  /* ------------------------------------------------------------------------ */
  /* Generic Target                                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_generic                                           */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_GENERIC\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;

  /* Call xp_moon function */
  /* --------------------- */
  status = xp_target_generic(&sat_id, 
                             &attitude_id,
                             &dem_id,
                             &deriv, pos_2, vel_2, acc_2,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);
  
  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_GENERIC_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Generic correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos[0], pos[1], pos[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel[0], vel[1], vel[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc[0], acc[1], acc[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos_2[0], pos_2[1], pos_2[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel_2[0], vel_2[1], vel_2[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc_2[0], acc_2[1], acc_2[2]);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.6lf,%12.6lf,%12.6lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Target Acc.      : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate_rate[0], vector_results_rate_rate[1], vector_results_rate_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_station                                           */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_STATION\n");

  /* Set input values */
  /* ---------------- */
  deriv         = XL_DER_2ND;
  geoc_long     =      315.0;
  geod_lat      =        5.0;
  geod_alt      =        0.0;
  min_link_el   =        0.0;

  /* Call xp_target_station function */
  /* ------------------------------- */
  status = xp_target_station(&sat_id,
                             &attitude_id_2,
                             &dem_id,
                             &deriv, &geoc_long,
                             &geod_lat, &geod_alt, &min_link_el,
                             /* output */
                             &num_user_target, &num_los_target,
                             &target_id,
                             ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_STATION_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Station correctly calculated");
  }

  printf("\n- Init Status      : %li",xp_target_status(&target_id));
  printf("\n- Init Mode        : %li",xp_target_get_mode(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_vector                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_extra_vector\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_vector function */
  /* ------------------------------------ */
  status = xp_target_extra_vector(&target_id,
                                  &choice, &target_type, &target_number, 
                                  /* output */
                                  vector_results,
                                  vector_results_rate,
                                  vector_results_rate_rate,
                                  ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTarget Extra Vector correctly executed");
  }

  printf("\n  INPUT");
  printf("\n- Time Reference   : %li",time_ref);
  printf("\n- Time             : %lf",time);
  printf("\n- Sat Position     : [%12.3lf,%12.3lf,%12.3lf]",pos_2[0], pos_2[1], pos_2[2]);
  printf("\n- Sat Velocity     : [%12.6lf,%12.6lf,%12.6lf]",vel_2[0], vel_2[1], vel_2[2]);
  printf("\n- Sat Acceleration : [%12.9lf,%12.9lf,%12.9lf]",acc_2[0], acc_2[1], acc_2[2]);
  printf("\n- Derivative Flag  : %li",deriv);
  printf("\n- Geocentri Long.  : %lf",geoc_long);
  printf("\n- Geodetic Lat.    : %lf",geod_lat);
  printf("\n- Geodetic Alt.    : %lf",geod_alt);
  printf("\n- Min. Link Elev.  : %lf",min_link_el);
  printf("\n  OUTPUT");
  printf("\n- Target Position  : [%12.3lf,%12.3lf,%12.3lf]",vector_results[0], vector_results[1], vector_results[2]);
  printf("\n- Target Velocity  : [%12.3lf,%12.3lf,%12.3lf]",vector_results_rate[0], vector_results_rate[1], vector_results_rate[2]);
  printf("\n- Target Acc.      : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate_rate[0], vector_results_rate_rate[1], vector_results_rate_rate[2]);
  printf("\n- Range            : %lf",vector_results[6]);
  printf("\n- Range Rate       : %lf",vector_results_rate[6]);
  printf("\n- Sat-Target LOS   : [%12.9lf,%12.9lf,%12.9lf]",vector_results[3], vector_results[4], vector_results[5]);
  printf("\n- Sat-Tar LOS Rate : [%12.9lf,%12.9lf,%12.9lf]",vector_results_rate[3], vector_results_rate[4], vector_results_rate[5]);


  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_main                                        */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_EXTRA_MAIN\n");

  /* Set input values */
  /* ---------------- */
  choice        = XP_TARG_EXTRA_AUX_ALL;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;

  /* Call xp_target_extra_main function */
  /* ---------------------------------- */
  status = xp_target_extra_main(&target_id,
                                &choice, &target_type, &target_number, 
                                /* output */
                                main_results, main_results_rate, main_results_rate_rate, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
  {
     func_id = XP_TARGET_EXTRA_MAIN_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }

  printf("\n  INPUT");
  printf("\n- Choice Flag                : %li",choice);
  printf("\n  OUTPUT");
  printf("\n- Geocentric Long.           : %lf",main_results[0]);
  printf("\n- Geocentric Lat.            : %lf",main_results[1]);
  printf("\n- Geodetic Latitude          : %lf",main_results[2]);
  printf("\n- Geodetic Altitude          : %lf",main_results[3]);
  printf("\n- Sat. to target Top. Azimuth: %lf",main_results[4]);
  printf("\n- Sat. to target Top. Elev.  : %lf",main_results[5]);
  printf("\n- Target Azimuth             : %lf",main_results[6]);
  printf("\n- Target Elevation           : %lf",main_results[7]);
  printf("\n- Topoc. Azimuth             : %lf",main_results[8]);
  printf("\n- Topoc. Elevation           : %lf",main_results[9]);
  printf("\n- Geocentric Long. rate      : %lf",main_results_rate[0]);
  printf("\n- Geocentric Lat. rate       : %lf",main_results_rate[1]);
  printf("\n- Geodetic Latitude rate     : %lf",main_results_rate[2]);
  printf("\n- Geodetic Altitude rate     : %lf",main_results_rate[3]);
  printf("\n- Sat2tar Top. Azimuth rate  : %lf",main_results_rate[4]);
  printf("\n- Sat2tar Top. Elev.rate     : %lf",main_results_rate[5]);
  printf("\n- Target Azimuth rate        : %lf",main_results_rate[6]);
  printf("\n- Target Elevation rate      : %lf",main_results_rate[7]);
  printf("\n- Topoc. Azimuth rate        : %lf",main_results_rate[8]);
  printf("\n- Topoc. Elevation rate      : %lf",main_results_rate[9]);
  printf("\n- Geocentric Long. rate rate : %lf",main_results_rate_rate[0]);
  printf("\n- Geocentric Lat. rate rate  : %lf",main_results_rate_rate[1]);
  printf("\n- Geodetic Latitude rate rate: %lf",main_results_rate_rate[2]);
  printf("\n- Geodetic Altitude rate rate: %lf",main_results_rate_rate[3]);
  printf("\n- Sat2tar Top. Azimuth rate r: %lf",main_results_rate_rate[4]);
  printf("\n- Sat2tar Top. Elev.rate rate: %lf",main_results_rate_rate[5]);
  printf("\n- Target Azimuth rate rate   : %lf",main_results_rate_rate[6]);
  printf("\n- Target Elevation rate rate : %lf",main_results_rate_rate[7]);
  printf("\n- Topoc. Azimuth rate rate   : %lf",main_results_rate_rate[8]);
  printf("\n- Topoc. Elevation rate rate : %lf",main_results_rate_rate[9]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_aux                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXP_TARGET_EXTRA_AUX\n");

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
  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
    {
      func_id = XP_TARGET_EXTRA_AUX_ID;
      xp_get_msg(&func_id, ierr, &n, msg);
      xp_print_msg(&n, msg);
      if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
    }

  printf("\n  INPUT");
  printf("\n- Choice Flag          : %li",choice);
  printf("\n  OUTPUT");
  printf("\n- Curvature Radius at target's nadir                                     = %lf", aux_results[0]);
  printf("\n- Distance: target's nadir to satellites's nadir                         = %lf", aux_results[1]);
  printf("\n- Distance target's nadir to ground track                                = %lf", aux_results[2]);
  printf("\n- Distance SSP to point in the ground track nearest to the target's nadir= %lf", aux_results[3]);
  printf("\n- MLST at target                                                         = %lf", aux_results[4]);
  printf("\n- TLST at target                                                         = %lf", aux_results[5]);
  printf("\n- RA throught the atmosphere                                             = %lf", aux_results[6]);
  printf("\n- Dec. throught the atmosphere                                           = %lf", aux_results[7]);
  printf("\n- Curvature Radius rate at target's nadir                                = %lf", aux_results_rate[0]);
  printf("\n- Distance rate: target's nadir to satellites's nadir                    = %lf", aux_results_rate[1]);
  printf("\n- Distance rate target's nadir to ground track                           = %lf", aux_results_rate[2]);
  printf("\n- Distance rate SSP to point in the ground track nearest to the target's nadir= %lf", aux_results_rate[3]);
  printf("\n- Target's nadir velocity (relative to the Earth). North                 = %lf", aux_results_rate[8]);
  printf("\n- Target's nadir velocity (relative to the Earth). East                  = %lf", aux_results_rate[9]);
  printf("\n- Target's nadir velocity (relative to the Earth). Azimuth               = %lf", aux_results_rate[10]);
  printf("\n- Target's nadir velocity (relative to the Earth). Magnitude             = %lf", aux_results_rate[11]);
  printf("\n- Curvature Radius rate rate at target's nadir                           = %lf", aux_results_rate_rate[0]);
  printf("\n- Distance rate rate: target's nadir to satellites's nadir               = %lf", aux_results_rate_rate[1]);
  printf("\n- Distance rate rate target's nadir to ground track                      = %lf", aux_results_rate_rate[2]);
  printf("\n- Distance rate rate SSP to point in the ground track nearest to the target's nadir= %lf", aux_results_rate_rate[3]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_target_to_sun                               */
  /* ------------------------------------------------------------------------ */
  printf("\n\n\nXP_TARGET_EXTRA_TARGET_TO_SUN\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_extra_main function */
  /* ---------------------------------- */
  status = xp_target_extra_target_to_sun(&target_id,
                                         &choice, &target_type, &target_number, 
                                         &iray, &freq,
                                         sun_results, sun_results_rate, sun_results_rate_rate, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
    {
      func_id = XP_TARGET_EXTRA_TARGET_TO_SUN_ID;
      xp_get_msg(&func_id, ierr, &n, msg);
      xp_print_msg(&n, msg);
      if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
    }

  printf("\n  INPUT");
  printf("\n- Choice Flag          : %li",choice);
  printf("\n- Ray Tracing Model    : %li",iray);
  printf("\n- Frequency            : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Topocentric Azimuth.       : %lf",sun_results[0]);
  printf("\n- Topocentric Elevation.     : %lf",sun_results[1]);
  printf("\n- Topocentric Azimuth rate.  : %lf",sun_results_rate[0]);
  printf("\n- Topocentric Elevation rate : %lf",sun_results_rate[1]);
  printf("\n- Topocentric Az. rate rate  : %lf",sun_results_rate_rate[0]);
  printf("\n- Topocentric Elev. rate rate: %lf",sun_results_rate_rate[1]);
  printf("\n- Tangent Altitude           : %lf",sun_results[2]);
  printf("\n- Target to sun visibility.  : %g",sun_results[3]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_target_to_moon                               */
  /* ------------------------------------------------------------------------ */
  printf("\n\n\nXP_TARGET_EXTRA_TARGET_TO_MOON\n");

  /* Set input values */
  /* ---------------- */
  choice        = XL_DER_2ND;
  target_type   = XP_USER_TARGET_TYPE;
  target_number = 0;
  iray          = XP_NO_REF_INIT;
  freq          =        1.e10;

  /* Call xp_target_extra_main function */
  /* ---------------------------------- */
  status = xp_target_extra_target_to_moon(&target_id,
                                          &choice, &target_type, &target_number, 
                                          &iray, &freq,
                                          moon_results, moon_results_rate, moon_results_rate_rate, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XP_OK)
    {
      func_id = XP_TARGET_EXTRA_TARGET_TO_MOON_ID;
      xp_get_msg(&func_id, ierr, &n, msg);
      xp_print_msg(&n, msg);
      if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
    }

  printf("\n  INPUT");
  printf("\n- Choice Flag          : %li",choice);
  printf("\n- Ray Tracing Model    : %li",iray);
  printf("\n- Frequency            : %lf",freq);
  printf("\n  OUTPUT");
  printf("\n- Topocentric Azimuth.       : %lf",moon_results[0]);
  printf("\n- Topocentric Elevation.     : %lf",moon_results[1]);
  printf("\n- Topocentric Azimuth rate.  : %lf",moon_results_rate[0]);
  printf("\n- Topocentric Elevation rate : %lf",moon_results_rate[1]);
  printf("\n- Topocentric Az. rate rate  : %lf",moon_results_rate_rate[0]);
  printf("\n- Topocentric Elev. rate rate: %lf",moon_results_rate_rate[1]);
  printf("\n- Tangent Altitude           : %lf",moon_results[2]);
  printf("\n- Target to moon visibility.  : %g",moon_results[3]);

  /* ------------------------------------------------------------------------ */
  /* Target pointing                                                          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_extra_ef                                          */
  /* ------------------------------------------------------------------------ */
  printf("\n\n\nXP_TARGET_EXTRA_EF\n");

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

  /* Print output values */
  /* ------------------- */
  if (status != XP_OK)
    {
      func_id = XP_TARGET_EXTRA_EF_TARGET_ID;
      xp_get_msg(&func_id, ierr, &n, msg);
      xp_print_msg(&n, msg);
      if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
    }

  printf("\n  INPUT");
  printf("\n- Choice flag              : %li",choice);
  printf("\n  OUTPUT");
  printf("\n- EF target to satellite range rate             : %lf", ef_target_results_rate[1]);
  printf("\n- EF target to satellite azimuth rate (TOP)     : %lf", ef_target_results_rate[2]);
  printf("\n- EF target to satellite elevation rate (TOP)   : %lf", ef_target_results_rate[3]);
  printf("\n- Satellite to EF target azimuth rate (TOP)     : %lf", ef_target_results_rate[4]);
  printf("\n- Satellite to EF target elevation rate (TOP)   : %lf", ef_target_results_rate[5]);
  printf("\n- Satellite to EF target azimuth rate (attitude): %lf", ef_target_results_rate[6]);
  printf("\n- Satellite to EF target elev. rate (attitude)  : %lf", ef_target_results_rate[7]);
  printf("\n- 2 way doppler shift of signal                 : %g",  ef_target_results_rate[0]);
  printf("\n- EF target to satellite range rate rate        : %lf", ef_target_results_rate_rate[1]);
  printf("\n- EF target to satellite az. rate rate (TOP)    : %lf", ef_target_results_rate_rate[2]);
  printf("\n- EF target to satellite elev. rate rate (TOP)  : %lf", ef_target_results_rate_rate[3]);
  printf("\n- Satellite to EF target az. rate rate (TOP)    : %lf", ef_target_results_rate_rate[4]);
  printf("\n- Satellite to EF target elev. rate rate (TOP)  : %lf", ef_target_results_rate_rate[5]);
  printf("\n- Satellite to EF target az. rate rate (att)    : %lf", ef_target_results_rate_rate[6]);
  printf("\n- Satellite to EF target elev. rate rate (att)  : %lf", ef_target_results_rate_rate[7]);


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_change_frame                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_change_frame\n");

  /* Set input values */
  /* ---------------- */
  time_ref      = XL_TIME_UT1;
  time          = 255.3456;
  /* Satellite state vector */
  cf_pos[0]        =  4859964.138;
  cf_pos[1]        = -5265612.059;
  cf_pos[2]        =        0.002;
  cf_vel[0]        =    -1203.303801;
  cf_vel[1]        =    -1098.845511;
  cf_vel[2]        =     7377.224410;
  cf_acc[0]        =        0.0;
  cf_acc[1]        =        0.0;
  cf_acc[2]        =        0.0;
  
  cf_mode = XP_MODE_FLAG_LOCATION;
  frame_flag_input = XP_FRAME_FLAG_SAT;
  frame_flag_output = XP_FRAME_FLAG_EXT;
  frame_id_input = XP_SAT_NOMINAL_ATT;
  frame_id_output = XL_TOD;
  deriv = XP_DER_2ND;

  vec_input[0]             =   6296843.841;
  vec_input[1]             =   -1397383.429;
  vec_input[2]             =   -10319300.710;
  vec_rate_input[0]        =   -152.260779;
  vec_rate_input[1]        =   -3217.355126;
  vec_rate_input[2]        =   939.545695;
  vec_rate_rate_input[0]   =   0.176318842;
  vec_rate_rate_input[1]   =   0.886385019;
  vec_rate_rate_input[2]   =   -4.762658393;

  /* Call xp_change_frame function */
  /* ----------------------------- */
  status = xp_change_frame (&sat_id, &model_id, &time_id,
                            &sat_nom_trans_id,&sat_trans_id,&instr_trans_id,
                            &cf_mode,
                            &frame_flag_input,&frame_id_input,
                            &frame_flag_output,&frame_id_output,
                            &time_ref,&time,
                            cf_pos,cf_vel,cf_acc,&deriv,
                            vec_input,vec_rate_input,vec_rate_rate_input,
                            vec_output,vec_rate_output,vec_rate_rate_output,
                            ierr);

  /* Print output values */
  /* ------------------- */
  printf("\n  INPUT VALUES:                                    "                                );
  printf("\n- Mode flag             : %ld                      ",cf_mode                        );
  printf("\n- Input frame flag      : %ld                      ",frame_flag_input               );
  printf("\n- Input frame ID        : %ld                      ",frame_id_input                 );
  printf("\n- Output frame flag     : %ld                      ",frame_flag_output              );
  printf("\n- Output frame ID       : %ld                      ",frame_id_output                );
  printf("\n- Time Reference        : %li                      ",time_ref                       );
  printf("\n- Time                  : %lf                      ",time                           );
  printf("\n- Sat Position          : [%12.3lf,%12.3lf,%12.3lf]",cf_pos[0], cf_pos[1], cf_pos[2]);
  printf("\n- Sat Velocity          : [%12.6lf,%12.6lf,%12.6lf]",cf_vel[0], cf_vel[1], cf_vel[2]);
  printf("\n- Sat Acceleration      : [%12.9lf,%12.9lf,%12.9lf]",cf_acc[0], cf_acc[1], cf_acc[2]);
  printf("\n- Input Vector          : [%12.3lf,%12.3lf,%12.2lf]",
	  vec_input[0], vec_input[1], vec_input[2]);
  printf("\n- Vector Rate           : [%12.6lf,%12.6lf,%12.6lf]",
	  vec_rate_input[0], vec_rate_input[1], vec_rate_input[2]);
  printf("\n- Vector Rate Rate      : [%12.9lf,%12.9lf,%12.9lf]",
	  vec_rate_rate_input[0], vec_rate_rate_input[1], vec_rate_rate_input[2]);
  printf("\n  OUTPUT VALUES:                                   "                                );
  printf("\n- Status ( 0 = OK)      : %ld                      ",status                         );
  printf("\n- Output Vector         : [%12.3lf,%12.3lf,%12.3lf]",
	  vec_output[0], vec_output[1], vec_output[2]);
  printf("\n- Vector Rate           : [%12.6lf,%12.6lf,%12.6lf]",
	  vec_rate_output[0], vec_rate_output[1], vec_rate_output[2]);
  printf("\n- Vector Rate Rate      : [%12.9lf,%12.9lf,%12.9lf]",
	  vec_rate_rate_output[0], vec_rate_rate_output[1], vec_rate_rate_output[2]);


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_close                                              */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_target_close\n");

  /* Call xp_target_close function */
  /* ----------------------------- */
  status = xp_target_close(&target_id,
                           /* output */
                           ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_TARGET_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_target_status(&target_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_attitude_close                                              */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_attitude_close\n");

  /* Call xp_attitude_close function */
  /* ------------------------------- */
  status = xp_attitude_close(&attitude_id,
                             /* output */
                             ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li\n",xp_attitude_init_status(&attitude_id));

  status = xp_attitude_close(&attitude_id_2,
                             /* output */
                             ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_attitude_init_status(&attitude_id_2));


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_nominal_att_close                                    */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_nominal_att_close\n");

  /* Call xp_sat_nominal_att_close function */
  /* -------------------------------------- */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id,
                                    /* output */
                                    ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_sat_nominal_att_init_status(&sat_nom_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_sat_att_close                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_sat_att_close\n");

  /* Call xp_sat_att_close function */
  /* ------------------------------ */
  status = xp_sat_att_close(&sat_trans_id,
                            /* output */
                            ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_SAT_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_sat_att_init_status(&sat_trans_id));

  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_instr_att_close                                          */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nxp_instr_att_close\n");

  /* Call xp_instr_att_close function */
  /* -------------------------------- */
  status = xp_instr_att_close(&instr_trans_id,
                              /* output */
                              ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XP_INSTR_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  } else {
     printf("\n  Memory freed successfully");
  }
  printf("\n- Init Status      : %li",xp_instr_att_init_status(&instr_trans_id));


  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_sc                                                */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_sc\n");
  
  /* ENVISAT attitude */
  model_enum = XP_MODEL_ENVISAT;
  model_param[0] = -0.1671;        
  model_param[1] =  0.0501;         
  model_param[2] =  3.9130;  
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id1, ierr);
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_INIT_MODEL_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Initialize GEO AUTO attitude */
  model_enum = XP_MODEL_GEO;
  model_param[0] = 0;        
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id2, ierr);
  
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_INIT_MODEL_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Initialize attitudes */
  status = xp_attitude_init(&attitude_id, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  status = xp_attitude_init(&attitude_id_2, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
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
                               pos, vel, acc, &target_frame, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_COMPUTE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  }
  
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
                               pos, vel, acc, &target_frame, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_COMPUTE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */

  }
  
  deriv = XL_DER_1ST;
  sat_id2 = XO_SAT_GENERIC_GEO;
  status = xp_target_sc(&sat_id, &attitude_id, &sat_id2, &attitude_id_2,
                        &deriv,
                        &num_user_target, &num_los_target,
                        &target_id, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_SC_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Call xp_target_close function */
  status = xp_target_close(&target_id,
                           /* output */
                           ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  status = xp_attitude_close(&attitude_id,
                             /* output */
                             ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  status = xp_attitude_close(&attitude_id_2,
                             /* output */
                             ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id1,
                                    /* output */
                                    ierr);
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id2,
                                    /* output */
                                    ierr);
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_inter                                               */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_inter\n");
  
  /* ENVISAT attitude */
  model_enum = XP_MODEL_ENVISAT;
  model_param[0] = -0.1671;        
  model_param[1] =  0.0501;         
  model_param[2] =  3.9130;  
    
  status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                         &sat_nom_trans_id1, ierr);
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_INIT_MODEL_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Initialize attitudes */
  status = xp_attitude_init(&attitude_id, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_INIT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
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
                               pos, vel, acc, &target_frame, ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_COMPUTE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
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
                                &target_num, &target_id, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_INTER_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  free(target_num.num_los_target);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_vector                                 */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_vector\n");
  
  choice      = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_vector(&target_id, &choice, &target_type,
                                       &vector_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_VECTOR_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",vector_list.num_rec);
  printf("\n- Target Position of first target : [%12.3lf,%12.3lf,%12.3lf]",vector_list.extra_vector_results[0].vector_results[0], vector_list.extra_vector_results[0].vector_results[1], vector_list.extra_vector_results[0].vector_results[2]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_main                                   */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_main\n");
  choice = XP_TARG_EXTRA_MAIN_ALL;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_main(&target_id, &choice, &target_type,
                                     &main_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_MAIN_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",main_list.num_rec);
  printf("\n- Geocentric Long of 1st target   : %lf",main_list.extra_main_results[0].main_results[0]);
  printf("\n- Geocentric Lat of 1st target    : %lf",main_list.extra_main_results[0].main_results[1]);
  printf("\n- Geodetic Latitude of 1st target : %lf",main_list.extra_main_results[0].main_results[2]);
  printf("\n- Geodetic Altitude of 1st target : %lf",main_list.extra_main_results[0].main_results[3]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_aux                                    */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_aux\n");
  choice = XP_TARG_EXTRA_AUX_ALL;
  target_type = XP_USER_TARGET_TYPE;
  status = xp_target_list_extra_aux(&target_id, &choice, &target_type,
                                    &aux_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_AUX_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",aux_list.num_rec);
  printf("\n- MLST at target of 1st target         = %lf", aux_list.extra_aux_results[0].aux_results[4]);
  printf("\n- TLST at target of 1st target         = %lf", aux_list.extra_aux_results[0].aux_results[5]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_ef_target                              */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_ef_target\n");
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  status = xp_target_list_extra_ef_target(&target_id, &choice, &target_type,
                                          &freq, &ef_target_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_EF_TARGET_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",ef_target_list.num_rec);
  printf("\n- EF target to satellite range rate  of 1st target          : %lf", ef_target_list.extra_ef_target_results[0].ef_target_results_rate[1]);
  printf("\n- EF target to satellite azimuth rate (TOP) of 1st target   : %lf", ef_target_list.extra_ef_target_results[0].ef_target_results_rate[2]);
  printf("\n- EF target to satellite elevation rate (TOP) of 1st target : %lf", ef_target_list.extra_ef_target_results[0].ef_target_results_rate[3]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_specular_reflection                    */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_specular_reflection\n");
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  defl_north = 0; 
  defl_east  = 0;
  status = xp_target_list_extra_specular_reflection(&target_id, &choice, &target_type,
                                                    &defl_north, &defl_east,
                                                    &spec_reflec_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_SPECULAR_REFLECT_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",spec_reflec_list.num_rec);
  printf("\n- Azimuth of the reflected point direction (Topocentric) of 1st target : %lf", spec_reflec_list.extra_spec_reflec_target_results[0].spec_reflec_results[3]);
  printf("\n- Elevation of the reflected point direction (Topocentric) of 1st target : %lf", spec_reflec_list.extra_spec_reflec_target_results[0].spec_reflec_results[4]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_target_to_moon                         */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_target_to_moon\n");
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  iray = 0; /* dummy */
  status = xp_target_list_extra_target_to_moon(&target_id, &choice, &target_type,
                                               &iray, &freq,
                                               &moon_list, ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_LIST_EXTRA_TARGET_TO_MOON_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",moon_list.num_rec);
  printf("\n- Topocentric Azimuth of 1st target       : %lf",moon_list.extra_moon_target_results[0].moon_results[0]);
  printf("\n- Topocentric Elevation of 1st target     : %lf",moon_list.extra_moon_target_results[0].moon_results[1]);
  
  /* ------------------------------------------------------------------------ */
  /* Function(s): xp_target_list_extra_target_to_sun                          */
  /* ------------------------------------------------------------------------ */
  
  printf("\n\n\nxp_target_list_extra_target_to_sun\n");
  choice = XP_DER_2ND;
  target_type = XP_USER_TARGET_TYPE;
  freq = 1.e10;
  iray = 0; /* dummy */
  status = xp_target_list_extra_target_to_sun(&target_id, &choice, &target_type,
                                              &iray, &freq,
                                              &sun_list, ierr);
  printf("\n  OUTPUT");
  printf("\n- Number of targets : %ld\n",sun_list.num_rec);
  printf("\n- Topocentric Azimuth of 1st target       : %lf",sun_list.extra_sun_target_results[0].sun_results[0]);
  printf("\n- Topocentric Elevation of 1st target     : %lf",sun_list.extra_sun_target_results[0].sun_results[1]);
  
  /* Call xp_target_close function */
  status = xp_target_close(&target_id,
                           /* output */
                           ierr);
  if (status != XL_OK)
  {
     func_id = XP_TARGET_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  status = xp_attitude_close(&attitude_id,
                             /* output */
                             ierr);
  if (status != XL_OK)
  {
     func_id = XP_ATTITUDE_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Call xp_sat_nominal_att_close function */
  status = xp_sat_nominal_att_close(&sat_nom_trans_id1,
                                    /* output */
                                    ierr);
  if (status != XL_OK)
  {
     func_id = XP_SAT_NOMINAL_ATT_CLOSE_ID;
     xp_get_msg(&func_id, ierr, &n, msg);
     xp_print_msg(&n, msg);
     if (status <= XP_ERR) return(XP_ERR);    /* CAREFUL: normal status */
  }
  
  /* Call close Ids functions */
  /* ------------------------ */

  ext_status = xo_orbit_close(&orbit_id, ierr);
  if (ext_status != XL_OK)
  {
    func_id = XO_ORBIT_CLOSE_ID;
    xo_get_msg(&func_id, ierr, &n, msg);
    xo_print_msg(&n, msg);
  }

  ext_status = xl_time_close(&time_id, ierr);
  if (ext_status != XL_OK)
  {
    func_id = XL_TIME_CLOSE_ID;
    xl_get_msg(&func_id, ierr, &n, msg);
    xl_print_msg(&n, msg);
  }
  
  ext_status = xl_model_close(&model_id, xl_ierr);
  if (ext_status != XL_OK)
  {
    func_id = XL_MODEL_CLOSE_ID;
    xl_get_msg(&func_id, ierr, &n, msg);
    xl_print_msg(&n, msg);
  }
  

/******************************************************************************/
  
   printf("\nEOCFI_POINTING EXAMPLE COMPLETED SUCCESSFULLY\n"); 

   return(XP_OK);
}

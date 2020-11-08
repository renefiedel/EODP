 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Test level  : VALIDATION
 *
 * Module      : explorer_visibility_valid.c
 * Purpose     : It runs validation tests of EXPLORER_VISIBILITY
 *
 * Reference   : Based on Envisat Mission CFI Software
 *
 * History:    +----------------------------------------------------------------------------------+
 *             | Version | Date     | Name                  | Change                              |
 *             |---------|----------|-----------------------|-------------------------------------|
 *             |    1.0  | 19/06/02 |   DEIMOS Space, S.L.  | First release from                  |
 *             |         |          |                       | Envisat                             |
 *             +----------------------------------------------------------------------------------+
 *             |    2.0  | 29/11/02 |   DEIMOS Space S.L.   | New functions added                 |
 *             |         |          |                       |  + xv_station_vis_time              |
 *             |         |          |                       |  + xv_star_vis_time                 |
 *             |         |          |                       |  + xv_drs_vis_time                  |
 *             |         |          |                       |  + xv_time_segment_not              |
 *             |         |          |                       |  + xv_time_segment_add              |
 *             |         |          |                       |  + xv_time_segment_or               |
 *             +----------------------------------------------------------------------------------+
 *             |    2.1  | 13/05/03 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             |         |          |                       | MAC OS Version                      |
 *             |         |          |                       | New functions added                 |
 *             |         |          |                       |  + xv_multizones_vis_time           |
 *             |         |          |                       |  + xv_multistations_vis_time        |
 *             |         |          |                       |  + xv_time_segment_mapping          |
 *             |         |          |                       |  + xv_orbit_extra                   |
 *             +----------------------------------------------------------------------------------+
 *             |    2.2  | 13/08/03 |   DEIMOS Space S.L.   | Pre-release                         |
 *             +----------------------------------------------------------------------------------+
 *             |    2.2  | 30/09/03 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   2.2.2 | 26/04/04 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             |         |          |                       |* Interface changed for              |
 *             |         |          |                       |   xv_time_segment_delta             |
 *             |         |          |                       |* Added Terrasar S/C                 |
 *             +----------------------------------------------------------------------------------+
 *             |    3.0  | 21/07/04 |   DEIMOS Space S.L.   | New interfaces for the              |
 *             |         |          |                       | new initialisation                  |
 *             |         |          |                       | strategy                            |
 *             +----------------------------------------------------------------------------------+
 *             |    3.1  | 13/10/04 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Use of the OEF/POF files         |
 *             |         |          |                       |    for xv_zone_vis_time             |
 *             |         |          |                       |  + Use of Swath Def. files in       |
 *             |         |          |                       |    xv_zone_vis_time                 |
 *             +----------------------------------------------------------------------------------+
 *             |    3.2  | 15/11/04 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    3.3  | 11/07/05 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       | + Use of the OEF/POF files in       |
 *             |         |          |                       |   all visibility functions          |
 *             |         |          |                       | + Use of Swath Def. Files in        |
 *             |         |          |                       |   all visibility functions          |
 *             |         |          |                       | + ENVISAT support removed           |
 *             +----------------------------------------------------------------------------------+
 *             |    3.4  | 18/11/05 |   DEIMOS Space S.L.   | Maintenance release:                |
 *             |         |          |                       | + Changes in the interface          |
 *             |         |          |                       |   of xv_swath_pos                   |
 *             +----------------------------------------------------------------------------------+
 *             |    3.5  | 26/05/06 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Thread safe library              |
 *             |         |          |                       |  + C99 compliant                    |
 *             |         |          |                       |  + Optimized libray                 |
 *             |         |          |                       |  + 64-Bits library for MACOS,       |
 *             |         |          |                       |    LINUX and SOLARIS                |
 *             +----------------------------------------------------------------------------------+
 *             |    3.6  | 24/11/06 |   DEIMOS Space S.L.   | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    3.7  | 13/07/07 |   DEIMOS Space S.L  . | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + xv_gen_scf                       |
 *             |         |          |                       |  + expcfi_check_libs                |
 *             |         |          |                       |  + xv_zone_vis_time_no_file         |
 *             |         |          |                       |  + xv_station_vis_time_no_file      |
 *             |         |          |                       |  + xv_gen_swath_no_file             |
 *             |         |          |                       |  + library version for Mac OS X     |
 *             |         |          |                       |    on Intel (32 and 64 bits)        |
 *             +----------------------------------------------------------------------------------+
 *             |  3.7.2  | 31/07/08 |   DEIMOS Space S.L  . | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Support for area/curved swath    |
 *             +----------------------------------------------------------------------------------+
 *             |    4.0  | 19/01/09 | DEIMOS Space S.L.     | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    4.1  | 07/05/10 | DEIMOS Space S.L.     | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Visib.across orbital changes     |
 *             |         |          |                       |  + AOS/LOS mask mode from GND_DB    |
 *             +----------------------------------------------------------------------------------+
 *             |    4.2  | 31/01/11 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Support for curved MLST          |
 *             |         |          |                       |  + Visibility functions adapted     |
 *             |         |          |                       |    for TLE and Precise propagator   |
 *             +----------------------------------------------------------------------------------+
 *             |    4.3  | 06/02/12 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    4.4  | 05/07/12 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + xv_sc_vis_time                   |
 *             +----------------------------------------------------------------------------------+
 *             |    4.5  | 01/03/13 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    4.6  | 03/10/13 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Support for new swath ID         |
 *             |         |          |                       |  + New functions:                   |
 *             |         |          |                       |    xv_zonevistime_compute           |
 *             |         |          |                       |    xv_stationvistime_compute        |
 *             |         |          |                       |    xv_swathpos_compute              |
 *             |         |          |                       |    xv_timesegments_xxx_compute      |
 *             +----------------------------------------------------------------------------------+
 *             |    4.7  | 28/03/14 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + New function:                    |
 *             |         |          |                       |    xv_zonevistime_coverage          |
 *             +----------------------------------------------------------------------------------+
 *             |    4.8  | 29/10/14 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |    4.9  | 23/04/15 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |  4.9.1  | 05/06/15 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   4.10  | 29/10/15 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   4.11  | 15/04/16 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   4.12  | 03/11/16 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + New functions:                   |
 *             |         |          |                       |    xv_set_sc_visibility_step        |
 *             +----------------------------------------------------------------------------------+
 *             |   4.13  | 05/04/17 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   4.14  | 16/11/17 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + Support for swath defined by     |
 *             |         |          |                       |    incidence angles                 |
 *             |         |          |                       |  + Updated generation of SCF        |
 *             +----------------------------------------------------------------------------------+
 *             |   4.15  | 20/04/18 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *             |   4.16  | 09/11/18 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             |         |          |                       | New features:                       |
 *             |         |          |                       |  + New functions:                   |
 *             |         |          |                       |     xv_celestial_body_vistime,      |
 *             |         |          |                       |     xv_compute_aoi                  |
 *             +----------------------------------------------------------------------------------+
 *             |   4.17  | 10/05/19 | DEIMOS Space S.L.U    | Maintenance release                 |
 *             +----------------------------------------------------------------------------------+
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include <explorer_visibility.h>

/* Macro definition */
/* ---------------- */

#define MAX_CONDITION			1000	/* Maximum number of checks per test case */

#define START_VALIDATION		int main(int argc, char *argv[]){ \
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

#define CHECK_STATUS(msg,stat)		if (stat < XV_OK ) { \
					  condition[checks] = XL_FALSE; \
					  printf(" ...\t%s (XL_FALSE)\n",msg); \
					}else{ \
					  condition[checks] = XL_TRUE; \
					  printf(" ...\t%s (XL_TRUE)\n",msg); \
					} \
                                        checks++;
					

#define CHECK_PAR(msg,p,p0,dp)		if((di=fabs(p-p0)) <= (th=dp)){ \
					  condition[checks] = XL_TRUE; \
					  printf(" ...\t%s (XL_TRUE)\n",msg); \
					}else{ \
					  condition[checks] = XL_FALSE; \
					  printf(" ...\t%s (XL_FALSE)\n",msg); \
					} \
					printf("\t\t Threshold  : %g\n",th); \
					printf("\t\t Difference : %g\n",di); \
					checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)	for(i=im;i<=iM;++i){ \
					  CHECK_PAR(msg,v[i],v0[i],dp); \
					}


#define END_VALIDATION			return(0); \
					}

/* xv_drsvistime max value */
#define MAX_SEGMENTS   999
#define MAX_LENGTH     256


typedef enum
{

XV_FALSE = 0,      /* False variable */
XV_TRUE = 1        /* True variable */

} XV_Boolean;

void XV_Free_segments_mem(long *num_mappings,
                          long **num_segments,
                          long **orbit_direction,
                          long ***bgn_orbit, long ***bgn_secs,
                          long ***bgn_microsecs, long ***bgn_cycle,
                          long ***end_orbit, long ***end_secs,
                          long ***end_microsecs, long ***end_cycle,
                          long ***segment_coverage);


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Validation for EXPLORER_VISIBILITY                                        */
/*                                                                           */
/* ------------------------------------------------------------------------- */

START_VALIDATION

/* Local variables definition */
/* -------------------------- */
	
   /* Earth Explorer Ids.: They should be initialized to NULL allways!!!! */
   xl_model_id    model_id    = {NULL};
   xl_time_id     time_id     = {NULL};
   xo_orbit_id    orbit_id    = {NULL};
   xp_atmos_id    atmos_id    = {NULL};
   xo_orbit_id    orbit_id1   = {NULL};
   xo_orbit_id    orbit_id2   = {NULL};
   xp_sat_nom_trans_id sat_nom_trans_id1 = {NULL};
   xp_sat_nom_trans_id sat_nom_trans_id2 = {NULL};
   xp_sat_trans_id sat_trans_id1         = {NULL};
   xp_sat_trans_id sat_trans_id2         = {NULL};
   xp_instr_trans_id instr_trans_id1     = {NULL};
   xp_instr_trans_id instr_trans_id2     = {NULL};

   long status;                         /* Main status flag */
   long local_status;
   long xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];
   long xo_ierr[XO_ERR_VECTOR_MAX_LENGTH];
   long xp_ierr[XP_ERR_VECTOR_MAX_LENGTH];
   long xv_ierr[XV_ERR_VECTOR_MAX_LENGTH];
   
   long n;								/* Number of error messages */
   long func_id;                        /* CFI function ID */
   
   char msg[XV_MAX_COD][XV_MAX_STR];    /* Error messages vector */

   long k, sat_id;

   /* xo_orbit_init_file variable declaration */
   /* --------------------------------------- */
   long time_init_mode, orbit_mode, n_files;
   char *input_files[1];
   long orbit0, orbit1;
   long time_ref_utc = XO_TIME_UTC;
   long orb_ierr[XO_ERR_VECTOR_MAX_LENGTH];
   double time0, time1, val_time0, val_time1;
   char orbit_scenario_file[XV_MAX_STR];

   /* Variables to call  xv_swathcalc  */
   /* --------------------------------------------- */
   long orbit_type, abs_orbit, second, microsec, cycle;
   double long_swath, lat_swath, alt_swath;
   long swath_pos_ierr[XV_NUM_ERR_SWATH_POS];  
   xd_stf_file stf_data;

   /* Variables to call "xv_zonevistime" */
   /* ---------------------------------- */

   long start_orbit, stop_orbit, start_cycle, stop_cycle, 
        max_segments, number_segments,
        *bgn_orbit,
        *bgn_second,
        *bgn_microsec,
        *bgn_cycle,
        *end_orbit,
        *end_second,
        *end_microsec,
        *end_cycle;
   double min_duration;
   long  swath_flag = 0;

   char zone_id[9];
   xd_zone_rec  zone_data;
   char swath_file[XV_MAX_STR], zone_db_file[XV_MAX_STR];
   long projection, zone_num;
   double zone_long[10], zone_lat[10], zone_diam;
   long *coverage, zone_vis_time_ierr[XV_NUM_ERR_ZONE_VIS_TIME];

   /* variable to call to time segments manipulation functions */
   /* -------------------------------------------------------- */
   long num_out, order_switch,
        *bgn_orbit_res,
        *bgn_secs_res,
        *bgn_microsecs_res,
        *bgn_cycle_res,
        *end_orbit_res,
        *end_secs_res,
        *end_microsecs_res,
        *end_cycle_res;
   long xv_not_ierr[XV_NUM_ERR_NOT];
   long xv_or_ierr[XV_NUM_ERR_OR];
   long xv_and_ierr[XV_NUM_ERR_AND];
   long xv_sort_ierr[XV_NUM_ERR_SORT];
   long xv_merge_ierr[XV_NUM_ERR_MERGE];
   long xv_delta_ierr[XV_NUM_ERR_DELTA];

   long order_criteria;

  double entry_delta;
  double exit_delta;


   /* variables to call to time segments mapping */
   /* ------------------------------------------ */
   long num_mappings;
   long *num_segments_map,
        *orbit_direction;
   long ** bgn_orbit_map,
        ** bgn_secs_map,
        ** bgn_microsec_map,
        ** bgn_cycle_map,
        ** end_orbit_map,
        ** end_secs_map,
        ** end_microsec_map,
        ** end_cycle_map,
        ** coverage_map;

   /* variable to call to multizones_vis_time */
   /* --------------------------------------- */
   char **m_zone_id;
   double m_zone_long[13], m_zone_lat[13], m_zone_diam[1];
   long jj, num_zones,
        m_projection[6], m_zone_num[6],
        extra_info_flag,
        * nb_zon_in_segment,
        **zones_in_segment,
        **m_coverage;
   long multizones_ierr[XV_NUM_ERR_MULTIZONES_VIS_TIME];

   /* variable to call to xv_station_vis_time */
   /* --------------------------------------- */
   char station_id[XV_MAX_STR];
   double aos_elev, los_elev;
   long mask;
   long *zdop_orb, *zdop_sec, *zdop_ms, *zdop_cyc;
   long station_err[XV_NUM_ERR_STATION_VIS_TIME];
   xd_station_rec station_data;

   /* variable to call to multistations_vis_time */
   /* ------------------------------------------ */
   char **stat_id,
        stat_file[XV_MAX_STR];
   long nb_stations;
   long mask2[7]={0};
   double aos_elevation[7]={0},
          los_elevation[7]={0};
   long *nb_stat_in_segment,
        **stat_in_segment,
        **zdop_orbit, **zdop_second,
        **zdop_microsec, **zdop_cycle;
   long multistations_err[XV_NUM_ERR_MULTISTATIONS_VIS_TIME];

   /* variables to call to orbit_extra */
   /* -------------------------------- */
   long orbit,
        num_sza;
   double sza[2];
   double orbit_info_vector[XO_ORBIT_INFO_EXTRA_NUM_ELEMENTS];
   double *sza_up, *sza_down;
   double eclipse_entry, eclipse_exit;
   double sun_moon_entry, sun_moon_exit;


   /* xl_time_ref_init variable declaration */
   /* ------------------------------------- */
   long tri_ierr[XL_NUM_ERR_TIME_REF_INIT];
   long   trif_time_model, trif_n_files, trif_time_init_mode, trif_time_ref ;
   char   *trif_time_file[1];
   double trif_time0, trif_time1, trif_val_time0, trif_val_time1;
   long   trif_orbit0, trif_orbit1;
   long   trif_ierr[XL_NUM_ERR_TIME_REF_INIT_FILE];
  
   /* Variables to call xv_gen_swath */
   /* ------------------------------ */
   char dir_name[10], sdf_name[XV_MAX_STR], stf_name[XV_MAX_STR];
   long req_orbit;
   char file_class[] = "TEST";
   long version_number = 1;
   char fh_system[] = "CFI";
   xd_sdf_file sdf;

   /* Variables to call xv_gen_scf */
   /* ------------------------------ */
   char instrum[] = "MERIS";
   char filename[XD_MAX_STR];
   xd_scf_appear *app = NULL;

   /* Variables to call xv_sc_vis_time */
   /* -------------------------------- */
   long sat_id1, sat_id2;
   long time_ref, iorb0;
   xo_ref_orbit_info ref_orbit_info;
   xo_geo_orbit_init_data geo_orbit_init;
   
   long model_enum, aocs_mode;
   double model_param[XP_NUM_MODEL_PARAM];
   double angles[3], offset[3];
   xv_link_data link_data;

   /* Variables to call xv_swath_id_init */
   /* ---------------------------------- */
   xv_swath_id                     swath_id = {NULL};
   xv_swath_info                   swath_info;
   
   /* Variables to call xv_zonevistime_compute */
   /* ---------------------------------------- */
   xp_attitude_def                 att_def = {XP_NONE_ATTITUDE, {NULL}, {NULL}, {NULL}};
   xv_zone_info_list               zone_list;
   xv_time_interval                interval;
   xv_zonevisibility_interval_list vis_list = {0, NULL};
   xv_station_info_list               sta_list;
   xv_stationvisibility_interval_list sta_vis_list = {0, NULL};
   xv_time     swathpos_time;
   xv_swath_point_list swath_point = {0, NULL};
   
   /* Variables to call xv_zonevistime_coverage */
   /* ----------------------------------------- */
   xv_zonevisibility_coverage_in zone_cov_in;
   xv_zonevisibility_coverage_out zone_cov_out;
   
   /* Set input values */
   /* ---------------- */
#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file,"../example/data/ACCEPTANCE_OSF.N1");
#else
   strcpy(orbit_scenario_file,"..\\example\\data\\ACCEPTANCE_OSF.N1");
#endif

   /* Time initialisation for following tests */
   trif_time_model     = XL_TIMEMOD_AUTO;
   trif_n_files        = 1;
   trif_time_init_mode = XL_SEL_FILE;
   trif_time_ref       = XL_TIME_UTC;
   
   trif_time_file[0] = orbit_scenario_file;
   
   status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                  &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                  &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                  &time_id, trif_ierr);
   
   if (status != XO_OK)
   {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xl_get_msg(&func_id, trif_ierr, &n, msg);
     xl_print_msg(&n, msg);
   }

  /* Orbit initialization */
  /* -------------------- */

   sat_id = XV_SAT_ENVISAT;
   time_init_mode = XO_SEL_FILE;


   input_files[0] = orbit_scenario_file;
   n_files = 1;
   orbit_mode = XO_ORBIT_INIT_OSF_MODE;
   
   status =  xo_orbit_init_file(&sat_id, &model_id, &time_id,
                                &orbit_mode, &n_files, input_files,
                                &time_init_mode, &time_ref_utc,
                                &time0, &time1, &orbit0, &orbit1,
                                &val_time0, &val_time1, &orbit_id,
                                orb_ierr);

   if (status != XO_OK)
   {
     func_id = XO_ORBIT_INIT_FILE_ID;
     xo_get_msg(&func_id, orb_ierr, &n, msg);
     xo_print_msg(&n, msg);
   }

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

   local_status = expcfi_check_libs();
   if (local_status != XV_OK)
   {
     printf("Library incompatibility.\n");
     CHECK_STATUS("Compatibility test (expcfi_check_libs)", local_status);
   }

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1
 *
 ****************************************************************************************/

START_CHECK("Check that XV_SWATH_POS status is OK")

   /* Calling xv_swath_pos */
   /* -------------------- */
   orbit_type = XV_ORBIT_ABS;
   abs_orbit = 2950;
   second = 0;
   microsec = 0;

#ifndef XL_WINDOWS
   strcpy(swath_file, "../example/data/RA_2___501_.N1");
#else
   strcpy(swath_file, "..\\example\\data\\RA_2___501_.N1");
#endif

   /* read the swath template file */
  local_status = xd_read_stf(swath_file, &stf_data, xd_ierr);
  CHECK_STATUS("xd_read_stf status", local_status);

   n = 0;
   sprintf(msg[n++], "\n\nXV_SWATH_POS\n");   
   xv_print_msg(&n, msg);

   local_status=xv_swath_pos(&orbit_id, &stf_data, 
                             &orbit_type, &abs_orbit, &second, &microsec, &cycle,
                             &long_swath, &lat_swath, &alt_swath,
                             swath_pos_ierr);
   if (local_status != XV_OK)
   {
     func_id = XV_SWATH_POS_ID;
     xv_get_msg(&func_id, swath_pos_ierr, &n, msg);
     xv_print_msg(&n, msg);
   }

   CHECK_STATUS("XV_SWATH_POS status", local_status)

   xd_free_stf(&stf_data);


END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-2
 *
 ****************************************************************************************/

START_CHECK("Check that XV_ZONE_VIS_TIME status is OK")

   /* Calling xv_zone_vis_time */
   /* ------------------------ */
   strcpy(orbit_scenario_file, "");		   
   start_orbit 	= 2900;
   stop_orbit 	= 2950;

#ifndef XL_WINDOWS
   strcpy(swath_file, "../example/data/RA_2___501_.N1");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "../example/data/MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#else
   strcpy(swath_file, "..\\example\\data\\RA_2___501_.N1");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "..\\example\\data\\MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#endif

   projection 	= 0;			
   zone_num 	= 0;				/* To be able to introduce the zone identifications */
   /* In another cases "zone_num" could have a value different from 0, i.e. "zone_num=5" and then,   
     "zone_long" and "zone_lat" could be defined as follows:
	zone_long[0]	= 0.0;
	zone_long[1]	= 20.0;
	zone_long[2]	= 20.0;
	zone_long[3]	= 0.0;
	zone_long[4]	= 0.0;
	zone_lat[0]	= 0.0;
	zone_lat[1]	= 0.0;
	zone_lat[2]	= -20.0;
	zone_lat[3]	= -20.0;
	zone_lat[4]	= 0.0;     */

   max_segments=MAX_SEGMENTS;
   min_duration = 0.0;

   n = 0;
   sprintf(msg[n++], "\n\nXV_ZONE_VIS_TIME\n");     
   xv_print_msg(&n, msg);

   local_status = xv_zone_vis_time(&orbit_id, 
				   &orbit_type, &start_orbit, &start_cycle, &stop_orbit, &stop_cycle,
				   &swath_flag, swath_file, zone_id, zone_db_file,
				   &projection, &zone_num,
				   zone_long, zone_lat, &zone_diam,
				   &min_duration,
				   &number_segments,
				   &bgn_orbit, &bgn_second, &bgn_microsec, &bgn_cycle,
				   &end_orbit, &end_second, &end_microsec, &end_cycle,
				   &coverage, zone_vis_time_ierr);

   if (local_status != XV_OK)
      {
      func_id = XV_ZONE_VIS_TIME_ID;
      xv_get_msg(&func_id, zone_vis_time_ierr, &n, msg);
      xv_print_msg(&n, msg);
      }

   CHECK_STATUS("XV_ZONE_VIS_TIME status", local_status)

END_CHECK



/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-3
 *
 ****************************************************************************************/

START_CHECK("Check that XV_TIME_SEGMENTS_NOT status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */

   order_switch=XV_TIME_ORDER;

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_NOT\n");     
   xv_print_msg(&n, msg);

   /* not function using zone_vis_time output segments as input segments */
   local_status=xv_time_segments_not( &orbit_id, 
				      &orbit_type,  &order_switch,
				      &number_segments,                                  /* input segments list */
				      bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
				      end_orbit, end_second, end_microsec, end_cycle,
				      &num_out,                                          /* output segments list */
				      &bgn_orbit_res, &bgn_secs_res, &bgn_microsecs_res, &bgn_cycle_res,
				      &end_orbit_res, &end_secs_res, &end_microsecs_res, &end_cycle_res,
				      xv_not_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_NOT_ID;
       xv_get_msg(&func_id, xv_not_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }

   CHECK_STATUS("XV_TIME_SEGMENTS_NOT status", local_status)

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

START_CHECK("Check that XV_TIME_SEGMENTS_OR status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */

   order_switch=XV_TIME_ORDER;

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_OR\n");     
   xv_print_msg(&n, msg);

   /* not function using zone_vis_time output segments as input segments */
   local_status=xv_time_segments_or (&orbit_id,
				     &orbit_type, &order_switch,
				     &number_segments,                                  /* input segments list 1*/
				     bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
				     end_orbit, end_second, end_microsec, end_cycle,
				     &number_segments,                                  /* input segments list 2*/
				     bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
				     end_orbit, end_second, end_microsec, end_cycle,
				     &num_out,                                          /* output segments list */
				     &bgn_orbit_res, &bgn_secs_res, &bgn_microsecs_res, &bgn_cycle_res,
				     &end_orbit_res, &end_secs_res, &end_microsecs_res, &end_cycle_res,
				     xv_or_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_OR_ID;
       xv_get_msg(&func_id, xv_or_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }

   CHECK_STATUS("XV_TIME_SEGMENTS_OR status", local_status)

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

START_CHECK("Check that XV_TIME_SEGMENTS_AND status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */
   order_switch=XV_TIME_ORDER;

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_AND\n");
   xv_print_msg(&n, msg);

   local_status=xv_time_segments_and (&orbit_id,
				      &orbit_type, &order_switch,
				      &number_segments,                                  /* input segments list 1*/
				      bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
				      end_orbit, end_second, end_microsec, end_cycle,
				      &number_segments,                                  /* input segments list 2*/
				      bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
				      end_orbit, end_second, end_microsec, end_cycle,
				      &num_out,                                          /* output segments list */
				      &bgn_orbit_res, &bgn_secs_res, &bgn_microsecs_res, &bgn_cycle_res,
				      &end_orbit_res, &end_secs_res, &end_microsecs_res, &end_cycle_res,
				      xv_and_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_AND_ID;
       xv_get_msg(&func_id, xv_and_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }


   CHECK_STATUS("XV_TIME_SEGMENTS_AND status", local_status)

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

START_CHECK("Check that XV_TIME_SEGMENTS_SORT status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */

   order_criteria=XV_ORBIT_REL;

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_SORT\n");     
   xv_print_msg(&n, msg);

   /* sort function using zone_vis_time output segments as input segments */
   local_status=xv_time_segments_sort(&orbit_id,
				      &orbit_type, &order_criteria,
				      &num_out,
				      bgn_orbit_res, bgn_secs_res, bgn_microsecs_res, bgn_cycle_res,
				      end_orbit_res, end_secs_res, end_microsecs_res, end_cycle_res,
				      xv_sort_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_SORT_ID;
       xv_get_msg(&func_id, xv_sort_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }

   CHECK_STATUS("XV_TIME_SEGMENTS_SORT status", local_status)

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

START_CHECK("Check that XV_TIME_SEGMENTS_MERGE status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_MERGE\n");
   xv_print_msg(&n, msg);

   orbit_type = XV_ORBIT_ABS;
   order_switch=XV_TIME_ORDER;
   
   local_status=xv_time_segments_merge (&orbit_id,
					&orbit_type, &order_switch,
					&number_segments,                     /* input segments list 1*/
					bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
					end_orbit, end_second, end_microsec, end_cycle,
					&num_out,                             /* output segments list */
					&bgn_orbit_res, &bgn_secs_res, &bgn_microsecs_res, &bgn_cycle_res,
					&end_orbit_res, &end_secs_res, &end_microsecs_res, &end_cycle_res,
					xv_merge_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_MERGE_ID;
       xv_get_msg(&func_id, xv_merge_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }

  CHECK_STATUS("XV_TIME_SEGMENTS_MERGE status", local_status)

END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-8
 *
 ****************************************************************************************/

START_CHECK("Check that XV_TIME_SEGMENTS_DELTA status is OK")

   /* Calling xv_time_segments */
   /* ------------------------ */
   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_DELTA\n");
   xv_print_msg(&n, msg);

  orbit_type=XV_ORBIT_ABS;

/*
  operation= XV_ADD;
  delta_secs=10;
  delta_microsecs=123;
*/
  entry_delta = 10.123;
  exit_delta  = 10.123;

  /* DELTA */
  local_status=xv_time_segments_delta ( &orbit_id,
                                        &orbit_type,
					&entry_delta, &exit_delta,
					&number_segments,                     /* input segments list */
					bgn_orbit, bgn_second, bgn_microsec, bgn_cycle,
					end_orbit, end_second, end_microsec, end_cycle,
					&num_out,                             /* output segments list */
					&bgn_orbit_res, &bgn_secs_res, &bgn_microsecs_res, &bgn_cycle_res,
					&end_orbit_res, &end_secs_res, &end_microsecs_res, &end_cycle_res,
					xv_delta_ierr);

   if (local_status != XV_OK)
    {
      func_id = XV_TIME_SEGMENTS_DELTA_ID;
      xv_get_msg(&func_id, xv_delta_ierr, &n, msg);
      xv_print_msg(&n, msg);
    }

  CHECK_STATUS("XV_TIME_SEGMENTS_DELTA status", local_status)

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-9
 *
 ****************************************************************************************/

START_CHECK("Check that XV_MULTIZONES_VIS_TIME status is OK")

   n = 0;
   sprintf(msg[n++], "\n\nXV_MULTIZONES_VIS_TIME\n");     
   xv_print_msg(&n, msg);

   orbit_type=XV_ORBIT_ABS;

   /* orbit range */
   start_orbit 	= 2900;
   stop_orbit 	= 2930;

   /* zone_id arrays */
   num_zones = 6;
   m_zone_id=(char **) malloc(num_zones * sizeof(char*));
   for (jj=0; jj<num_zones; jj++)
     {
       m_zone_id[jj]=(char*) malloc(9 * sizeof(char));
     }
   
   min_duration = 0.0;
   extra_info_flag = XV_TRUE;

   /* zone definition */
   /* --------------- */
   /* zone 0*/
   m_projection[0]= XD_READ_DB;			
   m_zone_num[0] 	= 0;		
   strcpy(m_zone_id[0], "ZANA____");

   /* zone 1*/
   m_projection[1]= XD_RECTANGULAR;
   m_zone_num[1] 	= 4;
   strcpy(m_zone_id[1],"rect1");
   m_zone_long[0]	= 0.0;
   m_zone_long[1]	= 20.0;
   m_zone_long[2]	= 20.0;
   m_zone_long[3]	= 0.0;
   m_zone_lat[0]	= 0.0;
   m_zone_lat[1]	= 0.0;
   m_zone_lat[2]	= -20.0;
   m_zone_lat[3]	= -20.0;

   /* zone 2*/
   m_projection[2]= XD_RECTANGULAR;
   m_zone_num[2] 	= 4;  
   strcpy(m_zone_id[2],"rect2");
   m_zone_long[4]	= 10.0;
   m_zone_long[5]	= 30.0;
   m_zone_long[6]	= 30.0;
   m_zone_long[7]	= 10.0;
   m_zone_lat[4]	= 0.0;
   m_zone_lat[5]	= 0.0;
   m_zone_lat[6]	= -20.0;
   m_zone_lat[7]	= -20.0;

   /* zone 3*/
   m_projection[3]= XD_RECTANGULAR;
   m_zone_num[3] 	= 4;
   strcpy(m_zone_id[3],"rect3");
   m_zone_long[8]	= 0.0;
   m_zone_long[9]	= 20.0;
   m_zone_long[10]= 20.0;
   m_zone_long[11]= 0.0;
   m_zone_lat[8]	= 20.0;
   m_zone_lat[9]	= 20.0;
   m_zone_lat[10]	= 0.0;
   m_zone_lat[11]	= 0.0;

  /* m_zone 4: circular zone*/
   m_projection[4]= XD_RECTANGULAR;
   m_zone_num[4] 	= 1;				
   strcpy(m_zone_id[4],"circle"); 
   m_zone_long[12]= 0.0;
   m_zone_lat[12]	= 20.0;
   m_zone_diam[0] = 20000;

  /* zone 5*/
   m_projection[5]= XD_READ_DB;			
   m_zone_num[5]  = 0;
   strcpy(m_zone_id[5], "ZANA____");

   local_status=xv_multizones_vis_time( &orbit_id, &orbit_type, 
					&start_orbit, &start_cycle,
					&stop_orbit, &stop_cycle,
					&swath_flag, swath_file, &num_zones,
					m_zone_id, zone_db_file,
					m_projection, m_zone_num,
					m_zone_long, m_zone_lat,
					m_zone_diam, &min_duration,
					&extra_info_flag,
					&number_segments,
					&bgn_orbit, &bgn_second, 
					&bgn_microsec, &bgn_cycle,
					&end_orbit, &end_second, 
					&end_microsec, &end_cycle,
					&nb_zon_in_segment,
					&zones_in_segment, &m_coverage,
					multizones_ierr);

   CHECK_STATUS("XV_MULTIZONES status", local_status)

END_CHECK


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-10
 *
 ****************************************************************************************/

START_CHECK("Check that XV_GEN_SCF status is OK")

   n = 0;
   sprintf(msg[n++], "\n\nXV_GEN_SCF\n");     
   xv_print_msg(&n, msg);

   app = malloc(number_segments * sizeof(xd_scf_appear));

   /* Set the appearance for the segments:
      odd and even segments will have different appearance */
   for (jj = 0; jj < number_segments; jj++)
   {
     if (jj % 2)
     {
       app[jj].colour  = 0XFF0000;
       app[jj].draw    = 1; 
       app[jj].fill    = 2; 
       app[jj].opacity = 4;
     }
     else
     {
       app[jj].colour  = 0XFFFFFF;
       app[jj].draw    = 0;
       app[jj].fill    = 0;
       app[jj].opacity = 5;
     }
   }

   strcpy ( dir_name, "." );
   strcpy ( filename, "SCF_from_multizones.EEF" );

   local_status = xv_gen_scf(&orbit_id, instrum, &number_segments,
                             bgn_orbit, bgn_second, bgn_microsec,
                             end_orbit, end_second, end_microsec,
                             app,
                             dir_name, filename,
                             file_class, &version_number, fh_system,
                             xv_ierr);
  CHECK_STATUS("xv_gen_scf status", local_status);

  /* free memory */
  /* ----------- */

  free (app);

  for (jj=0; jj<num_zones; jj++)
  {
    free(m_zone_id[jj]);
  }
  free(m_zone_id);

  free(bgn_orbit);
  free(bgn_second);
  free(bgn_microsec);
  free(bgn_cycle);
  free(end_orbit);
  free(end_second);
  free(end_microsec);
  free(end_cycle);

  for (jj=0; jj<nb_zon_in_segment[jj]; jj++)
  {
    free (zones_in_segment[jj]);
    free (m_coverage[jj]);
  }
  free (zones_in_segment);
  free (m_coverage);
  free (nb_zon_in_segment);



END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-11
 *
 ****************************************************************************************/

START_CHECK("Check that XV_STATION_VIS_TIME status is OK")
  /* Input data */
  /* ---------- */
  orbit_type=XV_ORBIT_ABS;
  strcpy(station_id, "GKOUROUS");

  /* orbit range */
  start_orbit 	= 2900;
  stop_orbit 	= 2910;

  /*files*/
#ifndef XL_WINDOWS
  strcpy (stat_file, "../example/data/STATION_DB");
#else
  strcpy (stat_file, "..\\example\\data\\STATION_DB");
#endif

  /* other inputs*/
  min_duration = 0.0;
  aos_elev = 0;
  los_elev = 0;
  mask = XV_COMBINE;

  n = 0;
  sprintf(msg[n++], "\n\nXV_STATION_VIS_TIME\n");     
  xv_print_msg(&n, msg);

  local_status = xv_station_vis_time( &orbit_id,
                                      &orbit_type, 
                                      &start_orbit, &start_cycle,
                                      &stop_orbit, &stop_cycle,
                                      &swath_flag, swath_file,
                                      station_id, stat_file, &mask,
                                      &aos_elev, &los_elev,
                                      &min_duration,
                                      /* outputs */
                                      &number_segments,
                                      &bgn_orbit, &bgn_second,   &bgn_microsec,  &bgn_cycle,
                                      &end_orbit, &end_second,   &end_microsec,  &end_cycle,
                                      &zdop_orb,  &zdop_sec,     &zdop_ms,       &zdop_cyc,
                                      station_err);
  CHECK_STATUS("XV_MULTISTATIONS_VIS_TIME status", local_status);

  if (local_status != XV_OK)
  {
    func_id = XV_STATION_VIS_TIME_ID;
    xv_get_msg(&func_id, station_err, &n, msg);
    xv_print_msg(&n, msg);
  }

  /* free memory */
  /* ----------- */
  free(bgn_orbit); free(bgn_second); free(bgn_microsec); free(bgn_cycle);
  free(end_orbit); free(end_second); free(end_microsec); free(end_cycle);
  free(zdop_orb);  free(zdop_sec);   free(zdop_ms);      free(zdop_cyc);

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

START_CHECK("Check that XV_MULTISTATIONS_VIS_TIME status is OK")

   n = 0;
   sprintf(msg[n++], "\n\nXV_MULTISTATIONS_VIS_TIME\n");     
   xv_print_msg(&n, msg);


  /* Input data */
  /* ---------- */
  orbit_type=XV_ORBIT_ABS;

  /* orbit range */
  start_orbit 	= 2900;
  stop_orbit 	= 2910;

  /* stat_id arrays */
  nb_stations = 7;
  stat_id=(char **) malloc(nb_stations * sizeof(char*));
  for (jj=0; jj<nb_stations; jj++)
    {
       stat_id[jj]=(char*) malloc(9 * sizeof(char));
    }

  /* stations */
  strcpy( stat_id[0], "GKOUROUS");
  strcpy( stat_id[1], "GMASPABX");
  strcpy( stat_id[2], "GVILFRBX");
  strcpy( stat_id[3], "GKIRUNBX");
  strcpy( stat_id[4], "GFAIRBHX");
  strcpy( stat_id[5], "GPERTH_S");   
  strcpy( stat_id[6], "GSPIA__D");   

  /*files*/
#ifndef XL_WINDOWS
  strcpy(orbit_scenario_file,"../example/data/ACCEPTANCE_OSF.N1");
  strcpy (stat_file, "../example/data/STATION_DB");
#else
  strcpy(orbit_scenario_file,"..\\example\\data\\ACCEPTANCE_OSF.N1");
  strcpy (stat_file, "..\\example\\data\\STATION_DB");
#endif

  /* other inputs*/
  min_duration = 0.0;
  extra_info_flag = XV_TRUE;

  local_status = xv_multistations_vis_time( &orbit_id, &orbit_type, 
					    &start_orbit, &start_cycle,
					    &stop_orbit, &stop_cycle,
					    &swath_flag, swath_file, &nb_stations,
					    stat_file, stat_id,
					    aos_elevation, los_elevation,
					    mask2, 
					    &min_duration,
					    &extra_info_flag,
					    /* outputs */
					    &number_segments,
					    &bgn_orbit, &bgn_second, 
					    &bgn_microsec, &bgn_cycle,
					    &end_orbit, &end_second, 
					    &end_microsec, &end_cycle,
					    &zdop_orbit, &zdop_second, 
					    &zdop_microsec, &zdop_cycle,
					    &nb_stat_in_segment,
					    &stat_in_segment,
					    multistations_err);
       

  /* free memory */
  /* ----------- */
  for (jj=0; jj<nb_stations; jj++)
  {
    free(stat_id[jj]);
  }
  free(stat_id);

  free(bgn_orbit);
  free(bgn_second);
  free(bgn_microsec);
  free(bgn_cycle);
  free(end_orbit);
  free(end_second);
  free(end_microsec);
  free(end_cycle);

  if (extra_info_flag==XV_TRUE)
  {
    for (jj=0; jj<number_segments; jj++)
      {
	free(zdop_orbit[jj]);
	free(zdop_second[jj]);
	free(zdop_microsec[jj]);
	if (orbit_type==XV_ORBIT_REL)
	  free(zdop_cycle[jj]);
	
	free (stat_in_segment[jj]);
      }   
  }

  free(zdop_orbit);
  free(zdop_second);
  free(zdop_microsec);
  free(zdop_cycle);

  free (stat_in_segment);
  free (nb_stat_in_segment);

  CHECK_STATUS("XV_MULTISTATIONS_VIS_TIME status", local_status)

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
START_CHECK("Check that XV_TIME_SEGMENTS_MAPPING status is OK")

   /* Calling xv_time_segments_mapping */
   /* -------------------------------- */
   strcpy(orbit_scenario_file, "");		   
   start_orbit 	= 2900;
   stop_orbit 	= 2950;

#ifndef XL_WINDOWS
   strcpy(orbit_scenario_file,"../example/data/ACCEPTANCE_OSF.N1");
   strcpy(swath_file, "../example/data/MERIS_1200");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "../example/data/MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#else
   strcpy(orbit_scenario_file,"..\\example\\data\\ACCEPTANCE_OSF.N1");
   strcpy(swath_file, "..\\example\\data\\MERIS_1200");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "..\\example\\data\\MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#endif
/*
   projection 	= 0;			
   zone_num 	= 0;
*/
   projection= XD_RECTANGULAR;
   zone_num 	= 4;

   zone_long[0]	= 0.0;
   zone_long[1]	= 0.0;
   zone_long[2]	= 30.0;
   zone_long[3]	= 30.0;
   zone_lat[0]	= 20.0;
   zone_lat[1]	= 40.0;
   zone_lat[2]	= 40.0;
   zone_lat[3]	= 20.0;

   max_segments=MAX_SEGMENTS;
   min_duration = 0.0;

   n = 0;
   sprintf(msg[n++], "\n\nXV_TIME_SEGMENTS_MAPPING\n");
   xv_print_msg(&n, msg);
   local_status = xv_time_segments_mapping(&orbit_id,
					   &orbit_type, &start_orbit, &start_cycle, &stop_orbit, &stop_cycle,
					   &swath_flag, swath_file, &zone_num, zone_id, zone_db_file,
					   &projection, &zone_diam, zone_long, zone_lat,
					   /*outpus*/
					   &num_mappings,
					   &num_segments_map,
					   &orbit_direction,
					   &bgn_orbit_map, &bgn_secs_map, &bgn_microsec_map, &bgn_cycle_map,
					   &end_orbit_map, &end_secs_map, &end_microsec_map, &end_cycle_map,
					   &coverage_map,
					   zone_vis_time_ierr);

   if (local_status != XV_OK)
     {
       func_id = XV_TIME_SEGMENTS_MAPPING_ID;
       xv_get_msg(&func_id, zone_vis_time_ierr, &n, msg);
       xv_print_msg(&n, msg);
     }

  CHECK_STATUS("XV_TIME_SEGMENTS_MAPPING status", local_status);

  XV_Free_segments_mem(&num_mappings,
                       &num_segments_map,
                       &orbit_direction,
                       &bgn_orbit_map, &bgn_secs_map,
                       &bgn_microsec_map, &bgn_cycle_map,
                       &end_orbit_map, &end_secs_map,
                       &end_microsec_map, &end_cycle_map,
                       &coverage_map);

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
START_CHECK("Check that XV_ORBIT_EXTRA status is OK")

  sat_id=XV_SAT_ENVISAT;
  
  orbit= 12426;
  num_sza=2;
  sza[0]=90;
  sza[1]=80;

  /*call to orbit_info */
  local_status = xo_orbit_info (&orbit_id,
                                &orbit,
                                orbit_info_vector, xv_ierr);
  
  if (local_status != XV_OK)
    {
      func_id = XO_ORBIT_INFO_ID;
      xv_get_msg(&func_id, zone_vis_time_ierr, &n, msg);
      xv_print_msg(&n, msg);
    }

  n = 0;
  sprintf(msg[n++], "\n\nXV_ORBIT_EXTRA\n");
  xv_print_msg(&n, msg);

  /* call to orbit_extra */
  local_status=xv_orbit_extra(&orbit_id, &orbit,
			      orbit_info_vector,
			      &num_sza, sza,
			      /*outputs*/
			      &sza_up, &sza_down, 
			      &eclipse_entry, &eclipse_exit,
			      &sun_moon_entry, &sun_moon_exit,
			      xv_ierr);

  if (local_status != XV_OK)
    {
      func_id = XV_ORBIT_EXTRA_ID;
      xv_get_msg(&func_id, zone_vis_time_ierr, &n, msg);
      xv_print_msg(&n, msg);
    }

  free (sza_up);
  sza_up = NULL;
  free (sza_down);
  sza_down = NULL;

  CHECK_STATUS("XV_ORBIT_EXTRA status", local_status);

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
START_CHECK("Check that XV_GEN_SWATH status is OK")

  /* Calling xv_genswath  */
  /* -------------------- */

   req_orbit=3000;
   strcpy ( dir_name, "." );
   strcpy(sdf_name,"../example/data/SDF_MERIS_1200pts.N1");
   strcpy(dir_name,"");
   strcpy(stf_name,"");

   n = 0;
   sprintf(msg[n++], "\n\nXV_GENSWATH\n");     
   xv_print_msg(&n, msg);

   local_status = xv_gen_swath(&orbit_id, &atmos_id,
                               &req_orbit, sdf_name, 
                               dir_name, stf_name,
                               file_class,
                               &version_number,
                               fh_system,
                               xv_ierr);

   CHECK_STATUS("xv_gen_swath status", local_status);

   if (local_status != XV_OK)
   {
      func_id = XV_GEN_SWATH_ID;
      xv_get_msg(&func_id, xv_ierr, &n, msg);
      xv_print_msg(&n, msg);
   }

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
START_CHECK("Check that XV_GEN_SWATH_NO_FILE status is OK")

   req_orbit=3000;
   strcpy(sdf_name,"../example/data/SDF_MERIS_1200pts.N1");

   n = 0;
   sprintf(msg[n++], "\n\nXV_GENSWATH_NO_FILE\n");     
   xv_print_msg(&n, msg);

   /* read the swath definition file */
   local_status = xd_read_sdf(sdf_name, &sdf, xd_ierr);
   if (local_status != XV_OK)
   {
     func_id = XD_READ_SDF_ID;
     xd_get_msg(&func_id, xd_ierr, &n, msg);
     xv_print_msg(&n, msg);
   }

  /* Calling xv_genswath_no_file  */
   local_status = xv_gen_swath_no_file(&orbit_id, &atmos_id,
                                       &req_orbit, &sdf, 
                                       &stf_data, xv_ierr);

   CHECK_STATUS("xv_gen_swath_no_file status", local_status);

   if (local_status != XV_OK)
   {
      func_id = XV_GEN_SWATH_ID;
      xv_get_msg(&func_id, xv_ierr, &n, msg);
      xv_print_msg(&n, msg);
   }

   xd_free_stf(&stf_data);
   xd_free_sdf(&sdf);

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
START_CHECK("Check that XV_ZONE_VIS_TIME_NO_FILE status is OK")

   orbit_type = XV_ORBIT_ABS;
   start_orbit 	= 2900;
   stop_orbit 	= 2950;

#ifndef XL_WINDOWS
   strcpy(swath_file, "../example/data/RA_2___501_.N1");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
	   "../example/data/MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#else
   strcpy(swath_file, "..\\example\\data\\RA_2___501_.N1");
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "..\\example\\data\\MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#endif

   projection 	= 0;			
   zone_num 	= 0;

   max_segments=MAX_SEGMENTS;
   min_duration = 0.0;


   /* read the zone */
   local_status = xd_read_zone(zone_db_file, zone_id, &zone_data, xd_ierr);
   if (local_status != XV_OK)
   {
     func_id = XD_READ_ZONE_ID;
     xd_get_msg(&func_id, xd_ierr, &n, msg);
     xv_print_msg(&n, msg);
   }

   /* read the swath template file */
   local_status = xd_read_stf(swath_file, &stf_data, xd_ierr);
   if (local_status != XV_OK)
   {
     func_id = XD_READ_STF_ID;
     xd_get_msg(&func_id, xd_ierr, &n, msg);
     xv_print_msg(&n, msg);
   }

   /* get visibility segments */
   n = 0;
   sprintf(msg[n++], "\n\nXV_ZONE_VIS_TIME_NO_FILE\n");     
   xv_print_msg(&n, msg);

   local_status = xv_zone_vis_time_no_file(&orbit_id, &orbit_type, 
                                           &start_orbit, &start_cycle,
                                           &stop_orbit, &stop_cycle,
                                           &stf_data, &zone_data,
                                           &projection, &zone_num,
                                           zone_long, zone_lat, &zone_diam,
                                           &min_duration,
                                           &number_segments,
                                           &bgn_orbit, &bgn_second, &bgn_microsec, &bgn_cycle,
                                           &end_orbit, &end_second, &end_microsec, &end_cycle,
                                           &coverage, zone_vis_time_ierr);
   CHECK_STATUS("xv_zone_vis_time_no_file status", local_status);

   if (local_status != XV_OK)
   {
     func_id = XV_ZONE_VIS_TIME_ID;
     xv_get_msg(&func_id, zone_vis_time_ierr, &n, msg);
     xv_print_msg(&n, msg);
   }

   /* free memory */
   free(bgn_orbit); free(bgn_second); free(bgn_microsec); free(bgn_cycle);
   free(end_orbit); free(end_second); free(end_microsec); free(end_cycle);
   free(coverage);

   xd_free_zone(&zone_data);

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
START_CHECK("Check that XV_STATION_VIS_TIME_NO_FILE status is OK")

  /* Input data */
  orbit_type=XV_ORBIT_ABS;
  strcpy(station_id, "GKOUROUS");

  /* orbit range */
  start_orbit 	= 2900;
  stop_orbit 	= 2910;

  /*files*/
#ifndef XL_WINDOWS
  strcpy (stat_file, "../example/data/STATION_DB");
#else
  strcpy (stat_file, "..\\example\\data\\STATION_DB");
#endif

  /* other inputs*/
  min_duration = 0.0;
  aos_elev = 0;
  los_elev = 0;
  mask = XV_COMBINE;

  n = 0;
  sprintf(msg[n++], "\n\nXV_STATION_VIS_TIME_NO_FILE\n");     
  xv_print_msg(&n, msg);

  /* Call  function: xd_read_station */
  local_status = xd_read_station (stat_file, station_id, 
                                  &station_data, xd_ierr);
  if (local_status != XV_OK)
  {
    func_id = XD_READ_STATION_ID;
    xd_get_msg(&func_id, xd_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }

  /*get visibility segments */
  local_status = xv_station_vis_time_no_file( &orbit_id, &orbit_type, 
                                              &start_orbit, &start_cycle,
                                              &stop_orbit, &stop_cycle,
                                              &stf_data, &station_data,
                                              &mask, &aos_elev, &los_elev,
                                              &min_duration,
                                              /* outputs */
                                              &number_segments,
                                              &bgn_orbit, &bgn_second,   &bgn_microsec,  &bgn_cycle,
                                              &end_orbit, &end_second,   &end_microsec,  &end_cycle,
                                              &zdop_orb,  &zdop_sec,     &zdop_ms,       &zdop_cyc,
                                              station_err);
  CHECK_STATUS("xv_station_vis_time_no_file status", local_status);
  if (local_status != XV_OK)
  {
    func_id = XV_STATION_VIS_TIME_ID;
    xv_get_msg(&func_id, station_err, &n, msg);
    xv_print_msg(&n, msg);
  }

  /* free memory */
  xd_free_stf(&stf_data);

  free(bgn_orbit); free(bgn_second); free(bgn_microsec); free(bgn_cycle);
  free(end_orbit); free(end_second); free(end_microsec); free(end_cycle);
  free(zdop_orb);  free(zdop_sec);   free(zdop_ms);      free(zdop_cyc);

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
START_CHECK("Check that XV_SC_VIS_TIME (and XV_SET_SC_VIS_TIME_STEP) status is OK")

  n = 0;
  sprintf(msg[n++], "\n\nXV_SC_VIS_TIME\n");     
  xv_print_msg(&n, msg);
  
  /* ENVISAT Orbit initialization */
  sat_id1 = XO_SAT_ENVISAT;
  time_ref = XO_TIME_UTC;
  time0 = 0.;
  iorb0 = 0;
  
  ref_orbit_info.drift_mode   = XO_NOSUNSYNC_DRIFT;
  ref_orbit_info.inclination  = 0.;
  ref_orbit_info.rep_cycle    = 35;
  ref_orbit_info.cycle_len    = 501;
  ref_orbit_info.ANX_long     = -47.2941;
  ref_orbit_info.mlst         = 22.0;
  ref_orbit_info.mlst_drift   = 0.;
  ref_orbit_info.mlst_nonlinear_drift.nof_harmonics = 0.;
  ref_orbit_info.mlst_nonlinear_drift.mlst_harmonics = NULL;
  
  local_status = xo_orbit_init_def_2(&sat_id1, &model_id, &time_id,
                                     &time_ref, &time0, &iorb0, 
                                     &ref_orbit_info,
                                     /* output */
                                     &val_time0, &val_time1,
                                     &orbit_id1, xo_ierr);
  CHECK_STATUS("xo_orbit_init_def_2 status", local_status)
  
  /* GEO Orbit initialization */
  sat_id2 = XO_SAT_GENERIC_GEO; 
  geo_orbit_init.init_type = XO_GC_LONGITUDE_ONLY;
  geo_orbit_init.geo_orbit_info.geod_coord.gc_longitude = 21.4;
  geo_orbit_init.geo_orbit_info.geod_coord.gd_latitude  = 0.; /* dummy */
  geo_orbit_init.geo_orbit_info.geod_coord.gd_altitude  = 0.; /* dummy */
  
  local_status =  xo_orbit_init_geo(&sat_id2, &model_id, &time_id,
                                    &geo_orbit_init,
                                    &val_time0, &val_time1, &orbit_id2,
                                    xo_ierr);
  CHECK_STATUS("xo_orbit_init_geo status", local_status)

  /* Initialize ENVISAT attitude: local normal pointing Yaw steering mode */
  aocs_mode = XP_AOCS_YSM;
  local_status = xp_sat_nominal_att_init(&aocs_mode,
                                         &sat_nom_trans_id1, xp_ierr);
  CHECK_STATUS("xp_sat_nominal_att_init status", local_status)
  
  /* Initialize GEO AUTO attitude */
  model_enum = XP_MODEL_GEO;
  model_param[0] = 0;        
  local_status = xp_sat_nominal_att_init_model(&model_enum, model_param,
                                               &sat_nom_trans_id2, xp_ierr);
  CHECK_STATUS("xp_sat_nominal_att_init_model status", local_status)
  
  /* Initialize satellite attitudes and instruments attitudes to identity */
  angles[0] = angles[1] = angles[2] = 0.;
  local_status = xp_sat_att_angle_init(angles, &sat_trans_id1, xp_ierr);
  CHECK_STATUS("xp_sat_att_angle_init status", local_status)
  
  local_status = xp_sat_att_angle_init(angles, &sat_trans_id2, xp_ierr);
  CHECK_STATUS("xp_sat_att_angle_init status", local_status)
  
  offset[0] = offset[1] = offset[2] = 0.;
  local_status = xp_instr_att_angle_init(angles, offset, &instr_trans_id1, xp_ierr);
  CHECK_STATUS("xp_instr_att_angle_init status", local_status)
  
  local_status = xp_instr_att_angle_init(angles, offset, &instr_trans_id2, xp_ierr);
  CHECK_STATUS("xp_instr_att_angle_init status", local_status)
  
  /* Call SC VIS TIME */
  
  /* Prepare mask: one inclusive and one exclusive masks are defined:
     o Inclusive mask: visibility if elevation <= 10 deg.
                       This mask defines a rectangular zone in elevation vs azimuth plane
                       with following points (az, el):
                       (0., 10.), (360., 10.), (360., -90.), (0.,-90.)
                       
     o Exclusive mask: forbidden area for elevation < -85 deg, azimuth from 165 deg to 185 deg.
                       This mask defines a polygon zone in elevation vs azimuth plane
                       with following points (az, el):
                       (0, -85), (165, -85.), (165., 90.), (195., 90.), (195, -85.), 
                       (360., -85.), (360., -90.), (0., -90.)
  */
  link_data.min_tg_height = 19000.; /* Minimum height set to 19 km */
  
  link_data.mask_data.incl_mask.status       = XL_TRUE;
  link_data.mask_data.incl_mask.num_mask_pt  =   4;
  link_data.mask_data.incl_mask.azimuth[0]   =   0.;
  link_data.mask_data.incl_mask.elevation[0] =  10.;
  link_data.mask_data.incl_mask.azimuth[1]   = 360.;
  link_data.mask_data.incl_mask.elevation[1] =  10.;
  link_data.mask_data.incl_mask.azimuth[2]   = 360.;
  link_data.mask_data.incl_mask.elevation[2] = -90.;
  link_data.mask_data.incl_mask.azimuth[3]   =   0.;
  link_data.mask_data.incl_mask.elevation[3] = -90.;
  
  link_data.mask_data.excl_mask.status       = XL_TRUE;
  link_data.mask_data.excl_mask.num_mask_pt  =   8;
  link_data.mask_data.excl_mask.azimuth[0]   =   0.;
  link_data.mask_data.excl_mask.elevation[0] = -85.;
  link_data.mask_data.excl_mask.azimuth[1]   = 165.;
  link_data.mask_data.excl_mask.elevation[1] = -85.;
  link_data.mask_data.excl_mask.azimuth[2]   = 165.;
  link_data.mask_data.excl_mask.elevation[2] =  90.;
  link_data.mask_data.excl_mask.azimuth[3]   = 195.;
  link_data.mask_data.excl_mask.elevation[3] =  90.;
  link_data.mask_data.excl_mask.azimuth[4]   = 195.;
  link_data.mask_data.excl_mask.elevation[4] = -85.;
  link_data.mask_data.excl_mask.azimuth[5]   = 360.;
  link_data.mask_data.excl_mask.elevation[5] = -85.;
  link_data.mask_data.excl_mask.azimuth[6]   = 360.;
  link_data.mask_data.excl_mask.elevation[6] = -90.;
  link_data.mask_data.excl_mask.azimuth[7]   =   0.;
  link_data.mask_data.excl_mask.elevation[7] = -90.;
  
  /* Complete inputs */
  orbit_type   = XV_ORBIT_ABS;
  start_orbit  = 100;
  stop_orbit   = 300;
  
  min_duration = 0.;
  
  /* Call xv_set_sc_vis_time_step to set the step for the algorithm */
  local_status = xv_set_sc_vis_time_step(&orbit_id1, 17, xv_ierr);
  CHECK_STATUS("xv_set_sc_vis_time_step", local_status);
  
  /* Call xv_sc_vis_time */
  local_status = xv_sc_vis_time(&orbit_id1, &sat_nom_trans_id1, &sat_trans_id1, &instr_trans_id1,
                                &orbit_type,
                                &start_orbit,  &start_cycle, &stop_orbit,   &stop_cycle,
                                &orbit_id2, &sat_nom_trans_id2, &sat_trans_id2, &instr_trans_id2,
                                &link_data, &min_duration,
                                /* Output */
                                &number_segments,
                                &bgn_orbit,    &bgn_second, &bgn_microsec, &bgn_cycle,
                                &end_orbit,    &end_second, &end_microsec, &end_cycle,
                                xv_ierr);
  CHECK_STATUS("xv_sc_vis_time status", local_status);
  if (local_status != XV_OK)
  {
    func_id = XV_SC_VIS_TIME_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }
  
  free(bgn_orbit); free(bgn_second); free(bgn_microsec);
  free(end_orbit); free(end_second); free(end_microsec);

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
START_CHECK("Check that XV_SWATH_ID_INIT status is OK")
  n = 0;
  sprintf(msg[n++], "\n\nXV_SWATH_ID_INIT\n");     
  xv_print_msg(&n, msg);
  
#ifndef XL_WINDOWS
   strcpy(swath_file, "../example/data/RA_2___501_.N1");
#else
   strcpy(swath_file, "..\\example\\data\\RA_2___501_.N1");
#endif

  swath_info.sdf_file = NULL;
  swath_info.stf_file = NULL;
  swath_info.nof_regen_orbits = 0;
  swath_info.filename = swath_file;
  swath_info.type = XV_FILE_STF;
  
  local_status = xv_swath_id_init(&swath_info, &atmos_id,
                                  &swath_id, xv_ierr);
  CHECK_STATUS("xv_swath_id_init status", local_status);
  
  if (local_status != XV_OK)
  {
    func_id = XV_SWATH_ID_INIT_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-22
 *
 ******************************************************************************/
START_CHECK("Check that XV_ZONEVISTIME_COMPUTE status is OK")

  n = 0;
  sprintf(msg[n++], "\n\nXV_ZONEVISTIME_COMPUTE\n");     
  xv_print_msg(&n, msg);
  
  // Time interval start
  interval.tstart.type       = XV_ORBIT_TYPE;
  interval.tstart.orbit_type = XV_ORBIT_ABS;
  interval.tstart.orbit_num  = 2900;
  
  // Time interval stop
  interval.tstop.type       = XV_ORBIT_TYPE;
  interval.tstop.orbit_type = XV_ORBIT_ABS;
  interval.tstop.orbit_num  = 2950;
  
#ifndef XL_WINDOWS
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "../example/data/MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#else
   strcpy(zone_id, "ZANA____");			
   strcpy (zone_db_file,
     "..\\example\\data\\MPL_STZ_DBTRGT19970515_120000_00000000_00000000_19950101_000000_20100101_000000.N1");
#endif

  zone_list.calc_flag = XV_COMPUTE;
  zone_list.num_rec = 1;
  zone_list.zone_info = (xv_zone_info*)malloc(sizeof(xv_zone_info));
  zone_list.zone_info->projection   = 0;
  zone_list.zone_info->min_duration = 0.0;
  zone_list.zone_info->type = XV_USE_ZONE_DB_FILE;
  zone_list.zone_info->zone_id = zone_id;
  zone_list.zone_info->zone_db_filename = zone_db_file;
  zone_list.zone_info->zone_data = NULL;
  
  att_def.type = XP_NONE_ATTITUDE;

  local_status = xv_zonevistime_compute(&orbit_id, &att_def, &swath_id,
    &zone_list, &interval,
    &vis_list, xv_ierr);
  CHECK_STATUS("xv_zonevistime_compute status", local_status);
  
  if (local_status != XV_OK)
  {
    func_id = XV_ZONEVISTIME_COMPUTE_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }
  
  /* Co not Free memory. Structs are use to test xv_zonevisibility_coverage */
  
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-23
 *
 ******************************************************************************/
START_CHECK("Check that XV_STATIONVISTIME_COMPUTE status is OK")

  n = 0;
  sprintf(msg[n++], "\n\nXV_STATIONVISTIME_COMPUTE\n");     
  xv_print_msg(&n, msg);
  
  // Time interval start
  interval.tstart.type       = XV_ORBIT_TYPE;
  interval.tstart.orbit_type = XV_ORBIT_ABS;
  interval.tstart.orbit_num  = 2900;
  interval.tstart.sec = 0;
  interval.tstart.msec = 0;
  
  // Time interval stop
  interval.tstop.type       = XV_ORBIT_TYPE;
  interval.tstop.orbit_type = XV_ORBIT_ABS;
  interval.tstop.orbit_num  = 2910;
  interval.tstop.sec = 9999999;
  interval.tstop.msec = 9999999;
  
  // Station info list
  sta_list.calc_flag = XV_DO_NOT_COMPUTE;
  sta_list.num_rec = 1;
  sta_list.station_info = (xv_station_info*)malloc(sizeof(xv_station_info));
  sta_list.station_info->type = XV_USE_STATION_FILE_AND_MASK_OVERRIDE;
  sta_list.station_info->station_id = station_id;
  sta_list.station_info->station_db_filename = stat_file;
  sta_list.station_info->default_aos = 0.;
  sta_list.station_info->default_los = 0.;
  sta_list.station_info->default_mask = 0;
  sta_list.station_info->min_duration = 0.;
  
  status = xv_stationvistime_compute(&orbit_id, &att_def, &swath_id,
                                     &sta_list, &interval,
                                     &sta_vis_list, xv_ierr);
  CHECK_STATUS("xv_stationvistime_compute status", local_status);
       
  if (local_status != XV_OK)
  {
    func_id = XV_STATIONVISTIME_COMPUTE_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }

  free(sta_list.station_info);
  
  /* Free memory */
  if (sta_vis_list.visibility_interval != NULL)
  {
    free(sta_vis_list.visibility_interval);
    sta_vis_list.visibility_interval = NULL;
  }
  
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-24
 *
 ******************************************************************************/
START_CHECK("Check that XV_SWATHPOS_COMPUTE status is OK")

  n = 0;
  sprintf(msg[n++], "\n\nXV_STATIONVISTIME_COMPUTE\n");     
  xv_print_msg(&n, msg);
  
  swathpos_time.type = XV_ORBIT_TYPE;
  swathpos_time.orbit_type = XV_ORBIT_ABS;
  swathpos_time.orbit_num = 2950;
  swathpos_time.sec = 0;
  swathpos_time.msec = 0;
  
  status = xv_swathpos_compute(&orbit_id, &swath_id, &swathpos_time,
    &swath_point, xv_ierr);
  CHECK_STATUS("xv_swathpos_compute status", local_status);
  
  if (local_status != XV_OK)
  {
    func_id = XV_SWATHPOS_COMPUTE_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }
  
  if (swath_point.swath_point != NULL)
  {
    free(swath_point.swath_point);
    swath_point.swath_point = NULL;
  }
  
END_CHECK

/*******************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-25
 *
 ******************************************************************************/
START_CHECK("Check that XV_ZONEVISTIME_COVERAGE status is OK")

  n = 0;
  sprintf(msg[n++], "\n\nXV_ZONEVISTIME_COVERAGE\n");     
  xv_print_msg(&n, msg);
  
  zone_list.zone_info->zone_data = (xd_zone_rec*)malloc(sizeof(xd_zone_rec));
  strcpy(zone_list.zone_info->zone_data[0].zone_id, "TEST");
  strcpy(zone_list.zone_info->zone_data[0].description, "description");
  strcpy(zone_list.zone_info->zone_data[0].surface, "surface");
  strcpy(zone_list.zone_info->zone_data[0].creator, "creator");
  zone_list.zone_info->type = XV_USE_ZONE_DATA;
  zone_list.zone_info->zone_data[0].zone_point = (xd_zone_point*)malloc(4*sizeof(xd_zone_point));

  zone_list.zone_info->zone_data[0].zone_type = XD_SEGMENT;
  zone_list.zone_info->zone_data[0].projection = XD_RECTANGULAR;
  zone_list.zone_info->zone_data[0].num_points = 2;
  zone_list.zone_info->zone_data[0].zone_point[0].pt_long =  20.;
  zone_list.zone_info->zone_data[0].zone_point[0].pt_lat  =  9.;
  zone_list.zone_info->zone_data[0].zone_point[1].pt_long =  20.;
  zone_list.zone_info->zone_data[0].zone_point[1].pt_lat  =  11.;
  
  zone_cov_in.type_coverage = XV_COVERAGE_FIXED_DISTANCE;
  zone_cov_in.point_geod_distance = 10.; // Kilometers
  zone_cov_in.percent_precision = 100; // dummy
  zone_cov_in.orbit_id = &orbit_id;
  zone_cov_in.attitude_def = &att_def;
  zone_cov_in.swath_id = &swath_id;
  zone_cov_in.zone_info = zone_list.zone_info;
  zone_cov_in.visibility_interval_list = &vis_list;
  
  local_status = xv_zonevistime_coverage(&zone_cov_in, &zone_cov_out, xv_ierr);
  CHECK_STATUS("xv_zonevistime_coverage status", local_status);
  
  if (local_status != XV_OK)
  {
    func_id = XV_ZONEVISTIME_COVERAGE_ID;
    xv_get_msg(&func_id, xv_ierr, &n, msg);
    xv_print_msg(&n, msg);
  }
  
  /* Free memory */
  free(zone_list.zone_info->zone_data);
  free(zone_list.zone_info);
  
  for (k = 0 ; k < vis_list.num_rec ; k ++)
  {
    free(vis_list.visibility_interval[k].zone_coverage_info_list.zone_coverage_info->zone_id);
    vis_list.visibility_interval[k].zone_coverage_info_list.zone_coverage_info->zone_id = NULL;
    free(vis_list.visibility_interval[k].zone_coverage_info_list.zone_coverage_info);
    vis_list.visibility_interval[k].zone_coverage_info_list.zone_coverage_info = NULL;
  }
  free(vis_list.visibility_interval);
  vis_list.visibility_interval = NULL;
  vis_list.num_rec = 0L;
  
  free(zone_cov_out.coverage_per_interval); 
  zone_cov_out.coverage_per_interval = NULL;
  free(zone_cov_out.coverage_by_N_intervals); 
  zone_cov_out.coverage_by_N_intervals = NULL;
  free(zone_cov_out.cumulative_coverage); 
  zone_cov_out.cumulative_coverage = NULL;
  
END_CHECK

  /* Close IDs */
  /* --------- */
  local_status = xp_sat_nominal_att_close(&sat_nom_trans_id1, xp_ierr);
  CHECK_STATUS("xp_sat_nominal_att_close status", local_status);
  
  local_status = xp_sat_nominal_att_close(&sat_nom_trans_id2, xp_ierr);
  CHECK_STATUS("xp_sat_nominal_att_close status", local_status);
  
  local_status = xp_sat_att_close(&sat_trans_id1, xp_ierr);
  CHECK_STATUS("xp_sat_att_close status", local_status);
  
  local_status = xp_sat_att_close(&sat_trans_id2, xp_ierr);
  CHECK_STATUS("xp_sat_att_close status", local_status);
  
  local_status = xp_instr_att_close(&instr_trans_id1, xp_ierr);
  CHECK_STATUS("xp_instr_att_close status", local_status);
  
  local_status = xp_instr_att_close(&instr_trans_id2, xp_ierr);
  CHECK_STATUS("xp_instr_att_close status", local_status);
  
  local_status = xv_swath_id_close(&swath_id, xv_ierr);
  CHECK_STATUS("xv_swath_id_close status", local_status);
  
  local_status = xo_orbit_close(&orbit_id1, xo_ierr);
  CHECK_STATUS("XV_ORBIT_CLOSE status", local_status);
  
  local_status = xo_orbit_close(&orbit_id2, xo_ierr);
  CHECK_STATUS("XV_ORBIT_CLOSE status", local_status);
    
  local_status = xo_orbit_close(&orbit_id, orb_ierr);
  CHECK_STATUS("XV_ORBIT_CLOSE status", local_status);

  local_status = xl_time_close(&time_id, tri_ierr);
  CHECK_STATUS("XV_TIME_CLOSE status", local_status);


printf("\nEOCFI_VISIBILITY VALIDATION COMPLETED SUCCESSFULLY\n");

END_VALIDATION


/*------------------------------------------------------------ */
/* Local functions */
void XV_Free_segments_mem(long *num_mappings,
                          long **num_segments,
                          long **orbit_direction,
                          long ***bgn_orbit, long ***bgn_secs,
                          long ***bgn_microsecs, long ***bgn_cycle,
                          long ***end_orbit, long ***end_secs,
                          long ***end_microsecs, long ***end_cycle,
                          long ***segment_coverage)
{
  
  long count;

  for (count=0; count <*num_mappings; count++)
    {
      free ((long*)(*bgn_orbit)[count]);
      free ((long*)(*bgn_secs)[count]);
      free ((long*)(*bgn_microsecs)[count]);
      if ((*bgn_cycle)!= NULL)
	free ((long*)(*bgn_cycle)[count]);
      
      free ((long*)(*end_orbit)[count]);
      free ((long*)(*end_secs)[count]);
      free ((long*)(*end_microsecs)[count]);
      if ((*end_cycle)!= NULL)
	free ((long*)(*end_cycle)[count]);

      free ((long*)(*segment_coverage)[count]);
    }
  
  free ((long*)(*num_segments));
  free ((long*)(*orbit_direction));

  free ((long**) *bgn_orbit);
  free ((long**) *bgn_secs);
  free ((long**) *bgn_microsecs);
  free ((long**) *bgn_cycle);

  free ((long**) *end_orbit);
  free ((long**) *end_secs);
  free ((long**) *end_microsecs);
  free ((long**) *end_cycle);

  free ((long**) *segment_coverage);

  *num_segments=NULL;
  *orbit_direction=NULL;
  *bgn_orbit=NULL;
  *bgn_secs=NULL;
  *bgn_microsecs=NULL;
  *bgn_cycle=NULL;
  *end_orbit=NULL;
  *end_secs=NULL;
  *end_microsecs=NULL;
  *end_cycle=NULL;
  *segment_coverage=NULL;

}
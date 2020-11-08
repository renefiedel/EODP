 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Module      : explorer_lib_c.c
 *
 * Functions   : main program (EXPLORER_LIB example) to call:
 *
 *                  o Time initialization functions
 *                    - xl_time_ref_init_file
 *                    - xl_time_ref_close
 *                    - xl_time_ref_init
 *                  o Reference system transformations
 *                    - xl_change_cart_cs
 *                    - xl_cart_to_geod
 *                    - xl_geod_to_cart
 *                    - xl_cart_to_kepl
 *                    - xl_kepl_to_cart
 *                    - xl_get_rotated_vectors
 *                    - xl_get_rotation_angles
 *                    - xl_position_on_orbit
 *                  o Geodesic functions
 *                    - xl_geod_distance
 *                  o Ephemerides functions
 *                    - xl_sun
 *                    - xl_moon
 *                    - xl_planet
 *                    - xl_star_radec
 *                  o Time transformation functions
 *                    - xl_time_transport_to_ascii
 *                    - xl_time_transport_to_transport
 *                    - xl_time_transport_to_processing
 *                    - xl_time_processing_to_ascii
 *                    - xl_time_processing_to_transport
 *                    - xl_time_processing_to_processing
 *                    - xl_time_ascii_to_ascii
 *                    - xl_time_ascii_to_transport
 *                    - xl_time_ascii_to_processing
 *                  o Other time functions
 *                    - xl_time_add
 *                    - xl_time_diff
 *                    - xl_time_obt_to_time
 *                    - xl_time_time_to_obt                  
 *
 * Purpose     : Example program to show the way to call the previous functions.
 *
 * Reference   : Based on Envisat Mission CFI Software
 *
 * History:      +----------------------------------------------------------------------------------+
 *               | Version |   Date   |       Name        | Change                                  |
 *               |----------------------------------------------------------------------------------|
 *               |    1.2  | 15/04/02 | DEIMOS Space S.L. | First version from                      |
 *               |         |          |                   | Envisat CFI                             |
 *               |----------------------------------------------------------------------------------|
 *               |    1.3  | 19/07/02 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    2.0  | 29/11/02 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | Leap Second Function                    |
 *               |         |          |                   | BOM, EOM ASCII times                    |
 *               |         |          |                   | CCSDS compact ASCII                     |
 *               +----------------------------------------------------------------------------------+
 *               |    2.0  | 10/12/02 | DEIMOS Space S.L. | Patch to solve SPRs:                    |
 *               | patch A |          |                   | - EXPCFI-SPR-007                        |
 *               |         |          |                   | - EXPCFI-SPR-008                        |
 *               |         |          |                   | - EXPCFI-SPR-009                        |
 *               |         |          |                   | - EXPCFI-SPR-010                        |
 *               +----------------------------------------------------------------------------------+
 *               |    2.0  | 16/12/02 | DEIMOS Space S.L. | Patch to solve SPRs:                    |
 *               | patch B |          |                   | - EXPCFI-SPR-014                        |
 *               |         |          |                   | - EXPCFI-SPR-015                        |
 *               |         |          |                   | - EXPCFI-SPR-016                        |
 *               |         |          |                   | - EXPCFI-SPR-017                        |
 *               +----------------------------------------------------------------------------------+
 *               |    2.1  | 13/05/03 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | MAC OS Version                          |
 *               +----------------------------------------------------------------------------------+
 *               |    2.2  | 13/08/03 | DEIMOS Space S.L. | Pre-release                             |
 *               +----------------------------------------------------------------------------------+
 *               |    2.2  | 30/09/03 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New functions added:                    |
 *               |         |          |                   |  + xl_default_sat_init                  |
 *               +----------------------------------------------------------------------------------+
 *               |   2.2.2 | 26/04/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | Added TERRASAR S/C                      |
 *               +----------------------------------------------------------------------------------+
 *               |   3.0   | 21/07/04 | DEIMOS Space S.L. | New initialization                      |
 *               |         |          |                   | strategy  (New IF)                      |
 *               +----------------------------------------------------------------------------------+
 *               |   3.1   | 13/10/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New functions:                          |
 *               |         |          |                   | + xl_get_rotation_angles                |
 *               |         |          |                   | + xl_get_rotated_vectors                |
 *               |         |          |                   | + xl_position_on_orbit                  |
 *               +----------------------------------------------------------------------------------+
 *               |   3.2   | 15/11/04 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    3.3  | 11/07/05 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   | + explorer_data_handling support        |
 *               |         |          |                   | + Id. Accessors                         |
 *               |         |          |                   | + ADM/SMOS OBT<->UTC conversion         |
 *               |         |          |                   | + ENVISAT support removed               |
 *               |         |          |                   | + New tolerances and orbital            |
 *               |         |          |                   |   parameters (METOP, ERS1, ERS2         |
 *               |         |          |                   |   Cryosat Eccentricity)                 |
 *               +----------------------------------------------------------------------------------+
 *               |    3.4  | 18/11/05 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   | + changes in xl_default_sat_init        |
 *               |         |          |                   | + New function xl_defaul_sat_close      |
 *               |         |          |                   | + EXPCFI-SPR-070 Closed                 |
 *               +----------------------------------------------------------------------------------+
 *               |    3.5  | 26/05/06 | DEIMOS Space S.L. | New features:                           |
 *               |         |          |                   |  + Thread safe library                  |
 *               |         |          |                   |  + C99 compliant                        |
 *               |         |          |                   |  + Optimized libray                     |
 *               |         |          |                   |  + 64-Bits library for MACOS,           |
 *               |         |          |                   |    LINUX and SOLARIS                    |
 *               |         |          |                   |  + New time_conv executable             |
 *               |         |          |                   |  + New satellites: SWARM & EARTHCARE    |
 *               |         |          |                   |  + xl_time_ref_init_file improved       |
 *               |         |          |                   |  + New routines:                        |
 *               |         |          |                   |     xl_star_catalog                     |
 *               |         |          |                   |     xl_radec_to_cart & xl_cart_to_radec |
 *               |         |          |                   |     xl_topocentric_to_ef                |
 *               |         |          |                   |     xl_ef_to_topocentric                |
 *               |         |          |                   |  + SPR- 075 corrected                   |
 *               +----------------------------------------------------------------------------------+
 *               |    3.6  | 24/11/06 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New Coordinate Reference Systems for |
 *               |         |          |                   |    tranformation routines: Barycentric  |
 *               |         |          |                   |    1950 and Galactic                    |
 *               |         |          |                   |  + New time format: SMOS UTC Proteus    |
 *               |         |          |                   |  + New routines:                        |
 *               |         |          |                   |     xl_euler_to_matrix                  |
 *               |         |          |                   |     xl_matrix_to_euler                  |
 *               |         |          |                   |     xl_topocentric_to_ef                |
 *               |         |          |                   |     xl_ef_to_topocentric                |
 *               |         |          |                   |     xl_radec_to_cart                    |
 *               |         |          |                   |     xl_cart_to_radec                    |
 *               |         |          |                   |     xl_star_catalog                     |
 *               +----------------------------------------------------------------------------------+
 *               |    3.7  | 13/07/07 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + expcfi_check_libs                    |
 *               |         |          |                   |  + library version for Mac OS X         |
 *               |         |          |                   |    on Intel (32 and 64 bits)            |
 *               +----------------------------------------------------------------------------------+
 *               |  3.7.2  | 31/07/08 | DEIMOS Space S.L. | Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    4.0  | 19/01/09 | DEIMOS Space S.L. | New features:                           |
 *               |         |          |                   |  + Funtion interfaces changed for model |
 *               |         |          |                   |    support                              |
 *               +----------------------------------------------------------------------------------+
 *               |    4.1  | 07/05/10 | DEIMOS Space S.L. | Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Time init with list of files         |
 *               |         |          |                   |  + Time initialization with OSF         |
 *               +----------------------------------------------------------------------------------+
 *               |    4.2  | 31/01/11 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Check and normalization of input     |
 *               |         |          |                   |    vectors and matrices                 |
 *               |         |          |                   |  + Support for curved MLST              |
 *               +----------------------------------------------------------------------------------+
 *               |    4.3  | 06/02/12 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Pseudo-EF CS added.                  |
 *               |         |          |                   |    Polar motion included in EF CS.      |
 *               |         |          |                   |  + New init function xl_time_id_init    |
 *               |         |          |                   |  + Time init. support IERS Bulletin A   |
 *               |         |          |                   |    and Bulletins A+B                    |
 *               |         |          |                   |  + New time transport formats:          |
 *               |         |          |                   |      - XL_TRANS_GENERIC_GPS             |
 *               |         |          |                   |      - XL_TRANS_GENERIC_GPS_WEEK        |
 *               +----------------------------------------------------------------------------------+
 *               |    4.4  | 05/07/12 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New non-iterative method to compute  |
 *               |         |          |                   |    transformation from cartesian to     |
 *               |         |          |                   |    geodetic coordinates                 |
 *               |         |          |                   |  + New reference frames for on-board    |
 *               |         |          |                   |    position scheduling: EF and GM2000   |
 *               +----------------------------------------------------------------------------------+
 *               |    4.5  | 01/03/13 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New function xl_geoid_calc to        |
 *               |         |          |                   |    transform between heights relative to|
 *               |         |          |                   |    the ellipsoid and the geoid.         |
 *               +----------------------------------------------------------------------------------+
 *               |    4.6  | 03/10/13 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |    4.7  | 28/03/14 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Support for SENTINEL-5P, MetOp-SG    |
 *               |         |          |                   |    and Jason-CS satellites              |
 *               +----------------------------------------------------------------------------------+
 *               |    4.8  | 29/10/14 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New reference frame: Earth Fixed non |
 *               |         |          |                   |    rotating.                            |
 *               |         |          |                   |  + New Sun model to take into account   |
 *               |         |          |                   |    Sun light travel time.               |
 *               |         |          |                   |  + New function for quaternion          |
 *               |         |          |                   |    interpolation:xl_quaternions_interpol|
 *               +----------------------------------------------------------------------------------+
 *               |    4.9  | 23/04/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |  4.9.1  | 05/06/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |   4.10  | 29/10/15 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |  4.11   | 15/04/16 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Support for BIOMASS, SENTINEL-5,     |
 *               |         |          |                   |    and SAOCOM-CS satellites             |
 *               +----------------------------------------------------------------------------------+
 *               |  4.12   | 03/11/16 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Added extrapolation algorithm for    |
 *               |         |          |                   |    quaternions (xl_quaternions_interpol)|
 *               +----------------------------------------------------------------------------------+
 *               |  4.13   | 05/04/17 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *               |  4.14   | 16/11/17 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + New functions for CUC time managing  |
 *               |         |          |                   |    xl_time_cuc_to_processing            |
 *               |         |          |                   |    xl_time_processing_to_cuc            |
 *               |         |          |                   |  + Support for FLEX satellite           |
 *               +----------------------------------------------------------------------------------+
 *               |   4.15  | 20/04/18 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Refactored code                      |
 *               +----------------------------------------------------------------------------------+
 *               |   4.16  | 09/11/18 | DEIMOS Space S.L.U| Maintenance release                     |
 *               |         |          |                   | New features:                           |
 *               |         |          |                   |  + Improved runtime in time conversions |
 *               +----------------------------------------------------------------------------------+
 *               |   4.17  | 10/05/19 | DEIMOS Space S.L.U| Maintenance release                     |
 *               +----------------------------------------------------------------------------------+
 *
 *****************************************************************************/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <explorer_lib.h>			/* EXPLORER_LIB header file */


/* Main program */
/* ------------ */

int main (int argc, char *argv[])
{

   long   mjdt[4], mjdt_2[4], mjdt_3[4];
   long   mjdt_a1[4], mjdt_add[4], mjdt_a3[4], mjdt_sub[4];
   long   mjdt_s1[4], mjdt_s2[4];
   long    cs_in_t, cs_out_t;

   unsigned long sbt0, per0, obtm_1, obtl_1, obtm_2, obtl_2;

   long    planet_id;
   double mjdp[2], mjdp_2[2], mjdp_3[2];
   double rsun[3], rdsun[3], rmoon[3], rdmoon[3], rplanet[3], rdplanet[3];
   double ra0, dec0, mu_ra, mu_dec, rad_vel, par, ra, dec;
   double rr_t[3], rrd_t[3], rr2d_t[3];
   double lon_t, lat_t, h_t, lond_t, latd_t, hd_t;
   double time_t, r_t[3], rd_t[3], r2d_t[3];
   double r_out_t[3], rd_out_t[3], r2d_out_t[3];

   double lon1_t, lat1_t, lon2_t, lat2_t;
   double d_t, az1_t, az2_t;
   double latitude, longitude;
   char   egm96_file_path[XL_MAX_STR], corr_coef_file_path[XL_MAX_STR];

   char   utce[28], dut1e[9], utce_2[28], dut1e_2[9], utce_3[28], dut1e_3[9];

   long   status;                       /* (Normal) status flag */
   long   ext_status;                   /* (Extended) status flag */

   long   n;				            /* Number of error messages */
   long   func_id;                      /* CFI function ID */

   long   sat_id, calc_mode, aocs_mode, time_ref;
   double time_ut1;

   char   msg[XL_MAX_COD][XL_MAX_STR];	/* Error messages vector */

   long  local_err;

   double dummy_d = 0.0;
   long   dummy_l = 0L;

  char iers_file[256];
  xd_iers_bulletin_file iers_data;
  xl_time_id_init_data  time_id_init_data;
  xd_eocfi_file         eocfi_file_array[1];

   xl_time_id time_id = {NULL};
   long xd_ierr[XD_ERR_VECTOR_MAX_LENGTH];
   long xl_ierr[XL_ERR_VECTOR_MAX_LENGTH];

   /* xl_kepl_to_cart & xl_cart_to_kepl */
   double kepl_in[6], kepl_out[6];
   double pos_out[3], vel_out[3], pos_in[3],vel_in[3];
   long kepl_mode;

   /* xl_time_ref_init */
   long   tri_orbit_num;
   double tri_anx_time, tri_orbit_duration;
   double tri_time[4];

   /* xl_time_id_init */
   long time_model;
   long n_files;
   long time_init_mode;
   long orbit0, orbit1;
   double time1;
   double val_time0, val_time1;

   /* xl_time_ref_init_file */
   long   trif_time_model, trif_n_files, trif_time_init_mode, trif_time_ref ;
   char   **trif_time_file;
   double trif_time0, trif_time1, trif_val_time0, trif_val_time1;
   long   trif_orbit0, trif_orbit1;
   long   i, imax;


   /* xl_time_transport_to_transport */
   long   t2t_trans_id_in, t2t_time_ref_in, t2t_trans_id_out, t2t_time_ref_out;
   long   t2t_transport_in[4];
   long   t2t_transport_out[4];

   /* xl_time_transport_to_processing */
   long   t2p_trans_id_in, t2p_time_ref_in, t2p_proc_id_out, t2p_time_ref_out;
   long   t2p_transport_in[4];
   double t2p_processing_out;

   /* xl_time_processing_to_transport */
   long   p2t_proc_id_in, p2t_time_ref_in, p2t_trans_id_out, p2t_time_ref_out;
   double p2t_processing_in;
   long   p2t_transport_out[4];

   /* xl_time_processing_to_processing */
   long   p2p_proc_id_in, p2p_time_ref_in, p2p_proc_id_out, p2p_time_ref_out;
   double p2p_processing_in;
   double p2p_processing_out;

   /* xl_time_ascii_to_ascii */
   long   a2a_ascii_id_in, a2a_time_ref_in, a2a_ascii_id_out, a2a_time_ref_out;
   char   a2a_ascii_in[32];
   char   a2a_ascii_out[32];

   /* xl_time_ascii_to_transport */
   long   a2t_ascii_id_in, a2t_time_ref_in, a2t_trans_id_out, a2t_time_ref_out;
   char   a2t_ascii_in[32];
   long   a2t_transport_out[4];

   /* xl_time_transport_to_ascii */
   long   t2a_trans_id_in, t2a_time_ref_in, t2a_ascii_id_out, t2a_time_ref_out;
   long   t2a_transport_in[4];
   char   t2a_ascii_out[32];

   /* xl_time_ascii_to_processing */
   long   a2p_ascii_id_in, a2p_time_ref_in, a2p_proc_id_out, a2p_time_ref_out;
   char   a2p_ascii_in[32];
   double a2p_processing_out;

   /* xl_time_processing_to_ascii */
   long   p2a_proc_id_in, p2a_time_ref_in, p2a_ascii_id_out, p2a_time_ref_out;
   double p2a_processing_in;
   char   p2a_ascii_out[32];

   /* xl_time_add, xl_time_diff */
   long   proc_id;
   double processing_in_1,processing_in_2,processing_out;

   /* xl_time_obt_to_time, xl_time_time_to_obt */
   xl_envisat_obt_param envisat_obt_param;
   xl_envisat_obt_value envisat_obt_value;

   double time0, time_out, time_in;
   unsigned long obt0[2],obt[2];
   unsigned long period0;

   /* xl_get_rotated_vectors, xl_get_rotation_angles */
   double x_in[3], y_in[3], z_in[3];
   double x_out[3], y_out[3], z_out[3];
   double ang_in[3], ang_out[3];

   /* xl_position_on_orbit */
   long angle_type = XL_ANGLE_TYPE_TRUE_LAT_TOD;   /* No other type is currently supported */
   double poo_time;  
   double poo_pos[3], poo_vel[3], poo_acc[3];
   long deriv;
   double angle_out;
   double angle_rate_out;
   double angle_rate_rate_out;

   /*xl_cart_to_radec & xl_radec_to_cart*/
   double pos[3], vel[3];
   long mode = XL_CALC_POS_VEL, 
       cs_in = XL_BM1950;
   double pc        = 3.08568025E16;
   double KM_PER_AU = 149597870.691;

   /* variables for time accessors */
   long flag;
   long time_mode;
   xl_time_id_data time_id_data;

   /* Variables for Rounding to 32, 40 & 43 bits */

   unsigned long round32 = (unsigned long)0x00000001;
   unsigned long round40 = (unsigned long)0x00000100;
   unsigned long round43 = (unsigned long)0x00000800;
   double   dround;
   unsigned long wrap  = (unsigned long)0xFFFFFFFF;
   double   dwrap = ((double) wrap) + (double) 1.0 ;

   unsigned long sbtm43, sbtl43;
   unsigned long sbtm40, sbtl40;
   unsigned long sbtm32, sbtl32;
   double dsbt;

   long vec[XL_MAX_COD];
   long vector_status;
   int  p;

   /* variables for euler <-> matrix conversion */
   double euler_ang[3];
   double rot_matrix[3][3];

   /* variables for xl_star_catalog */
   double time;
   long catalog_in, catalog_out;
   double mu_ra0, mu_dec0;
   double rad_vel0, par0;

   /* variables for xl_topocentric_to_ef */
   double azim, elev, range;
   double azim_d, elev_d, range_d; 
   double ef_dir[3], ef_dir_d[3];

   /* variables for xl_model_init */
   xl_model_id model_id = {NULL};
   long models[XL_NUM_MODEL_TYPES_ENUM];
   xl_model_data model_data;
   
   xl_geoid_calc_inputs geoid_in;
   xl_geoid_calc_outputs geoid_out;

   /* Set error handling mode to SILENT */
   /* ---------------------------------- */

   xl_silent();     /* Set error handling mode to SILENT */
/* xl_verbose();	/* Set error handling mode to VERBOSE */


/* Dummy Test of Logging feature */
/* ----------------------------- */

 /*  n = 0;
   strcpy(msg[n++],"This is the first user's log message");
   strcpy(msg[n++],"This is the second user's log message");
   xl_print_msg(&n,msg); */


/******************************************************************************/
/*                                                                            */
/* Time initialization functions                                              */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Time references initialization                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_id_init                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_ID_INIT\n");

  time_model     = XL_TIMEMOD_IERS_B_PREDICTED;
  n_files        = 1;
  time_init_mode = XL_SEL_FILE;
  time_ref       = XL_TIME_TAI;

  strcpy (iers_file, "../data/bulletinb-283.dat");

  /* read file */
  status = xd_read_bulletin_2(iers_file,
                              &iers_data,
                              xd_ierr);
  if (status != XL_OK)
  {
    func_id = XD_READ_BULLETIN_ID;
    xd_get_msg(&func_id, xd_ierr, &n, msg);
    xl_print_msg(&n, msg);
    if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  } 

  /* store read data */
  eocfi_file_array[0].file_type                = XD_BULLETIN_FILE;
  eocfi_file_array[0].eocfi_file.bulletin_file = iers_data;

  time_id_init_data.data_type = XL_FILE_DATA;
  time_id_init_data.time_id_init_data.file_set.num_files = n_files;
  time_id_init_data.time_id_init_data.file_set.eocfi_file_array = eocfi_file_array;

  /* Call xl_time_id_init function */
  /* ----------------------------- */
  status = xl_time_id_init(&time_model, 
                           &time_id_init_data,
                           &time_init_mode, &time_ref,
                           &time0, &time1,
                           &orbit0, &orbit1,
                           &val_time0, &val_time1, 
                           &time_id, xl_ierr);
  if (status != XL_OK)
  {
     func_id = XL_TIME_ID_INIT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }
  else 
  {
    printf("\nTime correctly initialized");
  }

   /* close time_id */
   xl_time_close(&time_id, xl_ierr);

   /* free memory */
   xd_free_bulletin(&iers_data);


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

#ifdef XL_WINDOWS
  strcpy (trif_time_file[0], "..\\data\\bulb.dat");
#else
  strcpy (trif_time_file[0], "../data/bulb.dat");
#endif

  /* Call xl_time_ref_init_file function */
  /* ----------------------------------- */
  status = xl_time_ref_init_file(&trif_time_model, &trif_n_files, trif_time_file,
                                 &trif_time_init_mode, &trif_time_ref, &trif_time0, &trif_time1,
                                 &trif_orbit0, &trif_orbit1, &trif_val_time0, &trif_val_time1, 
                                 &time_id, xl_ierr);

  /* Free memory */
  /* ----------- */

  free((char *)(trif_time_file[0]));
  free((char **)(trif_time_file));

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_REF_INIT_FILE_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
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
  xl_time_close(&time_id, xl_ierr);

  printf("\nMemory freed successfully");


  /* ------------------------------------------------------------------------ */
  /* Time references initialization                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ref_init                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_REF_INIT\n");

  /* Set input values */
  /* ---------------- */
  tri_time[0]   = -245.100000000;   /* TAI time [days] */ 
  tri_time[1]   = -245.100405092;   /* UTC time [days] (= TAI - 35.0 s)     */ 
  tri_time[2]   = -245.100408564;   /* UT1 time [days] (= TAI - 35.3 s)     */ 
  tri_time[3]   = -245.100219907;   /* GPS time [days] (= TAI - 19.0 s)     */

  tri_orbit_num = 10;
  tri_anx_time  = 5245.123456;
  tri_orbit_duration = 6035.928144;

  /* Call xl_time_ref_init function */
  /* ------------------------------ */
  status = xl_time_ref_init(tri_time, &tri_orbit_num, &tri_anx_time,
                            &tri_orbit_duration, &time_id, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_REF_INIT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  } else {
     printf("\nTime correctly initialized");
  }

/******************************************************************************/
/*                                                                            */
/* CFI Models                                                                 */
/*                                                                            */
/******************************************************************************/

  /* ----------------------------------------------- */
  /* Model initialisation                            */
  /* ----------------------------------------------  */
  /* Function(s): xl_model_init & xl_model_get_data  */
  /* ----------------------------------------------- */
  
  printf("\n\n\nXL_MODEL_INIT & model accessors \n");

  /* Default model */
  mode = XL_MODEL_DEFAULT;
  
  status = xl_model_init( &mode, models, &model_id, xl_ierr );
  
  /* get model data */
  printf("\n\n\nXL_MODEL_GET_DATA\n");
  status = xl_model_get_data(&model_id, &model_data);

  printf("\nModel data");
  printf("\n- Earth model      : %ld ", model_data.earth_model);
  printf("\n- Sun model        : %ld ", model_data.sun_model);
  printf("\n- Moon model       : %ld ", model_data.moon_model);
  printf("\n- Planet model     : %ld ", model_data.planet_model);
  printf("\n- Star model       : %ld ", model_data.star_model);
  printf("\n- Nutation model   : %ld ", model_data.nutation_model);
  printf("\n- Precession model : %ld ", model_data.precession_model);
  printf("\n- Constants model  : %ld ", model_data.constants_model);

  printf("\n- Earth equatorial radius [m]           : %lf ", model_data.re);
  printf("\n- Earth's gravitational constant [m3/s2]: %lf ", model_data.mu);
  printf("\n- Second zonal harmonic                 : %lf ", model_data.j2);
  printf("\n- Third zonal harmonic                  : %lf ", model_data.j3);
  printf("\n- Fourth zonal harmonic                 : %lf ", model_data.j4);
  printf("\n- Semi-major axis                       : %lf ", model_data.major_axis);
  printf("\n- Semi-minor axis                       : %lf ", model_data.minor_axis);
  printf("\n- First eccentricity                    : %lf ", model_data.ecc);
  printf("\n- Flattening                            : %lf ", model_data.flat);
  printf("\n- Earth rotation coeff[0]               : %lf ", model_data.gcoef_0);
  printf("\n- Earth rotation coeff[1]               : %lf ", model_data.gcoef_1);
  printf("\n- Earth rotation coeff[2]               : %lf ", model_data.gcoef_2);
  printf("\n- Sim. Earth rotation coeff[0]          : %lf ", model_data.gcoef_sim_0);
  printf("\n- Sim. Earth rotation coeff[1]          : %lf ", model_data.gcoef_sim_1);
  printf("\n- Sim. Earth rotation coeff[2]          : %lf ", model_data.gcoef_sim_2);




/******************************************************************************/
/*                                                                            */
/* Reference system transformations                                           */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Transform cartesian coordinates from Earth Fixed to True of Date CS      */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_change_cart_cs                                           */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_TAI;

   cs_in_t   = XL_EF;			/* Initial coordinate system = Earth fixed */
   cs_out_t  = XL_TOD;			/* Final coordinate system = True of Date */

   time_t    =  -2456.0;		/* TAI time in MJD2000 (1993-04-11 00:00:00) [days] */

   r_t[0]    =   4859964.138;   /* Position vector (x,y,z) [m] */
   r_t[1]    =  -5265612.059;
   r_t[2]    =         0.002;
   rd_t[0]   =  -1203.303801;   /* Velocity vector (x,y,z) [m/s] */
   rd_t[1]   =  -1098.845511;
   rd_t[2]   =   7377.224410;
   r2d_t[0]  =  0.0;			/* Acceleration vector (x,y,z) [m/s2] */
   r2d_t[1]  =  0.0;
   r2d_t[2]  =  0.0;

   printf("\n\n\nXL_CHANGE_CART_CS\n");

   ext_status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in_t, &cs_out_t,
                                  &time_ref, &time_t, r_t, rd_t, r2d_t,
                                  r_out_t, rd_out_t, r2d_out_t);

   if (ext_status != XL_OK)
   {
      func_id = XL_CHANGE_CART_CS_ID;
      xl_get_msg(&func_id, &ext_status, &n, msg);
      xl_print_msg(&n, msg);

      if (ext_status <= XL_ERR) return(XL_ERR);    /* CAREFUL: extended status */
   }

   printf("\n-   r_out_t[0]     : %lf ", r_out_t[0]);   /* Position vector (x,y,z) [m] */
   printf("\n-   r_out_t[1]     : %lf ", r_out_t[1]);
   printf("\n-   r_out_t[2]     : %lf ", r_out_t[2]);
   printf("\n-  rd_out_t[0]     : %lf ", rd_out_t[0]);  /* Velocity vector (x,y,z) [m/s] */
   printf("\n-  rd_out_t[1]     : %lf ", rd_out_t[1]);
   printf("\n-  rd_out_t[2]     : %lf ", rd_out_t[2]);
   printf("\n- r2d_out_t[0]     : %lf ", r2d_out_t[0]); /* Acceleration vector (x,y,z) [m/s2] */
   printf("\n- r2d_out_t[1]     : %lf ", r2d_out_t[1]);
   printf("\n- r2d_out_t[2]     : %lf ", r2d_out_t[2]);


  /* ------------------------------------------------------------------------ */
  /* Transform from cartesian to geodetic coordinates                         */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_cart_to_geod                                             */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL;

   rr_t[0]  =   4859964.138;		/* Position vector in the Earth fixed coordinate system (x,y,z) [m] */
   rr_t[1]  =  -5265612.059;
   rr_t[2]  =         0.002;
   rrd_t[0] =  -1203.303801;		/* Velocity vector in the Earth fixed coordinate system (x,y,z) [m/s] */
   rrd_t[1] =  -1098.845511;
   rrd_t[2] =   7377.224410;

   printf("\n\n\nXL_CART_TO_GEOD\n");

   ext_status = xl_cart_to_geod(&model_id, &calc_mode, rr_t, rrd_t, &lon_t, &lat_t, &h_t,
                                &lond_t, &latd_t, &hd_t);

   if (ext_status != XL_OK)
   {
      func_id = XL_CART_TO_GEOD_ID;
      xl_get_msg(&func_id, &ext_status, &n, msg);
      xl_print_msg(&n, msg);

      if (ext_status <= XL_ERR) return(XL_ERR);    /* CAREFUL: extended status */
   }

   printf("\n- lon_t            : %lf ", lon_t);		/* Geocentric longitude [deg] */
   printf("\n- lat_t            : %lf ", lat_t);		/* Geodetic longitude [deg] */
   printf("\n- h_t              : %lf ", h_t);			/* Geodetic altitude [m] */
   printf("\n- lond_t           : %lf ", lond_t);		/* Geocentric longitude rate [deg/s] */
   printf("\n- latd_t           : %lf ", latd_t);		/* Geodetic latitude rate [deg/s] */
   printf("\n- hd_t             : %lf ", hd_t);		/* Geodetic altitude rate [m/s] */


  /* ------------------------------------------------------------------------ */
  /* Transform from geodetic to cartesian coordinates                         */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_geod_to_cart                                             */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL;

   lon_t    =   4.17;		/* Geocentric longitude [deg] */
   lat_t    =  45.0;		/* Geodetic latitude [deg] */
   h_t      = 400.0;		/* Geodetic altitude [m] */
   lond_t   =   0.0;		/* Geocentric longitude rate [deg/s] */
   latd_t   =   0.0;		/* Geodetic latitude rate [deg/s] */
   hd_t     =   0.0;		/* Geodetic altitude rate [m/s] */

   printf("\n\n\nXL_GEOD_TO_CART\n");

   ext_status = xl_geod_to_cart(&model_id, &calc_mode, &lon_t, &lat_t, &h_t,
                                &lond_t, &latd_t, &hd_t, rr_t, rrd_t);

   if (ext_status != XL_OK)
   {
      func_id = XL_GEOD_TO_CART_ID;
      xl_get_msg(&func_id, &ext_status, &n, msg);
      xl_print_msg(&n, msg);

      if (ext_status <= XL_ERR) return(XL_ERR);    /* CAREFUL: extended status */
   }

   printf("\n- rr_t[0]          : %lf ", rr_t[0]);     /* Cartesian position vector (x,y,z) [m] */
   printf("\n- rr_t[1]          : %lf ", rr_t[1]);
   printf("\n- rr_t[2]          : %lf ", rr_t[2]);
   printf("\n- rrd_t[0]         : %lf ", rrd_t[0]);    /* Cartesian velocity vector (x,y,z) [m/s] */
   printf("\n- rrd_t[1]         : %lf ", rrd_t[1]);
   printf("\n- rrd_t[2]         : %lf ", rrd_t[2]);


  /* ------------------------------------------------------------------------ */
  /* Transform from cartesian state vector to keplerian elements              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_cart_to_kepl                                             */
  /* ------------------------------------------------------------------------ */

   kepl_mode = XL_KEPLER_OSC;

   pos_in[0] =   4859964.138;       /* Position vector in the Earth fixed coordinate system (x,y,z) [m] */
   pos_in[1] =  -5265612.059;
   pos_in[2] =         0.002;
   vel_in[0] =  -1203.303801;       /* Velocity vector in the Earth fixed coordinate system (x,y,z) [m/s] */
   vel_in[1] =  -1098.845511;
   vel_in[2] =   7377.224410;

   printf("\n\n\nXL_CART_TO_KEPL\n");

   status = xl_cart_to_kepl(&model_id, pos_in, vel_in, &kepl_mode, kepl_out, xl_ierr );


  /* Error handling functions */
  /* ------------------------ */

   if (status != XL_OK)
   {
       func_id = XL_CART_TO_KEPL_ID;
       xl_get_msg(&func_id, xl_ierr, &n, msg);
       xl_print_msg(&n, msg);
       if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- Semi-major axis  : %lf ", kepl_out[0]);  /* Semi-major axis          [m] */
   printf("\n- Eccenticity      : %lf ", kepl_out[1]);  /* Eccenticity                  */
   printf("\n- Inclination      : %lf ", kepl_out[2]);  /* Inclination            [deg] */
   printf("\n- RAAN             : %lf ", kepl_out[3]);  /* R.A. of Ascending Node [deg] */
   printf("\n- Arg. of Perigee  : %lf ", kepl_out[4]);  /* Arg. of Perigee        [deg] */
   printf("\n- Mean Anomaly     : %lf ", kepl_out[5]);  /* Mean Anomaly           [deg] */


  /* ------------------------------------------------------------------------ */
  /* Transform from keplerian elements to cartesian state vector              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_kepl_to_cart                                             */
  /* ------------------------------------------------------------------------ */

   kepl_mode = XL_KEPLER_OSC;

   kepl_in[0] = 7000000.0;       /* Semi-major axis          [m] */
   kepl_in[1] =       0.001;     /* Eccenticity                  */
   kepl_in[2] =      92.0;       /* Inclination            [deg] */
   kepl_in[3] =     128.0;       /* R.A. of Ascending Node [deg] */
   kepl_in[4] =     110.0;       /* Arg. of Perigee        [deg] */
   kepl_in[5] =      73.1;       /* Mean Anomaly           [deg] */

   printf("\n\n\nXL_KEPL_TO_CART\n");

   status = xl_kepl_to_cart(&model_id, &kepl_mode, kepl_in, pos_out, vel_out, xl_ierr );

   if (status != XL_OK)
   {
      func_id = XL_KEPL_TO_CART_ID;
      xl_get_msg(&func_id, xl_ierr, &n, msg);
      xl_print_msg(&n, msg);

      if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- pos_out[0]       : %lf ", pos_out[0]);    /* Cartesian position vector (x,y,z) [m] */
   printf("\n- pos_out[1]       : %lf ", pos_out[1]);
   printf("\n- pos_out[2]       : %lf ", pos_out[2]);
   printf("\n- vel_out[0]       : %lf ", vel_out[0]);    /* Cartesian velocity vector (x,y,z) [m/s] */
   printf("\n- vel_out[1]       : %lf ", vel_out[1]);
   printf("\n- vel_out[2]       : %lf ", vel_out[2]);


/******************************************************************************/
/*                                                                            */
/* Geodesic functions                                                         */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Calculate the geodesic (minimum) distance between two points that lay    */
  /* at a given altitude on the same ellipsoid                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_geod_distance                                            */
  /* ------------------------------------------------------------------------ */


   lon1_t    =   4.17;			/* Geocentric longitude of the first point [deg] */
   lat1_t    =  10.0;			/* Geodetic latitude of the first point [deg] */
   lon2_t    =   4.17;			/* Geocentric longitude of the second point [deg] */
   lat2_t    = -20.0;			/* Geodetic latitude of the second point [deg] */
   h_t       =   0.0;			/* Geodetic altitude of both points [m] */

   printf("\n\n\nXL_GEOD_DISTANCE\n");

   ext_status = xl_geod_distance(&model_id, &lon1_t, &lat1_t, &lon2_t, &lat2_t,
                                 &h_t, &d_t, &az1_t, &az2_t);

   if (ext_status != XL_OK)
   {
      func_id = XL_GEOD_DISTANCE_ID;
      xl_get_msg(&func_id, &ext_status, &n, msg);
      xl_print_msg(&n, msg);

      if (ext_status <= XL_ERR) return(XL_ERR);    /* CAREFUL: extended status */
   }

   printf("\n- d_t              : %lf ", d_t);		/* Geodesic distance [m] */
   printf("\n- az1_t            : %lf ", az1_t);	/* Topocentric azimuth of the geodesic line between the two points at point 1 [deg] */
   printf("\n- az2_t            : %lf ", az2_t);	/* Topocentric azimuth of the geodesic line between the two points at point 2 [deg] */


/******************************************************************************/
/*                                                                            */
/* Ephemerides functions                                                      */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* Calculate Sun position and velocity in the Earth Fixed CS               */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_sun                                                      */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_UT1;

   time_ut1 = 0.0;		/* UT1 time in MJD2000 [days] */

   printf("\n\n\nXL_SUN\n");

   status = xl_sun(&model_id, &time_id, &time_ref, &time_ut1, rsun, rdsun, &local_err);

   if (status != XL_OK)
   {
      func_id = XL_SUN_ID;
      xl_get_msg(&func_id, &local_err, &n, msg);
      xl_print_msg(&n, msg);

      if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- rsun[0]          : %lf ", rsun[0] );   /* Sun position vector in Earth Fixed coordinate system (x,y,z) [m] */
   printf("\n- rsun[1]          : %lf ", rsun[1] );
   printf("\n- rsun[2]          : %lf ", rsun[2] );
   printf("\n- rdsun[0]         : %lf ", rdsun[0] );  /* Sun velocity vector in Earth Fixed coordinate system (x,y,z) [m/s] */
   printf("\n- rdsun[1]         : %lf ", rdsun[1] );
   printf("\n- rdsun[2]         : %lf ", rdsun[2] );


  /* ------------------------------------------------------------------------ */
  /* Calculate Moon position and velocity in the Earth Fixed CS              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_moon                                                     */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_UT1;

   time_ut1 = 0.0;		/* UT1 time in MJD2000 [days] */

   printf("\n\n\nXL_MOON\n");

   status = xl_moon(&model_id, &time_id, &time_ref, &time_ut1, rmoon, rdmoon, &local_err);

   if (status != XL_OK)
   {
      func_id = XL_MOON_ID;
      xl_get_msg(&func_id, &local_err, &n, msg);
      xl_print_msg(&n, msg);

      if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- rmoon[0]         : %lf ", rmoon[0] );   /* Moon position vector in Earth Fixed coordinate system (x,y,z) [m] */
   printf("\n- rmoon[1]         : %lf ", rmoon[1] );
   printf("\n- rmoon[2]         : %lf ", rmoon[2] );
   printf("\n- rdmoon[0]        : %lf ", rdmoon[0] );  /* Moon velocity vector in Earth Fixed coordinate system (x,y,z) [m/s] */
   printf("\n- rdmoon[1]        : %lf ", rdmoon[1] );
   printf("\n- rdmoon[2]        : %lf ", rdmoon[2] );


  /* ------------------------------------------------------------------------ */
  /* Calculating planets position and velocity in the Earth Fixed CS          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_planet                                                   */
  /* ------------------------------------------------------------------------ */

   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_UT1;

   time_ut1  = 0.0;		/* UT1 time in MJD2000 [days] */

   planet_id = XL_VENUS; 	/* Venus ID */

   printf("\n\n\nXL_PLANET\n");

   status = xl_planet(&model_id, &time_id, &planet_id, &time_ref, &time_ut1, rplanet, rdplanet, &local_err);

   if (status != XL_OK)
   {
      func_id = XL_PLANET_ID;
      xl_get_msg(&func_id, &local_err, &n, msg);
      xl_print_msg(&n, msg);

      if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- rplanet[0]       : %lf ", rplanet[0] );   /* Planet position vector in Earth Fixed CS (x,y,z) [m] */
   printf("\n- rplanet[1]       : %lf ", rplanet[1] );
   printf("\n- rplanet[2]       : %lf ", rplanet[2] );
   printf("\n- rdplanet[0]      : %lf ", rdplanet[0] );  /* Planet velocity vector in Earth Fixed CS (x,y,z) [m/s] */
   printf("\n- rdplanet[1]      : %lf ", rdplanet[1] );
   printf("\n- rdplanet[2]      : %lf ", rdplanet[2] );

  /* ------------------------------------------------------------------------ */
  /* Calculating star coordinates in the Mean of Date coordinate system       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_star_radec                                               */
  /* ------------------------------------------------------------------------ */

   time_ref  = XL_TIME_UT1;

   time_ut1 =  -200.0;	/* UT1 time in MJD2000 [days] */

   ra0     =   0.35399670615; 	/* Star right ascension in the Barycentric Mean of 2000.0 coordinate at J2000.0 [rad] */
   dec0    =   4.8672587;	/* Star declination in the Barycentric Mean of 2000.0 coordinate at J2000.0 [rad] */
   mu_ra   =   0.001;	        /* Star proper motion in the right ascension [rad/century] */
   mu_dec  =  -0.001;       	/* Star proper motion in the declination [rad/century] */
   rad_vel =   0.01;       	/* Star radial velocity [au/century] */
   par     =   0.0001;       	/* Star parallax [rad] */

   printf("\n\n\nXL_STAR_RADEC\n");

   status = xl_star_radec(&model_id, &time_id, &time_ref, &time_ut1, &ra0, &dec0,
                          &mu_ra, &mu_dec, &rad_vel, &par, &ra, &dec, &local_err);

   if (status != XL_OK)
   {
      func_id = XL_STAR_RADEC_ID;
      xl_get_msg(&func_id, &local_err, &n, msg);
      xl_print_msg(&n, msg);

      if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
   }

   printf("\n- ra               : %lf [rad]", ra );   /* Star right ascension in Mean of Date at UT1 [rad] */
   printf("\n- dec              : %lf [rad]", dec );  /* Star declination in Mean of Date at UT1 [rad] */


/******************************************************************************/
/*                                                                            */
/* Time transformations functions                                             */
/*                                                                            */
/******************************************************************************/

  /* ------------------------------------------------------------------------ */
  /* From Transport(Standard) to Ascii(STD_REF_MICROSEC) time format          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_transport_to_ascii                                  */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_TRANSPORT_TO_ASCII\n");

  /* Set input values */
  /* ---------------- */

  t2a_trans_id_in  = XL_TRANS_STD;
  t2a_time_ref_in  = XL_TIME_TAI;
  t2a_ascii_id_out = XL_ASCII_STD_REF_MICROSEC;
  t2a_time_ref_out = XL_TIME_GPS;

  t2a_transport_in[0] = 245;     /* TAI time [integer days]         */
  t2a_transport_in[1] = 150;     /* TAI time [integer seconds]      */
  t2a_transport_in[2] = 1500;    /* TAI time [integer microseconds] */
  t2a_transport_in[3] = 0;       /* Unused in Transport_Standard    */

  /* Call xl_time_transport_to_ascii function */
  /* ---------------------------------------- */
  status = xl_time_transport_to_ascii(&time_id,  &t2a_trans_id_in,  &t2a_time_ref_in,
                                      t2a_transport_in, &t2a_ascii_id_out, &t2a_time_ref_out,
                                      t2a_ascii_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_TRANSPORT_TO_ASCII_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- trans_id_in      : %ld ", t2a_trans_id_in);     /* Input Time Format */
  printf("\n- time_ref_in      : %ld ", t2a_time_ref_in);     /* Input Time Reference */
  printf("\n- transport_in[0]  : %ld ", t2a_transport_in[0]); /* Input Transport Time [integer days] */
  printf("\n- transport_in[1]  : %ld ", t2a_transport_in[1]); /* Input Transport Time [integer milliseconds] */
  printf("\n- transport_in[2]  : %ld ", t2a_transport_in[2]); /* Input Transport Time [integer microseconds] */
  printf("\n- ascii_id_out     : %ld ", t2a_ascii_id_out);    /* Output Time Format */
  printf("\n- time_ref_out     : %ld ", t2a_time_ref_out);    /* Output Time Reference */
  printf("\n- ascii_out        : %s ",  t2a_ascii_out);       /* Output Ascii Time */


  /* ------------------------------------------------------------------------- */
  /* From Transport(XL_TRANS_CRYO_TM_SIRAL) to Transport(Standard) time format */
  /* ------------------------------------------------------------------------- */
  /* Function(s): xl_time_transport_to_transport                               */
  /* ------------------------------------------------------------------------- */

  printf("\n\n\nXL_TIME_TRANSPORT_TO_TRANSPORT\n");

  /* Set input values */
  /* ---------------- */
  t2t_trans_id_in  = XL_TRANS_CRYO_TM_SIRAL;
  t2t_time_ref_in  = XL_TIME_UTC;
  t2t_trans_id_out = XL_TRANS_STD;
  t2t_time_ref_out = XL_TIME_TAI;

  t2t_transport_in[0] = 245;    /* UTC time [integer days]         */
  t2t_transport_in[1] = 6000;   /* UTC time [integer milliseconds] */
  t2t_transport_in[2] = 500;    /* UTC time [integer microseconds] */
  t2t_transport_in[3] = 300000; /* Extra SIRAL counter ticks       */

  /* Call xl_time_transport_to_transport function */
  /* -------------------------------------------- */
  status = xl_time_transport_to_transport(&time_id, &t2t_trans_id_in,
                        &t2t_time_ref_in, t2t_transport_in, &t2t_trans_id_out,
                        &t2t_time_ref_out, t2t_transport_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_TRANSPORT_TO_TRANSPORT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- trans_id_in      : %ld ", t2t_trans_id_in);      /* Time Format */
  printf("\n- time_ref_in      : %ld ", t2t_time_ref_in);      /* Time Reference */
  printf("\n- transport_in[0]  : %ld ", t2t_transport_in[0]);  /* UTC time in XL_TRANS_CRYO_TM format [integer days] */
  printf("\n- transport_in[1]  : %ld ", t2t_transport_in[1]);  /* UTC time in XL_TRANS_CRYO_TM format [integer milliseconds] */
  printf("\n- transport_in[2]  : %ld ", t2t_transport_in[2]);  /* UTC time in XL_TRANS_CRYO_TM format [integer microseconds] */
  printf("\n- transport_in[3]  : %ld ", t2t_transport_in[3]);  /* Extra SIRAL counter ticks [integer] */
  printf("\n- trans_id_out     : %ld ", t2t_trans_id_out);     /* Time Format */
  printf("\n- time_ref_out     : %ld ", t2t_time_ref_out);     /* Time Reference */
  printf("\n- transport_out[0] : %ld ", t2t_transport_out[0]); /* TAI time in XL_TRANS_STD format [integer days] */
  printf("\n- transport_out[1] : %ld ", t2t_transport_out[1]); /* TAI time in XL_TRANS_STD format [integer seconds] */
  printf("\n- transport_out[2] : %ld ", t2t_transport_out[2]); /* TAI time in XL_TRANS_STD format [integer microseconds] */


  /* ------------------------------------------------------------------------- */
  /* From Transport(Standard) to Transport(XL_TRANS_CRYO_TM_SIRAL) time format */
  /* ------------------------------------------------------------------------- */
  /* Function(s): xl_time_transport_to_transport                               */
  /* ------------------------------------------------------------------------- */

  printf("\n\n\nXL_TIME_TRANSPORT_TO_TRANSPORT\n");

  /* Set input values */
  /* ---------------- */
  t2t_trans_id_in = XL_TRANS_STD;
  t2t_time_ref_in = XL_TIME_TAI;
  t2t_trans_id_out= XL_TRANS_CRYO_TM_SIRAL;
  t2t_time_ref_out= XL_TIME_UTC;

  t2t_transport_in[0] = 244;    /* TAI time [integer days]         */
  t2t_transport_in[1] = 86371;  /* TAI time [integer seconds]      */
  t2t_transport_in[2] = 619250; /* TAI time [integer microseconds] */

  /* Call xl_time_transport_to_transport function */
  /* -------------------------------------------- */
  status = xl_time_transport_to_transport(&time_id, &t2t_trans_id_in,
                                          &t2t_time_ref_in, t2t_transport_in, &t2t_trans_id_out,
                                          &t2t_time_ref_out, t2t_transport_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_TRANSPORT_TO_TRANSPORT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- trans_id_in      : %ld ", t2t_trans_id_in);      /* Time Format */
  printf("\n- time_ref_in      : %ld ", t2t_time_ref_in);      /* Time Reference */
  printf("\n- transport_in[0]  : %ld ", t2t_transport_in[0]);  /* TAI time in XL_TRANS_STD format [integer days] */
  printf("\n- transport_in[1]  : %ld ", t2t_transport_in[1]);  /* TAI time in XL_TRANS_STD format [integer seconds] */
  printf("\n- transport_in[2]  : %ld ", t2t_transport_in[2]);  /* TAI time in XL_TRANS_STD format [integer microseconds] */
  printf("\n- trans_id_out     : %ld ", t2t_trans_id_out);     /* Time Format */
  printf("\n- time_ref_out     : %ld ", t2t_time_ref_out);     /* Time Reference */
  printf("\n- transport_out[0] : %ld ", t2t_transport_out[0]); /* UTC time in XL_TRANS_CRYO_TM format [integer days] */
  printf("\n- transport_out[1] : %ld ", t2t_transport_out[1]); /* UTC time in XL_TRANS_CRYO_TM format [integer milliseconds] */
  printf("\n- transport_out[2] : %ld ", t2t_transport_out[2]); /* UTC time in XL_TRANS_CRYO_TM format [integer microseconds] */
  printf("\n- transport_out[3] : %ld ", t2t_transport_out[3]); /* Extra SIRAL counter ticks [integer] */

  /* ------------------------------------------------------------------------ */
  /* From Transport(Standard) to Processing time format                       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_transport_to_processing                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_TRANSPORT_TO_PROCESSING\n");

  /* Set input values */
  /* ---------------- */
  t2p_trans_id_in  = XL_TRANS_STD;
  t2p_time_ref_in  = XL_TIME_TAI;
  t2p_proc_id_out  = XL_PROC;
  t2p_time_ref_out = XL_TIME_UTC;

  t2p_transport_in[0] = 245;     /* TAI time [integer days]         */
  t2p_transport_in[1] = 60;      /* TAI time [integer seconds]      */
  t2p_transport_in[2] = 1500;    /* TAI time [integer microseconds] */
  t2p_transport_in[3] = 0;       /* Unused in Transport_Standard    */

  /* Call xl_time_transport_to_processing function */
  /* --------------------------------------------- */
  status = xl_time_transport_to_processing(&time_id, &t2p_trans_id_in,
                                           &t2p_time_ref_in, t2p_transport_in, &t2p_proc_id_out,
                                           &t2p_time_ref_out, &t2p_processing_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_TRANSPORT_TO_PROCESSING_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- trans_id_in      : %ld ",    t2p_trans_id_in);      /* Time Format */
  printf("\n- time_ref_in      : %ld ",    t2p_time_ref_in);      /* Time Reference */
  printf("\n- transport_in[0]  : %ld ",    t2p_transport_in[0]);  /* TAI time in XL_TRANS_STD format [integer days] */
  printf("\n- transport_in[1]  : %ld ",    t2p_transport_in[1]);  /* TAI time in XL_TRANS_STD format [integer seconds] */
  printf("\n- transport_in[2]  : %ld ",    t2p_transport_in[2]);  /* TAI time in XL_TRANS_STD format [integer microseconds] */
  printf("\n- proc_id_out      : %ld ",    t2p_proc_id_out);      /* Time Format */
  printf("\n- time_ref_out     : %ld ",    t2p_time_ref_out);     /* Time Reference */
  printf("\n- processing_out   : %12.12lf",t2p_processing_out);   /* UTC time in XL_PROC format [days] */


  /* ------------------------------------------------------------------------ */
  /* From Processing to Ascii(STD_REF_MICROSEC) time format                   */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_processing_to_ascii                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_PROCESSING_TO_ASCII\n");

  /* Set input values */
  /* ---------------- */
  p2a_proc_id_in   = XL_PROC;
  p2a_time_ref_in  = XL_TIME_UT1;
  p2a_ascii_id_out = XL_ASCII_STD_REF_MICROSEC;
  p2a_time_ref_out = XL_TIME_TAI;

  p2a_processing_in = 3775.591370370370370;

  /* Call xl_time_processing_to_ascii function */
  /* ----------------------------------------- */
  status = xl_time_processing_to_ascii(&time_id,  &p2a_proc_id_in,  &p2a_time_ref_in,
                                       &p2a_processing_in, &p2a_ascii_id_out, &p2a_time_ref_out,
                                       p2a_ascii_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_PROCESSING_TO_ASCII_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- proc_id_in       : %ld ",    p2a_proc_id_in);    /* Input Time Format */
  printf("\n- time_ref_in      : %ld ",    p2a_time_ref_in);   /* Input Time Reference */
  printf("\n- processing_in    : %12.12lf",p2a_processing_in); /* Input Processing Time */
  printf("\n- ascii_id_out     : %ld ",    p2a_ascii_id_out);  /* Output Time Format */
  printf("\n- time_ref_out     : %ld ",    p2a_time_ref_out);  /* Output Time Reference */
  printf("\n- ascii_out        : %s ",     p2a_ascii_out);     /* Output Ascii Time */


  /* ------------------------------------------------------------------------ */
  /* From Processing to Transport(CryoSat-TM) time format                     */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_processing_to_transport                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_PROCESSING_TO_TRANSPORT\n");

  /* Set input values */
  /* ---------------- */
  p2t_proc_id_in   = XL_PROC;
  p2t_time_ref_in  = XL_TIME_TAI;
  p2t_trans_id_out = XL_TRANS_CRYO_TM;
  p2t_time_ref_out = XL_TIME_UTC;

  p2t_processing_in = 245.1;  /* TAI time [days] */

  /* Call xl_time_processing_to_transport function */
  /* -------------------------------------------- */
  status = xl_time_processing_to_transport(&time_id, &p2t_proc_id_in,
                                           &p2t_time_ref_in, &p2t_processing_in, &p2t_trans_id_out,
                                           &p2t_time_ref_out, p2t_transport_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_PROCESSING_TO_TRANSPORT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- proc_id_in       : %ld ",    p2t_proc_id_in);       /* Time Format */
  printf("\n- time_ref_in      : %ld ",    p2t_time_ref_in);      /* Time Reference */
  printf("\n- processing_in    : %12.12lf",p2t_processing_in);    /* TAI time in XL_PROC format [days] */
  printf("\n- trans_id_out     : %ld ",    p2t_trans_id_out);     /* Time Format */
  printf("\n- time_ref_out     : %ld ",    p2t_time_ref_out);     /* Time Reference */
  printf("\n- transport_out[0] : %ld ",    p2t_transport_out[0]); /* UTC time in XL_TRANS_CRYO_TM format [integer days] */
  printf("\n- transport_out[1] : %ld ",    p2t_transport_out[1]); /* UTC time in XL_TRANS_CRYO_TM format [integer milliseconds] */
  printf("\n- transport_out[2] : %ld ",    p2t_transport_out[2]); /* UTC time in XL_TRANS_CRYO_TM format [integer microseconds] */



  /* ------------------------------------------------------------------------ */
  /* From Processing to Processing time format                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_processing_to_processing                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_PROCESSING_TO_PROCESSING\n");

  /* Set input values */
  /* ---------------- */
  p2p_proc_id_in   = XL_PROC;
  p2p_time_ref_in  = XL_TIME_TAI;
  p2p_proc_id_out  = XL_PROC;
  p2p_time_ref_out = XL_TIME_UTC;

  p2p_processing_in = 245.1;  /* TAI time [days] */

  /* Call xl_time_processing_to_processing function */
  /* ---------------------------------------------- */
  status = xl_time_processing_to_processing(&time_id, &p2p_proc_id_in,
                                            &p2p_time_ref_in, &p2p_processing_in, &p2p_proc_id_out,
                                            &p2p_time_ref_out, &p2p_processing_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_PROCESSING_TO_PROCESSING_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- proc_id_in       : %ld ",      p2p_proc_id_in);     /* Time Format */
  printf("\n- time_ref_in      : %ld ",      p2p_time_ref_in);    /* Time Reference */
  printf("\n- processing_in    : %12.12lf ", p2p_processing_in);  /* TAI time in XL_PROC format [days] */
  printf("\n- proc_id_out      : %ld ",      p2p_proc_id_out);    /* Time Format */
  printf("\n- time_ref_out     : %ld ",      p2p_time_ref_out);   /* Time Reference */
  printf("\n- processing_out   : %12.12lf ", p2p_processing_out); /* UTC time in XL_PROC format [days] */


  /* ------------------------------------------------------------------------ */
  /* From Ascii(STD) to Ascii(COMPACT_REF_MICROSEC) time format               */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ascii_to_ascii                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_ASCII_TO_ASCII\n");

  /* Set input values */
  /* ---------------- */
  a2a_ascii_id_in  = XL_ASCII_STD;
  a2a_time_ref_in  = XL_TIME_TAI;
  a2a_ascii_id_out = XL_ASCII_COMPACT_REF_MICROSEC;
  a2a_time_ref_out = XL_TIME_UT1;

  strcpy (a2a_ascii_in, "2010-05-03_14:12:10");

  /* Call xl_time_ascii_to_ascii function */
  /* ------------------------------------ */
  status = xl_time_ascii_to_ascii(&time_id,  &a2a_ascii_id_in,  &a2a_time_ref_in,
                                  a2a_ascii_in, &a2a_ascii_id_out, &a2a_time_ref_out,
                                  a2a_ascii_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_ASCII_TO_ASCII_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- ascii_id_in      : %ld ", a2a_ascii_id_in);  /* Input Time Format */
  printf("\n- time_ref_in      : %ld ", a2a_time_ref_in);  /* Input Time Reference */
  printf("\n- ascii_in         : %s ",  a2a_ascii_in);     /* Input Ascii Time */
  printf("\n- ascii_id_out     : %ld ", a2a_ascii_id_out); /* Output Time Format */
  printf("\n- time_ref_out     : %ld ", a2a_time_ref_out); /* Output Time Reference */
  printf("\n- ascii_out        : %s ",  a2a_ascii_out);    /* Output Ascii Time */


  /* ------------------------------------------------------------------------ */
  /* From Ascii(STD) to Transport(CryoSat-TM) time format                     */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ascii_to_transport                                  */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_ASCII_TO_TRANSPORT\n");

  /* Set input values */
  /* ---------------- */
  a2t_ascii_id_in  = XL_ASCII_STD;
  a2t_time_ref_in  = XL_TIME_TAI;
  a2t_trans_id_out = XL_TRANS_CRYO_TM;
  a2t_time_ref_out = XL_TIME_UT1;

  strcpy (a2t_ascii_in, "2010-05-03_14:12:10");

  /* Call xl_time_ascii_to_transport function */
  /* ---------------------------------------- */
  status = xl_time_ascii_to_transport(&time_id,  &a2t_ascii_id_in,  &a2t_time_ref_in,
                                      a2t_ascii_in, &a2t_trans_id_out, &a2t_time_ref_out,
                                      a2t_transport_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_ASCII_TO_TRANSPORT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- ascii_id_in      : %ld ", a2t_ascii_id_in);      /* Input Time Format */
  printf("\n- time_ref_in      : %ld ", a2t_time_ref_in);      /* Input Time Reference */
  printf("\n- ascii_in         : %s " , a2t_ascii_in);         /* Input Ascii Time */
  printf("\n- trans_id_out     : %ld ", a2t_trans_id_out);     /* Output Time Format */
  printf("\n- time_ref_out     : %ld ", a2t_time_ref_out);     /* Output Time Reference */
  printf("\n- transport_out[0] : %ld ", a2t_transport_out[0]); /* Output Transport Time [integer days] */
  printf("\n- transport_out[1] : %ld ", a2t_transport_out[1]); /* Output Transport Time [integer milliseconds] */
  printf("\n- transport_out[2] : %ld ", a2t_transport_out[2]); /* Output Transport Time [integer microseconds] */


  /* ------------------------------------------------------------------------ */
  /* From Ascii(STD) to Processing time format                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_ascii_to_processing                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_ASCII_TO_PROCESSING\n");

  /* Set input values */
  /* ---------------- */
  a2p_ascii_id_in  = XL_ASCII_STD;
  a2p_time_ref_in  = XL_TIME_TAI;
  a2p_proc_id_out  = XL_PROC;
  a2p_time_ref_out = XL_TIME_UT1;

  strcpy (a2p_ascii_in, "2010-05-03_14:12:10");

  /* Call xl_time_ascii_to_processing function */
  /* ----------------------------------------- */
  status = xl_time_ascii_to_processing(&time_id,  &a2p_ascii_id_in,  &a2p_time_ref_in,
                                       a2p_ascii_in, &a2p_proc_id_out, &a2p_time_ref_out,
                                       &a2p_processing_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_ASCII_TO_PROCESSING_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- ascii_id_in      : %ld ",    a2p_ascii_id_in);    /* Input Time Format */
  printf("\n- time_ref_in      : %ld ",    a2p_time_ref_in);    /* Input Time Reference */
  printf("\n- ascii_in         : %s " ,    a2p_ascii_in);       /* Input Ascii Time */
  printf("\n- proc_id_out      : %ld ",    a2p_proc_id_out);    /* Output Time Format */
  printf("\n- time_ref_out     : %ld ",    a2p_time_ref_out);   /* Output Time Reference */
  printf("\n- processing_out   : %12.12lf",a2p_processing_out); /* Output Processing Time */



  /* ------------------------------------------------------------------------ */
  /* Time Id. Accessor                                                        */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_init_status                                         */
  /*              xl_time_get_sat_id                                          */
  /*              xl_time_get_mode                                            */
  /*              xl_time_get_id_data                                         */
  /*              xl_time_set_id_data                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nTIME ID. ACCESSORS\n");

  flag = xl_time_init_status(&time_id);

  if (flag)
  {
    printf("\n- Time id is initialized");
  } 
  else
  {
    printf("\n- Time id is NOT initialized");
  }

  sat_id = xl_time_get_sat_id(&time_id);
  printf("\n- Satellite Id: %d", sat_id);

  time_mode = xl_time_get_mode(&time_id);
  printf("\n- Time Id mode: %d", time_mode);

  status = xl_time_get_id_data(&time_id, &time_id_data);

  printf("\n- leap flag      : %ld ", time_id_data.leap_sec.flag);  
  printf("\n- leap_utc time  : %f ",  time_id_data.leap_sec.utc_time);
  for (i = 0; i < time_id_data.num_lines; i++)
  {
    printf("\n- TAI time       : %f ", time_id_data.time_str[i].tai_time);
    printf("\n- UT1 time       : %f ", time_id_data.time_str[i].ut1_time);
    printf("\n- tai_utc        : %f ", time_id_data.time_str[i].tai_utc);
    printf("\n- tai_ut1        : %f ", time_id_data.time_str[i].tai_ut1);
    printf("\n- tai_gps        : %f ", time_id_data.time_str[i].tai_gps);
  }

  status = xl_time_set_id_data(&time_id, &time_id_data);

  free(time_id_data.time_str);



/******************************************************************************/
/*                                                                            */
/* Other time functions                                                       */
/*                                                                            */
/******************************************************************************/


  /* ------------------------------------------------------------------------ */
  /* Add two times in Processing time format                                  */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_add                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_ADD\n");

  /* Set input values */
  /* ---------------- */
  proc_id  = XL_PROC;
  time_ref = XL_TIME_TAI;

  processing_in_1 = 245.100001;   /* Processing Time, MJD2000 [days] */
  processing_in_2 = 110.123456;   /* Added duration [days] */

  /* Call xl_time_add function */
  /* ------------------------- */
  status = xl_time_add(&proc_id, &time_ref, &processing_in_1,
                       &processing_in_2, &processing_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_ADD_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- proc_id          : %ld ",      proc_id);         /* Time Format */
  printf("\n- time_ref         : %ld ",      time_ref);        /* Time Reference */
  printf("\n- processing_in    : %12.12lf ", processing_in_1); /* Time in XL_PROC format [days] */
  printf("\n- added_duration   : %12.12lf ", processing_in_2); /* Time in XL_PROC format [days] */
  printf("\n- processing_out   : %12.12lf ", processing_out);  /* Time in XL_PROC format [days] */


  /* ------------------------------------------------------------------------ */
  /* Compute the difference between two times in Processing time format       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_diff                                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_DIFF\n");

  /* Set input values */
  /* ---------------- */
  proc_id  = XL_PROC;
  time_ref = XL_TIME_TAI;

  processing_in_1 = 245.123456;   /* Processing Time, MJD2000 [days] */
  processing_in_2 = 110.100001;   /* Processing Time, MJD2000 [days] */

  /* Call xl_time_diff function */
  /* -------------------------- */
  status = xl_time_diff(&proc_id, &time_ref, &processing_in_1,
                        &processing_in_2, &processing_out, xl_ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_DIFF_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- proc_id          : %ld ",      proc_id);         /* Time Format */
  printf("\n- time_ref         : %ld ",      time_ref);        /* Time Reference */
  printf("\n- processing_in_1  : %12.12lf ", processing_in_1); /* Time in XL_PROC format [days] */
  printf("\n- processing_in_2  : %12.12lf ", processing_in_2); /* Time in XL_PROC format [days] */
  printf("\n- processing_out   : %12.12lf ", processing_out);  /* Time in XL_PROC format [days] */



  /* ------------------------------------------------------------------------ */
  /* From On-Board to Processing time format                                  */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_obt_to_time                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_OBT_TO_TIME\n");

  /* Set input values */
  /* ---------------- */
  sat_id   = XL_SAT_ENVISAT;

  proc_id  = XL_PROC;

  time0   = 245.123456789000000;   /* [days] */
  obt0[0] = 0x00001001;
  obt0[1] = 0x00011111;
  period0 = (1/256.0)*1.0E12; /* [picoseconds] */
  obt[0]  = 0xFFFF0FFF;
  obt[1]  = 0x000FF000;

  envisat_obt_param.sat_id  = sat_id;
  envisat_obt_param.time0   = time0;
  envisat_obt_param.obt0[0] = obt0[0];
  envisat_obt_param.obt0[1] = obt0[1];
  envisat_obt_param.period0 = period0;

  envisat_obt_value.sat_id  = sat_id;
  envisat_obt_value.obt[0]  = obt[0];
  envisat_obt_value.obt[1]  = obt[1];

  /* Call xl_time_obt_to_time function */
  /* --------------------------------- */
  status = xl_time_obt_to_time(&sat_id, &proc_id, &envisat_obt_param, 
                               &envisat_obt_value, &time_out, xl_ierr);


  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_OBT_TO_TIME_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- sat_id           : %ld ",      sat_id);          /* Satellite ID */
  printf("\n- proc_id          : %ld ",      proc_id);         /* Time Format */
  printf("\n- time0            : %20.20lf ", time0);           /* Input time in XL_PROC format [days] */
  printf("\n- period0          : %lu ",      period0);         /* OB Clock Period [picoseconds] */
  printf("\n- obt0[0]          : %lu ",      obt0[0]);         /* OBT counter (Most Significant bytes) */
  printf("\n- obt0[1]          : %lu ",      obt0[1]);         /* OBT counter (Least Significant bytes) */
  printf("\n- obt0[0] (X)      : %8lX ",     obt0[0]);         /* OBT counter (Most Significant bytes) */
  printf("\n- obt0[1] (X)      : %8lX ",     obt0[1]);         /* OBT counter (Least Significant bytes) */
  printf("\n- obt[0]           : %lu ",      obt[0]);          /* OBT counter (Most Significant bytes) */
  printf("\n- obt[1]           : %lu ",      obt[1]);          /* OBT counter (Least Significant bytes) */
  printf("\n- obt[0] (X)       : %8lX ",     obt[0]);          /* OBT counter (Most Significant bytes) */
  printf("\n- obt[1] (X)       : %8lX ",     obt[1]);          /* OBT counter (Least Significant bytes) */
  printf("\n- time_out         : %20.20lf ", time_out);        /* Output time in XL_PROC format [days] */


  /* ------------------------------------------------------------------------ */
  /* From Processing to On-Board time format                                  */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_time_time_to_obt                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\n\nXL_TIME_TIME_TO_OBT\n");

  /* Set input values */
  /* ---------------- */
  sat_id   = XL_SAT_ENVISAT;

  proc_id  = XL_PROC;
  time_in  = 245.120493735624819;   /* [days] */

  time0    = 245.123456789000000;   /* [days] */
  obt0[0]  = 0x00001001;
  obt0[1]  = 0x00011111;
  period0  = (1/256.0)*1.0E12; /* [picoseconds] */

  envisat_obt_param.sat_id  = sat_id;
  envisat_obt_param.time0   = time0;
  envisat_obt_param.obt0[0] = obt0[0];
  envisat_obt_param.obt0[1] = obt0[1];
  envisat_obt_param.period0 = period0;

  /* Call xl_time_time_to_obt function */
  /* --------------------------------- */
  status = xl_time_time_to_obt(&sat_id, &proc_id, &envisat_obt_param, 
                               &time_in, &envisat_obt_value, xl_ierr);


  /* Print output values */
  /* ------------------- */

  if (status != XL_OK)
  {
     func_id = XL_TIME_TIME_TO_OBT_ID;
     xl_get_msg(&func_id, xl_ierr, &n, msg);
     xl_print_msg(&n, msg);
     if (status <= XL_ERR) return(XL_ERR);    /* CAREFUL: normal status */
  }

  printf("\n- sat_id           : %ld ",      sat_id);          /* Satellite ID */
  printf("\n- proc_id          : %ld ",      proc_id);         /* Time Format */
  printf("\n- time_in          : %20.20lf ", time_in);         /* Input time in XL_PROC format [days] */
  printf("\n- time0            : %20.20lf ", time0);           /* Input time in XL_PROC format [days] */
  printf("\n- period0          : %lu ",      period0);         /* OB Clock Period [picoseconds] */
  printf("\n- obt0[0]          : %lu ",      obt0[0]);         /* OBT counter (Most Significant bytes) */
  printf("\n- obt0[1]          : %lu ",      obt0[1]);         /* OBT counter (Least Significant bytes) */
  printf("\n- obt0[0] (X)      : %8lX ",     obt0[0]);         /* OBT counter (Most Significant bytes) */
  printf("\n- obt0[1] (X)      : %8lX ",     obt0[1]);         /* OBT counter (Least Significant bytes) */
  printf("\n- obt[0]           : %lu ",      envisat_obt_value.obt[0]);  /* OBT counter (Most Significant bytes) */
  printf("\n- obt[1]           : %lu ",      envisat_obt_value.obt[1]);  /* OBT counter (Least Significant bytes) */
  printf("\n- obt[0] (X)       : %8lX ",     envisat_obt_value.obt[0]);  /* OBT counter (Most Significant bytes) */
  printf("\n- obt[1] (X)       : %8lX ",     envisat_obt_value.obt[1]);  /* OBT counter (Least Significant bytes) */




  /* ------------------------------------------------------------------------ */
  /* Calculation of relations between rotated vectors                         */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_get_rotated_vectors, xl_get_rotation_angles              */
  /* ------------------------------------------------------------------------ */
  
  /* Set input values */
  /* ---------------- */
  x_in[0]=1. ; x_in[1]=0. ; x_in[2]=0. ;
  y_in[0]=0. ; y_in[1]=1. ; y_in[2]=0. ;
  z_in[0]=0. ; z_in[1]=0. ; z_in[2]=1. ;

  x_out[0]=0. ; x_out[1]=1. ; x_out[2]=0. ; 
  y_out[0]=-1. ; y_out[1]=0. ; y_out[2]=1. ;
  z_out[0]=1. ; z_out[1]=0. ; z_out[2]=1. ;

  
  /* Call to function xl_get_rotation_angles */
  /* --------------------------------------- */
  printf("\n\n\nXL_GET_ROTATION_ANGLES\n");

  xl_get_rotation_angles (x_in,y_in,z_in,x_out,y_out,z_out,ang_out, xl_ierr);

  /* Print results */
  /* ------------- */
  printf("\n- Final Vector     :                  "                           );      
  printf("\n- x vector         : %8.3f %8.3f %8.3f",x_out[0],x_out[1],x_out[2]);
  printf("\n- y vector         : %8.3f %8.3f %8.3f",y_out[0],y_out[1],y_out[2]);
  printf("\n- z vector         : %8.3f %8.3f %8.3f",z_out[0],z_out[1],z_out[2]);
  printf("\n- Rotation angles  :                  "                           );
  printf("\n- Roll             : %9.3f            ",ang_out[0]                );
  printf("\n- Pitch            : %9.3f            ",ang_out[1]                );
  printf("\n- Yaw              : %9.3f            ",ang_out[2]                );

  ang_in[0] = ang_out[0] ; ang_in[1] = ang_out[1] ; ang_in[2] = ang_out[2] ;


  /* Call to function xl_get_rotated_vectors */
  /* --------------------------------------- */

  printf("\n\n\nXL_GET_ROTATED_VECTORS\n");
  
  xl_get_rotated_vectors(x_in,y_in,z_in,ang_in,x_out,y_out,z_out, xl_ierr);

  /* Print results */
  /* ------------- */
  printf("\n- Rotation angles  :                  "                           );
  printf("\n- Roll             : %9.3f            ",ang_out[0]                );
  printf("\n- Pitch            : %9.3f            ",ang_out[1]                );
  printf("\n- Yaw              : %9.3f            ",ang_out[2]                );
  printf("\n- Final Vector     :                  "                           );      
  printf("\n- x vector         : %8.3f %8.3f %8.3f",x_out[0],x_out[1],x_out[2]);
  printf("\n- y vector         : %8.3f %8.3f %8.3f",y_out[0],y_out[1],y_out[2]);
  printf("\n- z vector         : %8.3f %8.3f %8.3f",z_out[0],z_out[1],z_out[2]);

  
  /* ------------------------------------------------------------------------ */
  /* Calculation of the satellite orbital position                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_position_on_orbit                                        */
  /* ------------------------------------------------------------------------ */
  
  /* Set input values */
  /* ---------------- */
   time_ref  = XL_TIME_UT1;
   poo_time  = 0.0;	       	/* UT1 time in MJD2000 [days] */
   
   poo_pos[0]    =        0.138;      /* Position vector (x,y,z) [m] */
   poo_pos[1]    = -2365612.059;
   poo_pos[2]    =  6763859.946;
   poo_vel[0]    =      132.303801;   /* Velocity vector (x,y,z) [m/s] */
   poo_vel[1]    =    -1203.845511;
   poo_vel[2]    =       73.224410;
   poo_acc[0]    =        0.0634168;	      /* Acceleration vector (x,y,z) [m/s2] */
   poo_acc[1]    =       -0.0249763;
   poo_acc[2]    =       -0.3018956;

   deriv = XL_DER_2ND;

  /* Call to function xl_position_on_orbit */
  /* ------------------------------------- */
   printf("\n\n\nXL_POSITION_ON_ORBIT\n");

   status = xl_position_on_orbit(&model_id, &time_id,&angle_type,&time_ref,&poo_time,
				 poo_pos,poo_vel,poo_acc,&deriv,
				 &angle_out,&angle_rate_out,&angle_rate_rate_out,
				 xl_ierr);

  /* Print results */
  /* ------------- */
   printf("\n- Input Values          :                          "                                   );
   printf("\n- Time_ref              : %ld                      ",time_ref                          );
   printf("\n- Time                  : %5.3f                    ",poo_time                          );
   printf("\n- Sat Position          : [%12.3lf,%12.3lf,%12.3lf]",poo_pos[0], poo_pos[1], poo_pos[2]);
   printf("\n- Sat Velocity          : [%12.6lf,%12.6lf,%12.6lf]",poo_vel[0], poo_vel[1], poo_vel[2]);
   printf("\n- Sat Acceleration      : [%12.9lf,%12.9lf,%12.9lf]",poo_acc[0], poo_acc[1], poo_acc[2]);
   printf("\n- Output Values                        :           "                                   );
   printf("\n- Satellite position angle             : %12.3f     ",angle_out                        );           
   printf("\n- Satellite position angle_rate        : %12.6f     ",angle_rate_out                   );
   printf("\n- Satellite position angle_rate_rate   : %12.9f     ",angle_rate_rate_out              );

  /* ------------------------------------------------------------------------  */
  /* Conversion between cartesian coordinates and ra and declination          */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_cart_to_radec                                            */
  /* ------------------------------------------------------------------------ */
  
  /* Set input values */
  /* ---------------- */
   pos[0] = -8.82*pc;
   pos[1] = -5.93*pc;
   pos[2] = 3.7*pc;

   vel[0] = -57.7E3;
   vel[1] = 31.5E3;
   vel[2] = -102.3E3;

  /* Call to function xl_cart_to_radec */
  /* ------------------------------------- */
   printf("\n\n\nXL_CART_TO_RADEC\n");

   status = xl_cart_to_radec(&model_id, &mode, &cs_in, pos, vel, 
			     &ra, &dec,
			     &mu_ra, &mu_dec, 
			     &rad_vel, &par, xl_ierr);

  /* Print results */
  /* ------------- */
   printf("\n- Input Values          :                          "                                   );
   printf("\n- X                     : %f                       ",pos[0]                            );
   printf("\n- Y                     : %f                       ",pos[1]                            );
   printf("\n- Z                     : %f                       ",pos[2]                            );
   printf("\n- VX                    : %f                       ",vel[0]                            );
   printf("\n- VY                    : %f                       ",vel[1]                            );
   printf("\n- VZ                    : %f                       ",vel[2]                            );
   printf("\n- Output Values         :                          "                                   );
   printf("\n- ra                    : %f                       ",ra                                );           
   printf("\n- dec                   : %f                       ",dec                               );
   printf("\n- rad_vel               : %f                       ",rad_vel                           );
   printf("\n- mu_ra                 : %f                       ",mu_ra                             );
   printf("\n- mu_dec                : %f                       ",mu_dec                            );

  /* ------------------------------------------------------------------------ */
  /* Conversion between  ra and declination and cartesian coordinates         */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xl_radec_to_cart                                            */
  /* ------------------------------------------------------------------------ */
  
  /* Set input values */
  /* ---------------- */
   ra      =  3.733510e0;
   dec     =  3.350102e-1;
   mu_ra   = -5.301311e-4;
   mu_dec  = -9.685468e-4;
   rad_vel = -1.057037e2;
   par     =  4.308008e-7;

  /* Call to function xl_radec_to_cart */
  /* ------------------------------------- */
   printf("\n\n\nXL_RADEC_TO_CART\n");

   status = xl_radec_to_cart(&model_id, &mode, &cs_in, &ra, &dec,
  	                     &mu_ra, &mu_dec, &rad_vel, &par, pos, vel, xl_ierr);

  /* Print results */
  /* ------------- */
   printf("\n- Input Values          :                          "                                   );
   printf("\n- ra                    : %f                       ",ra                                );           
   printf("\n- dec                   : %f                       ",dec                               );
   printf("\n- rad_vel               : %f                       ",rad_vel                           );
   printf("\n- mu_ra                 : %f                       ",mu_ra                             );
   printf("\n- mu_dec                : %f                       ",mu_dec                            );
   printf("\n- Output Values         :                          "                                   );
   printf("\n- X                     : %f                       ",pos[0]                            );
   printf("\n- Y                     : %f                       ",pos[1]                            );
   printf("\n- Z                     : %f                       ",pos[2]                            );
   printf("\n- VX                    : %f                       ",vel[0]                            );
   printf("\n- VY                    : %f                       ",vel[1]                            );
   printf("\n- VZ                    : %f                       ",vel[2]                            );


  /* -------------------------------------------------------------------- */
  /* Conversion from Euler angles to rotation matrix                      */
  /* -------------------------------------------------------------------- */
  /* Function(s): xl_euler_to_matrix                                      */
  /* -------------------------------------------------------------------- */

  /* Set input values */
  /* ---------------- */
   euler_ang[0] = 45.;
   euler_ang[1] = 90.;
   euler_ang[2] = 20.;

  /* Call to function xl_euler_to_matrix */
  /* ----------------------------------- */
   printf("\n\n\nXL_EULER_TO_MATRIX\n");

   status = xl_euler_to_matrix(euler_ang, rot_matrix, xl_ierr);
   
  /* Print results */
  /* ------------- */
   printf("\n- Input Values");
   printf("\n     Euler angles       : %f \t %f \t %f              ", euler_ang[0], euler_ang[1], euler_ang[2]);
   printf("\n- Output Values");
   printf("\n-    Rotation matrix    : %f \t %f \t %f              ", rot_matrix[0][0], rot_matrix[0][1], rot_matrix[0][2]);
   printf("\n                        : %f \t %f \t %f              ", rot_matrix[1][0], rot_matrix[1][1], rot_matrix[1][2]);
   printf("\n                        : %f \t %f \t %f              ", rot_matrix[2][0], rot_matrix[2][1], rot_matrix[2][2]);


  /* -------------------------------------------------------------------- */
  /* Conversion from rotation matrix to Euler angles                      */
  /* -------------------------------------------------------------------- */
  /* Function(s): xl_matrix_to_euler                                      */
  /* -------------------------------------------------------------------- */

   /* using previous matrix */

   /* Call to function xl_matrix_to_euler */
   /* ----------------------------------- */
   printf("\n\n\nXL_MATRIX_TO_EULER\n");

   status = xl_matrix_to_euler(rot_matrix, euler_ang, xl_ierr);

  /* Print results */
  /* ------------- */

   printf("\n- Input Values");
   printf("\n-    Rotation matrix    : %f \t %f \t %f             ", rot_matrix[0][0], rot_matrix[0][1], rot_matrix[0][2]);
   printf("\n                        : %f \t %f \t %f             ", rot_matrix[1][0], rot_matrix[1][1], rot_matrix[1][2]);
   printf("\n                        : %f \t %f \t %f             ", rot_matrix[2][0], rot_matrix[2][1], rot_matrix[2][2]);
   printf("\n- Output Values");
   printf("\n     Euler angles       : %f \t %f \t %f             ", euler_ang[0], euler_ang[1], euler_ang[2]);
	 

  /* -------------------------------------------------------------------- */
  /* Star coordinates conversion from Fk4 to FK5                          */
  /* -------------------------------------------------------------------- */
  /* Function(s): xl_star_catalog                                         */
  /* -------------------------------------------------------------------- */


   printf("\n\n\nXL_STAR_CATALOG\n");

 
   /* inputs */
   time_ref = XL_TIME_UTC;
   time = 1646.0;
   mode = 0;

   catalog_in  = XL_FK4;
   catalog_out = XL_FK5;

   ra0     = 6.27906181420277;
   dec0    = -1.34986658532673;
   mu_ra0  = -0.0001394081738438; 
   mu_dec0 = -0.0000857635400903;
   
   rad_vel0 = 0.;
   par0    =  0.; 


   /* get star coordinates for the input time */
   status = xl_star_catalog(&model_id, &time_id, &time_ref, &time, &mode,
                            &catalog_in, &catalog_out, 
                            &ra0, &dec0, 
                            &mu_ra0, &mu_dec0, 
                            &rad_vel0, &par0,
                            /* output */
                            &ra, &dec, xl_ierr);
   /* Print results */
   /* ------------- */
   printf("\n- Input Values");  
   printf("\n       time = %.2f\n",time);;
   printf("\n       RA = %.6f, \tDec = %.5f\n", ra0, dec0);
   printf("\n       mu_ra = %.6f, \tmu_dec = %.6f\n", mu_ra0, mu_dec0);
   printf("\n       rad_vel = %.2f, \tparallax = %.6f\n", rad_vel0, par0);

   printf("\n- Output Values");
   printf("\n       RA = %.6f, \tDec = %.5f\n", ra, dec);


  /* -------------------------------------------------------------------- */
  /* Conversion between EF and Topocentric coordinates                    */
  /* -------------------------------------------------------------------- */
  /* Function(s): xl_ef_to_topocentric & xl_topocentric_to ef             */
  /* -------------------------------------------------------------------- */

   printf("\n\n\nXL_TOPOCENTRIC_TO_EF\n");

   /* inputs */
   mode  = XL_MODE_FLAG_LOCATION;
   deriv = XL_DER_1ST;
   azim = 20;
   elev = 30;
   range = 10000;
   azim_d = 0;
   elev_d = 0;
   range_d = 0;

   pos[0] = 3460675.389;
   pos[1] = 2903851.443;
   pos[2] = 4487348.409;

   vel[0] = 0.;
   vel[1] = 0.;
   vel[2] = 0.;

   printf("\n   INPUTS.\n");
   printf("\n       Mode = %s\n", (mode ==XL_MODE_FLAG_LOCATION? "LOCATION" : "DIRECTION"));
   printf("\n       Deriv = %s\n", (deriv == XL_NO_DER? "No Derivatives" : "1st. Derivative"));
   printf("\n       Center of the Topocentric CS   = %.3lf,  %.3lf, %.3lf\n", pos[0], pos[1], pos[2]);
   printf("\n       Velocity of the Topocentric CS = %.3lf,  %.3lf, %.3lf\n", vel[0], vel[1], vel[2]);
   printf("\n       Azimuth, Elevation, Altitude = %.3lf,  %.3lf, %.3lf\n", azim, elev, range);
   printf("\n       Rates for Azimuth, Elevation, Altitude = %.3lf,  %.3lf, %.3lf\n", azim_d, elev_d, range_d);

  /* topocentric to EF CS  */
  status = xl_topocentric_to_ef(&model_id, &mode, &deriv, pos, vel, 
                                &azim, &elev, &range,
                                &azim_d, &elev_d, &range_d, 
                                ef_dir, ef_dir_d, xl_ierr);
  printf("\n   OUTPUTS.\n");
  printf("\n     EF position = %.3f, %.3f, %.3f\n", ef_dir[0], ef_dir[1], ef_dir[2]);
  printf("\n     EF velocity = %.3f, %.3f, %.3f\n", ef_dir_d[0], ef_dir_d[1], ef_dir_d[2]);

  /* EF to topocentric */
  printf("\n\n\nXL_EF_TO_TOPOCENTRIC\n");

  status = xl_ef_to_topocentric(&model_id, &mode, &deriv, pos, vel,
                                ef_dir, ef_dir_d,
                                &azim, &elev, &range,
                                &azim_d, &elev_d, &range_d,                           
                                xl_ierr);
  printf("\n   OUTPUTS.\n");
  printf("\n     Topocentric Azimuth, Elevation, Range = %.3f, %.3f, %.3f\n", azim, elev, range);
  printf("\n     Rates for Topocentric Azimuth, Elevation, Range = %.3f, %.3f, %.3f\n", azim_d, elev_d, range_d);

  /* -------------------------------------------------------------------- */
  /* Computation of geoid undulation                                      */
  /* -------------------------------------------------------------------- */
  /* Function(s): xl_geoid_calc                                           */
  /* -------------------------------------------------------------------- */

  printf("\n\n\nXL_GEOID_CALC\n");
  
  /* inputs */
  geoid_in.model_id      = &model_id;
  geoid_in.nof_harmonics = 360;
  geoid_in.utc_time      = 0.;
  
  geoid_in.latitude  = 45.;
  geoid_in.longitude = 30.;
  
  printf("   INPUTS.\n");
  printf("       Number of harmonics = %ld\n", geoid_in.nof_harmonics);
  printf("       UTC time = %lf\n", geoid_in.utc_time);
  printf("       Latitude = %lf deg\n", geoid_in.latitude);
  printf("       Longitude = %lf deg\n", geoid_in.longitude);
  
  /* Geoid calculation  */
  status = xl_geoid_calc(&geoid_in, &geoid_out, xl_ierr);
  
  printf("   OUTPUTS.\n");
  printf("     Undulation = %lf\n", geoid_out.undulation);

   /* Call xl_time_close function */
   /* --------------------------- */
   xl_time_close(&time_id, xl_ierr);
   xl_model_close(&model_id, xl_ierr);
 
   printf("\nEOCFI_LIB EXAMPLE COMPLETED SUCCESSFULLY\n"); 
 
  return(XL_OK);
}

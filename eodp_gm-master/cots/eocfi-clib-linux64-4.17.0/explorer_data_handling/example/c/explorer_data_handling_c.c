 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Module      : explorer_data_handling_c.c
 *
 * Functions   : main program (EXPLORER_DATA_HANDLING example) to call:
 *
 *                  o Reading functions
 *                    - 
 *                  o Writing functions
 *                    - 
 *
 * Purpose     : Example program to show the way to call the previous functions.
 *
 * Reference   : -
 *
 * History:     +-----------------------------------------------------------------------------+
 *              | Version |   Date   |       Name        | Change                             |
 *              |-----------------------------------------------------------------------------|
 *              |    3.3  | 11/07/05 | DEIMOS Space S.L. | First release                      |
 *              +-----------------------------------------------------------------------------+
 *              |    3.4  | 18/11/05 | DEIMOS Space S.L. | Library exposed to users           |
 *              +-----------------------------------------------------------------------------+
 *              |    3.5  | 26/05/06 | DEIMOS Space S.L. | New features:                      |
 *              |         |          |                   |  + Thread safe library             |
 *              |         |          |                   |  + C99 compliant                   |
 *              |         |          |                   |  + Optimized libray                |
 *              |         |          |                   |  + 64-Bits library for MACOS,      |
 *              |         |          |                   |    LINUX and SOLARIS               |
 *              +-----------------------------------------------------------------------------+
 *              |    3.6  | 24/11/06 | DEIMOS Space S.L. | New routines:                      |
 *              |         |          |                   |  + xd_xml_validate                 |
 *              |         |          |                   | New executable function:           |
 *              |         |          |                   |  + xml_validator                   |
 *              +-----------------------------------------------------------------------------+
 *              |    3.7  | 13/07/07 | DEIMOS Space S.L. | Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + expcfi_check_libs               |
 *              |         |          |                   |  + library version for Mac OS X    |
 *              |         |          |                   |    on Intel (32 and 64 bits)       |
 *              +-----------------------------------------------------------------------------+
 *              |  3.7.2  | 31/07/08 | DEIMOS Space S.L. | Maintenance release                |
 *              +-----------------------------------------------------------------------------+
 *              |    4.0  | 19/01/09 | DEIMOS Space S.L. | Maintenance release                |
 *              +-----------------------------------------------------------------------------+
 *              |    4.1  | 07/05/10 | DEIMOS Space S.L. | Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + DEM GETASSEv2 supported         |
 *              |         |          |                   |  + IERS B Bulletin format 2010     |
 *              |         |          |                   |  + Ground Station DB 1.4 supported |
 *              +-----------------------------------------------------------------------------+
 *              |    4.2  | 31/01/11 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + New Dem configuration file      |
 *              |         |          |                   |    (schema version 1.3)            |
 *              |         |          |                   |  + NORAD TLE designators for       |
 *              |         |          |                   |    SMOS, GOCE and CRYOSAT          |
 *              |         |          |                   |  + New OSF format for curved MLST  |
 *              +-----------------------------------------------------------------------------+
 *              |    4.3  | 06/02/12 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for reading new IERS    |
 *              |         |          |                   |    bulletins A and B               |
 *              |         |          |                   |  + New functions to decimate orbit |
 *              |         |          |                   |    and attitude data               |
 *              |         |          |                   |    (xd_orbit_file_decimate and     |
 *              |         |          |                   |     xd_attitude_file_decimate)     |
 *              +-----------------------------------------------------------------------------+
 *              |    4.4  | 05/07/12 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + New tags in Dem configuration   |
 *              |         |          |                   |    for DEM cache                   |
 *              +-----------------------------------------------------------------------------+
 *              |    4.5  | 01/03/13 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + New tags in Dem configuration   |
 *              |         |          |                   |    for mini-tiles and geoid        |
 *              |         |          |                   |    computation.                    |
 *              |         |          |                   |  + EarthCase filenames compliant   |
 *              |         |          |                   |    with FFS 2.0.                   |
 *              +-----------------------------------------------------------------------------+
 *              |    4.6  | 03/10/13 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for new Attitude        |
 *              |         |          |                   |    Definition File                 |
 *              +-----------------------------------------------------------------------------+
 *              |    4.7  | 28/03/14 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for Doris files for     |
 *              |         |          |                   |    Sentinel 3.                     |
 *              |         |          |                   |  + Support for files with SP3      |
 *              |         |          |                   |    format (GPS orbit format)       |
 *              +-----------------------------------------------------------------------------+
 *              |    4.8  | 29/10/14 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for DEM GETASSE v3.0    |
 *              |         |          |                   |  + Support for GDEM v2             |
 *              |         |          |                   |  + New function to add style sheet |
 *              |         |          |                   |    to files: xd_xslt_add           |
 *              +-----------------------------------------------------------------------------+
 *              |    4.9  | 23/04/15 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for Orbit Ephemeris     |
 *              |         |          |                   |    Message files                   |
 *              +-----------------------------------------------------------------------------+
 *              |  4.9.1  | 05/06/15 | DEIMOS Space S.L.U| Maintenance release                |
 *              +-----------------------------------------------------------------------------+
 *              |   4.10  | 29/10/15 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for DEM ACE2 30 secs    |
 *              |         |          |                   |  + New diagnostic function for     |
 *              |         |          |                   |    orbit files with state vectors: |
 *              |         |          |                   |    xd_orbit_file_diagnostics       |
 *              |         |          |                   |  + Change of interface in functions|
 *              |         |          |                   |    xd_read_oem and xd_read_sp3     |
 *              +-----------------------------------------------------------------------------+
 *              |   4.11  | 15/04/16 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for DEM ACE2 3 secs     |
 *              +-----------------------------------------------------------------------------+
 *              |   4.12  | 03/11/16 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Support for FFS 3               |
 *              +-----------------------------------------------------------------------------+
 *              |   4.13  | 05/04/17 | DEIMOS Space S.L.U| Maintenance release                |
 *              +-----------------------------------------------------------------------------+
 *              |   4.14  | 16/11/17 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Added support for Jason-CS Doris|
 *              +-----------------------------------------------------------------------------+
 *              |   4.15  | 20/04/18 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + Refactored code                 |
 *              +-----------------------------------------------------------------------------+
 *              |   4.16  | 09/11/18 | DEIMOS Space S.L.U| Maintenance release                |
 *              +-----------------------------------------------------------------------------+
 *              |   4.17  | 10/05/19 | DEIMOS Space S.L.U| Maintenance release                |
 *              |         |          |                   | New features:                      |
 *              |         |          |                   |  + DEM configurable raster         |
 *              +-----------------------------------------------------------------------------+
 *
 *****************************************************************************/

#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <explorer_data_handling.h>


/* Main program */
/* ------------ */

int main (int argc, char *argv[])
{
  long   status;   /* (Normal) status flag */
  long   ierr[XD_ERR_VECTOR_MAX_LENGTH];

  long   n;        /* Number of error messages */
  long   func_id;  /* CFI function ID */
  char   msg[XD_MAX_COD][XD_MAX_STR];	/* Error messages vector */

  long   i; /* a counter */

  char input_file[XD_MAX_STR],
       input_file2[XD_MAX_STR],
       output_file[XD_MAX_STR];
  char *file_list[1];

  xd_iers_bulletin_b    iers_data;
  xd_orbit_file         orbit_data, orbit_data_out;
  xd_doris_file         doris_data;
  xd_doris_mph_sph      doris_header;
  xd_osf_file           osf_data;
  xd_tracker_conf_file  star_tracker_conf_data;
  xd_star_tracker_file  str_data;
  xd_att_file           att_data, att_data_out;
  xd_dem_config_file    dem_config_data;
  xd_dem_ace            ace_data;
  xd_dem_file           dem_data;
  xd_sdf_file           sdf_data;
  xd_stf_file           stf_data;
  xd_zone_rec           zone_data;
  xd_station_rec        station_data;
  xd_star_rec           star_data;
  xd_tle_file           tle_data;
  xd_fhr                fhr, fhr_out;
  xd_propag_precise_config precise_conf;
  xd_sp3_file           sp3_data;
  xd_fov_constraints_file fov_constraints;
  
  long   star_tracker_id;
  long   read_fro_flag, reading_osv_flag,
         time_orbit_flag, interpol_flag;
  long   time_ref=0;
  long   time_mode;
  double start_range, stop_range;

  long n_files;
  double time0, time1;

  char zone_id[10];
  char station_id[10];
  char star_id[10];

  long mode, valid_status;
  char schema[256];
  char logfile[256];

  char satellite[XD_MAX_STR] = "";

  double decimation_delta_time;

  xd_attitude_definition_data att_def_data;
  xd_osv_list_read_configuration osv_list_read_configuration;
  
  /* Set error handling mode to SILENT */
  /* ---------------------------------- */
  
  /*xd_silent();*/     /* Set error handling mode to SILENT */
  xd_verbose();

  /* ------------------------------------------------------------------------ */
  /* Reading IERS Bulletin files                                              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_bulletin                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading IERS Bulletin: xd_read_bulletin");
  printf("\n---------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\IERS_BULLETIN");
#else
  strcpy (input_file, "../data/IERS_BULLETIN");
#endif

  /* Call  function: xd_read_bulletin */
  /* -------------------------------- */
  status = xd_read_bulletin (input_file, &iers_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_BULLETIN_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\n-                  \t Day \t UT1-UTC \t UT1-TAI");
  printf("\n-   Table1: ");
  printf("\n-   First Element: \t %f \t %f \t %f ", 
          iers_data.table1[0].day, iers_data.table1[0].ut1_utc, iers_data.table1[0].ut1_tai);
  printf("\n-   Last Element: \t %f \t %f \t %f ", 
          iers_data.table1[99].day, iers_data.table1[99].ut1_utc, iers_data.table1[99].ut1_tai);
  printf("\n-   Table2: ");
  printf("\n-   First Element: \t %f \t %f \t %f", 
          iers_data.table2[0].day, iers_data.table2[0].ut1_utc, iers_data.table2[0].ut1_tai);
  printf("\n-   Last Element: \t %f \t %f \t %f", 
          iers_data.table2[99].day, iers_data.table2[99].ut1_utc, iers_data.table2[99].ut1_tai);


  /* ------------------------------------------------------------------------ */
  /* Reading Orbit Files                                                      */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_orbit_file                                          */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Orbit Files: xd_read_orbit_file");
  printf("\n---------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../data/EARTH_EXPLORER_FPO");
#endif

  read_fro_flag = 0;
  reading_osv_flag = 1;
  time_orbit_flag = XD_SEL_ORBIT;
  start_range = 1000;
  stop_range  = 1002;

  /* Call  function: xd_read_orbit_file */
  /* ---------------------------------- */
  status = xd_read_orbit_file (input_file, &read_fro_flag, 
                               &time_orbit_flag, &time_ref,
                               &start_range, &stop_range, 
                               &reading_osv_flag, 
                               &orbit_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_ORBIT_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   i = orbit_data.num_rec -1;
   printf("\n-   Number of records     : %ld ", orbit_data.num_rec);
   printf("\n-   First State Vector");
   printf("\n-      TAI Time           : %f ", orbit_data.osv_rec[0].tai_time);
   printf("\n-      UT1 Time           : %f ", orbit_data.osv_rec[0].ut1_time);
   printf("\n-      UTC Time           : %f ", orbit_data.osv_rec[0].utc_time);
   printf("\n-      Absolute Orbit     : %ld ", orbit_data.osv_rec[0].abs_orbit);
   printf("\n-      Position           : (%f, %f, %f) ", orbit_data.osv_rec[0].pos [0],
                                                                  orbit_data.osv_rec[0].pos [1],
                                                                  orbit_data.osv_rec[0].pos [2]);
   printf("\n-      Velocity           : (%f, %f, %f) ", orbit_data.osv_rec[0].vel [0],
                                                                  orbit_data.osv_rec[0].vel [1], 
                                                                  orbit_data.osv_rec[0].vel [2]);
   printf("\n-      Quality            : %f ", orbit_data.osv_rec[0].quality);
   printf("\n-   Last State Vector");
   printf("\n-      TAI Time           : %f ", orbit_data.osv_rec[i].tai_time);
   printf("\n-      UT1 Time           : %f ", orbit_data.osv_rec[i].ut1_time);
   printf("\n-      UTC Time           : %f ", orbit_data.osv_rec[i].utc_time);
   printf("\n-      Absolute Orbit     : %ld ", orbit_data.osv_rec[i].abs_orbit);
   printf("\n-      Position           : (%f, %f, %f) ", orbit_data.osv_rec[i].pos [0],
                                                                  orbit_data.osv_rec[i].pos [1], 
                                                                  orbit_data.osv_rec[i].pos [2]);
   printf("\n-      Velocity           : (%f, %f, %f) ", orbit_data.osv_rec[i].vel [0],
                                                                  orbit_data.osv_rec[i].vel [1], 
                                                                  orbit_data.osv_rec[i].vel [2]);
   printf("\n-      Quality            : %f ", orbit_data.osv_rec[i].quality);


  /* ------------------------------------------------------------------------ */
  /* Reading Fixed Header (form the previous orbit_file)                             */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_fhr                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Fixed Header: xd_read_fhr");
  printf("\n-----------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../data/EARTH_EXPLORER_FPO");
#endif


  /* Call  function: xd_read_fhr */
  /* --------------------------- */
  status = xd_read_fhr(input_file, &fhr, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_FHR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Filename:         %s ", fhr.file_name);
   printf("\n-   File Description: %s ", fhr.file_description);
   printf("\n-   Mission:          %s ", fhr.mission);
   printf("\n-   File Class:       %s ", fhr.file_class);
   printf("\n-   File Type:        %s ", fhr.file_type);
   printf("\n-   Version:          %ld ", fhr.version);
   printf("\n-   Validity start date: %s ", fhr.val_start_date);
   printf("\n-   Validity stop date: %s ",  fhr.val_stop_date);
   printf("\n-   System:          %s ", fhr.system);
   printf("\n-   Creator:         %s ", fhr.creator);
   printf("\n-   Creator Version: %s ", fhr.creator_version);
   printf("\n-   Creation Date:   %s ", fhr.creation_date);



  /* ------------------------------------------------------------------------ */
  /* Writing Orbit Files                                                      */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_write_orbit_file                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\nWriting Orbit Files: xd_write_orbit_file");
  printf("\n----------------------------------------");

  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../data/EARTH_EXPLORER_FPO");
#endif

   strcpy (output_file, "output_pof_file.xml");

  /* Call  function: xd_read_orbit_file */
  /* ---------------------------------- */
   status = xd_write_orbit_file(output_file, 
                                &fhr, &orbit_data,
                                ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_WRITE_ORBIT_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  /* ------------------------------------------------------------------------ */
  /* Configure orbit file records                                             */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_orbit_file_decimate                                      */
  /* ------------------------------------------------------------------------ */

  printf("\n\nDecimating Orbit Files: xd_orbit_file_decimate");
  printf("\n---------------------------------------");
  
  /* Set input values */
  /* ---------------- */
  decimation_delta_time = 4*60*60; /* 4 hours in seconds */
  
  /* Call  function: xd_orbit_file_decimate */
  /* -------------------------------------- */
  status = xd_orbit_file_decimate( &fhr, &orbit_data, 
                                   decimation_delta_time,
                                   &fhr_out, &orbit_data_out,
                                   ierr);

  /* Print output values */
  /* ------------------- */
  if (status != XD_OK)
  {
     func_id = XD_ORBIT_FILE_DECIMATE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\n-   Records before decimation:         %ld ", orbit_data.num_rec);
  printf("\n-   Records after decimation:         %ld ",  orbit_data_out.num_rec);
  
  /* Free memory */
  /* ----------- */
  
  xd_free_orbit_file (&orbit_data);
  xd_free_orbit_file (&orbit_data_out);
   

  /* ------------------------------------------------------------------------ */
  /* Reading DORIS Navigator Files                                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_doris_header                                        */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading DORIS Navigator Files: xd_read_doris_header");
  printf("\n-----------------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_DORIS_NAV_2000");
#else
  strcpy (input_file, "../data/CRYOSAT_DORIS_NAV_2000");
#endif


  interpol_flag = 1;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_doris_header */
  /* ------------------------------------ */
  status = xd_read_doris_header(input_file,
                                &doris_header, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_DORIS_HEADER_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Filename          : %s ", doris_header.filename);
   printf("\n-   Sensing start     : %s ", doris_header.sensing_start);
   printf("\n-   Sensing stop      : %s ", doris_header.sensing_stop);
   printf("\n-   Relative orbit    : %ld ", doris_header.rel_orbit);
   printf("\n-   Absolute orbit    : %ld ", doris_header.abs_orbit);
   printf("\n-   Delta UT1         : %f ", doris_header.delta_ut1);
   printf("\n-   Leap UTC          : %s ", doris_header.leap_utc);
   printf("\n-   Leap sign         : %ld ", doris_header.leap_sign);
   printf("\n-   Leap Error        : %ld ", doris_header.leap_err);
   printf("\n-   Number of DSD     : %ld ", doris_header.num_dsd);
   printf("\n-   DS Offset         : %ld ", doris_header.ds_offset);
   printf("\n-   Number of DSR     : %ld ", doris_header.num_dsr);


  /* ------------------------------------------------------------------------ */
  /* Reading DORIS Navigator Files                                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_doris                                               */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading DORIS Navigator Files: xd_read_doris");
  printf("\n----------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_DORIS_NAV_2000");
#else
  strcpy (input_file, "../data/CRYOSAT_DORIS_NAV_2000");
#endif


  interpol_flag = 1;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_doris */
  /* ----------------------------- */
  status = xd_read_doris(input_file, &time_mode,
                         &start_range, &stop_range,
                         &interpol_flag,
                         &doris_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_DORIS_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   i = doris_data.num_rec -1;
   printf("\n-   Number of records     : %ld ", doris_data.num_rec);
   printf("\n-   First State Vector");
   printf("\n-      TAI Time           : %f ", doris_data.osv_rec[0].tai_time);
   printf("\n-      UT1 Time           : %f ", doris_data.osv_rec[0].ut1_time);
   printf("\n-      Position           : (%f, %f, %f) ", doris_data.osv_rec[0].pos [0],
                                                                  doris_data.osv_rec[0].pos [1],
                                                                  doris_data.osv_rec[0].pos [2]);
   printf("\n-      Velocity           : (%f, %f, %f) ", doris_data.osv_rec[0].vel [0],
                                                                  doris_data.osv_rec[0].vel [1], 
                                                                  doris_data.osv_rec[0].vel [2]);
   printf("\n-      Quality            : %f ", doris_data.osv_rec[0].quality);
   printf("\n-   Last State Vector");
   printf("\n-      TAI Time           : %f ", doris_data.osv_rec[i].tai_time);
   printf("\n-      UT1 Time           : %f ", doris_data.osv_rec[i].ut1_time);
   printf("\n-      Position           : (%f, %f, %f) ", doris_data.osv_rec[i].pos [0],
                                                                  doris_data.osv_rec[i].pos [1], 
                                                                  doris_data.osv_rec[i].pos [2]);
   printf("\n-      Velocity           : (%f, %f, %f) ", doris_data.osv_rec[i].vel [0],
                                                                  doris_data.osv_rec[i].vel [1], 
                                                                  doris_data.osv_rec[i].vel [2]);
   printf("\n-      Quality            : %f ", doris_data.osv_rec[i].quality);


  /* ------------------------------------------------------------------------ */
  /* Writing Orbit Files                                                      */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_write_doris_file                                         */
  /* ------------------------------------------------------------------------ */

  printf("\n\nWriting DORIS File: xd_write_doris");
  printf("\n------------------------------------");
  
  /* Set input values */
  /* ---------------- */
   strcpy (output_file, "output_doris_file.eef");

  /* Call  function: xd_read_orbit_file */
  /* ---------------------------------- */
   status = xd_write_doris(output_file, 
                           &doris_header, &doris_data,
                           ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_WRITE_ORBIT_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   /* Free memory */
   /* ----------- */

   xd_free_doris(&doris_data);


  /* ------------------------------------------------------------------------ */
  /* Reading Orbit Scenario Files                                             */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_osf                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Orbit Scenario Files: xd_read_osf");
  printf("\n--------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_XML_OSF");
#else
  strcpy (input_file, "../data/CRYOSAT_XML_OSF");
#endif


  /* Call  function: xd_read_osf */
  /* --------------------------- */
  status = xd_read_osf(input_file,
                       &osf_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_OSF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   i = osf_data.num_rec -1;
   printf("\n-   Number of records     : %ld ", osf_data.num_rec);
   printf("\n-   First Orbital Change");
   printf("\n-      Absolute Orbit     : %ld ", osf_data.osf_rec[0].abs_orb);
   printf("\n-      Relative Orbit     : %ld ", osf_data.osf_rec[0].rel_orb);
   printf("\n-      ANX Cycle          : %ld ", osf_data.osf_rec[0].cycle);
   printf("\n-      ANX Phase          : %ld ", osf_data.osf_rec[0].phase);
   printf("\n-      Cycle Days         : %ld d", osf_data.osf_rec[0].cycle_days);
   printf("\n-      Cycle Orbit        : %ld ", osf_data.osf_rec[0].cycle_orbits);

   printf("\n-      MLST               : %f h", osf_data.osf_rec[0].mlst);
   printf("\n-      MLST Drift         : %f ", osf_data.osf_rec[0].mlst_drift);
   printf("\n-      Drift mode         : %ld ", osf_data.osf_rec[0].drift_mode);
   printf("\n-      ANX Longitude      : %f deg", osf_data.osf_rec[0].anx_long);

   printf("\n-      ANX TAI            : %f ", osf_data.osf_rec[0].anx_tai);
   printf("\n-      ANX UTC            : %f ", osf_data.osf_rec[0].anx_utc);
   printf("\n-      ANX UT1            : %f ", osf_data.osf_rec[0].anx_ut1);

   printf("\n-   Last State Vector");
   printf("\n-      Absolute Orbit     : %ld ", osf_data.osf_rec[i].abs_orb);
   printf("\n-      Relative Orbit     : %ld ", osf_data.osf_rec[i].rel_orb);
   printf("\n-      ANX Cycle          : %ld ", osf_data.osf_rec[i].cycle);
   printf("\n-      ANX Phase          : %ld ", osf_data.osf_rec[i].phase);
   printf("\n-      Cycle Days         : %ld d", osf_data.osf_rec[i].cycle_days);
   printf("\n-      Cycle Orbit        : %ld ", osf_data.osf_rec[i].cycle_orbits);

   printf("\n-      MLST               : %f h", osf_data.osf_rec[i].mlst);
   printf("\n-      MLST Drift         : %f ", osf_data.osf_rec[i].mlst_drift);
   printf("\n-      Drift mode         : %ld ", osf_data.osf_rec[i].drift_mode);
   printf("\n-      ANX Longitude      : %f deg", osf_data.osf_rec[i].anx_long);

   printf("\n-      ANX TAI            : %f ", osf_data.osf_rec[i].anx_tai);
   printf("\n-      ANX UTC            : %f ", osf_data.osf_rec[i].anx_utc);
   printf("\n-      ANX UT1            : %f ", osf_data.osf_rec[i].anx_ut1);



  /* ------------------------------------------------------------------------ */
  /* Reading Fixed Header (form the previous OSF)                             */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_fhr                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Fixed Header: xd_read_fhr");
  printf("\n-----------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_XML_OSF");
#else
  strcpy (input_file, "../data/CRYOSAT_XML_OSF");
#endif


  /* Call  function: xd_read_fhr */
  /* --------------------------- */
  status = xd_read_fhr(input_file, &fhr, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_FHR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Filename:         %s ", fhr.file_name);
   printf("\n-   File Description: %s ", fhr.file_description);
   printf("\n-   Mission:          %s ", fhr.mission);
   printf("\n-   File Class:       %s ", fhr.file_class);
   printf("\n-   File Type:        %s ", fhr.file_type);
   printf("\n-   Version:          %ld ", fhr.version);
   printf("\n-   Validity start date: %s ", fhr.val_start_date);
   printf("\n-   Validity stop date: %s ",  fhr.val_stop_date);
   printf("\n-   System:          %s ", fhr.system);
   printf("\n-   Creator:         %s ", fhr.creator);
   printf("\n-   Creator Version: %s ", fhr.creator_version);
   printf("\n-   Creation Date:   %s ", fhr.creation_date);


   /* ------------------------------------------------------------------------ */
   /* Writing Orbit Scenario Files                                             */
   /* ------------------------------------------------------------------------ */
   /* Function(s): xd_write_osf                                                */
   /* ------------------------------------------------------------------------ */

   printf("\n\nReading Orbit Scenario Files: xd_write_osf");
   printf("\n--------------------------------------------");
  
   /* Set input values */
   /* ---------------- */
   strcpy (output_file, "output_osf_file.xml");

  /* Call  function: xd_write_osf */
  /* ---------------------------- */
  status = xd_write_osf(output_file, &fhr, &osf_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_WRITE_OSF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }


   /* Free memory */
   /* ----------- */

   xd_free_osf(&osf_data);


  /* ------------------------------------------------------------------------ */
  /* Reading Star Tracker Configuration files                                 */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_star_tracker_conf_file                              */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Star Tracker Configuration files: xd_read_star_tracker_conf_file");
  printf("\n------------------------------------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_STAR_TRACKER_CONF_FILE.XML");
#else
  strcpy (input_file, "../data/CRYOSAT_STAR_TRACKER_CONF_FILE.XML");
#endif

  star_tracker_id = 1;

  /* Call  function: xd_read_star_tracker_conf_file */
  /* ---------------------------------------------- */

  status = xd_read_star_tracker_conf_file (input_file, &star_tracker_id,
                                           &star_tracker_conf_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_STR_CONF_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Satellite        : %s ", star_tracker_conf_data.satellite);
   printf("\n-   Maximum penalty  : %f ", star_tracker_conf_data.str_limit.max_penalty);
   printf("\n-   Norm threshold   : %f ", star_tracker_conf_data.str_limit.norm_thr);
   printf("\n-   Maximum gap      : %f seconds", star_tracker_conf_data.str_limit.max_gap);
   printf("\n-   Satellite Attitude to Star Tracker frame rotation matrix:");
   for (i = 0; i < 3; i++)
   {
     printf("\n  \t %f \t %f \t %f", 
             star_tracker_conf_data.str_att_rot[i][0], 
             star_tracker_conf_data.str_att_rot[i][1],
             star_tracker_conf_data.str_att_rot[i][2]);
   }

  /* ------------------------------------------------------------------------ */
  /* Reading Star Tracker files                                               */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_star_tracker                                        */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Star Tracker files: xd_read_star_tracker");
  printf("\n------------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_STAR_TRACKER_DATA.DBL");
#else
  strcpy (input_file, "../data/CRYOSAT_STAR_TRACKER_DATA.DBL");
#endif

  n_files = 1;
  file_list[0] = input_file;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_star_tracker */
  /* ------------------------------------ */
  status = xd_read_star_tracker(&n_files, file_list,
                                &time_mode, &time0, &time1,
                                &(star_tracker_conf_data.str_limit),
                                &str_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_STAR_TRACKER_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Number of records     : %ld ", str_data.num_rec);
   printf("\n-   Fist Quaternion: Time = %f, Q= %f, %f, %f, %f", 
           str_data.str_rec[0].time,
           str_data.str_rec[0].quaternion[0], str_data.str_rec[0].quaternion[1],
           str_data.str_rec[0].quaternion[2], str_data.str_rec[0].quaternion[3]);
   printf("\n-   Last Quaternion: Time = %f, Q= %f, %f, %f, %f", 
           str_data.str_rec[str_data.num_rec-1].time,
           str_data.str_rec[str_data.num_rec-1].quaternion[0], str_data.str_rec[str_data.num_rec-1].quaternion[1],
           str_data.str_rec[str_data.num_rec-1].quaternion[2], str_data.str_rec[str_data.num_rec-1].quaternion[3]);



   /* Free memory */
   /* ----------- */

   xd_free_star_tracker(&str_data);


  /* ------------------------------------------------------------------------ */
  /* Reading Generic Attitude files                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_att                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Attitude files: xd_read_att");
  printf("\n-----------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_ATT_FILE.XML");
#else
  strcpy (input_file, "../data/CRYOSAT_ATT_FILE.XML");
#endif

  /* Call  function: xd_read_att */
  /* --------------------------- */
  status = xd_read_att(input_file, &att_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_ATT_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Target reference frame     : %ld ", att_data.sat_ref);
   printf("\n-   Source reference frame     : %ld ", att_data.source_ref);
   printf("\n-   Maximum gap allowed between attitude records: %f ", att_data.max_gap);
   printf("\n-   Number of records     : %ld ", att_data.num_rec);

   if (att_data.data_type == XD_ATT_QUATERNIONS)
   {
     printf("\n-   Data Type     : %s ", "Quaternions");
     printf("\n-   First record: Time = %f, Q = %f, %f, %f, %f", 
           att_data.att_rec[0].time, 
             att_data.att_rec[0].data[0], att_data.att_rec[0].data[1], 
             att_data.att_rec[0].data[2], att_data.att_rec[0].data[3]);
   
     printf("\n-   Last record: Time = %f, Q = %f, %f, %f, %f", 
             att_data.att_rec[att_data.num_rec-1].time, 
             att_data.att_rec[att_data.num_rec-1].data[0], att_data.att_rec[att_data.num_rec-1].data[1], 
             att_data.att_rec[att_data.num_rec-1].data[2], att_data.att_rec[att_data.num_rec-1].data[3]);
   }
   else
   {
     printf("\n-   Data Type     : %s ", "Angles");
     printf("\n-   First record: Time = %f, Angles = %f, %f, %f", 
           att_data.att_rec[0].time, 
             att_data.att_rec[0].data[0], att_data.att_rec[0].data[1], 
             att_data.att_rec[0].data[2]);
   
     printf("\n-   Last record: Time = %f, Angles = %f, %f, %f", 
             att_data.att_rec[att_data.num_rec-1].time, 
             att_data.att_rec[att_data.num_rec-1].data[0], att_data.att_rec[att_data.num_rec-1].data[1], 
             att_data.att_rec[att_data.num_rec-1].data[2]);
   }



   /* Call  function: xd_read_fhr */
   /* --------------------------- */
   status = xd_read_fhr(input_file, &fhr, ierr);

   /* Print output values */
   /* ------------------- */
   
   if (status != XD_OK)
   {
     func_id = XD_READ_FHR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
   }
   else
   {
     printf("\n");
   }


   /* ------------------------------------------------------------------------ */
   /* Writing Attitude files                                                   */
   /* ------------------------------------------------------------------------ */
   /* Function(s): xd_write_att                                                */
   /* ------------------------------------------------------------------------ */

   printf("\n\nWriting Attitude Files: xd_write_att");
   printf("\n-------------------------------------");
   
   /* Set input values */
   /* ---------------- */
   strcpy (output_file, "output_att_file.eef");

   
   /* Call  function: xd_wite_att */
   /* --------------------------- */
   status = xd_write_att(output_file, &fhr, 
                         &att_data, ierr);
   
   /* Print output values */
   /* ------------------- */

   if (status != XD_OK)
   {
     func_id = XD_WRITE_ATT_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
   } 
   else
   {
     printf("\n");
   }

  /* ------------------------------------------------------------------------ */
  /* Decimating Attitude files                                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_attitude_file_decimate                                   */
  /* ------------------------------------------------------------------------ */

  printf("\n\nDecimating Attitude files: xd_attitude_file_decimate");
  printf("\n------------------------------------------------------");
  
  /* Set input values */
  /* ---------------- */
  decimation_delta_time = 2.; /* 2 seconds */
  
  /* Call  function: xd_attitude_file_decimate */
  /* ----------------------------------------- */
  status = xd_attitude_file_decimate(&fhr, &att_data,
                                     decimation_delta_time,
                                     &fhr_out, &att_data_out,
                                     ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_ATTITUDE_FILE_DECIMATE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Initial attitude records          : %ld ", att_data.num_rec);
   printf("\n-   Attitude records after decimation : %ld ", att_data_out.num_rec);
   
   /* Free memory */
   /* ----------- */
   xd_free_att(&att_data);
   xd_free_att(&att_data_out);


  /* ------------------------------------------------------------------------ */
  /* Reading DEM  Files                                                       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_dem_config_file & xd_read_dem                       */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading DEM Files: xd_read_dem_config_file & xd_read_dem");
  printf("\n----------------------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file2, "..\\data\\DEM_CONFIG_FILE.XML");
#else
  strcpy (input_file2, "../data/DEM_CONFIG_FILE.XML");
#endif
  strcpy (input_file, "45N000E.GETASSE30");


  /* Call  function: xd_read_dem_config_file */
  /* --------------------------------------- */
  status = xd_read_dem_config_file(input_file2, &dem_config_data, ierr);

  /* Print output values */
  /* ------------------- */
  if (status != XD_OK)
  {
     func_id = XD_READ_DEM_CONFIG_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 


  /* Call  function: xd_read_dem */
  /* --------------------------- */
  status = xd_read_dem (input_file, &dem_config_data, &dem_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_DEM_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }


  printf("\nNumber of points along X = %ld", dem_data.num_points_X);
  printf("\nNumber of points along Y = %ld", dem_data.num_points_Y);
  printf("\n1st. point: lon = %f, lat = %f, alt = %f", 
          dem_data.point[0][0].lon, dem_data.point[0][0].lat,  dem_data.point[0][0].alt);
  printf("\nLast. point: lon = %f, lat = %f, alt = %f", 
         dem_data.point[dem_data.num_points_X -1][dem_data.num_points_Y -1].lon, 
         dem_data.point[dem_data.num_points_X -1][dem_data.num_points_Y -1].lat, 
         dem_data.point[dem_data.num_points_X -1][dem_data.num_points_Y -1].alt);


  /* Free memory */
  /* ----------- */
  xd_free_dem_config_file(&dem_config_data);
  xd_free_dem(&dem_data);


  /* ------------------------------------------------------------------------ */
  /* Reading Swath Definition Files                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_sdf                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Swath Definition Files: xd_read_sdf");
  printf("\n-----------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\SWATH_DEF_FILE");
#else
  strcpy (input_file, "../data/SWATH_DEF_FILE");
#endif


  /* Call  function: xd_read_sdf */
  /* --------------------------- */
  status = xd_read_sdf(input_file,
                       &sdf_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_SDF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

   printf("\n-   Number of records     : %ld ", sdf_data.num_rec);
   printf("\n-   Swath Description     : %s ",  sdf_data.sdf_rec[0].swath_descr);
   printf("\n-   Swath Id              : %s ",  sdf_data.sdf_rec[0].swath_id);
   printf("\n-   Swath type            : %ld ", sdf_data.sdf_rec[0].swath_type);
   printf("\n-   Number of swath rec   : %ld ", sdf_data.sdf_rec[0].num_swath_rec);
   printf("\n-   Refraction mode       : %ld ", sdf_data.sdf_rec[0].refr_mode);
   printf("\n-   Frequency             : %f ",  sdf_data.sdf_rec[0].freq);

   for (i = 0; i < sdf_data.sdf_rec[0].num_points; i++)
   {
     printf("\n-   Swath geometry (point %ld)", i);
     printf("\n-      Geometry type      : %ld ", sdf_data.sdf_rec[0].swath_geom[i].geom_type);
     printf("\n-      Azimuth            : %f ",  sdf_data.sdf_rec[0].swath_geom[i].az);
     printf("\n-      Elevation          : %f ",  sdf_data.sdf_rec[0].swath_geom[i].el);
     printf("\n-      Altitude           : %f ",  sdf_data.sdf_rec[0].swath_geom[i].alt);
   }

   printf("\n-  Satellite Nominal Attitude model ");
   printf("\n-      Attitude Model      : %ld ", sdf_data.sdf_rec[0].sat_nom_att->attitude_model);
   printf("\n-      Model               : %ld ", sdf_data.sdf_rec[0].sat_nom_att->data.param_mode.model);
   printf("\n-      Number of parameters: %ld ", sdf_data.sdf_rec[0].sat_nom_att->data.param_mode.param_num);
   for (i = 0; i < sdf_data.sdf_rec[0].sat_nom_att->data.param_mode.param_num; i++)
   {
     printf("\n-    Model param[%ld]     : %f ", i, sdf_data.sdf_rec[0].sat_nom_att->data.param_mode.model_param[i]);
   }
   
   printf("\n-  Satellite Attitude model      ");
   printf("\n-      Model       : %ld ", sdf_data.sdf_rec[0].sat_att->attitude_model);
   for (i = 0; i < 3; i++)
   {
     printf("\n-      Angle       : %f ", sdf_data.sdf_rec[0].sat_att->data.angle_mode.angles[i]);
   }
   
   printf("\n-  Instrument Attitude model  ");
   printf("\n-      Model       : %ld ", sdf_data.sdf_rec[0].instr_att->attitude_model);



   /* Free memory */
   /* ----------- */

   xd_free_sdf(&sdf_data);

  /* ------------------------------------------------------------------------ */
  /* Reading Swath Template Files                                             */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_stf                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Swath Template Files: xd_read_stf");
  printf("\n----------------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\SWATH_TEMPLATE_FILE");
#else
  strcpy (input_file, "../data/SWATH_TEMPLATE_FILE");
#endif


  /* Call  function: xd_read_stf */
  /* --------------------------- */
  status = xd_read_stf(input_file,
                       &stf_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_STF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }


   printf("\n-   Swath Type    : %ld ", stf_data.vhr.swath_type);
   printf("\n-   Orbit Geometry ");
   printf("\n-      Repeat Cycle     : %ld day",    stf_data.vhr.rep_cycl);
   printf("\n-      Cycle Length     : %ld orbits", stf_data.vhr.cycle_length);
   printf("\n-      mlst drift       : %f s/day",   stf_data.vhr.mlst_drift);
   printf("\n-   Time Step       : %f s",           stf_data.vhr.time_step);
   printf("\n-   Line Altitude ");
   printf("\n-      Left    : %f s",  stf_data.vhr.altitude[0]);
   printf("\n-      Middle  : %f s",  stf_data.vhr.altitude[1]);
   printf("\n-      Right   : %f s",  stf_data.vhr.altitude[2]);
   printf("\n-   Refraction Model       : %ld s",  stf_data.vhr.refr_mode);
   printf("\n-   Frequency       : %f Hz",  stf_data.vhr.freq);
   printf("\n-   Number of records       : %ld s",  stf_data.num_rec);
   printf("\n-   First Swath Record:       (%f, %f), (%f, %f), (%f, %f)", 
           stf_data.stf_rec[0].stf_pt[0].lon, stf_data.stf_rec[0].stf_pt[0].lat,
           stf_data.stf_rec[0].stf_pt[1].lon, stf_data.stf_rec[0].stf_pt[1].lat,
           stf_data.stf_rec[0].stf_pt[2].lon, stf_data.stf_rec[0].stf_pt[2].lat);
   printf("\n-   Last Swath Record:       (%f, %f), (%f, %f), (%f, %f)", 
           stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[0].lon,  stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[0].lat,
           stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[1].lon,  stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[1].lat,
           stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[2].lon,  stf_data.stf_rec[stf_data.num_rec - 1].stf_pt[2].lat);



   /* Call  function: xd_read_fhr */
   /* --------------------------- */
   status = xd_read_fhr(input_file, &fhr, ierr);

   /* Print output values */
   /* ------------------- */
   
   if (status != XD_OK)
   {
     func_id = XD_READ_FHR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
   }
   else
   {
     printf("\n");
   }

#ifdef jjbb

   /* ------------------------------------------------------------------------ */
   /* Writing Swath Template files                                             */
   /* ------------------------------------------------------------------------ */
   /* Function(s): xd_write_stf                                                */
   /* ------------------------------------------------------------------------ */

   printf("\n\nWriting Swath Template Files: xd_write_stf");
   printf("\n--------------------------------------------");
   
   /* Set input values */
   /* ---------------- */
   strcpy (output_file, "output_stf_file.eef");

   
   /* Call  function: xd_wite_stf */
   /* --------------------------- */
   status = xd_write_stf(output_file, &fhr, 
                         &stf_data, ierr);
   
   /* Print output values */
   /* ------------------- */

   if (status != XD_OK)
   {
     func_id = XD_WRITE_STF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
   } 
   else
   {
     printf("\n");
   }


   /* Free memory */
   /* ----------- */

   xd_free_stf(&stf_data);
#endif

  /* ------------------------------------------------------------------------ */
  /* Reading Zone Files                                                       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_zone                                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Zone File: xd_read_zone");
  printf("\n---------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\ZONE_FILE.XML");
#else
  strcpy (input_file, "../data/ZONE_FILE.XML");
#endif

  strcpy(zone_id, "ZIOS____");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_zone (input_file, zone_id, &zone_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_ZONE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }


  printf("\n-   Read zone: %s",    zone_id);
  printf("\n-   Zone type = %ld",   zone_data.zone_type);
  printf("\n-   Description = %s", zone_data.description);
  printf("\n-   Surface = %s",     zone_data.surface);
  printf("\n-   Projection = %ld",  zone_data.projection);
  printf("\n-   Creator = %s",     zone_data.creator);
  printf("\n-   Zone points (longitude, latitude) = ");

  for (i = 0; i < zone_data.num_points; i++)
    printf("\n    \t(%f, %f)", 
            zone_data.zone_point[i].pt_long,
            zone_data.zone_point[i].pt_lat);



  /* ------------------------------------------------------------------------ */
  /* Reading Station Files                                                    */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_station                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Station File: xd_read_station");
  printf("\n-------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\STATION_FILE.XML");
#else
  strcpy (input_file, "../data/STATION_FILE.XML");
#endif

  strcpy(station_id, "GTAIWAHX");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_station (input_file, station_id, &station_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_STATION_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\n-   Read station: %s", station_id);
  printf("\n-   Station type = %s", station_data.type);
  printf("\n-   Description = %s", station_data.descriptor);
  printf("\n-   Antenna = %s", station_data.antenna);
  printf("\n-   Purpose = %s", station_data.purpose);
  printf("\n-   Type = %s", station_data.type);
  printf("\n-   Num points = %ld", station_data.num_mask_pt);
  printf("\n-   Station points (azimuth, elevation) = ");

  for (i = 0; i < station_data.num_mask_pt; i++)
    printf("\n-   \t(%f, %f)", station_data.azimuth[i], station_data.elevation[i]);

  printf("\n-   Station longitude = %f", station_data.station_long);
  printf("\n-   Station latitude = %f", station_data.station_lat);
  printf("\n-   Station altitude = %f", station_data.station_alt);

  printf("\n-   Satellite list = %ld", station_data.mission_list);
  for (i = 0; i < station_data.mission_list; i++)
  {
    printf("\n-   \tSpacecraft name = %s", station_data.mission_name[i]);
    printf("\n-   \tAOS Elevation = %f", station_data.mis_aos_el[i]);
    printf("\n-   \tLOS Elevation = %f", station_data.mis_los_el[i]);
    printf("\n-   \tMask type = %s", station_data.mask_type[i]);
  }



  /* ------------------------------------------------------------------------ */
  /* Reading Star Files                                                       */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_star                                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Star File: xd_read_star");
  printf("\n---------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\STAR_FILE.XML");
#else
  strcpy (input_file, "../data/STAR_FILE.XML");
#endif

  strcpy(star_id, "Alp Phe");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_star (input_file, star_id, &star_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_STAR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\n-   Read star: %s\n", star_id);
  printf("\n-   -------------------\n");
  printf("\n-   RA  = %f\n", star_data.star_ra);
  printf("\n-   Dec = %f\n", star_data.star_dec);
  printf("\n-   Parallax = %f\n", star_data.par);
  printf("\n-   RA proper motion (rad/century) = %f\n", star_data.mu_ra);
  printf("\n-   DEC proper motion (rad/century) = %f\n", star_data.mu_dec);
  printf("\n-   Radial Velocity = %f\n", star_data.rad_vel);


  /* ------------------------------------------------------------------------ */
  /* Validating XML Files                                                     */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_xml_validate                                             */
  /* ------------------------------------------------------------------------ */

  printf("\n\nValidating XML File: xd_xml_validate");
  printf("\n--------------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\CRYOSAT_XML_OSF");
  strcpy(schema, "..\\data\\schemas\\EO_OPER_MPL_ORBSCT_0100.XSD");

#else
  strcpy (input_file, "../data/CRYOSAT_XML_OSF");
  strcpy(schema, "../data/schemas/EO_OPER_MPL_ORBSCT_0100.XSD");
#endif

  mode = XD_USER_SCHEMA;

  /* Call  function: xd_xml_validate */
  /* ------------------------------- */

  strcpy(logfile, "./osf_validation_result.txt");
  status = xd_xml_validate (input_file, &mode, schema, logfile, &valid_status, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_XML_VALIDATE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\nValidation status for %s: [%s]\n", 
          input_file, (valid_status == XD_OK)? "VALID" : "INVALID");


  /* ------------------------------------------------------------------------ */
  /* Read TLE File                                                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_tle                                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading TLE File: xd_read_tle");
  printf("\n-------------------------------");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\NOAA_TLE_FILE");
#else
  strcpy (input_file, "../data/NOAA_TLE_FILE");
#endif

  /* Call  function: xd_read_tle */
  /* --------------------------- */
  status = xd_read_tle (input_file, satellite, &tle_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_TLE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\n");
  }

  printf("\n-   TLE elements for 1st satellite in file: %s.", input_file);
  printf("\n-   --------------------------------------");
  printf("\n-   Satellite name: %s", tle_data.tle_rec[0].norad_satcat);
  printf("\n-   NORAD Catalogue number: %ld", tle_data.tle_rec[0].sat_number);
  printf("\n-   Classification: %c", tle_data.tle_rec[0].classification);
  printf("\n-   International Designator: %s", tle_data.tle_rec[0].int_des);
  printf("\n-   TLE time: %lf", tle_data.tle_rec[0].time);
  printf("\n-   First Time Derivative of the Mean Motion: %lf", tle_data.tle_rec[0].n_1st);
  printf("\n-   Second Time Derivative of Mean Motion: %lf", tle_data.tle_rec[0].n_2nd);
  printf("\n-   BSTAR drag term: %lf", tle_data.tle_rec[0].bstar);
  printf("\n-   Ephemeris type: %d", tle_data.tle_rec[0].ephemeris_type);
  printf("\n-   Element number: %d", tle_data.tle_rec[0].index);
  printf("\n-   Checksum 1: %d", tle_data.tle_rec[0].checksum1);
  printf("\n-   Inclination: %lf", tle_data.tle_rec[0].i);
  printf("\n-   ANX Right Ascension: %lf", tle_data.tle_rec[0].ra);
  printf("\n-   Eccentricity: %lf", tle_data.tle_rec[0].e);
  printf("\n-   Argument of Perigee: %lf", tle_data.tle_rec[0].w);
  printf("\n-   Mean Anomaly: %lf", tle_data.tle_rec[0].m);
  printf("\n-   Mean Motion: %lf", tle_data.tle_rec[0].n);
  printf("\n-   Revolution number at epoch: %ld", tle_data.tle_rec[0].abs_orbit);
  printf("\n-   Checksum 2: %d", tle_data.tle_rec[0].checksum2);



  /* ------------------------------------------------------------------------ */
  /* Write TLE File                                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_write_tle                                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\nWriting TLE File: xd_write_tle");
  printf("\n--------------------------------");
  
  /* Set input values */
  /* ---------------- */

  strcpy (output_file, "output_tle_file");

  /* Call  function: xd_write_tle */
  /* ---------------------------- */

  status = xd_write_tle (output_file, &tle_data, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_WRITE_TLE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  else
  {
    printf("\nTLE file created: output_tle_file");
  }

  xd_free_tle(&tle_data);

  /* ------------------------------------------------------------------------ */
  /* Read precise propagation configuration file                              */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_precise_propag_file                                 */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading precise configuration file: xd_read_precise_propag_file");
  printf("\n--------------------------------\n");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\PRECISE_PROPAG_CONF.xml");
#else
  strcpy (input_file, "../data/PRECISE_PROPAG_CONF.xml");
#endif

  /* Call  function: xd_write_tle */
  /* ---------------------------- */

  status = xd_read_precise_propag_file(input_file, &precise_conf, ierr);

  if (status != XD_OK)
  {
     func_id = XD_READ_PRECISE_PROPAG_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  printf("- Models path: %s\n", precise_conf.models_path );
  printf("- Gravity file: %s\n", precise_conf.grav_file );
  printf("- SGA AP file: %s\n", precise_conf.sga_ap_file );
  printf("- SGA F107 file: %s\n", precise_conf.sga_f107_file );
  printf("- Satellite mass: %lf\n", precise_conf.sc_mass );
  printf("- Satellite grad area: %lf\n", precise_conf.sc_drag_area );
  printf("- Satellite srp area: %lf\n", precise_conf.sc_srp_area );
 
  /* ------------------------------------------------------------------------ */
  /* Read attitude definition file                                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_att_file                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading attitude definition file: xd_read_att_file");
  printf("\n--------------------------------\n");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\att_def_file_angles.xml");
#else
  strcpy (input_file, "../data/att_def_file_angles.xml");
#endif

  /* Call  function: xd_read_fhr */
  /* --------------------------- */
  status = xd_read_fhr(input_file, &fhr, ierr);

  /* Print output values */
  /* ------------------- */

  if (status != XD_OK)
  {
     func_id = XD_READ_FHR_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  /* Call  function: xd_read_att_def */
  /* ------------------------------- */

  status = xd_read_att_def(input_file, &att_def_data, ierr);
  if (status != XD_OK)
  {
     func_id = XD_READ_ATT_DEF_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  printf("- Sat Attitude Angles = (%lf, %lf, %lf)\n", 
         att_def_data.sat_att->data.angle_mode.angles[0],
         att_def_data.sat_att->data.angle_mode.angles[1],
         att_def_data.sat_att->data.angle_mode.angles[2]);
  
  /* ------------------------------------------------------------------------ */
  /* Write attitude definition file                                           */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_write_att_file                                           */
  /* ------------------------------------------------------------------------ */

  printf("\n\nWriting attitude definition file: xd_write_att_file");
  printf("\n--------------------------------\n");
  
  /* Call  function: xd_write_att_def */
  /* -------------------------------- */
  strcpy(input_file, "output_att_def_file.xml");
  status = xd_write_att_def(input_file, &fhr, &att_def_data, ierr);
  if (status != XD_OK)
  {
     func_id = XD_WRITE_PRECISE_PROPAG_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  xd_free_att_def(&att_def_data);
  
  /* ------------------------------------------------------------------------ */
  /* Read SP3 file                                                            */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_sp3                                            */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading SP3 file: xd_read_sp3");
  printf("\n--------------------------------\n");
  
  /* Set input values */
  /* ---------------- */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\emr17590.sp3");
#else
  strcpy (input_file, "../data/emr17590.sp3");
#endif

  /* Call  function: xd_read_sp3 */
  /* ------------------------------- */
  osv_list_read_configuration.time_mode = XD_SEL_FILE;
  status = xd_read_sp3(input_file, &osv_list_read_configuration,
                       &sp3_data, ierr);
  if (status != XD_OK)
  {
     func_id = XD_READ_SP3_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  printf("- Number of satellites = %ld\n", sp3_data.num_sat);
  printf("- Number of epochs = %ld\n", sp3_data.osv_rec_sp3[0].num_rec);
  
  xd_free_sp3(&sp3_data);

  /* ------------------------------------------------------------------------ */
  /* Read FOV Constraints file                                                */
  /* ------------------------------------------------------------------------ */
  /* Function(s): xd_read_fov_constraints_file                                */
  /* ------------------------------------------------------------------------ */

  printf("\n\nReading Constraints file: xd_read_fov_constraints_file");
  printf("\n------------------------------------------------------\n");
  
  /* Set input values */

#ifdef WINDOWS
  strcpy (input_file, "..\\data\\FOV_test_file.xml");
#else
  strcpy (input_file, "../data/FOV_test_file.xml");
#endif

  /* Call  function: xd_read_fov_constraints_file */
  status = xd_read_fov_constraints_file(input_file, &fov_constraints, ierr); 
  if (status != XD_OK)
  {
     func_id = XD_READ_FOV_CONSTRAINTS_FILE_ID;
     xd_get_msg(&func_id, ierr, &n, msg);
     xd_print_msg(&n, msg);
     if (status <= XD_ERR) return(XD_ERR);
  } 
  
  printf("- FOV constraints type = %ld\n", fov_constraints.type);
  if (fov_constraints.type == XD_FOV_CONSTRAINTS_SC_LINK)
  {
    printf("- Number of Inclusive mask points = %ld\n",
           fov_constraints.constraints.sc_link_data.mask_data.incl_mask.num_mask_pt);
    printf("- Number of Exclusive mask points = %ld\n",
           fov_constraints.constraints.sc_link_data.mask_data.excl_mask.num_mask_pt);
    printf("- Minimum tangent height = %lf\n",
           fov_constraints.constraints.sc_link_data.min_tg_height);
  }
  
  
  printf("\nEOCFI_DATA_HANDLING EXAMPLE COMPLETED SUCCESSFULLY\n"); 
 
  return(XD_OK);
}

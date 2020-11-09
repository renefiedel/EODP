 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Test level  : VALIDATION
 *
 * Module      : explorer_data_handling_valid.c
 * Purpose     : It runs validation tests of EXPLORER_DATA_HANDLING
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


/* Macro definition */
/* ---------------- */

#define MAX_CONDITION                   1000    /* Maximum number of checks per test case */

#define START_VALIDATION                int main(int argc, char *argv[]){ \
                                        double di,th,ta,tb,sinta,costa,sintb,costb;\
                                        double di_l,di_r,th_l,th_r; \
                                        int i,j; \
                                        int checks; \
                                        XD_Boolean condition[MAX_CONDITION]; \
                                        XD_Boolean result;

#define START_CHECK(msg)                printf(" *** %s\n",msg); \
                                        checks = 0;

#define END_CHECK                       result = XD_TRUE; \
                                        for (i = 0 ; i < checks ; i++) \
                                          { \
                                          if (condition[i] == XD_FALSE) \
                                            { \
                                            result = XD_FALSE; \
                                            break; \
                                            } \
                                          } \
                                        if (result == XD_TRUE) \
                                          { \
                                          printf(" *** RESULT = PASS ***\n\n");\
                                          } \
                                        else \
                                          { \
                                          printf(" *** RESULT = FAIL ***\n\n");\
                                          }
#define CHECK_STATUS(msg,stat)          if (stat < XD_OK ) { \
                                          condition[checks] = XD_FALSE; \
                                          printf(" ...\t%s (XD_FALSE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XD_TRUE; \
                                          printf(" ...\t%s (XD_TRUE)\n",msg); \
                                        } \
                                        checks++;


#define CHECK_PAR(msg,p,p0,dp)          if((di=fabs(p-p0)) <= (th=dp)){ \
                                          condition[checks] = XD_TRUE; \
                                          printf(" ...\t%s (XD_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XD_FALSE; \
                                          printf(" ...\t%s (XD_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Threshold  : %g\n",th); \
                                        printf("\t\t Difference : %g\n",di); \
                                        checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)    for(i=im;i<=iM;++i){ \
                                          CHECK_PAR(msg,v[i],v0[i],dp); \
                                        }

#define CHECK_STR(msg,str1,str2,maxlength)  if(strncmp(str1,str2,maxlength)==0){ \
					                      condition[checks] = XD_TRUE; \
					                      printf(" ...\t%s (XD_TRUE)\n",msg); \
					                    }else{ \
					                      condition[checks] = XD_FALSE; \
					                      printf(" ...\t%s (XD_FALSE)\n",msg); \
					                    } \
					                    printf("\t\t String 1 : %s\n",str1); \
					                    printf("\t\t String 2 : %s\n",str2); \
					                    checks++;

#define END_VALIDATION                  return(0); \
                                        }


/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Validation for EXPLORER_LIB                                               */
/*                                                                           */
/* ------------------------------------------------------------------------- */

START_VALIDATION
{
  long   status;   /* (Normal) status flag */
  long   ierr[XD_ERR_VECTOR_MAX_LENGTH];

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

  char satellite[] = "";

  double decimation_delta_time;

  xd_attitude_definition_data att_def_data;
  xd_osv_list_read_configuration osv_list_read_configuration;
  
  /* Set error handling mode to SILENT */
  /* ---------------------------------- */
    xd_silent();     /* Set error handling mode to SILENT */

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-0
 *
 ****************************************************************************************/

START_CHECK("Check the libraries version")

   status = expcfi_check_libs();
   if (status != XD_OK)
   {
     printf("Library incompatibility.\n");
     CHECK_STATUS("Compatibility test (expcfi_check_libs)", status);
   }

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-1
* ---------
*
********************************************************************/

START_CHECK("Reading IERS Bulletin: xd_read_bulletin validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\IERS_BULLETIN");
#else
  strcpy (input_file, "../example/data/IERS_BULLETIN");
#endif

  /* Call  function: xd_read_bulletin */
  status = xd_read_bulletin (input_file, &iers_data, ierr);

  CHECK_STATUS("xd_read_bulletin", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-2
* ---------
*
********************************************************************/

START_CHECK("Reading Orbit Files: xd_read_orbit_file validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../example/data/EARTH_EXPLORER_FPO");
#endif

  read_fro_flag = 0;
  reading_osv_flag = 1;
  time_orbit_flag = XD_SEL_ORBIT;
  start_range = 1000;
  stop_range  = 1002;

  /* Call  function: xd_read_orbit_file */
  status = xd_read_orbit_file (input_file, &read_fro_flag, 
                               &time_orbit_flag, &time_ref,
                               &start_range, &stop_range, 
                               &reading_osv_flag, 
                               &orbit_data, ierr);

  CHECK_STATUS("xd_read_orbit_file",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-3
* ---------
*
********************************************************************/

START_CHECK("Reading Fixed Header: xd_read_fhr validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../example/data/EARTH_EXPLORER_FPO");
#endif


  /* Call  function: xd_read_fhr */
  status = xd_read_fhr(input_file, &fhr, ierr);

  CHECK_STATUS("xd_read_fhr",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-4
* ---------
*
********************************************************************/

START_CHECK("Writing Orbit Files: xd_write_orbit_file validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\EARTH_EXPLORER_FPO");
#else
  strcpy (input_file, "../example/data/EARTH_EXPLORER_FPO");
#endif

   strcpy (output_file, "output_pof_file.xml");

  /* Call  function: xd_write_orbit_file */
   status = xd_write_orbit_file(output_file, 
                                &fhr, &orbit_data,
                                ierr);

  CHECK_STATUS("xd_write_orbit_file",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-5
* ---------
*
********************************************************************/

START_CHECK("Reading DORIS Navigator Files: xd_read_doris_header validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_DORIS_NAV_2000");
#else
  strcpy (input_file, "../example/data/CRYOSAT_DORIS_NAV_2000");
#endif


  interpol_flag = 1;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_doris_header */
  status = xd_read_doris_header(input_file,
                                &doris_header, ierr);

  CHECK_STATUS("xd_read_doris_header",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-6
* ---------
*
********************************************************************/

START_CHECK("Reading DORIS Navigator Files: xd_read_doris validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_DORIS_NAV_2000");
#else
  strcpy (input_file, "../example/data/CRYOSAT_DORIS_NAV_2000");
#endif


  interpol_flag = 1;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_doris */
  status = xd_read_doris(input_file, &time_mode,
                         &start_range, &stop_range,
                         &interpol_flag,
                         &doris_data, ierr);
  CHECK_STATUS("xd_read_doris",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-7
* ---------
*
********************************************************************/

START_CHECK("Writing Orbit File: xd_write_doris_file validation")

  strcpy (output_file, "output_doris_file.eef");

  /* Call  function: xd_write_orbit_file */
  status = xd_write_doris(output_file, 
                          &doris_header, &doris_data,
                          ierr);
  CHECK_STATUS("xd_write_doris",status);

  /* Free memory */
  /* ----------- */

  xd_free_doris(&doris_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-8
* ---------
*
********************************************************************/

START_CHECK("Reading Orbit Scenario Files: xd_read_osf validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_XML_OSF");
#else
  strcpy (input_file, "../example/data/CRYOSAT_XML_OSF");
#endif

  /* Call  function: xd_read_osf */
  status = xd_read_osf(input_file,
                       &osf_data, ierr);
  CHECK_STATUS("xd_read_osf",status)

  /* Call  function: xd_read_fhr */
  status = xd_read_fhr(input_file, &fhr, ierr);
  CHECK_STATUS("xd_read_fhr",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-9
* ---------
*
********************************************************************/

START_CHECK("Writing Orbit Scenario Files: xd_write_osf validation")

   strcpy (output_file, "output_osf_file.xml");

  /* Call  function: xd_write_osf */
  status = xd_write_osf(output_file, &fhr, &osf_data, ierr);
  CHECK_STATUS("xd_write_osf",status);

  /* Free memory */
  /* ----------- */

  xd_free_osf(&osf_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-10
* ---------
*
********************************************************************/

START_CHECK("Reading Star Tracker Configuration files: xd_read_star_tracker_conf_file validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_STAR_TRACKER_CONF_FILE.XML");
#else
  strcpy (input_file, "../example/data/CRYOSAT_STAR_TRACKER_CONF_FILE.XML");
#endif

  star_tracker_id = 1;

  /* Call  function: xd_read_star_tracker_conf_file */

  status = xd_read_star_tracker_conf_file (input_file, &star_tracker_id,
                                           &star_tracker_conf_data, ierr);
  CHECK_STATUS("xd_read_star_tracker_conf_file",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-11
* ---------
*
********************************************************************/

START_CHECK("Reading Star Tracker files: xd_read_star_tracker validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_STAR_TRACKER_DATA.DBL");
#else
  strcpy (input_file, "../example/data/CRYOSAT_STAR_TRACKER_DATA.DBL");
#endif

  n_files = 1;
  file_list[0] = input_file;
  time_mode = XD_SEL_FILE;

  /* Call  function: xd_read_star_tracker */
  status = xd_read_star_tracker(&n_files, file_list,
                                &time_mode, &time0, &time1,
                                &(star_tracker_conf_data.str_limit),
                                &str_data, ierr);
  CHECK_STATUS("xd_read_star_tracker",status)

  /* Free memory */
  /* ----------- */

  xd_free_star_tracker(&str_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-12
* ---------
*
********************************************************************/

START_CHECK("Reading Generic Attitude file: xd_read_att validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_ATT_FILE.XML");
#else
  strcpy (input_file, "../example/data/CRYOSAT_ATT_FILE.XML");
#endif

  /* Call  function: xd_read_att */
  status = xd_read_att(input_file, &att_data, ierr);
  CHECK_STATUS("xd_read_att",status)

  /* Call  function: xd_read_fhr */
  status = xd_read_fhr(input_file, &fhr, ierr);
  CHECK_STATUS("xd_read_fhr",status)

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-13
* ---------
*
********************************************************************/

START_CHECK("Writing Attitude files: xd_write_att validation")

   strcpy (output_file, "output_att_file.eef");
   
   /* Call  function: xd_wite_att */
   status = xd_write_att(output_file, &fhr, 
                         &att_data, ierr);
   CHECK_STATUS("xd_write_att",status);
   
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-14
* ---------
*
********************************************************************/

START_CHECK("Reading DEM  Files: xd_read_dem validation")

#ifdef WINDOWS
  strcpy (input_file2, "..\\example\\data\\DEM_CONFIG_FILE_val.XML");
#else
  strcpy (input_file2, "../example/data/DEM_CONFIG_FILE_val.XML");
#endif
  strcpy (input_file, "45N000E.GETASSE30");


  /* Call  function: xd_read_dem_config_file */
  /* --------------------------------------- */
  status = xd_read_dem_config_file(input_file2, &dem_config_data, ierr);
  CHECK_STATUS("xd_read_dem_config_file",status);

  /* Call  function: xd_read_dem */
  status = xd_read_dem (input_file, &dem_config_data, &dem_data, ierr);

  CHECK_STATUS("xd_read_dem",status);

  /* Free memory */
  /* ----------- */
  xd_free_dem_config_file(&dem_config_data);
  xd_free_dem(&dem_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-15
* ---------
*
********************************************************************/

START_CHECK("Reading Swath Definition Files: xd_read_sdf validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\SWATH_DEF_FILE");
#else
  strcpy (input_file, "../example/data/SWATH_DEF_FILE");
#endif


  /* Call  function: xd_read_sdf */
  /* --------------------------- */
  status = xd_read_sdf(input_file,
                       &sdf_data, ierr);
  CHECK_STATUS("xd_read_sdf",status);

  /* Free memory */
  /* ----------- */

  xd_free_sdf(&sdf_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-16
* ---------
*
********************************************************************/

START_CHECK("Reading Swath Template Files: xd_read_stf validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\SWATH_TEMPLATE_FILE");
#else
  strcpy (input_file, "../example/data/SWATH_TEMPLATE_FILE");
#endif


  /* Call  function: xd_read_stf */
  /* --------------------------- */
  status = xd_read_stf(input_file,
                       &stf_data, ierr);
  CHECK_STATUS("xd_read_stf", status);


  /* Call  function: xd_read_fhr */
  /* --------------------------- */
  status = xd_read_fhr(input_file, &fhr, ierr);
  CHECK_STATUS("xd_read_fhr", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-17
* ---------
*
********************************************************************/

START_CHECK("Writing Swath Template files: xd_write_stf validation")

   strcpy (output_file, "output_stf_file.eef");

   /* Call  function: xd_wite_stf */
   /* --------------------------- */
   status = xd_write_stf(output_file, &fhr, 
                         &stf_data, ierr);
   CHECK_STATUS("xd_write_stf", status);
   
   /* Free memory */
   /* ----------- */

   xd_free_stf(&stf_data);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-18
* ---------
*
********************************************************************/

START_CHECK("Reading Zone Files: xd_read_zone validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\ZONE_FILE.XML");
#else
  strcpy (input_file, "../example/data/ZONE_FILE.XML");
#endif

  strcpy(zone_id, "ZIOS____");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_zone (input_file, zone_id, &zone_data, ierr);
  CHECK_STATUS("xd_read_zone", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-19
* ---------
*
********************************************************************/

START_CHECK("Reading Station Files: xd_read_station validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\STATION_FILE.XML");
#else
  strcpy (input_file, "../example/data/STATION_FILE.XML");
#endif

  strcpy(station_id, "GTAIWAHX");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_station (input_file, station_id, 
                            &station_data, ierr);
  CHECK_STATUS("xd_read_station", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-20
* ---------
*
********************************************************************/

START_CHECK("Reading Star Files: xd_read_star validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\STAR_FILE.XML");
#else
  strcpy (input_file, "../example/data/STAR_FILE.XML");
#endif

  strcpy(star_id, "Alp Phe");

  /* Call  function: xd_read_zone */
  /* ---------------------------- */
  status = xd_read_star (input_file, star_id, &star_data, ierr);
  CHECK_STATUS("xd_read_star", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-20
* ---------
*
********************************************************************/
START_CHECK("Validating Files: xd_xml_validate validation")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\CRYOSAT_XML_OSF");
  strcpy(schema, "..\\example\\data\\schemas\\EO_OPER_MPL_ORBSCT_0100.XSD");
#else
  strcpy (input_file, "../example/data/CRYOSAT_XML_OSF");
  strcpy(schema, "../example/data/schemas/EO_OPER_MPL_ORBSCT_0100.XSD");
#endif

  /* Call  function: xd_xml_validate */
  /* ------------------------------- */

  mode = XD_USER_SCHEMA;
  strcpy(logfile, "");

  status = xd_xml_validate (input_file, &mode, schema, logfile, &valid_status, ierr);
  CHECK_STATUS("xd_xml_validate", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-21
* ---------
*
********************************************************************/
START_CHECK("Reading TLE file: xd_read_tle")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\NOAA_TLE_FILE");
#else
  strcpy (input_file, "../example/data/NOAA_TLE_FILE");
#endif

  /* Call  function: xd_read_tle */
  /* --------------------------- */

  status = xd_read_tle (input_file, satellite, &tle_data, ierr);
  CHECK_STATUS("xd_read_tle", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-22
* ---------
*
********************************************************************/
START_CHECK("Writing TLE file: xd_write_tle")

  strcpy (output_file, "output_tle_file");

  /* Call  function: xd_write_tle */
  /* ---------------------------- */

  status = xd_write_tle (output_file, &tle_data, ierr);
  CHECK_STATUS("xd_write_tle", status);

  xd_free_tle(&tle_data);
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-23
* ---------
*
********************************************************************/
START_CHECK("Reading precise propagator configuration file: xd_read_precise_propag_file")

#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\PRECISE_PROPAG_CONF.xml");
#else
  strcpy (input_file, "../example/data/PRECISE_PROPAG_CONF.xml");
#endif

  /* Call  function: xd_read_precise_propag_file */
  /* ------------------------------------------- */

  status = xd_read_precise_propag_file(input_file, &precise_conf, ierr);
  CHECK_STATUS("xd_read_precise_propag_file", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-24
* ---------
*
********************************************************************/
START_CHECK("Decimating orbit file state vectors: xd_orbit_file_decimate")

  /* Call  function: xd_orbit_file_decimate */
  /* -------------------------------------- */
  decimation_delta_time = 4*60*60; /* 4 hours in seconds */
  status = xd_orbit_file_decimate(&fhr, &orbit_data,
                                  decimation_delta_time,
                                  &fhr_out, &orbit_data_out,
                                  ierr);
  CHECK_STATUS("xd_orbit_file_decimate", status);

  xd_free_orbit_file(&orbit_data);
  
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-25
* ---------
*
********************************************************************/
START_CHECK("Decimating attitude file records: xd_orbit_file_decimate")

  /* Call  function: xd_orbit_file_decimate */
  /* -------------------------------------- */
  decimation_delta_time = 2.; /* 2 seconds */
  status = xd_attitude_file_decimate(&fhr, &att_data,
                                     decimation_delta_time,
                                     &fhr_out, &att_data_out,
                                     ierr);
  CHECK_STATUS("xd_attitude_file_decimate", status);

  xd_free_att(&att_data);
  xd_free_att(&att_data_out);
  
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-26
* ---------
*
********************************************************************/
START_CHECK("Reading Attitude definition file: xd_read_att_def")

#ifdef WINDOWS
  strcpy(input_file, "..\\example\\data\\att_def_file_angles.xml");
#else
  strcpy(input_file, "../example/data/att_def_file_angles.xml");
#endif

  /* Call  function: xd_read_fhr */
  /* --------------------------- */
  status = xd_read_fhr(input_file, &fhr, ierr);
  CHECK_STATUS("xd_read_fhr", status);
  
  /* Call  function: xd_read_att_def */
  /* -------------------------------------- */
  status = xd_read_att_def(input_file, &att_def_data, ierr);
  CHECK_STATUS("xd_read_att_def", status);

END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-27
* ---------
*
********************************************************************/
START_CHECK("Writing Attitude definition file: xd_write_att_def")

  /* Call  function: xd_write_att_def */
  /* -------------------------------------- */
  strcpy(input_file, "output_att_def_file.xml");
  status = xd_write_att_def(input_file, &fhr, &att_def_data, ierr);
  CHECK_STATUS("xd_write_att_def", status);

  xd_free_att_def(&att_def_data);
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-28
* ---------
*
********************************************************************/
START_CHECK("Reading SP3 file: xd_read_sp3")

#ifdef WINDOWS
  strcpy(input_file, "..\\example\\data\\emr17590.sp3");
#else
  strcpy(input_file, "../example/data/emr17590.sp3");
#endif

  /* Call  function: xd_read_sp3 */
  /* --------------------------- */
  osv_list_read_configuration.time_mode = XD_SEL_FILE;
  status = xd_read_sp3(input_file, &osv_list_read_configuration,
                       &sp3_data, ierr);
  CHECK_STATUS("xd_read_sp3", status);

  xd_free_sp3(&sp3_data);
END_CHECK

/********************************************************************
*
* ---------
* Test case:  Test number          : VT-29
* ---------
*
********************************************************************/
START_CHECK("Read FOV Constraints file: xd_read_fov_constraints_file")
  
#ifdef WINDOWS
  strcpy (input_file, "..\\example\\data\\FOV_test_file.xml");
#else
  strcpy (input_file, "../example/data/FOV_test_file.xml");
#endif

  /* Call  function: xd_read_fov_constraints_file */
  status = xd_read_fov_constraints_file(input_file, 
                                        &fov_constraints,
                                        ierr); 
  CHECK_STATUS("xd_read_fov_constraints_file", status);

END_CHECK

printf("\nEOCFI_DATA_HANDLING VALIDATION COMPLETED SUCCESSFULLY\n");

}
END_VALIDATION

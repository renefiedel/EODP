 /*******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Test level  : VALIDATION
 *
 * Module      : explorer_lib_valid.c
 * Purpose     : It runs validation tests of EXPLORER_LIB
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

#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#include <explorer_lib.h>     /* EXPLORER_LIB header file */



/* Macro definition */
/* ---------------- */

#define MAX_CONDITION                   1000    /* Maximum number of checks per test case */

#define START_VALIDATION                int main(int argc, char *argv[]){ \
                                        double di,th,ta,tb,sinta,costa,sintb,costb;\
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
                                          printf(" *** RESULT = PASS ***\n\n");\
                                          } \
                                        else \
                                          { \
                                          printf(" *** RESULT = FAIL ***\n\n");\
                                          }
#define CHECK_STATUS(msg,stat)          if (stat < XL_OK ) { \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        } \
                                        checks++;


#define CHECK_PAR(msg,p,p0,dp)          if((di=fabs(p-p0)) <= (th=dp)){ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Threshold  : %g\n",th); \
                                        printf("\t\t Difference : %g\n",di); \
                                        checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)    for(i=im;i<=iM;++i){ \
                                          CHECK_PAR(msg,v[i],v0[i],dp); \
                                        }

#define CHECK_STR(msg,str1,str2,maxlength)  if(strncmp(str1,str2,maxlength)==0){ \
					                      condition[checks] = XL_TRUE; \
					                      printf(" ...\t%s (XL_TRUE)\n",msg); \
					                    }else{ \
					                      condition[checks] = XL_FALSE; \
					                      printf(" ...\t%s (XL_FALSE)\n",msg); \
					                    } \
					                    printf("\t\t String 1 : %s\n",str1); \
					                    printf("\t\t String 2 : %s\n",str2); \
					                    checks++;

#define END_VALIDATION                  return(0); \
                                        }

/* Nominal validation values */
/* ------------------------- */

double mjdr[] = { -730.0 , 0.3};
long irep = 35;
long icyc = 501;
double rlong = -47.2941;
double ascmlst = 22.0;
long iorb0 = 0;
long iorb = 43;

double mjdp[] = { -2456.0 , 0.3 };
double pos[] = { 4859964.138 , -5265612.059 , 0.002 };
double vel[] = { -1203.303801, -1098.845511 , 7377.224410 };
double acc[] = { 0.0 , 0.0 , 0.0 };
double aocs[] = { -0.1672 , 0.0501 , 3.9284 };
double att[] = { 0.1 , -0.1 , 0.15 };
double datt[] = { 0.0 , 0.0 , 0.0 };

double longdrs = 15.4;
double mjdrs[] = { -2456.0 , 0.3};
double posdrs[] = { 40652295. , 11197507.0 , -844.0 };
double veldrs[] = { 0.06 , -0.22 , 0.078 };
double sta[] = {0.,0.,0.,0.};



#ifndef M_PI
  static const double M_PI=3.14159265358979323846;
#endif

static const double A = 6378137.0;



/* ------------------------------------------------------------------------- */
/*                                                                           */
/* Validation for EXPLORER_LIB                                               */
/*                                                                           */
/* ------------------------------------------------------------------------- */

START_VALIDATION

/* Local variables definition */
/* -------------------------- */

long   sat_id, time_model, n_files, time_init_mode, time_ref ;
char   **time_file;
double time0, time1, val_time0, val_time1;
long   orbit0, orbit1;
long   local_err[XL_ERR_VECTOR_MAX_LENGTH];

xl_time_id  time_id  = {NULL};
xl_model_id model_id = {NULL};

xl_model_data   model_data;
xl_time_id_data time_id_data;

long   orbit_num;
double anx_time, orbit_duration;
double init_time[4];

long   status=0;
double time;
double r_j2000[3],rd_j2000[3],r2d_j2000[3];
double r_MOD[3],rd_MOD[3],r2d_MOD[3];
double r_TOD[3],rd_TOD[3],r2d_TOD[3];
double r_EF[3],rd_EF[3],r2d_EF[3];
double r_out[3],rd_out[3],r2d_out[3];

long   calc_mode;
double rr[3],rrd[3],rr2d[3];
double lon_in,lat_in,h_in,lond_in,latd_in,hd_in;
double lon_out,lat_out,h_out,lond_out,latd_out,hd_out;

double kepl_out[6];
double pos_out[3], vel_out[3], pos_in[3],vel_in[3];
long   kepl_mode;

double lon1,lat1,lon2,lat2;
double h,d,az1,az2;
double p;

long   time_ref_in, time_ref_out;
long   trans_id_in, trans_id_out, ascii_id_in, ascii_id_out;
long   trans_id, proc_id;
long   transport_in[4], transport_out[4], transport[4];
double processing_in, processing_out;
long   ascii_format;
char   ascii_in[32], ascii_out[32];
char   refstr[4];

double mjdp_pr[2], mjdp_prnew[2];

int    con;
long   cs_in,cs_out;
double psun[3],vsun[3],pmoon[3],vmoon[3],pplanet[3],vplanet[3];
double time_jpl_d,  ut1_d;
long   pcs_in,pcs_out,iplanet;
double rr_out[3],rrd_out[3],rr2d_out[3];
double ang, rmoon[3], rdmoon[3], rsun[3], rdsun[3], rplanet[3], rdplanet[3];
double ra0, dec0, mu_ra, mu_dec, rad_vel, par, ra, dec, ra_p, dec_p;

double time_in_1, time_in_2, time_out, time_out_1;

unsigned long obt0[2],obt[2];
unsigned long period0;

xl_envisat_obt_param envisat_obt_param;
xl_envisat_obt_value envisat_obt_value_in;
xl_envisat_obt_value envisat_obt_value_out;

long angle_type;   
long deriv;
double angle_out;
double angle_rate_out;
double angle_rate_rate_out;

double x_in[3], y_in[3], z_in[3];
double x_out[3], y_out[3], z_out[3];
double ang_in[3], ang_out[3];

double euler_ang[3];
double rot_matrix[3][3];

char sat_init_file[5];
long ierr[1];

long mode;

double pc        = 3.08568025E16,
       KM_PER_AU = 149597870.691;

long catalog_in, catalog_out;
double mu_ra0, mu_dec0;
double rad_vel0, par0;

double pos[3], vel[3]; 
double azim, elev, range;
double azim_d, elev_d, range_d; 
double ef_dir[3], ef_dir_d[3];

long models[XL_NUM_MODEL_TYPES_ENUM];

char iers_file[256];
xd_iers_bulletin_file iers_data;
xl_time_id_init_data  time_id_init_data;
xd_eocfi_file         eocfi_file_array[1];

xl_geoid_calc_inputs geoid_in;
xl_geoid_calc_outputs geoid_out;

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
   if (status != XL_OK)
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
 * Test number          : VT-1A
 *
 ****************************************************************************************/

/*---------- xl_time_id_init validation -------------*/
/*---------------------------------------------------*/

START_CHECK("xl_time_id_init validation")

   time_model     = XL_TIMEMOD_IERS_B_PREDICTED;
   n_files        = 1;
   time_init_mode = XL_SEL_FILE;
   time_ref       = XL_TIME_TAI;

   strcpy (iers_file, "../example/data/bulletinb-283.dat");

   /* read file */
   status = xd_read_bulletin_2(iers_file,
                               &iers_data,
                               ierr);
   CHECK_STATUS("xd_read_bulletin_2 status", status);

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
                            &time_id, local_err);

   CHECK_STATUS("xl_time_ref_init_file",status);

   /* close time_id */
   xl_time_close(&time_id, ierr);

   /* free memory */
   xd_free_bulletin(&iers_data);

END_CHECK

/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1B
 *
 ****************************************************************************************/

/*---------- xl_time_ref_init_file validation -------------*/
/*---------------------------------------------------------*/

START_CHECK("xl_time_ref_init_file validation")

   time_model     = XL_TIMEMOD_IERS_B_PREDICTED;
   n_files        = 1;
   time_init_mode = XL_SEL_TIME;
   time_ref       = XL_TIME_TAI;
   time0          = 742.0;
   time1          = 762.0;
   orbit0         = 0;
   orbit1         = 100;

   time_file=(char **) calloc(5,sizeof(char*));
   time_file[0]=(char *) malloc((size_t)(200*sizeof(char*)));
   strcpy (time_file[0], "../example/data/bulb.dat");

   /* Call xl_time_ref_init_file function */
   /* ----------------------------------- */
   status = xl_time_ref_init_file(&time_model, &n_files, time_file,
                                  &time_init_mode, &time_ref, &time0, &time1,
                                  &orbit0, &orbit1, &val_time0, &val_time1, 
                                  &time_id, local_err);

   CHECK_STATUS("xl_time_ref_init_file",status)

   /* Free memory */
   /* ----------- */
   free((char *)(time_file[0]));
   free((char **)(time_file));

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

/*---------- time id accessors ---------------*/
/*--------------------------------------------*/

START_CHECK("time id accessors validation")

  status = xl_time_init_status(&time_id);
  CHECK_STATUS("xl_time_init_status", status);

  status = xl_time_get_id_data(&time_id, &time_id_data);
  CHECK_STATUS("xl_time_get_id_data", status);

  status = xl_time_set_id_data(&time_id, &time_id_data);
  CHECK_STATUS("xl_time_set_id_data", status);

  free(time_id_data.time_str);
  free (time_id_data.polar_motion_params);

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

/*---------- xl_time_ref_close validation ---------------*/
/*-------------------------------------------------------*/

START_CHECK("xl_time_ref_close validation")

   status = xl_time_close(&time_id, ierr);
   CHECK_STATUS("xl_time_close", status);

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

/*---------- xl_time_ref_init validation ---------------*/
/*------------------------------------------------------*/

START_CHECK("xl_time_ref_init validation")

   init_time[0] = -245.1000000000000000;   /* TAI time [days] */
   init_time[1] = -245.0995949074074074;   /* UTC time [days] (= TAI - 35.0 s) */
   init_time[2] = -245.0995879629629630;   /* UT1 time [days] (= TAI - 35.6 s) */
   init_time[3] = -245.0997800925925926;   /* GPS time [days] (= TAI - 19.0 s) */

   orbit_num = 10;
   anx_time  = 5245.123456;
   orbit_duration = 6035.928144;

   status = xl_time_ref_init(init_time, &orbit_num, &anx_time,
                             &orbit_duration, &time_id, local_err);

   CHECK_STATUS("xl_time_ref_init",status)

   xl_time_close(&time_id, ierr);

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
START_CHECK("xl_model_init and xl_model_get_data")

  /* Input */
  mode = XL_MODEL_DEFAULT;
  
  /* Init model */
  status = xl_model_init( &mode, models, &model_id, ierr );
  CHECK_STATUS("xl_model_init", status);

  /* get model data */
  status = xl_model_get_data(&model_id, &model_data);
  CHECK_STATUS("xl_model_get_data", status);
  
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

/*--------- xl_change_cart_cs validation ------------*/
/*---------------------------------------------------*/

START_CHECK("xl_change_cart_cs validation")

/* REAL DATA AS INPUTS FOR xl_change_cart_cs */
/* ------------------------------------------*/

for(con=0;con<2;con++)
{
   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_UTC;

   if(con==0)
      {

	time    = -1127.5;   /* 1996/11/29 12:00:00.0 */

	init_time[0] = time;   /* TAI time [days] */
	init_time[1] = time;   /* UTC time [days] */
	init_time[2] = time;   /* UT1 time [days] */
	init_time[3] = time;   /* GPS time [days] */
	
	orbit_num = 10;
	anx_time  = 5245.123456;
	orbit_duration = 6035.928144;
	
	status = xl_time_ref_init(init_time, &orbit_num, &anx_time,
				  &orbit_duration, &time_id, local_err);
	
	CHECK_STATUS("xl_time_ref_init",status)
	  
      /* AT THIS TIME : */

      r_j2000[0]=  (double)4954.255420826*1000.;
      r_j2000[1]=  (double)5176.446063286*1000.;
      r_j2000[2]=  (double)-39.764584115*1000. ;
      rd_j2000[0]= (double)   0.821544143*1000.;
      rd_j2000[1]= (double)  -0.741319667*1000.;
      rd_j2000[2]= (double)   7.377656733*1000.;
      r2d_j2000[0]=(double)0.;
      r2d_j2000[1]=(double)0.;
      r2d_j2000[2]=(double)0.;

      r_MOD[0]=   (double)4957.816882545*1000.;
      r_MOD[1]=   (double)5173.023476164*1000.;
      r_MOD[2]=   (double) -41.251875801*1000.;
      rd_MOD[0]=  (double)   0.823245938*1000.;
      rd_MOD[1]=  (double)  -0.741887569*1000.;
      rd_MOD[2]=  (double)   7.377409950*1000.;
      r2d_MOD[0]= (double)0.;
      r2d_MOD[1]= (double)0.;
      r2d_MOD[2]= (double)0.;

      r_TOD[0]=  (double) 4957.803233005*1000.;
      r_TOD[1]=  (double) 5173.034652428*1000.;
      r_TOD[2]=  (double)  -41.490126861*1000.;
      rd_TOD[0]= (double)    0.823239720*1000.;
      rd_TOD[1]= (double)   -0.741537770*1000.;
      rd_TOD[2]= (double)    7.377445812*1000.;
      r2d_TOD[0]=(double)0.;
      r2d_TOD[1]=(double)0.;
      r2d_TOD[2]=(double)0.;

      r_EF[0]=  (double)-6622.972393372*1000.;
      r_EF[1]=  (double) 2734.289198770*1000.;
      r_EF[2]=  (double)  -41.486108382*1000.;
      rd_EF[0]= (double)    0.590333424*1000.;
      rd_EF[1]= (double)    1.519660870*1000.;
      rd_EF[2]= (double)    7.377446179*1000.;
      r2d_EF[0]=(double)0.;
      r2d_EF[1]=(double)0.;
      r2d_EF[2]=(double)0.;

      }

   else if(con==1)
      {

      time    = -1127.48611111;     /* 1996/11/29 12:20:00.0 */

      /* AT THIS TIME : */

      r_j2000[0]=  (double) 2310.184281427*1000.;
      r_j2000[1]=  (double)  956.353819725*1000.;
      r_j2000[2]=  (double) 6703.713927191*1000.;
      rd_j2000[0]= (double)   -4.637710611*1000.;
      rd_j2000[1]= (double)   -5.350625551*1000.;
      rd_j2000[2]= (double)    2.356550956*1000.;
      r2d_j2000[0]=(double) 0.;
      r2d_j2000[1]=(double) 0.;
      r2d_j2000[2]=(double) 0.;

      r_MOD[0]=   (double) 2312.855805854*1000.;
      r_MOD[1]=   (double)  954.757527635*1000.;
      r_MOD[2]=   (double) 6703.020255454*1000.;
      rd_MOD[0]=  (double)   -4.640697179*1000.;
      rd_MOD[1]=  (double)   -5.347421788*1000.;
      rd_MOD[2]=  (double)    2.357943157*1000.;
      r2d_MOD[0]= (double) 0.;
      r2d_MOD[1]= (double) 0.;
      r2d_MOD[2]= (double) 0.;

      r_TOD[0]=  (double) 2312.845831401*1000.;
      r_TOD[1]=  (double)  955.079493995*1000.;
      r_TOD[2]=  (double) 6702.977829338*1000.;
      rd_TOD[0]= (double)   -4.640685624*1000.;
      rd_TOD[1]= (double)   -5.347322980*1000.;
      rd_TOD[2]= (double)    2.358189964*1000.;
      r2d_TOD[0]=(double) 0.;
      r2d_TOD[1]=(double) 0.;
      r2d_TOD[2]=(double) 0.;

      r_EF[0]=  (double) -1567.051918508*1000.;
      r_EF[1]=  (double)  1950.835982494*1000.;
      r_EF[2]=  (double)  6702.979316274*1000.;
      rd_EF[0]= (double)     6.578987079*1000.;
      rd_EF[1]= (double)    -2.835026155*1000.;
      rd_EF[2]= (double)     2.358185925*1000.;
      r2d_EF[0]=(double) 0.;
      r2d_EF[1]=(double) 0.;
      r2d_EF[2]=(double) 0.;

      }

   START_CHECK("xl_change_cart_cs validation.")

   /* From GM2000 to MOD */
   /* ------------------ */

   cs_in=XL_GM2000;
   cs_out=XL_MOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_j2000,rd_j2000,r2d_j2000,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from GM2000 to MOD(m)",r_out,r_MOD,0,2,1e-3)
   CHECK_VEC("Velocity vector from GM2000 to MOD(m/s)",rd_out,rd_MOD,0,2,1e-5)
   /* CHECK_VEC("Acceleration vector from GM2000 to MOD(m/s**2)",r2d_out,r2d_MOD,0,2,1e-7) */

   /* From GM2000 to TOD */
   /* ------------------ */

   cs_in=XL_GM2000;
   cs_out=XL_TOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_j2000,rd_j2000,r2d_j2000,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from GM2000 to TOD(m)",r_out,r_TOD,0,2,1)
   CHECK_VEC("Velocity vector from GM2000 to TOD(m/s)",rd_out,rd_TOD,0,2,1e-3)
   /* CHECK_VEC("Acceleration vector from GM2000 to TOD(m/s**2)",r2d_out,r2d_TOD,0,2,1e-6) */


   /* From GM2000 to EF */
   /* ----------------- */

   cs_in=XL_GM2000;
   cs_out=XL_EF;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_j2000,rd_j2000,r2d_j2000,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from GM2000 to EF(m)",r_out,r_EF,0,2,30)
   CHECK_VEC("Velocity vector from GM2000 to EF(m/s)",rd_out,rd_EF,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from GM2000 to EF(m/s**2)",r2d_out,r2d_EF,0,2,1) */


   /* From MOD to GM2000 */
   /* ------------------ */

   cs_in=XL_MOD;
   cs_out=XL_GM2000;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_MOD,rd_MOD,r2d_MOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from MOD to GM2000(m)",r_out,r_j2000,0,2,1e-3)
   CHECK_VEC("Velocity vector from MOD to GM2000(m/s)",rd_out,rd_j2000,0,2,1e-5)
   /* CHECK_VEC("Acceleration vector from MOD to GM2000(m/s**2)",r2d_out,r2d_j2000,0,2,1e-7) */


   /* From MOD to TOD */
   /* --------------- */

   cs_in=XL_MOD;
   cs_out=XL_TOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_MOD,rd_MOD,r2d_MOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from MOD to TOD(m)",r_out,r_TOD,0,2,1)
   CHECK_VEC("Velocity vector from MOD to TOD(m/s)",rd_out,rd_TOD,0,2,1e-3)
   /* CHECK_VEC("Acceleration vector from MOD to TOD(m/s**2)",r2d_out,r2d_TOD,0,2,1e-6) */


   /* From MOD to EF */
   /* -------------- */

   cs_in=XL_MOD;
   cs_out=XL_EF;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_MOD,rd_MOD,r2d_MOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from MOD to EF(m)",r_out,r_EF,0,2,30)
   CHECK_VEC("Velocity vector from MOD to EF(m/s)",rd_out,rd_EF,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from MOD to EF(m/s**2)",r2d_out,r2d_EF,0,2,1) */


   /* From TOD to GM2000 */
   /* ------------------ */

   cs_in=XL_TOD;
   cs_out=XL_GM2000;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_TOD,rd_TOD,r2d_TOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from TOD to GM2000(m)",r_out,r_j2000,0,2,1)
   CHECK_VEC("Velocity vector from TOD to GM2000(m/s)",rd_out,rd_j2000,0,2,1e-3)
   /* CHECK_VEC("Acceleration vector from TOD to GM2000(m/s**2)",r2d_out,r2d_j2000,0,2,1e-6) */


   /* From TOD to MOD */
   /* --------------- */

   cs_in=XL_TOD;
   cs_out=XL_MOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_TOD,rd_TOD,r2d_TOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from TOD to MOD(m)",r_out,r_MOD,0,2,1)
   CHECK_VEC("Velocity vector from TOD to MOD(m/s)",rd_out,rd_MOD,0,2,1e-3)
   /* CHECK_VEC("Acceleration vector from TOD to MOD(m/s**2)",r2d_out,r2d_MOD,0,2,1e-6) */


   /* From TOD to EF */
   /* -------------- */

   cs_in=XL_TOD;
   cs_out=XL_EF;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_TOD,rd_TOD,r2d_TOD,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from TOD to EF(m)",r_out,r_EF,0,2,30)
   CHECK_VEC("Velocity vector from TOD to EF(m/s)",rd_out,rd_EF,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from TOD to EF(m/s**2)",r2d_out,r2d_EF,0,2,1) */


   /* From EF to GM2000 */
   /* ----------------- */

   cs_in=XL_EF;
   cs_out=XL_GM2000;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_EF,rd_EF,r2d_EF,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from EF to GM2000(m)",r_out,r_j2000,0,2,30)
   CHECK_VEC("Velocity vector from EF to GM2000(m/s)",rd_out,rd_j2000,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from EF to GM2000(m/s**2)",r2d_out,r2d_j2000,0,2,1) */


   /* From EF to MOD */
   /* -------------- */

   cs_in=XL_EF;
   cs_out=XL_MOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_EF,rd_EF,r2d_EF,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from EF to MOD(m)",r_out,r_MOD,0,2,30)
   CHECK_VEC("Velocity vector from EF to MOD(m/s)",rd_out,rd_MOD,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from EF to MOD(m/s**2)",r2d_out,r2d_MOD,0,2,1) */


   /* From EF to TOD */
   /* -------------- */

   cs_in=XL_EF;
   cs_out=XL_TOD;

   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &cs_in, &cs_out, &time_ref, &time,
                              r_EF,rd_EF,r2d_EF,r_out,rd_out,r2d_out);

   CHECK_STATUS("xl_change_cart_cs",status)

   CHECK_VEC("Position vector from EF to TOD(m)",r_out,r_TOD,0,2,30)
   CHECK_VEC("Velocity vector from EF to TOD(m/s)",rd_out,rd_TOD,0,2,5e-2)
   /* CHECK_VEC("Acceleration vector from EF to TOD(m/s**2)",r2d_out,r2d_TOD,0,2,1) */

}

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

/*-------- xl_cart_to_geod & xl_geod_to_cart validation ---------*/
/*---------------------------------------------------------------*/

START_CHECK("xl_cart_to_geod & xl_geod_to_cart validation.")
{
  /*--- Initialize input data ---*/

  calc_mode = XL_CALC_POS_VEL;

  lon_in    = 60.0;
  lat_in    = 70.0;
  h_in      = 2000000.0;

  lond_in   = 5.0;
  latd_in   = 2.5;
  hd_in     = 1000.0;

  strcpy(sat_init_file,"");
  /*------------------------------*/

  status = xl_default_sat_init(&sat_id, sat_init_file, ierr);
  CHECK_STATUS("xl_default_sat_init status",status);

  xl_default_sat_close(&sat_id);

  status = xl_geod_to_cart(&model_id, &calc_mode, &lon_in, &lat_in, &h_in,
                           &lond_in, &latd_in, &hd_in, rr, rrd);

  CHECK_STATUS("xl_geod_to_cart status",status);


  status = xl_cart_to_geod(&model_id, &calc_mode, rr, rrd, &lon_out, &lat_out, &h_out,
                           &lond_out, &latd_out, &hd_out);

  CHECK_STATUS("xl_cart_to_geod status",status);

  /*------------------------------*/

  CHECK_PAR ("Geocentric longitude consistency.     ",lon_out, lon_in, 1e-6);
  CHECK_PAR ("Geodetic latitude consistency.        ",lat_out, lat_in, 1e-6);
  CHECK_PAR ("Geodetic altitude consistency.        ",h_out,   h_in,   1e-3);
  CHECK_PAR ("Geocentric longitude rate consistency.",lond_out,lond_in,1e-3);
  CHECK_PAR ("Geodetic latitude rate consistency.   ",latd_out,latd_in,1e-3);
  CHECK_PAR ("Geodetic altitude rate consistency.   ",hd_out,  hd_in,  1e-3);
}
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


/*---------- xl_attitude_cs validation --------------*/
/*---------------------------------------------------*/
/* Test deleted, function moved to EXPLORER_POINTING */


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-9
 *
 ****************************************************************************************/

/*-------- xl_cart_to_kepl & xl_kepl_to_cart validation ---------*/
/*---------------------------------------------------------------*/

START_CHECK("xl_cart_to_kepl & xl_kepl_to_cart validation.")
{
  /*--- Initialize input data ---*/

  kepl_mode = XL_KEPLER_OSC;

  pos_in[0] =   4859964.138;       /* Position vector in the Earth fixed coordinate system (x,y,z) [m] */
  pos_in[1] =  -5265612.059;
  pos_in[2] =         0.002;
  vel_in[0] =  -1203.303801;       /* Velocity vector in the Earth fixed coordinate system (x,y,z) [m/s] */
  vel_in[1] =  -1098.845511;
  vel_in[2] =   7377.224410;

  /*------------------------------*/

  status = xl_cart_to_kepl(&model_id, pos_in, vel_in, &kepl_mode, kepl_out, local_err );

  CHECK_STATUS("xl_cart_to_kepl status",status);

  status = xl_kepl_to_cart(&model_id, &kepl_mode, kepl_out, pos_out, vel_out, local_err );

  CHECK_STATUS("xl_kepl_to_cart status",status);


  /*------------------------------*/
  
  CHECK_VEC ("Position Vector. ",pos_in,pos_out,0,2,1e-3);
  CHECK_VEC ("Velocity Vector. ",vel_in,vel_out,0,2,1e-3);
}
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

/*------------ xl_geod_distance validation -------------------*/
/*------------------------------------------------------------*/

START_CHECK("xl_geod_distance validation")

/*--- Input Initialization ---*/
/*----------------------------*/

lon1 = 0.0;
lat1 = 0.0;
lon2 = 90.0;
lat2 = 0.0;
h    = 0.0;

/*------------------------------*/

status = xl_geod_distance(&model_id, &lon1, &lat1, &lon2, &lat2, &h, &d, &az1, &az2);

CHECK_STATUS("xl_geod_distance status",status)

/*------------------------------*/

p=(M_PI)*A/2.0;

CHECK_PAR("AT-21.Geodesic distance accuracy.       ",d,p,20000)
printf("\t\tGeodesic distance is equal to: %lf m.\n",d);
CHECK_PAR("AT-21.Geodesic azimuth of initial point.",az1,90.0,1e-6)
CHECK_PAR("AT-21.Geodesic azimuth of final point.  ",az2,270.0,1e-6)

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

/*------ xl_time_ascii_to_processing & xl_time_processing_to_ascii validation -------*/
/*-----------------------------------------------------------------------------------*/

START_CHECK("xl_time_ascii_to_processing & xl_time_processing_to_ascii validation")

  for (time_ref=0; time_ref < 4; time_ref ++) {

      /* Set time references */
      /* ------------------- */
      time_ref_in  = time_ref;
      time_ref_out = time_ref_in;

	  /* Define time reference string */
	  /* ---------------------------- */

	  if     (time_ref_in == 1) strcpy (refstr, "UTC");
	  else if(time_ref_in == 2) strcpy (refstr, "UT1");
	  else if(time_ref_in == 3) strcpy (refstr, "GPS");
	  else                      strcpy (refstr, "TAI");

      printf(" ...\t---------------------------\n");
      printf(" ...\tTime Reference =   %ld\n",time_ref);
      printf(" ...\t---------------------------\n");

      for (ascii_format=0; ascii_format <= 15; ascii_format ++)  {
		  /* Set input time format and input values */
		  /* -------------------------------------- */
		  if      (ascii_format == 0) {
				  /* ASCII Standard: "yyyy-mm-dd_hh:mm:ss" */
				  ascii_id_in = XL_ASCII_STD;
				  strcpy (ascii_in, "2010-05-03_14:12:10");
				  }
		  else if (ascii_format == 1) {
				  /* ASCII Standard with reference: "RRR=yyyy-mm-dd_hh:mm:ss" */
				  ascii_id_in = XL_ASCII_STD_REF;
				  (void) sprintf(ascii_in, "%3s=2010-05-03_14:12:10", refstr);
				  }
		  else if (ascii_format == 2) {
				  /* ASCII Standard with microseconds: "yyyy-mm-dd_hh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_STD_MICROSEC;
				  strcpy (ascii_in, "2010-05-03_14:12:10.123456");
				  }
		  else if (ascii_format == 3) {
				  /* ASCII Standard with rererence and micrseconds: "RRR=yyyy-mm-dd_hh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_STD_REF_MICROSEC;
				  (void) sprintf(ascii_in, "%3s=2010-05-03_14:12:10.123456", refstr);
				  }
		  else if (ascii_format == 4) {
				  /* ASCII Compact: "yyyymmdd_hhmmss" */
				  ascii_id_in = XL_ASCII_COMPACT;
				  strcpy (ascii_in, "20100503_141210");
				  }
		  else if (ascii_format == 5) {
				  /* ASCII Compact with reference: "RRR=yyyymmdd_hhmmss" */
				  ascii_id_in = XL_ASCII_COMPACT_REF;
				  (void) sprintf(ascii_in, "%3s=20100503_141210", refstr);
				  }
		  else if (ascii_format == 6) {
				  /* ASCII Compact with microseconds: "yyyymmdd_hhmmssuuuuuu" */
				  ascii_id_in = XL_ASCII_COMPACT_MICROSEC;
				  strcpy (ascii_in, "20100503_141210123456");
				  }
		  else if (ascii_format == 7) {
				  /* ASCII Compact with rererence and micrseconds: "RRR=yyyymmdd_hhmmssuuuuuu" */
				  ascii_id_in = XL_ASCII_COMPACT_REF_MICROSEC;
				  (void) sprintf(ascii_in, "%3s=20100503_141210123456", refstr);
				  }
		  else if (ascii_format == 8) {
				  /* ASCII Envisat: "dd-mmm-yyyy hh:mm:ss" */
				  ascii_id_in = XL_ASCII_ENVI;
				  strcpy (ascii_in, "03-MAY-2010 14:12:10");
				  }
		  else if (ascii_format == 9) {
				  /* ASCII Envisat with reference: "RRR=dd-mmm-yyyy hh:mm:ss" */
				  ascii_id_in = XL_ASCII_ENVI_REF;
				  (void) sprintf(ascii_in, "%3s=03-MAY-2010 14:12:10", refstr);
				  }
		  else if (ascii_format ==10) {
				  /* ASCII Envisat with microseconds: "dd-mmm-yyyy hh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_ENVI_MICROSEC;
				  strcpy (ascii_in, "03-MAY-2010 14:12:10.123456");
				  }
		  else if (ascii_format ==11) {
				  /* ASCII Envisat with rererence and micrseconds: "RRR=dd-mmm-yyyy hh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_ENVI_REF_MICROSEC;
				  (void) sprintf(ascii_in, "%3s=03-MAY-2010 14:12:10.123456", refstr);
				  }
		  else if (ascii_format ==12) {
				  /* ASCII CCSDS-A: "yyyy-mm-ddThh:mm:ss" */
				  ascii_id_in = XL_ASCII_CCSDSA;
				  strcpy (ascii_in, "2010-05-03T14:12:10");
				  }
		  else if (ascii_format ==13) {
				  /* ASCII CCSDS-A with reference: "RRR=yyyy-mm-ddThh:mm:ss" */
				  ascii_id_in = XL_ASCII_CCSDSA_REF;
				  (void) sprintf(ascii_in, "%3s=2010-05-03T14:12:10", refstr);
				  }
		  else if (ascii_format ==14) {
				  /* ASCII CCSDS-A with microseconds: "yyyy-mm-ddThh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_CCSDSA_MICROSEC;
				  strcpy (ascii_in, "2010-05-03T14:12:10.123456");
				  }
		  else if (ascii_format ==15) {
				  /* ASCII CCSDS-A with rererence and micrseconds: "RRR=yyyy-mm-ddThh:mm:ss.uuuuuu" */
				  ascii_id_in = XL_ASCII_CCSDSA_REF_MICROSEC;
				  (void) sprintf(ascii_in, "%3s=2010-05-03T14:12:10.123456", refstr);
				  }

		  /* Set output time format */
		  /* ---------------------- */
          proc_id=XL_PROC;


         /* Call xl_time_ascii_to_processing function */
         /* ----------------------------------------- */
         status = xl_time_ascii_to_processing(&time_id, &ascii_id_in, &time_ref_in,
                                              ascii_in, &proc_id, &time_ref_out, &processing_out, 
                                              local_err);


         CHECK_STATUS( "xl_time_ascii_to_processing status", status )

         /* Call xl_time_processing_to_ascii function */
         /* ----------------------------------------- */
         status = xl_time_processing_to_ascii(&time_id, &proc_id, &time_ref_in,
                                              &processing_out, &ascii_id_in, &time_ref_out, 
                                              ascii_out, local_err);

         CHECK_STATUS( "xl_time_processing_to_ascii status", status )


      /* Check that the values at the end of the loop are equal to the starting conditions */

	  CHECK_STR("Comparing date with target:       ", ascii_in, ascii_out, 32)

      }
  }

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

/*------ xl_time_ascii_to_transport & xl_time_transport_to_ascii validation -------*/
/*---------------------------------------------------------------------------------*/

START_CHECK("xl_time_ascii_to_transport & xl_time_transport_to_ascii validation")

/*--- Initialize input data ---*/

ascii_id_in  = XL_ASCII_STD;
time_ref_in  = XL_TIME_TAI;
trans_id     = XL_TRANS_CRYO_TM;
time_ref_out = XL_TIME_UT1;

strcpy (ascii_in, "2010-05-03_14:12:10");

/*------------------------------*/

status = xl_time_ascii_to_transport(&time_id,  &ascii_id_in,  &time_ref_in,
                                    ascii_in, &trans_id, &time_ref_out,
                                    transport, local_err);

CHECK_STATUS( "xl_time_ascii_to_transport status", status )

/*------------------------------*/

status = xl_time_transport_to_ascii(&time_id, &trans_id,  &time_ref_out,
                                    transport, &ascii_id_in, &time_ref_in,
                                    ascii_out, local_err);

CHECK_STATUS( "xl_time_transport_to_ascii status", status )


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

/*------ xl_time_ascii_to_ascii, xl_time_processing_to_processing & xl_time_transport_to_transport validation -------*/
/*-------------------------------------------------------------------------------------------------------------------*/

START_CHECK("xl_time_ascii_to_ascii, xl_time_processing_to_processing & xl_time_transport_to_transport validation")

/*--- Initialize input data ---*/

time_ref_in     = XL_TIME_TAI;
time_ref_out    = XL_TIME_UT1;

ascii_id_in     = XL_ASCII_STD;
ascii_id_out    = XL_ASCII_COMPACT_REF_MICROSEC;
strcpy (ascii_in, "2010-05-03_14:12:10");

proc_id         = XL_PROC;
processing_in   = 245.1;  /* TAI time [days] */

trans_id_in     = XL_TRANS_CRYO_TM_SIRAL;
trans_id_out    = XL_TRANS_STD;
transport_in[0] = 245;    /* UTC time [integer days]         */
transport_in[1] = 6000;   /* UTC time [integer milliseconds] */
transport_in[2] = 500;    /* UTC time [integer microseconds] */
transport_in[3] = 300000; /* Extra SIRAL counter ticks       */

/*------------------------------*/

status = xl_time_ascii_to_ascii(&time_id,  &ascii_id_in,  &time_ref_in,
                                ascii_in, &ascii_id_out, &time_ref_out,
                                ascii_out, local_err);

CHECK_STATUS( "xl_time_ascii_to_ascii status", status )

/*------------------------------*/

status = xl_time_processing_to_processing(&time_id, &proc_id,
                                          &time_ref_in, &processing_in, &proc_id,
                                          &time_ref_out, &processing_out, local_err);

CHECK_STATUS( "xl_time_processing_to_processing status", status )

/*------------------------------*/

status = xl_time_transport_to_transport(&time_id, &trans_id_in,
                                        &time_ref_in, transport_in, &trans_id_out,
                                        &time_ref_out, transport_out, local_err);

CHECK_STATUS( "xl_time_transport_to_transport status", status )


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

/*----------- xl_sun, xl_moon, xl_planet & xl_star_radec validation -----------*/
/*-----------------------------------------------------------------------------*/

START_CHECK("xl_sun, xl_moon, xl_planet & xl_star_radec validation.")

/*--- Initialize input data ---*/

   calc_mode = XL_CALC_POS_VEL_ACC;
   time_ref  = XL_TIME_TAI;

   /* Output data taken from JPL file for date 1 Jan 1997.
      Given in GEO-MEAN-2000 reference system              */

   psun[0] =  27194878.68362263;
   psun[1] = -132630129.1728563;
   psun[2] = -57503402.89730293;
   vsun[0] = 29.76142628120521;
   vsun[1] = 5.144322852105286;
   vsun[2] = 2.231621282770508;
   pmoon[0] = -401090.0604245735;
   pmoon[1] =    8806.974516115712;
   pmoon[2] =    1317.167354695972;
   vmoon[0] = 0.01573390305025041;
   vmoon[1] = -0.924535097549946;
   vmoon[2] = -0.3073301858923245;
   pplanet[0] =  360537246.5220062;
   pplanet[1] = -620606064.8551784;
   pplanet[2] = -274804229.4228395;
   vplanet[0] = 11.37592527879614;
   vplanet[1] = 6.301985231532927;
   vplanet[2] = 2.424137059795838;

   /* To compare with JPL data we will need to transform from MEAN-2000 to EF or TOD  */

   time_jpl_d = -1095.0;

   pcs_in=XL_GM2000;  /* GEO_MEAN_2000 */
   pcs_out=XL_EF;    /* EARTH_FIXED */

   /* Moon */
   for( i=0 ; i<3 ; i++ ) {
      rr[i] = pmoon[i];
      rrd[i] =vmoon[i];
   }
   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &pcs_in, &pcs_out, &time_ref, &time_jpl_d,
                              rr,rrd,rr2d,rr_out,rrd_out,rr2d_out);
   for( i=0 ; i<3 ; i++ ) {
      pmoon[i] = rr_out[i];
      vmoon[i] = rrd_out[i];
   }

   /* Sun */
   for( i=0 ; i<3 ; i++ ) {
      rr[i] = psun[i];
      rrd[i] =vsun[i];
   }
   pcs_out = XL_TOD;
   status = xl_change_cart_cs(&model_id, &time_id, &calc_mode, &pcs_in, &pcs_out, &time_ref, &time_jpl_d,
                              rr,rrd,rr2d,rr_out,rrd_out,rr2d_out);
   for( i=0 ; i<3 ; i++ ) {
      psun[i] = rr_out[i];
      vsun[i] = rrd_out[i];
   }

   ut1_d     = -1095.0;
   time_ref  = XL_TIME_UT1;

   ra0 = 1.2;     /* rad */
   dec0 = 0.2;    /* rad */
   mu_ra = 0.;    /* rad/century */
   mu_dec = 0.;   /* rad/century */
   rad_vel = 0.;  /* AU/century */
   par = 0.;      /* rad */
   ra=dec=0;

   ra_p = 1.2;    /* Guess of the true values */
   dec_p = 0.2;

/*------------------------------*/

status = xl_sun(&model_id, &time_id, &time_ref, &ut1_d, rsun, rdsun, local_err);

CHECK_STATUS("xl_sun status",status)

status = xl_moon(&model_id, &time_id, &time_ref, &ut1_d, rmoon, rdmoon, local_err);

CHECK_STATUS("xl_moon status",status)

iplanet=5;

status = xl_planet(&model_id, &time_id, &iplanet, &time_ref, &ut1_d, rplanet, rdplanet, local_err);

CHECK_STATUS("xl_planet status",status)

status = xl_star_radec(&model_id, &time_id, &time_ref, &ut1_d, &ra0, &dec0, &mu_ra, &mu_dec,
                          &rad_vel, &par, &ra, &dec, local_err);

CHECK_STATUS("xl_star_radec status",status)


   /* Tranform planet state vector to the HM_2000 CS for comparison */
   for( i=0 ; i<3 ; i++ ) {
     rr[i] = rplanet[i];
     rrd[i] =rdplanet[i];
   }
   calc_mode = XL_CALC_POS_VEL;
   pcs_in = XL_EF;
   pcs_out = XL_HM2000;
   time_ref = XL_TIME_TAI;

   status = xl_change_cart_cs (&model_id, &time_id, &calc_mode, &pcs_in, &pcs_out, &time_ref, &time_jpl_d, 
		   rr,rrd,rr2d,
		   rr_out,rrd_out,rr2d_out);
   CHECK_STATUS( "XL_CHANGE_CART_CS status", status ) 

   for( i=0 ; i<3 ; i++ ) {
      rplanet[i] = rr_out[i];
      rdplanet[i] = rrd_out[i];
      }


   /* Tranform sun state vector to the TOD CS for comparison */
   /* Note: Direct comparison in the EF CS is not allowable, because it doesn't reach acceptable threshold */
   for( i=0 ; i<3 ; i++ ) {
     rr[i] = rsun[i];
     rrd[i] =rdsun[i];
   }
   calc_mode = XL_CALC_POS_VEL;
   pcs_in = XL_EF;
   pcs_out = XL_TOD;
   time_ref = XL_TIME_TAI;

   status = xl_change_cart_cs (&model_id, &time_id, &calc_mode, &pcs_in, &pcs_out, &time_ref, &time_jpl_d, 
		   rr,rrd,rr2d,
		   rr_out,rrd_out,rr2d_out);
   CHECK_STATUS( "XL_CHANGE_CART_CS status", status ) 

   for( i=0 ; i<3 ; i++ ) {
      rsun[i] = rr_out[i];
      rdsun[i] = rrd_out[i];
      }

   for( i=0 ; i<3 ; i++ ) {  /* transform to km and km/s  */
   rsun[i] /=1000.;
   rdsun[i] /=1000.;
   rmoon[i] /=1000.;
   rdmoon[i] /=1000.;
   rplanet[i] /=1000.;
   rdplanet[i] /=1000.;
}
/*------------------------------*/

CHECK_VEC( "Sun position consistency:   ", rsun, psun, 0,2, 2000.0 )
CHECK_VEC( "Sun velocity consistency:   ", rdsun, vsun, 0,2, 0.005 )
ang = acos( (rsun[0]*psun[0]+rsun[1]*psun[1]+rsun[2]*psun[2])/sqrt(rsun[0]*rsun[0]+rsun[1]*rsun[1]+rsun[2]*rsun[2])/sqrt(psun[0]*psun[0]+psun[1]*psun[1]+psun[2]*psun[2]))*
      (180000./M_PI);
CHECK_PAR( "Sun angle difference(mdeg)  ", ang, 0., 1. )

CHECK_VEC( "Moon position consistency:  ", rmoon, pmoon, 0,2, 100.0 )
CHECK_VEC( "Moon velocity consistency:  ", rdmoon, vmoon, 0,2, 0.005 )
ang = acos( (rmoon[0]*pmoon[0]+rmoon[1]*pmoon[1]+rmoon[2]*pmoon[2])/sqrt(rmoon[0]*rmoon[0]+rmoon[1]*rmoon[1]+rmoon[2]*rmoon[2])/sqrt( pmoon[0]*pmoon[0]+pmoon[1]*pmoon[1]+pmoon[2]*pmoon[2]))*
      (180000./M_PI);
CHECK_PAR( "Moon angle difference(mdeg) ", ang, 0., 10 )

CHECK_VEC( "Planet position consistency:  ", rplanet, pplanet, 0,2, 200000.0 )
CHECK_VEC( "Planet velocity consistency:  ", rdplanet, vplanet, 0,2, 0.1 )
ang = acos( (rplanet[0]*pplanet[0]+rplanet[1]*pplanet[1]+rplanet[2]*pplanet[2])/sqrt(rplanet[0]*rplanet[0]+rplanet[1]*rplanet[1]+rplanet[2]*rplanet[2])/sqrt( pplanet[0]*pplanet[0]+pplanet[1]*pplanet[1]+pplanet[2]*pplanet[2]))*
      (180000./M_PI);
CHECK_PAR( "Planet angle difference(mdeg) ", ang, 0., 10. )

CHECK_PAR( "Star RA  consistency:         ", ra, ra_p, 1e-3 )
CHECK_PAR( "Star DEC consistency:         ", dec, dec_p, 1e-3 )

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

/*------------ xl_time_add & xl_time_diff validation ---------------*/
/*------------------------------------------------------------------*/

START_CHECK("xl_time_add & xl_time_diff validation")

   proc_id  = XL_PROC;
   time_ref = XL_TIME_TAI;

   time_in_1 = 245.123456;   /* Processing Time, MJD2000 [days] */
   time_in_2 = 110.100001;   /* Processing Time, MJD2000 [days] */

   status = xl_time_add(&proc_id, &time_ref, &time_in_1, &time_in_2, &time_out, local_err);
   CHECK_STATUS("xl_time_add status",status)

   status = xl_time_diff(&proc_id, &time_ref, &time_out, &time_in_2, &time_out_1, local_err);
   CHECK_STATUS("xl_time_diff status",status)

   CHECK_PAR( "xl_time_add & xl_time_diff consistency:  ", time_in_1, time_out_1, 1e-11)

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


/*----------xl_time_obt_to_time & xl_time_time_to_obt----------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xl_time_obt_to_time & xl_time_time_to_obt validation")

   /* Set input values */
   /* ---------------- */
   sat_id   = XL_SAT_ENVISAT;
   proc_id  = XL_PROC;

   time0   = 1111.995374228;   /* [days] */
   obt0[0] = 0xABCDEF01;
   obt0[1] = 0x00000000;
   period0 = (1/256.0)*1.0E12; /* [picoseconds] */
   obt[0]  = 0xABCDEF01;
   obt[1]  = 0x00000000;

   envisat_obt_param.sat_id  = sat_id;
   envisat_obt_param.time0   = time0;
   envisat_obt_param.obt0[0] = obt0[0];
   envisat_obt_param.obt0[1] = obt0[1];
   envisat_obt_param.period0 = period0;
   
   envisat_obt_value_in.sat_id  = sat_id;
   envisat_obt_value_in.obt[0]  = obt[0];
   envisat_obt_value_in.obt[1]  = obt[1];
   
   status = xl_time_obt_to_time(&sat_id, &proc_id, &envisat_obt_param, 
                                &envisat_obt_value_in, &time_out, local_err);

   CHECK_STATUS("xl_time_obt_to_time status",status)

   status = xl_time_time_to_obt(&sat_id, &proc_id, &envisat_obt_param, 
                                &time_out, &envisat_obt_value_out, local_err);

   CHECK_STATUS("xl_time_time_to_obt status",status)

   CHECK_PAR ("obt consistency LSB",envisat_obt_value_in.obt[0],envisat_obt_value_out.obt[0],1e-11)
   CHECK_PAR ("obt consistency MSB",envisat_obt_value_in.obt[1],envisat_obt_value_out.obt[1],1e-11)

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


/*----------xl_position_on_orbit----------------*/
/*----------------------------------------------*/

START_CHECK("xl_position_on_orbit")

   /* Set input values */
   /* ---------------- */
   angle_type = XL_ANGLE_TYPE_TRUE_LAT_TOD;
   time  = 0.0;
   deriv = XL_DER_2ND;

   status = xl_position_on_orbit(&model_id, &time_id, &angle_type, &time_ref, &time,
				 pos_in, vel_in, acc, &deriv,
				 &angle_out, &angle_rate_out, &angle_rate_rate_out,
				 local_err);

   CHECK_STATUS("xl_position_on_orbit",status)

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


/*----------xl_get_rotated_vectors & xl_get_rotation_angles----------------*/
/*-------------------------------------------------------------------------*/

START_CHECK("xl_get_rotated_vectors & xl_get_rotation_angles")

   /* Set input values */
   /* ---------------- */
  x_in[0]=1. ; x_in[1]=0. ; x_in[2]=0. ;
  y_in[0]=0. ; y_in[1]=1. ; y_in[2]=0. ;
  z_in[0]=0. ; z_in[1]=0. ; z_in[2]=1. ;

  ang_in[0]=-45. ; ang_in[1]=0. ; ang_in[2]=90.;
  

  status = xl_get_rotated_vectors(x_in,y_in,z_in,ang_in,x_out,y_out,z_out,local_err);
  CHECK_STATUS("xl_get_rotated_vectors",status)

  status = xl_get_rotation_angles (x_in,y_in,z_in,x_out,y_out,z_out,ang_out,local_err);
  CHECK_STATUS("xl_get_rotation_angles",status)

     
  printf(" ...\tchecking consistency:\n");
  CHECK_PAR( "roll angle:   ",ang_in[0],ang_out[0],1e-9)
  CHECK_PAR( "pitch angle:  ",ang_in[1],ang_out[1],1e-9)
  CHECK_PAR( "yaw angle:    ",ang_in[2],ang_out[2],1e-9)


END_CHECK   


/*****************************************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-19
 *
 ****************************************************************************************/


/*-----------------xl_cart_to_radec & xl_radec_to_cart---------------------*/
/*-------------------------------------------------------------------------*/

START_CHECK("xl_cart_to_radec & xl_radec_to_cart")
  
   /* Inputs for xl_cart_to_radec */
   pos[0] = -8.82*pc;
   pos[1] = -5.93*pc;
   pos[2] = 3.7*pc;

   vel[0] = -57.7E3;
   vel[1] = 31.5E3;
   vel[2] = -102.3E3;

   mode  = XL_CALC_POS_VEL, 
   cs_in = XL_BM1950;
	 
   status = xl_cart_to_radec(&model_id, &mode, &cs_in, pos, vel, 
			     &ra, &dec,
			     &mu_ra, &mu_dec, 
			     &rad_vel, &par, ierr);
														 
   CHECK_STATUS("xl_cart_to_radec Status == OK", status);
   
   /*Printing output for xl_cart_to_radec*/	 
   printf("\nOutputs:\n");
   printf("--------\n");
   printf("\tra =\t%f hours \n\tdec =\t%f degrees \n",
	    ra, dec);
	 
   printf("\n\tparallax=\t%g rad\n", par);
	 
   printf("\n\tVR=\t%f AU/century \t\t=\t%f Km/sec\n",
	  rad_vel*KM_PER_AU/(100*365.256363*24*3600), rad_vel);
   printf("\tMu_ra=\t%f rad/century \t=\t%f arcsec/year\n",
	  mu_ra/100*1296000/2/M_PI, mu_ra);
   printf("\tMu_dec=\t%f rad/century \t=\t%f arcsec/year\n",
	   mu_dec/100*1296000/2/M_PI, mu_dec);
   printf("---------------------\n");

   /* Input values for xl_radec_to_cart*/
   ra      =  3.733510e0;
   dec     =  3.350102e-1;
   mu_ra   = -5.301311e-4;
   mu_dec  = -9.685468e-4;
   rad_vel = -1.057037e2;
   par     =  4.308008e-7;

   status = xl_radec_to_cart(&model_id, &mode, &cs_in, &ra, &dec,
  	                     &mu_ra, &mu_dec, &rad_vel, &par, pos, vel,ierr);
   
   CHECK_STATUS("xl_radec_to_cart Status == OK", status);
	 
   /*Printing output for xl_radec_to_cart*/
   printf("\n---------------------\n");
   printf("Outputs:\n");
   printf("--------\n");
   printf("\n\tx= %lf m\t=\t%lf pc\n\ty= %lf m\t=\t%lf pc\n\tz= %lf m\t=\t%lf pc\n",
   pos[0], pos[0]/pc, pos[1], pos[1]/pc, pos[2], pos[2]/pc);
	 
   printf("\n\tvx= %lf m/s\n\tvy= %lf m/s\n\tvz= %lf m/s\n"\
          ,vel[0], vel[1], vel[2]);
   
   printf("---------------------\n");
   	 
	 
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

/*---------------- xl_euler_to_matrix & xl_matrix_to_euler ----------------*/
/*-------------------------------------------------------------------------*/

START_CHECK("xl_euler_to_matrix & xl_matrix_to_euler")

   /* Euler angles */
   euler_ang[0] = 45.;
   euler_ang[1] = 90.;
   euler_ang[2] = 20.;

   printf("   INPUTS.\n");
   printf("      Euler angles: Pitch = %.2f, Roll = %.2f, Yaw = %.2f\n", 
          euler_ang[0], euler_ang[1], euler_ang[2]);

   /* get matrix */
   status = xl_euler_to_matrix(euler_ang, rot_matrix, ierr);
   CHECK_STATUS("xl_euler_to_matrix status", status );				   
   
   printf("   OUTPUTS.\n");
   printf("      Rotation matrix: %.3f, %.3f, %.3f\n", rot_matrix[0][0], rot_matrix[0][1], rot_matrix[0][2]);
   printf("                       %.3f, %.3f, %.3f\n", rot_matrix[1][0], rot_matrix[1][1], rot_matrix[1][2]);
   printf("                       %.3f, %.3f, %.3f\n", rot_matrix[2][0], rot_matrix[2][1], rot_matrix[2][2]);

   /* get angles */
   status = xl_matrix_to_euler(rot_matrix, euler_ang, ierr);
   CHECK_STATUS("xl_matrix_to_euler status", status );

   printf("   OUTPUTS.\n");
   printf("      Euler angles: Pitch = %.2f, Roll = %.2f, Yaw = %.2f\n", 
          euler_ang[0], euler_ang[1], euler_ang[2]);	
	 
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

/*---------------- xl_star_catalog ----------------*/
/*-------------------------------------------------*/

START_CHECK("xl_star_catalog")
{
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

  printf("   INPUTS.\n");
  printf("       time = %.2f\n",time);;
  printf("       RA = %.6f, \tDec = %.5f\n", ra0, dec0);
  printf("       mu_ra = %.6f, \tmu_dec = %.6f\n", mu_ra0, mu_dec0);
  printf("       rad_vel = %.2f, \tparallax = %.6f\n", rad_vel0, par0);

  /* get star coordinates for the input time */
  status = xl_star_catalog(&model_id, &time_id, &time_ref, &time, &mode,
			   &catalog_in, &catalog_out, 
			   &ra0, &dec0, 
			   &mu_ra0, &mu_dec0, 
			   &rad_vel0, &par0,
			   /* output */
			   &ra, &dec, ierr);
  CHECK_STATUS("xl_star_catalog status", status );				   
   
  printf("   OUTPUTS.\n");
  printf("       RA = %.6f, \tDec = %.5f\n", ra, dec);

}
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

/*---------------- xl_ef_to_topocentric & xl_topocentric_to ef ----------------*/
/*-----------------------------------------------------------------------------*/

START_CHECK("xl_ef_to_topocentric & xl_topocentric_to ef")
{
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


  printf("   INPUTS.\n");
  printf("       Mode = %s\n", (mode ==XL_MODE_FLAG_LOCATION? "LOCATION" : "DIRECTION"));
  printf("       Deriv = %s\n", (deriv == XL_NO_DER? "No Derivatives" : "1st. Derivative"));
  printf("       Center of the Topocentric CS   = %.3lf,  %.3lf, %.3lf\n", pos[0], pos[1], pos[2]);
  printf("       Velocity of the Topocentric CS = %.3lf,  %.3lf, %.3lf\n", vel[0], vel[1], vel[2]);
  printf("       Azimuth, Elevation, Altitude = %.3lf,  %.3lf, %.3lf\n", azim, elev, range);
  printf("       Rates for Azimuth, Elevation, Altitude = %.3lf,  %.3lf, %.3lf\n", azim_d, elev_d, range_d);

  /* topocentric to EF CS  */
  status = xl_topocentric_to_ef(&model_id, &mode, &deriv, pos, vel, 
                                &azim, &elev, &range,
                                &azim_d, &elev_d, &range_d, 
                                ef_dir, ef_dir_d, ierr);
  CHECK_STATUS("xl_topocentric_to_ef", status );
   
  printf("   OUTPUTS.\n");
  printf("     EF position = %.3f, %.3f, %.3f\n", ef_dir[0], ef_dir[1], ef_dir[2]);
  printf("     EF velocity = %.3f, %.3f, %.3f\n", ef_dir_d[0], ef_dir_d[1], ef_dir_d[2]);

  /* EF to topocentric */
  status = xl_ef_to_topocentric(&model_id, &mode, &deriv, pos, vel,
                                ef_dir, ef_dir_d,
                                &azim, &elev, &range,
                                &azim_d, &elev_d, &range_d,                           
                                ierr);
  CHECK_STATUS("xl_ef_to_topocentric", status);

  printf("   OUTPUTS.\n");
  printf("     Topocentric Azimuth, Elevation, Range = %.3f, %.3f, %.3f\n", azim, elev, range);
  printf("     Rates for Topocentric Azimuth, Elevation, Range = %.3f, %.3f, %.3f\n", azim_d, elev_d, range_d);

}
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

/*---------------- xl_geoid_calc ----------------*/
/*-----------------------------------------------*/

START_CHECK("xl_geoid_calc")
{
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
  status = xl_geoid_calc(&geoid_in, &geoid_out, ierr);
  CHECK_STATUS("xl_geoid_calc", status );
   
  printf("   OUTPUTS.\n");
  printf("     Undulation = %lf\n", geoid_out.undulation);

}
END_CHECK

  /* Call xl_time_close function */
  /* --------------------------- */
  xl_time_close(&time_id, ierr);

  /* Close model */
  status = xl_model_close( &model_id, ierr );

/****************************************************************************************/

printf("\nEOCFI_LIB VALIDATION COMPLETED SUCCESSFULLY\n");

END_VALIDATION


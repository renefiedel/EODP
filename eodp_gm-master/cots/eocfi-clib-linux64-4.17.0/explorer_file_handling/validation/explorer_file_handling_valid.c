#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <explorer_file_handling.h>

/*****************************************************************************************
 *
 * Copyright    : DEIMOS, S.L.
 * Project      : EXPCFI
 *
 * Test level   : VALIDATION
 *
 * Module       : explorer_file_handling_valid.c
 * Purpose      : It runs validation tests of EXPLORER_FILE_HANDLING
 *
 * History     : +-----------------------------------------------------------------------------+
 *               | Version |  Date    |       Name        | Change                             |
 *               |-----------------------------------------------------------------------------|
 *               |    1.0  | 10/02/02 | DEIMOS Space S.L. | First version                      |
 *               +-----------------------------------------------------------------------------+
 *               |    2.0  | 29/11/02 | DEIMOS Space S.L. | Maintenance release                |
 *               |         |          |                   | New header functions               |
 *               +-----------------------------------------------------------------------------+
 *               |    2.1  | 13/05/03 | DEIMOS, S.L.      | Maintenance release                |
 *               |         |          |                   | MAC OS Version                     |
 *               |         |          |                   | New functions added:               |
 *               |         |          |                   |  + function to write a complete FH |
 *               |         |          |                   |  + new search function             |
 *               +-----------------------------------------------------------------------------+
 *               |    2.2  | 30/09/03 | DEIMOS Space S.L. | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.0  | 21/07/04 | DEIMOS, S.L.      | New interfaces                     |
 *               +-----------------------------------------------------------------------------+
 *               |    3.1  | 13/10/04 | DEIMOS, S.L.      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.2  | 15/11/04 | DEIMOS Space S.L. | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.3  | 11/07/05 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.4  | 18/11/05 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.5  | 26/05/06 | DEIMOS S.L.       | New features:                      |
 *               |         |          |                   |  + Thread safe library             |
 *               |         |          |                   |  + C99 compliant                   |
 *               |         |          |                   |  + Optimized libray                |
 *               |         |          |                   |  + 64-Bits library for MACOS,      |
 *               |         |          |                   |  + LINUX and SOLARIS               |
 *               +-----------------------------------------------------------------------------+
 *               |    3.6  | 24/11/06 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    3.7  | 13/07/07 | DEIMOS S.L.       | Maintenance release                |
 *               |         |          |                   | New features:                      |
 *               |         |          |                   |  + expcfi_check_libs               |
 *               |         |          |                   |  + library version for Mac OS X    |
 *               |         |          |                   |    on Intel (32 and 64 bits)       |
 *               +-----------------------------------------------------------------------------+
 *               |  3.7.2  | 31/07/08 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.0  | 19/01/09 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.1  | 07/05/10 | DEIMOS S.L.       | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.2  | 31/01/11 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.3  | 06/02/12 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.4  | 05/07/12 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.5  | 01/03/13 | DEIMOS S.L.U      | Maintenance release                |
 *               |         |          |                   | New features:                      |
 *               |         |          |                   |  + Longitude of XML fields not     |
 *               |         |          |                   |    limited to 512 characters.      |
 *               +-----------------------------------------------------------------------------+
 *               |    4.6  | 03/10/13 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.7  | 28/03/14 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.8  | 29/10/14 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |    4.9  | 23/04/15 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |  4.9.1  | 05/06/15 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.10  | 29/10/15 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.11  | 15/04/16 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.12  | 03/11/16 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.13  | 05/04/17 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.14  | 16/11/17 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.15  | 20/04/18 | DEIMOS S.L.U      | Maintenance release                |
 *               |         |          |                   | New features:                      |
 *               |         |          |                   |  + Refactored code                 |
 *               +-----------------------------------------------------------------------------+
 *               |   4.16  | 09/11/18 | DEIMOS S.L.U      | Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *               |   4.17  | 10/05/19 | DEIMOS Space S.L.U| Maintenance release                |
 *               +-----------------------------------------------------------------------------+
 *
 *****************************************************************************/
/* Macro definition */
/* ---------------- */

#define MAX_CONDITION                   1000    /* Maximum number of checks per test case */

#define START_VALIDATION                int main(int argc, char *argv[]){ \
                                        long ldi; \
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
#define CHECK_STATUS(msg,stat)          if (stat < XF_CFI_OK ) { \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        } \
                                        checks++;


#define CHECK_PAR(msg,p,p0,dp)          if(di=fabs(p-p0) <= (th=dp)){ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Threshold  : %g\n",th); \
                                        printf("\t\t Difference : %g\n",di); \
                                        checks++;

#define CHECK_INT_PAR(msg,p,p0)         if((ldi=labs(p-p0)) == 0){ \
                                          condition[checks] = XL_TRUE; \
                                          printf(" ...\t%s (XL_TRUE)\n",msg); \
                                        }else{ \
                                          condition[checks] = XL_FALSE; \
                                          printf(" ...\t%s (XL_FALSE)\n",msg); \
                                        } \
                                        printf("\t\t Difference : %ld\n",ldi); \
                                        checks++;

#define CHECK_VEC(msg,v,v0,im,iM,dp)    for(i=im;i<=iM;++i){ \
                                          CHECK_PAR(msg,v[i],v0[i],dp); \
                                        }

#define END_VALIDATION                  return(0); \
                                        }

#define XL_Boolean XF_Boolean
#define XL_FALSE XF_FALSE
#define XL_TRUE XF_TRUE

typedef enum
{

XL_FALSE = 0,      /* False variable */
XL_TRUE = 1        /* True variable */

} XL_Boolean;


/* Validation for EXPLORER_FILE_HANDLING */
/* ------------------------------------- */

START_VALIDATION

   /* General purpose variables */
   long		fd_1, fd_2;
#ifdef WINDOWS
   static char 	xmlFile [] = "..\\example\\data\\mpl_orb_sc.xml";
   static char	secondXmlFile [] = "..\\example\\data\\mpl_orb_sc.second.xml";
#else
   static char 	xmlFile [] = "../example/data/mpl_orb_sc.xml";
   static char	secondXmlFile [] = "../example/data/mpl_orb_sc.second.xml";
#endif
   long 	error, array_length;
	
   /* String reading variables */
   char /*string_value [ XF_MAX_VALUE_LENGTH ],
        string_array [ XF_MAX_ARRAY_SIZE ][ XF_MAX_VALUE_LENGTH ], ANR-368*/
		    element_node [ XF_MAX_XML_NODE_NAME_LENGTH ], 
		    attr_name [ XF_MAX_XML_NODE_NAME_LENGTH ];
   static char 	string_element[]  = "TAI_of_ANX";
   char *attr_value;
   char *string_value;
   char **string_array;
   
   /* Integer reading variables */
   static long 	expected_integer_value = 29;
   long 	integer_value, 
                integer_array [ XF_MAX_ARRAY_SIZE ], 
		integer_attr;
   static char 	integer_element[]  = "Cycle_Length";

   /* Double reading variables */
   static double 	expected_double_value = 23.6;
   double 		double_value, 
                	double_array [ XF_MAX_ARRAY_SIZE ], 
			double_attr;
   static char 		double_element[]  = "ANX_Longitude";

   /* Path reading variables */
   char 	path [ XF_MAX_PATH_LENGTH ];

   /* Search function variables */
   char found_path[XF_MAX_PATH_LENGTH],
        search_path[XF_MAX_PATH_LENGTH],
        search_value[XF_MAX_VALUE_LENGTH];

   /* Writing XML file variables */
   long		fd_3;
   static char	writtenXmlFile [] = "mpl_orb_sc.written.xml";

   /* Writing XML file header variables */
   long		fd_4;
   static char	writtenXmlFile_2 [] = "mpl_orb_sc.written_header.xml";
   long file_extension_type;
   char file_description[30],
     notes[30],
     mission[30],
     file_class[30],
     file_type[30],
     system[30],
     validity_start[30],
     validity_stop[30],
     creator[30],
     creator_version[30],
     creation_date[30];
   long file_version;
   long status;

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
   if (status != XF_CFI_OK)
   {
     printf("Library incompatibility.\n");
     CHECK_STATUS("Compatibility test (expcfi_check_libs)", status);
   }

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.1
 *
 ***********************************************************************/

/*--------- xf_tree_init_parser validation ------------*/
/*-----------------------------------------------------*/

START_CHECK("xf_tree_init_parser")

   fd_1 = xf_tree_init_parser ( xmlFile, &error );
   
   CHECK_STATUS("xf_tree_init_parser",error)
	
END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.2
 *
 ***********************************************************************/

/*--------- xf_tree_read_string_element_value validation ------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xf_tree_read_string_element_value")

  xf_tree_read_string_element_value ( &fd_1, string_element, &string_value, &error );
  CHECK_STATUS("xf_tree_read_string_element_value", error)
  if ( string_value != NULL )
  {
    free(string_value);
    string_value = NULL;
  }
   
END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.3
 *
 ***********************************************************************/

/*--------- xf_tree_read_string_element_array validation ------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xf_tree_read_string_element_array")
  string_array = (char **)calloc(XF_MAX_ARRAY_SIZE, sizeof(char *));
  xf_tree_read_string_element_array ( &fd_1, 
                                      string_element, 
                                      &string_array, 
                                      &array_length, 
                                      &error );

  CHECK_STATUS("xf_tree_read_string_element_array",error)
  for (i = 0; i < array_length; i++)
  {
    if (  string_array[i] != NULL)
    {
      free(string_array[i]);
      string_array[i] = NULL;
    }
  }
  if ( string_array != NULL )
  {
    free(string_array);
    string_array = NULL;
  }
END_CHECK

	
/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.4
 *
 ***********************************************************************/

/*--------- xf_tree_read_integer_element_value validation ------------*/
/*--------------------------------------------------------------------*/

START_CHECK("xf_tree_read_integer_element_value")

   /*Rewind to the top of the file */
   xf_tree_rewind ( &fd_1, &error );

   CHECK_STATUS("xf_tree_read_integer_element_value (calling xf_tree_rewind)",error)

   xf_tree_read_integer_element_value ( &fd_1, 
                                        integer_element, 
                                        &integer_value, 
                                        &error );
		
   CHECK_STATUS("xf_tree_read_integer_element_value",error)
   CHECK_INT_PAR("Checking integer value read",integer_value, expected_integer_value )

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.5
 *
 ***********************************************************************/

/*--------- xf_tree_read_integer_element_array validation ------------*/
/*--------------------------------------------------------------------*/

START_CHECK("xf_tree_read_integer_element_array")

   xf_tree_read_integer_element_array ( &fd_1, 
                                        integer_element, 
					integer_array, 
					&array_length, 
					&error );
		
   CHECK_STATUS("xf_tree_read_integer_element_array",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.6
 *
 ***********************************************************************/

/*--------- xf_tree_read_real_element_value validation ------------*/
/*-----------------------------------------------------------------*/

START_CHECK("xf_tree_read_real_element_value")

   /*Rewind to the top of the file */
   xf_tree_rewind ( &fd_1, &error );

   CHECK_STATUS("xf_tree_read_real_element_value (calling xf_tree_rewind)",error)

   xf_tree_read_real_element_value ( &fd_1, 
                                     double_element, 
				     &double_value, 
				     &error );
   CHECK_STATUS("xf_tree_read_real_element_value",error)
   CHECK_PAR("Checking real value read",double_value, expected_double_value, 0.)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.7
 *
 ***********************************************************************/

/*--------- xf_tree_read_real_element_array validation ------------*/
/*-----------------------------------------------------------------*/

START_CHECK("xf_tree_read_real_element_array")

   xf_tree_read_real_element_array ( &fd_1, 
                                     double_element, 
				     double_array, 
				     &array_length, 
				     &error );

   CHECK_STATUS("xf_tree_read_real_element_array",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.8
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_string_node_value validation ------------*/
/*---------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_string_node_value")

  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[1]/Time_of_ANX/UTC_of_ANX" );
  xf_tree_path_read_string_node_value( &fd_1, 
                                       path, 
                                       &string_value, 
                                       &error );
		
  CHECK_STATUS("xf_tree_path_read_string_node_value",error)
  if ( string_value != NULL )
  {
    free(string_value);
    string_value = NULL;
  }
  
END_CHECK
   

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.9
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_integer_node_value validation ------------*/
/*----------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_integer_node_value")

   strcpy ( path, "../../../Orbit_Change[2]/Orbit/Absolute_Orbit" );
   xf_tree_path_read_integer_node_value ( &fd_1, 
                                          path, 
					  &integer_value, 
					  &error );
		
   CHECK_STATUS("xf_tree_path_read_integer_node_value",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.10
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_real_node_value validation ------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_real_node_value")

   strcpy ( path, "../../../Orbit_Change[2]/Cycle/ANX_Longitude" );
   xf_tree_path_read_real_node_value ( &fd_1, 
                                       path, 
				       &double_value, 
				       &error );
		
   CHECK_STATUS("xf_tree_path_read_real_node_value",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.11
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_string_node_value validation ------------*/
/*---------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_string_node_value")

  strcpy ( path, "../Repeat_Cycle/@unit" );
  xf_tree_path_read_string_node_value( &fd_1, 
                                       path, 
					                             &string_value, 
					                             &error );
		
  CHECK_STATUS("xf_tree_path_read_string_node_value",error)
  if ( string_value != NULL )
  {
    free(string_value);
    string_value = NULL;
  }
  
END_CHECK



/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.12
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_string_node_array validation ------------*/
/*---------------------------------------------------------------------*/

START_CHECK("xf_tree_read_string_element_array")

  string_array = (char **)calloc(XF_MAX_ARRAY_SIZE, sizeof(char *));
  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Time_of_ANX/UTC_of_ANX" );
  xf_tree_path_read_string_node_array( &fd_1, 
                                       path, 
				                               &string_array, 
				                               &array_length, 
				                               &error );

  CHECK_STATUS("xf_tree_path_read_string_node_array",error)
   
  for (i = 0; i < array_length; i++)
  {
    if (string_array[i] != NULL)
    {
      free(string_array[i]);
      string_array[i] = NULL;
    }
  }
  if (string_array != NULL)
  {
    free(string_array);
    string_array = NULL;
  }
END_CHECK



/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.13
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_integer_node_array validation ------------*/
/*----------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_integer_node_array")

   strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Orbit/Absolute_Orbit" );
   xf_tree_path_read_integer_node_array ( &fd_1, 
                                          path, 
				          integer_array, 
				          &array_length, 
				          &error );

   CHECK_STATUS("xf_tree_path_read_integer_node_array",error)
   
END_CHECK



/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.14
 *
 ***********************************************************************/

/*--------- xf_tree_path_read_real_node_array validation ------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xf_tree_path_read_real_node_array")

   strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Cycle/MLST_Drift" );
   xf_tree_path_read_real_node_array ( &fd_1, 
                                       path, 
				       double_array, 
				       &array_length, 
				       &error );

   CHECK_STATUS("xf_tree_path_read_real_node_array",error)
   
END_CHECK



/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.15
 *
 ***********************************************************************/

/*--------- xf_tree_rewind validation ------------*/
/*------------------------------------------------*/

START_CHECK("xf_tree_rewind")

   xf_tree_rewind ( &fd_1, &error );

   CHECK_STATUS("xf_tree_rewind",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.16
 *
 ***********************************************************************/

/*--------- xf_tree_go_to_element_node validation ------------*/
/*------------------------------------------------------------*/

START_CHECK("xf_tree_go_to_element_node")

   strcpy ( element_node, "List_of_Orbit_Changes" );
   xf_tree_go_to_element_node ( &fd_1, (char *)element_node, &error );

   CHECK_STATUS("xf_tree_go_to_element_node",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.17
 *
 ***********************************************************************/

/*--------- xf_tree_read_integer_attribute validation ------------*/
/*----------------------------------------------------------------*/

START_CHECK("xf_tree_read_integer_attribute")

   strcpy ( attr_name, "count" );
   xf_tree_read_integer_attribute ( &fd_1, NULL, (char *)attr_name, &integer_attr, &error );

   CHECK_STATUS("xf_tree_read_integer_attribute",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.18
 *
 ***********************************************************************/

/*--------- xf_tree_read_string_attribute validation ------------*/
/*---------------------------------------------------------------*/

START_CHECK("xf_tree_read_string_attribute")

  strcpy( element_node, "Repeat_Cycle" );
  xf_tree_go_to_element_node ( &fd_1, (char *)element_node, &error );

  CHECK_STATUS("xf_tree_go_to_element_node",error)

  strcpy ( attr_name, "unit" );
  xf_tree_read_string_attribute ( &fd_1, NULL, (char *)attr_name, &attr_value, &error );
  CHECK_STATUS("xf_tree_read_string_attribute",error)
  if ( attr_value != NULL )
  {
    free(attr_value);
    attr_value = NULL;
  }
  
END_CHECK



/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.19
 *
 ***********************************************************************/

/*--------- xf_tree_read_real_attribute validation ------------*/
/*-------------------------------------------------------------*/

   /* Deleted, no sample file */


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.20
 *
 ***********************************************************************/

/*--------- xf_tree_go_to_path_node validation ------------*/
/*-------------------------------------------------------------*/

START_CHECK("xf_tree_go_to_path_node")

   strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[1]/Cycle/MLST_Drift" );
   xf_tree_go_to_path_node ( &fd_1, path, &error );

   CHECK_STATUS("xf_tree_go_to_path_node",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.21
 *
 ***********************************************************************/

/*--------- xf_tree_get_path validation ------------*/
/*--------------------------------------------------*/

START_CHECK("xf_tree_get_path")

   xf_tree_get_path ( &fd_1, path, &error );

   CHECK_STATUS("xf_tree_get_path",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.22
 *
 ***********************************************************************/

/*--------- xf_tree_find_string_value_element validation ------------*/
/*-------------------------------------------------------------------*/

START_CHECK("xf_tree_find_string_value_element")

   xf_tree_rewind(&fd_1, &error);
   strcpy(search_path, "Absolute_Orbit");
   strcpy(search_value, "2");

   xf_tree_find_string_value_element(&fd_1, search_path, search_value,
                                     found_path, &error);

   CHECK_STATUS("xf_tree_find_string_value_element",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-1.23
 *
 ***********************************************************************/

/*--------- xf_tree_find_string_value_path validation ------------*/
/*----------------------------------------------------------------*/

START_CHECK("xf_tree_find_string_value_path")

   strcpy(search_path,
          "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Orbit/Absolute_Orbit");
   strcpy(search_value, "1");

   xf_tree_find_string_value_path(&fd_1, search_path, search_value,
                                  found_path, &error);

   CHECK_STATUS("xf_tree_find_string_value_path",error)

END_CHECK

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-2.1
 *
 ***********************************************************************/

/*--------- second call to xf_tree_init_parser validation ------------*/
/*--------------------------------------------------------------------*/

START_CHECK("xf_tree_init_parser (second call)")

   fd_2 = xf_tree_init_parser ( secondXmlFile, &error );
   
   CHECK_STATUS("xf_tree_init_parser",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-2.2
 *
 ***********************************************************************/

/*--------- xf_tree_cleanup_parser validation ------------*/
/*--------------------------------------------------------*/

START_CHECK("xf_tree_cleanup_parser")

   xf_tree_cleanup_parser ( &fd_2, &error );

   CHECK_STATUS("xf_tree_cleanup_parser",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-3.1
 *
 ***********************************************************************/

/*--------- xf_tree_create validation ------------*/
/*------------------------------------------------*/

START_CHECK("xf_tree_create")

   fd_3 = xf_tree_create( &error );

   CHECK_STATUS("xf_tree_create",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-3.2
 *
 ***********************************************************************/

/*--------- xf_tree_create_root validation ------------*/
/*-----------------------------------------------------*/

START_CHECK("xf_tree_create_root")

   xf_tree_create_root ( &fd_3, "Earth_Explorer_File", &error );

   CHECK_STATUS("xf_tree_create_root",error)

END_CHECK

   /* In the next block, errors are not checked for the sake of simplicity */

/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-3.3
 *
 ***********************************************************************/

/*--------- explorer file handling writing validation ------------*/
/*----------------------------------------------------------------*/

START_CHECK("explorer file handling writing (please inspect the file mpl_orb_sc.written.xml)")

   /* Creating a child after another */
   xf_tree_add_child ( &fd_3, ".", "Data_Block", &error );
   xf_tree_add_child ( &fd_3, ".", "List_of_Orbit_Changes", &error );
   xf_tree_add_child ( &fd_3, ".", "Orbit_Change", &error );
   xf_tree_add_child ( &fd_3, ".", "Orbit", &error );
   xf_tree_add_child ( &fd_3, ".", "Absolute_Orbit", &error );
   
   /* Adding a value to the current node */
   xf_tree_set_string_node_value ( &fd_3, ".", "10", "%s", &error );
   
   /* Adding a sibling next to the current node, and then its value */
   xf_tree_add_next_sibling ( &fd_3, ".", "Relative_Orbit", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "15", "%s", &error );
   
   xf_tree_add_child ( &fd_3, "..", "Phase_Number", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "1", "%s", &error );
   
   /* Adding a sibling before the current node, and then its value */
   xf_tree_add_previous_sibling ( &fd_3, ".", "Cycle_Number", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "1", "%s", &error );
   
   /* Another child, witl a different path */
   xf_tree_add_child ( &fd_3, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[1]",
               "Cycle", &error );
	       
   xf_tree_add_child ( &fd_3, ".", "Repeat_Cycle", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "3", "%s", &error );
   xf_tree_add_attribute ( &fd_3, ".", "units", &error );
   xf_tree_set_string_node_value ( &fd_3, "@units", "day", "%s", &error );
   xf_tree_add_next_sibling ( &fd_3, ".", "Cycle_Length", &error );
   
   /* Adding an attribute to the current node, and then its value */
   xf_tree_add_attribute ( &fd_3, ".", "unit", &error );
   xf_tree_set_string_node_value ( &fd_3, "@unit", "orbit", "%s", &error );
   
   xf_tree_set_string_node_value ( &fd_3, ".", "43", "%s", &error );
   xf_tree_add_next_sibling ( &fd_3, ".", "ANX_Longitude", &error );
   /* Adding a value as double. Please, pay attention to the format */
   double_value = 0.1335;
   xf_tree_set_real_node_value ( &fd_3, ".", &double_value, "%06.4lf", &error );
   
   xf_tree_add_attribute ( &fd_3, ".", "unit", &error );
   xf_tree_set_string_node_value ( &fd_3, "@unit", "deg", "%s", &error );
   
   /* Removing an attribute, and then the current node */
   xf_tree_remove_node ( &fd_3, "@unit", &error );
   xf_tree_remove_node ( &fd_3, "../Repeat_Cycle", &error );

 
   xf_tree_add_previous_sibling ( &fd_3, "Cycle_Length", "Repeat_Cycle", &error );

   /* Adding a value as long. Please, pay attention to the format */
   integer_value = 5L;
   xf_tree_set_integer_node_value ( &fd_3, ".", &integer_value, "%ld", &error );
   
   xf_tree_add_attribute ( &fd_3, ".", "unit", &error );
   xf_tree_set_string_node_value ( &fd_3, "@unit", "day", "%s", &error );
   xf_tree_set_string_node_value ( &fd_3, "../Cycle_Length", "57", "%s", &error );
   xf_tree_add_child ( &fd_3, "..", "MLST", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "22:00:00.45545", "%s", &error );
   xf_tree_add_next_sibling ( &fd_3, ".", "MLST_Drift", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "011.010101", "%s", &error );
   xf_tree_add_child ( &fd_3, "../..", "Time_of_ANX", &error );
   xf_tree_add_child ( &fd_3, ".", "TAI_of_ANX", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "TAI=2002-03-01T03:01:09.01345", "%s", &error );
   xf_tree_add_next_sibling ( &fd_3, ".", "UTC_of_ANX", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "UTC=2002-03-01T03:01:10.01345", "%s", &error );
   xf_tree_add_next_sibling ( &fd_3, ".", "UT1_of_ANX", &error );
   xf_tree_set_string_node_value ( &fd_3, ".", "UT1=2002-03-01T03:01:11.01345", "%s", &error );

   xf_tree_write ( &fd_3, writtenXmlFile, &error );

   CHECK_STATUS("explorer file handling writing",error)

END_CHECK


/***********************************************************************
 *
 * ---------
 * Test case
 * ---------
 *
 * Test number          : VT-4.1
 *
 ***********************************************************************/

/*--------- xf_tree_set_fixed_header_items validation ------------*/
/*-----------------------------------------------------*/

START_CHECK("xf_tree_set_fixed_header_items")

   file_extension_type = XF_HEADER_FORMAT_EEF;
   strcpy(file_description, "header_proof");
   strcpy(notes, "no notes");
   strcpy(mission, "example_and_validation");
   strcpy(file_class, "file class");
   strcpy(file_type, "file type");
   strcpy(validity_start, "xx-xxx-xxxx xx:xx:xx");
   strcpy(validity_stop, "xx-xxx-xxxx xx:xx:xx");
   strcpy(system, "system");
   strcpy(creator, "creator");
   strcpy(creator_version, "creator_version");
   strcpy(creation_date, "xx-xxx-xxxx xx:xx:xx");
   file_version = 0;

   fd_4 = xf_tree_create( &error );

   xf_tree_create_root ( &fd_4, "Earth_Explorer_File", &error );

   xf_tree_create_header (&fd_4, &file_extension_type, &error);

   xf_tree_set_fixed_header_items ( &fd_4, writtenXmlFile_2, file_description, notes,
				    mission, file_class, file_type, validity_start,
				    validity_stop, &file_version, system, creator,
				    creator_version, creation_date, &error);

   CHECK_STATUS("xf_tree_set_fixed_header_items",error);

   xf_tree_write ( &fd_4, writtenXmlFile_2, &error );

   CHECK_STATUS("explorer file handling writing",error);

END_CHECK


   /* Cleaning. It does not return any error */
   xf_tree_cleanup_all_parser ();

printf("\nEOCFI_FILE_HANDLING VALIDATION COMPLETED SUCCESSFULLY\n");

END_VALIDATION

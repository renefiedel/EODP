 /******************************************************************************
 *
 * Project     : EXPCFI
 * Copyright   : DEIMOS Space S.L.
 *
 * Module      : explorer_file_handling_c.c
 *
 * Functions   : main program (EXPLORER_FILE_HANDLING example) to call:
 *                    - xf_tree_init_parser
 *                    - xf_tree_read_string_element_value
 *                    - xf_tree_read_string_element_array
 *                    - xf_tree_read_integer_element_value
 *                    - xf_tree_read_integer_element_array
 *                    - xf_tree_read_real_element_value
 *                    - xf_tree_read_real_element_array
 *                    - xf_tree_path_read_string_node_value
 *                    - xf_tree_path_read_integer_node_value
 *                    - xf_tree_path_read_real_node_value
 *                    - xf_tree_path_read_string_node_array
 *                    - xf_tree_path_read_integer_node_array
 *                    - xf_tree_path_read_real_node_array
 *                    - xf_tree_rewind
 *                    - xf_tree_go_to_element_node
 *                    - xf_tree_go_to_path_node
 *                    - xf_tree_get_path
 *                    - xf_tree_read_string_attribute
 *                    - xf_tree_read_integer_attribute
 *                    - xf_tree_read_real_attribute
 *                    - xf_tree_create
 *                    - xf_tree_create_root
 *                    - xf_tree_add_child
 *                    - xf_tree_add_next_sibling
 *                    - xf_tree_add_previous_sibling
 *                    - xf_tree_add_attribute
 *                    - xf_tree_remove_node
 *                    - xf_tree_set_string_node_value
 *                    - xf_tree_set_integer_node_value
 *                    - xf_tree_set_real_node_value
 *		                - xf_tree_create_header
 *                    - xf_tree_set_fixed_header_item
 *                    - xf_tree_get_fixed_header_item
 *                    - xf_tree_get_fixed_header_items
 *                    - xf_create_filename
 *                    - xf_read_filename_items
 *                    - xf_tree_write
 *                    - xf_tree_cleanup_parser
 *                    - xf_tree_cleanup_all_parser
 *
 * Purpose     : Example program to show the way to call the previous functions.
 *
 * Reference   : None
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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include <explorer_file_handling.h>


/* Auxiliary function for closing in case of error */
/* ----------------------------------------------- */

void closeup (long error_code )
{
   char 	error_message [ XF_MAX_ERROR_MSG_LENGTH ];
   
   xf_basic_error_msg ( error_code, error_message );
   printf ( "%s\n", error_message );
   /* Cleaning */
   xf_tree_cleanup_all_parser ();
   exit ( EXIT_FAILURE );
   
}

/* Main program */
/* ------------ */

int main(int argc, char **argv)
{
  /* General purpose variables */
  long		fd_1, fd_2;
  static char 	xmlFile [] = "../data/mpl_orb_sc.xml";
  static char	secondXmlFile [] = "../data/mpl_orb_sc.second.xml";
  char 	error_message [ XF_MAX_ERROR_MSG_LENGTH ];
  int  	i;
  long 	error, array_length, duration;
  clock_t 	start, stop;

  /* String reading variables */
  char *string_value;
  char **string_array;
  char *attr_value;
  char *value;
	char element_node [ XF_MAX_XML_NODE_NAME_LENGTH ], 
	     attr_name [ XF_MAX_XML_NODE_NAME_LENGTH ];
  static char 	string_element[]  = "TAI_of_ANX";

  /* Integer reading variables */
  long 	integer_value, 
               integer_array [ XF_MAX_ARRAY_SIZE ], 
	 integer_attr;
  static char 	integer_element[]  = "Cycle_Length";

  /* Double reading variables */
  double 	double_value, 
               double_array [ XF_MAX_ARRAY_SIZE ], 
	 double_attr;
  static char 	double_element[]  = "ANX_Longitude";

  /* Path reading variables */
  char 	path [ XF_MAX_PATH_LENGTH ];

  /* Search function variables */
  char found_path[XF_MAX_PATH_LENGTH],
       search_path[XF_MAX_PATH_LENGTH],
       search_value[XF_MAX_VALUE_LENGTH];

  /* Writing XML file variables */
  long		fd_3;
  static char	writtenXmlFile [] = "mpl_orb_sc.written.xml";

  /* Reading Fixed Header values variables */
  static char 	item_id [XF_MAX_VALUE_LENGTH] = "Notes";
  static char 	item_value [XF_MAX_VALUE_LENGTH] = "This is a example of adding value to a Header element";
  long         header_type;   
  
  char 	*file_name_all;
  char 	*file_description_all;
  char 	*notes_all;
  char 	*mission_all;
  char 	*file_class_all;
  char 	*file_type_all;
  char 	*validity_start_all;
  char 	*validity_stop_all;
  long 	*file_version_all;
  char 	*system_all;
  char 	*creator_all;
  char 	*creator_version_all;
  char 	*creation_date_all;

  /* write filename variables */
  static char 	   filename [XF_MAX_FILENAME_LENGTH];
  long            satellite_id	                          = XF_SAT_CRYOSAT;
  static char     file_class [5] 	                  = "CCCC";
  static char     file_type [XF_MAX_VALUE_LENGTH]        = "TTTTTTTTTT";
  static char     instance_id [XF_MAX_VALUE_LENGTH]      = "yyyymmddThhmmss_YYYYMMDDTHHMMSS_vvvv";   
  long            fet                                    = XF_HEADER_FORMAT_DBL; 

  /* read filename variables */
  long		            satellite_id_r;
  static char 			file_class_r [5];
  static char 			file_type_r [11];
  static char 			instance_id_r [43];  

  /* Writing XML file header variables */
  long		fd_4;
  static char	writtenXmlFile_2 [] = "mpl_orb_sc.written_header.xml";
  long file_extension_type,
       file_version;

  /* Initialization */
  /* -------------- */
  file_version=0;
  file_version_all= &file_version;

  printf ( "\n*** Loading the file %s ***\n\n", xmlFile );

  start = clock();
  fd_1 = xf_tree_init_parser ( xmlFile, &error );
  stop = clock();

  if ( error < XF_CFI_OK )
  {
     printf("\nError parsing file %s\n", xmlFile);
     closeup (error);
  }

  duration = ((long)stop-(long)start)/1000;
  printf("\nFile %s loaded OK\n", xmlFile);


  /* Reading first element as string  */
  /* -------------------------------- */
  printf ( "\n*** Reading element as string ***\n\n" );

  xf_tree_read_string_element_value ( &fd_1, string_element, &string_value, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading element as string\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %s\n", string_element, string_value );
  
  if ( string_value != NULL )
  {
    free(string_value);
    string_value = NULL;
  }

  /* Reading all elements as strings */
  /* ------------------------------- */
  printf ( "\n*** Reading all the %s elements as strings ***\n\n", string_element );
  string_array = (char **)calloc(XF_MAX_ARRAY_SIZE, sizeof(char *));
  xf_tree_read_string_element_array ( &fd_1, 
                                      string_element, 
                                      &string_array, 
                                      &array_length, 
                                      &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading all the %s elements as strings\n", string_element );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Element: %s\n", string_element );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %d ]: %s\n", i, string_array [ i ] );
     }
  }
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

  /* Reading element as integer  */
  /* --------------------------- */
  printf ( "\n*** Reading element as integer ***\n\n" );

  /*Rewind to the top of the file */
  xf_tree_rewind ( &fd_1, &error );
  if ( error < XF_CFI_OK )
  {
     printf("\nError rewinding\n" );
     closeup (error);
  }

  xf_tree_read_integer_element_value ( &fd_1, 
                                       integer_element, 
				 &integer_value, 
				 &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading element as integer\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %ld\n", integer_element, integer_value );


  /* Reading all elements as integers */
  /* -------------------------------- */
  printf ( "\n*** Reading all the %s elements as integers ***\n\n", integer_element );

  xf_tree_read_integer_element_array ( &fd_1, 
                                       integer_element, 
				 integer_array, 
				 &array_length, 
				 &error );
  if ( error < XF_CFI_OK )
  {
     printf("\nError reading all the %s elements as integers\n", integer_element );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Element: %s\n", integer_element );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %ld ]: %ld\n", i, integer_array [ i ] );
     }
  }


  /* Reading element as double  */
  /* -------------------------- */
  printf ( "\n*** Reading element as double ***\n\n" );

  /*Rewind to the top of the file */
  xf_tree_rewind ( &fd_1, &error );
  if ( error < XF_CFI_OK )
  {
     printf("\nError rewinding\n" );
     closeup (error);
  }

  xf_tree_read_real_element_value ( &fd_1, 
                                    double_element, 
				    &double_value, 
				    &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading element as double\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %f\n", double_element, double_value );


  /* Reading all elements as doubles */
  /* ------------------------------- */
  printf ( "\n*** Reading all the %s elements as doubles ***\n\n", double_element );

  xf_tree_read_real_element_array ( &fd_1, 
                                    double_element, 
				    double_array, 
				    &array_length, 
				    &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading all the %s elements as doubles\n", double_element );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Element: %s\n", double_element );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %d ]: %f\n", i, double_array [ i ] );
     }
  }


  /* Reading an element as string given a path  */
  /* ------------------------------------------ */
  printf ( "\n*** Reading an element as string given a path ***\n\n" );

  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[1]/Time_of_ANX/UTC_of_ANX" );
  xf_tree_path_read_string_node_value ( &fd_1, 
                                        path, 
                                        &string_value, 
                                        &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an element as string given a path\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %s\n", path, string_value );
  
  if ( string_value != NULL )
  {
    free (string_value);
    string_value = NULL;
  }


  /* Reading an element as integer given a path  */
  /* ---------------------------------------------------- */
  printf ( "\n*** Reading an element as integer given a path ***\n\n" );

  strcpy ( path, "../../../Orbit_Change[2]/Orbit/Absolute_Orbit" );
  xf_tree_path_read_integer_node_value ( &fd_1, 
                                         path, 
					 &integer_value, 
					 &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an element as integer given a path\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %ld\n", path, integer_value );


  /* Reading a double element given a path  */
  /* -------------------------------------- */
  printf ( "\n*** Reading a double element given a path ***\n\n" );

  strcpy ( path, "../../../Orbit_Change[2]/Cycle/ANX_Longitude" );
  xf_tree_path_read_real_node_value ( &fd_1, 
                                      path, 
				                              &double_value, 
				                              &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading a double element given a path\n" );
     closeup (error);
  }
  else
     printf ( "Element: %s *** Value: %g\n", path, double_value );



  /* Reading the attribute of an element given a path  */
  /* ------------------------------------------------- */
  printf ( "\n*** Reading the attribute of an element given a path ***\n\n" );

  strcpy ( path, "../Repeat_Cycle/@unit" );
  xf_tree_path_read_string_node_value ( &fd_1, 
                                        path, 
                                        &string_value, 
                                        &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an attribute given a path\n" );
     closeup (error);
  }
  else
     printf ( "Attribute: %s *** Value: %s\n", path, string_value );
  
  if ( string_value != NULL )
  {
    free (string_value);
    string_value = NULL;
  }


  /* Reading an array of strings given a path  */
  /* ----------------------------------------- */
  printf ( "\n*** Reading an array of strings given a path ***\n\n" );
  string_array = (char **)calloc(XF_MAX_ARRAY_SIZE, sizeof(char *));
  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Time_of_ANX/UTC_of_ANX" );
  xf_tree_path_read_string_node_array ( &fd_1, 
                                        path, 
				                                &string_array, 
				                                &array_length, 
				                                &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an array of strings given the path: \n", path );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Path: %s\n", path );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %d ]: %s\n", i, string_array [ i ] );
     }
  }
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
  
  
  /* Reading an array of integers given a path  */
  /* ------------------------------------------ */
  printf ( "\n*** Reading an array of integers given a path ***\n\n" );

  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Orbit/Absolute_Orbit" );
  xf_tree_path_read_integer_node_array ( &fd_1, 
                                         path, 
				         integer_array, 
				         &array_length, 
				         &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an array of integers given the path: \n", path );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Path: %s\n", path );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %d ]: %ld\n", i, integer_array [ i ] );
     }
  }


  /* Reading an array of doubles given a path  */
  /* ----------------------------------------- */
  printf ( "\n*** Reading an array of doubles given a path ***\n\n" );

  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Cycle/MLST_Drift" );
  xf_tree_path_read_real_node_array ( &fd_1, 
                                      path, 
				      double_array, 
				      &array_length, 
				      &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an array of doubles given the path: \n", path );
     closeup (error);
  }
  else
  {
     /* Look for warnings */
     if ( error > XF_CFI_OK )
     {
        xf_basic_error_msg ( error, error_message );
        printf ( "WARNING: %s\n", error_message );
     }
     printf ( "Path: %s\n", path );
     for ( i =  0; i < array_length; i++ )
     {
        printf ( " Value [ %d ]: %lf\n", i, double_array [ i ] );
     }
  }

  /* Rewinding  */
  /* ---------- */
  printf ( "\n*** Rewinding ***\n\n" );

  xf_tree_rewind ( &fd_1, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError rewinding\n" );
     closeup (error);
  }


  /* Moving to an element  */
  /* --------------------- */
  strcpy ( element_node, "List_of_Orbit_Changes" );
  printf ( "\n*** Moving to the element %s ***\n\n", element_node );

  xf_tree_go_to_element_node ( &fd_1, (char *)element_node, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError navigating\n" );
     closeup (error);
  }

  /* Reading an integer attribute from the current element  */
  /* ------------------------------------------------------ */
  strcpy ( attr_name, "count" );
  printf ( "\n*** Reading the integer attribute %s from the current element %s ***\n\n", attr_name, element_node );

  xf_tree_read_integer_attribute ( &fd_1, NULL, (char *)attr_name, &integer_attr, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading an integer attribute\n" );
     closeup (error);
  }
  else
     printf ( "Attribute: %s *** Value: %ld\n", attr_name, integer_attr );


  /* Moving to an element  */
  /* --------------------- */
  strcpy ( element_node, "Repeat_Cycle" );
  printf ( "\n*** Moving to the element %s ***\n\n", element_node );

  xf_tree_go_to_element_node ( &fd_1, (char *)element_node, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError navigating\n" );
     closeup (error);
  }


  /* Reading a string attribute from the current element  */
  /* ---------------------------------------------------- */
  strcpy ( attr_name, "unit" );
  printf ( "\n*** Reading the string attribute %s from the current element %s ***\n\n", attr_name, element_node );

  xf_tree_read_string_attribute ( &fd_1, NULL, (char *)attr_name, &attr_value, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError reading a string attribute\n" );
     closeup (error);
  }
  else
     printf ( "Attribute: %s *** Value: %s\n", attr_name, attr_value );
 
  if ( attr_value != NULL )
  {
    free(attr_value);
    attr_value = NULL;
  }


  /* Moving to a path node  */
  /* ---------------------- */
  strcpy ( path, "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[1]/Cycle/MLST_Drift" );
  printf ( "\n*** Moving to the node %s ***\n\n", path );

  xf_tree_go_to_path_node ( &fd_1, path, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError moving to path node\n" );
     closeup (error);
  }


  /* Getting the current node path and comparing  */
  /* ------------------------------------------- */
  printf ( "\n*** Getting the current node path ***\n\n", path );

  xf_tree_get_path ( &fd_1, path, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError getting path node\n" );
     closeup (error);
  }
  else
     printf ( "Path: %s\n", path );

  /* SEARCH FUNCTIONS */
  /* ---------------- */

  printf("\n*** Search Functions ***\n\n");
  xf_tree_rewind(&fd_1, &error);

  printf("\t*** Search using the element name:");
  strcpy(search_path, "Absolute_Orbit");
  strcpy(search_value, "2");

  xf_tree_find_string_value_element(&fd_1, search_path, search_value, found_path, &error);

  printf("\n\tSearch element %s with value = %s\n", search_path, search_value);
  printf("\n\tFound path = %s\n\n", found_path);

  printf("\t*** Search using an XPath expression:");
  strcpy(search_path,
         "/Earth_Explorer_File/Data_Block/List_of_Orbit_Changes/Orbit_Change[*]/Orbit/Absolute_Orbit");
  strcpy(search_value, "1");

  xf_tree_find_string_value_path(&fd_1, search_path, search_value, found_path, &error);

  printf("\n\tSearch path %s with value = %s\n", search_path, search_value);
  printf("\n\tFound path = %s\n", found_path);


  /* Loading another file */
  /* -------------------- */
  printf ( "\n*** Loading the file %s ***\n\n", secondXmlFile );

  start = clock();
  fd_2 = xf_tree_init_parser ( secondXmlFile, &error );
  stop = clock();

  if ( error < XF_CFI_OK )
  {
     printf("\nError parsing file %s\n", secondXmlFile);
     closeup (error);
  }

  duration = ((long)stop-(long)start)/1000;
  printf("\nFile %s loaded OK\n", secondXmlFile);

  /* Any operation with the explorer_file_handling routines can be performed 
     in this second file, alternating desired with operations on other files */

  /* Freeing the second file */
  printf ( "\n*** Freeing the file %s ***\n\n", secondXmlFile );

  xf_tree_cleanup_parser ( &fd_2, &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError freeing file %s\n", secondXmlFile);
     closeup (error);
  }


  /* Creating an XML file */
  printf ( "\n*** Creating the XML file %s ***\n\n", writtenXmlFile );

  fd_3 = xf_tree_create( &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError creating XML document\n" );
     closeup (error);
  }

  xf_tree_create_root ( &fd_3, "Earth_Explorer_File", &error );

  if ( error < XF_CFI_OK )
  {
     printf("\nError creating root in XML document\n" );
     closeup (error);
  }
  /* In the next block, errors are not checked for the sake of simplicity.
     However, the user must do it in order to have a robust code */

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

  /*********************************************************** 
  *	Adding Header and values for the Header elements 
  ************************************************************/

  /* adding Header */
  header_type =  XF_HEADER_FORMAT_EEF;

  printf ( "\n	... Creating Header ...\n\n"); 
  xf_tree_create_header ( &fd_3, &header_type, &error );   
  if ( error < XF_CFI_OK )
  {
    printf("\n	... Error creating header ...\n\n" );      	      	
    closeup (error);
  } 		

  /* adding value for Header elemnts */
  printf ( "\n	... Setting fixed-header element value ...\n\n"); 
  xf_tree_set_fixed_header_item ( &fd_3, item_id, item_value, &error ); 
  if ( error < XF_CFI_OK )
  {
    printf("\n	... Error setting fixed-header item ...\n\n" );      	      	
    closeup (error);
  }

  fet = XF_HEADER_FORMAT_NONE;

  /* generating filename */ 
  printf ( "\n	... Writing filename ...\n\n");
  xf_create_filename ( (long * )&satellite_id, file_class, file_type, instance_id, &fet, filename, &error); 
  if ( error < XF_CFI_OK )
  {
    printf("\nError writting filename\n" );      	      	
    closeup (error);
  }
  else
  {
    printf("\n ... filename ---> %s\n", &filename );	
  }

  xf_tree_set_fixed_header_item ( &fd_3, "File_Name", filename, &error ); 
  if ( error < XF_CFI_OK )
  {
    printf("\n	... Error setting fixed-header item ...\n\n" );      	      	
    closeup (error);
  }

  /* reading a Header value */  
  printf("\n ... Reading an item in the Fixed header ...\n\n", item_value);	
  strcpy(item_id,"Notes");

  xf_tree_get_fixed_header_item ( &fd_3, item_id, &value, &error );
  if ( error < XF_CFI_OK )
  {
    printf("\nError reading fixed-header item\n" );      	      	
    closeup (error);
  }
  else
  {
    printf("\n ... value is: ---> %s\n", value);	
  }
  if ( value != NULL )
  {
    free(value);
    value = NULL;
  }

  /* reading all Header values */
  printf("\n ... Reading the complete Fixed header ...\n\n", value);	
  xf_tree_get_fixed_header_items ( &fd_3, 
                                   &file_name_all, 
                                   &file_description_all, 
                                   &notes_all, 
                                   &mission_all, 
                                   &file_class_all, 
                                   &file_type_all,
                                   &validity_start_all, 
                                   &validity_stop_all, 
                                   file_version_all, 
                                   &system_all, 
                                   &creator_all, 
                                   &creator_version_all,
                                   &creation_date_all, 
                                   &error);   
  if ( error < XF_CFI_OK && error != XF_CFI_EMPTY_ELEMENT )
  {
    printf("\nError reading fixed-header item\n" );      	      	
    closeup (error);
  }
  else
  {
    printf("\n ... File_Name: ---> %s\n", file_name_all);	
    printf("\n ... Notes    : ---> %s\n", notes_all);	
  }

  /* reading filename */  
  printf ( "\n	... Reading filename ...\n\n");
  xf_read_filename_items ( file_name_all, &satellite_id_r, file_class_r, file_type_r, instance_id_r, &error); 
  if ( error < XF_CFI_OK ) {
       printf("\nError reading filename\n" );      	      	
       closeup (error);
  } else {
   printf("\n ... satellite_id ---> %ld\n" , satellite_id_r );	
   printf("\n ... file_class   ---> %s\n"  , &file_class_r );
   printf("\n ... file_type    ---> %s\n"  , &file_type_r );
   printf("\n ... instance_id  ---> %s\n"  , &instance_id_r );
  }    

  /*********************************************************** 
  *	/Adding Header and values for the Header elements 
  ************************************************************/   

  /* Writing to disk. If the errors are XF_CFI_CREATING_NODE_ERROR or
     XF_CFI_ADDING_SIBLING_ERROR, then an indentation error has ocurred,
     which is not very important and can be ignored */
  start = clock();
  xf_tree_write ( &fd_3, writtenXmlFile, &error );
  stop = clock();

  if ( error < XF_CFI_OK && error != XF_CFI_CREATING_NODE_ERROR && error != XF_CFI_ADDING_SIBLING_ERROR )
  {
     printf("\nWriting error\n" );
     closeup (error);
  }

  duration = ((long)stop - (long)start)/1000;
  printf("\nFile written\n\n");



  /*********************************************************** 
  *	/Adding Header and values for the Header elements 
  ************************************************************/   
  file_extension_type = XF_HEADER_FORMAT_EEF;

  fd_4 = xf_tree_create( &error );

  xf_tree_create_root ( &fd_4, "Earth_Explorer_File", &error );

  xf_tree_create_header (&fd_4, &file_extension_type, &error);

  xf_tree_set_fixed_header_items ( &fd_4, writtenXmlFile_2, file_description_all, notes_all,
				   mission_all, file_class, file_type, validity_start_all,
				   validity_stop_all, file_version_all, system_all, creator_all,
				   creator_version_all, creation_date_all, &error);

  xf_tree_write ( &fd_4, writtenXmlFile_2, &error );

  free(file_name_all);
  file_name_all=NULL;
  free(file_description_all);
  file_description_all=NULL;
  free(notes_all);
  notes_all=NULL;
  free(mission_all);
  mission_all=NULL;
  free(file_class_all);
  file_class_all=NULL;
  free(file_type_all);
  file_type_all=NULL;
  free(validity_start_all);
  validity_start_all=NULL;
  free(validity_stop_all);
  validity_stop_all=NULL;
  free(system_all);
  system_all=NULL;
  free(creator_all);
  creator_all=NULL;
  free(creator_version_all);
  creator_version_all=NULL;
  free(creation_date_all);
  creation_date_all=NULL;
  
  
  /* Cleaning */
  xf_tree_cleanup_all_parser ();

  printf("\nEOCFI_FILE_HANDLING EXAMPLE COMPLETED SUCCESSFULLY\n"); 

  return XF_CFI_OK;
}

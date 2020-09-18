
from netCDF4 import Dataset
import numpy as np
import os
import sys
from common.io.outputdir import mkdirOutputdir

def writeToa(outputdir, name, toa):

    # Check output directory
    mkdirOutputdir(outputdir)

    # TOA filename
    savetostr = os.path.join(outputdir, name + '.nc')

    # open a netCDF file to write
    ncout = Dataset(savetostr, 'w', format='NETCDF4')
    
    # define axis size
    ncout.createDimension('alt_lines', toa.shape[0])  # unlimited
    ncout.createDimension('act_columns', toa.shape[1])

    # create variable array
    floris_toa_scene = ncout.createVariable('toa', 'float32',
                                            ('alt_lines', 'act_columns',))

    # Assign data
    floris_toa_scene[:]         = toa[:]
    
    # close files
    ncout.close()

    print("Finished writting: " + savetostr)

def readToa(directory, filename):

    # concatenate filename and check that it exists
    ncfile = os.path.join(directory, filename)
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    toa = np.array(dset.variables['toa'][:])

    dset.close()

    print('Size of matrix ' + str(toa.shape))

    return toa

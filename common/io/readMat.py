from netCDF4 import Dataset
import numpy as np
import os
import sys
from common.io.outputdir import mkdirOutputdir


def readMat(directory, filename):

    ncfile = os.path.join(directory, filename)
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    mat = np.array(dset.variables['mat'][:])
    dset.close()
    print('Size of matrix ' + str(mat.shape))
    
    return mat

def writeMat(outputdir, name, mat):

    # Check output directory
    mkdirOutputdir(outputdir)

    # TOA filename
    savetostr = os.path.join(outputdir, name + '.nc')

    # open a netCDF file to write
    ncout = Dataset(savetostr, 'w', format='NETCDF4')

    # define axis size
    ncout.createDimension('alt_lines', mat.shape[0])  # unlimited
    ncout.createDimension('act_columns', mat.shape[1])

    # create variable array
    floris_toa_scene = ncout.createVariable('mat', 'float32',
                                            ('alt_lines', 'act_columns',))

    # Assign data
    floris_toa_scene[:]         = mat[:]

    # close files
    ncout.close()

    print("Finished writting: " + savetostr)

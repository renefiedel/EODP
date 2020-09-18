from netCDF4 import Dataset
import numpy as np
import os
import sys

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

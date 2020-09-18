from netCDF4 import Dataset
import numpy as np

def readIsrf(isrffile, b):

    ncfile = isrffile + b + '.nc'
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    isrf = np.array(dset.variables['isrf'][:])
    wv_isrf = np.array(dset.variables['wavelength'][:])

    dset.close()

    return isrf, wv_isrf

from netCDF4 import Dataset
import numpy as np
import os
import sys
from common.io.outputdir import mkdirOutputdir

def readCube(directory, filename):

    # concatenate filename and check that it exists
    ncfile = os.path.join(directory, filename)
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    toa = np.array(dset.variables['toa'][:])
    wv = np.array(dset.variables['wv'][:])
    dset.close()
    print('Size of cube ' + str(toa.shape))
    
    return toa, wv

def writeCube(directory, filename, toa, wv):

    # Check output directory
    mkdirOutputdir(directory)

    # TOA filename
    savetostr = os.path.join(directory, filename + '.nc')

    # open a netCDF file to write
    ncout = Dataset(savetostr, 'w', format='NETCDF4')

    # define axis size
    ncout.createDimension('n_lines', toa.shape[0])  # unlimited
    ncout.createDimension('n_columns', toa.shape[1])
    ncout.createDimension('n_wavelengths', toa.shape[2])

    # create variable array
    floris_toa_scene = ncout.createVariable('toa', 'float32',
                                            ('n_lines', 'n_columns','n_wavelengths',))
    floris_toa_scene.units = 'mW/sr/m2/nm'
    floris_toa_scene.description = "TOA spectral radiances"
    wavelengths = ncout.createVariable('wv', 'float32', ('n_wavelengths',))
    wavelengths.units = 'nm'
    wavelengths.description = "Wavelengths in nanometers"

    # Assign data
    floris_toa_scene[:]         = toa[:]
    wavelengths[:]              = wv[:]

    # close files
    ncout.close()

    print("Finished writting: " + savetostr)

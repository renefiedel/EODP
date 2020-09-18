
from netCDF4 import Dataset
import numpy as np
import os
import sys
from common.io.outputdir import mkdirOutputdir

def writeL1c(outputdir, name, lat, lon, toa):

    # Check output directory
    mkdirOutputdir(outputdir)

    # TOA filename
    savetostr = os.path.join(outputdir, name + '.nc')

    # open a netCDF file to write
    ncout = Dataset(savetostr, 'w', format='NETCDF4')

    # define axis size
    ncout.createDimension('npoints', len(lat))

    # create variable array
    toa_scene = ncout.createVariable('toa', 'float32', ('npoints',))
    toa_scene.units = 'mW/m2/sr'
    toa_scene.description = "L1C radiances"
    lat_scene = ncout.createVariable('lat', 'float32', ('npoints',))
    lat_scene.units = 'degrees'
    lat_scene.description = "L1C geodetic latitude"
    lon_scene = ncout.createVariable('lon', 'float32', ('npoints',))
    lon_scene.units = 'degrees'
    lon_scene.description = "L1C geodetic longitude"

    # Assign data
    toa_scene[:]         = toa[:]
    lat_scene[:]         = lat[:]
    lon_scene[:]         = lon[:]

    # close files
    ncout.close()

    print("Finished writting: " + savetostr)

def readL1c(directory, filename):

    # concatenate filename and check that it exists
    ncfile = os.path.join(directory, filename)
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from FIPS NetCDF file
    toa = np.array(dset.variables['toa'][:])
    lat = np.array(dset.variables['lat'][:])
    lon = np.array(dset.variables['lon'][:])

    dset.close()

    print('Size of matrix ' + str(toa.shape))

    return toa, lat, lon

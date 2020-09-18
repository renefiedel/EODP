from netCDF4 import Dataset
import numpy as np
import os
import sys

def readGeodetic(directory, filename):
    '''
    Reads the output geodetic file from the GM
    :param directory: directory
    :param filename: geodetic.nc
    :return: latitude and longitude matrices in degrees
    '''

    ncfile = os.path.join(directory, filename)
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    lat = np.array(dset.groups['projection'].variables['latitude'][:])
    lon = np.array(dset.groups['projection'].variables['longitude'][:])

    dset.close()
    print('Size of matrix ' + str(lat.shape))

    return lat, lon

def getCorners(mat):
    '''
    Returns the corners of a 2D matrix
    :param mat: 2D matrix
    :return: corners
    '''
    corners = [mat[0,0],mat[0,-1],mat[-1,-1],mat[-1,0],mat[0,0]]
    return corners

def readGeodeticCorners(directory, filename):
    '''
    Reads the corners of geodetic.nc
    :param directory: directory
    :param filename: geodetic.nc
    :return: corners of the latitude and longitude
    '''

    # Load dataset
    lat,lon = readGeodetic(directory, filename)

    # Assign in a clockwise direction
    lat_corners = getCorners(lat)
    lon_corners = getCorners(lon)

    return lat_corners,lon_corners


from netCDF4 import Dataset
import numpy as np
import sys
import os
#from common.io.outputdir import mkdirOutputdir

EQ_MULT = "equalization_multiplicative_factor"
EQ_ADD = "equalization_additive_factor"
NC_EXT = ".nc"

def readFactor(ncfile, varname):
    '''
    Reading a variable from a TOA
    :param ncfile:  NC file
    :param varname: String with the name of the variable
    :return: Numpy array with the variable
    '''

    # Check
    if not os.path.isfile(ncfile):
        sys.exit('File not found ' +ncfile + ". Exiting.")
    print('Reading ' + ncfile)

    # Load dataset
    dset = Dataset(ncfile)

    # Extract data from NetCDF file
    gain = np.array(dset.variables[varname][:])
    dset.close()
    print('Size of matrix ' + str(gain.shape))

    return gain

def writeFactor(outputdir, name, gain, varname, varunis, vardescript):
    '''
    Writes a NC file for a 1D variable (a function of the pixels)
    :param outputdir: output directory
    :param name: name of the file
    :param gain: variable to write
    :param varname: Name of the variable (string)
    :param varunis: units of the variable (string)
    :param vardescript: Description of the variable (string)
    :return: NA
    '''

    # Check output directory
   # mkdirOutputdir(outputdir)

    # TOA filename
    savetostr = os.path.join(outputdir, name + '.nc')

    # open a netCDF file to write
    ncout = Dataset(savetostr, 'w', format='NETCDF4')

    # define axis size
    ncout.createDimension('act_columns', len(gain))

    # create variable array
    gainvar = ncout.createVariable(varname, 'float32',
                                            ('act_columns',))
    gainvar.units = varunis
    gainvar.description = vardescript

    # Assign data
    gainvar[:] = gain[:]

    # close files
    ncout.close()

    print("Finished writing: " + savetostr)



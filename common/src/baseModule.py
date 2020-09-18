import logging.config
from config.globalConfig import globalConfig
from auxiliary.constants import constants
from common.io.fileExists import fileExists, addFileSep
import os

class baseModule:

    def __init__(self, auxdir, indir, outdir, modulestr):

        # Check the input, output and auxiliary directories
        # ----------------------------------------------------------------
        #  Check that it can find the Auxiliary Folder
        if not (fileExists(auxdir)):
            raise Exception('Auxiliary folder not found ' + auxdir)
        else:
            self.auxdir = addFileSep(auxdir)

        # Check whether there are one or two folders as inputs
        indir = indir.split(',')
        for istr in range(len(indir)):
            if not (fileExists(indir[istr])):
                raise Exception('Inputs folder not found ' + indir)
            else:
                indir[istr] = addFileSep(indir[istr])
        if len(indir)==1: # If there is only one directory, remove the list
            indir = indir[0]
        # Assign
        self.indir = indir

        # Checks if the Output folder exists, if not creates it
        if not (fileExists(outdir)):
            print('Creating output folder ' + outdir)
            os.mkdir(outdir, mode=0o777)
            self.outdir = addFileSep(outdir)
        else:
            self.outdir = addFileSep(outdir)


        # Initialise logger and global config
        # ----------------------------------------------------------------
        # Module name
        self.modulestr = modulestr

        # Global Config
        self.globalConfig = globalConfig()

        # Init logger
        logstr = auxdir + os.path.sep + self.globalConfig.logconfigfile
        if not (fileExists(logstr)):
            raise Exception('Check the auxililary path and the logconf in the Global configuration. '
                            'File not found: ' + logstr)

        outlog = outdir + os.path.sep + modulestr + '.log'
        logging.config.fileConfig(logstr,
                                  defaults={'logfilename': outlog})
        self.logger = logging.getLogger(self.modulestr)

        # Get constants
        self.constants = constants()

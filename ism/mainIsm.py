
# MAIN FUNCTION TO CALL THE ISM MODULE

from ism.src.ism import ism

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/auxiliary'
indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-ISM/input'
outdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/ism_output'

# Initialise the ISM
myIsm = ism(auxdir, indir, outdir)
myIsm.processModule()

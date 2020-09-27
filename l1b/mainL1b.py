
# MAIN FUNCTION TO CALL THE L1B MODULE

from l1b.src.l1b import l1b

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/auxiliary'
indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1B/input'
outdir = '/home/renefiedel/Documents/Python/output'

# Initialise the ISM
myL1b = l1b(auxdir, indir, outdir)
myL1b.processModule()

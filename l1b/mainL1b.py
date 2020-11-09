
# MAIN FUNCTION TO CALL THE L1B MODULE

from l1b.src.l1b import l1b

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/auxiliary'

indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/ism_output/E2E' # for end-to-end simuulation
outdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1b_output/E2E'

# Initialise the ISM
myL1b = l1b(auxdir, indir, outdir)
myL1b.processModule()


# MAIN FUNCTION TO CALL THE L1B MODULE

from l1b.src.l1b import l1b

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/luss/EODP/eodp/auxiliary'
indir = '/home/luss/EODP/eodp/ism/test/ut02/output'
outdir = '/home/luss/EODP/eodp/l1b/test/ut02/output'

# Initialise the ISM
myL1b = l1b(auxdir, indir, outdir)
myL1b.processModule()

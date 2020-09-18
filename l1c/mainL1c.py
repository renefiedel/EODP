
# MAIN FUNCTION TO CALL THE L1C MODULE

from l1c.src.l1c import l1c

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/luss/EODP/eodp/auxiliary'
# GM dir + L1B dir
indir = '/home/luss/my_shared_folder/gm_out/gm_alt100_act_150/,/home/luss/EODP/eodp/l1b/test/ut02/output'
outdir = '/home/luss/EODP/eodp/l1c/test/ut01/output'

# Initialise the ISM
myL1c = l1c(auxdir, indir, outdir)
myL1c.processModule()

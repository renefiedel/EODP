
# MAIN FUNCTION TO CALL THE L1B MODULE

from l1b.src.l1b import l1b

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/PycharmProjects/EODP/auxiliary'
indir = '/home/renefiedel/PycharmProjects/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1B/input'
#  indir = '/home/renefiedel/PycharmProjects/EODP/Output/ism_output/E2E'  # for end-to-end simulation
outdir = '/home/renefiedel/PycharmProjects/EODP/Output/l1b_output'

# Initialise the ISM
myL1b = l1b(auxdir, indir, outdir)
myL1b.processModule()


# MAIN FUNCTION TO CALL THE L1C MODULE

from l1c.src.l1c import l1c

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/auxiliary'
# GM dir + L1B dir
indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/input/gm_alt100_act_150,/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1b_output'
outdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
# E2E
# indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/eodp_gm-master/bin/output_dir,/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1b_output/E2E'
# outdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output/E2E'
# E2E folder only for the end-to-end simulation


# Initialise the ISM
myL1c = l1c(auxdir, indir, outdir)
myL1c.processModule()

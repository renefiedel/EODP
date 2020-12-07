
# MAIN FUNCTION TO CALL THE ISM MODULE

from ism.src.ism import ism

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/renefiedel/PycharmProjects/EODP/auxiliary'
indir = '/home/renefiedel/PycharmProjects/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-ISM/input/' \
        'gradient_alt100_act150'
#  indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-E2E/sgm_out'
outdir = '/home/renefiedel/PycharmProjects/EODP/Output/ism_output'
#  E2E for end-to-end and Output for ism only

# Initialise the ISM
myIsm = ism(auxdir, indir, outdir)
myIsm.processModule()

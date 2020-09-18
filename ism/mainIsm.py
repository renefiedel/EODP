
# MAIN FUNCTION TO CALL THE ISM MODULE

from ism.src.ism import ism

# Directory - this is the common directory for the execution of the E2E, all modules
auxdir = '/home/luss/EODP/eodp/auxiliary'
indir = '/home/luss/my_shared_folder/sgm_out/gradient_alt100_act150/' # small scene
outdir = '/home/luss/EODP/eodp/ism/test/ut02/output'

# Initialise the ISM
myIsm = ism(auxdir, indir, outdir)
myIsm.processModule()

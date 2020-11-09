import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa
from common.io.l1cProduct import readL1c

# output l1c
indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
# reference l1c
refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/output'

for i in range(4):
    mytoa1 = readToa(indir, "l1c_toa_VNIR-" + str(i) + ".nc")
    mytoa = np.sort(mytoa1)
    reftoa1 = readToa(refoutdir, "l1c_toa_VNIR-" + str(i) + ".nc")
    reftoa = np.sort(reftoa1)

    diff_toa = np.max(np.abs(mytoa - reftoa)/reftoa)
    print('difftoa_VNIR-' + str(i) + '=', diff_toa*100)

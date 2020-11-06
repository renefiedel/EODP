import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa


indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/output'

mytoa = [None]*4
reftoa = [None]*4
diff_toa = [None]*4

for ii in range(4):
    mytoa[ii] = readToa(indir, "l1c_toa_VNIR-" + str(ii) + ".nc")
    reftoa[ii] = readToa(refoutdir, 'l1c_toa_VNIR-' + str(ii) + '.nc')
    mytoa[ii] = np.sort(mytoa[ii])
    reftoa[ii] = np.sort(reftoa[ii])

    diff_toa[ii] = np.min(np.abs((mytoa[ii] - reftoa[ii])/reftoa[ii]))
    print('difftoa_VNIR-' + str(ii) + '=', diff_toa[ii]*100)

import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa


indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/output'

mytoa = [None]*4
reftoa = [None]*4
diff_toa = [None]*4

for i in range(4):
    mytoa[i] = readToa(indir, "l1c_toa_VNIR-" + str(i) + ".nc")
    mytoa[i] = np.sort(mytoa[i])
    reftoa[i] = readToa(refoutdir, 'l1c_toa_VNIR-' + str(i) + '.nc')
    reftoa[i] = np.sort(reftoa[i])

    diff_toa[i] = np.min(np.abs((mytoa[i] - reftoa[i])/reftoa[i]))
    print('difftoa_VNIR-' + str(i) + '=', diff_toa[i]*100)

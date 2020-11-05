import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa


indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
mytoa = readToa(indir, "l1c_toa_VNIR-0.nc")
l1c1 = np.sort(mytoa)

refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/output'
reftoa = readToa(refoutdir, "l1c_toa_VNIR-0.nc")
l1c2 = np.sort(reftoa)

difftoa = np.min(np.abs(l1c1-l1c2))
print(difftoa)

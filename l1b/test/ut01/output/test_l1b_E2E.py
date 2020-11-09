
import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa

indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1b_output/E2E'
mytoa = readToa(indir, "l1b_toa_VNIR-0.nc")

refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-E2E/l1b_out'
reftoa = readToa(refoutdir, "l1b_toa_VNIR-0.nc")

difftoa = np.max(np.abs(mytoa - reftoa)/reftoa)
print(difftoa*100)
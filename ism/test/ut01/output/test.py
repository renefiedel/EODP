import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa

indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/ism_output'
mytoa = readToa(indir, "ism_toa_optical_VNIR-0.nc")

refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-ISM/output'
reftoa = readToa(refoutdir, "ism_toa_optical_VNIR-0.nc")

difftoa = np.max(np.abs(mytoa-reftoa))
print(difftoa)

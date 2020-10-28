import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa
#  This script is to test the output generated by L1C and compared with the outputs of the teacher
indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/l1c_output'
mytoa = readToa(indir, "l1c_toa_VNIR-0.nc")

refoutdir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1C/output'
reftoa = readToa(refoutdir, "l1c_toa_VNIR-0.nc")

difftoa = np.max(np.abs(mytoa-reftoa))
print(difftoa)
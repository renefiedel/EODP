import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa

indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/ism_output'
mytoa = readToa(indir, "")

refoutdir = '/home/renefiedel/Downloads/eodpystemmtf'
reftoa = readMat(refoutdir, "Hsys_VNIR-0.nc")

difftoa = np.max(np.abs(mytoa-reftoa))
print(difftoa)

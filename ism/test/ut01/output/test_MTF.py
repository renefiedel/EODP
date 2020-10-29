import numpy as np
import matplotlib.pyplot as plt

from common.io.readMat import readMat
from common.io.writeToa import readToa

indir = '/home/renefiedel/Documents/EO DATA PROCESSING/EODP/EODP/Output/ism_output'
mytoa = readMat(indir, "mtfVNIR-0.nc")

refoutdir = '/home/renefiedel/Downloads/eodpystemmtf'
reftoa = readMat(refoutdir, "Hsys_VNIR-0.nc")

difftoa = np.max(np.abs(mytoa-reftoa))
print(difftoa)

import numpy as np
import matplotlib.pyplot as plt
from common.io.writeToa import readToa

indir = '/home/renefiedel/PycharmProjects/EODP/Output/l1b_output'
#  mytoa = readToa(indir, "l1b_toa_eq_VNIR-0.nc")

refoutdir = '/home/renefiedel/PycharmProjects/EODP_TER-20200917T082333Z-001/EODP_TER/EODP-TS-L1B/output'
#   reftoa = readToa(refoutdir, "l1b_toa_eq_VNIR-0.nc")

for ii in range(4):
    mytoa = readToa(indir, "l1b_toa_eq_VNIR-" + str(ii) + ".nc")
    reftoa = readToa(refoutdir, "l1b_toa_eq_VNIR-" + str(ii) + ".nc")

    #  absolute error
    #  difftoa_abs = np.max(np.abs(mytoa-reftoa))
    #  print(difftoa_abs)

    #  relative error
    difftoa_rel = np.max(np.abs(mytoa - reftoa) / reftoa)
    print("difftoa_rel_VNIR-" + str(ii) + "=", difftoa_rel * 100)

#  Plot
    fig = plt.figure(figsize=(20, 10))
    plt.plot(mytoa, 'b-o', label='user data')
    plt.plot(reftoa, 'r-o', label='reference data')
    plt.title('Difference between user and reference data ', fontsize=20)
    plt.xlabel('ACT [-]', fontsize=16)
    plt.ylabel('ALT [-]', fontsize=16)
    plt.grid()
    plt.legend()
    directory = '/home/renefiedel/PycharmProjects/EODP/l1b/test/ut01/output'
    savestr = "{0}/L1B test file".format(directory)
    plt.savefig(savestr)
    plt.close(fig)

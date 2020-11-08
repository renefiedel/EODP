
# L1B CONFIGURATION FILE

import numpy as np


class l1bConfig:

    def __init__(self):

        # Flags to enable or disable the equalization
        self.do_equalization = False

        # Auxiliary inputs (relative paths to the root folder)
        #--------------------------------------------------------------------------------
        # Gain, conversion factor from Digital Numbers to Radiances
        self.gain = np.array([0.005764054, 0.0042465106, 0.0032643573, 0.002987937])  # [mW/m2/sr/DN]

        # Equalisation, multiplicative and additive factors.
        self.eq_mult = 'equalization/eq_mult_'
        self.eq_add = 'equalization/eq_add_'

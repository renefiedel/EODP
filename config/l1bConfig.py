
# L1B CONFIGURATION FILE

import numpy as np

class l1bConfig:

    def __init__(self):

        # Flags to enable or disable the equalization
        self.do_equalization = True

        # Auxiliary inputs (relative paths to the root folder)
        #--------------------------------------------------------------------------------
        # Gain, conversion factor from Digital Numbers to Radiances
        self.gain = np.array([0.09209303, 0.06787323, 0.052162305, 0.047756273]) # [mW/m2/sr/DN]

        # Equalisation, multiplicative and additive factors.
        self.eq_mult = 'equalization/eq_mult_'
        self.eq_add = 'equalization/eq_add_'


# L1C CONFIGURATION FILE

import numpy as np

class l1cConfig:

    def __init__(self):

        # MILITARY GRID REFERENCE SYSTEM
        # https://en.wikipedia.org/wiki/Military_Grid_Reference_System

        # Size of the MGRS tiles (100 km)
        # NOTE: The tile size needs to be > that the L1C grid size, so precision >=3
        self.mgrs_tile_size = 100 # [m]

        # Precision of the MGRS for the lat/lon to MGRS conversion
        # 4QFJ ...................GZD and 100 km Grid Square ID, precision level 100 km -> MGSPrecision 0
        # 4QFJ 1 6 ...............precision level 10 km                                 -> MGSPrecision 1
        # 4QFJ 12 67 .............precision level 1 km                                  -> MGSPrecision 2
        # 4QFJ 123 678 ...........precision level 100 m                                 -> MGSPrecision 3
        # 4QFJ 1234 6789 .........precision level 10 m                                  -> MGSPrecision 4
        # 4QFJ 12345 67890 .......precision level 1 m                                   -> MGSPrecision 5
        self.mgrs_tile_precision = 3 # [m]

        self.plotL1cGrid = True

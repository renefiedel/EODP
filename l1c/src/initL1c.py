
from config.l1cConfig import l1cConfig
from common.src.baseModule import baseModule

class initL1c(baseModule):
    def __init__(self, auxdir, indir, outdir):

        # Initialise baseModule (the log, etc.)
        super().__init__(auxdir, indir, outdir, "L1C")

        # Init Local config
        self.l1cConfig = l1cConfig()

        # Make sure the logger is enabled
        self.logger.disabled = False

        # Assign the GM and the L1B input directories
        self.gmdir = self.indir[0]
        self.l1bdir = self.indir[1]

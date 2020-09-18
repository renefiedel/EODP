
from config.l1bConfig import l1bConfig
from common.src.baseModule import baseModule
from common.io.fileExists import fileExists, addFileSep
import os


class initL1b(baseModule):
    def __init__(self, auxdir, indir, outdir):

        # Initialise baseModule (the log, etc.)
        super().__init__(auxdir, indir, outdir, "L1B")

        # Init Local config
        self.l1bConfig = l1bConfig()

        # Make sure the logger is enabled
        self.logger.disabled = False

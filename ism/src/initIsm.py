from config.ismConfig import ismConfig
from common.src.baseModule import baseModule

class initIsm(baseModule):

    def __init__(self, auxdir, indir, outdir):

        # Initialise baseModule (the log, etc.)
        super().__init__(auxdir, indir, outdir, "ISM")

        # Init Local config
        self.ismConfig = ismConfig()

        # Make sure the logger is enabled
        self.logger.disabled = False

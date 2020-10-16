
# INSTRUMENT MODULE

from ism.src.initIsm import initIsm
from ism.src.opticalPhase import opticalPhase
from ism.src.detectionPhase import detectionPhase
from ism.src.videoChainPhase import videoChainPhase
from common.io.readCube import readCube
from common.io.writeToa import writeToa

class ism(initIsm):

    def __init__(self, auxdir, indir, outdir):
        super().__init__(auxdir, indir, outdir)

    def processModule(self):

        self.logger.info("Start of the Instrument Module")

        # Read input TOA cube
        # -------------------------------------------------------------------------------
        sgm_toa, sgm_wv = readCube(self.indir, self.globalConfig.scene)

        for band in self.globalConfig.bands:

            self.logger.info("Start of BAND " + band)

            # Optical Phase
            # -------------------------------------------------------------------------------
            myOpt = opticalPhase(self.auxdir, self.indir, self.outdir)
            toa = myOpt.compute(sgm_toa, sgm_wv, band)

            # Detection Stage
            # -------------------------------------------------------------------------------
            myDet = detectionPhase(self.auxdir, self.indir, self.outdir)
            toa = myDet.compute(toa, band)

            # Video Chain Phase
            # -------------------------------------------------------------------------------
            myVcu = videoChainPhase(self.auxdir, self.indir, self.outdir)
            toa = myVcu.compute(toa, band)

            # Write output TOA
            # -------------------------------------------------------------------------------
            writeToa(self.outdir, self.globalConfig.ism_toa + band, toa)

            self.logger.info("End of BAND " + band)

        self.logger.info("End of the Instrument Module!")



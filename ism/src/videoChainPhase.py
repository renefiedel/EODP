from ism.src.initIsm import initIsm
import numpy as np
from common.plot.plotMat2D import plotMat2D
from common.plot.plotF import plotF


class videoChainPhase(initIsm):

    def __init__(self, auxdir, indir, outdir):
        super().__init__(auxdir, indir, outdir)

    def compute(self, toa, band):
        self.logger.info("EODP-ALG-ISM-3000: Video Chain")

        # Electrons to Voltage - read-out & amplification
        # -------------------------------------------------------------------------------
        self.logger.info("EODP-ALG-ISM-3010: Electrons to Voltage – Read-out and Amplification")
        toa = self.electr2Volt(toa,
                               self.ismConfig.OCF,
                               self.ismConfig.ADC_gain)

        self.logger.debug("TOA [0,0] " + str(toa[0, 0]) + " [V]")

        # Digitisation
        # -------------------------------------------------------------------------------
        self.logger.info("EODP-ALG-ISM-3020: Voltage to Digital Numbers – Digitisation")
        toa = self.digitisation(toa,
                                self.ismConfig.bit_depth,
                                self.ismConfig.min_voltage,
                                self.ismConfig.max_voltage)

        self.logger.debug("TOA [0,0] " + str(toa[0, 0]) + " [DN]")

        # Plot
        if self.ismConfig.save_vcu_stage:
            saveas_str = self.globalConfig.ism_toa_vcu + band
            title_str = 'TOA after the VCU phase [DN]'
            xlabel_str = 'ACT'
            ylabel_str = 'ALT'
            plotMat2D(toa, title_str, xlabel_str, ylabel_str, self.outdir, saveas_str)

            idalt = int(toa.shape[0] / 2)
            saveas_str = saveas_str + '_alt' + str(idalt)
            plotF([], toa[idalt, :], title_str, xlabel_str, ylabel_str, self.outdir, saveas_str)

        return toa

    def electr2Volt(self, toa, OCF, gain_adc):
        """
        Electron to Volts conversion.
        Simulates the read-out and the amplification
        (multiplication times the gain).
        :param toa: input toa in [e-]
        :param OCF: Output Conversion factor [V/e-]
        :param gain_adc: Gain of the Analog-to-digital conversion [-]
        :return: output toa in [V]
        """
        # TODO
        toa = toa * OCF * gain_adc

        return toa

    def digitisation(self, toa, bit_depth, min_voltage, max_voltage):
        """
        Digitisation - conversion from Volts to Digital counts
        :param toa: input toa in [V]
        :param bit_depth: bit depth
        :param min_voltage: minimum voltage
        :param max_voltage: maximum voltage
        :return: toa in digital counts
        """
        # TODO
        bdepth = 2 ** bit_depth - 1
        toa_dn = np.round((toa / (max_voltage - min_voltage)) * bdepth)

        # Make sure DN is not above the saturation level
        # TODO
        for iact in range(toa.shape[0]):
            for ialt in range(toa.shape[1]):
                if toa_dn[iact, ialt] < 0:
                    toa_dn[iact, ialt] = 0
                    print("toa_dn is below the saturation level.")

                    if toa_dn[iact, ialt] > bdepth:
                        toa_dn[iact, ialt] = bdepth
                        print("toa_dn is above the saturation level.")

        return toa_dn

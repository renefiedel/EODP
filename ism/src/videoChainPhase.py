
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

        self.logger.debug("TOA [0,0] " +str(toa[0,0]) + " [V]")

        # Digitisation
        # -------------------------------------------------------------------------------
        self.logger.info("EODP-ALG-ISM-3020: Voltage to Digital Numbers – Digitisation")
        toa = self.digitisation(toa,
                          self.ismConfig.bit_depth,
                          self.ismConfig.min_voltage,
                          self.ismConfig.max_voltage)

        self.logger.debug("TOA [0,0] " +str(toa[0,0]) + " [DN]")

        # Plot
        if self.ismConfig.save_vcu_stage:
            saveas_str = self.globalConfig.ism_toa_vcu + band
            title_str = 'TOA after the VCU phase [DN]'
            xlabel_str='ACT'
            ylabel_str='ALT'
            plotMat2D(toa, title_str, xlabel_str, ylabel_str, self.outdir, saveas_str)

            idalt = int(toa.shape[0]/2)
            saveas_str = saveas_str + '_alt' + str(idalt)
            plotF([], toa[idalt,:], title_str, xlabel_str, ylabel_str, self.outdir, saveas_str)

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
        toa = toa*OCF*gain_adc

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
        bdepth = 2**bit_depth - 1
        toa_dn = np.round((toa / (max_voltage - min_voltage)) * (bdepth))

        # Make sure DN is not above the saturation level
        # TODO
        #if toa_dn > bdepth:

         #   raise Exception('toa_dn is above the saturation level!!!')
        #print("This is always printed.")

        #if toa_dn <= bdepth:
         #   print(toa_dn, "is below the saturation level.")
        #print("This is also always printed.")

        # Given range
       # X = 2
        #Y = 0

        #def checkRange(toa_dh):
            # using comparison operator
         #   if X <= toa_dh <= Y:
          #      print('The number {} is in range ({}, {})'.format(toa_dh, X, Y))
           # else:
            #    print('The number {} is not in range ({}, {})'.format(toa_dh, X, Y))
                # Test Input List
             #   testInput = [X - 1, X, X + 1, Y + 1, Y, Y - 1]

              #  for eachItem in testInput:
               #     checkRange(eachItem)

        return toa_dn


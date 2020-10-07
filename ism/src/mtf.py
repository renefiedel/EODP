from math import pi

import scipy
from numpy import sinc

from config.ismConfig import ismConfig
import numpy as np
import math
import matplotlib.pyplot as plt
from scipy.special import j1
from numpy.matlib import repmat
from common.plot.plotMat2D import plotMat2D
from scipy.interpolate import interp2d
from numpy.fft import fftshift, ifft2
import os

class mtf:
    """
    Class MTF. Collects the analytical modelling of the different contributions
    for the system MTF
    """
    def __init__(self, logger):
        self.ismConfig = ismConfig()
        self.logger = logger

    def system_mtf(self, nlines, ncolumns, D, lambd, focal, pix_size,
                   kLF, wLF, kHF, wHF, defocus, ksmear, kmotion, directory, band):
        """
        System MTF
        :param nlines: Lines of the TOA
        :param ncolumns: Columns of the TOA
        :param D: Telescope diameter [m]
        :param lambd: central wavelength of the band [m]
        :param focal: focal length [m]
        :param pix_size: pixel size in meters [m]
        :param kLF: Empirical coefficient for the aberrations MTF for low-frequency wavefront errors [-]
        :param wLF: RMS of low-frequency wavefront errors [m]
        :param kHF: Empirical coefficient for the aberrations MTF for high-frequency wavefront errors [-]
        :param wHF: RMS of high-frequency wavefront errors [m]
        :param defocus: Defocus coefficient (defocus/(f/N)). 0-2 low defocusing
        :param ksmear: Amplitude of low-frequency component for the motion smear MTF in ALT [pixels]
        :param kmotion: Amplitude of high-frequency component for the motion smear MTF in ALT and ACT
        :param directory: output directory
        :return: mtf
        """

        self.logger.info("Calculation of the System MTF")

        # Calculate the 2D relative frequencies
        self.logger.debug("Calculation of 2D relative frequencies")
        fn2D, fr2D, fnAct, fnAlt = self.freq2d(nlines, ncolumns, D, lambd, focal, pix_size)

        # Diffraction MTF
        self.logger.debug("Calculation of the diffraction MTF")
        Hdiff = self.mtfDiffract(fr2D)

        # Defocus
        Hdefoc = self.mtfDefocus(fr2D, defocus, focal, D)

        # WFE Aberrations
        Hwfe = self.mtfWfeAberrations(fr2D, lambd, kLF, wLF, kHF, wHF)

        # Detector
        Hdet  = self. mtfDetector(fn2D)

        # Smearing MTF
        Hsmear = self.mtfSmearing(fnAlt, ncolumns, ksmear)

        # Motion blur MTF
        Hmotion = self.mtfMotion(fn2D, kmotion)

        # Calculate the System MTF
        self.logger.debug("Calculation of the Sysmtem MTF by multiplying the different contributors")
        # TODO
        Hsys = Hdiff*Hwfe*Hdefoc*Hdet*Hsmear*Hmotion

        # Plot cuts ACT/ALT of the MTF
        self.plotMtf(Hdiff, Hdefoc, Hwfe, Hdet, Hsmear, Hmotion, Hsys, nlines, ncolumns, fnAct, fnAlt, directory, band)

        return Hsys

    def freq2d(self,nlines, ncolumns, D, lambd, focal, w):
        """
        Calculate the relative frequencies 2D (for the diffraction MTF)
        :param nlines: Lines of the TOA
        :param ncolumns: Columns of the TOA
        :param D: Telescope diameter [m]
        :param lambd: central wavelength of the band [m]
        :param focal: focal length [m]
        :param w: pixel size in meters [m]
        :return fn2D: normalised frequencies 2D (f/(1/w))
        :return fr2D: relative frequencies 2D (f/(1/fc))
        :return fnAct: 1D normalised frequencies 2D ACT (f/(1/w))
        :return fnAlt: 1D normalised frequencies 2D ALT (f/(1/w))
        """

        # TODO
        fstepAlt = 1/nlines/w
        fstepAct = 1/ncolumns/w
        fAlt = np.arange(-1 / (2 * w), 1 / (2 * w) - eps, fstepAlt)
        if nlines != len(fAlt):
            raise Exception('Error in the frequency calculation. Lines TOA ' + str(nlines) + ' Sizes of the frequencies ALT' + str(len(fAlt)) )

        fAct = np.arange(-1 / (2 * w), 1 / (2 * w) - eps, fstepAct)
        if ncolumns != len(fAct):
            raise Exception('Error in the frequency calculation. Columns TOA ' + str(
                ncolumns) + 'Sizes of the frequencies ACT' + str(len(fAct)))

        [fnAltxx, fnActxx] = np.meshgrid(fAlt, fAct, indexing='ij')
        fn2D = np.sqrt(fnAltxx * fnAltxx + fnActxx * fnActxx)

        [frAltxx,frActxx] = np.meshgrid(fAlt*(1/w)/focal, fAct*(1/w)/focal, indexing='ij')
        fr2D=np.sqrt(frAltxx*frAltxx + frActxx*frActxx)

        #fn2D = focal/(1/w)
        # E_cutoff = D/(lambd*focal)
        #fr2D = focal/(D/E_cutoff)
        fnAct = focal/(1/w)
        fnAlt = focal/(1/w)

        return fn2D, fr2D, fnAct, fnAlt

    def mtfDiffract(self,fr2D):
        """
        Optics Diffraction MTF
        :param fr2D: 2D relative frequencies (f/fc), where fc is the optics cut-off frequency
        :return: diffraction MTF
        """
        # Optics diffraction MTF
        def acosf(x):
            return math.acos(x)
        acosv = np.vectorize(acosf)
        # TODO
        Hdiff = (2 / pi) * (acosv(fr2D) - fr2D * np.sqrt(1 - fr2D * fr2D))
        Hdiff[fr2D*fr2D > 1] = 0
        return Hdiff


    def mtfDefocus(self, fr2D, defocus, focal, D):
        """
        Defocus MTF
        :param fr2D: 2D relative frequencies (f/fc), where fc is the optics cut-off frequency
        :param defocus: Defocus coefficient (defocus/(f/N)). 0-2 low defocusing
        :param focal: focal length [m]
        :param D: Telescope diameter [m]
        :return: Defocus MTF
        """
        # TODO
        x = pi * (defocus / (focal / D)) * fr2D * (1 - fr2D)
        scipy.special.j1(x)
        Hdefoc = 2*j1(x) / x

        return Hdefoc

    def mtfWfeAberrations(self, fr2D, lambd, kLF, wLF, kHF, wHF):
        """
        Wavefront Error Aberrations MTF
        :param fr2D: 2D relative frequencies (f/fc), where fc is the optics cut-off frequency
        :param lambd: central wavelength of the band [m]
        :param kLF: Empirical coefficient for the aberrations MTF for low-frequency wavefront errors [-]
        :param wLF: RMS of low-frequency wavefront errors [m]
        :param kHF: Empirical coefficient for the aberrations MTF for high-frequency wavefront errors [-]
        :param wHF: RMS of high-frequency wavefront errors [m]
        :return: WFE Aberrations MTF
        """
        # TODO
        a = -fr2D(1-fr2D)
        b = kLF(wLF/lambd)**2 + kHF(wHF/lambd)**2
        Hwfe = np.exp(a * b)

        return Hwfe

    def mtfDetector(self,fn2D):
        """
        Detector MTF
        :param fnD: 2D normalised frequencies (f/(1/w))), where w is the pixel width
        :return: detector MTF
        """
        # TODO
        Hdet = sinc(fn2D)
        return Hdet

    def mtfSmearing(self, fnAlt, ncolumns, ksmear):
        """
        Smearing MTF
        :param ncolumns: Size of the image ACT
        :param fnAlt: 1D normalised frequencies 2D ALT (f/(1/w))
        :param ksmear: Amplitude of low-frequency component for the motion smear MTF in ALT [pixels]
        :return: Smearing MTF
        """
        # TODO
        smearAlt = np.zeros((len(fnAlt),1))
        smearAlt[:, 0] = np.sinc(fnAlt*ksmear)
        Hsmear = repmat(smearAlt, 1, ncolumns)
        return Hsmear

    def mtfMotion(self, fn2D, kmotion):
        """
        Motion blur MTF
        :param fnD: 2D normalised frequencies (f/(1/w))), where w is the pixel width
        :param kmotion: Amplitude of high-frequency component for the motion smear MTF in ALT and ACT
        :return: detector MTF
        """
        # TODO
        Hmotion = sinc(kmotion*fn2D)
        return Hmotion

    def plotMtf(self,Hdiff, Hdefoc, Hwfe, Hdet, Hsmear, Hmotion, Hsys, nlines, ncolumns, fnAct, fnAlt, directory, band):
        """
        Plotting the system MTF and all of its contributors
        :param Hdiff: Diffraction MTF
        :param Hdefoc: Defocusing MTF
        :param Hwfe: Wavefront electronics MTF
        :param Hdet: Detector MTF
        :param Hsmear: Smearing MTF
        :param Hmotion: Motion blur MTF
        :param Hsys: System MTF
        :param nlines: Number of lines in the TOA
        :param ncolumns: Number of columns in the TOA
        :param fnAct: normalised frequencies in the ACT direction (f/(1/w))
        :param fnAlt: normalised frequencies in the ALT direction (f/(1/w))
        :param directory: output directory
        :param band: band
        :return: N/A
        """
        # Plot cuts of the MTF ACT
        mAlt=int(nlines/2.0)
        mAct=int(ncolumns/2.0)

        fig = plt.figure(figsize=(20,10))
        plt.plot(-fnAct[0:mAct], abs(Hdiff[mAlt,0:mAct]),label='Diffraction MTF')
        plt.plot(-fnAct[0:mAct], abs(Hdefoc[mAlt,0:mAct]),label='Defocus MTF')
        plt.plot(-fnAct[0:mAct], abs(Hwfe[mAlt,0:mAct]),label='WFE Aberrations MTF')
        plt.plot(-fnAct[0:mAct], abs(Hdet[mAlt,0:mAct]),label='Detector MTF')
        plt.plot(-fnAct[0:mAct], abs(Hsmear[mAlt,0:mAct]),label='Smearing MTF')
        plt.plot(-fnAct[0:mAct], abs(Hmotion[mAlt,0:mAct]),label='Motion blur MTF')
        plt.plot(-fnAct[0:mAct], abs(Hsys[mAlt,0:mAct]),'k',linewidth=3,label='System MTF')
        auxv = np.arange(0,1.1,0.1)
        plt.plot(0.5*np.ones(auxv.shape),auxv,'--k',linewidth=3,label='f Nyquist')
        plt.title('System MTF slice ACT for '+band, fontsize=20)
        plt.xlabel('Spatial frequencies f/(1/w) [-]', fontsize=16)
        plt.ylabel('MTF', fontsize=16)
        plt.grid()
        plt.legend()
        saveas_str = 'system_mtf_cutAct_'+band
        savestr = directory + os.path.sep + saveas_str
        plt.savefig(savestr)
        plt.close(fig)
        self.logger.debug("Saved image " + savestr)

        # Plot cuts of the MTF ALT
        fig = plt.figure(figsize=(20,10))
        plt.plot(-fnAlt[0:mAlt], abs(Hdiff[0:mAlt,mAct]),label='Diffraction MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hdefoc[0:mAlt,mAct]),label='Defocus MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hwfe[0:mAlt,mAct]),label='WFE Aberrations MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hdet[0:mAlt,mAct]),label='Detector MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hsmear[0:mAlt,mAct]),label='Smearing MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hmotion[0:mAlt,mAct]),label='Motion blur MTF')
        plt.plot(-fnAlt[0:mAlt], abs(Hsys[0:mAlt,mAct]),'k',linewidth=3,label='System MTF')
        auxv = np.arange(0,1.1,0.1)
        plt.plot(0.5*np.ones(auxv.shape),auxv,'--k',linewidth=3,label='f Nyquist')
        plt.title('System MTF slice ALT for '+band, fontsize=20)
        plt.xlabel('Spatial frequencies f/(1/w) [-]', fontsize=16)
        plt.ylabel('MTF', fontsize=16)
        plt.grid()
        plt.legend()
        saveas_str = 'system_mtf_cutAlt_'+band
        savestr = directory + os.path.sep + saveas_str
        plt.savefig(savestr)
        plt.close(fig)
        self.logger.debug("Saved image " + savestr)

        # Plot 2D system MTF
        plotMat2D(Hsys, "System MTF for " +band, "ACT", "ALT", directory, "system_mtf_2d_"+band)


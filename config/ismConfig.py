
# ISM CONFIGURATION FILE
import numpy as np

class ismConfig:

    def __init__(self):

        # Configuration parameters
        #--------------------------------------------------------------------------------
        # CCD
        self.pix_size = 30e-6                    # [m] Pixel size in microns for the MS channels
        self.t_int = 0.00672                     # [s] Integration time

        # Optical system
        self.D = 0.150                           # [m] Telescope pupil diameter
        self.f = 0.5262                          # [m] Focal length
        self.Tr = 0.99                           # [-] Optical transmittance
        self.wLF = 100e-9                        # [m] RMS of low-frequency wavefront errors
        self.wHF = 100e-9                        # [m] RMS of high-frequency wavefront errors
        self.kLF = 180                           # [-] Empirical coefficient for the aberrations MTF for low-frequency wavefront errors
        self.kHF = 300                           # [-] Empirical coefficient for the aberrations MTF for high-frequency wavefront errors
        self.defocus = 2                         # [-] Defocus coefficient (defocus/(f/N)). 0-2 low defocusing
        self.ksmear = 0.191                      # [pixels] Coefficient for the smearing ALT
        self.kmotion = 0.02                      # [pixels] Amplitude of high-frequency component for the motion smear MTF in ALT and ACT
        self.kernel_half_width = 0.5             # [pixels] Half-width of the kernel
        self.kernel_step = 0.1                   # [pixels] Sampling of the kernel

        # Central wavelength of the band
        self.wv = np.array([0.49,0.665,0.865,0.945])*1e-6  # [m] Central wavelength

        # Photonic Stage
        self.QE = 0.8                            # [e-/ph] Quantum efficiency
        self.FWC = 420000                        # [ph] Full Well Capacity

        # Detection stage
        self.bad_pix = 1.0                      # [%] Percentage of bad/dead pixels in the CCD
        self.dead_pix = 0.5                      # [%]
        self.bad_pix_red = 0.1                   # [-] Reduction in the quantum efficiency of the pixel (over 1)
        self.dead_pix_red = 0.4                  # [-]
        self.kprnu = 0.04                        # 4% Coefficient by which we multiply the PRNU standard normal distribution
        # Dark signal modelling
        self.kdsnu = 0.2                         # 20% Coefficient by which we multiply the DSNU standard normal distribution
        self.T = 300.0                           # [K] Temperature of the system
        self.Tref = 238                          # [K] Reference temperature
        self.ds_A_coeff = 7.87                   # [e-]
        self.ds_B_coeff = 6040                   # [K]

        # Electronic stage
        self.ADC_gain = 0.56                     # [-]
        self.OCF = 5.4e-6                        # [V/e-] Output conversion factor
        self.bit_depth = 12                      # [-]
        self.min_voltage = 0.0                   # [V]
        self.max_voltage = 0.86                  # [V]

        self.seed = 123456789                    # Seed for the random generators

        # Auxiliary inputs (relative paths to the root folder)
        #--------------------------------------------------------------------------------
        self.isrffile = 'isrf/ISRF_'

        # Flags to save intermediate outputs
        #--------------------------------------------------------------------------------
        self.save_after_isrf = True         # optical stage after the ISRF
        self.save_optical_stage = True      # optical stage after the MTF
        self.save_after_ph2e = True         # detections stage after the photon to electron conversion
        self.save_after_prnu = True         # detections stage after the PRNU
        self.save_after_ds = True           # detections stage after the Dark Signal
        self.save_detection_stage = True    # detections stage after the bad/dead pixels
        self.save_vcu_stage = True          # Video Conversion Unit stage

        # Flags to enable or disable the application of noises and effects
        #--------------------------------------------------------------------------------
        # Optical stage. Use the PSF convolution. If False, will use the MTF
        self.do_psf_conv = False
        # Detection stage errors and effects
        self.apply_prnu = False
        self.apply_dark_signal = False
        self.apply_bad_dead = False

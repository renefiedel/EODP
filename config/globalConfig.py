
# GLOBAL CONFIGURATION FILE
# Configuration parameters that affect more than one module of the simulator

class globalConfig:

    def __init__(self):

        # Auxiliary files
        self.logconfigfile = 'logging.conf'

        # bands
        self.bands = ['VNIR-0','VNIR-1','VNIR-2','VNIR-3']

        # Name of the scene (output of the SGM)
        self.scene = 'sgm_toa.nc'

        # Name of the GM outputs
        self.gm_geoloc = 'geolocation.nc'
        self.gm_orbit = 'real_orbit.xml' # EOCFI format

        # Name of the TOA outputs of the ISM. attaches BAND + NC extension
        self.ism_toa = 'ism_toa_' # [DN] Digital numbers, output of the of the ISM
        self.ism_toa_isrf = 'ism_toa_isrf_' # [mW/m2/sr] Radiances. Intermediate output after the spectral integration and ISRF
        self.ism_toa_optical = 'ism_toa_optical_' # [mW/m2] Irradiances. Intermediate output after the optical stage
        self.ism_toa_e = 'ism_toa_e_' # [e-] Electrons. Intermediate output after the Detection stage - Photons to Electrons
        self.ism_toa_prnu = 'ism_toa_prnu_' # [e-] Electrons. Intermediate output after the Detection stage - PRNU
        self.ism_toa_ds = 'ism_toa_ds_' # [e-] Electrons. Intermediate output after the Detection stage - Dark signal
        self.ism_toa_detection = 'ism_toa_detection_' # [e-] Digital numbers. Intermediate output after the Detection stage (after bad/dead pix)
        self.ism_toa_vcu = 'ism_toa_vcu_' # [DN] Digital numbers. Intermediate output after the Video Control Unit

        # Name of the TOA outputs of the L1B
        self.l1b_toa = "l1b_toa_" # [mW/m2/sr] Radiances. Output of the L1B
        self.l1b_toa_eq = "l1b_toa_eq_" # [DN] TOA after equalization

        # Name of the TOA outputs of the L1C
        self.l1c_toa = "l1c_toa_" # [mW/m2/sr] Radiances. Output of the L1C

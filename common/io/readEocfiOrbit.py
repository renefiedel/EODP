# Read an EOCFI orbit file

from xml.dom.minidom import parse
import numpy as np

def readEOCFIOrbit(eocfiorbitfile):
    """
    Reads an EOCFI orbit file
    :param eocfiorbitfile: input XML filename
    :return: pos and vel. Numpy arrays of the size Number of orbit positions x 3
    Units: [m] and [m/s]
    """
    # parse an XML file by name
    dom = parse(eocfiorbitfile)

    # Read variables
    nameX = dom.getElementsByTagName("X")[:]
    nameY = dom.getElementsByTagName("Y")[:]
    nameZ = dom.getElementsByTagName("Z")[:]
    nameVX = dom.getElementsByTagName("VX")[:]
    nameVY = dom.getElementsByTagName("VY")[:]
    nameVZ = dom.getElementsByTagName("VZ")[:]

    norb = len(nameX)
    pos = np.zeros((norb,3))
    vel = np.zeros((norb,3))

    for iorb in range(norb):
        pos[iorb,0] = float(nameX[iorb].firstChild.data) # [m]
        pos[iorb,1] = float(nameY[iorb].firstChild.data)
        pos[iorb,2] = float(nameZ[iorb].firstChild.data)
        vel[iorb,0] = float(nameVX[iorb].firstChild.data) # [m/s]
        vel[iorb,1] = float(nameVY[iorb].firstChild.data)
        vel[iorb,2] = float(nameVZ[iorb].firstChild.data)

    return pos, vel

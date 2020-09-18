import math
import numpy as np
import pyproj

def haversine(lat1, lon1, lat2, lon2):
    """
    Compute the geodetic distance on ground
    :param lat1: Latitude of the first point
    :param lon1: Longitude of the first point
    :param lat2: Latitude of the second point
    :param lon2: Longitude of the second point
    :return: Distance between two points [m]
    """
    R = 6378137 # [m] WGS84 Equatorial radius

    phi1 = math.radians(lat1)
    phi2 = math.radians(lat2)

    dphi       = np.abs(math.radians(lat2 - lat1))
    dlambda    = np.abs(math.radians(lon2 - lon1))

    a = math.sin(dphi/2)**2 + \
        math.cos(phi1)*math.cos(phi2)*math.sin(dlambda/2)**2

    res = 2*R*math.atan2(math.sqrt(a), math.sqrt(1 - a)) # m

    return res

ecef = pyproj.Proj(proj='geocent', ellps='WGS84', datum='WGS84') # not sure if this is geodetic
lla = pyproj.Proj(proj='latlong', ellps='WGS84', datum='WGS84')

def ecef2geo(pos):
    '''
    Conversion of ECEF to geodetic
    :param pos: 3x1 vector of ECEF in meters
    :return: Geodetic coordinates in degrees and meters
    '''
    lon, lat, alt = pyproj.transform(ecef, lla, pos[0], pos[1], pos[2], radians=False)
    return lat, lon, alt # [deg]

def geo2ecef(lat, lon, alt):
    '''
    Conversion of geodetic coordinates to ECEF
    :param lat: Latitude in degrees
    :param lon: Longitude in degrees
    :param alt: Altitude in meters - TBC
    :return:3x1 vector of ECEF in meters
    '''
    pos = np.zeros(3)
    pos[0], pos[1], pos[2] = pyproj.transform(lla, ecef, lon, lat, alt, radians=False)
    return pos # [m]


def earthRadiusAtLatitude(lat):
    '''
    Calculates the Earth radius for a given latitude\
    Source:
    https://stackoverflow.com/questions/56420909/calculating-the-radius-of-earth-by-latitude-in-python-replicating-a-formula
    :param lat: input latitude in [deg]
    :return: Earth radius [m]
    '''

    B = math.radians(lat) #converting into radians
    a = 6378137  # [km] Radius at sea level at equator WGS84
    b = 6356752.314245  # [km] Radius at poles WGS84
    c = (a**2*math.cos(B))**2
    d = (b**2*math.sin(B))**2
    e = (a*math.cos(B))**2
    f = (b*math.sin(B))**2
    R = math.sqrt((c+d)/(e+f))

    return R # [m]

def getOrbitAltitude(pos):
    '''
    For an orbit state vector, calculates the orbit altitude
    :param pos: array with the orbit positions of norb x 3
    :return: orbit altitude in meters
    '''

    # Read the orbit
    norb = pos.shape[0]
    alt = np.zeros(norb)
    for iorb in range(norb):
        alt[iorb] = np.linalg.norm(pos[iorb,:]) # [m]
    orbit_radius = np.mean(alt) # [m]

    # Get Earth radius at the latitude of interest
    lat, lon, alt = ecef2geo(pos[0,:])
    R = earthRadiusAtLatitude(lat) # [m]

    # Subtract the Earth radius
    orbit_altitude = orbit_radius - R
    print('Orbit altitude ' + str(orbit_altitude/1000) + ' [km]')

    return orbit_altitude # [m]


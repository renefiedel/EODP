
# Auxiliary functions

def getIndexBand(band):
    '''
    Given a bandname like 'VNIR-0' returns the index '0'
    :param band: bandname
    :return: index
    '''
    return int(band[-1])

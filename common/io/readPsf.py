import os.path
import numpy as np
import sys

def readPsf(filename):
        
    psf = []
    if not os.path.isfile(filename):
        sys.exit('File not found ' +filename + ". Exiting.")
    
    fid = open(filename, 'r')
    #next(fid) # skip first line
    for line in fid:
        line = line.strip()
        columns = line.split()
        psf.append(float(columns[0]))
   
    fid.close()
    print("Finished reading " + filename)
    return np.array(psf) 
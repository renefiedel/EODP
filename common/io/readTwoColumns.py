import os.path
import numpy as np
import sys

def readTwoColumns(filename):
        
    col1 = []
    col2 = []
    
    if not os.path.isfile(filename):
        sys.exit('File not found ' +filename + ". Exiting.")
    
    fid = open(filename, 'r')
    
    #next(fid) # skip first line
    
    for line in fid:
        line = line.strip()
        columns = line.split()
        col1.append(float(columns[0]))
        col2.append(float(columns[1]))
   
    fid.close()
    print("Finished reading " + filename)
    
    col1 = np.array(col1)
    col2 = np.array(col2)
    
    print("Size of the columns " + str(col1.size))
    
    return col1, col2
#import sys
import os

def fileExists(filename):
    return os.path.exists(filename)

def addFileSep(dirname):
    if dirname[-1] != os.path.sep:
        return dirname + os.path.sep
    else:
        return dirname

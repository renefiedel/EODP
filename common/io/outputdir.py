# Check if the output dir exists, and if not create it

import os

def mkdirOutputdir(outputdir):

    if os.path.isdir(outputdir):
        return
    else:
        try:
            os.mkdir(outputdir)
        except OSError:
            print("Creation of the directory %s failed" % outputdir)
        else:
            print("Successfully created the directory %s " % outputdir)
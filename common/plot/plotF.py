import matplotlib.pyplot as plt
import numpy as np
import os

def plotF(x, y, title_str, xlabel_str, ylabel_str, directory, saveas_str):

    # Diff and plot
    fig = plt.figure(figsize=(10, 7))

    x = np.array(x)  # In case they are not numpy arrays, convert them to those
    y = np.array(y)

    if x.size>0 and y.size>0:
        plt.plot(x, y, '-r')
    elif x.size == 0:
        plt.plot(y, '-r')
    elif y.size == 0:
        plt.plot(x, '-r')

    plt.title(title_str, fontsize=20)
    plt.xlabel(xlabel_str, fontsize=16)
    plt.ylabel(ylabel_str, fontsize=16)
    plt.grid()
    savestr = directory + os.path.sep + saveas_str
    plt.savefig(savestr)
    plt.close(fig)
    print("Saved image " + savestr)

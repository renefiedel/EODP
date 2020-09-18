import matplotlib.pyplot as plt
import os

def plotMat2D(mat, title_str, xlabel_str, ylabel_str, directory, saveas_str):
    
    fig, ax = plt.subplots(figsize=(20, 10))
    pos = ax.imshow(mat, cmap='jet', origin='lower')
    fig.colorbar(pos, ax=ax)# add the colorbar
    plt.title(title_str, fontsize=20)    
    plt.xlabel(xlabel_str, fontsize=16)
    plt.ylabel(ylabel_str, fontsize=16)
    plt.axis('equal')
    plt.savefig(directory + os.path.sep + saveas_str +'.png')
    plt.close(fig)

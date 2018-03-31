import ctypes as c
import glob
import numpy as np
import matplotlib
import matplotlib.pyplot as plt
import os.path
import seaborn as sns
matplotlib.style.use("ggplot")

colors = ["#6d0410", "#b5636d", "#757575",
          "#001377", "#6f7dc6", "#757575",
          "#007a35", "#69ce95", "#757575",
          "#6d7500", "#acb259", "#757575",
          "#74007c", "#c260c9" "#757575"]

#
# Result files
#

def split_name(f):
    name = os.path.basename(f)
    comp, ver = name.split("__")
    return comp, ver

#
# Single Precision
#
data = {}
files = glob.glob("../results/float/*.dat")
for f in files:
    results = {}
    names = np.loadtxt(f, usecols = (0), dtype = str)
    times = np.loadtxt(f, usecols = (1, 2, 3))

    for n in set(names):
        results[n] = np.zeros((0, 3))

    for i, n in enumerate(names):
        results[n] = np.append(results[n], times[i, :].reshape(1, -1), axis = 0)

    data[f] = results

n_files = len(files)

n_ax_v = (n_files // 2) + 1
n_ax_h = np.minimum(2, n_files)
fig, axs = plt.subplots(n_ax_v, n_ax_h, figsize = (n_ax_h * 4, n_ax_v * 4))
axs = np.array([axs]).reshape(-1, 2)

t_max = 0.0
for f in files:
    results = data[f]["Standard"]
    t_max = np.maximum(t_max, results[0, 1])

for i, f in enumerate(files):
    ax = axs[i // 2, i % 2]
    ax.xaxis.grid(False)

    comp, ver = split_name(f)
    ax.set_title(comp + " (" + ver[:-4] + ")")
    # IEEE
    results = data[f]["IEEE"]
    n = results.shape[0]
    width = 1.0 / n
    x = np.linspace(0, 1.0, (n + 1))[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 0])

    x_ticks = x
    labels  = ["IEEE, {0}".format(int(d)) for d in results[:, 0]]

    # Product
    offset = 1.1
    results = data[f]["Product"]
    n = results.shape[0]
    width = 1.0 / n
    x = np.linspace(offset, offset + 1.0, (n + 1))[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 1])

    x_ticks = np.append(x_ticks, x)
    labels  += ["Product, {0}".format(int(d)) for d in results[:, 0]]

    # Standard
    offset = 2.2
    results = data[f]["Standard"]
    width = 1.0 / n
    x = np.linspace(offset, offset + 1.0, 2)[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 2])

    x_ticks = np.append(x_ticks, x)
    labels  += ["Std. Lib."]

    ax.set_ylim([1.0, t_max])
    ax.set_yscale("log")
    ax.set_xticks(x_ticks)
    ax.set_xticklabels(labels, rotation = 45)


for i in range(i + 1, n_ax_v * n_ax_h):
    ax = axs[i // 2, i % 2]
    ax.axis("off")
    ax.axis("off")

plt.tight_layout()
fig.savefig("/home/simon/build/fastexp/plots/single_precision.png",
            bbox_inches = "tight")

#
# Double Precision
#

data = {}
files = glob.glob("../results/double/*.dat")
for f in files:
    results = {}
    names = np.loadtxt(f, usecols = (0), dtype = str)
    times = np.loadtxt(f, usecols = (1, 2, 3))

    for n in set(names):
        results[n] = np.zeros((0, 3))

    for i, n in enumerate(names):
        results[n] = np.append(results[n], times[i, :].reshape(1, -1), axis = 0)

    data[f] = results

n_files = len(files)

n_ax_v = (n_files // 2) + 1
n_ax_h = np.minimum(2, n_files)
fig, axs = plt.subplots(n_ax_v, n_ax_h, figsize = (n_ax_h * 4, n_ax_v * 4))
axs = np.array([axs]).reshape(-1, 2)

t_max = 0.0
for f in files:
    results = data[f]["Standard"]
    t_max = np.maximum(t_max, results[0, 1])

for i, f in enumerate(files):
    ax = axs[i // 2, i % 2]
    ax.xaxis.grid(False)

    comp, ver = split_name(f)
    ax.set_title(comp + " (" + ver[:-4] + ")")
    # IEEE
    results = data[f]["IEEE"]
    n = results.shape[0]
    width = 1.0 / n
    x = np.linspace(0, 1.0, (n + 1))[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 0])

    x_ticks = x
    labels  = ["IEEE, {0}".format(int(d)) for d in results[:, 0]]

    # Product
    offset = 1.1
    results = data[f]["Product"]
    n = results.shape[0]
    width = 1.0 / n
    x = np.linspace(offset, offset + 1.0, (n + 1))[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 1])

    x_ticks = np.append(x_ticks, x)
    labels  += ["Product, {0}".format(int(d)) for d in results[:, 0]]

    # Standard
    offset = 2.2
    results = data[f]["Standard"]
    width = 1.0 / n
    x = np.linspace(offset, offset + 1.0, 2)[:-1]
    ax.bar(x, results[:, 1], yerr = results[:, 2],
            width = 0.8 * width, color = colors[3 * i + 2])

    x_ticks = np.append(x_ticks, x)
    labels  += ["Std. Lib."]

    ax.set_ylim([1.0, t_max])
    ax.set_yscale("log")
    ax.set_xticks(x_ticks)
    ax.set_xticklabels(labels, rotation = 45)


for i in range(i + 1, n_ax_v * n_ax_h):
    ax = axs[i // 2, i % 2]
    ax.axis("off")
    ax.axis("off")

plt.tight_layout()
fig.savefig("/home/simon/build/fastexp/plots/double_precision.png",
            bbox_inches = "tight")
#
# Double Precision
#

plt.show()

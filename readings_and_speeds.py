import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

sns.set_style("darkgrid")

data = pd.read_csv("readings_and_speeds.csv", usecols=[0,1,3,4])
data["time"] = data.index / 100
data = data.dropna()

fig, ax = plt.subplots(figsize=(15,5))

ax.scatter(data["time"], data["left_ir"], color='black', s=2, alpha=0.4, label="Left IR Sensor")

ax.scatter(data["time"], data["right_ir"], color='red', s=2, alpha=0.4, label="Right IR Sensor")

ax2 = ax.twinx()

ax2.scatter(data["time"], data["left_motor"], s=1, label="Left Motor")

ax2.scatter(data["time"], data["right_motor"], s=1, alpha=0.1, label="Right Motor")

ax.set_title("Readings and Speeds of IR Car")

ax.set_xlabel("Time (s)")
ax.set_ylabel("IR Reading")
ax2.set_ylabel("Motor Output")

fig.legend()

plt.savefig("images/readings_and_speeds.png")
plt.savefig("images/readings_and_speeds.svg")
plt.show()
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
import seaborn as sns

sns.set_style("darkgrid")

tape_readings = pd.read_csv("ir_calibration_tape.csv")
floor_readings = pd.read_csv("ir_calibration_floor.csv")

fig, ax = plt.subplots(figsize=(15,3))

ax.plot(tape_readings["reading"], tape_readings["reading"]*0,
	"ko", alpha=0.4, label="tape")

ax.plot(floor_readings["reading"], floor_readings["reading"]*0,
	"bo", alpha=0.4, label="floor")

print("Tape readings:")
print(tape_readings.describe())
print("Floor readings:")
print(floor_readings.describe())

fig.legend()
ax.axes.get_yaxis().set_visible(False)

ax.set_title("Tape and Floor Infrared Sensor Readings")
ax.set_xlabel("IR Reading (float)")

fig.savefig("images/ir_calibration.png")
fig.savefig("images/ir_calibration.svg")
plt.show()
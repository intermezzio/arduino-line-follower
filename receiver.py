import serial
import sys
import time

# set ports and other constants for collecting data
ARDUINO_COM_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600
SERIAL_PORT = serial.Serial(ARDUINO_COM_PORT, BAUD_RATE, timeout=1)

if __name__ == "__main__":
	assert len(sys.argv) > 2, "Specify the file and data to collect"

	fname = sys.argv[1] + ".csv"
	colnames = sys.argv[2:]

	with open(fname, "w") as outfile:
		outfile.write(",".join(colnames) + "\n")

	while True:
		data = SERIAL_PORT.readline().decode()

		# if data has been sent via Serial
		if len(data):
			with open(fname, "a") as outfile:
				outfile.write(",".join(data.split()) + "\n")

		# time.sleep(50)
import serial

# set ports and other constants for collecting data
ARDUINO_COM_PORT = "/dev/ttyACM0"
BAUD_RATE = 9600
SERIAL_PORT = serial.Serial(ARDUINO_COM_PORT, BAUD_RATE, timeout=1)

speed = 1

while speed != 0:
	speed = int(input("Choose a speed from 1-32, or type '0' to stop."))
	if 0 <= speed <= 32:
		SERIAL_PORT.write(bytes(str(speed), 'utf-8'))
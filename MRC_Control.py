import serial
import time
ser = serial.Serial('COM7', 9600, timeout=2)
print(f"Connected to {ser.port}")
try:
    ser.reset_input_buffer()
    while True:
        print("-" * 30)
        command = input("Enter command to send (or 'quit' to exit): ")
        if command.lower() == 'quit':
            break
        command_with_newline = command + '\n'
        ser.write(command_with_newline.encode('utf-8'))
        response_bytes = ser.readline()
        if response_bytes:
            response = response_bytes.decode('utf-8')
            print(f"Received: {response}")
        else:
            print("Received no response within the timeout period.")
except KeyboardInterrupt:
    print("Exiting.")
finally:
    ser.close()
    print("Serial port closed.")
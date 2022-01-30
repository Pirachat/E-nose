#!/usr/bin/env python3
import json
import os
import time
from datetime import datetime

import serial  # conda install pyserial

PORT = "COM3"
BAUDRATE = 9600
RAW_DIR = "../dataset/raw/raw_data_air"
RAW_FILE_PREFIX = "raw_data_air_5"

if __name__ == '__main__':
    ser = serial.Serial(PORT, BAUDRATE, timeout=1)
    # ser.flushInput()
    ser.reset_input_buffer()
    dc = dict()
    file_name = f'{os.path.join(RAW_DIR,RAW_FILE_PREFIX)}_{datetime.now().strftime("%Y_%m_%dT%H%M%S")}.json'
    if not os.path.exists(RAW_DIR):
        os.makedirs(RAW_DIR)
    with open(file_name, 'w') as f:
        while True:
            try:
                if ser.in_waiting > 0:
                    line = ser.readline().decode('utf-8').rstrip()
                    dc['tsm_ns'] = time.time_ns()
                    dc['sensors'] = line
                    f.write(json.dumps(dc))
                    f.write('\n')
                    print(line)
            except KeyboardInterrupt:
                print("Keyboard Interrupt")
                break

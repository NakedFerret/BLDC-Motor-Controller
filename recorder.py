import serial
import struct
import argparse

parser = argparse.ArgumentParser(description='Recorder: Record voltage readings.')

parser.add_argument('port', help='which port to listen to')
parser.add_argument('baud', type=int, help='baud rate of the port')

args = parser.parse_args()

print 'Recorder: Listening to %s with baud rate: %d' % (args.port, args.baud)
port = serial.Serial(args.port, baudrate=args.baud)

print 'Recorder: Listening for start'

readings = list(range(5000))

count = 0
while(True):

  if count >= 10:
    break

  text = port.readline()

  if text.strip() == 'A':
    print 'Found one of %d' % count
    count = count + 1

print 'Recorder: Sending start signal'

port.write('A');
port.flush();

count = 0
while(True):
  if count >= 5000:
    break

  info = port.read(24)
  timeValue = struct.unpack('>L', info[1:5])[0]
  # unpacking from short cause Uno uses 2 bytes for ints
  sensor0Value = struct.unpack('>h', info[6:8])[0]
  sensor1Value = struct.unpack('>h', info[9:11])[0]
  sensor2Value = struct.unpack('>h', info[12:14])[0]
  sensor3Value = struct.unpack('>h', info[15:17])[0]
  sensor4Value = struct.unpack('>h', info[18:20])[0]
  sensor5Value = struct.unpack('>h', info[21:23])[0]

  readings[count] = (count, timeValue, sensor0Value, sensor1Value, sensor2Value, sensor3Value, sensor4Value, sensor5Value)
  count = count + 1

for r in readings:
  print "%d,%d" % r[1:3]

port.close() 

import serial
import struct
import argparse

parser = argparse.ArgumentParser(description='Byte Record voltage readings.')

parser.add_argument('port', help='which port to listen to')
parser.add_argument('baud', type=int, help='baud rate of the port')

args = parser.parse_args()

print 'Byte Recorder: Listening to %s with baud rate: %d' % (args.port, args.baud)
port = serial.Serial(args.port, baudrate=args.baud)

print 'Byte Recorder: Listening for start'

count = 0
while(True):

  if count >= 10:
    break

  text = port.readline()

  if text.strip() == 'A':
    print 'Found one of %d' % count
    count = count + 1

print 'Byte Recorder: Sending start signal'

port.write('A');
port.flush();

count = 0;
while(True):
  if count > 2**32:
    break

  info = port.read(10)
  timeValue = struct.unpack('>L', info[1:5])[0]
  # unpacking from short cause Uno uses 2 bytes for ints
  sensor0Value = struct.unpack('>h', info[8:10])[0]

  print map(bin, bytearray(info))
  print (timeValue, sensor0Value)
  print count
  count = count + 1

port.close()     

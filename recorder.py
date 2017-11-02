import serial
import argparse

parser = argparse.ArgumentParser(description='Record voltage readings.')

parser.add_argument('port', help='which port to listen to')
parser.add_argument('baud', type=int, help='baud rate of the port')

args = parser.parse_args()

print 'Listening to %s with baud rate: %d' % (args.port, args.baud)
port = serial.Serial(args.port, baudrate=args.baud)

print 'Waiting for input'

while(True):
  text = port.readline();
  print text

print 'Ready to run..'

port.close()     

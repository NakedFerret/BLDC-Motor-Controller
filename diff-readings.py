import argparse

parser = argparse.ArgumentParser(description='Parse voltage readings and show diff in time between readings.')

parser.add_argument('file', help='which file to parse')

args = parser.parse_args()

f = open(args.file)

last = 0;
for l in f:
  if l.startswith('Recorder:'):
    continue

  if not l.strip():
    continue

  currentTime = l.split(',')[:1]

  if not currentTime:
    continue

  currentTime = currentTime[0]

  if (last == 0):
    last = currentTime
    continue

  diff = int(currentTime) - int(last)

  print "%d  %s" % (diff, l.strip())

  last = currentTime

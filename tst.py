def run(args):
  assert len(args) == 0
  import ccp4io_adaptbx
  ccp4io_adaptbx.MMDBManager()
  print "OK"

if (__name__ == "__main__"):
  import sys
  run(args=sys.argv[1:])

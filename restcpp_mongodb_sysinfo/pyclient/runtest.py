import sys
from systemdata.systeminfo import device
from rest.register import registerdevice
from unittest import testpulishdata
def register():
    registerdevice.register(None,"amitabh.modak@outlook.com", device.getmac(None))
    pass

def executeTest():
    #try:
        register()
        key = registerdevice.issuetoken(None, "amitabh.modak@outlook.com", device.getmac(None))
        print("Key "+key)
        test = testpulishdata(key)
        test.testmemory()
        test.testcpu()
        test.testprocess()
   # except:
        #print("Unexpected error:", sys.exc_info()[0])


executeTest()


import sys
from systemdata.systeminfo import device
from rest.sendCpu import publishcpu
from rest.sendMemory import publishmemory
from rest.sendProcess import publishprocess
from rest.register import registerdevice
from processtimer import helperprocess
from unittest import testpulishdata

def register():
    registerdevice.register(None,"amitabh.modak@outlook.com", device.getmac(None))
    pass

def monitor():
    try:
        key = registerdevice.issuetoken(None, "amitabh.modak@outlook.com")
        cpuUsage =  device.getCpu(None)
        memoryUsage = device.getMemoryUsage(None)
        processNamelist = device.getProcessName(None)
        print(publishprocess.publish(None,key,processNamelist))
        print(publishmemory.publish(None,key, memoryUsage))
        print(publishcpu.publish(None, key, cpuUsage))
    except:
        print("Unexpected error:", sys.exc_info()[0])
        pass

def startmonitor():
    try:
        register()
    except:
        print("Unexpected error:", sys.exc_info()[0])
    process = helperprocess(5000, monitor)
    process.start()
    pass

startmonitor()

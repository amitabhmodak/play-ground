import sys
from systemdata.systeminfo import device
from rest.sendCpu import publishcpu
from rest.sendMemory import publishmemory
from rest.sendProcess import publishprocess
from rest.register import registerdevice

class testpulishdata:
    def __init__(self, clientid):
        self.clientid = clientid
        pass

    def testcpu(self):
        print("Running cpu test")
        cpu = publishcpu()
        self.verify(cpu.publish(self.clientid, -1), 400)
        self.verify(cpu.publish(self.clientid, 19), 200)
        self.verify(cpu.publish(self.clientid, 0), 200)
        self.verify(cpu.publish("", -1), 400)
        self.verify(cpu.publish("xyz", 19), 400)
        pass

    def testmemory(self):
        print("Running memory test")
        memory = publishmemory()
        self.verify(memory.publish(self.clientid,-1),400)
        self.verify(memory.publish(self.clientid, 19), 200)
        self.verify(memory.publish(self.clientid, 0), 200)
        self.verify(memory.publish("", -1), 400)
        self.verify(memory.publish("xyz", 19), 400)


    def testprocess(self):
        print("Running process test")
        process = publishprocess()
        processNamelist = device.getProcessName(None)

        self.verify(process.publish(self.clientid, processNamelist), 200)
        processNamelist.clear()
        self.verify(process.publish(self.clientid, processNamelist), 400)
        self.verify(process.publish("", processNamelist), 400)
        self.verify(process.publish("xyz", processNamelist), 400)
        pass
        pass

    def verify(self,value, expected):
        if (value == expected):
            print ("Success " + str(value) + " "+str(expected))
        else:
            print ("Fail " + str(value) + " "+str(expected))
        pass


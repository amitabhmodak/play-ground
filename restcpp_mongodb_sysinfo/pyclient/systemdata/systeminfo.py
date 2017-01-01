import psutil
from uuid import getnode as get_mac
class device:
    def getCpu(self):
        usage = psutil.cpu_percent(None)
        return  usage
        pass

    def getMemoryUsage(self):
        mem = psutil.virtual_memory()
        return mem.percent
    pass

    def getProcessName(self):
        list = []
        for proc in psutil.process_iter():
            try:
                pinfo = proc.as_dict(['name'])
            except psutil.NoSuchProcess:
                pass
            else:
                list.append(pinfo['name'])
        return list
    pass

    def getmac(self):
        mac = get_mac()
        return hex(mac)
        pass


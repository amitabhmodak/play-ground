import requests
import json
class publishmemory:
    def publish(self, clientid, memoryUsage):
        data = {}
        data['clientkey'] = str(clientid)
        data['memoryusage'] = memoryUsage
        r = requests.post("http://localhost:8080/postMemory", json=data)
        return r.status_code
    pass
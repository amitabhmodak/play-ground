import requests
import json
class publishprocess:
    def publish(self, clientid, processList):
        data = {}
        data['clientkey'] = str(clientid)
        data['processlist'] = processList
        r = requests.post("http://localhost:8080/postProcess", json=data)
        return r.status_code
    pass
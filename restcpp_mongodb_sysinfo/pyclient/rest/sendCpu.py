import requests

class publishcpu:
    def publish(self, clientid, cpuUsage):
        data = {}
        data['clientkey'] = str(clientid)
        data['cpuusage'] = cpuUsage
        r = requests.post("http://localhost:8080/postCpu", json=data)
        return r.status_code
    pass
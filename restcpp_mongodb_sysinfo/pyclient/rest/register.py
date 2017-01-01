import requests
import json
class registerdevice:
    def register(self, email, macaddress):
        data = {}
        data['email'] = email
        data['macaddress'] = macaddress
        r = requests.post("http://localhost:8080/registerDevice", json=data)
        print(r.status_code)
        print(r.json())
        return r.status_code
    pass

    def issuetoken(self, email, key):
        data = {}
        payload = {'email': email, 'macaddress':key}
        r = requests.get("http://localhost:8080/issueToken", params=payload)
        return r.text
    pass
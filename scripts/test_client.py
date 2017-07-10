import cjson
import random


class TestClient(object):
    def __init__(self):
        self.client_ids = ["test1", "test2", "test3"]
        self.stocks = ["IBM", "APPL", "MSFT", "AMZN"]
        self.mssg_type = "update"
        #field types:  1-string, 2-int, 3-float, 4-bool
        return

    def run(self):
        while True:
            dic = {}
            dic['clientId'] = random.choice(self.client_ids)
            dic['mssgType'] = self.mssg_type
            fv = {}
            fv['stock'] = {'type': 1, 'value': random.choice(self.stocks)} 
            fv['qty'] = {'type': 2, 'value': random.randint(1, 1000)}
            fv['px'] = {'type': 3, 'value': 100 + random.gauss(0, 10)}
            dic['fieldValues'] = fv
            print cjson.encode(dic)
        return

def main():
    c = TestClient()
    c.run()

if __name__ == '__main__':
    main()

import requests

def get():
    url = 'http://192.168.0.101:8080/historicoCupCarro/get'

    headers = {}

    aluno_data = {}

    response = requests.get(url=url, json=aluno_data, headers=headers)
    print("Status get: ",response.status_code)
    response_data = response.json()
    print(response_data)
    
def post(comodo, numComodo):

    url = 'http://192.168.0.101:8080/historicoCupCarro/post'

    headers = {
    "Content-Type": "application/json"
    }

    historico_data = {
        "classe": comodo,
        "numClasse": numComodo,
    }

    response = requests.post(url=url, json=historico_data, headers=headers)
    print("Status post: ", response.status_code)

if __name__ == '__main__':
    post("person", 0)
    get()
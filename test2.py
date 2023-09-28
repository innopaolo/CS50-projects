from requests import Request, Session
from requests.exceptions import ConnectionError, Timeout, TooManyRedirects
import json

url = 'https://pro-api.coinmarketcap.com/v1/cryptocurrency/map'
parameters = {
  'start':'1',
  'limit':'5000',

}
headers = {
  'Accepts': 'application/json',
  'X-CMC_PRO_API_KEY': '885c87e7-835a-4035-831b-8fd9d00db130',
}

session = Session()
session.headers.update(headers)

try:
  response = session.get(url, params=parameters)
  data = json.loads(response.text)
  coins = data['data']
  for x in coins:
    print(x['id'], x['name'], x['symbol'])
except (ConnectionError, Timeout, TooManyRedirects) as e:
  print(e)
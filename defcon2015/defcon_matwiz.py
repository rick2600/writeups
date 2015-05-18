import socket

def connect():
  s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
  s.connect(('mathwhiz_c951d46fed68687ad93a84e702800b7a.quals.shallweplayaga.me', 21249))
  return s

s = connect()

while True:
  data = s.recv(4096)
  if "=" not in data:
    print data
    break

  oper = data[0:-2]

  print oper

  oper = oper\
  .replace("[", "(")\
  .replace("]", ")")\
  .replace("{","(") \
  .replace("}", ")")\
  .replace("THREE", "3")\
  .replace("TWO", "2")\
  .replace("ONE", "1")\
  .replace("^", "**")

  res = eval(oper)
  s.sendall(str(res) + "\n")


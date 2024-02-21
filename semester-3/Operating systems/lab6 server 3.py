
from socket import *

host = 'localhost'
port = 777
addr = (host, port)


tcp_socket = socket(AF_INET, SOCK_STREAM)
tcp_socket.bind(addr)
tcp_socket.listen(1)

print('waiting for connection...')
conn, addr = tcp_socket.accept()
print('client address: ', addr)

while True:

    data = conn.recv(1024)

    if not data:
        conn.close()
        break
    else:
        print(data)
        conn.send(b'Response from server')


    question = input('Do you want to quit? y\\n: ')
    if question == 'y':
        break
    print('waiting for connection...')

conn.close()
tcp_socket.close()
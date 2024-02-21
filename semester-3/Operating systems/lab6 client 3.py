from socket import *
import sys

host = 'localhost'
port = 777
addr = (host,port)

tcp_socket = socket(AF_INET, SOCK_STREAM)
tcp_socket.connect(addr)

while True:
    data = input('write to server: ')
    if not data : 
        tcp_socket.close() 
        sys.exit(1)


    data = str.encode(data)
    tcp_socket.send(data)
    print(data)
    question = input('Send another message? y\\n: ')
    if question == 'n':
        break


tcp_socket.close()

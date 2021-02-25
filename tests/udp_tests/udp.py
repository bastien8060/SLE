import time
import socket
from time import sleep

for pings in range(10):
    client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    client_socket.settimeout(1.0)
    message = b"@[circle]{r:50;c:10,56;}\n@@@"
    addr = ("127.0.0.1", 6770)

    start = time.time()
    client_socket.sendto(message, addr)
    try:
        text = "";
        fulltext = "";
        i=1
        while "@@@" not in text:
            data, server = client_socket.recvfrom(1024)
            #print(text)
            print("\nReceived Part "+str(i)+"\n");
            text = data.decode();
            if "@@@" not in text:
                fulltext += text;
            end = time.time()
            elapsed = end - start
            i += 1
        i = 0
            #print(f'{data}')
        print(fulltext);
        for kv in fulltext.split(","):
            print(kv.strip("[").strip("]").split("&"))
        #print(key, value)
        sleep(0.016)

    except socket.timeout:
        print('REQUEST TIMED OUT')
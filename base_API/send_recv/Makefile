send_recv:send.cpp recv.cpp
	g++ -o send send.cpp  -lpthread
	g++ -o recv recv.cpp  -lpthread
	./recv 192.168.186.128 5000 && ./send 192.168.186.128 5000
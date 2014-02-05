#include <iostream>

#include "../TCPSocket.hh"

using namespace std;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    cerr << "Usage: ./app hostname port\n";
    return 1;
  }

  cout << "Creating INET socket" << endl;
  /* Switch IPV4 to IPV6 if you want to use it instead */
  TCPSocket socket(IPV4);
  cout << "Connection to "<< argv[1] << ":" << argv[2] << endl;
  if (socket._connect(argv[1], stoi(argv[2])) != 0) {
    cerr << "Failed to connect to host!\n";
    return 1;
  }

  cout << "Hostname: " << socket._getHostname() << endl;
  cout << "Creating data string" << endl;
  string data;
  data.resize(1024);
  cout << "Input data to send:" << endl;
  fgets(&data[0], 1024, stdin);
  cout << "Sending data" << endl;
  socket._send(data);
  cout << "Receiving data" << endl;
  data = socket._recv(1024);
  cout << "Received data:\"" << data << "\"" << endl;
  cout << "Closing socket" << endl;
  socket._close();
  cout << "Done - Exiting" << endl;
  return 0;
}

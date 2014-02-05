#include <iostream>

#include "../TCPSocket.hh"

using namespace std;

int main() {
  cout << "Creating a INET4 TCP Socket" << endl;
  /* Switch IPV4 to IPV6 if you want to use it instead */
  TCPSocket socket(IPV4);
  cout << "Settings SO_REUSEADDR to 1" << endl;
  socket._reuseAddr(1);
  cout << "Binding on port 1337" << endl;
  if (socket._bind(1337) != 0) {
    return 1;
  }

  cout << "Settings listenqueue to 10" << endl;
  if (socket._listen(10) != 0) {
    return 1;
  }

  for (;;) {
    cout << "Waiting for connection" << endl;
    TCPSocket *client = socket._accept();
    if (client == NULL) {
      cout << "Error while accepting - Exiting" << endl;
      return 1;
    }
    cout << "Received connection from " << client->_getHostname() << endl;
    cout << "Receiving data" << endl;
    string data = client->_recv(1024);
    cout << "Sending data" << endl;
    client->_send(data);
    cout << "Closing connection" << endl;
    client->_close();
    cout << "Freeing client socket" << endl;
    delete client;
    cout << "Data received:\"" << data << "\"" << endl;
  }
  cout << "Closing server socket" << endl;
  socket._close();
  cout << "Exiting" << endl;
  return 0;
}

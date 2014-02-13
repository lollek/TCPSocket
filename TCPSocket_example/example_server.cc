#include <iostream>

#include "../TCPSocket.hh"

using namespace std;

int main() {
  cout << "Creating a INET4 TCP Socket" << endl;
  /* Switch IPV4 to IPV6 if you want to use it instead */
  TCPSocket socket(IPV4);
  cout << "Settings SO_REUSEADDR to 1" << endl;
  socket.reuseAddr(1);
  cout << "Binding on port 1337" << endl;
  if (socket.bind(1337) != 0) {
    return 1;
  }

  cout << "Settings listenqueue to 10" << endl;
  if (socket.listen(10) != 0) {
    return 1;
  }

  for (;;) {
    cout << "Waiting for connection" << endl;
    TCPSocket *client = socket.accept();
    if (client == NULL) {
      cout << "Error while accepting - Exiting" << endl;
      return 1;
    }
    cout << "Received connection from " << client->getHostname() << endl;
    cout << "Receiving data" << endl;
    string data = client->recv(1024).data();
    cout << "Sending data" << endl;
    client->send(data);
    cout << "Closing connection" << endl;
    client->close();
    cout << "Freeing client socket" << endl;
    delete client;
    cout << "Data received:\"" << data << "\"" << endl;
  }
  cout << "Closing server socket" << endl;
  socket.close();
  cout << "Exiting" << endl;
  return 0;
}

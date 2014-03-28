#include <string>

#include <gtest/gtest.h>

#include "../TCPSocket.hh"

using namespace std;

TEST(Constructors, all) {
  TCPSocket server(IPV4);
  ASSERT_EQ(server.getLastError(), string());
  server.close();
  server.close();

  ASSERT_EQ(server.bind(1337), 0);
  server.close();
  server.close();

  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  server.close();
  server.close();

  TCPSocket server2(server);
  ASSERT_EQ(server2.getLastError(), string());
  server2.close();
  server2.close();

  ASSERT_EQ(server2.bind(1337), 0);
  server2.close();
  server2.close();

  ASSERT_EQ(server2.bind(1337), 0);
  ASSERT_EQ(server2.listen(10), 0);
  server2.close();
  server2.close();

  TCPSocket server3 = server2;
  ASSERT_EQ(server3.getLastError(), string());
  server3.close();
  server3.close();

  ASSERT_EQ(server3.bind(1337), 0);
  server3.close();
  server3.close();

  ASSERT_EQ(server3.bind(1337), 0);
  ASSERT_EQ(server3.listen(10), 0);
  server3.close();
  server3.close();
}

TEST(Bind, all) {
  TCPSocket server(IPV4);
  server.reuseAddr(1);

  ASSERT_EQ(server.bind(1337), 0);
  server.close();

  ASSERT_EQ(server.bind(13337), 0);
  server.close();

  ASSERT_EQ(server.bind(1), 1);
  ASSERT_EQ(server.getLastError(), "bind: Permission denied");

  ASSERT_EQ(server.bind(1337), 0);

  TCPSocket aux_server(IPV4);
  ASSERT_EQ(aux_server.bind(1337), 1);
  ASSERT_EQ(aux_server.getLastError(), "bind: Address already in use");

  ASSERT_EQ(aux_server.listen(10), 1);
  ASSERT_EQ(aux_server.getLastError(), "listen: Bad file descriptor");

  TCPSocket *accepted = aux_server.accept();
  ASSERT_EQ(accepted, nullptr);
  ASSERT_EQ(aux_server.getLastError(), "accept: Bad file descriptor");

  server.close();
}

TEST(Connect, all) {
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 1);
  ASSERT_EQ(client.getLastError(), "connect: Connection refused");

  TCPSocket server(IPV4);
  server.reuseAddr(1);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  ASSERT_EQ(client.connect("localhost", 1337), 0);

  client.close();
  server.close();
}

TEST(Connect, copyconstructor) {
  TCPSocket aux_client(IPV4);
  TCPSocket client(aux_client);
  ASSERT_EQ(client.connect("localhost", 1337), 1);
  ASSERT_EQ(client.getLastError(), "connect: Connection refused");

  TCPSocket server(IPV4);
  server.reuseAddr(1);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  ASSERT_EQ(client.connect("localhost", 1337), 0);

  client.close();
  server.close();
}

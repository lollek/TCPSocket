#include <gtest/gtest.h>

#include "../TCPSocket.hh"

TEST(Constructors, all) {
  TCPSocket server(IPV4);
  TCPSocket server2(server);
  TCPSocket server3 = server2;
}

TEST(Connect, ipv4) {
  TCPSocket server(IPV4);
  server.reuseAddr(1);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 0);
  client.close();
  server.close();
}

TEST(Connect, ipv6) {
  TCPSocket server(IPV6);
  server.reuseAddr(1);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 0);
  client.close();
  server.close();
}

TEST(Connect, ipv4_copycontructor) {
  TCPSocket server_constructor(IPV4);
  TCPSocket server(server_constructor);
  server.reuseAddr(1);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 0);
  client.close();
  server.close();

  server_constructor.reuseAddr(1);
  ASSERT_EQ(server_constructor.bind(1337), 0);
  ASSERT_EQ(server_constructor.listen(10), 0);
  ASSERT_EQ(client.connect("localhost", 1337), 0);
  server_constructor.close();
  client.close();
  server.close();


}
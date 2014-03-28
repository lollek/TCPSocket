#include <string>

#include <gtest/gtest.h>

#include "../TCPSocket.hh"

using namespace std;

TEST(Constructors, all) {
  TCPSocket server41(IPV4);
  ASSERT_EQ(server41.getLastError(), string());

  TCPSocket server61(IPV6);
  ASSERT_EQ(server61.getLastError(), string());

  TCPSocket server42(server41);
  ASSERT_EQ(server42.getLastError(), string());

  TCPSocket server62(server61);
  ASSERT_EQ(server62.getLastError(), string());

  TCPSocket server43 = server42;
  ASSERT_EQ(server43.getLastError(), string());

  TCPSocket server63 = server62;
  ASSERT_EQ(server63.getLastError(), string());
}

TEST(Bind, ipv4) {
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

  server.close();
}

TEST(Bind, ipv6) {
  TCPSocket server(IPV6);
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

  server.close();
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

TEST(FailedConnect, ipv4) {
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 1);
  client.close();
}

TEST(FailedConnect, ipv6) {
  TCPSocket client(IPV6);
  ASSERT_EQ(client.connect("localhost", 1337), 1);
  client.close();
}

TEST(Connect, ipv4_copycontructor) {
  TCPSocket server_constructor(IPV4);
  server_constructor.reuseAddr(1);
  TCPSocket server(server_constructor);
  ASSERT_EQ(server.bind(1337), 0);
  ASSERT_EQ(server.listen(10), 0);
  TCPSocket client(IPV4);
  ASSERT_EQ(client.connect("localhost", 1337), 0);
  client.close();
  server.close();

  ASSERT_EQ(server_constructor.bind(1337), 0);
  ASSERT_EQ(server_constructor.listen(10), 0);
  TCPSocket server2(server_constructor);
  server_constructor.close();
  ASSERT_EQ(client.connect("localhost", 1337), 1);
  client.close();
  server.close();


}

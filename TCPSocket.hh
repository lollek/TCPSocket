#ifndef __LOLLEK_TCPSOCKET_HH__
#define __LOLLEK_TCPSOCKET_HH__

#include <string>
#include <vector>

enum IPV { IPV4, IPV6 };

class TCPSocket {
  public:
    TCPSocket (IPV ip_version);
    TCPSocket (const TCPSocket &other);
    ~TCPSocket();

    /* Connects to remote host
     * hostname = hostname or ip of remote host
     * port     = port of remote host to connect to
     * returns 0 on success
     */
    int connect(const std::string &hostname, int port);

    /* Bind to a local port
     * port = local port to bind to
     * returns 0 on success
     */
    int bind(int port);

    /* Listen to incoming connections
     * num = how many incoming connections that can be queued
     * returns 0 on success
     */
    int listen(int num);

    /* Accept an incoming connection
     * returns a pointer to the client socket, which must later be deleted
     */
    TCPSocket *accept();

    /* Receive data from socket
     * num = size of buffer
     * returns a string with received data,
     *  which is empty if nothing is received
     */
    std::vector<char> recv(int num);

    /* Receive all data from socket
     * This is basically calling recv() several times */
    std::vector<char> recvall();

    /* Send data to socket
     * message = data to send
     * returns 0 on success
     */
    int send(const std::vector<char> &message);
    int send(const std::string &message);
    int send(const char *message, long length);

    /* Close socket */
    void close();

    /* Set if socket should reuse port or not
     * Must be set before bind to have an effect 
     */
    void reuseAddr(bool var);

    /* Get hostname of which the socket is connected to */
    std::string getHostname() const;

    /* Get the last error that occured */
    const std::string &getLastError() const;

    /* Disabled */
    TCPSocket &operator=(const TCPSocket &other) = delete;

  private:

    TCPSocket(int sock, const char *ip, IPV ip_version);
    int construct(const char *hostname, const char *port);

    void setLastError(const char *part1, const char *part2);

    /* Member variables */
    const IPV ip_version_;
    int sock_;
    char *ip_;
    bool reuseaddr_;
    std::string last_error_;
};

#endif //__LOLLEK_TCPSOCKET_HH__


#include <string>

enum IPV { IPV4, IPV6 };

class TCPSocket {
  public:
    TCPSocket (IPV ip_version);
    TCPSocket (const TCPSocket &other);
    ~TCPSocket();

    void operator=(const TCPSocket&) = delete;

    void _reuseAddr(bool var);
    int _connect(const std::string &hostname, int port);
    int _bind(int port);
    int _listen(int num);
    TCPSocket *_accept();
    std::string _recv(int num);
    void _send(const std::string &message);
    void _close();

    std::string _getHostname();

  private:
    TCPSocket(int sock, const char *ip, IPV ip_version);
    int construct(const char *hostname, const char *port);

    const IPV ip_version_;
    int sock_;
    char *ip_;
    bool reuseaddr_;
};

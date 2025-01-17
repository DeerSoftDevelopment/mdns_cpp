#pragma once

#include <functional>
#include <string>
#include <thread>
#include <unordered_map>

#include "mdns_cpp/defs.hpp"

struct sockaddr;

namespace mdns_cpp {

struct Query_result {
  Query_result(std::string service_nam, std::string canonical_hostname) {	  
	  this->hostNam = service_nam;
      this->canonical_hostname = canonical_hostname;
  } 
  
  std::string   hostNam;
  std::string   canonical_hostname;
  uint16_t		port;
  std::string   ipV4_adress;
  std::string   ipV6_adress;  
};

class mDNS { 
 public:
  ~mDNS();

  void startService();
  void stopService();
  bool isServiceRunning();

  void setServiceHostname(const std::string &hostname);
  void setServicePort(std::uint16_t port);
  void setServiceName(const std::string &name);
  void setServiceTxtRecord(const std::string &text_record);

  std::vector<Query_result> executeQuery2(const std::string &service);

  void executeQuery(const std::string &service);
  void executeDiscovery();
  

 private:
  void runMainLoop();
  int openClientSockets(int *sockets, int max_sockets, int port);
  int openServiceSockets(int *sockets, int max_sockets);

  std::string hostname_{"dummy-host"};
  std::string name_{"_http._tcp.local."};
  std::uint16_t port_{42424};
  std::string txt_record_{};

  bool running_{false};

  bool has_ipv4_{false};
  bool has_ipv6_{false};

  uint32_t service_address_ipv4_{0};
  uint8_t service_address_ipv6_[16]{0};

  std::thread worker_thread_;
};

}  // namespace mdns_cpp

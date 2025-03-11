#include "coro/net/udp/peer.hpp"
#include "coro/net/ip_address.hpp"
#include "coro/net/socket.hpp"

namespace coro::net::udp
{
peer::peer(std::shared_ptr<io_scheduler> scheduler, net::domain_t domain)
    : m_io_scheduler(std::move(scheduler)),
      m_socket(net::make_socket(net::socket::options{domain, net::socket::type_t::udp, net::socket::blocking_t::no}))
{
}

peer::peer(std::shared_ptr<io_scheduler> scheduler, const info& bind_info)
    : m_io_scheduler(std::move(scheduler)),
      m_socket(net::make_accept_socket(
          net::socket::options{bind_info.address.domain(), net::socket::type_t::udp, net::socket::blocking_t::no},
          bind_info.address,
          bind_info.port)),
      m_bound(true)
{
}

peer::peer(std::shared_ptr<io_scheduler> scheduler, const info& bind_info, const net::ip_address& multicast_address)
    : m_io_scheduler(std::move(scheduler)),
      m_socket(net::make_multicast_socket(
          net::socket::options{bind_info.address.domain(), net::socket::type_t::udp, net::socket::blocking_t::no},
          bind_info.address,
          bind_info.port,
          multicast_address)),
      m_bound(true)
{
}

} // namespace coro::net::udp

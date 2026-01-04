#ifndef _CWSPP_CONFIG_HPP
#define _CWSPP_CONFIG_HPP


#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/extensions/permessage_deflate/enabled.hpp>


namespace WSPP {

struct asio_client : public websocketpp::config::asio_client {};

struct asio_tls_client : public websocketpp::config::asio_tls_client {};

struct asio_client_compress : public websocketpp::config::asio_client {
    struct permessage_deflate_config {};

    typedef websocketpp::extensions::permessage_deflate::enabled
        <permessage_deflate_config> permessage_deflate_type;
};

struct asio_tls_client_compress : public websocketpp::config::asio_tls_client {
    struct permessage_deflate_config {};

    typedef websocketpp::extensions::permessage_deflate::enabled
        <permessage_deflate_config> permessage_deflate_type;
};

} // namespace WSPP

#endif

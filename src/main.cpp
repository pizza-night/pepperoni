// #include "config.hpp"
// #include "events.hpp"
// #include "frontend.hpp"
// #include "peer_listener.hpp"

// #include <optional>

// int main(int argc, char const* argv[]) {
//     using namespace peppe;

//     // Parse config
//     // TODO: handle argument errors
//     auto config = Config::parse(argc, argv);

//     // Load peer table
//     // TODO: handle parse errors
//     auto table = PeerTable::load(config.peer_table_file);

//     // Launch input handler
//     const int num_threads_hint = int(std::thread::hardware_concurrency());
//     asio::io_context io_context(num_threads_hint);
//     auto frontend = Frontend();
//     std::jthread frontend_thread([&frontend] { frontend.start(); });

//     // Launch peer listener
//     PeerListener peer_listener(io_context, std::move(table));
//     peer_listener.set_port(config.port);
//     co_spawn(io_context, peer_listener.listener(), detached);

//     // Setup signal handlers and run async event loop
//     asio::signal_set signals(io_context, SIGINT, SIGTERM);
//     signals.async_wait([&](auto, auto) { io_context.stop(); });
//     io_context.run();
// }

//////////////////////////////////////////////////////////////////////

#include <asio/ip/address.hpp>
#include <fmt/core.h>
// #include <ftxui/component/screen_interactive.hpp>

#include "config.hpp"
#include "frontend.hpp"

int main() {
    // peppe::Frontend{}.start();
    auto config_opt = peppe::Config::load_toml("config.toml");
    if (config_opt) {
        auto& config = config_opt.value();
        fmt::print("name: '{}'\n", config.name);
        fmt::print("port: '{}'\n", config.port);
        fmt::print("peers:\n");
        for (const auto& peer : config.peer_table) {
            fmt::print(
                "  ip/port: '{}:{}'\n", peer.address.to_string(), peer.port
            );
        }
    }
    else {
        fmt::print("Couldn't load config!\n");
    }
}
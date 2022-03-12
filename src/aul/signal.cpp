#include "aul/signal.hpp" // NOLINT(modernize-deprecated-headers)

namespace Aul {
    void Signal::Setup() {
        struct sigaction sigHandler{};
        sigHandler.sa_handler = [](int s) { Signal::Action(s); };
        sigemptyset(&sigHandler.sa_mask);
        sigHandler.sa_flags = 0;
        sigaction(SIGINT, &sigHandler, nullptr);
        sigaction(SIGABRT, &sigHandler, nullptr);
        sigaction(SIGTERM, &sigHandler, nullptr);
    }

    void Signal::Action(int s) {
        std::cout << std::endl << "goodbye :)" << std::endl;
        exit(1);
    }
}

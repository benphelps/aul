#pragma once

#include <csignal>
#include <functional>
#include <cstdlib>
#include <iostream>

namespace Aul
{
    class Signal {
    public:
        static void Setup();
        static void Action(int s);
    };
}

#pragma once

namespace GameEngine {

    class NonMovable
    {
    public:
        NonMovable(NonMovable&&) = delete;

        NonMovable& operator=(NonMovable&&) = delete;

    protected:
        NonMovable() = default;
    };

}
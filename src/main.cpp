#include <stdlib.h>
#include <vector>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

int main(int argc, char* argv[])
{
    { // Run the tests
        if (doctest::Context{}.run() != 0)
            return EXIT_FAILURE;
        // The CI does not have a GPU so it cannot run the rest of the code.
        const bool no_gpu_available = argc >= 2 && strcmp(argv[1], "-nogpu") == 0; // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
        if (no_gpu_available)
            return EXIT_SUCCESS;
    }

    // Actual app
    auto ctx = p6::Context{{.title = "Simple-p6-Setup"}};
    ctx.maximize_window();

    float screenWidth = ctx.aspect_ratio();

    std::vector<std::vector<float>> randSquare;

    for (int i = 0; i < 100; i++)
    {
        randSquare.emplace_back();
        glm::vec2 RandCoord = p6::random::point();
        randSquare[i].push_back(RandCoord.x * ctx.aspect_ratio());
        randSquare[i].push_back(RandCoord.y);
        randSquare[i].push_back(floorf(p6::random::number(4)));
        randSquare[i].push_back(p6::random::number());
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // ctx.background(p6::NamedColor::RedViolet);
        ctx.use_stroke = false;
        ctx.fill       = {0.f, 0.f, 0.f, 0.1f};
        ctx.rectangle(p6::FullScreen{});

        for (auto& i : randSquare)
        {
            ctx.fill = {i[3], 0.f, 0.f};
            ctx.square(
                p6::Center{i[0], i[1]},
                p6::Radius{0.1f}
            );

            switch (static_cast<int>(i[2]))
            {
            case 0:
                i[1] += 0.01f;
                if (i[1] > 1.f)
                    i[2] = 2;
                break;

            case 1:
                i[0] += 0.01f;
                if (i[0] > screenWidth)
                    i[2] = 4;
                break;

            case 2:
                i[1] -= 0.01f;
                if (i[1] < -1.f)
                    i[2] = 0;
                break;

            default:
                i[0] -= 0.01f;
                if (i[0] < -screenWidth)
                    i[2] = 1;
                break;
            }
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

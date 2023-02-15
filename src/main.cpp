#include <stdlib.h>
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
    
    float randSquare[100][3];
    
    for (int i = 0; i < 100; i++) {
        glm::vec2 RandCoord = p6::random::point();
        randSquare[i][0] = RandCoord.x * ctx.aspect_ratio();
        randSquare[i][1] = RandCoord.y;
        randSquare[i][2] = floorf(p6::random::number(4));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        //ctx.background(p6::NamedColor::RedViolet);
        ctx.use_stroke = false;
        ctx.fill = {0.f, 0.f, 0.f, 0.1f};
        ctx.rectangle(p6::FullScreen{});
        
        ctx.fill = {1.f, 1.f, 1.f};
        
        for (int i = 0; i < 100; i++) {
            ctx.square(
                p6::Center{randSquare[i][0], randSquare[i][1]},
                p6::Radius{0.1f}
            );
            
            switch ((int)randSquare[i][2]) {
                case 0:
                    randSquare[i][1] += 0.01f;
                    if (randSquare[i][1] > 1.f) randSquare[i][2] = 2;
                    break;
                    
                case 1:
                    randSquare[i][0] += 0.01f;
                    if (randSquare[i][0] > screenWidth) randSquare[i][2] = 4;
                    break;
                    
                case 2:
                    randSquare[i][1] -= 0.01f;
                    if (randSquare[i][1] < -1.f) randSquare[i][2] = 0;
                    break;
                    
                default:
                    randSquare[i][0] -= 0.01f;
                    if (randSquare[i][0] < -screenWidth) randSquare[i][2] = 1;
                    break;
            }
        }
        
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

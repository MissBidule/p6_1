#include <stdlib.h>
#include <vector>
#include "p6/p6.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest/doctest.h"

struct Boid {
private:
    float m_posX;
    float m_posY;
    int   m_angle;
    float m_speed;
    float m_color;

public:
    Boid()
        : m_posX(0), m_posY(0), m_angle(0), m_speed(0), m_color(1.f) {}
    Boid(float posX, float posY, int angle, float speed, float color)
        : m_posX(posX), m_posY(posY), m_angle(angle), m_speed(speed), m_color(color) {}
    void setPos(float posX, float posY)
    {
        m_posX = posX;
        m_posY = posY;
    }
    void setAngle(int angle)
    {
        m_angle = angle;
    }
    float getX() const { return m_posX; }
    float getY() const { return m_posY; }
    int   getAngle() const { return m_angle; }
    float getSpeed() const { return m_speed; }
    float getColor() const { return m_color; }
};

float Deg2Rad(int deg)
{
    return static_cast<float>(deg * (M_PI / static_cast<float>(180)));
}

glm::vec2 newPosFromAngle(float centerX, float centerY, int angle, float speed)
{
    glm::vec2 newPos;

    newPos.x = (speed * cos(Deg2Rad(angle))) / 2.f + centerX;
    newPos.y = (speed * sin(Deg2Rad(angle))) / 2.f + centerY;

    return newPos;
}

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

    std::vector<Boid> randSquare;

    for (int i = 0; i < 50; i++)
    {
        glm::vec2 RandCoord = p6::random::point();
        randSquare.emplace_back(RandCoord.x * screenWidth, RandCoord.y, p6::random::integer(1, 360), 0.002, p6::random::number(0.25f, 1.f));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // ctx.background(p6::NamedColor::RedViolet);
        ctx.use_stroke = false;
        ctx.fill       = {0.f, 0.f, 0.f, 0.1f};
        ctx.rectangle(p6::FullScreen{});

        for (auto& i : randSquare)
        {
            ctx.fill = {i.getColor(), 0.f, 0.f};
            ctx.square(
                p6::Center{i.getX(), i.getY()},
                p6::Radius{0.03f}
            );

            int direction = p6::random::integer(1, 100);

            if (direction <= 15)
            {
                i.setAngle(i.getAngle() + 11);
            }
            else if (direction >= 86)
            {
                i.setAngle(i.getAngle() - 11);
            }

            glm::vec2 newPos = newPosFromAngle(i.getX(), i.getY(), i.getAngle(), i.getSpeed());
            if (newPos.x > screenWidth)
                newPos.x = -1.f * screenWidth;
            if (newPos.y > 1)
                newPos.y = -1.f;
            if (newPos.x < -screenWidth)
                newPos.x = 1.f * screenWidth;
            if (newPos.y < -1)
                newPos.y = 1.f;
            i.setPos(newPos.x, newPos.y);
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

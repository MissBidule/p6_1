#include <stdlib.h>
#include <vector>
#include "glm/fwd.hpp"
#include "glm/geometric.hpp"
#include "glm/gtx/norm.hpp"
#include "glm/trigonometric.hpp"
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
    return static_cast<float>(deg) * (p6::PI / static_cast<float>(180));
}

int Rad2Deg(float rad)
{
    return static_cast<int>((rad * 180) / p6::PI);
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
    bool  SEPERATION = true;
    float distance   = 0.1f;

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

    for (int i = 0; i < 60; i++)
    {
        glm::vec2 RandCoord = p6::random::point();
        randSquare.emplace_back(RandCoord.x * screenWidth, RandCoord.y, p6::random::integer(1, 360), 0.002f, p6::random::number(0.25f, 1.f));
    }

    // Declare your infinite update loop.
    ctx.update = [&]() {
        // ctx.background(p6::NamedColor::RedViolet);
        ctx.use_stroke = false;
        ctx.fill       = {0.f, 0.f, 0.f, 0.1f};
        ctx.rectangle(p6::FullScreen{});

        for (auto& i : randSquare)
        {
            if (&i == randSquare.data())
            {
                ctx.fill = {0.f, 0.f, 0.8f};
                ctx.circle(
                    p6::Center{i.getX(), i.getY()},
                    p6::Radius{distance}
                );
            }
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

        // SEPARATION
        if (SEPERATION)
        {
            glm::vec2 vect0(1, 0);
            for (size_t i = 0; i < randSquare.size(); i++)
            {
                glm::vec2 totalForce = glm::vec2();
                glm::vec2 posInit    = glm::vec2(randSquare[i].getX(), randSquare[i].getY());
                for (size_t j = 0; j < randSquare.size(); j++)
                {
                    if (j == i)
                        continue;

                    glm::vec2 posFinal        = glm::vec2(randSquare[j].getX(), randSquare[j].getY());
                    float     distanceBetween = abs(glm::distance(posInit, posFinal));
                    if (distanceBetween < distance)
                    {
                        totalForce += (posInit - posFinal) / distanceBetween;
                    }
                }

                if (i == 0)
                {
                    ctx.stroke = {0.f, 1.f, 0.f};
                    ctx.line(posInit, posInit + totalForce);
                }

                if (totalForce != glm::vec2())
                {
                    float newAngle = glm::acos((glm::dot(totalForce, vect0)) / glm::l2Norm(glm::vec3(totalForce, 0)));

                    std::cout << "Angle : " << glm::acos(glm::dot(totalForce, vect0) / glm::l2Norm(glm::vec3(totalForce, 0))) << std::endl;

                    randSquare[i].setAngle(Rad2Deg(newAngle));
                }
            }
        }
    };

    // Should be done last. It starts the infinite loop.
    ctx.start();
}

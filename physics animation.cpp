#include <iostream>
#include <SFML/Graphics.hpp>

const int WIDTH = 800;
const int HEIGHT = 600;
const double GRAVITY = 9.8;
const double TIME_STEP = 0.01;

class Ball {
public:
    Ball() : x_(WIDTH / 2), y_(HEIGHT / 2), vx_(0), vy_(0), radius_(50) {}

    void update() {
        vy_ += GRAVITY * TIME_STEP;
        x_ += vx_ * TIME_STEP;
        y_ += vy_ * TIME_STEP;

        // handle collision with the ground
        if (y_ + radius_ >= HEIGHT) {
            y_ = HEIGHT - radius_;
            vy_ = -vy_;
        }
    }

    void draw(sf::RenderWindow& window) {
        sf::CircleShape shape(radius_);
        shape.setPosition(x_ - radius_, y_ - radius_);
        shape.setFillColor(sf::Color::Red);
        window.draw(shape);
    }

private:
    double x_;
    double y_;
    double vx_;
    double vy_;
    double radius_;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Physics-based Animation");
    Ball ball;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        ball.update();

        window.clear();
        ball.draw(window);
        window.display();
    }

    return 0;
}

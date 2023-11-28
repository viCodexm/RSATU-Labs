

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <chrono>
#include <random>
#include "Consts.hpp"

struct Image;
std::vector<std::shared_ptr<Image>> images;

struct Image : sf::Sprite {
    Image() {}
    Image(sf::Texture* texture, sf::Vector2f position) {
        this->setTexture(*texture);
        this->setPosition(position);
    }
    ~Image() {}
    virtual void logic() {}
};
struct RotatedImage : public Image {
    RotatedImage() {}
    RotatedImage(sf::Texture *texture, sf::Vector2f position) : Image(texture, position) {        
        sf::Vector2u size = this->getTexture()->getSize();
        this->setOrigin(size.x / 2.f, size.y / 2.f);
    }
    void logic() override {
        this->rotate(0.001);
    }
};
struct ScalingRotatedImage : public RotatedImage {
    int scaleCount = 0;
    const int scaleBorder = 50000;

    ScalingRotatedImage(sf::Texture *texture, sf::Vector2f position) : RotatedImage(texture, position) {}

    void logic() override {
        if (scaleCount >= 0)
            this->scale(sf::Vector2f(1.000001, 1.000001));
        else this->scale(sf::Vector2f(0.999999, 0.999999));
        if (scaleCount > scaleBorder)
            scaleCount = -scaleBorder;
        scaleCount++;
    }
};
struct BouncingImage : public Image {
    sf::Vector2f direction;
    sf::Vector2u size = this->getTexture()->getSize();
    sf::Sound collisionSound;

    BouncingImage(sf::Texture* texture, sf::Vector2f position, sf::Vector2f direction, sf::Sound collisionSound)
        : Image(texture, position), direction(direction), collisionSound(collisionSound) {}

    void logic() override {
        
        sf::Vector2f position = this->getPosition();
        position += direction;

        if (position.x < 0 || position.x + size.x > SCREEN_WIDTH)
            direction.x = -direction.x;

        if (position.y < 0 || position.y + size.y > SCREEN_HEIGHT)
            direction.y = -direction.y;

        for (auto& image : images) {
            if (this != image.get() && this->getGlobalBounds().intersects(image->getGlobalBounds())) {
                direction = -direction;
                position += direction + direction + direction + direction;
                collisionSound.play();
                break;
            }
        }

        this->setPosition(position);
    }
};




void thread_logic(sf::RenderWindow* window) {
    sf::Mutex mtx;
    while (window->isOpen()) {
        window->clear(COLOR_BACKGROUND);
        mtx.lock();
        for (int i = 0; i < images.size(); ++i)
            window->draw(*images[i]);
        mtx.unlock();
        window->display();
    }
}


int main() {

    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), L"Картинки", sf::Style::Titlebar | sf::Style::Close);
    window.setActive(false);
    sf::Thread thread(&thread_logic, &window);
    thread.launch();

    sf::Texture happyDuck, familyDuck;
    if (!happyDuck.loadFromFile("cool duck.jpeg"))
        exit(-1);
    if (!familyDuck.loadFromFile("duck with kids.jpeg"))
        exit(-2);
        
    images.push_back(std::make_shared<Image>(
        Image(&happyDuck, {400, 50})
    ));
    images.push_back(std::make_shared<RotatedImage>(
        RotatedImage(&happyDuck, {200, 180})
    ));
    images.push_back(std::make_shared<ScalingRotatedImage>(
        ScalingRotatedImage(&happyDuck, {1000, 180})
    ));
    sf::SoundBuffer buffer; buffer.loadFromFile("quack-sound-effect.mp3");
    sf::Sound soundQuack(buffer);
    const sf::Vector2f duckSpeed = {0.003, 0.003};
    images.push_back(std::make_shared<BouncingImage>(
        BouncingImage(&happyDuck, {400, 350}, duckSpeed, soundQuack)
    ));
    images.push_back(std::make_shared<BouncingImage>(
        BouncingImage(&familyDuck, {50, 550}, duckSpeed, soundQuack)
    ));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();    
        }
        for (auto& image : images)
            image->logic();
    }
    
    return 0;
}
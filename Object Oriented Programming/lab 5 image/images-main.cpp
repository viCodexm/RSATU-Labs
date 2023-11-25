

#include <SFML/Graphics.hpp>
#include <bits/stdc++.h>
#include "Consts.hpp"


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
    RotatedImage(sf::Texture *texture, sf::Vector2f position) {
        this->setTexture(*texture);
        this->setPosition(position);
        sf::Vector2u size = this->getTexture()->getSize();
        this->setOrigin(size.x / 2.f, size.y / 2.f);
    }
    void logic() override {
        this->rotate(10);
    }
};
struct MegaRotatedImage : public RotatedImage {
    bool bScale = true;

    MegaRotatedImage(sf::Texture *texture, sf::Vector2f position) {
        this->setTexture(*texture);
        this->setPosition(position);
        sf::Vector2u size = this->getTexture()->getSize();
        this->setOrigin(size.x / 2.f, size.y / 2.f);   
    }
    void logic() override {
        if (bScale)
            this->scale(sf::Vector2f(1.1, 1.1));
        else this->scale(sf::Vector2f(0.909091, 0.909091));
        bScale = !bScale;
    }
};


std::vector<std::shared_ptr<Image>> images;

void thread_logic(sf::RenderWindow* window) {
    while (window->isOpen()) {
        window->clear(COLOR_BACKGROUND);
        for (int i = 0; i < images.size(); ++i)
            window->draw(*images[i]);

        window->display();
    }
}


int main() {

    
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), L"Картинки", sf::Style::Titlebar | sf::Style::Close);
    window.setActive(false);
    sf::Thread thread(&thread_logic, &window);
    thread.launch();

    sf::Texture texture;
    if (!texture.loadFromFile("cool duck.jpeg")) {
        exit(-1);
    }
    
    
    Image duck(&texture, {400, 50});
    RotatedImage RotatedDuck(&texture, {200, 180});
    MegaRotatedImage MegaDuck(&texture, {800, 180});

    images.push_back(std::make_shared<Image>(duck));
    images.push_back(std::make_shared<RotatedImage>(RotatedDuck));
    images.push_back(std::make_shared<MegaRotatedImage>(MegaDuck));

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.setActive(false);
                window.close();
            }
            for (auto& image : images)
                image->logic();
        }
    }
    
    return 0;
}
// Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

void applyGreenScreenEffect(Image& image, const Color& keyColor, int tolerance) {
    Vector2u size = image.getSize();
    for (unsigned int y = 0; y < size.y; ++y) {
        for (unsigned int x = 0; x < size.x; ++x) {
            Color pixelColor = image.getPixel(x, y);

            int diff = abs(pixelColor.r - keyColor.r) +
                abs(pixelColor.g - keyColor.g) +
                abs(pixelColor.b - keyColor.b);

            if (diff < tolerance) {
                image.setPixel(x, y, Color(0, 0, 0, 0));
            }
        }
    }
}

int main() {
    string backgroundPath = "D://spring 2024/programming/Lab6/backgrounds/winter.png";
    string foregroundPath = "D://spring 2024/programming/Lab6/characters/yoda.png";

    Texture backgroundTex;
    if (!backgroundTex.loadFromFile(backgroundPath)) {
        cout << "Couldn't load image" << endl;
        return -1;
    }

    Texture foregroundTex;
    if (!foregroundTex.loadFromFile(foregroundPath)) {
        cout << "Couldn't load image" << endl;
        return -1;
    }

    Image foregroundImage = foregroundTex.copyToImage();

    Color keyColor = Color(0, 255, 0);
    int tolerance = 100;
    applyGreenScreenEffect(foregroundImage, keyColor, tolerance);

    foregroundTex.loadFromImage(foregroundImage);

    Sprite backgroundSprite;
    backgroundSprite.setTexture(backgroundTex);

    Sprite foregroundSprite;
    foregroundSprite.setTexture(foregroundTex);

    RenderWindow window(VideoMode(1024, 768), "Here's the output");

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.draw(backgroundSprite);
        window.draw(foregroundSprite);
        window.display();
    }

    return 0;
}
#include <SFML/Graphics.hpp>
#include <array>
#include <random>
#include <iostream>
#include "Header.h"


Etat etatInitial, etatFinal, etatCourant;

int tabini[TAILLE_GRILLE][TAILLE_GRILLE] = {
    {2, 3, 0},//{2, 0, 3},
    {1, 8, 4},
    {7, 6, 5}
};

int tabfin[TAILLE_GRILLE][TAILLE_GRILLE] = {
    {1, 2, 3},
    {8, 0, 4},
    {7, 6, 5}
};

class Taquin {
private:

    std::vector<char> directions;
    int plateau[TAILLE_GRILLE][TAILLE_GRILLE];

public:

    Taquin() {
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                plateau[i][j] = tabini[i][j];
            }
        }
    }

    void mix() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);

        for (int i = 0; i < 10; ++i) {
            int rand_dir = dis(gen);
            char direction;
            switch (rand_dir) {
            case 0:
                direction = 'L';
                break;
            case 1:
                direction = 'R';
                break;
            case 2:
                direction = 'U';
                break;
            case 3:
                direction = 'D';
                break;
            }
            directions.push_back(direction);
        }

        for (char dir : directions) {
            switch (dir) {
            case 'L':
                left();
                break;
            case 'R':
                right();
                break;
            case 'U':
                up();
                break;
            case 'D':
                down();
                break;
            }
        }
    }

    void left() {
        std::pair<int, int> pos = poszero();
        int i = pos.first;
        int j = pos.second;
        if (j != TAILLE_GRILLE - 1) {
            plateau[i][j] = plateau[i][j + 1];
            plateau[i][j + 1] = 0;
        }
    }

    void right() {
        std::pair<int, int> pos = poszero();
        int i = pos.first;
        int j = pos.second;
        if (j != 0) {
            plateau[i][j] = plateau[i][j - 1];
            plateau[i][j - 1] = 0;
        }
    }

    void up() {
        std::pair<int, int> pos = poszero();
        int i = pos.first;
        int j = pos.second;
        if (i != TAILLE_GRILLE - 1) {
            plateau[i][j] = plateau[i + 1][j];
            plateau[i + 1][j] = 0;
        }
    }

    void down() {
        std::pair<int, int> pos = poszero();
        int i = pos.first;
        int j = pos.second;
        if (i != 0) {
            plateau[i][j] = plateau[i - 1][j];
            plateau[i - 1][j] = 0;
        }
    }

    std::pair<int, int> poszero() {
        for (int y = 0; y < TAILLE_GRILLE; ++y) {
            for (int x = 0; x < TAILLE_GRILLE; ++x) {
                if (Taquin::plateau[y][x] == 0) return { y, x };
            }
        }
        return { -1, -1 }; // Si la position de zero n'est pas trouvee
    }

    void printPlateau() {
        for (int i = 0; i < TAILLE_GRILLE; ++i) {
            for (int j = 0; j < TAILLE_GRILLE; ++j) {
                std::cout << plateau[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    void graphicPlate(sf::RenderWindow& window, bool win) {
        sf::Font font;
        font.loadFromFile("OpenSans-Bold.ttf");
        sf::Text text;
        text.setFont(font);
        text.setCharacterSize(100);
        text.setFillColor(sf::Color::White);

        if (win) {
            window.clear(sf::Color(0, 102, 0));
            text.setString("You Win!");
            text.setPosition(140.f, 180.f);
            window.draw(text);

        }
        else {
            font.loadFromFile("arial.ttf");
            sf::Text texte("GAME OF TAQUIN", font);
            texte.setCharacterSize(70); // Taille du texte
            texte.setFillColor(sf::Color::Black); // Couleur du texte

            // Positionnement du texte au milieu du haut de la fenetre
            sf::FloatRect textBound = texte.getLocalBounds();
            texte.setOrigin(textBound.left + textBound.width / 2.0f, textBound.top + textBound.height / 2.0f);
            texte.setPosition(window.getSize().x / 2.0f, 50);
            sf::Text textBottom("AJALE Saad _BENHADDOU Lahcen (1GI)", font); // Remplacez "Votre nom" par votre nom
            textBottom.setCharacterSize(20); // Taille du texte
            textBottom.setFillColor(sf::Color::White); // Couleur du texte
            sf::FloatRect textBoundsBottom = textBottom.getLocalBounds();
            textBottom.setOrigin(textBoundsBottom.left + textBoundsBottom.width / 2.0f, textBoundsBottom.top + textBoundsBottom.height / 2.0f);
            textBottom.setPosition(window.getSize().x / 2.0f, window.getSize().y - 15);
            sf::Text textBottomright("Press the 'h' key for assistance", font);
            textBottomright.setCharacterSize(20); // Taille du texte
            textBottomright.setFillColor(sf::Color(255, 50, 0)); // Couleur du texte

            // Positionnement du texte "Press h for help" au milieu du bas de la fenetre
            sf::FloatRect textBoundsBottomright = textBottomright.getLocalBounds();
            textBottomright.setOrigin(textBoundsBottomright.left + textBoundsBottomright.width / 2.0f, textBoundsBottomright.top + textBoundsBottomright.height / 2.0f);
            textBottomright.setPosition(window.getSize().x / 2.0f, window.getSize().y - 60);
            window.draw(texte);
            window.draw(textBottom);
            window.draw(textBottomright);
            sf::RectangleShape tile(sf::Vector2f(142.f, 142.f));
            sf::FloatRect textBounds = text.getLocalBounds();
            for (int y = 0; y < TAILLE_GRILLE; ++y) {
                for (int x = 0; x < TAILLE_GRILLE; ++x) {
                    if (plateau[y][x] != 0) {
                        tile.setPosition(110 + 16.f + x * 146.f, 50 + 80.f + y * 146.f);
                        if (plateau[y][x] < 10) {
                            text.setPosition(54.f + x * 146.f, 58.f + y * 146.f);
                            text.setOrigin(textBounds.width / 2.0f, textBounds.height / 2.0f);
                            text.setPosition(tile.getPosition().x - 0.2 * tile.getSize().x + tile.getSize().x / 2.0f, tile.getPosition().y - 0.4 * tile.getSize().y + tile.getSize().y / 2.0f);

                        }
                        else {
                            text.setPosition(54.f + x * 146.f, 58.f + y * 146.f);
                        }
                        tile.setFillColor(sf::Color(40, 58, 82));
                        window.draw(tile);
                        text.setString(std::to_string(plateau[y][x]));
                        window.draw(text);
                    }
                }
            }
        }
    }
    bool etatSolutiontab(int tabCourant[TAILLE_GRILLE][TAILLE_GRILLE], int tabFinal[TAILLE_GRILLE][TAILLE_GRILLE]) {
        int estEgal = 1;
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                if (tabCourant[i][j] != tabFinal[i][j]) {
                    estEgal = 0;
                    break;
                }
            }
            if (!estEgal) {
                break;
            }
        }
        return (estEgal);
    }
    void help() {
        Etat etatCourant;
        etatInitial.g = 0;
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                etatInitial.tableau[i][j] = plateau[i][j];
                etatFinal.tableau[i][j] = tabfin[i][j];
            }
        }
        noeud* helpnoeud = RechercheAetoile(etatInitial, etatFinal);
        for (int i = 0; i < TAILLE_GRILLE; i++) {
            for (int j = 0; j < TAILLE_GRILLE; j++) {
                plateau[i][j] = helpnoeud->etat.tableau[i][j];
            }
        }
    }

    void play(sf::RenderWindow& window) {
        mix();
        //sf::RenderWindow window(sf::VideoMode(700, 680), "Le jeu du Taquin - AJALE SAAD - BENHADDOU");
        window.setPosition(sf::Vector2i(300, 0));
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Up) {
                        up();
                    }
                    else if (event.key.code == sf::Keyboard::Down) {
                        down();
                    }
                    else if (event.key.code == sf::Keyboard::Left) {
                        left();
                    }
                    else if (event.key.code == sf::Keyboard::Right) {
                        right();
                    }
                    else if (event.key.code == sf::Keyboard::H) {
                        help();
                    }
                }
            }

            window.clear(sf::Color(190, 180, 0));
            sf::RectangleShape background(sf::Vector2f(148 * 3.f, 148 * 3.f));
            background.setPosition(110 + 13.f, 50 + 76.f);
            background.setFillColor(sf::Color(0, 0, 0));
            window.draw(background);

            sf::RectangleShape border(sf::Vector2f(145.5 * 3.f, 145.5 * 3.f));
            border.setPosition(110 + 16.f, 50 + 80.f);
            border.setFillColor(sf::Color(100, 100, 3));
            window.draw(border);

            if (etatSolutiontab(plateau, tabfin)) {

                graphicPlate(window, true);
                sf::Texture buttonTexture, buttonTexture1;
                buttonTexture.loadFromFile("X.png");
                sf::Sprite buttonSprite(buttonTexture);
                buttonSprite.setPosition(100, 500);
                window.draw(buttonSprite);
                buttonTexture1.loadFromFile("Retry Button.png");
                sf::Sprite buttonSprite1(buttonTexture1);
                buttonSprite1.setPosition(450, 515);
                buttonSprite1.setScale(0.8f, 0.8f);
                window.draw(buttonSprite);
                window.draw(buttonSprite1);
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
                        if (buttonSprite.getGlobalBounds().contains(mousePos)) {
                            return;
                        }
                        else if (buttonSprite1.getGlobalBounds().contains(mousePos)) {
                            play(window);
                            return;

                        }
                    }
                }
            }
            else {
                graphicPlate(window, false);

            }

            window.display();
        }
    }
};


enum class MenuOption {
    Play,
    Rules,
    Quit
};

class Menu {
public:
    MenuOption display(sf::RenderWindow& window) {
        sf::Font font;
        font.loadFromFile("Arial.ttf");
        sf::Text title("GAME OF TAQUIN", font, 60);
        title.setFillColor(sf::Color::White);
        title.setPosition(100.0f, 50.f);
        //centerText(title);

        sf::RectangleShape menuBox(sf::Vector2f(400.f, 300.f));
        menuBox.setFillColor(sf::Color(33, 21, 3));
        menuBox.setPosition(50 + 100.f, 70 + 150.f);
        menuBox.setOutlineThickness(5.f);
        menuBox.setOutlineColor(sf::Color(47, 32, 8));

        sf::Text playText("Jouer", font, 50);
        playText.setFillColor(sf::Color::White);
        playText.setPosition(30 + 250.f, 30 + 220.f);
        //centerText(playText);

        sf::Text rulesText("Regles", font, 50);
        rulesText.setFillColor(sf::Color::White);
        rulesText.setPosition(30 + 250.f, 50 + 290.f);
        //centerText(rulesText);

        sf::Text quitText("Quitter", font, 50);
        quitText.setFillColor(sf::Color::White);
        quitText.setPosition(30 + 250.f, 70 + 360.f);
        //centerText(quitText);

        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                    return MenuOption::Quit;
                }
                else if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                    if (playText.getGlobalBounds().contains(mousePos)) {
                        return MenuOption::Play;
                    }
                    else if (rulesText.getGlobalBounds().contains(mousePos)) {
                        return MenuOption::Rules;
                    }
                    else if (quitText.getGlobalBounds().contains(mousePos)) {
                        window.close();
                        return MenuOption::Quit;
                    }
                }
            }

            window.clear(sf::Color(9, 44, 28));
            window.draw(title);
            window.draw(menuBox);
            window.draw(playText);
            window.draw(rulesText);
            window.draw(quitText);
            window.display();
        }

        return MenuOption::Quit;
    }
    void play(sf::RenderWindow& window) {
        Taquin T;
        T.play(window);
    }

    void displayRules(sf::RenderWindow& window) {
        sf::Font font;
        font.loadFromFile("OpenSans-Bold.ttf");

        sf::Text title("Regles du Taquin", font, 30);
        title.setFillColor(sf::Color::White);
        title.setPosition(50.f, 20.f);

        sf::Text rules1("Le Taquin est un jeu de puzzle ou le but est de", font, 20);
        rules1.setFillColor(sf::Color::White);
        rules1.setPosition(50.f, 80.f);

        sf::Text rules2("rearranger les numeros dans l'ordre, en deplacant ", font, 20);
        rules2.setFillColor(sf::Color::White);
        rules2.setPosition(50.f, 110.f);

        sf::Text rules3("la case vide.", font, 20);
        rules3.setFillColor(sf::Color::White);
        rules3.setPosition(50.f, 140.f);



        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    return; // Ne ferme pas la fenetre principale, seulement la fenetre des regles
                }
            }

            window.clear(sf::Color(9, 44, 28));
            window.draw(title);
            window.draw(rules1);
            window.draw(rules2);
            window.draw(rules3);
            window.display();
        }
    }

    void centerText(sf::Text& text) {
        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width / 2.0f,
            textRect.top + textRect.height / 2.0f);
        text.setPosition(sf::Vector2f(300.f, text.getPosition().y));
    }
};

int main() {
    Etat etatInitial, etatFinal;
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            etatInitial.tableau[i][j] = tabini[i][j];
            etatFinal.tableau[i][j] = tabfin[i][j];
        }
    }
    etatInitial.g = 0;
    sf::RenderWindow menuWindow(sf::VideoMode(700, 680), "Le jeu du Taquin - AJALE SAAD - BENHADDOU - LAHCEN");
    menuWindow.setPosition(sf::Vector2i(300, 0));

    Menu menu;
    MenuOption option = menu.display(menuWindow);

    while (option != MenuOption::Quit) {
        if (option == MenuOption::Play) {
            menu.play(menuWindow);
        }
        else if (option == MenuOption::Rules) {
            menu.displayRules(menuWindow);
        }
        option = menu.display(menuWindow);
    }

    return 0;
}

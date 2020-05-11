#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

/*Some problems with creating balls while LControl+LeftClick(RightClick)
Hope to make balls bounce one from another*/
using namespace std;

struct Ball
{
    float charge;
    float mass;
    float radius;
    sf::Vector2f position;
    sf::Vector2f velocity;
};


int main()
{       
    srand(time(0));
    
    const int width = 1000;
    const int height = 800;
     int n_balls = 3;

    // Шаг по времени
    const float delta_t = 0.1;

    // Создаём экземпляр класса окно
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    // Задаём максимальное количество кадров в секунду
    window.setFramerateLimit(60);

    // Так как sf::CircleShape занимает много памяти, создаём всего 1 экземпляр
    sf::CircleShape circle(50.0f);
    circle.setFillColor({ 255, 0, 0 });    

    std::vector<Ball> balls;
    balls.resize(n_balls);
    for (int i = 0; i < n_balls; i++){
        balls[i].charge = (float)(rand() % 20 - 10);      
        balls[i].radius = 4 + rand() % 8;
        balls[i].position = { (float)(rand() % width), (float)(rand() % height) };
        balls[i].velocity = { 0, 0};
        balls[i].mass = (float)(rand() %1 + 0.1)*balls[i].radius* balls[i].radius;                    
    }

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::MouseButtonPressed and (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))){
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::cout << "the right button was pressed" << std::endl;
                    n_balls++;
                    balls.resize(n_balls);
                    balls[n_balls - 1].mass = 4;
                    balls[n_balls - 1].radius = 5;
                    balls[n_balls - 1].position.x = event.mouseButton.x;
                    balls[n_balls - 1].position.y = event.mouseButton.y;
                    balls[n_balls - 1].velocity = { 0, 0 };
                    balls[n_balls - 1].charge = -3;
                }

                if (event.mouseButton.button == sf::Mouse::Left){
                    std::cout << "the left button was pressed" << std::endl;
                    n_balls++;
                    balls.resize(n_balls);
                    balls[n_balls - 1].mass = 1;
                    balls[n_balls - 1].radius = 10;
                    balls[n_balls - 1].position.x = event.mouseButton.x;
                    balls[n_balls - 1].position.y = event.mouseButton.y;
                    balls[n_balls - 1].velocity = { 0, 0 };
                    balls[n_balls - 1].charge = 1;
                }
            }
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right){
                    std::cout << "the right button was pressed" << std::endl;
                    n_balls++;
                    balls.resize(n_balls);
                    balls[n_balls - 1].mass = 4;
                    balls[n_balls - 1].radius = 5;
                    balls[n_balls - 1].position.x = event.mouseButton.x;
                    balls[n_balls - 1].position.y = event.mouseButton.y;
                    balls[n_balls - 1].velocity = { 0, 0 };
                    balls[n_balls - 1].charge = 3;
                }

                if (event.mouseButton.button == sf::Mouse::Left){
                    std::cout << "the left button was pressed" << std::endl;
                    n_balls++;
                    balls.resize(n_balls);
                    balls[n_balls - 1].mass = 10;
                    balls[n_balls - 1].radius = 5;
                    balls[n_balls - 1].position.x = event.mouseButton.x;
                    balls[n_balls - 1].position.y = event.mouseButton.y;
                    balls[n_balls - 1].velocity = { 0, 0 };
                    balls[n_balls - 1].charge = 10;
                }
            }
    }
        // В данном примере проверяем окно на закрытие
        if (event.type == sf::Event::Closed)
                window.close();            
        // очистить скрытый холст черным цветом
        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++){
            balls[i].position += balls[i].velocity * delta_t;


            /*  if (balls[i].position.x < 0)
                  balls[i].position.x += width;
              if (balls[i].position.x > width)
                  balls[i].position.x -= width;

              if (balls[i].position.y < 0)
                  balls[i].position.y += height;
              if (balls[i].position.y > height)
                  balls[i].position.y -= height;*/


                  // Используем 1 sf::CircleShape, чтобы нарисовать все шары
            circle.setRadius(balls[i].radius);
            // setOrigin - задаёт центр объекта
            // По умолчанию центр - в левом верхнем угле объекта
            // Строка ниже устанавливает центр в центре шарика
            // В дальнейшем функция, setPosition устанавливает положение шарика так, 
            // чтобы его центр был в точке balls[i].position
            circle.setOrigin(balls[i].radius, balls[i].radius);
            circle.setPosition(balls[i].position);

            window.draw(circle);

            if (balls[i].radius > balls[i].position.y) {
                balls[i].velocity.y = -balls[i].velocity.y;
                balls[i].position.y += 2 * (balls[i].radius - balls[i].position.y);
            }
            if (balls[i].radius > (height - balls[i].position.y)) {
                balls[i].position.y -= 2 * (balls[i].radius - (height - balls[i].position.y));
                balls[i].velocity.y = -balls[i].velocity.y;
            }
            if (balls[i].radius > balls[i].position.x) {
                balls[i].velocity.x = -balls[i].velocity.x;
                balls[i].position.x += 2 * (balls[i].radius - balls[i].position.x);
            }
            if (balls[i].radius > (width - balls[i].position.x)) {
                balls[i].position.x -= 2 * (balls[i].radius - (width - balls[i].position.x));
                balls[i].velocity.x = -balls[i].velocity.x;
            }
            //Гравитация
            for (int i = 0; i < n_balls; i++) {
                float sumx = 0;
                float sumy = 0;
                for (int j = 0; j < n_balls; j++) {
                    if (i != j) {
                        float w = (balls[i].position.x - balls[j].position.x) * (balls[i].position.x - balls[j].position.x) + (balls[i].position.y - balls[j].position.y) * (balls[i].position.y - balls[j].position.y);
                        sumx += (balls[j].position.x - balls[i].position.x) * balls[j].mass / pow(w, 3 / 2);
                        sumy += (balls[j].position.y - balls[i].position.y) * balls[j].mass / pow(w, 3 / 2);
                    }

                    balls[i].velocity.x += sumx * delta_t;
                    balls[i].velocity.y += sumy * delta_t;
                }
            }
            //Кулон
            for (int i = 0; i < n_balls; i++) {
                float sumx = 0;
                float sumy = 0;
                for (int j = 0; j < n_balls; j++) {
                    if (i != j) {
                        float w = (balls[i].position.x - balls[j].position.x) * (balls[i].position.x - balls[j].position.x) + (balls[i].position.y - balls[j].position.y) * (balls[i].position.y - balls[j].position.y);
                        if (balls[j].charge * balls[i].charge > 0) {
                            sumx -= (balls[j].position.x - balls[i].position.x) * balls[j].charge * balls[i].charge / pow(w, 3 / 2) / balls[i].mass;
                            sumy -= (balls[j].position.y - balls[i].position.y) * balls[j].charge * balls[i].charge / pow(w, 3 / 2) / balls[i].mass;
                        }
                        else {
                            sumx += (balls[j].position.x - balls[i].position.x) * abs(balls[j].charge * balls[i].charge) / pow(w, 3 / 2) / balls[i].mass;
                            sumy += (balls[j].position.y - balls[i].position.y) * abs(balls[j].charge * balls[i].charge)/ pow(w, 3 / 2) / balls[i].mass;
                        }
                    }

                    balls[i].velocity.x += sumx * delta_t;
                    balls[i].velocity.y += sumy * delta_t;
                }
            }
        }
        // отображаем содержимое скрытого холста на экран
        window.display();
    }  
    return 0;
}
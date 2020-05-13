#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>


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
    const float delta_t = 0.05;

    // Создаём экземпляр класса окно
    sf::RenderWindow window(sf::VideoMode(width, height), "My window");
    // Задаём максимальное количество кадров в секунду
    window.setFramerateLimit(60);

    // Так как sf::CircleShape занимает много памяти, создаём всего 2 экземпляра для + и - зарядов
    sf::CircleShape circleP(50.0f);
    sf::CircleShape circleM(50.0f);
    circleP.setFillColor({ 255, 0, 0 });
    circleM.setFillColor({0, 0, 255});

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
            if (event.type == sf::Event::MouseButtonPressed){
                if (event.mouseButton.button == sf::Mouse::Right){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::cout << "the right button + ctrl was pressed" << std::endl;
                        n_balls++;
                        balls.resize(n_balls);
                        balls[n_balls - 1].mass = 4;
                        balls[n_balls - 1].radius = 5;
                        balls[n_balls - 1].position.x = event.mouseButton.x;
                        balls[n_balls - 1].position.y = event.mouseButton.y;
                        balls[n_balls - 1].velocity = {0, 0};
                        balls[n_balls - 1].charge = -3;
                    }else{
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
                }

                if (event.mouseButton.button == sf::Mouse::Left){
                    if(sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
                        std::cout << "the left button + ctrl was pressed" << std::endl;
                        n_balls++;
                        balls.resize(n_balls);
                        balls[n_balls - 1].mass = 1;
                        balls[n_balls - 1].radius = 10;
                        balls[n_balls - 1].position.x = event.mouseButton.x;
                        balls[n_balls - 1].position.y = event.mouseButton.y;
                        balls[n_balls - 1].velocity = {0, 0};
                        balls[n_balls - 1].charge = 1;
                    }else{
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

    }
        // В данном примере проверяем окно на закрытие
        if (event.type == sf::Event::Closed)
                window.close();            
        // очистить скрытый холст черным цветом
        window.clear(sf::Color::Black);

        for (int i = 0; i < n_balls; i++) {
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
            balls[i].charge >= 0 ? circleP.setRadius(balls[i].radius) : circleM.setRadius(balls[i].radius);
            // setOrigin - задаёт центр объекта
            // По умолчанию центр - в левом верхнем угле объекта
            // Строка ниже устанавливает центр в центре шарика
            // В дальнейшем функция, setPosition устанавливает положение шарика так, 
            // чтобы его центр был в точке balls[i].position
            balls[i].charge >= 0 ? circleP.setOrigin(balls[i].radius, balls[i].radius) : circleM.setOrigin(
                    balls[i].radius, balls[i].radius);
            balls[i].charge >= 0 ? circleP.setPosition(balls[i].position) : circleM.setPosition(balls[i].position);

            window.draw(circleP);
            window.draw(circleM);

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
        }
            //collision
        for(int i = 0; i<n_balls; i++){
            for(int j = 0; j<n_balls; j++) {
                if (i != j) {
                    float N = delta_t;           //need to change while dont work :)
                    float dx = balls[i].position.x + balls[i].velocity.x * N - balls[j].position.x - balls[j].velocity.x * N;
                    float dy = balls[i].position.y + balls[i].velocity.y * N - balls[j].position.y - balls[j].velocity.y * N;
                    float dist = sqrt(pow(dx, 2)+pow(dy, 2));
                    float R = balls[i].radius+balls[j].radius;
                    if(dist<=R){
                        float bet = atan2f(balls[j].position.y - balls[i].position.y, balls[j].position.x - balls[i].position.x);
                        float x1 = balls[i].velocity.x*cosf(-bet) - balls[i].velocity.y*sinf(-bet);
                        float y1 = balls[i].velocity.x*sinf(-bet) + balls[i].velocity.y*cosf(-bet);
                        float x2 = balls[j].velocity.x*cosf(-bet) - balls[j].velocity.y*sinf(-bet);
                        float y2 = balls[j].velocity.x*sinf(-bet) + balls[j].velocity.y*cosf(-bet);
                        balls[i].velocity.x = x2*cosf(bet) - y1*sinf(bet);
                        balls[i].velocity.y = x2*sinf(bet) + y1*cosf(bet);
                        balls[j].velocity.x = x1*cosf(bet) - y2*sinf(bet);
                        balls[j].velocity.y = x1*sinf(bet) + y2*cosf(bet);
                    }
                }
            }
        }
            //Гравитация
        for (int k = 0; k < n_balls; k++) {
            float sumx = 0;
            float sumy = 0;
            for (int j = 0; j < n_balls; j++) {
                if (k != j) {
                    float w = (balls[k].position.x - balls[j].position.x) * (balls[k].position.x - balls[j].position.x) + (balls[k].position.y - balls[j].position.y) * (balls[k].position.y - balls[j].position.y);
                    sumx += (balls[j].position.x - balls[k].position.x) * balls[j].mass / pow(w, 3 / 2);
                    sumy += (balls[j].position.y - balls[k].position.y) * balls[j].mass / pow(w, 3 / 2);
                }

                balls[k].velocity.x += sumx * delta_t;
                balls[k].velocity.y += sumy * delta_t;
            }
        }
        //Кулон
        for (int k = 0; k < n_balls; k++) {
            float sumx = 0;
            float sumy = 0;
            for (int j = 0; j < n_balls; j++) {
                if (k != j) {
                    float w = (balls[k].position.x - balls[j].position.x) * (balls[k].position.x - balls[j].position.x) + (balls[k].position.y - balls[j].position.y)
                                                                                                                          * (balls[k].position.y - balls[j].position.y);
                    if (balls[j].charge * balls[k].charge > 0) {
                        sumx -= (balls[j].position.x - balls[k].position.x) * balls[j].charge * balls[k].charge / pow(w, 3 / 2) / balls[k].mass;
                        sumy -= (balls[j].position.y - balls[k].position.y) * balls[j].charge * balls[k].charge / pow(w, 3 / 2) / balls[k].mass;
                    }
                    else {
                        sumx += (balls[j].position.x - balls[k].position.x) * abs(balls[j].charge * balls[k].charge) / pow(w, 3 / 2) / balls[k].mass;
                        sumy += (balls[j].position.y - balls[k].position.y) * abs(balls[j].charge * balls[k].charge)/ pow(w, 3 / 2) / balls[k].mass;
                    }
                }

                balls[k].velocity.x += sumx * delta_t;
                balls[k].velocity.y += sumy * delta_t;
            }
        }

            //отскок шаров друг от друга
            //Будем связывать новую СО с верхним шариком, строить матрицу перехода в новый базис,
            // направляющий вектор прямой всегда выходит из центра верхнего шарика
            //исходная СК начинается в верхнем левом углу окна
            /*for(int k = 0; k < n_balls; k++){
                for(int j = 0; j < n_balls; j++){
                    if(k!=j){
                        float dx = balls[k].position.x-balls[j].position.x;
                        float dy = balls[k].position.y-balls[j].position.y;
                        float R = balls[k].radius+balls[j].radius;
                        if(dx*dx+dy*dy<=R*R+1e-16){     //шарики столкнулись.
                            if()
                        }
                    }
                }
            }*/


        // отображаем содержимое скрытого холста на экран
        window.display();
    }  
    return 0;
}
#include <SFML/Graphics.hpp>
#include <fstream>
#include <Windows.h>
#include <thread>
#include <string>


short c, r;
short bomb[38][19];
short isOpenedOrFlaged[38][19];
short bomb_counter, cell_counter;
short lv;
bool game_stop;
short Time;
bool timer_stop;


sf::Texture cell;
sf::Texture flag;
sf::Texture explode;
sf::Texture zero;
sf::Texture one;
sf::Texture two;
sf::Texture three;
sf::Texture four;
sf::Texture five;
sf::Texture six;
sf::Texture seven;
sf::Texture eight;
sf::Sprite grid[38][19];


struct SaveGame
{
    short bomb[38][19];
    short isOpenedOrFlaged[38][19];
    short bomb_counter;
    short c, r;
    short lv;
    short Time;
};


sf::RenderWindow window(sf::VideoMode(1920, 1080), "MINE SWEEPER", sf::Style::Close);


void menu();
void customlevel();
void newgame();


void effect(sf::RectangleShape& sth,sf::Vector2i& mousePos)
{
    sf::FloatRect sthRect = sth.getGlobalBounds();
    if (mousePos.x >= sthRect.left && mousePos.x <= sthRect.left + sthRect.width && mousePos.y >= sthRect.top && mousePos.y <= sthRect.top + sthRect.height)
    {
        sf::RectangleShape selected({ sthRect.width,sthRect.height });
        selected.setFillColor(sf::Color(255, 255, 255, 150));
        selected.setPosition(sthRect.left, sthRect.top);
        window.draw(selected);
    }
}


void chooselevel()
{
    sf::FloatRect visibleArea(0, 0, 480, 300);
    window.setView(sf::View(visibleArea));
    window.setSize({ 480,300 });


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");


    sf::RectangleShape lv1button({ 144, 30 });
    lv1button.setOutlineThickness(2);
    lv1button.setOutlineColor(sf::Color(0, 0, 0, 255));
    lv1button.setPosition(168, 48);
    sf::Text lv1text("Beginer", font, 24);
    lv1text.setFillColor(sf::Color::Black);
    sf::FloatRect lv1textRect = lv1text.getLocalBounds();
    lv1text.setOrigin(lv1textRect.left + lv1textRect.width / 2.0f, lv1textRect.top + lv1textRect.height / 2.0f);
    lv1text.setPosition(lv1button.getPosition().x + lv1button.getSize().x / 2.0f, lv1button.getPosition().y + lv1button.getSize().y / 2.0f);


    sf::RectangleShape lv2button({ 144, 30 });
    lv2button.setOutlineThickness(2);
    lv2button.setOutlineColor(sf::Color(0, 0, 0, 255));
    lv2button.setPosition(168, 108);
    sf::Text lv2text("Intermediate", font, 24);
    lv2text.setFillColor(sf::Color::Black);
    sf::FloatRect lv2textRect = lv2text.getLocalBounds();
    lv2text.setOrigin(lv2textRect.left + lv2textRect.width / 2.0f, lv2textRect.top + lv2textRect.height / 2.0f);
    lv2text.setPosition(lv2button.getPosition().x + lv2button.getSize().x / 2.0f, lv2button.getPosition().y + lv2button.getSize().y / 2.0f);


    sf::RectangleShape lv3button({ 144, 30 });
    lv3button.setOutlineThickness(2);
    lv3button.setOutlineColor(sf::Color(0, 0, 0, 255));
    lv3button.setPosition(168, 168);
    sf::Text lv3text("Expert", font, 24);
    lv3text.setFillColor(sf::Color::Black);
    sf::FloatRect lv3textRect = lv3text.getLocalBounds();
    lv3text.setOrigin(lv3textRect.left + lv3textRect.width / 2.0f, lv3textRect.top + lv3textRect.height / 2.0f);
    lv3text.setPosition(lv3button.getPosition().x + lv3button.getSize().x / 2.0f, lv3button.getPosition().y + lv3button.getSize().y / 2.0f);


    sf::RectangleShape custombutton({ 144, 30 });
    custombutton.setOutlineThickness(2);
    custombutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    custombutton.setPosition(168, 228);
    sf::Text customtext("Custom", font, 24);
    customtext.setFillColor(sf::Color::Black);
    sf::FloatRect customtextRect = customtext.getLocalBounds();
    customtext.setOrigin(customtextRect.left + customtextRect.width / 2.0f, customtextRect.top + customtextRect.height / 2.0f);
    customtext.setPosition(custombutton.getPosition().x + custombutton.getSize().x / 2.0f, custombutton.getPosition().y + custombutton.getSize().y / 2.0f);


    sf::RectangleShape selected({ 144,30 });
    selected.setFillColor(sf::Color(255, 255, 255, 150));


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }


        if (evnt.type == evnt.KeyReleased)
        {
            if (evnt.key.code == sf::Keyboard::Escape)
            {
                menu();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));


        window.draw(lv1button);
        window.draw(lv1text);
        window.draw(lv2button);
        window.draw(lv2text);
        window.draw(lv3button);
        window.draw(lv3text);
        window.draw(custombutton);
        window.draw(customtext);


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        effect(lv1button,mousePos);
        effect(lv2button, mousePos);
        effect(lv3button, mousePos);
        effect(custombutton, mousePos);


        window.display();


        if (evnt.type == evnt.MouseButtonReleased)
        {
            if (mousePos.x >= 168 && mousePos.x <= 312)
            {
                if (mousePos.y >= 48 && mousePos.y <= 78)
                {
                    lv = 1;
                    bomb_counter = 10;
                    c = 8;
                    r = 8;
                    newgame();
                    break;
                }
                else if (mousePos.y >= 108 && mousePos.y <= 138)
                {
                    lv = 2;
                    bomb_counter = 40;
                    c = 13;
                    r = 13;
                    newgame();
                    break;
                }
                else if (mousePos.y >= 168 && mousePos.y <= 198)
                {
                    lv = 3;
                    bomb_counter = 99;
                    c = 30;
                    r = 16;
                    newgame();
                    break;
                }
                else if (mousePos.y >= 228 && mousePos.y <= 258)
                {
                    customlevel();
                    break;
                }
            }
        }
    }
}


void customlevel()
{
    sf::FloatRect visibleArea(0, 0, 480, 280);
    window.setView(sf::View(visibleArea));
    window.setSize({ 480,280 });


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");


    sf::RectangleShape adjustnumber({ 53,34 });
    adjustnumber.setOutlineThickness(2);
    adjustnumber.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::Texture uptexture;
    uptexture.loadFromFile("image/uparrow.png");
    sf::Texture downtexture;
    downtexture.loadFromFile("image/downarrow.png");


    sf::RectangleShape cUp({ 15,16 });
    cUp.setOutlineThickness(2);
    cUp.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::RectangleShape cDown({ 15,16 });
    cDown.setOutlineThickness(2);
    cDown.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::RectangleShape rUp({ 15,16 });
    rUp.setOutlineThickness(2);
    rUp.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::RectangleShape rDown({ 15,16 });
    rDown.setOutlineThickness(2);
    rDown.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::RectangleShape bombUp({ 15,16 });
    bombUp.setOutlineThickness(2);
    bombUp.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::RectangleShape bombDown({ 15,16 });
    bombDown.setOutlineThickness(2);
    bombDown.setOutlineColor(sf::Color(0, 0, 0, 255));


    sf::Text plus("+", font, 24);
    plus.setFillColor(sf::Color::Black);
    sf::Text minus("_", font, 24);
    minus.setFillColor(sf::Color::Black);


    sf::RectangleShape startbutton({ 144, 30 });
    startbutton.setOutlineThickness(2);
    startbutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    startbutton.setPosition(168, 220);
    sf::Text starttext("Start", font, 24);
    starttext.setFillColor(sf::Color::Black);
    sf::FloatRect starttextRect = starttext.getLocalBounds();
    starttext.setOrigin(starttextRect.left + starttextRect.width / 2.0f, starttextRect.top + starttextRect.height / 2.0f);
    starttext.setPosition(startbutton.getPosition().x + startbutton.getSize().x / 2.0f, startbutton.getPosition().y + startbutton.getSize().y / 2.0f);


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }

        
        if (evnt.type == evnt.KeyReleased)
        {
            if (evnt.key.code == sf::Keyboard::Escape)
            {
                menu();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));


        sf::Text title("CUSTOM GAME", font, 48);
        title.setPosition(60, 0);
        window.draw(title);


        sf::Text inputcolumn("Number of columns:  ", font, 24);
        inputcolumn.setPosition(48, 72);
        window.draw(inputcolumn);


        adjustnumber.setPosition(303, 69);
        window.draw(adjustnumber);
        cUp.setPosition(357, 69);
        window.draw(cUp);
        plus.setPosition(358, 60);
        window.draw(plus);
        cDown.setPosition(357, 87);
        window.draw(cDown);
        minus.setPosition(360, 69);
        window.draw(minus);


        sf::Text columns(std::to_string(c), font, 24);
        columns.setPosition(315, 72);
        columns.setFillColor(sf::Color::Black);
        window.draw(columns);


        sf::Text inputrow("Number of rows:     ", font, 24);
        inputrow.setPosition(48, 120);
        window.draw(inputrow);


        adjustnumber.setPosition(303, 117);
        window.draw(adjustnumber);
        rUp.setPosition(357, 117);
        window.draw(rUp);
        plus.setPosition(358, 108);
        window.draw(plus);
        rDown.setPosition(357, 135);
        window.draw(rDown);
        minus.setPosition(360, 117);
        window.draw(minus);


        sf::Text rows(std::to_string(r), font, 24);
        rows.setPosition(315, 120);
        rows.setFillColor(sf::Color::Black);
        window.draw(rows);


        sf::Text inputbomb("Number of bombs:    ", font, 24);
        inputbomb.setPosition(48, 170);
        window.draw(inputbomb);


        adjustnumber.setPosition(303, 167);
        window.draw(adjustnumber);
        bombUp.setPosition(357, 167);
        window.draw(bombUp);
        plus.setPosition(358, 158);
        window.draw(plus);
        bombDown.setPosition(357, 185);
        window.draw(bombDown);
        minus.setPosition(360, 167);
        window.draw(minus);


        sf::Text bombs(std::to_string(bomb_counter), font, 24);
        bombs.setPosition(315, 170);
        bombs.setFillColor(sf::Color::Black);
        window.draw(bombs);


        window.draw(startbutton);
        window.draw(starttext);


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        effect(cUp, mousePos);
        effect(cDown, mousePos);
        effect(rUp, mousePos);
        effect(rDown, mousePos);
        effect(bombUp, mousePos);
        effect(bombDown, mousePos);
        effect(startbutton, mousePos);


        window.display();


        if (evnt.type == evnt.MouseButtonPressed)
        {
            Sleep(80);
            if (mousePos.x >= 357 && mousePos.x <= 373)
            {
                if (mousePos.y >= 69 && mousePos.y <= 86)
                {
                    c++;
                }
                else if (mousePos.y >= 87 && mousePos.y <= 104)
                {
                    c--;
                }
                else if (mousePos.y >= 117 && mousePos.y <= 134)
                {
                    r++;
                }
                else if (mousePos.y >= 135 && mousePos.y <= 152)
                {
                    r--;
                }
                else if (mousePos.y >= 167 && mousePos.y <= 184)
                {
                    bomb_counter++;
                }
                else if (mousePos.y >= 185 && mousePos.y <= 202)
                {
                    bomb_counter--;
                }
            }
            else if (mousePos.x >= 168 && mousePos.x <= 312 && mousePos.y >= 220 && mousePos.y <= 249)
            {
                if (c * r >= 30 * 16 && bomb_counter >= 99)
                {
                    lv = 3;
                }
                else if (c * r >= 13 * 13 && bomb_counter >= 40)
                {
                    lv = 2;
                }
                else if (c * r >= 8 * 8 && bomb_counter >= 10)
                {
                    lv = 1;
                }
                else
                {
                    lv = 0;
                }
                newgame();
            }
        }


        if (c > 38)
        {
            c = 38;
        }
        else if (c < 4)
        {
            c = 4;
        }
        if (r > 19)
        {
            r = 19;
        }
        else if (r < 4)
        {
            r = 4;
        }
        if (bomb_counter > c * r - 9)
        {
            bomb_counter = c * r - 9;
        }
        else if (bomb_counter < 1)
        {
            bomb_counter = 1;
        }
    }
}


void randombombposition(sf::Vector2i& first)
{
    for (short i = 0; i < c; i++)
    {
        for (short j = 0; j < r; j++)
        {
            bomb[i][j] = 0;
        }
    }


    short n = 0;
    srand((unsigned int)time(0));
    while (n < bomb_counter)
    {
        short i = rand() % c;
        short j = rand() % r;
        if (i >= 0 && i < c && j >= 0 && j < r && bomb[i][j] != 10 && (i != first.x || j != first.y) && (i != first.x - 1 || j != first.y) && (i != first.x - 1 || j != first.y - 1) && (i != first.x - 1 || j != first.y + 1) && (i != first.x || j != first.y - 1) && (i != first.x + 1 || j != first.y - 1) && (i != first.x + 1 || j != first.y) && (i != first.x + 1 || j != first.y + 1) && (i != first.x || j != first.y + 1))
        {
            bomb[i][j] = 10;
            n++;
        }
    }
}


void addtocell(short x_coord, short y_coord)
{
    if (bomb[x_coord][y_coord] != 10 && x_coord >= 0 && x_coord < c && y_coord >= 0 && y_coord < r)
    {
        bomb[x_coord][y_coord]++;
    }
}


void addnumbers()
{
    for (short i = 0; i < c; i++)
    {
        for (short j = 0; j < r; j++)
        {
            if (bomb[i][j] == 10)
            {
                addtocell(i, j - 1);
                addtocell(i, j + 1);
                addtocell(i + 1, j);
                addtocell(i - 1, j);
                addtocell(i + 1, j + 1);
                addtocell(i - 1, j - 1);
                addtocell(i + 1, j - 1);
                addtocell(i - 1, j + 1);
            }
        }
    }
}


void open(sf::Vector2i cellPos)
{
    if (isOpenedOrFlaged[cellPos.x][cellPos.y] == 0 && cellPos.x >= 0 && cellPos.x < c && cellPos.y >= 0 && cellPos.y < r)
    {
        switch (bomb[cellPos.x][cellPos.y])
        {
        case 0:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(zero);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            open({ cellPos.x - 1,cellPos.y - 1 });
            open({ cellPos.x - 1,cellPos.y });
            open({ cellPos.x - 1,cellPos.y + 1 });
            open({ cellPos.x,cellPos.y - 1 });
            open({ cellPos.x,cellPos.y + 1 });
            open({ cellPos.x + 1,cellPos.y - 1 });
            open({ cellPos.x + 1,cellPos.y });
            open({ cellPos.x + 1,cellPos.y + 1 });
            break;
        }
        case 1:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(one);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 2:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(two);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 3:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(three);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 4:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(four);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 5:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(five);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 6:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(six);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 7:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(seven);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        case 8:
        {
            cell_counter++;
            grid[cellPos.x][cellPos.y].setTexture(eight);
            isOpenedOrFlaged[cellPos.x][cellPos.y] = 1;
            break;
        }
        default:
        {
            grid[cellPos.x][cellPos.y].setTexture(explode);
            game_stop = 1;
            break;
        }
        }
    }
}


void setflag(sf::Vector2i cellPos)
{
    if (isOpenedOrFlaged[cellPos.x][cellPos.y] == 0 && cellPos.x >= 0 && cellPos.x < c && cellPos.y >= 0 && cellPos.y < r)
    {
        grid[cellPos.x][cellPos.y].setTexture(flag);
        isOpenedOrFlaged[cellPos.x][cellPos.y] = 2;
    }
    else if (isOpenedOrFlaged[cellPos.x][cellPos.y] == 2 && cellPos.x >= 0 && cellPos.x < c && cellPos.y >= 0 && cellPos.y < r)
    {
        grid[cellPos.x][cellPos.y].setTexture(cell);
        isOpenedOrFlaged[cellPos.x][cellPos.y] = 0;
    }
}


void timer()
{
    timer_stop = 0;
    while (!game_stop && !timer_stop)
    {
        Time++;
        Sleep(1000);
    }
}


void savegame(const SaveGame& loaddata)
{
    std::ofstream savefile("data/savegame.txt", std::ios::binary);
    if (savefile.is_open())
    {
        savefile.write(reinterpret_cast<const char*>(&loaddata), sizeof(SaveGame));
        savefile.close();
    }
}


void savescore(short score)
{
    std::ifstream takescore("data/score.txt");
    short highScore = 0;
    takescore >> highScore;
    takescore.close();


    std::ofstream savescore("data/score.txt");
    if (score > highScore)
    {
        savescore.seekp(0);
        savescore << score;
    }
    else
    {
        savescore.seekp(0);
        savescore << highScore;
    }
    savescore.close();
}


void continueGame()
{
    SaveGame loaddata;
    std::ifstream savefile("data/savegame.txt", std::ios::binary);
    if (savefile.is_open())
    {
        savefile.read(reinterpret_cast<char*>(&loaddata), sizeof(SaveGame));
        lv = loaddata.lv;
        c = loaddata.c;
        r = loaddata.r;
        Time = loaddata.Time - 1;
        bomb_counter = loaddata.bomb_counter;
        savefile.close();
    }


    if (c == 0)
    {
        menu();
    }
    else
    {
        for (short i = 0; i < c; i++)
        {
            for (short j = 0; j < r; j++)
            {
                bomb[i][j] = loaddata.bomb[i][j];
                isOpenedOrFlaged[i][j] = loaddata.isOpenedOrFlaged[i][j];
            }
        }


        game_stop = 0;
        cell_counter = 0;


        sf::FloatRect visibleArea(0, 0, (c + 2) * 48.f, (r + 3) * 48.f);
        window.setView(sf::View(visibleArea));
        window.setSize(sf::Vector2u((c + 2) * 48, (r + 3) * 48));


        sf::Font font;
        font.loadFromFile("font/cambria.ttc");


        //Effect when move the cusor to a cell
        sf::Texture selectedcelltexture;
        selectedcelltexture.loadFromFile("image/selectedcell.png");
        sf::Sprite selectedcell(selectedcelltexture);


        cell.loadFromFile("image/cell.png");


        explode.loadFromFile("image/explode.png");


        flag.loadFromFile("image/flag.png");


        zero.loadFromFile("image/0.png");


        one.loadFromFile("image/1.png");


        two.loadFromFile("image/2.png");


        three.loadFromFile("image/3.png");


        four.loadFromFile("image/4.png");


        five.loadFromFile("image/5.png");


        six.loadFromFile("image/6.png");


        seven.loadFromFile("image/7.png");


        eight.loadFromFile("image/8.png");


        std::thread t(timer);


        for (short i = 0; i < c; i++)
        {
            for (short j = 0; j < r; j++)
            {
                switch (isOpenedOrFlaged[i][j])
                {
                case 0:
                {
                    grid[i][j].setTexture(cell);
                    break;
                }
                case 1:
                {
                    isOpenedOrFlaged[i][j] = 0;
                    open({ i,j });
                    break;
                }
                case 2:
                {
                    isOpenedOrFlaged[i][j] = 0;
                    setflag({ i,j });
                    break;
                }
                }
            }
        }


        while (window.isOpen())
        {
            sf::Event evnt;
            while (window.pollEvent(evnt))
            {
                if (evnt.type == evnt.Closed)
                {
                    SaveGame currentgamestate;
                    for (short i = 0; i < c; i++)
                    {
                        for (short j = 0; j < r; j++)
                        {
                            currentgamestate.bomb[i][j] = bomb[i][j];
                            currentgamestate.isOpenedOrFlaged[i][j] = isOpenedOrFlaged[i][j];
                        }
                    }
                    currentgamestate.bomb_counter = bomb_counter;
                    currentgamestate.c = c;
                    currentgamestate.r = r;
                    currentgamestate.lv = lv;
                    currentgamestate.Time = Time;
                    if (game_stop)
                    {
                        for (short i = 0; i < c; i++)
                        {
                            for (short j = 0; j < r; j++)
                            {
                                currentgamestate.bomb[i][j] = 0;
                                currentgamestate.isOpenedOrFlaged[i][j] = 0;
                            }
                        }
                        currentgamestate.bomb_counter = -1;
                        currentgamestate.c = 0;
                        currentgamestate.r = 0;
                        currentgamestate.lv = 0;
                        currentgamestate.Time = 0;
                    }
                    savegame(currentgamestate);


                    timer_stop = 1;
                    t.join();


                    window.close();
                }
            }


            if (evnt.type == evnt.KeyReleased)
            {
                if (evnt.key.code == sf::Keyboard::Escape)
                {
                    SaveGame currentgamestate;
                    for (short i = 0; i < c; i++)
                    {
                        for (short j = 0; j < r; j++)
                        {
                            currentgamestate.bomb[i][j] = bomb[i][j];
                            currentgamestate.isOpenedOrFlaged[i][j] = isOpenedOrFlaged[i][j];
                        }
                    }
                    currentgamestate.bomb_counter = bomb_counter;
                    currentgamestate.c = c;
                    currentgamestate.r = r;
                    currentgamestate.lv = lv;
                    currentgamestate.Time = Time;
                    if (game_stop)
                    {
                        for (short i = 0; i < c; i++)
                        {
                            for (short j = 0; j < r; j++)
                            {
                                currentgamestate.bomb[i][j] = 0;
                                currentgamestate.isOpenedOrFlaged[i][j] = 0;
                            }
                        }
                        currentgamestate.bomb_counter = -1;
                        currentgamestate.c = 0;
                        currentgamestate.r = 0;
                        currentgamestate.lv = 0;
                        currentgamestate.Time = 0;
                    }
                    savegame(currentgamestate);


                    timer_stop = 1;
                    t.join();


                    menu();
                }
            }


            window.clear(sf::Color(226, 80, 196, 255));


            //Check if game over
            if (cell_counter == c * r - bomb_counter)
            {
                sf::Text text("YOU WON", font, 48);
                text.setPosition(24 * c - 40.f, 0);
                window.draw(text);


                sf::Text showscore("Score: " + std::to_string(1000 * lv - Time), font, 24);
                sf::FloatRect scoreRect = showscore.getGlobalBounds();
                showscore.setPosition((c + 1) * 48.f - scoreRect.width, 60);
                window.draw(showscore);
                savescore(1000 * lv - Time);


                game_stop = 1;
            }
            else if (game_stop)
            {
                sf::Text text("YOU LOSE", font, 48);
                text.setPosition(24 * c - 65.f, 0);
                window.draw(text);


                for (short i = 0; i < c; i++)
                {
                    for (short j = 0; j < r; j++)
                    {
                        if (bomb[i][j] == 10)
                        {
                            grid[i][j].setTexture(explode);
                        }
                    }
                }
            }


            for (short i = 0; i < c; i++)
            {
                for (short j = 0; j < r; j++)
                {
                    grid[i][j].setPosition((i + 1) * 48.f, (j + 2) * 48.f);
                    window.draw(grid[i][j]);
                }
            }


            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            sf::Vector2i cellPos = { mousePos.x / 48 - 1,mousePos.y / 48 - 2 };
            if (cellPos.x >= 0 && cellPos.x < c && cellPos.y >= 0 && cellPos.y < r && !game_stop)
            {
                selectedcell.setPosition((cellPos.x + 1) * 48.f, (cellPos.y + 2) * 48.f);
                window.draw(selectedcell);
            }


            if (evnt.type == evnt.MouseButtonPressed)
            {
                while (1)
                {
                    window.pollEvent(evnt);
                    if (evnt.type == evnt.MouseButtonReleased)
                    {
                        sf::Vector2i newmousePos = sf::Mouse::getPosition(window);
                        sf::Vector2i newcellPos = { newmousePos.x / 48 - 1,newmousePos.y / 48 - 2 };


                        if (newcellPos.x == cellPos.x && newcellPos.y == cellPos.y)
                        {
                            if (evnt.mouseButton.button == sf::Mouse::Left && !game_stop)
                            {
                                if (cell_counter == 0)
                                {
                                    randombombposition(cellPos);
                                    addnumbers();
                                }
                                open(cellPos);
                            }


                            if (evnt.mouseButton.button == sf::Mouse::Right && !game_stop)
                            {
                                setflag(cellPos);
                            }


                            //Wheel button to open all the cells in the 3x3 square except flaged one if number of plag is equal number of bomb
                            if (evnt.mouseButton.button == sf::Mouse::Middle && !game_stop)
                            {
                                if (isOpenedOrFlaged[cellPos.x][cellPos.y] == 1)
                                {
                                    short flagcounter = 0;
                                    for (short i = -1; i <= 1; i++)
                                    {
                                        for (short j = -1; j <= 1; j++)
                                        {
                                            if (isOpenedOrFlaged[cellPos.x + i][cellPos.y + j] == 2)
                                            {
                                                flagcounter++;
                                            }
                                        }
                                    }
                                    if (flagcounter == bomb[cellPos.x][cellPos.y])
                                    {
                                        open({ cellPos.x - 1,cellPos.y - 1 });
                                        open({ cellPos.x - 1,cellPos.y });
                                        open({ cellPos.x - 1,cellPos.y + 1 });
                                        open({ cellPos.x,cellPos.y - 1 });
                                        open({ cellPos.x,cellPos.y + 1 });
                                        open({ cellPos.x + 1,cellPos.y - 1 });
                                        open({ cellPos.x + 1,cellPos.y });
                                        open({ cellPos.x + 1,cellPos.y + 1 });
                                    }
                                }
                            }
                        }


                        break;
                    }
                }
            }


            sf::Text timer("Time: " + std::to_string(Time), font, 24);
            timer.setPosition(48, 60);
            window.draw(timer);


            window.display();
        }
    }
}


void newgame()
{
    game_stop = 0;
    cell_counter = 0;
    Time = -1;


    sf::FloatRect visibleArea(0, 0, (c + 2) * 48.f, (r + 3) * 48.f);
    window.setView(sf::View(visibleArea));
    window.setSize(sf::Vector2u((c + 2) * 48, (r + 3) * 48));


    sf::Texture selectedcelltexture;
    selectedcelltexture.loadFromFile("image/selectedcell.png");
    sf::Sprite selectedcell(selectedcelltexture);


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");


    cell.loadFromFile("image/cell.png");


    explode.loadFromFile("image/explode.png");


    flag.loadFromFile("image/flag.png");


    zero.loadFromFile("image/0.png");


    one.loadFromFile("image/1.png");


    two.loadFromFile("image/2.png");


    three.loadFromFile("image/3.png");


    four.loadFromFile("image/4.png");


    five.loadFromFile("image/5.png");


    six.loadFromFile("image/6.png");


    seven.loadFromFile("image/7.png");


    eight.loadFromFile("image/8.png");


    std::thread t(timer);


    for (short i = 0; i < c; i++)
    {
        for (short j = 0; j < r; j++)
        {
            grid[i][j].setTexture(cell);
            isOpenedOrFlaged[i][j] = 0;
        }
    }


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                SaveGame currentgamestate;
                for (short i = 0; i < c; i++)
                {
                    for (short j = 0; j < r; j++)
                    {
                        currentgamestate.bomb[i][j] = bomb[i][j];
                        currentgamestate.isOpenedOrFlaged[i][j] = isOpenedOrFlaged[i][j];
                    }
                }
                currentgamestate.bomb_counter = bomb_counter;
                currentgamestate.c = c;
                currentgamestate.r = r;
                currentgamestate.lv = lv;
                currentgamestate.Time = Time;
                if (game_stop)
                {
                    for (short i = 0; i < c; i++)
                    {
                        for (short j = 0; j < r; j++)
                        {
                            currentgamestate.bomb[i][j] = 0;
                            currentgamestate.isOpenedOrFlaged[i][j] = 0;
                        }
                    }
                    currentgamestate.bomb_counter = -1;
                    currentgamestate.c = 0;
                    currentgamestate.r = 0;
                    currentgamestate.lv = 0;
                    currentgamestate.Time = 0;
                }
                savegame(currentgamestate);


                timer_stop = 1;
                t.join();


                window.close();
            }
        }


        if (evnt.type == evnt.KeyReleased)
        {
            if (evnt.key.code == sf::Keyboard::Escape)
            {
                SaveGame currentgamestate;
                for (short i = 0; i < c; i++)
                {
                    for (short j = 0; j < r; j++)
                    {
                        currentgamestate.bomb[i][j] = bomb[i][j];
                        currentgamestate.isOpenedOrFlaged[i][j] = isOpenedOrFlaged[i][j];
                    }
                }
                currentgamestate.bomb_counter = bomb_counter;
                currentgamestate.c = c;
                currentgamestate.r = r;
                currentgamestate.lv = lv;
                currentgamestate.Time = Time;
                if (game_stop)
                {
                    for (short i = 0; i < c; i++)
                    {
                        for (short j = 0; j < r; j++)
                        {
                            currentgamestate.bomb[i][j] = 0;
                            currentgamestate.isOpenedOrFlaged[i][j] = 0;
                        }
                    }
                    currentgamestate.bomb_counter = -1;
                    currentgamestate.c = 0;
                    currentgamestate.r = 0;
                    currentgamestate.lv = 0;
                    currentgamestate.Time = 0;
                }
                savegame(currentgamestate);


                timer_stop = 1;
                t.join();


                menu();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));


        //Check if game over
        if (cell_counter == c * r - bomb_counter)
        {
            sf::Text text("YOU WON", font, 48);
            text.setPosition(24 * c - 40.f, 0);
            window.draw(text);


            sf::Text showscore("Score: " + std::to_string(1000 * lv - Time), font, 24);
            sf::FloatRect scoreRect = showscore.getGlobalBounds();
            showscore.setPosition((c + 1) * 48.f - scoreRect.width, 60);
            window.draw(showscore);
            savescore(1000 * lv - Time);


            game_stop = 1;
        }
        else if (game_stop)
        {
            sf::Text text("YOU LOSE", font, 48);
            text.setPosition(24 * c - 65.f, 0);
            window.draw(text);


            for (short i = 0; i < c; i++)
            {
                for (short j = 0; j < r; j++)
                {
                    if (bomb[i][j] == 10)
                    {
                        grid[i][j].setTexture(explode);
                    }
                }
            }
        }


        for (short i = 0; i < c; i++)
        {
            for (short j = 0; j < r; j++)
            {
                grid[i][j].setPosition((i + 1) * 48.f, (j + 2) * 48.f);
                window.draw(grid[i][j]);
            }
        }


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2i cellPos = { mousePos.x / 48 - 1,mousePos.y / 48 - 2 };
        if (cellPos.x >= 0 && cellPos.x < c && cellPos.y >= 0 && cellPos.y < r && !game_stop)
        {
            selectedcell.setPosition((cellPos.x + 1) * 48.f, (cellPos.y + 2) * 48.f);
            window.draw(selectedcell);
        }


        if (evnt.type == evnt.MouseButtonPressed)
        {
            while (1)
            {
                window.pollEvent(evnt);
                if (evnt.type == evnt.MouseButtonReleased)
                {
                    sf::Vector2i newmousePos = sf::Mouse::getPosition(window);
                    sf::Vector2i newcellPos = { newmousePos.x / 48 - 1,newmousePos.y / 48 - 2 };


                    if (newcellPos.x == cellPos.x && newcellPos.y == cellPos.y)
                    {
                        if (evnt.mouseButton.button == sf::Mouse::Left && !game_stop)
                        {
                            if (cell_counter == 0)
                            {
                                randombombposition(cellPos);
                                addnumbers();
                            }
                            open(cellPos);
                        }


                        if (evnt.mouseButton.button == sf::Mouse::Right && !game_stop)
                        {
                            setflag(cellPos);
                        }


                        //Wheel button to open all the cells in the 3x3 square except flaged one if number of plag is equal number of bomb
                        if (evnt.mouseButton.button == sf::Mouse::Middle && !game_stop)
                        {
                            if (isOpenedOrFlaged[cellPos.x][cellPos.y] == 1)
                            {
                                short flagcounter = 0;
                                for (short i = -1; i <= 1; i++)
                                {
                                    for (short j = -1; j <= 1; j++)
                                    {
                                        if (isOpenedOrFlaged[cellPos.x + i][cellPos.y + j] == 2)
                                        {
                                            flagcounter++;
                                        }
                                    }
                                }
                                if (flagcounter == bomb[cellPos.x][cellPos.y])
                                {
                                    open({ cellPos.x - 1,cellPos.y - 1 });
                                    open({ cellPos.x - 1,cellPos.y });
                                    open({ cellPos.x - 1,cellPos.y + 1 });
                                    open({ cellPos.x,cellPos.y - 1 });
                                    open({ cellPos.x,cellPos.y + 1 });
                                    open({ cellPos.x + 1,cellPos.y - 1 });
                                    open({ cellPos.x + 1,cellPos.y });
                                    open({ cellPos.x + 1,cellPos.y + 1 });
                                }
                            }
                        }
                    }


                    break;
                }
            }
        }


        std::string str = "Time: " + std::to_string(Time);
        sf::Text timer(str, font, 24);
        timer.setPosition(48, 60);
        window.draw(timer);


        window.display();
    }
}


void score()
{
    std::fstream scoreFile("data/score.txt", std::ios::in | std::ios::out);
    short highScore = 0;
    if (scoreFile.is_open())
    {
        scoreFile >> highScore;
        scoreFile.close();
    }


    sf::FloatRect visibleArea(0, 0, 600, 72);
    window.setView(sf::View(visibleArea));
    window.setSize({ 600,72 });


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }


        if (evnt.type == evnt.KeyReleased)
        {
            if (evnt.key.code == sf::Keyboard::Escape)
            {
                menu();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));


        sf::Text highscore("Highest score: " + std::to_string(highScore), font, 48);
        highscore.setPosition(24, 0);
        window.draw(highscore);


        window.display();
    }
}


void tutorial()
{
    sf::FloatRect visibleArea(0, 0, 648, 480);
    window.setView(sf::View(visibleArea));
    window.setSize({ 648,480 });


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");

    
    sf::Text title("TUTORIAL", font, 48);
    sf::Text tutorialtext("WELCOME TO MINESWEEPER! YOUR GOAL IS TO CLEAR\nTHE MINEFIELD WITHOUT DETONATING ANY MINES.\nFOLLOW THIS GUIDE TO BECOME A MINESWEEPER\nMASTER.\n\n**CONTROLS:**\n- LEFT CLICK: OPEN A CELL. THE FIRST TIME YOU OPEN\nALWAYS A SAFE CELL.\n- RIGHT CLICK: FLAG A CELL AS A MINE. YOU AN UNFLAG\nIT BY CLICKING AGAIN.\n- MIDDLE CLICK (WHEEL BUTTON): OPEN CELLS IN A 3X3\nSQUARE, EXCLUDING FLAGGED CELLS, IF THE NUMBER\nOF FLAGS MATCHES THE NUMBER ON THE CELL.\n\n**WINNING AND LOSING:**\n- WIN: OPEN ALL SAFE CELLS WITHOUT DETONATING\nANY MINES.\n- LOSE: DETONATE A MINE.\n\n**DIFFICULTY LEVELS:**\n- LEVEL 1: BEGINNER (8X8 GRID, 10 MINES).\n- LEVEL 2: INTERMEDIATE (13X13 GRID, 40 MINES).\n-LEVEL 3: EXPERT (30X16 GRID, 99 MINES).\n\n**SCORE**\n- YOUR SCORE IS 1000 * <LEVEL> - <TIME>.\nCONGRATULATIONS! YOU ARE NOW READY TO EXPLORE\nTHE MINESWEEPER MINEFIELD. HAVE FUN AND HAPPY\nSWEEPING!", font, 24);


    float position = 0.f;


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }


        if (evnt.type == evnt.KeyReleased)
        {
            if (evnt.key.code == sf::Keyboard::Escape)
            {
                menu();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));


        if (evnt.type == evnt.MouseWheelScrolled)
        {
            position += evnt.mouseWheelScroll.delta * 10.f;
        }


        if (position < -450.f)
        {
            position = -450.f;
        }
        else if (position > 0.f)
        {
            position = 0.f;
        }

        title.setPosition(210, position);
        tutorialtext.setPosition(24, position + 72);
        window.draw(title);
        window.draw(tutorialtext);


        window.display();
    }
}


void menu()
{
    sf::FloatRect visibleArea(0, 0, 480, 300);
    window.setView(sf::View(visibleArea));
    window.setSize({ 480,300 });


    sf::Font font;
    font.loadFromFile("font/cambria.ttc");


    sf::RectangleShape continuebutton({ 144, 30 });
    continuebutton.setOutlineThickness(2);
    continuebutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    continuebutton.setPosition(168, 96);
    sf::Text continuetext("Continue", font, 24);
    continuetext.setFillColor(sf::Color::Black);
    sf::FloatRect continuetextRect = continuetext.getLocalBounds();
    continuetext.setOrigin(continuetextRect.left + continuetextRect.width / 2.0f, continuetextRect.top + continuetextRect.height / 2.0f);
    continuetext.setPosition(continuebutton.getPosition().x + continuebutton.getSize().x / 2.0f, continuebutton.getPosition().y + continuebutton.getSize().y / 2.0f);


    sf::RectangleShape newgamebutton({ 144, 30 });
    newgamebutton.setOutlineThickness(2);
    newgamebutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    newgamebutton.setPosition(168, 156);
    sf::Text newgametext("New Game", font, 24);
    newgametext.setFillColor(sf::Color::Black);
    sf::FloatRect newgametextRect = newgametext.getLocalBounds();
    newgametext.setOrigin(newgametextRect.left + newgametextRect.width / 2.0f, newgametextRect.top + newgametextRect.height / 2.0f);
    newgametext.setPosition(newgamebutton.getPosition().x + newgamebutton.getSize().x / 2.0f, newgamebutton.getPosition().y + newgamebutton.getSize().y / 2.0f);


    sf::RectangleShape scorebutton({ 144, 30 });
    scorebutton.setOutlineThickness(2);
    scorebutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    scorebutton.setPosition(168, 216);
    sf::Text scoretext("Score", font, 24);
    scoretext.setFillColor(sf::Color::Black);
    sf::FloatRect scoretextRect = scoretext.getLocalBounds();
    scoretext.setOrigin(scoretextRect.left + scoretextRect.width / 2.0f, scoretextRect.top + scoretextRect.height / 2.0f);
    scoretext.setPosition(scorebutton.getPosition().x + scorebutton.getSize().x / 2.0f, scorebutton.getPosition().y + scorebutton.getSize().y / 2.0f);


    sf::RectangleShape tutorialbutton({ 24, 24 });
    tutorialbutton.setOutlineThickness(2);
    tutorialbutton.setOutlineColor(sf::Color(0, 0, 0, 255));
    tutorialbutton.setPosition(431, 251);
    sf::Text tutorialtext("?", font, 24);
    tutorialtext.setFillColor(sf::Color::Black);
    sf::FloatRect tutorialtextRect = tutorialtext.getLocalBounds();
    tutorialtext.setOrigin(tutorialtextRect.left + tutorialtextRect.width / 2.0f, tutorialtextRect.top + tutorialtextRect.height / 2.0f);
    tutorialtext.setPosition(tutorialbutton.getPosition().x + tutorialbutton.getSize().x / 2.0f, tutorialbutton.getPosition().y + tutorialbutton.getSize().y / 2.0f);


    sf::RectangleShape selected({ 144,30 });
    selected.setFillColor(sf::Color(255, 255, 255, 150));

  
    sf::RectangleShape selectedtutorial({ 24,24 });
    selectedtutorial.setFillColor(sf::Color(255, 255, 255, 150));


    while (window.isOpen())
    {
        sf::Event evnt;
        while (window.pollEvent(evnt))
        {
            if (evnt.type == evnt.Closed)
            {
                window.close();
            }
        }


        window.clear(sf::Color(226, 80, 196, 255));

        sf::Text txt;
        window.draw(txt);

        sf::Text title("MINE SWEEPER", font, 48);
        title.setPosition(60, 0);
        window.draw(title);


        window.draw(continuebutton);
        window.draw(continuetext);
        window.draw(newgamebutton);
        window.draw(newgametext);
        window.draw(scorebutton);
        window.draw(scoretext);
        window.draw(tutorialbutton);
        window.draw(tutorialtext);


        sf::Vector2i mousePos = sf::Mouse::getPosition(window);


        effect(continuebutton, mousePos);
        effect(newgamebutton, mousePos);
        effect(scorebutton, mousePos);
        effect(tutorialbutton, mousePos);


        window.display();


        if (evnt.type == evnt.MouseButtonReleased)
        {
            if (mousePos.x >= 168 && mousePos.x <= 312)
            {
                if (mousePos.y >= 96 && mousePos.y <= 126)
                {
                    continueGame();
                }
                else if (mousePos.y >= 156 && mousePos.y <= 186)
                {
                    chooselevel();
                }
                else if (mousePos.y >= 216 && mousePos.y <= 246)
                {
                    score();
                }
            }
            else if (mousePos.x >= 431 && mousePos.x <= 455 && mousePos.y >= 251 && mousePos.y <= 275)
            {
                tutorial();
            }
        }
    }
}


int CALLBACK wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
    window.setFramerateLimit(60);
    menu();
    return 0;
}
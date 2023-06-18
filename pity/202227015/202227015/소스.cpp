#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <thread>
#include <vector>
#include <cctype> // std::toupper �Լ��� ���� ���
using namespace std;
#define _SLEEP_INIT_ 300
#define _SLEEP_LAMP_ 15

//�� �ڵ�(�ܿ� �ʿ� ����)
#define ANSI_COLOR_RED      "\x1b[31m" //�ٷ� �� ���ڿ��� �ݿ��ȴ�.
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"



vector<string> menues = {
            "mainpage",
            "start game",
            "maneual",
            "end game"
};
bool bgmEnd = true;//������ǿ� ���ӿ��� �Ұ�
bool new_key = true;
enum Keyinput { UP, DOWN, LEFT, RIGHT };
Keyinput in_key;
int sleeptime = _SLEEP_INIT_;
int screen_cursor = 0;
const int width = 20;
const int height = 10;

/*int melody[] = {262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 330, 262, 196, 262, 262, 196, 262, 294, 247, 262, 262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 330, 262, 196, 262};
int duration[] = { 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300 };
*/

int melody[] = { 329.6276, 329.6276,329.6276, 261.6256, 329.6276, 391.9954,  195.9977,261.6256, 195.9977 ,   164.8138, 220 ,246.9417,  220, 195.9977,  329.6276, 391.9954, 440.0000,349.2282,391.9954,329.6276,261.6256, 293.6648, 246.9417, 130.8128 ,391.9954 ,349.2282,349.2282, 293.6648,  329.6276,195.9977,  220.0000, 261.6256,220.0000, 261.6256, 293.6648, 391.9954 , 349.2282, 293.6648, 329.6276, 523.2511 , 523.2511,523.2511 };
int duration[] = { 100, 120, 120, 100, 120, 300, 300, 200, 200, 200, 150, 150, 150, 100, 150, 150, 150, 150, 150, 200, 150, 200, 300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 200, 150, 150, 150, 150, 150, 150, 300, 200,300,300 };




int snake_x, snake_y;
int snake_length = 1;
int snake_body[width * height][2];
Keyinput direction = RIGHT;
bool game_over = false;
// ���� ��ġ ����
int food_x, food_y;

void Setup()
{
    snake_x = width / 2;
    snake_y = height / 2;
    snake_body[0][0] = snake_x;
    snake_body[0][1] = snake_y;
    food_x = rand() % (width - 2) + 1;
    food_y = rand() % (height - 2) + 1;
}

void bgm()
{

    while (bgmEnd) {
        for (int i = 0; i < sizeof(melody) / sizeof(melody[0]) - 1; i++) {
            Beep(melody[i], duration[i]);
            Sleep(duration[i]);
            if (bgmEnd == false) { break; }
        }

    }

}

void Draw()
{
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD cursorPosition;
    cursorPosition.X = 0;
    cursorPosition.Y = 0;
    SetConsoleCursorPosition(consoleHandle, cursorPosition);

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            if (x == 0 || x == width - 1 || y == 0 || y == height - 1)
                cout << "#";
            else if (x == food_x && y == food_y)
                cout << "F";
            else if (x == snake_body[0][0] && y == snake_body[0][1])
            {
                // ���� ���� ��¦�̱�
                int color = rand() % 15 + 1;
                SetConsoleTextAttribute(consoleHandle, color);
                cout << "O";
            }
            else
            {
                bool is_body_part = false;
                for (int i = 1; i < snake_length; i++)
                {
                    if (x == snake_body[i][0] && y == snake_body[i][1])
                    {
                        cout << "o";
                        is_body_part = true;
                        break;
                    }
                }
                if (!is_body_part)
                    cout << " ";
            }

        }
        cout << endl;
    }
}

void Input()
{
    if (_kbhit())
    {
        char key = _getch();
        new_key = true;
        switch (key)
        {
        case 'w':
            in_key = UP;
            if (direction != DOWN)
                direction = UP;
            break;
        case 's':
            in_key = DOWN;
            if (direction != UP)
                direction = DOWN;
            break;
        case 'a':
            in_key = LEFT;
            if (direction != RIGHT)
                direction = LEFT;
            break;
        case 'd':
            in_key = RIGHT;
            if (direction != LEFT)
                direction = RIGHT;
            break;
        case 27:
            game_over = true;
            break;
        }
    }
}

void playBeep(int frequency, int duration)
{
    Beep(frequency, duration);
}

void SCENE_MENU() {
    sleeptime = 0;
    static int cursor = 0;
    if (new_key) {
        new_key = false;
        switch (in_key)
        {
        case UP:
            cursor--;
            break;
        case DOWN:
            cursor++;
            break;
        case RIGHT:
            screen_cursor = cursor;
            in_key = LEFT;
            new_key = true;
            break;
        default:
            break;
        }
        if (cursor < 0) cursor = menues.size() - 1;
        if (cursor >= menues.size() ) cursor = 0;


        system("CLS");  // ȭ�� �����
        for (int i = 0; i < height / 2; i++)  // ��� ��ġ�� �̵�
            cout << endl;
        for (int i = 0; i < width / 2 - 4; i++)  // ��� ��ġ�� �̵�
            cout << " ";
        cout << ANSI_COLOR_YELLOW "Snake_Game" << endl;
        for (int i = 0; i < menues.size(); i++) {
            if (i == cursor) {
                string imsi;
                for (int j = 0; j < menues[i].size(); ++j) {
                    imsi.push_back(std::toupper(menues[i][j]));
                }
                cout << imsi << endl;
            }
            else
                cout << menues[i] << endl;
        }
    }
}
void SCENE_DISCRIP() {
    
    if (new_key) {
        new_key = false;
        switch (in_key)
        {
        case RIGHT:
            screen_cursor = 0;
            in_key = LEFT;
            new_key = true;
            break;
        default:
            break;
        }
        system("CLS");  // ȭ�� �����
        for (int i = 0; i < height / 2; i++)  // ��� ��ġ�� �̵�
            cout << endl;
        for (int i = 0; i < width / 2 - 4; i++)  // ��� ��ġ�� �̵�
            cout << " ";
        cout << ANSI_COLOR_YELLOW "Snake_Game" << endl;
        cout << "      ���� ���" << endl;
        cout << "����Ű w,a,s,d " << endl;
        cout << "F �� �Ծ� ����" << endl;
        cout << "�������� ��������" << endl;
      //  cout << "���� ������" << endl;
       // cout << "�ݴ������� �̵�" << endl;
        
    }
};
void SCENE_GAME() {
    switch (direction)
    {
    case UP:
        snake_y--;
        break;
    case DOWN:
        snake_y++;
        break;
    case LEFT:
        snake_x--;
        break;
    case RIGHT:
        snake_x++;
        break;
    }

    // ���� �ε����� �� ���� ����
    if (snake_x == 0 || snake_x == width - 1 || snake_y == 0 || snake_y == height - 1)
        game_over = true, bgmEnd = false;

    // �ڱ� �ڽſ� �ε����� �� ���� ����
    for (int i = 1; i < snake_length; i++)
    {
        if (snake_x == snake_body[i][0] && snake_y == snake_body[i][1])
            game_over = true;
    }
    // ���� �Ա�
    if (snake_x == food_x && snake_y == food_y)
    {
        snake_length++;
        food_x = rand() % (width - 2) + 1;
        food_y = rand() % (height - 2) + 1;
        Beep(100, 10);
        Beep(300, 10);
        Beep(500, 10);
    }
    // �� �� ���� ����
    for (int i = snake_length - 1; i > 0; i--)
    {
        snake_body[i][0] = snake_body[i - 1][0];
        snake_body[i][1] = snake_body[i - 1][1];
    }
    snake_body[0][0] = snake_x;
    snake_body[0][1] = snake_y;
    sleeptime = _SLEEP_INIT_ - snake_length * _SLEEP_LAMP_;
    Draw();
    if (game_over){
    new_key = true; 
    sleeptime = 0;
    screen_cursor = 11;
    }
}

void SCENE_GameOver()
{
    bgmEnd = false;
    // ���� ����Ʈ
    for (int i = 0; i < 1; i++)
    {

        // ���� ���� ��ε� ���
        playBeep(100, 20);
        playBeep(800, 20);
        playBeep(100, 20);
        playBeep(800, 20);
        Sleep(200);
        playBeep(261, 150); // C4
        playBeep(400, 50); // A3
        Sleep(150);
        playBeep(400, 100); // G3
        playBeep(400, 100); // F3
        playBeep(350, 150); // B2
        playBeep(300, 150); // B2
        playBeep(261, 300); // B2

        Sleep(100);
    }
    system("CLS");  // ȭ�� �����
    for (int i = 0; i < height / 2; i++)  // ��� ��ġ�� �̵�
        cout << endl;
    for (int i = 0; i < width / 2 - 4; i++)  // ��� ��ġ�� �̵�
        cout << " ";
    cout << "GameOver!" << endl;
    cout << "�ƹ� Ű�� ���� �޴���" << endl;
    int nothing;
    _getch();
    // ����ȭ������ ���ư���.
    screen_cursor = 0;
    new_key = true;
    game_over = false;
    in_key = LEFT;
    Setup();
}


void Logic()
{
    switch (screen_cursor)
    {
    case 0:
        SCENE_MENU();
        break;
    case 1:
        SCENE_GAME();
        break;
    case 2:
        SCENE_DISCRIP();
        break;
    case 3:
        screen_cursor = 12;//close
        break;
    case 10://Ư���޴�
        screen_cursor = 12;
        break;
    case 11:
        SCENE_GameOver();
        break;
    default:
        screen_cursor = 12;
        break;
    }
    /*
   
    */
    
}


int main()
{

    // �õ� ����
    srand(static_cast<unsigned>(time(0)));

    // �ܼ� â ũ�� ����
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT windowSize = { 0, 0, width, height };
    SetConsoleWindowInfo(consoleHandle, TRUE, &windowSize);

    Setup();

    std::thread bgMusicThread(bgm);
    bgMusicThread.detach();
    while (1)
    {
        Input();
        Logic();
        Sleep(sleeptime);  // ���� �ӵ� ���� (100ms���� ������Ʈ)
        if (screen_cursor == 12) break;
    }
    return 0;
}
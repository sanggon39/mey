#pragma once 
//#define _IS_THIS_HEADER_INCLUDE//한번 한 메인은 다시 빌드하지않음
#include <iostream>
#include<conio.h>
#include <Windows.h>

#define Key_ESC 27//ESC키 입력해두기
#define Key_LEFT 'a'
#define Key_RIGHT 'd'
#define Key_ENTER 13


#define ANSI_COLOR_RED      "\x1b[31m"
#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_YELLOW   "\x1b[33m"
#define ANSI_COLOR_BLUE     "\x1b[34m"
#define ANSI_COLOR_MAGENTA  "\x1b[35m"
#define ANSI_COLOR_CYAN     "\x1b[36m"
#define ANSI_COLOR_RESET    "\x1b[0m"

namespace MuSoeun
{
	void gotoxy(int x, int y) {
		//x, y 좌표 설정
		COORD pos = { x,y };
		//커서 이동
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	}
	
	void SetCursorState(bool visible)
	{
		CONSOLE_CURSOR_INFO consoleCursorInfo;
		consoleCursorInfo.bVisible = visible;
		consoleCursorInfo.dwSize = 1;
		SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &consoleCursorInfo);
	}
	class MgameLoop
	{
	public:
		MgameLoop() {}//생성자
		~MgameLoop() {}//소멸자
		bool isGameRunning = false;

		void Initialize() {
			SetCursorState(false);
			gotoxy(3, 14);
			std::cout << ANSI_COLOR_RESET"게임 초기화중" << std::endl;
			isGameRunning = true;
			
		}
		void Release()
		{
			gotoxy(3, 15);
			std::cout << ANSI_COLOR_RESET "종료중" << std::endl;
		}
		void Update()
		{
			gotoxy(3, 15);
			std::cout << ANSI_COLOR_RESET "게임 키입력대기" << std::endl;
			if (_kbhit())
			{
				keyEvent(_getch());
			}
		}
		void Render() {
			gotoxy(3, 16);
			std::cout << ANSI_COLOR_RESET"게임 화면 그리기" << std::endl;
		}
		void Run()
		{
			Initialize();
			while (isGameRunning)
			{
				Update();
				Render();
			}
			Release();
		}

		void keyEvent(char Keyinput)
		{
			switch (Keyinput)
			{
			case Key_ESC://27
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_CYAN "ESC눌림  " << std::endl;
				break;
			case Key_LEFT://a
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_YELLOW "왼쪽눌림  " << std::endl;
				break;
			case Key_RIGHT://d
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_GREEN "오른쪽눌림" << std::endl;
				break;
			case Key_ENTER: //13
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_RED "엔터눌림  " << std::endl;
				break;
			default:
				//빨간점을 찍으면 브레이크 포인트를 찍을수 이다
				isGameRunning = true;
				break;

			}
		}
	};
}
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
		bool isPause = false;
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
		
		void RenderRest()
		{
			gotoxy(3, 20);
			std::cout << "                                " << std::endl;
			gotoxy(3, 22);
			std::cout << "                                " << std::endl;
			gotoxy(7, 22);
			std::cout << "                                " << std::endl;
		}
		void gem()
		{
			gotoxy(3, 20);
			std::cout << ANSI_COLOR_RESET "종료 하시겠습니까?  " << std::endl;
			gotoxy(3, 22);
			std::cout << ANSI_COLOR_RESET "[  예  ]  " << std::endl;
			gotoxy(15, 22);
			std::cout << ANSI_COLOR_RESET "[아니오]  " << std::endl;

			bool rd=false;
			bool ld=false;
			while (isPause) {
				if (_kbhit())
				{
					char kinput = _getch();
					switch (kinput)
					{
					case Key_LEFT:

						if (rd) {
							gotoxy(15, 22);
							std::cout << ANSI_COLOR_RESET"[아니오]  " << std::endl;
						}
						if (ld == false) {
							gotoxy(3, 22);
							std::cout << ANSI_COLOR_YELLOW"[  예  ]  " << std::endl;

						}
						ld = true;
						rd = false;
						break;
					case Key_RIGHT:
						if (ld) {
							gotoxy(3, 22);
							std::cout << ANSI_COLOR_RESET"[  예  ]  " << std::endl;
						}
						if (rd == false) {
							gotoxy(15, 22);
							std::cout << ANSI_COLOR_YELLOW"[아니오]  " << std::endl;
						}
						rd = true;
						ld = false;
						break;
					case Key_ENTER:
						if (ld) {
							RenderRest();
							isPause = false;
							isGameRunning = false;
						}
						if (rd) {
							RenderRest();
							isPause = false;
							isGameRunning = true;
						}
						break;
					default:
						//isGameRunning = true;
						break;
					}
				}
			}
		}

		void keyEvent(char Keyinput)
		{
			switch (Keyinput)
			{
			case Key_ESC://27
				isPause = true;
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_CYAN "ESC눌림  " << std::endl;
				gem();
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
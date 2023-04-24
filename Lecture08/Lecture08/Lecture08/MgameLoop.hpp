#pragma once 
//#define _IS_THIS_HEADER_INCLUDE//�ѹ� �� ������ �ٽ� ������������
#include <iostream>
#include<conio.h>
#include <Windows.h>

#define Key_ESC 27//ESCŰ �Է��صα�
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
		//x, y ��ǥ ����
		COORD pos = { x,y };
		//Ŀ�� �̵�
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
		MgameLoop() {}//������
		~MgameLoop() {}//�Ҹ���
		bool isGameRunning = false;

		void Initialize() {
			SetCursorState(false);
			gotoxy(3, 14);
			std::cout << ANSI_COLOR_RESET"���� �ʱ�ȭ��" << std::endl;
			isGameRunning = true;
			
		}
		void Release()
		{
			gotoxy(3, 15);
			std::cout << ANSI_COLOR_RESET "������" << std::endl;
		}
		void Update()
		{
			gotoxy(3, 15);
			std::cout << ANSI_COLOR_RESET "���� Ű�Է´��" << std::endl;
			if (_kbhit())
			{
				keyEvent(_getch());
			}
		}
		void Render() {
			gotoxy(3, 16);
			std::cout << ANSI_COLOR_RESET"���� ȭ�� �׸���" << std::endl;
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
				std::cout << ANSI_COLOR_CYAN "ESC����  " << std::endl;
				break;
			case Key_LEFT://a
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_YELLOW "���ʴ���  " << std::endl;
				break;
			case Key_RIGHT://d
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_GREEN "�����ʴ���" << std::endl;
				break;
			case Key_ENTER: //13
				gotoxy(2, 5);
				std::cout << ANSI_COLOR_RED "���ʹ���  " << std::endl;
				break;
			default:
				//�������� ������ �극��ũ ����Ʈ�� ������ �̴�
				isGameRunning = true;
				break;

			}
		}
	};
}
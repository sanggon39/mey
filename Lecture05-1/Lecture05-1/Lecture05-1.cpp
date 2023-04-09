// Lecture05-1.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>

int print_title_sereen()
{
	std::cout << "*****************************" << std::endl;
	std::cout << "*                           *" << std::endl;
	std::cout << "*       지렁이 게임         *" << std::endl;
	std::cout << "*      (Snake Bite)         *" << std::endl;
	std::cout << "*  1. 게임 시작             *" << std::endl;
	std::cout << "*  2.게임설명               *" << std::endl;
	std::cout << "*  3.게임랭킹보기           *" << std::endl;
	std::cout << "*  4.게임종료 (ESC)         *" << std::endl;
	std::cout << "*****************************"  << std::endl;
	return 0;

}
int print_introduction_screen()
{
	std::cout<<" *****************************" << std::endl;
	std::cout << "ㅣ   게임설명 화면입니다    ㅣ" << std::endl;
	std::cout << "ㅣ      메뉴얼이엇던 것     ㅣ" << std::endl;
	std::cout << " *****************************" << std::endl;
	std::cout << " 타이틀화면으로 돌아갈깡?(Y/S)" << std::endl;
	return 0;
}

void gotoxy(int x, int y)
{
	COORD pos = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

int print_game_screen(int stage_width, int stage_height)
{

	for (int i = 0; i < stage_width; i++) {
		gotoxy(i, 0);
		std::cout << "■" << std::endl;
	}
	for (int i = 0; i < stage_height; i++) {
		gotoxy(0, i);
		std::cout << "■" << std::endl;
	}
	for (int i = 0; i < stage_height; i++) {
		gotoxy(stage_width, i);
		std::cout << "■" << std::endl;
	}
	for (int i = 0; i <= stage_width; i++) {
		gotoxy(i, stage_height);
		std::cout << "■" << std::endl;
	}

	return 0;
}

	

//	gotoxy(10, 5);
	//std::cout << "여기가 (10,5)입니다.\n";

		/*if (_kbhit())
		{
			if (_getch() == '2')
			{
				print_introduction_screen();
			}
			if (_getch() == 27 or _getch() == '4')
			{
				printf("\n!게임을 종료합니다!\n");
				break;

			}
		}*/

int main() {

	int game_state = 0;
	int need_regash = 1;
	int is_game_runing = 1;

	while (is_game_runing)
	{
		char key_input = 0;
		switch (game_state)
		{
		case 0:
			if (need_regash) {
				print_title_sereen();
			};
			key_input = _getch();

			need_regash = 0;

			switch (key_input)
			{
			case '1':
				game_state = 1;
				need_regash = 1;
				break;
			case '2':
				game_state = 2;
				need_regash = 1;
				break;
			case '3':
				break;
			case '4':
				is_game_runing = 0;
				break;
			case 27:
				is_game_runing = 0;
			default:
				break;
			}
			break;
		case 1:
			//system("cls");
			if (need_regash) {
				int x = 0;
				int y = 0;
				std::cout << "ㅣ맵을 만들기 위해 x,y값을 입력해주세요!ㅣ" << std::endl;
				std::cout << "*************************************************************" << std::endl;
				scanf_s("%d", &x);
				scanf_s("%d", &y);
				system("cls");
				print_game_screen(x, y);
			};
			key_input = _getch();
			need_regash = 0;
			break;
		case 2:

			if (need_regash) {
				print_introduction_screen();
			}

			key_input = 0;
			key_input = _getch();

			need_regash = 0;

			if (key_input == 'y') {
				game_state = 0;
				need_regash = 1;
			}
			else if (key_input == 'n') {

			}

		default:
			break;
		}

	}
	return 0;


// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

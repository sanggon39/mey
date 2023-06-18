#include <iostream>
#include <windows.h>

int main() {
    // 마리오 테마 음계와 지속시간
    int melody[] = { 262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 330, 262, 196, 262, 262, 196, 262, 294, 247, 262, 262, 294, 330, 262, 262, 294, 330, 262, 330, 349, 392, 330, 349, 392, 330, 262, 196, 262 };
    int duration[] = { 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 300, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 150, 300 };

    // 마리오 테마를 재생
    for (int i = 0; i < sizeof(melody) / sizeof(melody[0]); i++) {
        Beep(melody[i], duration[i]);
        Sleep(duration[i]);
    }

    return 0;
}

// 07.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>

using namespace std;//<<std 를 계속써주기 힘들어서 그냥 네임 스페이스 지정해줌
class Animal
{
public:
    Animal()
    {
        cout << "Animal : 동물이다잉 (탄생)" << endl;
    }
    virtual ~Animal()
    {
        cout << "Animal : 뒤졌어예 (죽음)" << endl;

    }
    virtual void Talk()
    {
        cout << "Animal : 동물이 뭔 말을 해" << endl;
    }
};
class Hamster : public Animal
{
public:
    Hamster()
    {
        cout << "Hamster : 찍(탄생)" << endl;
    }
    ~Hamster()
    {
        cout << "Hamster : 히이이익(죽음)" << endl;
    }

    void Talk()
    {
        cout << "Hamster : 법규나 처머겅" << endl;
    }
};

class Cat : public Animal
{
    //교수님은 프라이빗 쓰는거 안좋아함, 접근 제한..잘 코드 짜지도못하는데 굳이? 나중에 정말 필요해지면 써라
    public:
        Cat()
        {
            //이 함수는 생성자     로컬함수 반대는 전역함수
            cout << "고양이가 강림했다" << endl;
        }
        //생성자는 꼭 생성후 소멸자로 소멸해줘야함
        ~Cat()
        {
            cout << "Cat:끄악(죽음)" << endl;
        }
        void Talk()
        {
            cout << "Cat:야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹야옹" <<endl;
        }
};
class Tiger : public Animal
{
public:
    Tiger()
    {
        cout << "Tiger:크앙(탄생)" << endl;
    }
    ~Tiger()
    {
        cout << "Tifer:호랑죽음" << endl;
    }
    void Talk()
    {
        cout << "Tiger:영어를잘해야 호랑" << endl;
    }

};
int main()
{
   // std::cout <<std::endl;//std란? 네임 스페이스
    //cout <<endl;//위에std를 써줘서 std를 안써줘도 적용됨,BAT  std가 느린편이라 잘 안쓴다estl가 더 빠르다

    //정적 할당
    cout << "냐옹앱시작" << endl;
    cout << endl;

    int AnimalNum = 3;
    Animal** ani = new Animal*[AnimalNum];

    ani[0] = new Tiger();
    ani[1] = new Cat();
    ani[2] = new Hamster();

    for (size_t i = 0; i < AnimalNum; i++)
    {
        ani[i]->Talk();
        delete(ani[i]);
    }

   // Cat *c = new Tiger();
   // Tiger *t = (Tiger*)c;//c를 t로 형변환
    //t->Meow();
  //  t->Roar();

    //delete (t);//객체 죽이기
    //객체지향 부모 상속 
}


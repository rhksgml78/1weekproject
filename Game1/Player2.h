#pragma once
class Player2 : public Actor
{
public:
    MainState	mainState;

    static Player2* Create(string name = "Player2");
    Actor* swim2[18];

    float swimspeed;
    float boostspeed;

    int src, dest;
    float t = 0.0f;
    float zerotime = 0.0f;
    int movecount;
    float movespeed;

    float zerotime2 = 0.0f;
    int movecount2;

    float zerotime3 = 0.0f;
    int movecount3;
    int boostercount;

    float zerotime4 = 0.0f;
    int movecount4;
    int drowncount;
    float playerypos;

    float zerotime5 = 0.0f;
    int movecount5;

    float zerotime6 = 0.0f;
    int movecount6;

    bool isturn;
    bool playerstyle;


private:
    Player2();
    virtual ~Player2();
public:
    void	Update() override;
    void	Release() override;
    void    Animation(GameObject* root);

    //상태에따라 변화하는 함수
    void    idle();
    void    swimming();
    void    booster();
    void    drown();
    void    winner();
    void    loser();

};

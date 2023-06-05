#include "stdafx.h"

Player* Player::Create(string name)
{
    Player* player = new Player();
    player->LoadFile("Swim.xml");


    // IDLE 상태용
    player->swim[0] = Actor::Create();
    player->swim[0]->Update();
    player->swim[1] = Actor::Create();
    player->swim[1]->Update();
    player->swim[0]->LoadFile("SwimIdle0.xml");
    player->swim[1]->LoadFile("SwimIdle1.xml");

    // SWIMMING & BOOSTER 상태용
    player->swim[2] = Actor::Create();
    player->swim[2]->Update();
    player->swim[3] = Actor::Create();
    player->swim[3]->Update();
    player->swim[4] = Actor::Create();
    player->swim[4]->Update();
    player->swim[5] = Actor::Create();
    player->swim[5]->Update();
    player->swim[2]->LoadFile("SwimIng0.xml");
    player->swim[3]->LoadFile("SwimIng1.xml");
    player->swim[4]->LoadFile("SwimIng2.xml");
    player->swim[5]->LoadFile("SwimIng3.xml");

    // DROWN 상태용
    player->swim[6] = Actor::Create();
    player->swim[6]->Update();
    player->swim[7] = Actor::Create();
    player->swim[7]->Update();
    player->swim[8] = Actor::Create();
    player->swim[8]->Update();
    player->swim[9] = Actor::Create();
    player->swim[9]->Update();
    player->swim[6]->LoadFile("SwimDrown0.xml");
    player->swim[7]->LoadFile("SwimDrown1.xml");
    player->swim[8]->LoadFile("SwimDrown2.xml");
    player->swim[9]->LoadFile("SwimDrown3.xml");

    // WIN 상태용
    player->swim[10] = Actor::Create();
    player->swim[10]->Update();
    player->swim[11] = Actor::Create();
    player->swim[11]->Update();
    player->swim[12] = Actor::Create();
    player->swim[12]->Update();
    player->swim[13] = Actor::Create();
    player->swim[13]->Update();
    player->swim[10]->LoadFile("SwimWin0.xml");
    player->swim[11]->LoadFile("SwimWin1.xml");
    player->swim[12]->LoadFile("SwimWin2.xml");
    player->swim[13]->LoadFile("SwimWin3.xml");

    // LOSE 상태용
    player->swim[14] = Actor::Create();
    player->swim[14]->Update();
    player->swim[15] = Actor::Create();
    player->swim[15]->Update();
    player->swim[16] = Actor::Create();
    player->swim[16]->Update();
    player->swim[17] = Actor::Create();
    player->swim[17]->Update();
    player->swim[14]->LoadFile("SwimLose0.xml");
    player->swim[15]->LoadFile("SwimLose1.xml");
    player->swim[16]->LoadFile("SwimLose2.xml");
    player->swim[17]->LoadFile("SwimLose3.xml");

    player->src = player->dest = 0;
    player->t = 1.0f;
    player->movespeed = 1.0f;

    // 기본상태 IDLE
    player->movecount = 0;
    player->zerotime = 0.0f;
    // 기본수영상태 SWIMMING
    player->movecount2 = 0; // 0번xml 부터 1번xml 까지
    player->zerotime2 = 0.0f;
    // 부스터수영상태 BOOSTER
    player->movecount3 = 2; // 2번xml 부터 5번xml 까지
    player->zerotime3 = 0.0f;
    player->boostercount = 0; // 부스터상태일때 일정시간 카운트후 일반수영상태로 되돌리기용
    // 물에빠진상태 DROWN
    player->movecount4 = 6; // 6번xml 부터 10번xml 까지
    player->zerotime4 = 0.0f;
    player->drowncount = 0; // 물에빠진상태일때 일정시간 카운트후 일반수영상태로 되돌리기용
    player->playerypos = 0; // 물에빠지기바로전 플레이어의 수면높이를 되돌릴 저장할 변수
    // 승리상태 WINNER
    player->movecount5 = 10; // 0번xml 부터 1번xml 까지
    player->zerotime5 = 0.0f;
    // 패배상태 LOSER
    player->movecount6 = 14; // 0번xml 부터 1번xml 까지
    player->zerotime6 = 0.0f;

    // 플레이어 방향 회전용 변수
    player->isturn = false;

    // 플레이어 스킨타입 설정용 변수
    player->playerstyle = true;

    // 플레이어 수영 속도 설정용 변수
    player->swimspeed = 5.0f; // 권장 스피드 5.0f
    player->boostspeed = 10.0f; // 권장 스피드 10.0f
    player->mainState = MainState::IDLE;

    return player;
}

Player::Player()
{
}

Player::~Player()
{
}

void Player::Update()
{
    //플레이어의 스킨을 정하는 불변수 조건문
    //if (playerstyle) // 백인 스타일
    //    texture->LoadFile("swim.png");
    //else if(!playerstyle) // 흑인 스타일
    //    texture->LoadFile("swim2.png");

    switch (mainState) // 캐릭터 상태별로 함수를 불러온다
    {
    case MainState::IDLE: idle();
        break; // 게임 시작 전 기본상태, 혹은 대기중인상태
    case MainState::SWIMMING: swimming();
        break; // 게임 시작직후 기본 수영상태
    case MainState::BOOSTER: booster();
        break; // 커맨드 입력 성공시 부스터 상태로
    case MainState::DROWN: drown();
        break; // 커맨드 입력 실패시 멈춰서 허우적대는 상태로
    case MainState::WINNER: winner();
        break; // 게임종료시 먼저 도착한 플레이어는 승리상태로
    case MainState::LOSER: loser();
        break; // 게임종료시 도착하지 못한 플레이어는 패배상태로
    }


    if (isturn) // 턴이 true일때 로드 파일 카메라반대방향으로 출발하기때문에 Y 180도 회전되어있음
    {
        swim[0]->LoadFile("SwimIdle0turn.xml");
        swim[1]->LoadFile("SwimIdle1turn.xml");
        swim[2]->LoadFile("SwimIng0turn.xml");
        swim[3]->LoadFile("SwimIng1turn.xml");
        swim[4]->LoadFile("SwimIng2turn.xml");
        swim[5]->LoadFile("SwimIng3turn.xml");
        swim[6]->LoadFile("SwimDrown0turn.xml");
        swim[7]->LoadFile("SwimDrown1turn.xml");
        swim[8]->LoadFile("SwimDrown2turn.xml");
        swim[9]->LoadFile("SwimDrown3turn.xml");
    }
    else if (!isturn) // 턴이 false일때 로드 파일 카메라 방향으로 바라보는것은 Y 0도 상태임
    {
        swim[0]->LoadFile("SwimIdle0.xml");
        swim[1]->LoadFile("SwimIdle1.xml");
        swim[2]->LoadFile("SwimIng0.xml");
        swim[3]->LoadFile("SwimIng1.xml");
        swim[4]->LoadFile("SwimIng2.xml");
        swim[5]->LoadFile("SwimIng3.xml");
        swim[6]->LoadFile("SwimDrown0.xml");
        swim[7]->LoadFile("SwimDrown1.xml");
        swim[8]->LoadFile("SwimDrown2.xml");
        swim[9]->LoadFile("SwimDrown3.xml");
    }

    Actor::Update();
}

void Player::Release()
{
    for (auto it = children.begin(); it != children.end(); it++)
    {
        SafeRelease(it->second);
    }
    delete this;
}

void Player::Animation(GameObject* root) // 애니매이션 관련 함수, 위치보간x 각도보간.
{
    GameObject* _src = swim[src]->Find(root->name);
    GameObject* _dest = swim[dest]->Find(root->name);
    //root->SetLocalPos(Util::Lerp(_src->GetLocalPos(),
    //    _dest->GetLocalPos(), t));
    root->rotation = Util::QuaternionToYawPtichRoll(
        Util::Lerp(
            Quaternion::CreateFromYawPitchRoll(_src->rotation.y, _src->rotation.x, _src->rotation.z),
            Quaternion::CreateFromYawPitchRoll(_dest->rotation.y, _dest->rotation.x, _dest->rotation.z)
            , t));
    //root->rotation = Util::Lerp(_src->rotation, _dest->rotation, t);
    for (auto it = root->children.begin(); it != root->children.end(); it++)
    {
        Animation(it->second);
    }
}

void Player::idle() // 게임시작 전 상태 기본
{
    playerypos = position.y; // 수면높이 y축 높이를 저장해두고있는다.

    if (TIMER->GetTick(zerotime, movespeed))
    {
        t = 0.0f;
        dest = movecount;
        movecount++;
        if (movecount > 1)
        {
            movecount = 0;
        }
    }
    if (t <= 1.0f)
    {
        Animation(this);
        t += 2 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}

void Player::swimming()  // 기본 출발 상태일때 애니매이션
{
    playerypos = position.y; // 수면높이 y축 높이를 저장해두고있는다.

    if (movecount2 >= 2)
    {
        if (!isturn)
        {
            MoveWorldPos(FORWARD * swimspeed * DELTA);
        }
        else if (isturn)
        {
            MoveWorldPos(-FORWARD * swimspeed * DELTA);
        }
    }

    if (TIMER->GetTick(zerotime2, movespeed))
    {
        t = 0.0f;
        dest = movecount2;
        movecount2++;
        if (movecount2 > 5)
        {
            movecount2 = 2;
        }
    }

    if (t <= 1.0f)
    {
        Animation(this);
        t += 2 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}

void Player::booster() // 커맨드입력 성공 상태일때 애니매이션
{
    playerypos = position.y; // 수면높이 y축 높이를 저장해두고있는다.

    if (movecount3 >= 2)
    {
        if (!isturn)
        {
            MoveWorldPos(FORWARD * boostspeed * DELTA);
        }
        else if (isturn)
        {
            MoveWorldPos(-FORWARD * boostspeed * DELTA);
        }
    }

    if (TIMER->GetTick(zerotime3, 0.5))
    {
        t = 0.0f;
        dest = movecount3;
        movecount3++;
        if (movecount3 > 5)
        {
            movecount3 = 2;
            boostercount++;
            if (boostercount == 1)
            {
                boostercount = 0;
                mainState = MainState::SWIMMING;
            }
        }
    }
    if (t <= 1.0f)
    {
        Animation(this);
        t += 4 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}

void Player::drown()  // 커맨드입력 실패상태일때 애니매이션
{
    if (movecount4 >= 6)
    {
        if (movecount4 % 2 == 0) // 물에빠져서 허우적대는 느낌으로 오르락내리락함
        {
            MoveWorldPos(-UP * 3 * DELTA); // 조금씩 물밑으로 내려감
        }
        else
            MoveWorldPos(UP * 3 * DELTA); // 조금씩 물위로 올라감

    }

    if (TIMER->GetTick(zerotime4, 0.5))
    {
        t = 0.0f;
        dest = movecount4;
        movecount4++;
        if (movecount4 > 9)
        {
            movecount4 = 6;
            drowncount++;
            if (drowncount == 1)
            {
                drowncount = 0;
                position.y = 0; // 다시수영상태로 돌릴때 저장된높이로 세팅해준다.
                mainState = MainState::SWIMMING;
            }
        }
    }
    if (t <= 1.0f)
    {
        Animation(this);
        t += 4 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}

void Player::winner() // 승리상태일때 애니매이션
{
    position.y = playerypos; // 다시수영상태로 돌릴때 저장된높이로 세팅해준다.

    if (TIMER->GetTick(zerotime5, 2.0f))
    {
        t = 0.0f;
        dest = movecount5;
        movecount5++;
        if (movecount5 > 13)
        {
            movecount5 = 10;

        }
    }
    if (t <= 1.0f)
    {
        Animation(this);
        t += 4 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}

void Player::loser() // 패배상태일때 애니매이션
{
    position.y = playerypos; // 다시수영상태로 돌릴때 저장된높이로 세팅해준다.

    if (TIMER->GetTick(zerotime6, 2.0f))
    {
        t = 0.0f;
        dest = movecount6;
        movecount6++;
        if (movecount6 > 17)
        {
            movecount6 = 14;
        }
    }
    if (t <= 1.0f)
    {
        Animation(this);
        t += 4 * DELTA;
        if (t > 1.0f)
        {
            t = 1.0f;
            src = dest;
        }
    }
}


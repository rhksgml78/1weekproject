#include "stdafx.h"

Player2* Player2::Create(string name)
{
    Player2* player = new Player2();
    player->LoadFile("Swim2.xml");

    // IDLE ���¿�
    player->swim2[0] = Actor::Create();
    player->swim2[0]->Update();
    player->swim2[1] = Actor::Create();
    player->swim2[1]->Update();
    player->swim2[0]->LoadFile("SwimIdle0.xml");
    player->swim2[1]->LoadFile("SwimIdle1.xml");

    // SWIMMING & BOOSTER ���¿�
    player->swim2[2] = Actor::Create();
    player->swim2[2]->Update();
    player->swim2[3] = Actor::Create();
    player->swim2[3]->Update();
    player->swim2[4] = Actor::Create();
    player->swim2[4]->Update();
    player->swim2[5] = Actor::Create();
    player->swim2[5]->Update();
    player->swim2[2]->LoadFile("SwimIng0.xml");
    player->swim2[3]->LoadFile("SwimIng1.xml");
    player->swim2[4]->LoadFile("SwimIng2.xml");
    player->swim2[5]->LoadFile("SwimIng3.xml");

    // DROWN ���¿�
    player->swim2[6] = Actor::Create();
    player->swim2[6]->Update();
    player->swim2[7] = Actor::Create();
    player->swim2[7]->Update();
    player->swim2[8] = Actor::Create();
    player->swim2[8]->Update();
    player->swim2[9] = Actor::Create();
    player->swim2[9]->Update();
    player->swim2[6]->LoadFile("SwimDrown0.xml");
    player->swim2[7]->LoadFile("SwimDrown1.xml");
    player->swim2[8]->LoadFile("SwimDrown2.xml");
    player->swim2[9]->LoadFile("SwimDrown3.xml");

    // WIN ���¿�
    player->swim2[10] = Actor::Create();
    player->swim2[10]->Update();
    player->swim2[11] = Actor::Create();
    player->swim2[11]->Update();
    player->swim2[12] = Actor::Create();
    player->swim2[12]->Update();
    player->swim2[13] = Actor::Create();
    player->swim2[13]->Update();
    player->swim2[10]->LoadFile("SwimWin0.xml");
    player->swim2[11]->LoadFile("SwimWin1.xml");
    player->swim2[12]->LoadFile("SwimWin2.xml");
    player->swim2[13]->LoadFile("SwimWin3.xml");

    // LOSE ���¿�
    player->swim2[14] = Actor::Create();
    player->swim2[14]->Update();
    player->swim2[15] = Actor::Create();
    player->swim2[15]->Update();
    player->swim2[16] = Actor::Create();
    player->swim2[16]->Update();
    player->swim2[17] = Actor::Create();
    player->swim2[17]->Update();
    player->swim2[14]->LoadFile("SwimLose0.xml");
    player->swim2[15]->LoadFile("SwimLose1.xml");
    player->swim2[16]->LoadFile("SwimLose2.xml");
    player->swim2[17]->LoadFile("SwimLose3.xml");

    player->src = player->dest = 0;
    player->t = 1.0f;
    player->movespeed = 1.0f;

    // �⺻���� IDLE
    player->movecount = 0;
    player->zerotime = 0.0f;
    // �⺻�������� SWIMMING
    player->movecount2 = 0; // 0��xml ���� 1��xml ����
    player->zerotime2 = 0.0f;
    // �ν��ͼ������� BOOSTER
    player->movecount3 = 2; // 2��xml ���� 5��xml ����
    player->zerotime3 = 0.0f;
    player->boostercount = 0; // �ν��ͻ����϶� �����ð� ī��Ʈ�� �Ϲݼ������·� �ǵ������
    // ������������ DROWN
    player->movecount4 = 6; // 6��xml ���� 10��xml ����
    player->zerotime4 = 0.0f;
    player->drowncount = 0; // �������������϶� �����ð� ī��Ʈ�� �Ϲݼ������·� �ǵ������
    player->playerypos = 0; // ����������ٷ��� �÷��̾��� ������̸� �ǵ��� ������ ����
    // �¸����� WINNER
    player->movecount5 = 10; // 0��xml ���� 1��xml ����
    player->zerotime5 = 0.0f;
    // �й���� LOSER
    player->movecount6 = 14; // 0��xml ���� 1��xml ����
    player->zerotime6 = 0.0f;

    // �÷��̾� ���� ȸ���� ����
    player->isturn = false;

    // �÷��̾� ��ŲŸ�� ������ ����
    player->playerstyle = true;

    // �÷��̾� ���� �ӵ� ������ ����
    player->swimspeed = 5.0f; // ���� ���ǵ� 5.0f
    player->boostspeed = 10.0f; // ���� ���ǵ� 10.0f
    player->mainState = MainState::IDLE;

    return player;
}

Player2::Player2()
{
}

Player2::~Player2()
{
}

void Player2::Update()
{
    //�÷��̾��� ��Ų�� ���ϴ� �Һ��� ���ǹ�
    //if (playerstyle) // ���� ��Ÿ��
    //    texture->LoadFile("swim.png");
    //else if (!playerstyle) // ���� ��Ÿ��
    //    texture->LoadFile("swim2.png");

    //Find("Head")->texture->LoadFile("swim2.png");
    //Find("BodyMesh")->texture->LoadFile("swim2.png");
    //Find("LeftArm")->texture->LoadFile("swim2.png");
    //Find("LeftLeg")->texture->LoadFile("swim2.png");
    //Find("RightArm")->texture->LoadFile("swim2.png");
    //Find("RightLeg")->texture->LoadFile("swim2.png");

    switch (mainState) // ĳ���� ���º��� �Լ��� �ҷ��´�
    {
    case MainState::IDLE: idle(); break; // ���� ���� �� �⺻����, Ȥ�� ������λ���
    case MainState::SWIMMING: swimming(); break; // ���� �������� �⺻ ��������
    case MainState::BOOSTER: booster(); break; // Ŀ�ǵ� �Է� ������ �ν��� ���·�
    case MainState::DROWN: drown(); break; // Ŀ�ǵ� �Է� ���н� ���缭 �������� ���·�
    case MainState::WINNER: winner(); break; // ��������� ���� ������ �÷��̾�� �¸����·�
    case MainState::LOSER: loser(); break; // ��������� �������� ���� �÷��̾�� �й���·�
    }



    if (isturn) // ���� true�϶� �ε� ���� ī�޶�ݴ�������� ����ϱ⶧���� Y 180�� ȸ���Ǿ�����
    {
        swim2[0]->LoadFile("SwimIdle0turn.xml");
        swim2[1]->LoadFile("SwimIdle1turn.xml");
        swim2[2]->LoadFile("SwimIng0turn.xml");
        swim2[3]->LoadFile("SwimIng1turn.xml");
        swim2[4]->LoadFile("SwimIng2turn.xml");
        swim2[5]->LoadFile("SwimIng3turn.xml");
        swim2[6]->LoadFile("SwimDrown0turn.xml");
        swim2[7]->LoadFile("SwimDrown1turn.xml");
        swim2[8]->LoadFile("SwimDrown2turn.xml");
        swim2[9]->LoadFile("SwimDrown3turn.xml");
    }
    else if (!isturn) // ���� false�϶� �ε� ���� ī�޶� �������� �ٶ󺸴°��� Y 0�� ������
    {
        swim2[0]->LoadFile("SwimIdle0.xml");
        swim2[1]->LoadFile("SwimIdle1.xml");
        swim2[2]->LoadFile("SwimIng0.xml");
        swim2[3]->LoadFile("SwimIng1.xml");
        swim2[4]->LoadFile("SwimIng2.xml");
        swim2[5]->LoadFile("SwimIng3.xml");
        swim2[6]->LoadFile("SwimDrown0.xml");
        swim2[7]->LoadFile("SwimDrown1.xml");
        swim2[8]->LoadFile("SwimDrown2.xml");
        swim2[9]->LoadFile("SwimDrown3.xml");
    }

    Actor::Update();
}

void Player2::Release()
{
    for (auto it = children.begin(); it != children.end(); it++)
    {
        SafeRelease(it->second);
    }
    delete this;
}

void Player2::Animation(GameObject* root) // �ִϸ��̼� ���� �Լ�, ��ġ����x ��������.
{
    GameObject* _src = swim2[src]->Find(root->name);
    GameObject* _dest = swim2[dest]->Find(root->name);
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

void Player2::idle() // ���ӽ��� �� ���� �⺻
{
    playerypos = position.y; // ������� y�� ���̸� �����صΰ��ִ´�.

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

void Player2::swimming()  // �⺻ ��� �����϶� �ִϸ��̼�
{
    playerypos = position.y; // ������� y�� ���̸� �����صΰ��ִ´�.

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

void Player2::booster() // Ŀ�ǵ��Է� ���� �����϶� �ִϸ��̼�
{
    playerypos = position.y; // ������� y�� ���̸� �����صΰ��ִ´�.

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

void Player2::drown()  // Ŀ�ǵ��Է� ���л����϶� �ִϸ��̼�
{
    if (movecount4 >= 6)
    {
        if (movecount4 % 2 == 0) // ���������� �������� �������� ��������������
        {
            MoveWorldPos(-UP * 3 * DELTA); // ���ݾ� �������� ������
        }
        else
            MoveWorldPos(UP * 3 * DELTA); // ���ݾ� ������ �ö�

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
                position.y = 0; // �ٽü������·� ������ ����ȳ��̷� �������ش�.
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

void Player2::winner() // �¸������϶� �ִϸ��̼�
{
    position.y = playerypos; // �ٽü������·� ������ ����ȳ��̷� �������ش�.

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

void Player2::loser() // �й�����϶� �ִϸ��̼�
{
    position.y = playerypos; // �ٽü������·� ������ ����ȳ��̷� �������ش�.

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

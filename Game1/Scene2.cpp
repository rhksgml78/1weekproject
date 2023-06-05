#include "stdafx.h"
#include "Solar.h"
#include "Scene2.h"

Scene2::Scene2()
{

}

Scene2::~Scene2()
{

}

void Scene2::Init()
{
    //�Ű���
    player = Player::Create();
    player->mainState = MainState::IDLE;
    player->SetLocalPosX(3);
    player2 = Player2::Create();
    player2->SetLocalPosX(31);
    player2->mainState = MainState::IDLE;


    dead = Actor::Create();
    dead->LoadFile("Swim.xml");
    isplayer = true; // �÷��̾� true �̸� �÷��̾� ����, false�� �𵨿� dead ����

    exitbutton = UI::Create();
    exitbutton->LoadFile("exitbutton.xml");
    pausebutton = UI::Create();
    pausebutton->LoadFile("pausebutton.xml");
    playbutton = UI::Create();
    playbutton->LoadFile("playbutton.xml");
    cam1pause = UI::Create();
    cam1pause->LoadFile("campause1.xml");
    cam2pause = UI::Create();
    cam2pause->LoadFile("campause2.xml");
    win = UI::Create();
    win->LoadFile("win.xml");
    ismenu = false;
    isstop = false;
    isstoptime = 0;
    isgameover = false;

    // ������ �������ϰ� ���������ϰ� ���⼭ �����ϼ���
    turn_point = 390;
    goal_point = 0;

    //���� �߰�
    SOUND->AddSound("scene2bgm.mp3", "scene2bgm", false);

    //ī�޶�
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Cam2 = Camera::Create();
    Cam2->LoadFile("Cam2.xml");

    Camera::main = Cam;
    Cam->width = App.GetHalfWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetHalfWidth();
    Cam->viewport.height = App.GetHeight();

    Cam2->width = App.GetHalfWidth();
    Cam2->height = App.GetHeight();
    Cam2->viewport.width = App.GetHalfWidth();
    Cam2->viewport.height = App.GetHeight();
    Cam2->viewport.x = App.GetHalfWidth();

    //õ����
    game_ui = Game_ui::Create();

    //���ȣ
    pool = Actor::Create();
    pool->LoadFile("swimmingPool3.xml");
    pool->SetWorldPos(Vector3(-8.5, -3.5f, 15));
    pool2 = Actor::Create();
    pool2->LoadFile("swimmingPool4.xml");
    pool2->SetWorldPosY(-3.5f);

    bg = Actor::Create();
    bg->LoadFile("Bg2.xml");
    // ���� ��ŸƮ 
    game_start = false;
    start_swim = false;
    game_start_timer = 500;
    grid = Grid::Create();
}

void Scene2::Release()
{
    Cam->Release();
    Cam2->Release();
}


void Scene2::Update()
{


    Cam->SetWorldPosX(player->GetWorldPos().x);
    Cam->SetWorldPosY(player->GetWorldPos().y + 15);
    Cam->SetWorldPosZ(player->GetWorldPos().z - 20);
    Cam->rotation.x = 35 * TORADIAN;
    Cam->rotation.y = 0;
    Cam->rotation.z = 0;


    Cam2->SetWorldPosX(player2->GetWorldPos().x);
    Cam2->SetWorldPosY(player2->GetWorldPos().y + 15);
    Cam2->SetWorldPosZ(player2->GetWorldPos().z - 20);
    Cam2->rotation.x = 35 * TORADIAN;
    Cam2->rotation.y = 0;
    Cam2->rotation.z = 0;


    Camera::ControlMainCam();
    cout << player->GetWorldPos().z << endl;
    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    //Hierarchy
    ImGui::Begin("Hierarchy");

    //  ���ȣ
    pool->RenderHierarchy();
    pool2->RenderHierarchy();
    bg->RenderHierarchy();

    // õ����
    game_ui->RenderHierarchy();

    //  �Ű���
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->RenderHierarchy();
    else
    {
        player->RenderHierarchy();
        player2->RenderHierarchy(); // ����� 2 ����
    }
    exitbutton->RenderHierarchy();
    pausebutton->RenderHierarchy();
    playbutton->RenderHierarchy();
    cam1pause->RenderHierarchy();
    cam2pause->RenderHierarchy();
    win->RenderHierarchy();
    Cam2->RenderHierarchy();
    Cam->RenderHierarchy();
    grid->RenderHierarchy();

    ImGui::End();
    //////////////////////////////////////////////////////////
    game_start_timer -= DELTA;



    if (game_start_timer == 200)
    {
        //���� �߰�
        SOUND->Play("scene2bgm");
        start_swim = true;
        if (start_swim)
        {
            player->mainState = MainState::SWIMMING;
            player2->mainState = MainState::SWIMMING;
            start_swim = false;
        }
        game_start = true;

    }
    if (game_start_timer < 2)
    {
        game_ui->evnet_start = true;
        game_logic();
    }

    // turn_point �������ϸ� �÷��̾� ȸ��
    if (player->GetWorldPos().z > turn_point) 
        player->isturn = true;
    if (player2->GetWorldPos().z > turn_point)
        player2->isturn = true;
    if (player->isturn == true && player->GetWorldPos().z < goal_point)
    {
        isgameover = true;
        player->mainState = MainState::WINNER;
        player2->mainState = MainState::LOSER;
    }
    else if (player2->isturn == true && player2->GetWorldPos().z < goal_point)
    {
        isgameover = true;
        player2->mainState = MainState::WINNER;
        player->mainState = MainState::LOSER;
    }







    /// <summary>
    /// /////////////////////////////////////////////////////////////////////////////
    /// </summary>
    grid->Update();
    Cam->Update();
    Cam2->Update();


    //���ȣ
    pool->Update();
    pool2->Update();
    bg->Update();

    //õ����
    if (!ismenu && !isgameover) // �Ͻ����� �����϶� ������Ʈ �ϸ� �ȵǼ� ���ǹ��� �־����ϴ�. -�Ű���
    {
        game_ui->Update();
    }

    //�Ű���
    if (pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.35;
        pausebutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            ismenu = true;
        }
    }
    else if (!pausebutton->MouseOver())
    {
        pausebutton->scale.x = 0.3;
        pausebutton->scale.y = 0.15;
    }
    if (ismenu)
    {
        isstoptime++;
        if (isstoptime % 100 == 50)
        {
            isstop = !isstop;
        }
        TIMER->deltaScaleTime = 0;
    }
    if (exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.35;
        exitbutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            SCENE->ChangeScene("MC")->Init();
        }
    }
    else if (!exitbutton->MouseOver())
    {
        exitbutton->scale.x = 0.3;
        exitbutton->scale.y = 0.15;
    }
    if (playbutton->MouseOver())
    {
        playbutton->scale.x = 0.35;
        playbutton->scale.y = 0.20;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            isstoptime = 0;
            ismenu = false;
            // Ÿ�̸�Ŭ���� ��� ���� �ΰ� Public���� �̵�!
            TIMER->deltaScaleTime = TIMER->deltaTime * App.deltaScale;
        }
    }
    else if (!playbutton->MouseOver())
    {
        playbutton->scale.x = 0.3;
        playbutton->scale.y = 0.15;
    }
    exitbutton->Update();
    pausebutton->Update();
    playbutton->Update();
    win->Update();
    cam1pause->Update();
    cam2pause->Update();


    if (!isplayer) // �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Update();
    else
    {
        player->Update();
        player2->Update();
    }

}

void Scene2::LateUpdate()
{
    //õ����
    if (!ismenu) // �Ͻ����� �����϶� ������Ʈ �ϸ� �ȵǼ� ���ǹ��� �־����ϴ�. -�Ű���
    {
        game_ui->set_pos_ui(player, player2);
    }

}
void Scene2::Render()
{
    Camera::main->Set();
    //grid->Render();
    // 
    pool->Render();
    pool2->Render();
    bg->Render();
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Render();
    else
    {
        player->Render();
        player2->Render();
    }

    // õ����
    if (!isgameover) // ���ӿ������ƴҶ��� ����
    {
        game_ui->Render(); // �Ͻ����������϶� ��ư�� ���������ߵǼ� ��ġ ���⿡ �ξ����ϴ� - �Ű���
    }

    if (ismenu)
    {
        if (isstop)
        {
            cam1pause->Render();
        }
    }
    if (player->mainState == MainState::WINNER)
    {
        //���� �߰�
        SOUND->Play("scene2bgm");
        win->Render();
    }

    Cam2->Set();
    /// <summary>
    /// //////////////////////////////////
    /// </summary>
    pool->Render();
    pool2->Render();
    bg->Render();
    if (!isplayer)// �𵨸��� ��ü�Դϴ� �Ű椤��
        dead->Render();
    else
    {
        player->Render();
        player2->Render();
    }

    // õ����
    if (!isgameover) // ���ӿ������ƴҶ��� ����
    {
        game_ui->Render(); // �Ͻ����������϶� ��ư�� ���������ߵǼ� ��ġ ���⿡ �ξ����ϴ� - �Ű���
    }

    pausebutton->Render();
    if (ismenu)
    {
        exitbutton->Render();
        playbutton->Render();
        if (isstop)
        {
            cam2pause->Render();
        }
    }
    if (player2->mainState == MainState::WINNER)
    {
        //���� �߰�
        SOUND->Play("scene2bgm");
        win->Render();
    }

}
void Scene2::PreRender()
{
}
void Scene2::ResizeScreen()
{
    // Cam->width = App.GetWidth();
    // Cam->height = App.GetHeight();
    // Cam->viewport.width = App.GetWidth();
    // Cam->viewport.height = App.GetHeight();
    // 
    // Cam2->width = App.GetWidth();
    // Cam2->height = App.GetHeight();
    // Cam2->viewport.width = App.GetWidth();
    // Cam2->viewport.height = App.GetHeight();
}
void Scene2::game_logic()
{
    if (game_start)
    {

        if (game_ui->player1_bust == true)
        {
            player->mainState = MainState::BOOSTER;
        }
        else if (game_ui->player1_drown == true)
        {
            player->mainState = MainState::DROWN;
        }
        if (game_ui->player2_bust == true)
        {
            player2->mainState = MainState::BOOSTER;

        }
        else if (game_ui->player2_drown == true)
        {
            player2->mainState = MainState::DROWN;
        }
    }

}

void Scene2::game_manager()
{

}

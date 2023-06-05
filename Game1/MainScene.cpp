#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

void MainScene::Init()
{
    //카메라
    Cam = Camera::Create();
    Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();

    //UI
    ui = UI::Create();
    ui->LoadFile("Background.xml");
    ui2 = UI::Create();
    ui2->LoadFile("Background2.xml");
    ui3 = UI::Create();
    ui3->LoadFile("Background3.xml");

    button = UI::Create();
    button->LoadFile("Button.xml");

    logo = UI::Create();
    logo->LoadFile("Logo.xml");
    logomovex = 1.5;

    park = UI::Create();
    park->LoadFile("park.xml");
    VS = UI::Create();
    VS->LoadFile("VS.xml");
    pelp = UI::Create();
    pelp->LoadFile("pelp.xml");
}

void MainScene::Release()
{
    Cam->Release();

}

void MainScene::Update()
{
    Camera::main->width = App.GetWidth();
    Camera::main->height = App.GetHeight();
    Camera::main->viewport.width = App.GetWidth();
    Camera::main->viewport.height = App.GetHeight();
    Camera::ControlMainCam();
    Cam->SetWorldPos(Vector3(0,0,0));
    Cam->rotation.x = 0;
    Cam->rotation.y = 0;
    Cam->rotation.z = 0;
    Cam->Update();

    //debug
    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());

    
    ImGui::Begin("Hierarchy"); //Hierarchy 시작
    Cam->RenderHierarchy();
    ui->RenderHierarchy();
    ui2->RenderHierarchy();
    ui3->RenderHierarchy();
    logo->RenderHierarchy();
    park->RenderHierarchy();
    VS->RenderHierarchy();
    pelp->RenderHierarchy();
    button->RenderHierarchy();
    ImGui::End(); //Hierarchy 끝

    //버튼 충돌 처리
    if (button->MouseOver())
    {
        button->scale.x = 0.55;
        button->scale.y = 0.33;
        if (INPUT->KeyDown(VK_LBUTTON))
        {
            SCENE->ChangeScene("SC2")->Init();
            cout << "Button Ui Mouse Over" << endl;
        }
    }
    else if (!button->MouseOver())
    {
        button->scale.x = 0.5;
        button->scale.y = 0.3;
    }
    if (logomovex < -1.5f)
    {
        logomovex = 1.5f;
    }
    logomovex -= DELTA*0.2f;
    logo->SetWorldPosX(logomovex);

    //업데이트
    ui->Update();
    ui2->Update();
    logo->Update();
    ui3->Update();
    button->Update();
    park->Update();
    VS->Update();
    pelp->Update();
}

void MainScene::LateUpdate()
{
    
}

void MainScene::Render()
{
    // 카메라 세팅
    Camera::main->Set();

    //렌더
    BLEND->Set(true);
    ui->Render();
    park->Render();
    pelp->Render();
    VS->Render();
    ui3->Render();
    logo->Render();
    ui2->Render();
    button->Render();

}

void MainScene::PreRender()
{
}

void MainScene::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();
}

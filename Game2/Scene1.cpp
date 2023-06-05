#include "stdafx.h"

Scene1::Scene1()
{
 
    Cam = Camera::Create();
  
    Player = Actor::Create();
    Player->mesh = make_shared<Mesh>();
    Player->mesh->LoadFile("6.Edit.mesh");

    Player->shader = make_shared<Shader>();
    Player->shader->LoadFile("6.Cube.hlsl");

    Player->texture = make_shared<Texture>();
    Player->texture->LoadFile("Bold.png");

    grid = Grid::Create();
}

Scene1::~Scene1()
{
   

    Cam->Release();
    Player->Release();
}

void Scene1::Init()
{
    //Cam->LoadFile("Cam.xml");
    Camera::main = Cam;
}

void Scene1::Release()
{
    Player->mesh->SaveFile("6.Edit.mesh");
}


void Scene1::Update()
{
    grid->Update();
    for (int i = 0; i < 4 * 6; i++)
    {
        string ver = "vertex" + to_string(i);
        VertexPT* vertices = (VertexPT*)Player->mesh->vertices;
       
       /* if (ImGui::InputFloat3((ver + "pos").c_str(),
            (float*)&vertices[i].position))
        {
            Player->mesh->Reset();
            break;
        }*/
        if (ImGui::InputFloat2((ver + "uv").c_str(),
            (float*)&vertices[i].uv))
        {
            Player->mesh->Reset();
            break;
        }
    }



    ImGui::Text("FPS: %d", TIMER->GetFramePerSecond());
    Camera::ControlMainCam();
 
    ImGui::Begin("Hierarchy");   
    Cam->RenderHierarchy();
    Player->RenderHierarchy();
    ImGui::End();


    Cam->Update();
    Player->Update();
}

void Scene1::LateUpdate()
{
   
}

void Scene1::PreRender()
{
   
    
}

void Scene1::Render()
{
    Camera::main->Set();
    grid->Render();
    Player->Render();
}

void Scene1::ResizeScreen()
{
    Cam->width = App.GetWidth();
    Cam->height = App.GetHeight();
    Cam->viewport.width = App.GetWidth();
    Cam->viewport.height = App.GetHeight();

   
}

#include "stdafx.h"
#include "Main.h"
#include "MainScene.h"
#include "Scene2.h"

Main::Main()
{

}

Main::~Main()
{

}

void Main::Init()
{
    {
        Xml::XMLDocument* doc = new Xml::XMLDocument();
        Xml::XMLElement* ob = doc->NewElement("Root");
        doc->LinkEndChild(ob);
        ob->SetAttribute("name", "Sun");
        {
            Xml::XMLElement* Transform = doc->NewElement("Transform");
            Xml::XMLElement* Pos = doc->NewElement("Position");
            Xml::XMLElement* Scale = doc->NewElement("Scale");
            Xml::XMLElement* Rot = doc->NewElement("Rotation");
            //   link
            ob->LinkEndChild(Transform);
            Transform->LinkEndChild(Pos);
            Transform->LinkEndChild(Scale);
            Transform->LinkEndChild(Rot);

            //                key  value
            Pos->SetAttribute("X", 1.0f);
            Pos->SetAttribute("Y", 10.0f);
            Pos->SetAttribute("Z", 0.0f);
        }
        doc->SaveFile("../Contents/GameObject/XMLTest.xml");
    }
    //가져올때
    {
        Xml::XMLDocument* doc = new Xml::XMLDocument();
        doc->LoadFile("../Contents/GameObject/XMLTest.xml");
        Xml::XMLElement* ob;
        Xml::XMLElement* trans;
        Xml::XMLElement* Pos;
        ob = doc->FirstChildElement();
  
        trans = ob->FirstChildElement("Transform");
        Pos = trans->FirstChildElement("Position");
     
        cout << ob->Attribute("name") << endl;
        cout << Pos->FloatAttribute("X") << endl;
        cout << Pos->FloatAttribute("Y") << endl;
    }

    SCENE->AddScene("SC2", new Scene2());
    SCENE->AddScene("MC", new MainScene());
    SCENE->ChangeScene("MC")->Init();
}

void Main::Release()
{
    SCENE->Release();
}

void Main::Update()
{
    SCENE->Update();
}

void Main::LateUpdate()
{
    SCENE->LateUpdate();
}
void Main::PreRender()
{
    SCENE->PreRender();
}
void Main::Render()
{
    SCENE->Render();
}

void Main::ResizeScreen()
{
    SCENE->ResizeScreen();
}

int WINAPI wWinMain(HINSTANCE instance, HINSTANCE prevInstance, LPWSTR param, int command)
{
	App.SetAppName(L"Game1");
	App.SetInstance(instance);
    WIN->Create();
    D3D->Create();
	Main * main = new Main();
    main->Init();

	int wParam = (int)WIN->Run(main);


    main->Release();
	SafeDelete(main);
    D3D->DeleteSingleton();
	WIN->DeleteSingleton();

	return wParam;
}
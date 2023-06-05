#include "framework.h"

GameObject::GameObject()
{
	type = ObType::GameObject;
	root = nullptr;
	collider = nullptr;
	visible = true;
	//mesh = make_shared<Mesh>();
}
Actor::Actor()
{
	type = ObType::Actor;
	root = this;
}
GameObject::~GameObject()
{
	mesh.reset();
	shader.reset();
	SafeDelete(collider);
}
Actor::~Actor()
{
}





GameObject* GameObject::Create(string name)
{
	GameObject* temp = new GameObject();
	temp->name = name;
	return temp;
}

void GameObject::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}


void Actor::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

void Actor::ReleaseMember()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		it->second->Release();
	}
	
	obList.clear();
	children.clear();
}

Actor* Actor::Create(string name)
{
	Actor* temp = new Actor();
	temp->name = name;
	return temp;
}


void GameObject::Update()
{

	Transform::Update();


	if (collider)
		collider->Update(this);


	for (auto it = children.begin(); it != children.end(); it++)
		it->second->Update();
}

void GameObject::Render()
{
	if (visible)
	{
		//내가 메쉬가 있을떄 렌더링 시작
		if (mesh and shader)
		{
			mesh->Set();
			Transform::Set();
			shader->Set();

			if (texture)
				texture->Set(1);

			D3D->GetDC()->DrawIndexed(mesh->indexCount, 0, 0);
		}
	}


	if (collider)
		collider->Render();


	for (auto it = children.begin(); it != children.end(); it++)
		it->second->Render();
}
GameObject* GameObject::axis = nullptr;
void GameObject::CreateStaticMember()
{
	axis = new GameObject();
	axis->mesh = make_shared<Mesh>();
	axis->shader = make_shared<Shader>();
	axis->mesh->LoadFile("1.Transform.mesh");
	axis->shader->LoadFile("1.Cube.hlsl");
}

void GameObject::DeleteStaticMember()
{
	SafeDelete(axis);
}

void GameObject::RenderAxis()
{
	if (not GUI->target)return;
	GameObject* target = GUI->target;
	axis->S = Matrix::CreateScale(App.GetHeight() * 0.1f);
	if (not target->parent)
		axis->W = axis->S * target->T;
	else if (worldPos)
		axis->W = axis->S * Matrix::CreateTranslation(target->GetWorldPos());
	else
		axis->W = axis->S * target->T * target->parent->W;

	axis->Render();
}

void GameObject::AddChild(GameObject* child)
{
	if (root->Find(child->name))
		return;
	root->obList[child->name] = child;
	children[child->name] = child;
	child->parent = this;
	child->root = root;
}

GameObject* Actor::Find(string name)
{
	auto it = obList.find(name);
	//찾았다
	if (it != obList.end())
	{
		return it->second;
	}
	return nullptr;
}

bool Actor::DeleteObject(string Name)
{
	if (Name == name) return false;

	auto temp = obList.find(Name);

	if (temp == obList.end())  return false;

	//지워질대상,지워질대상의 부모 포인터
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//부모리스트에서 타겟 비우기
	Parent->children.erase(Parent->children.find(Name));

	for (auto it = Target->children.begin();
		it != Target->children.end(); it++)
	{
		Parent->children[it->second->name] = it->second;
		it->second->parent = Parent;
		//SafeRelease(it->second);
	}
	SafeDelete(Target);
	obList.erase(temp);
	return true;
}

bool Actor::DeleteAllObject(string Name)
{
	if (Name == name) return false;

	auto temp = obList.find(Name);

	if (temp == obList.end())  return false;

	//지워질대상,지워질대상의 부모 포인터
	GameObject* Target = temp->second;
	GameObject* Parent = temp->second->parent;
	//부모리스트에서 타겟 비우기
	Parent->children.erase(Parent->children.find(Name));
	root->obList.erase(root->obList.find(Name));
	while (1)
	{
		if (Target->children.empty())break;
		auto it = Target->children.begin();
		DeleteAllObject(it->first);
	}
	SafeDelete(Target);
	return true;
}

void Actor::Update()
{

	GameObject::Update();
}

void Actor::Render()
{

	//int a = 0;

	GameObject::Render();
}

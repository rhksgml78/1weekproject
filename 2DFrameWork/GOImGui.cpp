#include "framework.h"
bool GameObject::RenderHierarchy()
{
	ImGui::PushID(this);
	if (ImGui::TreeNode(name.c_str()))
	{
		if (ImGui::IsItemToggledOpen() or
			ImGui::IsItemClicked())
		{
			GUI->target = this;
		}
		if (ImGui::Button("addChild"))
		{
			ImGui::OpenPopup("childName");
		}
		if (ImGui::BeginPopup("childName"))
		{
			static char childName[32] = "None";
			ImGui::InputText("childName", childName, 32);
			if (ImGui::Button("G.O"))
			{
				AddChild(GameObject::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("Actor"))
			{
				AddChild(Actor::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("Camera"))
			{
				AddChild(Camera::Create(childName));
			}
			ImGui::SameLine();
			if (ImGui::Button("UI"))
			{
				AddChild(UI::Create(childName));
			}
			ImGui::EndPopup();
		}

		ImGui::SameLine();
		if (ImGui::Button("delete"))
		{
			if (parent == nullptr)
				ImGui::OpenPopup("SearchDeleteName");
			else
				ImGui::OpenPopup("DeleteChild");

		}

		if (ImGui::BeginPopup("SearchDeleteName"))
		{
			static char deleteName[32] = "None";
			ImGui::InputText("deleteName", deleteName, 32);

			if (ImGui::Button("DeleteAll"))
			{
				root->DeleteAllObject(deleteName);
				ImGui::EndPopup();
				ImGui::TreePop();
				ImGui::PopID();
				GUI->target = nullptr;
				return true;
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete2"))
			{
				root->DeleteObject(deleteName);
				ImGui::EndPopup();
				ImGui::TreePop();
				ImGui::PopID();
				GUI->target = nullptr;
				return true;
			}

			ImGui::EndPopup();
		}
		if (ImGui::BeginPopup("DeleteChild"))
		{
			if (ImGui::Button("DeleteAll"))
			{
				//부모한테 접근
				if (parent)
				{
					root->DeleteAllObject(name);
					ImGui::EndPopup();
					ImGui::TreePop();
					ImGui::PopID();
					GUI->target = nullptr;
					return true;
				}
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete2"))
			{
				//부모한테 접근
				if (parent)
				{
					root->DeleteObject(name);
					ImGui::EndPopup();
					ImGui::TreePop();
					ImGui::PopID();
					GUI->target = nullptr;
					return true;
				}
			}
			ImGui::EndPopup();
		}

		// l->r
		for (auto it = children.begin(); it != children.end(); it++)
		{
			if (it->second->RenderHierarchy())
			{
				ImGui::TreePop();
				ImGui::PopID();
				GUI->target = nullptr;
				return true;
			}
		}
		ImGui::TreePop();
	}
	ImGui::PopID();
	return false;
}

void Transform::RenderDetail()
{
	ImGui::Checkbox("WorldPos", &worldPos);
	if (worldPos)
	{
		//get
		Vector3 wol = GetWorldPos();
		if (ImGui::DragFloat3("WorldPos", (float*)&wol, 0.05f))
			//set
			SetWorldPos(wol);
	}
	else
	{
		Vector3 loc = GetLocalPos();
		if (ImGui::DragFloat3("LocalPos", (float*)&loc, 0.05f))
			SetLocalPos(loc);
	}

	ImGui::SliderAngle("rotationX", &rotation.x);
	ImGui::SliderAngle("rotationY", &rotation.y);
	ImGui::SliderAngle("rotationZ", &rotation.z);
	ImGui::DragFloat3("scale", (float*)&scale, 0.05f);
}
void GameObject::RenderDetail()
{
	ImGui::Text(name.c_str());
	ImGui::Checkbox("visible", &visible);
	if (ImGui::BeginTabBar("MyTabBar"))
	{
		if (ImGui::BeginTabItem("Transform"))
		{
			Transform::RenderDetail();
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Mesh"))
		{
			if (mesh)
			{
				ImGui::Text(mesh->file.c_str());
			}
			if (GUI->FileImGui("Save", "Save Mesh",
				".mesh", "../Contents/Mesh"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentPath();
				Util::Replace(&path, "\\", "/");
				if (path.find("/Mesh/") != -1)
				{
					size_t tok = path.find("/Mesh/") + 6;
					path = path.substr(tok, path.length())
						+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				mesh->SaveFile(path);
			}
			ImGui::SameLine();
			if (GUI->FileImGui("Load", "Load Mesh",
				".mesh", "../Contents/Mesh"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentPath();
				Util::Replace(&path, "\\", "/");
				if (path.find("/Mesh/") != -1)
				{
					size_t tok = path.find("/Mesh/") + 6;
					path = path.substr(tok, path.length())
						+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				SafeReset(mesh);
				mesh = RESOURCE->meshes.Load(path);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				SafeReset(mesh);
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Shader"))
		{
			if (shader)
			{
				ImGui::Text(shader->file.c_str());
			}
			if (GUI->FileImGui("Load", "Load Shader",
				".hlsl", "../Shaders"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentPath();
				Util::Replace(&path, "\\", "/");
				if (path.find("/Shaders/") != -1)
				{
					size_t tok = path.find("/Shaders/") + 9;
					path = path.substr(tok, path.length())
						+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				SafeReset(shader);
				shader = RESOURCE->shaders.Load(path);
			}
			ImGui::SameLine();
			if (ImGui::Button("Delete"))
			{
				SafeReset(shader);
			}
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Texture"))
		{
			if (texture)
			{
				texture->RenderDetail();
			}

			if (GUI->FileImGui("Load Texture", "Load Texture",
				".dds,.jpg,.tga,.png,.bmp", "../Contents/Texture"))
			{
				string path = ImGuiFileDialog::Instance()->GetCurrentPath();
				Util::Replace(&path, "\\", "/");
				if (path.find("/Texture/") != -1)
				{
					size_t tok = path.find("/Texture/") + 9;
					path = path.substr(tok, path.length())
						+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				else
				{
					path = ImGuiFileDialog::Instance()->GetCurrentFileName();
				}
				SafeReset(texture);
				texture = RESOURCE->textures.Load(path);
			}

			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Collider"))
		{
			if (collider)
			{
				collider->RenderDetail();
				if (ImGui::Button("Delete"))
				{
					SafeDelete(collider);
				}
			}
			else
			{
				ImGui::Text("Create");
				if (ImGui::Button("Box"))
				{
					collider = new Collider(ColliderType::BOX);
				}
				ImGui::SameLine();
				if (ImGui::Button("OBox"))
				{
					collider = new Collider(ColliderType::OBOX);
				}
				ImGui::SameLine();
				if (ImGui::Button("Sphere"))
				{
					collider = new Collider(ColliderType::SPHERE);
				}
			}
			ImGui::EndTabItem();
		}


		ImGui::EndTabBar();
	}
}
bool GameObject::Intersect(GameObject* target)
{
	if (collider and target->collider)
	{
		return collider->Intersect(target->collider);
	}
	return false;
}
bool GameObject::Intersect(Ray Ray, Vector3& Hit)
{
	if (collider)
	{
		return collider->Intersect(Ray, Hit);
	}
	return false;
}
void Actor::RenderDetail()
{
	GameObject::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar2"))
	{
		if (root == this)
		{
			if (ImGui::BeginTabItem("Actor"))
			{
				if (GUI->FileImGui("Save", "Save Actor",
					".xml", "../Contents/GameObject"))
				{
					string path = ImGuiFileDialog::Instance()->GetCurrentPath();
					Util::Replace(&path, "\\", "/");
					if (path.find("/GameObject/") != -1)
					{
						size_t tok = path.find("/GameObject/") + 12;
						path = path.substr(tok, path.length())
							+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
					}
					else
					{
						path = ImGuiFileDialog::Instance()->GetCurrentFileName();
					}
					SaveFile(path);
				}
				ImGui::SameLine();
				if (GUI->FileImGui("Load", "Load Actor",
					".xml", "../Contents/GameObject"))
				{
					string path = ImGuiFileDialog::Instance()->GetCurrentPath();
					Util::Replace(&path, "\\", "/");
					if (path.find("/GameObject/") != -1)
					{
						size_t tok = path.find("/GameObject/") + 12;
						path = path.substr(tok, path.length())
							+ "/" + ImGuiFileDialog::Instance()->GetCurrentFileName();
					}
					else
					{
						path = ImGuiFileDialog::Instance()->GetCurrentFileName();
					}
					LoadFile(path);
				}
				ImGui::EndTabItem();
			}
		}
		


		ImGui::EndTabBar();
	}
}
void Camera::RenderDetail()
{
	Actor::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("Camera"))
		{
			if (ImGui::Button("ChangeMain"))
			{
				Camera::main = this;
			}
			ImGui::DragFloat("CamSpeed", &mainCamSpeed, 0.05f, 1.0f);
			ImGui::Checkbox("ortho", &ortho);
			ImGui::SliderAngle("fov", &fov,0,180.0f);
			ImGui::DragFloat("nearZ", &nearZ, 0.05f,0.00001f);
			ImGui::DragFloat("farZ", &farZ, 0.05f, 0.00001f,1.0f);
			ImGui::DragFloat("width", &width, 0.05f,1.0f);
			ImGui::DragFloat("height", &height, 0.05f, 1.0f);
			ImGui::DragFloat("x", &viewport.x, 0.05f, 0.0f);
			ImGui::DragFloat("y", &viewport.y, 0.05f, 0.0f);
			ImGui::DragFloat("w", &viewport.width, 0.05f, 1.0f);
			ImGui::DragFloat("h", &viewport.height, 0.05f, 1.0f);

			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}
void UI::RenderDetail()
{
	Actor::RenderDetail();
	if (ImGui::BeginTabBar("MyTabBar3"))
	{
		if (ImGui::BeginTabItem("UI"))
		{
			if (ImGui::Button("LT"))
			{
				pivot = Vector2(0.5f, -0.5f);
			}
			ImGui::SameLine();
			if (ImGui::Button("T"))
			{
				pivot = Vector2(0.0f, -0.5f);
			}
			ImGui::SameLine();
			if (ImGui::Button("RT"))
			{
				pivot = Vector2(-0.5f, -0.5f);
			}

			if (ImGui::Button("L "))
			{
				pivot = Vector2(0.5f, 0.0f);
			}
			ImGui::SameLine();
			if (ImGui::Button("N"))
			{
				pivot = Vector2(0.0f, 0.0f);
			}
			ImGui::SameLine();
			if (ImGui::Button("R "))
			{
				pivot = Vector2(-0.5f, 0.0f);
			}

			if (ImGui::Button("LB"))
			{
				pivot = Vector2(0.5f, 0.5f);
			}
			ImGui::SameLine();
			if (ImGui::Button("B"))
			{
				pivot = Vector2(0.0f, 0.5f);
			}
			ImGui::SameLine();
			if (ImGui::Button("RB"))
			{
				pivot = Vector2(-0.5f, 0.5f);
			}


			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}
}

void UI::Render()
{
	DEPTH->Set(false);
	Actor::Render();
	DEPTH->Set(true);
}

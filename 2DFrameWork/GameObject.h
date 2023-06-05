#pragma once
enum class MainState
{
	IDLE,
	SWIMMING,
	BOOSTER,
	DROWN,
	WINNER,
	LOSER
};
enum class ObType
{
	GameObject,
	Actor,
	Camera,
	Terrain,
	UI,
	Billboard,
	Light,
	Rain,
	Pop
};

class GameObject : public Transform
{
	friend class Actor;
	//static
private:
	static GameObject* axis;

public:
	static GameObject* Create(string name = "GameObject");
	static void CreateStaticMember();
	static void DeleteStaticMember();
	static void RenderAxis();
	//member
protected:
	ObType						type;
	
public:
	shared_ptr<Shader>			shader;
	shared_ptr<Texture>			texture;
	shared_ptr<Mesh>			mesh;
	string						name;	//key
	bool						visible;
	class Collider*				collider;
	class Actor*				root;
	map<string, GameObject*>	children;
	
	//Method
protected:
	GameObject();
	virtual	~GameObject();
	void	SaveObject(Xml::XMLElement* This, Xml::XMLDocument* doc);
	void	LoadObject(Xml::XMLElement* This);
public:
	virtual void	Release();
	virtual void	Update();
	virtual void	Render();
	void			AddChild(GameObject* child);
	virtual bool	RenderHierarchy();
	virtual void	RenderDetail();
	bool            Intersect(GameObject* target);
	bool            Intersect(Ray Ray, Vector3& Hit);
	//Getter Setter
};


class Actor : public GameObject
{
	friend GameObject;
public:
	static Actor*	Create(string name = "Actor");

private:
	
public:
	unordered_map<string, GameObject*> obList;
	string			file;
protected:
	Actor();
	virtual	~Actor();
public:
	virtual void	Release();
	void			ReleaseMember();
	GameObject*		Find(string name);
	bool            DeleteObject(string Name);
	bool            DeleteAllObject(string Name);
	void			SaveFile(string file);
	void			LoadFile(string file);
	virtual void	RenderDetail();
	virtual void	Update();
	virtual void    Render();
	//void			RotationZ() { rotation.z += 0.03f; }
};


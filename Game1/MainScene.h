#pragma once
// 게임시작전 메인 씬
class MainScene : public Scene 
{
private:
	Camera* Cam;
	UI* ui;
	UI* ui2;
	UI* ui3;
	UI* button;
	UI* logo;
	UI* park;
	UI* pelp;
	UI* VS;


	float logomovex;

public:
	MainScene();
	~MainScene();
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;
};


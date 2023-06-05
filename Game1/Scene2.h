#pragma once

class Scene2 : public Scene
{
private:
	// 신관희
	Player* player;
	//Player* player2;
	Player2* player2;
	bool isplayer;

	UI* exitbutton;
	UI* pausebutton;
	UI* playbutton;
	UI* cam1pause;
	UI* cam2pause;
	UI* win;
	bool ismenu;
	bool isstop;
	int isstoptime;
	int turn_point;
	int goal_point;
	bool isgameover;


	// 카메라
	Camera* Cam;
	Camera* Cam2;


	// 천재진
	class Game_ui* game_ui;

	// 김두호
	Actor* pool;
	Actor* pool2;
	Actor* bg;

	// 수업관련
	Grid* grid;
	//Actor*  player2;
	Actor* plane;
	Actor* dead;
	Vector3 src, dest;
	float   t;
	float   dis;
	float	srcR, destR;
	float   tR;
	float   disR;
	Actor* ui;


	// 게임시작

	bool	game_start;
	bool	start_swim;

	int 	game_start_timer;











public:
	Scene2();
	~Scene2();
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void PreRender() override;
	virtual void ResizeScreen() override;

	void	game_logic();
	void	game_manager();
};


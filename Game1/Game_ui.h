#pragma once
class Game_ui : public Actor
{
public:
	static Game_ui* Create(string name = "Game_ui");

	char* p1_letters;
	vector<char>	p1_random_letters;
	vector<char>	inputed_p1;
	int				input_count;

	char* p2_letters;
	vector<char>	p2_random_letters;
	vector<char>	inputed_p2;
	int				input_count2;

public:
	bool			evnet_start;
	float			event_cycle_time;
	float			event_limit_time;

public:
	bool			player1_bust;
	bool			player2_bust;

	bool			player1_drown;
	bool			player2_drown;




private:
	Game_ui();
	virtual ~Game_ui();

public:

	void	Update() override;
	void	Release() override;

	void	visible_gameui(bool true_false);

	vector<char>	 make_random_p1
	(char*& _p1_letter, int size);

	vector<char>	 make_random_p2
	(char*& _p2_letter, int size);

	bool			 checked_input
	(const vector<char>& computerLetters, const vector<char>& playerInput, int inputCount);


	void			set_pos_ui(Actor* _player1, Actor* _player2);
	void			set_im_ui();
	void			set_im_ui2();

	void			p1_element_update();
	void			p2_element_update();

public:

	bool			give_bust(bool _canbost);

};


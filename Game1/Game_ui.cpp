#include "stdafx.h"

Game_ui* Game_ui::Create(string name)
{
	Game_ui* temp = new Game_ui();
	temp->LoadFile("Game_ui(1).xml");

	return temp;
}

Game_ui::Game_ui()
{
	p1_letters = new char[6];
	p1_letters[0] = { 'q' };
	p1_letters[1] = { 'w' };
	p1_letters[2] = { 'e' };
	p1_letters[3] = { 'a' };
	p1_letters[4] = { 's' };
	p1_letters[5] = { 'd' };

	p1_random_letters = make_random_p1(p1_letters, 6);

	input_count = 0;

	/// <summary>
	/// ///////////////////////////
	/// </summary>
	p2_letters = new char[6];
	p2_letters[0] = { '4' };
	p2_letters[1] = { '5' };
	p2_letters[2] = { '6' };
	p2_letters[3] = { '7' };
	p2_letters[4] = { '8' };
	p2_letters[5] = { '9' };

	p2_random_letters = make_random_p2(p2_letters, 6);

	input_count2 = 0;
	/// <summary>
	/// ///////////////////////
	/// </summary>
	evnet_start = false;
	event_cycle_time = 0.0f;
	event_limit_time = 8.0f;

	////////////////////
	player1_bust = false;
	player2_bust = false;

	player1_drown = false;
	player2_drown = false;
}

Game_ui::~Game_ui()
{
}

void Game_ui::Update()
{
	if (INPUT->KeyDown(VK_TAB))
	{
		evnet_start = true;
	}
	if (!evnet_start)
	{
		visible_gameui(false);
	}
	if (evnet_start)
	{
		if (event_cycle_time > 10.0f)
		{
			event_cycle_time = 0.0f;
			event_limit_time = 4.0f;
		}
		if (event_limit_time == 4.0f)
		{
			player1_bust = false;
			player2_bust = false;

			player1_drown = false;
			player2_drown = false;
		}
		event_cycle_time += DELTA; // 이벤트 주기 타이머				10초주기
		event_limit_time -= DELTA; // 이벤트 수행해야하는 타이머		3초안에


		visible_gameui(true);

		p1_element_update();
		p2_element_update();





		cout << " 이벤트 주기 타이머 : " << event_cycle_time << endl;
		cout << " 이벤트 제한 타이머 : " << event_limit_time << endl;


		Actor::Update();
	}

	Actor::Update();
}

void Game_ui::Release()
{
	for (auto it = children.begin(); it != children.end(); it++)
	{
		SafeRelease(it->second);
	}
	delete this;
}

void Game_ui::visible_gameui(bool true_false)
{
	if (true_false == true)
	{
		Find("pos1_1")->visible = true;
		Find("pos1_2")->visible = true;
		Find("pos1_3")->visible = true;
		Find("pos1_4")->visible = true;
		Find("pos1_5")->visible = true;
		Find("pos1_6")->visible = true;
		Find("pos1_7")->visible = true;

		Find("pos2_1")->visible = true;
		Find("pos2_2")->visible = true;
		Find("pos2_3")->visible = true;
		Find("pos2_4")->visible = true;
		Find("pos2_5")->visible = true;
		Find("pos2_6")->visible = true;
		Find("pos2_7")->visible = true;
	}
	else
	{
		Find("pos1_1")->visible = false;
		Find("pos1_2")->visible = false;
		Find("pos1_3")->visible = false;
		Find("pos1_4")->visible = false;
		Find("pos1_5")->visible = false;
		Find("pos1_6")->visible = false;
		Find("pos1_7")->visible = false;

		Find("pos2_1")->visible = false;
		Find("pos2_2")->visible = false;
		Find("pos2_3")->visible = false;
		Find("pos2_4")->visible = false;
		Find("pos2_5")->visible = false;
		Find("pos2_6")->visible = false;
		Find("pos2_7")->visible = false;
	}
}

vector<char> Game_ui::make_random_p1(char*& _p1_letter, int size)
{
	vector<char> mixed_letters;

	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> dis(0, size - 1);

	for (int i = 0; i < 7; i++)
	{
		int index = dis(gen);
		mixed_letters.push_back(_p1_letter[index]);
	}

	return mixed_letters;
}

vector<char> Game_ui::make_random_p2(char*& _p2_letter, int size)
{
	vector<char> mixed_letters2;

	random_device rd2;
	mt19937 gen2(rd2());
	uniform_int_distribution<> dis2(0, size - 1);

	for (int i = 0; i < 7; i++)
	{
		int index2 = dis2(gen2);
		mixed_letters2.push_back(_p2_letter[index2]);
	}

	return mixed_letters2;
}

bool Game_ui::checked_input(const vector<char>& computerLetters, const vector<char>& playerInput, int inputCount)
{
	for (int i = 0; i < inputCount; i++)
	{
		if (playerInput[i] != computerLetters[i])
		{
			return false;
		}
	}

	return true;
}

void Game_ui::set_pos_ui(Actor* _player1, Actor* _player2)
{ // 재진씨 플레이어 머리랑 위치겹쳐져서 따로설정하고 Y축만 좀더 위로 잡았어요 by.관희

	this->Find("player1_ui")->SetWorldPosX(_player1->GetWorldPos().x);
	this->Find("player1_ui")->SetWorldPosY(_player1->GetWorldPos().y + 3.0f);
	this->Find("player1_ui")->SetWorldPosZ(_player1->GetWorldPos().z);

	this->Find("player2_ui")->SetWorldPosX(_player2->GetWorldPos().x);
	this->Find("player2_ui")->SetWorldPosY(_player2->GetWorldPos().y + 3.0f);
	this->Find("player2_ui")->SetWorldPosZ(_player2->GetWorldPos().z);
}

void Game_ui::set_im_ui()
{
	// 키가 알파벳, 값은 1. 회색이미지, 2. 그린이미지
	map<char, pair<string, string>> textureMap =
	{
		{'q', {"q_code.png","qn_code.png"}},
		{'w', {"w_code.png","wn_code.png"}},
		{'e', {"e_code.png","en_code.png"}},
		{'a', {"a_code.png","an_code.png"}},
		{'s', {"s_code.png","sn_code.png"}},
		{'d', {"d_code.png","dn_code.png"}}
	};

	// p1_random_letters의 이미지 설정
		// p1_random_letters 문자를 순회함
			// i < input_count는 판단기준
			// 참 : 녹색이미지 ,거짓 : 회색이미지
			// i 가 플레이어가 정확하게 입력한 문자 수보다 작은지 안 작은지
	for (int i = 0; i < p1_random_letters.size(); i++)
	{
		string pos = "pos1_" + to_string(i + 1);
		Find(pos)->texture = RESOURCE->textures.Load
		((i < input_count) ? textureMap[p1_random_letters[i]].second :
			textureMap[p1_random_letters[i]].first);
	}
}

void Game_ui::set_im_ui2()
{
	// 키가 숫자, 값은 1. 회색이미지, 2. 그린이미지
	map<char, pair<string, string>> textureMap =
	{
		{'4', {"4_code.png","4n_code.png"}},
		{'5', {"5_code.png","5n_code.png"}},
		{'6', {"6_code.png","6n_code.png"}},
		{'7', {"7_code.png","7n_code.png"}},
		{'8', {"8_code.png","8n_code.png"}},
		{'9', {"9_code.png","9n_code.png"}}
	};

	// p2_random_letters의 이미지 설정
		// p2_random_letters 문자를 순회함
			// i < input_count2는 판단기준
			// 참 : 녹색이미지 ,거짓 : 회색이미지
			// i 가 플레이어가 정확하게 입력한 문자 수보다 작은지 안 작은지
	for (int i = 0; i < p2_random_letters.size(); i++)
	{
		string pos = "pos2_" + to_string(i + 1);
		Find(pos)->texture = RESOURCE->textures.Load
		((i < input_count2) ? textureMap[p2_random_letters[i]].second :
			textureMap[p2_random_letters[i]].first);
	}
}

void Game_ui::p1_element_update()
{
	if (event_limit_time > 0)
	{
		set_im_ui();

		char currentInput;
		if (INPUT->KeyDown('Q'))
		{
			currentInput = 'q';
		}
		else if (INPUT->KeyDown('W'))
		{
			currentInput = 'w';
		}
		else if (INPUT->KeyDown('E'))
		{
			currentInput = 'e';
		}
		else if (INPUT->KeyDown('A'))
		{
			currentInput = 'a';
		}
		else if (INPUT->KeyDown('S'))
		{
			currentInput = 's';
		}
		else if (INPUT->KeyDown('D'))
		{
			currentInput = 'd';
		}
		else
		{
			currentInput = '\0';
		}


		// player 입력 확인 매크로들
		if (currentInput != '\0' && currentInput == p1_random_letters[input_count])
		{
			// 한 입력이 정확할 경우 원하는 동작 수행 가능
				// 1. 다음 문자 확인
			cout << "맞음" << endl;
			input_count++;
			set_im_ui();
		}
		else if (currentInput != '\0')
		{
			// 한 입력이 틀릴 경우
				// 1. 처음으로 되돌림  (0)
			cout << "틀림" << endl;
			input_count = 0;
			set_im_ui();
		}
		if (input_count == p1_random_letters.size())
		{
			// 모든 입력이 맞을 경우
				// 1. 시퀸스 재설정 
				// 2. 부스터 모션 나오가 하는 불 값 둘수 있음
			player1_bust = true;

		}
	}
	else if (event_limit_time <= 0)
	{
		visible_gameui(false);
		p1_random_letters = make_random_p1(p1_letters, 6);
		input_count = 0;

		// 빠지는 모션 < 패널티>
		player1_drown = true;

	}
}

void Game_ui::p2_element_update()
{
	if (event_limit_time > 0)
	{
		set_im_ui2();

		char currentInput2;
		if (INPUT->KeyDown(100))
		{
			currentInput2 = '4';
		}
		else if (INPUT->KeyDown(101))
		{
			currentInput2 = '5';
		}
		else if (INPUT->KeyDown(102))
		{
			currentInput2 = '6';
		}
		else if (INPUT->KeyDown(103))
		{
			currentInput2 = '7';
		}
		else if (INPUT->KeyDown(104))
		{
			currentInput2 = '8';
		}
		else if (INPUT->KeyDown(105))
		{
			currentInput2 = '9';
		}
		else
		{
			currentInput2 = '\0';
		}


		// player 입력 확인 매크로들
		if (currentInput2 != '\0' && currentInput2 == p2_random_letters[input_count2])
		{
			// 한 입력이 정확할 경우 원하는 동작 수행 가능
				// 1. 다음 문자 확인
			cout << "맞음" << endl;
			input_count2++;
			set_im_ui2();
		}
		else if (currentInput2 != '\0')
		{
			// 한 입력이 틀릴 경우
				// 1. 처음으로 되돌림  (0)
				// 2. 헤엄치지 못하는 모션 나오게 하는 불값 둘수 있음

			cout << "틀림" << endl;
			input_count2 = 0;
			set_im_ui2();
		}
		if (input_count2 == p2_random_letters.size())
		{
			// 모든 입력이 맞을 경우
				// 1. 시퀸스 재설정
				// 2. 부스터 모션 나오가 하는 불 값 둘수 있음
			player2_bust = true;
		}
	}
	else if (event_limit_time <= 0)
	{
		visible_gameui(false);
		p2_random_letters = make_random_p2(p2_letters, 6);
		input_count2 = 0;

		// 빠지는 모션 < 패널티>
		player2_drown = true;

	}
}

bool Game_ui::give_bust(bool _canbost)
{
	if (_canbost == true)
	{
		return true;
	}
	else if (_canbost == false)
	{
		return false;
	}
}

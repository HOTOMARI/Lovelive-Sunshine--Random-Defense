#pragma once
#include "resource.h"

struct Tower {
	int x;
	int y;
	int kind;
	int rank;
	int group;
	int atk;
	int range;
	int target;
	int speed_atk;
	int atk_tmr;
	int bulspeed;
	int bulframe;
	int skillcool;
	bool ur_skillchk;
};

struct Tile {
	float x;
	float y;
	int kind;
	bool install;
	Tower tower;
};

struct Timer {
	int frame_tmr, mv_tmr, die_tmr;
	int breaktime;
	int mari_tmr;
	int settimer;
	int mission[3] = { 15000, 15000, 15000 };
};

struct Mod {
	int install;
	int combine;
	int sell;
	int view_info;
	int breaktime;
	int boss;
	int skill;

	bool gamemode = false;
	bool mainmenu = true;
	bool gameover = false;
	bool howto = false;
	bool endgame = false;

	bool pause = false;

	bool achive = false;
};

struct Mouse {
	int x, y;
	int sel_x, sel_y;
	int save_x, save_y;
};

struct Boss {
	bool boss;
	int act;
	bool skill;
	float skillcool;
	int skilltaget;
	int skillmax;
};

struct Monster {
	float x, y;
	float hp;
	float maxhp;
	float speed;
	int mv_way;
	int frame;
	int kind;
	int distance;
	int death;
	bool mission;
	Boss boss;
};


struct Bullet {
	float x, y;
	float mx, my;
	float speed;
	float target_x, target_y;
	int frame;
	int kind;
	int target;
	int atk;
	int rank;
	int maxframe;
	float t_maxf;
	float t_setf;
	bool target_lose;
	bool hit;
	bool ur;
};

struct Effect {
	float x, y;
	int frame;
	float maxframe;
	int kind;
	int rank;
	int target;
	bool ur;
	int atk;
	float setframe;
};

struct Info {
	float tile_W;		// Ÿ�� ����
	float tile_H;		// Ÿ�� ����
	float tower_W;		// Ÿ�� ����(�Ѱ� ����)
	float tower_H;		// Ÿ�� ����(�Ѱ� ����)
	float monster_W;	// ���� ����(�Ѱ� ����)
	float monster_H;	// ���� ����(�Ѱ� ����)
	float object_W;		// �Ѿ� ����(�Ѱ� ����)
	float object_H;		// �Ѿ� ����(�Ѱ� ����)
	float effect_W;		// ����Ʈ ����
	float effect_H;		// ����Ʈ ����
	float upgrade[3] = { 1.0, 1.0, 1.0 };
	float dia_upgrade = 1.0;
	int monster_num;	// ���� ����
	int bullet_num;		// �Ѿ� ������Ʈ ����
	int effect_num;		// ����Ʈ ����
	int combi_tower;	// Ÿ�� ���� �Լ�
	int nextrank;		// ���� Ÿ���� ��ũ
	int nextmonspd;		// ���� ������ ���ǵ�
	int now_wave;		// ���� ���̺�
	int remain_life;	// ���� ����
	int money;			// ��
	int count_mon;		// ���� �̹����̺꿡 ��� ���Ӵ���
	int boss_kind;		// ���� ����
	int kill_count;		// ų ī��Ʈ
	bool gameover = false;
	bool gameclear = false;
	int gameover_alpha;
	int gameclear_alpha;
	int upgrade_stack[3];
	bool bossskill = false;
	int howto_page = 0;
};

struct Button {
	float x, y;
	float width, height;
	bool on_mouse;
};

struct Font {
	float x, y;
	float width, height;
};

struct Skill {
	float x, y;
	float draw_x, draw_y;
	float range_x, range_y;
	float delta_x, delta_y;
	int tile_x = -1, tile_y = -1;
	int type = 0;
	int degree = 0;
	int alpha = 0;
	int cutin_timer = 0;
	int skill_timer = 0;
	int kanan_timer = -32;
	bool activate = false;
	bool play_cutin = false;
	bool alpha_up = true;
	bool mari_upgrade;
};

struct Achieve {
	// ���� ����
	/*
	0 r
	1 sr
	2 ssr
	3 ur
	4 kill100
	5 kill500
	6 Fsentermari
	7 S_upgrade
	8 C_upgrade
	9 P_upgrade
	10 hidden
	11 heap�ջ�
	*/

	bool Achive_List[12] = { false,false, false, false, false, false, false, false, false, false, false, false };
	bool popup_mod = false;

	int achieve_alpha = 0;
	int achieve_counter = 0;
	int now_view;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow);	// ������ �⺻ ���� �Լ�
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);						// ������ �⺻ ���� �Լ�


void add(int* monster_num, Monster** monster);
void del(int* monster_num, Monster** monster);
void add(int* bullet_num, Bullet** bullet);
void del(int* bullet_num, Bullet** bullet);
void add(int* effect_num, Effect** effect);
void del(int* effect_num, Effect** effect);
void truecimage(CImage *cimage);
void subskill(Tower* tower, Monster** monster, int* monster_num, Bullet** bullet, int* bullet_num, Effect** effect, int* effect_num, Info* info);
void seteffect(int x, int y, int frame, int effect_num, Effect** effect);
void bossmod(Monster** boss, Tile* map, Effect** effect, int* effect_num, Skill* skill);
void achievement(Tile* map, Info* info, Achieve* achieve);
bool rectcrash(RECT a, RECT b);
bool inrange(int range, float tower_x, float tower_y, float monster_x, float monster_y);
bool mouse_in_box(int mx, int my, Button);
double get_radian(double degree);
float LengthPts(float x1, float y1, float x2, float y2);
void bullet_damage(Bullet* bullet, Monster* monster);		// �����ϰ� �Ѿ��ϰ� �浹������ �Ѿ˻��� & ������
void skill_damage(Skill skill, Monster* monster, int wave);			// ��ų ������ ����
void towercombine(Tower* tower);	// Ÿ�� ��ġ��
void towerset(Tower* tower);			// Ÿ�� ���� ����
bool upgrade(float* upgrade, int* money);
bool play_lotto(int num);

static HINSTANCE g_hInst;
static LPCTSTR lpszClass = "Window Class Name";

const int width = 768+16; // 16�� �� ��ǻ�� �������� â �ٟm���� GetClientRect ���� rt.right�� ������ ��
const int high = 1000+39; // 39�� �� ��ǻ�� �������� â �ٟm���� GetClientRect ���� rt.bottom�� ������ ��

static Tile tile;
static Tile map[12][12];
static Tile* map_addr;
static Tile combi[2];
static Monster* monster = (Monster*)malloc(sizeof(Monster));
static Mod mod;
static Mouse mouse;
static Bullet* bullet = (Bullet*)malloc(sizeof(Bullet));
static Effect* effect = (Effect*)malloc(sizeof(Effect));
static Info info;
static Timer timer;
static Button main_buttons[4];
static Button buttons[4];
static Font number[10], word;
static HWND mother, child;
static Skill skill;
static Skill only_kanan[10];
static Achieve achieve, achieve_ani;
static int tmp_x;
static int tmp_y;
static FMOD_SYSTEM* soundSystem;
static FMOD_SOUND *BGM, *Menu_sound, *Hit_sound, *Effect_sound, *Touch_voice, *Skill_sound, *Boss_sound, *Boom_sound;
static FMOD_CHANNEL *BGM_c, *Menu_sound_c, *Hit_sound_c, *Effect_sound_c, *Touch_voice_c, *Skill_sound_c, *Boss_sound_c, *Boom_sound_c;
static unsigned int *sound_length;
static unsigned int bgm_length;
static double start, end;
static int mission_status = 0;

// ä�� ���
// ���� ����  bgm , �״¼Ҹ�
//				�޴�Ŭ��
//				ĳ���� �������� ���̽�
//				��ų�Ҹ�
//				��ų������ �� á����
//				�Ѿ� �ǰݼҸ�
//				���� �״¼Ҹ�
//				�����Ҹ�
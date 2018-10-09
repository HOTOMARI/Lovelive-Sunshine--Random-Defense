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
	float tile_W;		// 타일 넓이
	float tile_H;		// 타일 높이
	float tower_W;		// 타워 넓이(한개 넓이)
	float tower_H;		// 타워 높이(한개 높이)
	float monster_W;	// 몬스터 넓이(한개 넓이)
	float monster_H;	// 몬스터 높이(한개 높이)
	float object_W;		// 총알 넓이(한개 넓이)
	float object_H;		// 총알 높이(한개 높이)
	float effect_W;		// 이펙트 높이
	float effect_H;		// 이펙트 넓이
	float upgrade[3] = { 1.0, 1.0, 1.0 };
	float dia_upgrade = 1.0;
	int monster_num;	// 몬스터 숫자
	int bullet_num;		// 총알 오브젝트 숫자
	int effect_num;		// 이펙트 숫자
	int combi_tower;	// 타워 저장 함수
	int nextrank;		// 다음 타워의 랭크
	int nextmonspd;		// 다음 몬스터의 스피드
	int now_wave;		// 현재 웨이브
	int remain_life;	// 남은 생명
	int money;			// 돈
	int count_mon;		// 몬스터 이번웨이브에 몇마리 나왓는지
	int boss_kind;		// 보스 종류
	int kill_count;		// 킬 카운트
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
	// 업적 순서
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
	11 heap손상
	*/

	bool Achive_List[12] = { false,false, false, false, false, false, false, false, false, false, false, false };
	bool popup_mod = false;

	int achieve_alpha = 0;
	int achieve_counter = 0;
	int now_view;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow);	// 윈도우 기본 생성 함수
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);						// 윈도우 기본 생성 함수


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
void bullet_damage(Bullet* bullet, Monster* monster);		// 몬스터하고 총알하고 충돌했을때 총알삭제 & 데미지
void skill_damage(Skill skill, Monster* monster, int wave);			// 스킬 데미지 판정
void towercombine(Tower* tower);	// 타워 합치기
void towerset(Tower* tower);			// 타워 정보 셋팅
bool upgrade(float* upgrade, int* money);
bool play_lotto(int num);

static HINSTANCE g_hInst;
static LPCTSTR lpszClass = "Window Class Name";

const int width = 768+16; // 16은 내 컴퓨터 기준으로 창 뛰웟을때 GetClientRect 한후 rt.right에 빼지는 값
const int high = 1000+39; // 39은 내 컴퓨터 기준으로 창 뛰웟을때 GetClientRect 한후 rt.bottom에 빼지는 값

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

// 채널 배분
// 사운드 파일  bgm , 죽는소리
//				메뉴클릭
//				캐릭터 눌렀을떄 보이스
//				스킬소리
//				스킬게이지 꽉 찼을때
//				총알 피격소리
//				몬스터 죽는소리
//				보스소리
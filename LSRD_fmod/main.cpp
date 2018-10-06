#include "stdafx.h"
#include "함수 헤더.h"

#pragma comment(lib, "msimg32.lib")
//------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------//
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow) {

	HWND hWnd;
	MSG Message;
	WNDCLASSEX WndClass;
	g_hInst = hInstance;

	// 윈도우 클래스 구조체 값 설정
	WndClass.cbSize = sizeof(WndClass);
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = (WNDPROC)WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = lpszClass;
	WndClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON2));

	// 윈도우 클래스 등록
	RegisterClassEx(&WndClass);

	//차일드 윈도우 클래스 등록
	//WndClass.hCursor = LoadCursor(NULL, IDC_HELP);
	//WndClass.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	//WndClass.lpszClassName = "ChildClass1";
	//WndClass.lpfnWndProc = ChildProc_1;
	//RegisterClassEx(&WndClass);

	// 윈도우 생성
	hWnd = CreateWindow(lpszClass, "Lovelive! Sunshine! Random Defense", WS_OVERLAPPEDWINDOW, 0, 0, width, 807, NULL, (HMENU)NULL, hInstance, NULL);

	// 윈도우 출력
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	// 이벤트 루프처리
	while (1) {
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE)) {
			if (Message.message == WM_QUIT) break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);

		}
		else {

		}
	}
	return ((int)Message.wParam);
}
//------------------------------------------------------------------------------------------------------------------------------------------------//
//------------------------------------------------------------------------------------------------------------------------------------------------//

LRESULT CALLBACK WndProc(HWND hWnd, UINT IMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, memdc;
	static HDC mem1dc,mem2dc;
	static HBITMAP hBit,hBit2, oldBit1, oldBit2;
	static CImage Grass1, Sand1, Tower, Monster, Effect[5], Area, Bullet, Map[3], Boss, Skill, Cutin[9], Atkeffect[3][9], System[4], Subskill[9], HowtoP[9], Achievement,Mission, Menu, Card;
	PAINTSTRUCT ps;
	BITMAP bmp;

	static RECT rt;
	HPEN hPen, oldPen;
	HBRUSH hBrush, oldBrush;

	static float window_W, window_H;	// 창의 크기를 double로 저장
	int i, j, k, l, m;						// for문 돌릴때
	static int mx, my;							// 마우스변수
	static int shotdown;
	static int tanostimer = 0;
	int distance;
	float rad;
	static int upgrade_status, upgrade_kind;
	static char upgrade_message[25];

	RECT bul, mob;

	switch (IMsg) {
	case WM_CREATE:
		mother = hWnd;
		hdc = GetDC(hWnd);
		memdc = CreateCompatibleDC(hdc);
		SetTimer(hWnd, 1, 15, NULL);
		//// 타이머 배속
		/*SetTimer(hWnd, 2, 10, NULL);
		SetTimer(hWnd, 3, 10, NULL);
		SetTimer(hWnd, 4, 10, NULL);
		SetTimer(hWnd, 5, 10, NULL);
		SetTimer(hWnd, 6, 10, NULL);
		SetTimer(hWnd, 7, 10, NULL);*/
		srand(time(NULL));
		GetClientRect(hWnd, &rt);
		// fmod 생성
		FMOD_System_Create(&soundSystem);
		// fmod 초기화
		FMOD_System_Init(soundSystem, 10, FMOD_INIT_NORMAL, NULL);
		// 메뉴 클릭 소리 추가
		FMOD_System_CreateSound(soundSystem, "resource/sound/system/menu_sel.mp3", FMOD_DEFAULT, 0, &Menu_sound);
		// 메뉴 bgm
		FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/main.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
		FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
		// 소리길이받기
		sound_length = &bgm_length;
		//차일드 윈도우 생성
		//child = CreateWindow("ChildClass1", NULL, WS_CHILD | WS_VISIBLE,
		//	0, 768, 768, 231, hWnd, NULL, g_hInst, NULL);

		// 창의 크기를 double로 저장
		window_W = rt.right;
		window_H = rt.bottom;

		// bmp 정의 및 크기 저장
		info.tile_W = (double)64;
		info.tile_H = (double)64;

		Tower.Load(".\\resource\\aqoura\\tower.png");
		truecimage(&Tower);
		SelectObject(memdc, Tower);
		GetObject(Tower, sizeof(BITMAP), &bmp);
		info.tower_W = (double)bmp.bmWidth / 9;
		info.tower_H = (double)bmp.bmHeight / 5;

		Monster.Load(".\\resource\\aqoura\\monster.png");
		truecimage(&Monster);
		SelectObject(memdc, Monster);
		GetObject(Monster, sizeof(BITMAP), &bmp);
		info.monster_W = (double)bmp.bmWidth / 4;
		info.monster_H = (double)bmp.bmHeight / 12;

		Mission.Load(".\\resource\\aqoura\\mission.png");
		truecimage(&Mission);

		Boss.Load(".\\resource\\aqoura\\boss.png");
		truecimage(&Boss);

		Bullet.Load(".\\resource\\aqoura\\bullet.png");
		truecimage(&Bullet);

		SelectObject(memdc, Bullet);
		GetObject(Bullet, sizeof(BITMAP), &bmp);
		info.object_W = (double)bmp.bmWidth / 9;
		info.object_H = (double)bmp.bmHeight / 28;

		Effect[0].Load("resource/effect/effect.png");
		Effect[1].Load("resource/effect/tanos_effect.png");
		Effect[2].Load("resource/effect/ele_effect.png");
		Effect[3].Load("resource/effect/white.png");
		Effect[4].Load("resource/effect/Water3.png");

		for (i = 0; i < 5; ++i) {
			truecimage(&Effect[i]);
		}

		Map[0].Load(".\\resource\\map\\Map002.png");
		Map[1].Load(".\\resource\\map\\Map003.png");
		Map[2].Load(".\\resource\\map\\Map004.png");
		
		Skill.Load("resource/effect/skill.png");
		truecimage(&Skill);

		Cutin[0].Load("resource/effect/chika_skill.png");
		Cutin[1].Load("resource/effect/hanamaru_skill.png");
		Cutin[2].Load("resource/effect/mari_skill.png");
		Cutin[3].Load("resource/effect/riko_skill.png");
		Cutin[4].Load("resource/effect/yoshiko_skill.png");
		Cutin[5].Load("resource/effect/dia_skill.png");
		Cutin[6].Load("resource/effect/you_skill.png");
		Cutin[7].Load("resource/effect/ruby_skill.png");
		Cutin[8].Load("resource/effect/kanan_skill.png");

		Atkeffect[0][0].Load("resource/effect/chika_sr.png");
		Atkeffect[0][1].Load("resource/effect/hanamaru_sr.png");
		Atkeffect[0][2].Load("resource/effect/mari_sr.png");
		Atkeffect[0][3].Load("resource/effect/riko_sr.png");
		Atkeffect[0][4].Load("resource/effect/yoshiko_sr.png");
		Atkeffect[0][5].Load("resource/effect/dia_sr.png");
		Atkeffect[0][6].Load("resource/effect/you_sr.png");
		Atkeffect[0][7].Load("resource/effect/ruby_sr.png");
		Atkeffect[0][8].Load("resource/effect/kanan_sr.png");

		Atkeffect[1][0].Load("resource/effect/chika_ssr.png");
		Atkeffect[1][1].Load("resource/effect/hanamaru_ssr.png");
		Atkeffect[1][2].Load("resource/effect/mari_ssr.png");
		Atkeffect[1][3].Load("resource/effect/riko_ssr.png");
		Atkeffect[1][4].Load("resource/effect/yoshiko_ssr.png");
		Atkeffect[1][5].Load("resource/effect/dia_ssr.png");
		Atkeffect[1][6].Load("resource/effect/you_ssr.png");
		Atkeffect[1][7].Load("resource/effect/ruby_ssr.png");
		Atkeffect[1][8].Load("resource/effect/kanan_ssr.png");

		Atkeffect[2][0].Load("resource/effect/chika_ur.png");
		Atkeffect[2][1].Load("resource/effect/hanamaru_ur.png");
		Atkeffect[2][2].Load("resource/effect/mari_ur.png");
		Atkeffect[2][3].Load("resource/effect/riko_ur.png");
		Atkeffect[2][4].Load("resource/effect/yoshiko_ur.png");
		Atkeffect[2][5].Load("resource/effect/dia_ur.png");
		Atkeffect[2][6].Load("resource/effect/you_ur.png");
		Atkeffect[2][7].Load("resource/effect/ruby_ur.png");
		Atkeffect[2][8].Load("resource/effect/kanan_ur.png");

		for (i = 0; i < 3; ++i) {
			for (j = 0; j < 9; ++j) {
				truecimage(&Atkeffect[i][j]);
			}
		}

		Area.Load("resource/effect/area.png");
		truecimage(&Area);
		System[0].Load("resource/system/main_background.png");
		System[1].Load("resource/system/main.png");
		System[2].Load("resource/system/gameover.png");

		for (i = 0; i < 3; ++i) {
				truecimage(&System[i]);
		}

		Subskill[0].Load("resource/effect/chika_ur.png");
		Subskill[1].Load("resource/effect/spark_02.png");
		Subskill[2].Load("resource/effect/mari_subskill.png");
		Subskill[3].Load("resource/effect/riko_subskill.png");
		Subskill[4].Load("resource/effect/yoshiko_subskill.png");
		Subskill[5].Load("resource/effect/dia_subskill.png");
		Subskill[6].Load("resource/effect/you_subskill.png");
		Subskill[7].Load("resource/effect/ruby_subskill.png");
		Subskill[8].Load("resource/effect/kanan_subskill.png");

		for (i = 0; i < 9; ++i) {
			truecimage(&Subskill[i]);
		}

		// 도움말
		HowtoP[0].Load("resource/help/help_1.jpg");
		HowtoP[1].Load("resource/help/help_2.jpg");
		HowtoP[2].Load("resource/help/help_3.jpg");
		HowtoP[3].Load("resource/help/help_4.jpg");
		HowtoP[4].Load("resource/help/help_5.jpg");
		HowtoP[5].Load("resource/help/help_6.jpg");
		HowtoP[6].Load("resource/help/help_7.jpg");
		HowtoP[7].Load("resource/help/help_8.jpg");
		HowtoP[8].Load("resource/help/help_9.jpg");

		// 도전과제
		Achievement.Load("resource/system/achievement.png");
		truecimage(&Achievement);

		// 메인메뉴 버튼 좌표 지정
		main_buttons[0].x = 280, main_buttons[0].y = 400;
		main_buttons[0].width = 206, main_buttons[0].height = 54;
		main_buttons[1].x = 170, main_buttons[1].y = 500;
		main_buttons[1].width = 427, main_buttons[1].height = 54;
		main_buttons[2].x = 320, main_buttons[2].y = 600;
		main_buttons[2].width = 133, main_buttons[2].height = 52;
		// 게임오버 버튼 좌표 지정
		main_buttons[3].x = 293, main_buttons[3].y = 400;
		main_buttons[3].width = 182, main_buttons[3].height = 26;

		// 비트맵 로드
		Menu.Load(".\\resource\\aqoura\\menu.png");
		truecimage(&Menu);
		Card.Load(".\\resource\\aqoura\\card.png");
		// 숫자
		for (int i = 0; i < 10; ++i) {
			number[i].x = 183 + 32 * i;
			number[i].y = 77;
			number[i].height = number[i].width = 32;
		}
		// 버튼 위치 설정
		for (int i = 0; i < 3; ++i) {
			buttons[i].x = 0, buttons[i].y = i * 77+768;
			buttons[i].width = 152, buttons[i].height = 77;
		}
		Button tmp = buttons[1];
		buttons[1] = buttons[2];
		buttons[2] = tmp;
		buttons[3].x = 580, buttons[3].y = 30+768;
		buttons[3].width = 176, buttons[3].height = 176;

		// 소멸자
		DeleteDC(memdc);
		ReleaseDC(hWnd, hdc);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// 더블버퍼링
		if (hBit == NULL) {
			hBit = CreateCompatibleBitmap(hdc, width, high);
		}

		mem1dc = CreateCompatibleDC(hdc);

		oldBit1 = (HBITMAP)SelectObject(mem1dc, hBit);


		// 게임화면
		if (mod.gamemode) {
			if (skill.activate&&skill.type == 2) {
				Map[2].Draw(mem1dc, 0, 0, 768, 768);
			}
			else if (skill.activate&&skill.type == 6) {
				Map[1].Draw(mem1dc, 0, 0, 768, 768);
			}
			else {
				Map[0].Draw(mem1dc, 0, 0, 768, 768);
			}

			// 타워 보이게하기
			for (i = 0; i < 12; ++i) {
				for (j = 0; j < 12; ++j) {
					if (map[i][j].install) {
						Tower.Draw(mem1dc, map[i][j].x, map[i][j].y, info.tile_W, info.tile_H,
							info.tower_W * map[i][j].tower.kind, info.tower_H * map[i][j].tower.rank, info.tower_W, info.tower_H);
					}
				}
			}

			// 치카 서브 스킬
			for (i = 0; i < 12; ++i) {
				for (j = 0; j < 12; ++j) {
					if (map[i][j].tower.ur_skillchk) {
						switch (map[i][j].tower.kind) {
						case 0:
							if (map[i][j].tower.target < info.monster_num && map[i][j].tower.target != -1 && map[i][j].tower.skillcool > 700) {
								hPen = CreatePen(PS_SOLID, 3, RGB(255, 0, 0));
								oldPen = (HPEN)SelectObject(mem1dc, hPen);
								MoveToEx(mem1dc, map[i][j].x + 32, map[i][j].y + 32, NULL);
								LineTo(mem1dc, monster[map[i][j].tower.target].x + 32, monster[map[i][j].tower.target].y + 32);
								Subskill[map[i][j].tower.kind].Draw(mem1dc, monster[map[i][j].tower.target].x, monster[map[i][j].tower.target].y, 64, 64, 0, 0, 128, 128);
								SelectObject(mem1dc, oldPen);
								DeleteObject(hPen);
							}
							break;
						}
					}
				}
			}

			// 몬스터 보이게하기
			// (HBITMAP)SelectObject(mem2dc, Monster);
			if (mod.boss == 0) {
				for (i = 0; i < info.monster_num; ++i) {
					if (monster[i].mission == false) {
						hBrush = CreateSolidBrush(RGB(0, 255, 0));
						oldBrush = (HBRUSH)SelectObject(mem1dc, hBrush);
						SelectObject(mem1dc, GetStockObject(NULL_PEN));
						Rectangle(mem1dc, monster[i].x + 10, monster[i].y - 10, monster[i].x + 10 + ((monster[i].hp / monster[i].maxhp) * ((float)44)), monster[i].y);
						SelectObject(mem1dc, GetStockObject(BLACK_PEN));
						SelectObject(mem1dc, oldBrush);
						DeleteObject(hBrush);
						SelectObject(mem1dc, GetStockObject(NULL_BRUSH));
						Rectangle(mem1dc, monster[i].x + 10, monster[i].y - 10, monster[i].x + 54, monster[i].y);
						SelectObject(mem1dc, GetStockObject(WHITE_BRUSH));
						Monster.Draw(mem1dc, monster[i].x, monster[i].y, info.tile_W, info.tile_H,
							info.monster_W * monster[i].frame, info.monster_H * monster[i].kind, info.monster_W, info.monster_H);
					}
					else {
						hBrush = CreateSolidBrush(RGB(0, 0, 255));
						oldBrush = (HBRUSH)SelectObject(mem1dc, hBrush);
						SelectObject(mem1dc, GetStockObject(NULL_PEN));
						Rectangle(mem1dc, monster[i].x + 10, monster[i].y - 10, monster[i].x + 10 + ((monster[i].hp / monster[i].maxhp) * ((float)44)), monster[i].y);
						SelectObject(mem1dc, GetStockObject(BLACK_PEN));
						SelectObject(mem1dc, oldBrush);
						DeleteObject(hBrush);
						SelectObject(mem1dc, GetStockObject(NULL_BRUSH));
						Rectangle(mem1dc, monster[i].x + 10, monster[i].y - 10, monster[i].x + 54, monster[i].y);
						SelectObject(mem1dc, GetStockObject(WHITE_BRUSH));
						Mission.Draw(mem1dc, monster[i].x, monster[i].y, info.tile_W, info.tile_H,
							info.monster_W * monster[i].frame, info.monster_H * (monster[i].mv_way + monster[i].kind * 4), info.monster_W, info.monster_H);
					}
				}
			}
			
			// 보스 모드
			if (mod.boss == 1) {
				for (i = 0; i < info.monster_num; ++i) {		
					if (monster[i].kind == 4 && (monster[i].boss.skillcool > 300 && monster[i].boss.skill == false)) {
						RECT a = { monster[i].x, monster[i].y - 128, monster[i].x + 64, monster[i].y + 196 };
						RECT b = { monster[i].x - 64, monster[i].y - 64, monster[i].x + 128, monster[i].y + 128 };
						RECT c = { monster[i].x - 128, monster[i].y, monster[i].x + 196, monster[i].y + 64 };
						Area.AlphaBlend(mem1dc, a.left, a.top, 64, 196 + 128, 0, 0, 800, 800, 128);
						Area.AlphaBlend(mem1dc, b.left, b.top, 128 + 64, 128 + 64, 0, 0, 800, 800, 128);
						Area.AlphaBlend(mem1dc, c.left, c.top, 196 + 128, 64, 0, 0, 800, 800, 128);
					}
					if (monster[i].kind == 2 && (monster[i].boss.skillcool > 300 && monster[i].boss.skill == false)) {
						Area.AlphaBlend(mem1dc, monster[i].x, 0, 64, 768, 0, 0, 800, 800, 128);
						Area.AlphaBlend(mem1dc, 0, monster[i].y, 768, 64, 0, 0, 800, 800, 128);
					}
					
					hBrush = CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(mem1dc, hBrush);
					SelectObject(mem1dc, GetStockObject(NULL_PEN));
					// HP METER
					Rectangle(mem1dc, monster[i].x - 10, monster[i].y - 15, monster[i].x - 10 + ((monster[i].hp / monster[i].maxhp) * ((float)84)), monster[i].y);
					SelectObject(mem1dc, oldBrush);
					DeleteObject(hBrush);

					// SKILL METER		
					hBrush = CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = (HBRUSH)SelectObject(mem1dc, hBrush);
					if (monster[i].boss.skill == false) {
						Rectangle(mem1dc, monster[i].x - 10, monster[i].y - 25, monster[i].x - 10 + ((float)((float)monster[i].boss.skillcool / (float)monster[i].boss.skillmax) * ((float)84)), monster[i].y - 15);
					}
					if (monster[i].boss.skill == true) {
						Rectangle(mem1dc, monster[i].x - 10, monster[i].y - 25, monster[i].x - 10 + ((0 / monster[i].boss.skillmax) * ((float)84)), monster[i].y - 15);
					}
					SelectObject(mem1dc, oldBrush);
					DeleteObject(hBrush);

					// METER BOX
					SelectObject(mem1dc, GetStockObject(BLACK_PEN)); 
					SelectObject(mem1dc, GetStockObject(NULL_BRUSH));
					Rectangle(mem1dc, monster[i].x - 10, monster[i].y - 25, monster[i].x - 10 + (float)84, monster[i].y - 15);
					Rectangle(mem1dc, monster[i].x - 10, monster[i].y - 15, monster[i].x - 10 + 84, monster[i].y);
					SelectObject(mem1dc, GetStockObject(WHITE_BRUSH));
					
					// BOSS DRAW
					Boss.Draw(mem1dc, monster[i].x, monster[i].y, info.tile_W, info.tile_H,
						info.monster_W * monster[i].frame, info.monster_H * ((monster[i].kind - 1) * 6) + info.monster_H * monster[i].boss.act, info.monster_W, info.monster_H);
				}
			}

			// 총알 보이게 하기
			for (i = 0; i < info.bullet_num; ++i) {
				if (bullet[i].rank == 0) {
					Bullet.Draw(mem1dc, bullet[i].x, bullet[i].y, info.object_W, info.object_H,
						info.object_W * bullet[i].kind, 0, info.object_W, info.object_W);
				}
				if (bullet[i].rank == 1) {
					Bullet.Draw(mem1dc, bullet[i].x, bullet[i].y, info.object_W, info.object_H,
						info.object_W * (int)(bullet[i].frame / 3), info.object_H + (info.object_H * bullet[i].kind), info.object_W, info.object_W);
				}
				if (bullet[i].rank >= 2) {
					if (bullet[i].ur == false) {
						Bullet.Draw(mem1dc, bullet[i].x, bullet[i].y, info.object_W, info.object_H,
							info.object_W * (int)(bullet[i].frame / 3), info.object_H + info.object_H * (9 * (bullet[i].rank - 1)) + (info.object_H * bullet[i].kind), info.object_W, info.object_W);
					}
					if (bullet[i].ur) {		// 추가
						switch (bullet[i].kind) {
						case 0:
							Subskill[0].Draw(mem1dc, bullet[i].x, bullet[i].y, 64, 64,
								128 * 2, 0, 128, 128);
							break;
						}
					}
				}
			}

			// 이펙트 보이기
			for (i = 0; i < info.effect_num; ++i) {
				if (effect[i].rank == -1) {		// 총알 쿨타임
					Effect[0].Draw(mem1dc, effect[i].x, effect[i].y, info.tile_W, info.tile_H,
						128 * (int)(effect[i].frame / effect[i].setframe), 128 * 5, 128, 128);
				}
				else if (effect[i].rank == -2) {	// 죽는거
					Effect[0].Draw(mem1dc, effect[i].x, effect[i].y, info.tile_W, info.tile_H,
						128 * (int)(effect[i].frame / effect[i].setframe), 128 * 4, 128, 128);
				}
				else if (effect[i].rank == -3) {
					if (effect[i].frame >= 0) {
						if (effect[i].kind != 3) {
							Effect[effect[i].kind].Draw(mem1dc, effect[i].x, effect[i].y, info.tile_W, info.tile_H,
								64 * ((int)(effect[i].frame / effect[i].setframe) % 5), 64 * ((int)(effect[i].frame / effect[i].setframe) / 5), 64, 64);
						}
					}
				}
				if (effect[i].rank == 0) {
					Effect[0].Draw(mem1dc, effect[i].x, effect[i].y, info.tile_W, info.tile_H,
						128 * (int)(effect[i].frame / effect[i].setframe), 128 * 0, 128, 128);
				}
				else if (effect[i].rank > 0 && effect[i].ur == false) {
					Atkeffect[effect[i].rank - 1][effect[i].kind].Draw(mem1dc, effect[i].x, effect[i].y, info.tile_W, info.tile_H,
						128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
				}
				if (effect[i].ur == true) {		// 추가
					switch (effect[i].kind) {
					case 1:		// 하나마루 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 175, effect[i].y - 175, 350, 350,
							256 * ((int)(effect[i].frame / effect[i].setframe) % 5), 256 * ((int)(effect[i].frame / effect[i].setframe) / 5), 256, 256);
						if (effect[i].frame % 11 == 10) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 175 < monster[j].x + 32 && effect[i].y - 175 < monster[j].y + 32
									&& effect[i].x + 175 > monster[j].x - 32 && effect[i].y + 175 > monster[j].y - 32) {
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					case 2:		// 마리 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x, effect[i].y, 64, 64,
							64 * ((int)(effect[i].frame / effect[i].setframe)), 0, 64, 64);
						break;
					case 3:		// 리코 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						if (effect[i].frame == 80) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 64 < monster[j].x + 32 && effect[i].y - 64 < monster[j].y + 32
									&& effect[i].x + 64 > monster[j].x - 32 && effect[i].y + 64 > monster[j].y - 32) {
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					case 4:		// 요시코 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						if (effect[i].frame > 36) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 64 < monster[j].x + 32 && effect[i].y - 64 < monster[j].y + 32
									&& effect[i].x + 64 > monster[j].x - 32 && effect[i].y + 64 > monster[j].y - 32) {
									if ((monster[j].mv_way == 0 || monster[j].mv_way == 2) && monster[j].x + 32 > effect[i].x) {
										monster[j].x -= 3;
									}
									else if ((monster[j].mv_way == 0 || monster[j].mv_way == 2) && monster[j].x + 32 < effect[i].x) {
										monster[j].x += 1;
									}
									else if ((monster[j].mv_way == 1 || monster[j].mv_way == 3) && monster[j].y + 32 > effect[i].y) {
										monster[j].y -= 1;
									}
									else if ((monster[j].mv_way == 1 || monster[j].mv_way == 3) && monster[j].y + 32 < effect[i].y) {
										monster[j].y += 1;
									}
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					case 5:		// 리코 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						if (effect[i].frame % 10 == 0) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 64 < monster[j].x + 32 && effect[i].y - 64 < monster[j].y + 32
									&& effect[i].x + 64 > monster[j].x - 32 && effect[i].y + 64 > monster[j].y - 32) {
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					case 6:		// 요우 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						if (effect[i].frame % 10 == 0) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 64 < monster[j].x + 32 && effect[i].y - 64 < monster[j].y + 32
									&& effect[i].x + 64 > monster[j].x - 32 && effect[i].y + 64 > monster[j].y - 32) {
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					case 7:		// 루비 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						break;
					case 8:		// 요우 서브스킬 이펙트
						Subskill[effect[i].kind].Draw(mem1dc, effect[i].x - 64, effect[i].y - 64, 128, 128,
							128 * ((int)(effect[i].frame / effect[i].setframe) % 5), 128 * ((int)(effect[i].frame / effect[i].setframe) / 5), 128, 128);
						if (effect[i].frame % 10 == 0) {
							for (j = 0; j < info.monster_num; ++j) {
								if (effect[i].x - 64 < monster[j].x + 32 && effect[i].y - 64 < monster[j].y + 32
									&& effect[i].x + 64 > monster[j].x - 32 && effect[i].y + 64 > monster[j].y - 32) {
									monster[j].hp -= effect[i].atk;
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)120;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].boss.skill == false && monster[j].boss.boss && monster[j].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
										monster[j].boss.skillcool -= (float)effect[i].atk / (float)200;
										if (monster[j].boss.skillcool < 0) {
											monster[j].boss.skillcool = 0;
										}
									}
									if (monster[j].hp < 0) {
										monster[j].hp = 0;
									}
								}
							}
						}
						break;
					}
				}
			}

			// 3번째 보스 더월드 출력
			if (mod.boss == true && monster[0].boss.skill == true && info.now_wave / 10 == 3) {
				Effect[3].StretchBlt(mem1dc, monster[0].x - shotdown, monster[0].y - shotdown, 64 + shotdown * 2, 64 + shotdown * 2,
					0, 0, 768, 768, DSTINVERT);
			}

			// 설치모드 보이게하기
			if (mod.install == 1 && map[mouse.sel_y][mouse.sel_x].kind == 1 && map[mouse.sel_y][mouse.sel_x].install == false) {
				Tower.Draw(mem1dc, mouse.x, mouse.y, info.tile_W, info.tile_H,
					info.tower_W * 0, info.tower_H * 4, info.tower_W, info.tower_H);
			}

			// 판매모드 보이게하기
			if (mod.sell == 1 && map[mouse.sel_y][mouse.sel_x].kind == 1 && map[mouse.sel_y][mouse.sel_x].install == true) {
				Tower.Draw(mem1dc, mouse.x, mouse.y, info.tile_W, info.tile_H,
					info.tower_W * 0, info.tower_H * 4, info.tower_W, info.tower_H);
			}

			// 합치기모드 보이게하기
			if (mod.combine == 1) {
				for (i = 0; i < 12; ++i) {
					for (j = 0; j < 12; ++j) {
						if (map[mouse.sel_y][mouse.sel_x].tower.rank == map[i][j].tower.rank
							&& map[mouse.sel_y][mouse.sel_x].tower.kind == map[i][j].tower.kind && map[i][j].install && info.combi_tower == 0 && map[mouse.sel_y][mouse.sel_x].install) {
							Tower.Draw(mem1dc, map[i][j].x, map[i][j].y, info.tile_W, info.tile_H,
								info.tower_W * 1, info.tower_H * 4, info.tower_W, info.tower_H);
						}  // if
						if (combi[0].tower.rank == map[i][j].tower.rank
							&& combi[0].tower.kind == map[i][j].tower.kind && map[i][j].install && info.combi_tower == 1) {
							Tower.Draw(mem1dc, map[i][j].x, map[i][j].y, info.tile_W, info.tile_H,
								info.tower_W * 1, info.tower_H * 4, info.tower_W, info.tower_H);
						}  // if
						if ((combi[0].x == map[i][j].x && combi[0].y == map[i][j].y)
							&& map[i][j].install) {
							Tower.Draw(mem1dc, map[i][j].x, map[i][j].y, info.tile_W, info.tile_H,
								info.tower_W * 0, info.tower_H * 4, info.tower_W, info.tower_H);
						}	// if
					}	// for j
				}	// for i
				if (map[mouse.sel_y][mouse.sel_x].kind == 1 && map[mouse.sel_y][mouse.sel_x].install == true) {
					Tower.Draw(mem1dc, mouse.x, mouse.y, info.tile_W, info.tile_H,
						info.tower_W * 0, info.tower_H * 4, info.tower_W, info.tower_H);
				}
			}	// if
			// 정보 보기
			if (mod.view_info == 1) {
				SelectObject(mem1dc, GetStockObject(NULL_BRUSH));
				Ellipse(mem1dc, map[mouse.save_y][mouse.save_x].x + (info.tile_W / 2) - (map[mouse.save_y][mouse.save_x].tower.range),
					map[mouse.save_y][mouse.save_x].y + (info.tile_H / 2) - (map[mouse.save_y][mouse.save_x].tower.range)
					, map[mouse.save_y][mouse.save_x].x + (info.tile_W / 2) + (map[mouse.save_y][mouse.save_x].tower.range),
					map[mouse.save_y][mouse.save_x].y + (info.tile_H / 2) + (map[mouse.save_y][mouse.save_x].tower.range));
				SelectObject(mem1dc, GetStockObject(WHITE_BRUSH));
			}

			// 마리 업그레이드 표시
			if (skill.mari_upgrade) {
				Skill.Draw(mem1dc, skill.tile_x * 64, skill.tile_y * 64, 64, 64, 768, 128, 128, 128);
			}
			// 스킬 범위 보이게하기
			if (skill.activate == false && mod.skill == 1) {
				switch (skill.type) {
				case 1:
				case 5:
					Skill.AlphaBlend(mem1dc, mx - 100, my - 100, 200, 200, 0, 0, 128, 128, 100);
					break;
				case 7:
					Skill.AlphaBlend(mem1dc, mx - 100, my - 100, 200, 200, 256, 0, 128, 128, 100);
					break;
				}
			}
			// 스킬 효과 출력
			else if (skill.activate) {
				switch (skill.type) {
				case 1:
					Skill.Draw(mem1dc, skill.draw_x - skill.range_x, skill.draw_y - skill.range_y, 2 * skill.range_x, 2 * skill.range_y, 128, 0, 128, 128);
					Skill.Draw(mem1dc, skill.draw_x - skill.range_x * 3, skill.draw_y - skill.range_y, 6 * skill.range_x, 2 * skill.range_y, 256, 256, 256, 256);
					/*
					switch (rand() % 2) {
					case 0:
						Skill.Draw(mem1dc, skill.draw_x - skill.range_x*2, skill.draw_y - skill.range_y, 4 * skill.range_x, 2 * skill.range_y, 256, 256, 256, 256);
						break;
					case 1:
						Skill.Draw(mem1dc, skill.draw_x - skill.range_x*2, skill.draw_y - skill.range_y, 4 * skill.range_x, 2 * skill.range_y, 512, 256, 256, 256);
						break;
					}
					*/
					break;
				case 5:
					Skill.AlphaBlend(mem1dc, skill.draw_x - skill.range_x, skill.draw_y - skill.range_y, 200, 200, 512, 0, 256, 256, 50);
					break;
				case 7:
					Skill.Draw(mem1dc, skill.draw_x - skill.range_x, skill.draw_y - 64, 2 * skill.range_x, 256, 384, 0, 128, 256);
					break;
				case 8:
					for (i = 0; i < info.monster_num; ++i) {
						switch (rand() % 2) {
						case 0:
							Skill.Draw(mem1dc, monster[i].x, monster[i].y, 64, 64, 768, 0, 128, 128);
							break;
						case 1:
							Skill.Draw(mem1dc, monster[i].x, monster[i].y, 64, 64, 896, 0, 128, 128);
							break;
						}
					}
					break;
				case 9:
					for (i = 0; i < 12; ++i) {
						for (j = 0; j < 12; ++j) {
							if (map[i][j].kind == 0)
								Skill.AlphaBlend(mem1dc, i * 64, j * 64, 64, 64, 0, 256, 256, 256, 255 - 5 * skill.skill_timer);
						}
					}
					break;
				}
			}
			// 스킬 컷인
			if (skill.play_cutin) {
				Cutin[skill.type - 1].AlphaBlend(mem1dc, 0, 0, skill.alpha);
			}
			// 업적
			if (mod.achive) {
				Achievement.AlphaBlend(mem1dc, 175, 650, 423, 100, 0, 0, 678, 160, achieve_ani.achieve_alpha);
				switch (achieve_ani.now_view) {
				case 0:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 161, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 1:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 253, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 2:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 621, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 3:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 253, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 4:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 529, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 5:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 529, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 6:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 345, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 7:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 345, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 8:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 437, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 9:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 437, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 10:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 0, 621, 339, 92, achieve_ani.achieve_alpha);
					break;
				case 11:
					Achievement.AlphaBlend(mem1dc, 240, 660, 339, 92, 339, 161, 339, 92, achieve_ani.achieve_alpha);
					break;
				}
			}
			if (mod.endgame) {
			// 게임오버화면
				System[2].AlphaBlend(mem1dc, 0, 0, 768, 768, 0, 80, 128, 176, info.gameover_alpha);
				System[2].AlphaBlend(mem1dc, 128, 200, 512, 80, 0, 0, 512, 80, info.gameover_alpha);
				System[2].AlphaBlend(mem1dc, main_buttons[3].x, main_buttons[3].y, main_buttons[3].width, main_buttons[3].height, 256, 80, 182, 26, info.gameover_alpha);
				// 게임클리어 화면
				System[2].AlphaBlend(mem1dc, 0, 0, 768, 768, 128, 80, 128, 176, info.gameclear_alpha);
				System[2].AlphaBlend(mem1dc, 128, 200, 512, 80, 0, 0, 512, 80, info.gameclear_alpha);
				System[2].AlphaBlend(mem1dc, main_buttons[3].x, main_buttons[3].y, main_buttons[3].width, main_buttons[3].height, 256, 80, 182, 26, info.gameclear_alpha);
			}
		}
		// 메인메뉴
		else if (mod.mainmenu) {
			System[0].Draw(mem1dc, 0, 0, 768, 768);
			//타이틀
			System[1].Draw(mem1dc, 134, 100, 500, 250, 0, 0, 1024, 512);
			//시작
			if (main_buttons[0].on_mouse) {
				System[1].Draw(mem1dc, main_buttons[0].x, main_buttons[0].y, main_buttons[0].width, main_buttons[0].height, 512, 512, 206, 54);
			}
			else {
				System[1].Draw(mem1dc, main_buttons[0].x, main_buttons[0].y, main_buttons[0].width, main_buttons[0].height, 0, 512, 206, 54);
			}
			//도움말
			if (main_buttons[1].on_mouse) {
				System[1].Draw(mem1dc, main_buttons[1].x, main_buttons[1].y, main_buttons[1].width, main_buttons[1].height, 512, 566, 427, 54);
			}
			else {
				System[1].Draw(mem1dc, main_buttons[1].x, main_buttons[1].y, main_buttons[1].width, main_buttons[1].height, 0, 566, 427, 54);
			}
			//종료
			if (main_buttons[2].on_mouse) {
				System[1].Draw(mem1dc, main_buttons[2].x, main_buttons[2].y, main_buttons[2].width, main_buttons[2].height, 512, 620, 133, 52);
			}
			else {
				System[1].Draw(mem1dc, main_buttons[2].x, main_buttons[2].y, main_buttons[2].width, main_buttons[2].height, 0, 620, 133, 52);
			}
		}
		//게임오버화면
		else if (mod.gameover) {
			if (info.gameover_alpha == 255) {
				System[2].Draw(mem1dc, 0, 0, 768, 768, 0, 80, 128, 176);
			}
			if (info.gameclear_alpha == 255) {
				System[2].Draw(mem1dc, 0, 0, 768, 768, 128, 80, 128, 176);
			}
			System[2].Draw(mem1dc, 128, 200, 512, 80, 0, 0, 512, 80);
			if (main_buttons[3].on_mouse) {
				System[2].Draw(mem1dc, main_buttons[3].x, main_buttons[3].y, main_buttons[3].width, main_buttons[3].height, 256, 106, 182, 26);
			}
			else {
				System[2].Draw(mem1dc, main_buttons[3].x, main_buttons[3].y, main_buttons[3].width, main_buttons[3].height, 256, 80, 182, 26);
			}
		}
		// 도움말
		else if (mod.howto) {
			HowtoP[info.howto_page].Draw(mem1dc, 0, 0, 768, 768, 0, 0, 1134, 1134);
		}

		// 메뉴 출력
		
			// 메뉴 배경
			Menu.Draw(mem1dc, 0, 768, 32, 1000-768, 183, 154, 32, 154);
			Menu.Draw(mem1dc, 32, 768, 768 - 64, 1000 -768, 183 + 32 * 1, 154, 32, 154);
			Menu.Draw(mem1dc, 768 - 32, 768, 32, 1000 -768, 183 + 32 * 2, 154, 32, 154);
			// 인포메이션 윈도우
			// 현재 기준 시작좌표 155,20		크기 518*171
			Menu.Draw(mem1dc, 155, 20+768, 32, 1000 - 40-768, 184 + 32 * 3, 154, 32, 154);
			Menu.Draw(mem1dc, 187, 20+768, 768 - 437, 1000 -768- 40, 184 + 32 * 4, 154, 32, 154);
			Menu.Draw(mem1dc, 768 - 250, 20+768, 32, 1000 - 768-40, 184 + 32 * 5, 154, 32, 154);
			{
				char tmp[4];
				// 웨이브
				Menu.Draw(mem1dc, 180, 171+768, 60, 30, 184, 109, 96, 40);
				if (info.now_wave <= 99) {
					if (info.now_wave / 10 != 0)
						Menu.Draw(mem1dc, 242, 175+768, 25, 25, number[info.now_wave / 10].x, number[info.now_wave / 10].y, number[info.now_wave / 10].width, number[info.now_wave / 10].height);
					Menu.Draw(mem1dc, 262, 175+768, 25, 25, number[info.now_wave % 10].x, number[info.now_wave % 10].y, number[info.now_wave % 10].width, number[info.now_wave % 10].height);
				}
				// 생명
				Menu.Draw(mem1dc, 320, 178+768, 20, 20, 178, 64, 13, 13);
				if (info.remain_life > 0 && info.remain_life < 100) {
					if (info.remain_life / 10 != 0) {
						Menu.Draw(mem1dc, 343, 175 + 768, 25, 25, number[info.remain_life / 10].x, number[info.remain_life / 10].y, number[info.remain_life / 10].width, number[info.remain_life / 10].height);
					}
					Menu.Draw(mem1dc, 363, 175 + 768, 25, 25, number[info.remain_life % 10].x, number[info.remain_life % 10].y, number[info.remain_life % 10].width, number[info.remain_life % 10].height);
				}
				// 재화
				Menu.Draw(mem1dc, 440, 178+768, 20, 20, 165, 64, 13, 13);
				if (info.money <= 999) {
					if (info.money >= 100)
						Menu.Draw(mem1dc, 462, 175+768, 25, 25, number[info.money / 100].x, number[info.money / 100].y, number[info.money / 100].width, number[info.money / 100].height);
					if (info.money >= 10)
						Menu.Draw(mem1dc, 482, 175+768, 25, 25, number[info.money % 100 / 10].x, number[info.money % 100 / 10].y, number[info.money % 100 / 10].width, number[info.money % 100 / 10].height);
					Menu.Draw(mem1dc, 502, 175+768, 25, 25, number[info.money % 10].x, number[info.money % 10].y, number[info.money % 10].width, number[info.money % 10].height);
				}
			}
			// 선택한 타워 정보
			// 모드 출력
			if (mod.view_info == 1) {
				// 등급
				switch (map[mouse.save_y][mouse.save_x].tower.rank)
				{
				case 0:
					Menu.Draw(mem1dc, 180, 30+768, 40, 40, 248, 32, 32, 32);
					break;
				case 1:
					Menu.Draw(mem1dc, 180, 30+768, 40, 40, 280, 32, 32, 32);
					break;
				case 2:
					Menu.Draw(mem1dc, 180, 30 + 768, 40, 40, 312, 32, 32, 32);
					break;
				case 3:
					Menu.Draw(mem1dc, 180, 30 + 768, 40, 40, 344, 32, 32, 32);
					break;
				}
				// 이름
				switch (map[mouse.save_y][mouse.save_x].tower.kind)
				{
				case 0:
					Menu.Draw(mem1dc, 222, 40 + 768, 89, 23, 376, 109, 89, 23);
					break;
				case 1:
					Menu.Draw(mem1dc, 222, 40 + 768, 133, 23, 376, 133, 133, 23);
					break;
				case 2:
					Menu.Draw(mem1dc, 222, 40 + 768, 87, 23, 376, 156, 87, 23);
					break;
				case 3:
					Menu.Draw(mem1dc, 222, 40 + 768, 118, 23, 376, 181, 118, 23);
					break;
				case 4:
					if (rand() % 2 == 0)
						Menu.Draw(mem1dc, 222, 40 + 768, 104, 23, 376, 206, 104, 23);
					else Menu.Draw(mem1dc, 222, 40 + 768, 103, 23, 376, 230, 103, 23);
					break;
				case 5:
					Menu.Draw(mem1dc, 222, 40 + 768, 118, 23, 376, 254, 118, 23);
					break;
				case 6:
					Menu.Draw(mem1dc, 222, 40 + 768, 104, 23, 376, 279, 104, 23);
					break;
				case 7:
					Menu.Draw(mem1dc, 222, 40 + 768, 103, 23, 376, 303, 103, 23);
					break;
				case 8:
					Menu.Draw(mem1dc, 222, 40 + 768, 103, 23, 376, 327, 103, 23);
					break;
				}
				// 얼굴
				switch (map[mouse.save_y][mouse.save_x].tower.kind)
				{
				case 0:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 0, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 0, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 0, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 0, 405, 96, 135);
						break;
					}
					break;
				case 1:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 96, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 96, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 96, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 96, 405, 96, 135);
						break;
					}
					break;
				case 2:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 192, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 192, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 192, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 192, 405, 96, 135);
						break;
					}
					break;
				case 3:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 288, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 288, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 288, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 288, 405, 96, 135);
						break;
					}
					break;
				case 4:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 384, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 384, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 384, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 384, 405, 96, 135);
						break;
					}
					break;
				case 5:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 480, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 480, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 480, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 480, 405, 96, 135);
						break;
					}
					break;
				case 6:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 576, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 576, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 576, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 576, 405, 96, 135);
						break;
					}
					break;
				case 7:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 672, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 672, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 672, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 672, 405, 96, 135);
						break;
					}
					break;
				case 8:
					switch (map[mouse.save_y][mouse.save_x].tower.rank)
					{
					case 3:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 768, 0, 96, 135);
						break;
					case 2:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 768, 135, 96, 135);
						break;
					case 1:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 768, 270, 96, 135);
						break;
					case 0:
						Card.Draw(mem1dc, 430, 30 + 768, 96, 135, 768, 405, 96, 135);
						break;
					}
					break;
				}
				// 공격력
				int atk = map[mouse.save_y][mouse.save_x].tower.atk*info.upgrade[map[mouse.save_y][mouse.save_x].tower.group] * info.dia_upgrade;
				if (atk > 9999)
					atk = 9999;
				Menu.Draw(mem1dc, 180, 73 + 768, 64, 32, 376, 32, 64, 32);
				if (atk >= 1000)
					Menu.Draw(mem1dc, 246, 73+768, 25, 25,
						number[atk / 1000].x, number[atk / 1000].y, number[atk / 1000].width, number[atk / 1000].height);
				if (atk >= 100)
					Menu.Draw(mem1dc, 266, 73 + 768, 25, 25,
						number[atk % 1000 / 100].x, number[atk % 1000 / 100].y, number[atk % 1000 / 100].width, number[atk % 1000 / 100].height);
				Menu.Draw(mem1dc, 286, 73 + 768, 25, 25,
					number[atk % 100 / 10].x, number[atk % 100 / 10].y, number[atk % 100 / 10].width, number[atk % 100 / 10].height);
				Menu.Draw(mem1dc, 306, 73 + 768, 25, 25,
					number[atk % 10].x, number[atk % 10].y, number[atk % 10].width, number[atk % 10].height);
				// 사정거리
				Menu.Draw(mem1dc, 180, 107 + 768, 64, 32, 440, 32, 64, 32);
				if (map[mouse.save_y][mouse.save_x].tower.range > 100)
					Menu.Draw(mem1dc, 266, 107 + 768, 25, 25,
						number[map[mouse.save_y][mouse.save_x].tower.range / 100].x, number[map[mouse.save_y][mouse.save_x].tower.range / 100].y, number[map[mouse.save_y][mouse.save_x].tower.range / 100].width, number[map[mouse.save_y][mouse.save_x].tower.range / 100].height);
				Menu.Draw(mem1dc, 286, 107 + 768, 25, 25,
					number[map[mouse.save_y][mouse.save_x].tower.range % 100 / 10].x, number[map[mouse.save_y][mouse.save_x].tower.range % 100 / 10].y, number[map[mouse.save_y][mouse.save_x].tower.range % 100 / 10].width, number[map[mouse.save_y][mouse.save_x].tower.range % 100 / 10].height);
				Menu.Draw(mem1dc, 306, 107 + 768, 25, 25,
					number[map[mouse.save_y][mouse.save_x].tower.range % 10].x, number[map[mouse.save_y][mouse.save_x].tower.range % 10].y, number[map[mouse.save_y][mouse.save_x].tower.range % 10].width, number[map[mouse.save_y][mouse.save_x].tower.range % 10].height);
			}
			else if (mod.combine == 1) {
				Menu.Draw(mem1dc, 230, 50 + 768, 240, 70, 269, 308, 104, 29);
			}
			else if (mod.install == 1) {
				Menu.Draw(mem1dc, 250, 50 + 768, 200, 80, 184, 308, 83, 29);
			}
			else if (mod.sell == 1) {
				Menu.Draw(mem1dc, 250, 50 + 768, 200, 80, 184, 337, 83, 29);
			}
			// 메세지
			SetBkMode(mem1dc, TRANSPARENT);
			if (upgrade_status == 1) {
				wsprintf(upgrade_message, "+%d Upgrade Complete", info.upgrade_stack[upgrade_kind]);
				TextOut(mem1dc, 270, 145 + 768, upgrade_message, strlen(upgrade_message));
			}
			else if (upgrade_status == 2) {
				TextOut(mem1dc, 300, 145 + 768, "Upgrade Fail", 12);
			}
			if (mission_status == 1) {
				TextOut(mem1dc, 300, 145 + 768, "Mission 1 activated", 19);
			}
			else if (mission_status == 2) {
				TextOut(mem1dc, 300, 145 + 768, "Mission 2 activated", 19);
			}
			else if (mission_status == 3) {
				TextOut(mem1dc, 300, 145 + 768, "Mission 3 activated", 19);
			}

			// 업그레이드 버튼
			for (int i = 0; i < 3; ++i) {
				if (buttons[i].on_mouse)
					Menu.Draw(mem1dc, buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttons[i].x, i * 154 + 77, buttons[i].width, buttons[i].height);
				else Menu.Draw(mem1dc, buttons[i].x, buttons[i].y, buttons[i].width, buttons[i].height, buttons[i].x, i * 154, buttons[i].width, buttons[i].height);
			}
			// 스킬 버튼
			hPen = CreatePen(PS_SOLID, 2, RGB(0, 255, 0));
			oldPen = (HPEN)SelectObject(mem1dc, hPen);
			Ellipse(mem1dc, buttons[3].x - 10, buttons[3].y - 10 , buttons[3].x + 186, buttons[3].y + 186 );
			for (int i = 0; i < skill.degree; i += 2) {
				MoveToEx(mem1dc, 658, 108+768, NULL);
				LineTo(mem1dc, 98 * cos(get_radian(i - 89)) + 668, 98 * sin(get_radian(i - 89)) + 118+768);
			}
			SelectObject(mem1dc, oldPen);
			DeleteObject(hPen);

			Menu.Draw(mem1dc, buttons[3].x, buttons[3].y, buttons[3].width, buttons[3].height, 152, 0, 64, 64);
			if (skill.type == 0)
				Menu.Draw(mem1dc, 618, 70+768, 100, 100, 216, 32, 32, 32);
			else
				Menu.Draw(mem1dc, 618, 70+768, 100, 100, 216 + 32 * (skill.type - 1), 0, 32, 32);

			//일시정지
			if (mod.pause) {
				Menu.Draw(mem1dc, 250, 400, 243, 77, 165, 385, 243, 77);
			}
		

		// 더블버퍼링
		BitBlt(hdc, 0, 0, width, high, mem1dc, 0, 0, SRCCOPY);

		// 소멸자
		SelectObject(mem1dc, oldBit1);
		DeleteDC(mem1dc);
		EndPaint(hWnd, &ps);
		break;

	case WM_CHAR:
		if (mod.gamemode) {
			mod.view_info = 0;
			if (mod.pause == false) {
				switch (wParam) {
				case 't':	// 설치모드 키
					mod.install = 1 - mod.install;
					mod.combine = 0;
					mod.sell = 0;
					break;
				case 'q':	// 합치기 모드
					mod.install = 0;
					mod.combine = 1 - mod.combine;
					mod.sell = 0;
					for (i = 0; i < 2; ++i) {
						combi[i].x = NULL;
						combi[i].y = NULL;
						combi[i].tower.kind = NULL;
						combi[i].tower.rank = NULL;
						combi[i].tower.group = NULL;
					}
					info.combi_tower = 0;
					break;
				case 'e':
					mod.sell = 1 - mod.sell;
					mod.combine = 0;
					mod.install = 0;
					break;
				case 'a':
					if (timer.mission[0] >= 15000) {
						add(&info.monster_num, &monster);
						monster[info.monster_num - 1].x = map[0][0].x;
						monster[info.monster_num - 1].y = map[0][0].y;
						monster[info.monster_num - 1].speed = 2;
						monster[info.monster_num - 1].hp = 2200;
						monster[info.monster_num - 1].maxhp = 2200;
						monster[info.monster_num - 1].mv_way = 1;
						monster[info.monster_num - 1].frame = 0;
						monster[info.monster_num - 1].kind = 0;
						monster[info.monster_num - 1].distance = 0;
						monster[info.monster_num - 1].death = 0;
						monster[info.monster_num - 1].boss.boss = false;
						monster[info.monster_num - 1].mission = true;
						timer.mission[0] = 0;
						mission_status = 1;
						SetTimer(child, 99, 3000, NULL);
					}
					break;
				case 's':
					if (timer.mission[1] >= 15000) {
						add(&info.monster_num, &monster);
						monster[info.monster_num - 1].x = map[0][0].x;
						monster[info.monster_num - 1].y = map[0][0].y;
						monster[info.monster_num - 1].speed = 2;
						monster[info.monster_num - 1].hp = 20000;
						monster[info.monster_num - 1].maxhp = 20000;
						monster[info.monster_num - 1].mv_way = 1;
						monster[info.monster_num - 1].frame = 0;
						monster[info.monster_num - 1].kind = 1;
						monster[info.monster_num - 1].distance = 0;
						monster[info.monster_num - 1].death = 0;
						monster[info.monster_num - 1].boss.boss = false;
						monster[info.monster_num - 1].mission = true;
						timer.mission[1] = 0;
						mission_status = 2;
						SetTimer(child, 99, 3000, NULL);
					}
					break;
				case 'd':
					if (timer.mission[2] >= 15000) {
						add(&info.monster_num, &monster);
						monster[info.monster_num - 1].x = map[0][0].x;
						monster[info.monster_num - 1].y = map[0][0].y;
						monster[info.monster_num - 1].speed = 2;
						monster[info.monster_num - 1].hp = 120000;
						monster[info.monster_num - 1].maxhp = 120000;
						monster[info.monster_num - 1].mv_way = 1;
						monster[info.monster_num - 1].frame = 0;
						monster[info.monster_num - 1].kind = 2;
						monster[info.monster_num - 1].distance = 0;
						monster[info.monster_num - 1].death = 0;
						monster[info.monster_num - 1].boss.boss = false;
						monster[info.monster_num - 1].mission = true;
						timer.mission[2] = 0;
						mission_status = 3;
						SetTimer(child, 99, 3000, NULL);
					}
					break;
				}
			}
			switch (wParam) {
			case 'p':
				if (mod.pause) {
					mod.pause = false;
					SetTimer(hWnd, 1, 15, NULL);
				}
				else {
					KillTimer(hWnd, 1);
					mod.pause = true;
					InvalidateRect(hWnd, NULL, FALSE);
					//UpdateWindow(hWnd);
				}
				break;
			}
		}
		break;

	case WM_MOUSEMOVE:
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		if (mod.gamemode) {
			// 자리 충돌체크 및 설치모드 보이게하기 정보 설정
			for (i = 0; i < 12; ++i) {
				for (j = 0; j < 12; ++j) {
					if (map[i][j].x < mx && map[i][j].x + info.tile_W > mx && map[i][j].y < my && map[i][j].y + info.tile_H > my) {
						mouse.x = map[i][j].x;
						mouse.y = map[i][j].y;
						mouse.sel_x = j;
						mouse.sel_y = i;
					}
				}
			}
		}
		else if (mod.mainmenu) {
			if (mouse_in_box(mx, my, main_buttons[0])) {
				main_buttons[0].on_mouse = true;
				main_buttons[1].on_mouse = false;
				main_buttons[2].on_mouse = false;
			}
			else {
				main_buttons[0].on_mouse = false;
			}
			if (mouse_in_box(mx, my, main_buttons[1])) {
				main_buttons[0].on_mouse = false;
				main_buttons[1].on_mouse = true;
				main_buttons[2].on_mouse = false;
			}
			else {
				main_buttons[2].on_mouse = false;
			}
			if (mouse_in_box(mx, my, main_buttons[2])) {
				main_buttons[0].on_mouse = false;
				main_buttons[1].on_mouse = false;
				main_buttons[2].on_mouse = true;
			}
			else {
				main_buttons[2].on_mouse = false;
			}

		}
		else if (mod.gameover) {
			if (mouse_in_box(mx, my, main_buttons[3])) {
				main_buttons[3].on_mouse = true;
			}
			else {
				main_buttons[3].on_mouse = false;
			}
		}
		break;
	case WM_LBUTTONUP:
		for (int i = 0; i < 4; ++i) {
			buttons[i].on_mouse = false;
		}
		break;
	case WM_LBUTTONDOWN:
		if (mod.gamemode&&mod.pause==false) {
			mod.view_info = 0;
			if (mod.skill == 1 && skill.activate == false) {
				if (skill.type == 7) {
					skill.draw_x = mx;
					skill.draw_y = -300;
				}
				else if (skill.type == 5) {
					skill.draw_x = mx;
					skill.draw_y = my;
				}
				skill.x = mx;
				skill.y = my;
				skill.delta_x = skill.x - skill.draw_x;
				skill.delta_y = skill.y - skill.draw_y;
				skill.degree = 0;
				skill.activate = true;
				skill.play_cutin = true;
				// 스킬 보이스
				FMOD_Sound_Release(Skill_sound);
				switch (skill.type) {
				case 1:
					FMOD_System_CreateSound(soundSystem, "resource/sound/chika/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 2:
					FMOD_System_CreateSound(soundSystem, "resource/sound/hanamaru/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 3:
					FMOD_System_CreateSound(soundSystem, "resource/sound/mari/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 4:
					FMOD_System_CreateSound(soundSystem, "resource/sound/riko/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 5:
					FMOD_System_CreateSound(soundSystem, "resource/sound/yoshiko/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 6:
					FMOD_System_CreateSound(soundSystem, "resource/sound/dia/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 7:
					FMOD_System_CreateSound(soundSystem, "resource/sound/you/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 8:
					FMOD_System_CreateSound(soundSystem, "resource/sound/ruby/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				case 9:
					FMOD_System_CreateSound(soundSystem, "resource/sound/kanan/skill.mp3", FMOD_DEFAULT, 0, &Skill_sound);
					break;
				}
				FMOD_System_PlaySound(soundSystem, Skill_sound, NULL, false, &Skill_sound_c);
			}
			// 타워 정보 차일드 윈도우에 출력
			if (mod.sell == 0 && mod.combine == 0 && mod.install == 0 && map[mouse.sel_y][mouse.sel_x].install) {
				mod.view_info = 1;
				mouse.save_x = mouse.sel_x;
				mouse.save_y = mouse.sel_y;

				// 누른 타워의 멤버에따라 소리 재생
				FMOD_Sound_Release(Touch_voice);
				switch (map[mouse.sel_y][mouse.sel_x].tower.kind) {
				case 0:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/chika/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/chika/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/chika/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 1:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/hanamaru/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/hanamaru/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/hanamaru/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 2:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/mari/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/mari/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/mari/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 3:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/riko/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/riko/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/riko/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 4:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/yoshiko/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/yoshiko/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/yoshiko/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 5:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/dia/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/dia/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/dia/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 6:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/you/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/you/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/you/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 7:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/ruby/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/ruby/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/ruby/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				case 8:
					switch (rand() % 3) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/kanan/touch_1.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/kanan/touch_2.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/kanan/touch_3.mp3", FMOD_DEFAULT, 0, &Touch_voice);
						break;
					}
					break;
				}
				FMOD_System_PlaySound(soundSystem, Touch_voice, NULL, false, &Touch_voice_c);
				// 만질때 소리 줄이기
				FMOD_Channel_SetVolume(Touch_voice_c, 0.7);
			}

			// 눌럿을때 타워 설치 정보 설정
			if (mod.install == 1 && map[mouse.sel_y][mouse.sel_x].install == false && map[mouse.sel_y][mouse.sel_x].kind == 1 && info.money >= 5) {
				mod.install = 1 - mod.install;
				map[mouse.sel_y][mouse.sel_x].install = true;
				map[mouse.sel_y][mouse.sel_x].tower.x = map[mouse.sel_y][mouse.sel_x].x;
				map[mouse.sel_y][mouse.sel_x].tower.y = map[mouse.sel_y][mouse.sel_x].y;
				map[mouse.sel_y][mouse.sel_x].tower.kind = rand() % 9;
				// 치트부분 타워가 특정 타워만 나옴
				// map[mouse.sel_y][mouse.sel_x].tower.kind = 1;
				map[mouse.sel_y][mouse.sel_x].tower.rank = info.nextrank;
				// 치트부분 타워가 최종등급의 타워만 나옴
				//map[mouse.sel_y][mouse.sel_x].tower.rank = 3;
				map[mouse.sel_y][mouse.sel_x].tower.group = map[mouse.sel_y][mouse.sel_x].tower.kind / 3;
				towerset(&map[mouse.sel_y][mouse.sel_x].tower);
				map[mouse.sel_y][mouse.sel_x].tower.ur_skillchk = false;
				map[mouse.sel_y][mouse.sel_x].tower.target = NULL;
				info.nextrank = 0;
				info.money -= 5;
				FMOD_Sound_Release(Effect_sound);
				FMOD_System_CreateSound(soundSystem, "resource/sound/system/r_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
				FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);
				achievement(&map[0][0], &info, &achieve);
			}
			// 설치모드 확인
			if (mod.combine == 1 && map[mouse.sel_y][mouse.sel_x].install && map[mouse.sel_y][mouse.sel_x].tower.rank <= 3) {
				combi[info.combi_tower] = map[mouse.sel_y][mouse.sel_x];
				info.combi_tower++;
			}
			if (info.combi_tower == 2) {
				// 같은 자리를 눌렀을때
				if (combi[0].x == combi[1].x && combi[0].y == combi[1].y) {
					for (i = 0; i < 2; ++i) {
						combi[i].x = NULL;
						combi[i].y = NULL;
						combi[i].tower.kind = NULL;
						combi[i].tower.rank = NULL;
						combi[i].tower.group = NULL;
					}
					info.combi_tower = 0;
				}	// else if
					// 다른 종류의 타워를 눌렀을때
				else if ((combi[0].tower.rank != combi[1].tower.rank) || (combi[0].tower.kind != combi[1].tower.kind)) {
					mod.combine = 1 - mod.combine;
					for (i = 0; i < 2; ++i) {
						combi[i].x = NULL;
						combi[i].y = NULL;
						combi[i].tower.kind = NULL;
						combi[i].tower.rank = NULL;
						combi[i].tower.group = NULL;
					}
					info.combi_tower = 0;
				}	// else if
				else if (combi[0].tower.rank == 3 || combi[1].tower.rank == 3) {
					mod.combine = 1 - mod.combine;
					for (i = 0; i < 2; ++i) {
						combi[i].x = NULL;
						combi[i].y = NULL;
						combi[i].tower.kind = NULL;
						combi[i].tower.rank = NULL;
						combi[i].tower.group = NULL;
					}
					info.combi_tower = 0;
				}
				// 그외에
				else {
					for (i = 0; i < 12; ++i) {
						for (j = 0; j < 12; ++j) {
							if ((combi[1].x == map[i][j].x && combi[1].y == map[i][j].y)
								&& (combi[0].tower.rank == combi[1].tower.rank && combi[0].tower.kind == combi[1].tower.kind)
								&& map[i][j].install) {
								towercombine(&map[i][j].tower);
								//합칠때 소리 재생
								FMOD_Sound_Release(Effect_sound);
								switch (combi[0].tower.rank) {
								case 0:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/sr_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
									break;
								case 1:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/ssr_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
									break;
								case 2:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/ur_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
									break;
								}
								FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);
								achievement(&map[0][0], &info, &achieve);
								mod.combine = 1 - mod.combine;
								info.combi_tower = 0;
							}	// if
							if ((combi[0].x == map[i][j].x && combi[0].y == map[i][j].y)
								&& (combi[0].tower.rank == combi[1].tower.rank && combi[0].tower.kind == combi[1].tower.kind)
								&& map[i][j].install) {
								map[i][j].install = false;
							}	// if
						}	// for j
					}	// for i
				}	// else
			}	// if

			if (mod.sell == 1 && map[mouse.sel_y][mouse.sel_x].install) {
				if (play_lotto(50)) {
					switch (map[mouse.sel_y][mouse.sel_x].tower.rank) {
					case 0:
						info.money += 5;
						break;
					case 1:
						info.money += 10;
						break;
					case 2:
						info.money += 20;
						break;
					case 3:
						info.money += 40;
						break;
					}
				}
				map[mouse.sel_y][mouse.sel_x].install = false;
				mod.sell = 0;
			}
			for (int i = 0; i < 4; ++i) {
				if (mouse_in_box(mx, my, buttons[i]))
					buttons[i].on_mouse = true;
			}
			// 업그레이드
			for (int i = 0; i < 3; ++i) {
				if (buttons[i].on_mouse&&info.upgrade[i] < 3.00) {
					//업그레이드 성공
					if (upgrade(&info.upgrade[i], &info.money)) {
						upgrade_status = 1;
						info.upgrade_stack[i]++;
						upgrade_kind = i;
						SetTimer(hWnd, 99, 3000, NULL);
						FMOD_Channel_Stop(Effect_sound_c);
						FMOD_Sound_Release(Effect_sound);
						FMOD_System_CreateSound(soundSystem, "resource/sound/system/up_success.ogg", FMOD_DEFAULT, 0, &Effect_sound);
						FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);
					}
					//실패
					else {
						upgrade_status = 2;
						SetTimer(hWnd, 99, 3000, NULL);
						FMOD_Channel_Stop(Effect_sound_c);
						FMOD_Sound_Release(Effect_sound);
						FMOD_System_CreateSound(soundSystem, "resource/sound/system/up_fail.ogg", FMOD_DEFAULT, 0, &Effect_sound);
						FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);
					}
				}
				achievement(&map[0][0], &info, &achieve);
			}
			// 스킬 빠르게 쓰고싶을때
			/*
			if (skill.degree < 360 && mouse_in_box(mx, my, buttons[3]) && skill.activate == false)
			skill.degree += 360;
			if (skill.degree >= 360 && skill.type == 0 && skill.activate == false) {
			skill.type = 9;
			skill.skill_timer = 0;
			skill.kanan_timer = 0;
			}
			else if (skill.degree == 360 && skill.type != 0 && mouse_in_box(mx, my, buttons[3]) && skill.activate == false) {
			mod.skill = 1;
			switch (skill.type) {
			case 1:
			skill.range_x = 100;
			skill.range_y = 100;
			skill.draw_x = 1000;
			skill.draw_y = -200;
			break;
			case 5:
			skill.range_x = 100;
			skill.range_y = 100;
			break;
			case 7:
			skill.range_x = 32;
			skill.range_y = 1024;
			skill.draw_y = -200;
			break;
			default:
			break;
			}
			}
			*/
			// 통상		
			if (skill.degree == 360 && skill.type != 0 && mouse_in_box(mx, my, buttons[3]) && skill.activate == false) {
				mod.skill = 1;
				switch (skill.type) {
				case 1:
					skill.range_x = 100;
					skill.range_y = 100;
					skill.draw_x = 1000;
					skill.draw_y = -200;
					break;
				case 5:
					skill.range_x = 100;
					skill.range_y = 100;
					break;
				case 7:
					skill.range_x = 32;
					skill.range_y = 1024;
					skill.draw_y = -200;
					break;
				default:
					break;
				}
			}
		}
		else if (mod.mainmenu) {
			if (mouse_in_box(mx, my, main_buttons[0])) {
				// BGM 교체
				FMOD_System_PlaySound(soundSystem, Menu_sound, NULL, false, &Menu_sound_c);
				FMOD_Channel_Stop(BGM_c);
				FMOD_Sound_Release(BGM);
				switch (rand() % 8) {
				case 0:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_1.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 1:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_2.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 2:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_3.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 3:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_4.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 4:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_5.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 5:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_6.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 6:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_7.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				case 7:
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_8.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					break;
				}
				FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
				FMOD_Sound_GetLength(BGM, sound_length, FMOD_TIMEUNIT_MS);
				start = clock();
				FMOD_Channel_SetVolume(BGM_c, 0.3);

				//스킬게이지
				FMOD_System_CreateSound(soundSystem, "resource/sound/system/skill_slot_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
				//맞출때, 몬스터 죽을때 소리
				FMOD_System_CreateSound(soundSystem, "resource/sound/system/hit.wav", FMOD_DEFAULT, 0, &Hit_sound);
				FMOD_System_CreateSound(soundSystem, "resource/sound/system/boom.wav", FMOD_DEFAULT, 0, &Boom_sound);

				mod.mainmenu = false;
				mod.gamemode = true;
				SetWindowPos(hWnd, HWND_TOP, 0, 0, width, high, SWP_NOZORDER);

				// map 정보 저장
				for (i = 0; i < 12; ++i) {
					for (j = 0; j < 12; ++j) {
						map[i][j].x = 64 * j;
						map[i][j].y = 64 * i;
						map[i][j].install = false;
						map[i][j].tower.atk_tmr = 0;
					}
				}
				for (i = 0; i < 12; ++i) {
					map[0][i].kind = 0;
					map[4][i].kind = 0;
					map[7][i].kind = 0;
					map[11][i].kind = 0;
					map[i][0].kind = 0;
					map[i][4].kind = 0;
					map[i][7].kind = 0;
					map[i][11].kind = 0;
				}
				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 3; ++j) {
						map[1 + i][1 + j].kind = 1;
						map[1 + i][8 + j].kind = 1;
						map[8 + i][1 + j].kind = 1;
						map[8 + i][8 + j].kind = 1;
					}
				}

				for (i = 0; i < 3; ++i) {
					for (j = 0; j < 2; ++j) {
						map[1 + i][5 + j].kind = 1;
						map[8 + i][5 + j].kind = 1;
					}
				}

				for (i = 0; i < 2; ++i) {
					for (j = 0; j < 3; ++j) {
						map[5 + i][1 + j].kind = 1;
						map[5 + i][8 + j].kind = 1;
					}
				}

				for (i = 0; i < 2; ++i) {
					for (j = 0; j < 2; ++j) {
						map[5 + i][5 + j].kind = 1;
					}
				}
				for (i = 0; i < 2; ++i) {
					map[5 + i][0].kind = 2;
					map[0][5 + i].kind = 2;
					map[5 + i][11].kind = 2;
					map[11][5 + i].kind = 2;
				}

				map[0][4].kind = 3;

				map_addr = &map[0][0];
				// 그 외에 변수 저장
				shotdown = 0;
				timer.frame_tmr = 0;
				timer.mv_tmr = 0;
				timer.die_tmr = 0;
				timer.breaktime = 0;
				timer.mari_tmr = 0;
				timer.mission[0] = 15000;
				timer.mission[1] = 15000;
				timer.mission[2] = 15000;
				mod.install = 0;
				mod.sell = 0;
				mod.combine = 0;
				mod.breaktime = 1;
				// BBBBBBB
				mod.boss = 0;
				mod.view_info = 0;
				info.monster_num = 0;
				info.bullet_num = 0;
				info.effect_num = 0;
				info.nextrank = 0;
				info.combi_tower = 0;
				// BBBBBBB
				info.now_wave = 0;
				info.money = 30;
				info.count_mon = 0;
				info.remain_life = 20;
				info.gameover_alpha = 0;
				info.gameclear_alpha = 0;
				info.kill_count = 0;
				skill.degree = 0;
				skill.type = 0;
				skill.alpha = 0;
				skill.cutin_timer = 0;
				skill.skill_timer = 0;
				for (i = 0; i < 10; ++i) {
					only_kanan[i].kanan_timer = -32;
				}
				info.nextmonspd = rand() % 4 + 1;
				for (i = 0; i < 3; ++i) {
					info.upgrade_stack[i] = 0;
					info.upgrade[i] = 1.0;
				}
				info.dia_upgrade = 1.0;
				for (i = 0; i < 12; ++i) {
					achieve.Achive_List[i] = false;
					achieve_ani.Achive_List[i] = false;
				}
				achieve.achieve_alpha = 0;
				achieve.achieve_counter= 0;
				achieve.now_view = 0;
				achieve.popup_mod = false;
				achieve_ani.achieve_alpha = 0;
				achieve_ani.achieve_counter = 0;
				achieve_ani.now_view = 0;
				achieve_ani.popup_mod = false;
			}
			else if (mouse_in_box(mx, my, main_buttons[1])) {
				FMOD_System_PlaySound(soundSystem, Menu_sound, NULL, false, NULL);
				mod.mainmenu = false;
				mod.howto = true;
			}
			else if (mouse_in_box(mx, my, main_buttons[2])) {
				PostQuitMessage(0);
			}

		}
		else if (mod.gameover) {
			if (mouse_in_box(mx, my, main_buttons[3])) {
				info.gameover_alpha = 0;
				info.gameover = false;
				info.gameclear = false;
				mod.gameover = false;
				mod.gamemode = false;
				mod.mainmenu = true;
				FMOD_Channel_Stop(BGM_c);
				FMOD_Channel_Stop(Effect_sound_c);
				FMOD_Channel_Stop(Hit_sound_c);
				FMOD_Channel_Stop(Boom_sound_c);
				FMOD_Sound_Release(BGM);
				FMOD_Sound_Release(Hit_sound);
				FMOD_Sound_Release(Boom_sound);
				FMOD_Sound_Release(Effect_sound);
				FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/main.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
				FMOD_System_PlaySound(soundSystem, Menu_sound, NULL, false, &Menu_sound_c);
				FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
				FMOD_Channel_SetVolume(BGM_c, 1.0);
			}
		}
		else if (mod.howto) {
			info.howto_page++;
			if (info.howto_page == 9) {
				mod.mainmenu = true;
				mod.howto = false;
				info.howto_page = 0;
			}
		}	

		
		break;

	case WM_RBUTTONDOWN:
		mod.combine = 0;
		mod.install = 0;
		mod.skill = 0;
		mod.sell=0;
		mod.view_info = 0;
		break;

	case WM_TIMER:
		switch(wParam){
		case 99:
			mission_status = 0;
			upgrade_status = 0;

			KillTimer(hWnd, 99);
			break;
		case 1:
		// 게임 중
		if (mod.gamemode) {
			end = clock();
			if (end - start >= bgm_length) {
				FMOD_Channel_Stop(BGM_c);
				FMOD_Sound_Release(BGM);
				if (play_lotto(1)) {
					FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_hidden.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
					if (achieve.Achive_List[10] == false) {
						achieve.Achive_List[10] = true;
					}
				}
				else {
					switch (rand() % 8) {
					case 0:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_1.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 1:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_2.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 2:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_3.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 3:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_4.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 4:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_5.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 5:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_6.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 6:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_7.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					case 7:
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_8.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						break;
					}
				}
				FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
				FMOD_Channel_SetVolume(BGM_c, 0.3);
				FMOD_Sound_GetLength(BGM, sound_length, FMOD_TIMEUNIT_MS);
				start = clock();
			}
			// 스킬 사용 중 일시정지
			// 장판 계열은 제외
			if (skill.activate == false || (skill.type == 2 || skill.type == 5 || skill.type == 6 || skill.type == 8) && skill.play_cutin == false) {
				// 타이머 함수들
					timer.frame_tmr++;
					timer.mv_tmr++;
					for (i = 0; i < 3; ++i) {
						if (timer.mission[i] < 15000) {
							timer.mission[i]++;
						}
					}

				if (mod.breaktime == 1) {
					timer.breaktime++;
					if (timer.breaktime > 100) {
						mod.breaktime = 0;
						info.now_wave++;
						if (info.now_wave % 10 == 0) {
							mod.boss = 1;
						}
						// BBBBBBB
						//info.now_wave--;
					}
				}

				if (mod.boss == 0) {
					// 몬스터 생성 하면서 정의
					if (timer.frame_tmr >= 40 && info.count_mon < 20 && mod.breaktime == 0) {
						add(&info.monster_num, &monster);
						monster[info.monster_num - 1].x = map[0][0].x;
						monster[info.monster_num - 1].y = map[0][0].y;
						monster[info.monster_num - 1].speed = info.nextmonspd;
						monster[info.monster_num - 1].hp = 500 + (info.now_wave * (int)(info.now_wave / 4) * 150) + (info.now_wave * (int)(info.now_wave / 4) * 150 / monster[info.monster_num - 1].speed);
						monster[info.monster_num - 1].maxhp = 500 + (info.now_wave * (int)(info.now_wave / 4) * 150) + (info.now_wave * (int)(info.now_wave / 4) * 150 / monster[info.monster_num - 1].speed);
						monster[info.monster_num - 1].mv_way = 1;
						monster[info.monster_num - 1].frame = 0;
						monster[info.monster_num - 1].kind = ((info.now_wave - 1) % 4) * 3 + ((info.now_wave - 1) % 3);
						monster[info.monster_num - 1].distance = 0;
						monster[info.monster_num - 1].death = 0;
						monster[info.monster_num - 1].boss.boss = false;
						monster[info.monster_num - 1].mission = false;
						info.count_mon++;
						timer.frame_tmr = 0;
					}

					// 몬스터 모션
					if (timer.mv_tmr >= 9) {
						for (i = 0; i < info.monster_num; ++i) {
							if (monster[i].hp > 0) {
								monster[i].frame++;
							}
							// 미션몬스터는 3프레임
							if (monster[i].mission) {
								monster[i].frame %= 3;
							}
							else {
								monster[i].frame %= 4;
							}
						}
						timer.mv_tmr = 0;
					}

					// 몬스터 방향전환
					// 방향전환
					for (k = 0; k < info.monster_num; ++k) {
						RECT mon = { monster[k].x , monster[k].y , monster[k].x + 64 , monster[k].y + 64 };
						for (i = 0; i < 12; ++i) {
							for (j = 0; j < 12; ++j) {
								RECT rect = { map[i][j].x , map[i][j].y , map[i][j].x + 64 , map[i][j].y + 64 };
								// 다음 갈곳이 없을때

								if ((rectcrash(mon, rect) && map[i][j].kind == 3) && monster[k].mv_way == 3) {			// 라이프 깎임
									if (!(skill.activate&&skill.type == 2)) {
										if (monster[k].mission == false) {
											info.remain_life -= 1;
										}
										else {
											info.remain_life -= 5;
										}
										if (info.remain_life <= 0) {
											info.gameover = true;
											mod.endgame = true;
											SetWindowPos(hWnd, HWND_TOP, 0, 0, width, 807, SWP_NOZORDER);
											//실패음 재생
											FMOD_Channel_Stop(BGM_c);
											FMOD_Sound_Release(BGM);
											switch (rand() % 9) {
											case 0:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_1.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 1:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_2.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 2:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_3.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 3:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_4.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 4:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_5.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 5:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_6.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 6:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_7.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 7:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_8.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 8:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_9.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											}
											FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
											FMOD_Channel_SetVolume(BGM_c, 1.0);
										}
									}
									for (l = 0; l < info.bullet_num; ++l) {
										if (bullet[l].target == k) {
											bullet[l].target_lose = true;
										}
										if (bullet[l].target > k) {
											bullet[l].target -= 1;
										}
									}
									for (l = k; l < info.monster_num - 1; ++l) {
										monster[l] = monster[l + 1];
									}
									achievement(&map[0][0], &info, &achieve);
									del(&info.monster_num, &monster);
								}	// if

								if ((rectcrash(mon, rect) && map[i][j].kind == 2) && monster[k].mv_way == 0) {			// 오른쪽으로 이동할때
									monster[k].x = map[i][j].x - 64;
									monster[k].mv_way = 3;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 1) {								// 아래쪽으로 이동할때
									monster[k].y = map[i][j].y - 64;
									monster[k].mv_way = 0;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 2) {								// 왼쪽으로 이동할때
									monster[k].x = map[i][j].x + 64;
									monster[k].mv_way = 1;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 3) {								// 위쪽으로 이동할때
									monster[k].y = map[i][j].y + 64;
									monster[k].mv_way = 2;
								}	// if

									// 밖으로 나갈때
								if (monster[k].x + 64 >= 64 * 12 && monster[k].mv_way == 0) {							// 오른쪽으로 이동할때
									monster[k].x = 64 * 11;
									monster[k].mv_way = 3;
								}	// if
								else if (monster[k].y + 64 >= 64 * 12 && monster[k].mv_way == 1) {						// 아래쪽으로 이동할때
									monster[k].y = 64 * 11;
									monster[k].mv_way = 0;
								}	// if
								else if (monster[k].x <= 0 && monster[k].mv_way == 2) {								// 왼쪽으로 이동할때
									monster[k].x = 0;
									monster[k].mv_way = 1;
								}	// if
								else if (monster[k].y <= 0 && monster[k].mv_way == 3) {								// 위쪽으로 이동할때
									monster[k].y = 0;
									monster[k].mv_way = 2;
								}	// if
							}	// for j
						}	// for i
					}	// for k
					if (!(skill.type == 8 && skill.activate == true)) {
						for (i = 0; i < info.monster_num; ++i) {
							// 이동
							if (monster[i].hp > 0) {
								if (monster[i].mv_way == 0) {
									monster[i].distance += monster[i].speed;
									monster[i].x += monster[i].speed;
								}
								if (monster[i].mv_way == 1) {
									monster[i].distance += monster[i].speed;
									monster[i].y += monster[i].speed;
								}
								if (monster[i].mv_way == 2) {
									monster[i].distance += monster[i].speed;
									monster[i].x -= monster[i].speed;
								}
								if (monster[i].mv_way == 3) {
									monster[i].distance += monster[i].speed;
									monster[i].y -= monster[i].speed;
								}
							}
						}
					}
				}


				if (mod.boss == 1) {
					if (info.count_mon < 1) {
						add(&info.monster_num, &monster);
						monster[info.monster_num - 1].x = map[0][0].x;
						monster[info.monster_num - 1].y = map[0][0].y;
						monster[info.monster_num - 1].speed = 1.5;
						monster[info.monster_num - 1].hp = (500 + (info.now_wave * (int)(info.now_wave / 4) * 150) + (info.now_wave * (int)(info.now_wave / 4) * 150 / monster[info.monster_num - 1].speed)) * 10;
						monster[info.monster_num - 1].maxhp = (500 + (info.now_wave * (int)(info.now_wave / 4) * 150) + (info.now_wave * (int)(info.now_wave / 4) * 150 / monster[info.monster_num - 1].speed)) * 10;
						monster[info.monster_num - 1].mv_way = 1;
						monster[info.monster_num - 1].frame = 0;
						monster[info.monster_num - 1].kind = info.now_wave / 10;
						// BBBBBBB
						//monster[info.monster_num - 1].kind = 2;
						monster[info.monster_num - 1].distance = 0;
						monster[info.monster_num - 1].death = 0;
						monster[info.monster_num - 1].mission = false;
						monster[info.monster_num - 1].boss.boss = true;
						monster[info.monster_num - 1].boss.act = 0;
						monster[info.monster_num - 1].boss.skill = false;
						monster[info.monster_num - 1].boss.skillcool = 0;
						switch (monster[info.monster_num - 1].kind) {
						case 1:
							monster[info.monster_num - 1].boss.skillmax = 500;
							break;
						case 2:
							monster[info.monster_num - 1].boss.skillmax = 500;
							break;
						case 3:
							monster[info.monster_num - 1].boss.skillmax = 500;
							break;
						case 4:
							monster[info.monster_num - 1].boss.skillmax = 500;
							break;
						}
						info.count_mon++;
						timer.frame_tmr = 0;
					}

					// 몬스터 모션
					if (timer.mv_tmr >= 9) {
						for (i = 0; i < info.monster_num; ++i) {
							if (monster[i].hp > 0) {
								monster[i].frame++;
							}
							// 미션몬스터는 3프레임
							if (monster[i].mission) {
								monster[i].frame %= 3;
							}
							else {
								monster[i].frame %= 4;
							}
						}
						timer.mv_tmr = 0;
					}

					// 몬스터 방향전환
					// 방향전환
					for (k = 0; k < info.monster_num; ++k) {
						RECT mon = { monster[k].x , monster[k].y , monster[k].x + 64 , monster[k].y + 64 };
						for (i = 0; i < 12; ++i) {
							for (j = 0; j < 12; ++j) {
								RECT rect = { map[i][j].x , map[i][j].y , map[i][j].x + 64 , map[i][j].y + 64 };
								// 다음 갈곳이 없을때

								if ((rectcrash(mon, rect) && map[i][j].kind == 3) && monster[k].mv_way == 3) {			// 라이프 깎임
									if (!(skill.activate&&skill.type == 2)) {
										info.remain_life -= 10;
										if (info.remain_life <= 0 || info.now_wave == 40) {
											info.gameover = true;
											mod.endgame = true;
											SetWindowPos(hWnd, HWND_TOP, 0, 0, width, 807, SWP_NOZORDER);
											//실패소리재생
											FMOD_Channel_Stop(BGM_c);
											FMOD_Sound_Release(BGM);
											switch (rand() % 9) {
											case 0:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_1.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 1:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_2.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 2:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_3.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 3:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_4.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 4:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_5.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 5:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_6.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 6:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_7.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 7:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_8.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											case 8:
												FMOD_System_CreateSound(soundSystem, "resource/sound/system/fail_9.mp3", FMOD_DEFAULT, 0, &BGM);
												break;
											}
											FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
											FMOD_Channel_SetVolume(BGM_c, 1.0);
										}
									}
									for (l = 0; l < info.bullet_num; ++l) {
										if (bullet[l].target == k) {
											bullet[l].target_lose = true;
										}
										if (bullet[l].target > k) {
											bullet[l].target -= 1;
										}
									}
									for (l = k; l < info.monster_num - 1; ++l) {
										monster[l] = monster[l + 1];
									}
									achievement(&map[0][0], &info, &achieve);
									del(&info.monster_num, &monster);
								}	// if

								if ((rectcrash(mon, rect) && map[i][j].kind == 2) && monster[k].mv_way == 0) {			// 오른쪽으로 이동할때
									monster[k].x = map[i][j].x - 64;
									monster[k].mv_way = 3;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 1) {								// 아래쪽으로 이동할때
									monster[k].y = map[i][j].y - 64;
									monster[k].mv_way = 0;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 2) {								// 왼쪽으로 이동할때
									monster[k].x = map[i][j].x + 64;
									monster[k].mv_way = 1;
								}	// if
								else if ((rectcrash(mon, rect)
									&& map[i][j].kind == 2) && monster[k].mv_way == 3) {								// 위쪽으로 이동할때
									monster[k].y = map[i][j].y + 64;
									monster[k].mv_way = 2;
								}	// if

									// 밖으로 나갈때
								if (monster[k].x + 64 >= 64 * 12 && monster[k].mv_way == 0) {							// 오른쪽으로 이동할때
									monster[k].x = 64 * 11;
									monster[k].mv_way = 3;
								}	// if
								else if (monster[k].y + 64 >= 64 * 12 && monster[k].mv_way == 1) {						// 아래쪽으로 이동할때
									monster[k].y = 64 * 11;
									monster[k].mv_way = 0;
								}	// if
								else if (monster[k].x <= 0 && monster[k].mv_way == 2) {								// 왼쪽으로 이동할때
									monster[k].x = 0;
									monster[k].mv_way = 1;
								}	// if
								else if (monster[k].y <= 0 && monster[k].mv_way == 3) {								// 위쪽으로 이동할때
									monster[k].y = 0;
									monster[k].mv_way = 2;
								}	// if
							}	// for j
						}	// for i
					}	// for k
					if (!(skill.type == 8 && skill.activate == true)) {
						bossmod(&monster, &map[0][0], &effect, &info.effect_num, &skill);
					}
				}

				// 라운드 끝
				if (mod.breaktime == 0 && info.count_mon >= 20 && info.monster_num <= 0 && mod.boss == 0) {
					info.money += 20;
					mod.breaktime = 1;
					timer.breaktime = 0;
					info.count_mon = 0;
					info.nextmonspd = rand() % 4 + 1;
				}

				// 보스전 끝
				if (mod.breaktime == 0 && info.monster_num <= 0 && mod.boss == 1) {
					info.money += 30;
					mod.breaktime = 1;
					timer.breaktime = 0;
					info.count_mon = 0;
					// BBBBBBB
					mod.boss = 0;
					info.nextmonspd = rand() % 4 + 1;
				}

				// 공격속도 타이머
				for (i = 0; i < 12; ++i) {
					for (j = 0; j < 12; ++j) {
						if (map[i][j].install && map[i][j].tower.atk_tmr < map[i][j].tower.speed_atk) {
							if (map[i][j].tower.atk_tmr == 0) {
								add(&info.effect_num, &effect);
								effect[info.effect_num - 1].kind = map[i][j].tower.kind;
								effect[info.effect_num - 1].frame = 0;
								effect[info.effect_num - 1].maxframe = map[i][j].tower.speed_atk;
								effect[info.effect_num - 1].target = map[i][j].tower.rank;
								effect[info.effect_num - 1].setframe = (float)((float)map[i][j].tower.speed_atk / (float)8);
								effect[info.effect_num - 1].rank = -1;
								effect[info.effect_num - 1].x = map[i][j].x;
								effect[info.effect_num - 1].y = map[i][j].y;
								effect[info.effect_num - 1].ur = false;
							}
							map[i][j].tower.atk_tmr++;
						}
					}
				}

				if ((mod.boss == true && monster[0].boss.skill == true&&monster[0].kind==3)) {
					shotdown += 768 / 50;
				}

				// 공격
				if (mod.boss == false || ((mod.boss == true && monster[0].boss.skill == false) || info.now_wave / 10 != 3)) {
					shotdown = 0;
					for (j = 0; j < 12; ++j) {
						for (k = 0; k < 12; ++k) {
							if (map[j][k].install) {
								distance = 0;
								for (i = 0; i < info.monster_num; ++i) {
									if (inrange(map[j][k].tower.range, map[j][k].x + info.tile_W / 2, map[j][k].y + info.tile_H / 2,
										monster[i].x + info.tile_W / 2, monster[i].y + info.tile_H / 2) && monster[i].distance > distance && monster[i].hp > 0) {
										distance = monster[i].distance;
										map[j][k].tower.target = i;
									}	// if
								}	// for
								if (distance == 0) {
									map[j][k].tower.target = -1;
								}
								subskill(&map[j][k].tower, &monster, &info.monster_num, &bullet, &info.bullet_num, &effect, &info.effect_num, &info);
							}	// if
						}	// for
					}	// for

					for (j = 0; j < 12; ++j) {
						for (k = 0; k < 12; ++k) {
							if (map[j][k].install) {
								if (map[j][k].tower.target < info.monster_num && map[j][k].tower.target != -1) {
									if (inrange(map[j][k].tower.range, map[j][k].x + info.tile_W / 2, map[j][k].y + info.tile_H / 2,
										monster[map[j][k].tower.target].x + info.tile_W / 2, monster[map[j][k].tower.target].y + info.tile_H / 2)
										&& map[j][k].tower.atk_tmr >= map[j][k].tower.speed_atk) {
										add(&info.bullet_num, &bullet);
										bullet[info.bullet_num - 1].x = map[j][k].x + info.tile_W / 2;
										bullet[info.bullet_num - 1].y = map[j][k].y + info.tile_H / 2;
										bullet[info.bullet_num - 1].target = map[j][k].tower.target;
										bullet[info.bullet_num - 1].speed = map[j][k].tower.bulspeed;
										bullet[info.bullet_num - 1].kind = map[j][k].tower.kind;
										bullet[info.bullet_num - 1].rank = map[j][k].tower.rank;
										bullet[info.bullet_num - 1].hit = false;
										bullet[info.bullet_num - 1].target_lose = false;
										bullet[info.bullet_num - 1].ur = false;
										bullet[info.bullet_num - 1].atk = map[j][k].tower.atk * info.upgrade[map[j][k].tower.group] * info.dia_upgrade;
										bullet[info.bullet_num - 1].frame = 0;
										bullet[info.bullet_num - 1].maxframe = map[j][k].tower.bulframe;
										switch (map[j][k].tower.kind) {
										case 0:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 30;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 10;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 63;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 21;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 75;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 25;
												break;
											}
											break;
										case 1:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 45;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 15;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 75;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 25;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 90;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 30;
												break;
											}
											break;
										case 2:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 30;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 10;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 75;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 25;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 8;
												break;
											}
											break;
										case 3:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 27;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 9;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 33;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 11;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 54;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 18;
												break;
											}
											break;
										case 4:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 27;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 9;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 78;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 26;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 63;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 21;
												break;
											}
											break;
										case 5:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 45;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 15;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 48;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 16;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 63;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 21;
												break;
											}
											break;
										case 6:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 20;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 4;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 57;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 19;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 69;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 23;
												break;
											}
											break;
										case 7:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 21;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 7;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 33;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 11;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 54;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 18;
												break;
											}
											break;
										case 8:
											switch (map[j][k].tower.rank) {
											case 0:
												bullet[info.bullet_num - 1].t_maxf = 24;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 6;
												break;
											case 1:
												bullet[info.bullet_num - 1].t_maxf = 45;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 15;
												break;
											case 2:
												bullet[info.bullet_num - 1].t_maxf = 42;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 14;
												break;
											case 3:
												bullet[info.bullet_num - 1].t_maxf = 75;
												bullet[info.bullet_num - 1].t_setf = bullet[info.bullet_num - 1].t_maxf / 25;
												break;
											}
											break;
										}
										if (bullet[info.bullet_num - 1].atk > 9999) {
											bullet[info.bullet_num - 1].atk = 9999;
										}
										map[j][k].tower.atk_tmr = 0;
									}	// if
								}	// if
							}	// if
						}	// for
					}	// for

					for (i = 0; i < info.bullet_num; ++i) {
						if (bullet[i].target_lose == false) {
							rad = LengthPts(bullet[i].x + info.object_W / 2, bullet[i].y + info.object_H / 2, monster[bullet[i].target].x + info.tile_W / 2, monster[bullet[i].target].y + info.tile_H / 2);
							bullet[i].mx = ((monster[bullet[i].target].x + info.tile_W / 2) - (bullet[i].x + info.object_W / 2)) / rad;
							bullet[i].my = ((monster[bullet[i].target].y + info.tile_H / 2) - (bullet[i].y + info.object_H / 2)) / rad;
							bullet[i].x += bullet[i].mx * bullet[i].speed;
							bullet[i].y += bullet[i].my * bullet[i].speed;
							bullet[i].target_x = monster[bullet[i].target].x;
							bullet[i].target_y = monster[bullet[i].target].y;
							bullet[i].frame++;
							bullet[i].frame %= bullet[i].maxframe;
						}
					}

					// 총알 충돌했을때 삭제
					for (i = 0; i < info.bullet_num; ++i) {
						if (bullet[i].target_lose == false) {
							bullet_damage(&bullet[i], &monster[bullet[i].target]);
							if (bullet[i].hit) {
								FMOD_Channel_Stop(Hit_sound_c);
								if (monster[bullet[i].target].boss.skill == false && monster[bullet[i].target].boss.boss && monster[bullet[i].target].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
									monster[bullet[i].target].boss.skillcool -= (float)bullet[i].atk / (float)120;
									if (monster[bullet[i].target].boss.skillcool < 0) {
										monster[bullet[i].target].boss.skillcool = 0;
									}
								}
								if (monster[bullet[i].target].boss.skill == false && monster[bullet[i].target].boss.boss && monster[bullet[i].target].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
									monster[bullet[i].target].boss.skillcool -= (float)bullet[i].atk / (float)200;
									if (monster[bullet[i].target].boss.skillcool < 0) {
										monster[bullet[i].target].boss.skillcool = 0;
									}
								}
								add(&info.effect_num, &effect);
								effect[info.effect_num - 1].kind = bullet[i].kind;
								effect[info.effect_num - 1].frame = 0;
								effect[info.effect_num - 1].target = bullet[i].target;
								effect[info.effect_num - 1].rank = bullet[i].rank;
								effect[info.effect_num - 1].maxframe = bullet[i].t_maxf;
								effect[info.effect_num - 1].setframe = bullet[i].t_setf;
								effect[info.effect_num - 1].x = monster[effect[info.effect_num - 1].target].x;
								effect[info.effect_num - 1].y = monster[effect[info.effect_num - 1].target].y;
								effect[info.effect_num - 1].ur = false;

								for (j = i; j < info.bullet_num - 1; ++j) {
									bullet[j] = bullet[j + 1];
								}
								del(&info.bullet_num, &bullet);
								FMOD_System_PlaySound(soundSystem, Hit_sound, NULL, false, &Hit_sound_c);
								FMOD_Channel_SetVolume(Hit_sound_c, 0.2);
							}
						}
					}
					// 공격시 이펙트
					for (i = 0; i < info.effect_num; ++i) {
						effect[i].frame++;
						if (effect[i].frame >= effect[i].maxframe) {
							for (j = i; j < info.effect_num - 1; ++j) {
								effect[j] = effect[j + 1];
							}
							del(&info.effect_num, &effect);
						}
					}
					// 총알이 타겟을 잃었을때 원래 타겟쪽으로 이동 후 삭제
					for (i = 0; i < info.bullet_num; ++i) {
						if (bullet[i].target_lose) {
							bul.left = bullet[i].x;
							bul.top = bullet[i].y;
							bul.right = (int)bullet[i].x + info.object_W / 2;
							bul.bottom = (int)bullet[i].y + info.object_H / 2;
							mob.left = bullet[i].target_x;
							mob.top = bullet[i].target_y;
							mob.right = (int)bullet[i].target_x + info.tile_W / 2;
							mob.bottom = (int)bullet[i].target_y + info.tile_H / 2;
							bullet[i].x += bullet[i].mx * bullet[i].speed;
							bullet[i].y += bullet[i].my * bullet[i].speed;
							bullet[i].frame++;
							bullet[i].frame %= bullet[i].maxframe;
							if (rectcrash(bul, mob)) {
								for (j = i; j < info.bullet_num - 1; ++j) {
									bullet[j] = bullet[j + 1];
								}
								del(&info.bullet_num, &bullet);
							}
						}
					}
				}
				//몬스터 hp 0이하일시 몬스터 삭제
				for (i = 0; i < info.monster_num; ++i) {
					if (monster[i].hp <= 0) {
						if (monster[i].death == 0) {
							add(&info.effect_num, &effect);
							effect[info.effect_num - 1].kind = 0;
							effect[info.effect_num - 1].frame = 0;
							effect[info.effect_num - 1].target = i;
							effect[info.effect_num - 1].rank = -2;
							effect[info.effect_num - 1].maxframe = 28;
							effect[info.effect_num - 1].setframe = effect[info.effect_num - 1].maxframe / 14;
							effect[info.effect_num - 1].x = monster[effect[info.effect_num - 1].target].x;
							effect[info.effect_num - 1].y = monster[effect[info.effect_num - 1].target].y;
							effect[info.effect_num - 1].ur = false;
							monster[i].death++;
						}
						else {
							monster[i].death++;
						}

						// 몹 죽었을때
						if (monster[i].death > 15) {
							// 킬 카운트
							info.kill_count += 1;		
							for (j = 0; j < info.bullet_num; ++j) {
								// 죽었으니 총알타겟 없앰
								if (bullet[j].target == i) {		
									bullet[j].target_lose = true;
								}
								// 총알을 배열로 만들어서 하는짓
								if (bullet[j].target > i) {			
									bullet[j].target -= 1;
								}
							}
							if (monster[i].mission) {
								if (monster[i].kind == 0) {
									info.money += 10;
								}
								else if (monster[i].kind == 1) {
									info.money += 20;
								}
								else if (monster[i].kind == 2) {
									info.money += 50;
								}
							}
							if (skill.degree < 360) {
								if (monster[i].boss.boss) {
									skill.degree += 180;
								}
								else {
									skill.degree += 12;
								}
							}
							if (skill.degree >= 360 && skill.type == 0) {
								// 스킬게이지 다 찼을때 소리
								FMOD_Channel_Stop(Effect_sound_c);
								FMOD_Sound_Release(Effect_sound);
								FMOD_System_CreateSound(soundSystem, "resource/sound/system/skill_slot_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
								FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);

								skill.degree = 360;
								if (skill.degree == 360 && skill.type == 0 && skill.activate == false) {
									// 스킬 결정
									skill.type = rand() % 9 + 1;
									//skill.type = 9;
									skill.skill_timer = 0;
									skill.kanan_timer = 0;
								}
							}
							for (j = i; j < info.monster_num - 1; ++j) {
								monster[j] = monster[j + 1];
							}
							FMOD_Channel_Stop(Boom_sound_c);
							FMOD_System_PlaySound(soundSystem, Boom_sound, NULL, false, &Boom_sound_c);
							FMOD_Channel_SetVolume(Boom_sound_c, 0.8);
							achievement(&map[0][0], &info, &achieve);
							del(&info.monster_num, &monster);
							// 게임클리어 체크
							if (info.now_wave == 40) {
								info.gameclear = true;
								mod.endgame = true;
								SetWindowPos(hWnd, HWND_TOP, 0, 0, width, 807, SWP_NOZORDER);
								//성공음 재생
								FMOD_Channel_Stop(BGM_c);
								FMOD_Sound_Release(BGM);
								switch (rand() % 9) {
								case 0:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_1.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 1:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_2.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 2:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_3.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 3:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_4.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 4:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_5.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 5:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_6.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 6:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_7.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 7:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_8.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								case 8:
									FMOD_System_CreateSound(soundSystem, "resource/sound/system/clear_9.mp3", FMOD_DEFAULT, 0, &BGM);
									break;
								}
								FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
								FMOD_Channel_SetVolume(BGM_c, 1.0);
							}
						}
					}
				}
			}
			// 스킬 사용시
			if (skill.activate&&skill.play_cutin == false) {
				switch (skill.type) {
				case 1:
					skill.draw_x += skill.delta_x / 50;
					skill.draw_y += skill.delta_y / 50;
					if (skill.draw_y > skill.y) {
						for (i = 0; i < info.monster_num; ++i) {
							skill_damage(skill, &monster[i], info.now_wave);
						}
						skill.activate = false;
						skill.type = 0;
						mod.skill = 0;
					}
					break;
				case 2:
					skill.skill_timer++;
					if (skill.skill_timer == 500) {
						skill.activate = false;
						skill.type = 0;
						skill.skill_timer = 0;
						mod.skill = 0;
					}
					break;
				case 3:
					for (i = 0; i < 500; ++i) {
						int t_x, t_y;
						t_x = rand() % 12;
						t_y = rand() % 12;
						if (map[t_y][t_x].install&&map[t_y][t_x].tower.rank < 3) {
							//합칠때 소리 재생
							FMOD_Sound_Release(Effect_sound);
							switch (map[t_y][t_x].tower.rank) {
							case 0:
								FMOD_System_CreateSound(soundSystem, "resource/sound/system/sr_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
								break;
							case 1:
								FMOD_System_CreateSound(soundSystem, "resource/sound/system/ssr_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
								break;
							case 2:
								FMOD_System_CreateSound(soundSystem, "resource/sound/system/ur_open.mp3", FMOD_DEFAULT, 0, &Effect_sound);
								break;
							}
							FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);

							map[t_y][t_x].tower.rank++;
							map[t_y][t_x].tower.kind = rand() % 9;
							skill.mari_upgrade = true;
							skill.tile_x = t_x;
							skill.tile_y = t_y;
							break;
						}
					}
					skill.activate = false;
					skill.type = 0;
					mod.skill = 0;
					break;
				case 4:
					// 리코스킬
					FMOD_Channel_Stop(BGM_c);
					FMOD_Sound_Release(BGM);
					if (play_lotto(1)) {
						FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_hidden.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
						if (achieve.Achive_List[10] == false) {
							achieve.Achive_List[10] = true;
						}
					}
					else {
						switch (rand() % 8) {
						case 0:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_1.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 1:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_2.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 2:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_3.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 3:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_4.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 4:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_5.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 5:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_6.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 6:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_7.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						case 7:
							FMOD_System_CreateSound(soundSystem, "resource/sound/bgm/bgm_8.mp3", FMOD_LOOP_NORMAL, 0, &BGM);
							break;
						}
					}
					FMOD_System_PlaySound(soundSystem, BGM, NULL, false, &BGM_c);
					FMOD_Channel_SetVolume(BGM_c, 0.3);
					FMOD_Sound_GetLength(BGM, sound_length, FMOD_TIMEUNIT_MS);
					start = clock();
					skill.activate = false;
					skill.type = 0;
					mod.skill = 0;
					break;
				case 5:
					skill.skill_timer++;
					if (skill.skill_timer % 100 == 0) {
						for (i = 0; i < info.monster_num; ++i) {
							skill_damage(skill, &monster[i], info.now_wave);
						}
					}
					if (skill.skill_timer == 500) {
						skill.activate = false;
						skill.type = 0;
						skill.skill_timer = 0;
						mod.skill = 0;
					}
					break;
				case 6:
					if (skill.skill_timer == 0) {
						info.dia_upgrade = 3.0;
					}
					skill.skill_timer++;
					if (skill.skill_timer == 500) {
						info.dia_upgrade = 1.0;
						skill.activate = false;
						skill.skill_timer = 0;
						mod.skill = 0;
						skill.type = 0;
					}
					break;
				case 7:
					skill.draw_y += 20;
					if (skill.draw_y - 128 > window_H) {
						for (i = 0; i < info.monster_num; ++i) {
							skill_damage(skill, &monster[i], info.now_wave);
						}
						skill.activate = false;
						skill.type = 0;
						mod.skill = 0;
					}
					break;
				case 8:
					skill.skill_timer++;
					if (skill.skill_timer == 100) {
						skill.activate = false;
						skill.type = 0;
						mod.skill = 0;
						skill.skill_timer = 0;
					}
					break;
				case 9:
					while (skill.kanan_timer < 64) {
						skill.kanan_timer++;
					}
					if (skill.skill_timer == 51) {
						skill.activate = false;
						skill.type = 0;
						mod.skill = 0;
						skill.skill_timer = 0;
						skill.kanan_timer = 0;
						for (i = 0; i < 10; ++i) {
							only_kanan[i].tile_x = -1;
							only_kanan[i].tile_y = -1;
						}
					}
					else {
						skill.skill_timer++;
					}
					if (skill.kanan_timer == 64) {
						if (mod.boss != 1) {
							for (k = 0; k < info.monster_num; ++k) {
								monster[k].hp -= 500 + (info.now_wave * 500);
								if (monster[k].hp < 0) {
									monster[k].hp = 0;
								}
							}
						}
						else {
							monster[0].hp -= monster[0].maxhp / 2;
							if (monster[0].hp < 0) {
								monster[0].hp = 0;
							}
						}
						skill.kanan_timer++;
					}
					break;
				default:
					skill.activate = false;
					skill.type = 0;
					mod.skill = 0;
					break;
				}
			}
			// 컷인 발동
			// 컷인이 발동되고 스킬이 작동됨
			if (skill.activate&&skill.play_cutin == true) {
				if (skill.alpha_up) {
					if (skill.alpha < 255) {
						skill.alpha += 5;
					}
					else if (skill.alpha == 255) {
						skill.cutin_timer++;
						if (skill.cutin_timer == 50) {
							skill.cutin_timer = 0;
							skill.alpha_up = false;
						}
					}
				}
				else {
					skill.alpha -= 10;
					if (skill.alpha < 0) {
						skill.alpha = 0;
						skill.alpha_up = true;
						skill.play_cutin = false;
					}
				}
			}
			if (skill.mari_upgrade) {
				timer.mari_tmr++;
			}
			// 마리 스킬 꺼주기
			if (timer.mari_tmr > 200) {
				skill.mari_upgrade = false;
				timer.mari_tmr = 0;
			}
		}
		// 업적 달성시 애니메이션
		for (i = 0; i < 12; ++i) {
			if (achieve.Achive_List[i] && achieve_ani.Achive_List[i] == false && mod.achive == false) {
				achieve_ani.now_view = i;
				mod.achive = true;
				achieve_ani.popup_mod = true;
				FMOD_Channel_Stop(Effect_sound_c);
				FMOD_Sound_Release(Effect_sound);
				FMOD_System_CreateSound(soundSystem, "resource/sound/system/achievement.mp3", FMOD_DEFAULT, 0, &Effect_sound);
				FMOD_System_PlaySound(soundSystem, Effect_sound, NULL, false, &Effect_sound_c);
			}
			if (mod.achive) {
				if (achieve_ani.popup_mod) {
					if (achieve_ani.achieve_alpha < 255) {
						achieve_ani.achieve_alpha += 1;
					}
				}
				else {
					achieve_ani.achieve_alpha -= 1;
				}
				achieve_ani.achieve_counter += 1;

				if (achieve_ani.achieve_alpha == 255 && achieve_ani.achieve_counter > 1600) {
					achieve_ani.popup_mod = false;
				}
				else if (achieve_ani.achieve_alpha == 0) {
					achieve_ani.popup_mod = true;
					achieve_ani.Achive_List[achieve_ani.now_view] = true;
					mod.achive = false;
					achieve_ani.achieve_counter = 0;
				}
			}
		}
		// 게임오버
		if (info.gameover&&info.gameover_alpha < 255) {
			info.gameover_alpha += 5;
		}
		else if (info.gameover&&info.gameover_alpha == 255) {
			mod.gamemode = false;
			mod.gameover = true;
			mod.endgame = false;
			info.gameover = false;
		}
		// 게임클리어
		if (info.gameclear&&info.gameclear_alpha < 255) {
			info.gameclear_alpha += 5;
		}
		else if (info.gameclear&&info.gameclear_alpha == 255) {
			mod.gamemode = false;
			mod.gameover = true;
			mod.endgame = false;
			info.gameclear = false;
		}
		
		break;
		}
		InvalidateRect(hWnd, NULL, FALSE);
		UpdateWindow(hWnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hWnd, IMsg, wParam, lParam);	// 위의 세 메시지 외의 나머지 메시지는 OS로
}


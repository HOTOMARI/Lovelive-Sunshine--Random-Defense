#include"stdafx.h"
#include "함수 헤더.h"
//---------------------------------------------------------------------------------------------------------------------------------------------------------//
//---------------------------------------------------------------------------------------------------------------------------------------------------------//
// 여기서부터 필요 함수 추가

void truecimage(CImage *cimage) {
	unsigned char * pCol = 0;
	long w = (*cimage).GetWidth();
	long h = (*cimage).GetHeight();
	for (long y = 0; y < h; y++)
	{
		for (long x = 0; x < w; x++)
		{
			pCol = (unsigned char *)(*cimage).GetPixelAddress(x, y);
			unsigned char alpha = pCol[3];
			if (alpha != 255)
			{
				pCol[0] = ((pCol[0] * alpha) + 128) >> 8;
				pCol[1] = ((pCol[1] * alpha) + 128) >> 8;
				pCol[2] = ((pCol[2] * alpha) + 128) >> 8;
			}
		}
	}
	(*cimage).SetHasAlphaChannel(true);
}

void add(int* monster_num, Monster** monster) {
	int newsize = *monster_num + 1; //size의 크기를 3 증가시킴

						  //main의 arr보다 길이가 3긴 배열 생성
	Monster* temp = (Monster*)malloc(sizeof(Monster)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *monster_num; i++)
		temp[i] = (*monster)[i];

	free(*monster); //이전 배열 삭제

	*monster = temp;
	*monster_num += 1; //main의 size를 3증가시킴
}

void del(int* monster_num, Monster** monster) {
	int newsize = *monster_num - 1; //size의 크기를 3 감소시킴

								   //main의 arr보다 길이가 3준 배열 생성
	Monster* temp = (Monster*)malloc(sizeof(Monster)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *monster_num - 1; i++)
		temp[i] = (*monster)[i];

	free(*monster); //이전 배열 삭제

	*monster = temp;
	*monster_num -= 1; //main의 size를 3감소시킴
}

void add(int* bullet_num, Bullet** bullet) {
	int newsize = *bullet_num + 1; //size의 크기를 3 증가시킴

									//main의 arr보다 길이가 3긴 배열 생성
	Bullet* temp = (Bullet*)malloc(sizeof(Bullet)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *bullet_num; i++)
		temp[i] = (*bullet)[i];

	free(*bullet); //이전 배열 삭제

	*bullet = temp;
	*bullet_num += 1; //main의 size를 3증가시킴
}

void del(int* bullet_num, Bullet** bullet) {
	int newsize = *bullet_num - 1; //size의 크기를 3 감소시킴

								   //main의 arr보다 길이가 3준 배열 생성
	Bullet* temp = (Bullet*)malloc(sizeof(Bullet)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *bullet_num - 1; i++)
		temp[i] = (*bullet)[i];

	free(*bullet); //이전 배열 삭제

	*bullet = temp;
	*bullet_num -= 1; //main의 size를 3감소시킴
}

void add(int* effect_num, Effect** effect) {
	int newsize = *effect_num + 1; //size의 크기를 3 감소시킴

								   //main의 arr보다 길이가 3준 배열 생성
	Effect* temp = (Effect*)malloc(sizeof(Effect)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *effect_num; i++)
		temp[i] = (*effect)[i];

	free(*effect); //이전 배열 삭제

	*effect = temp;
	*effect_num += 1; //main의 size를 3감소시킴
}

void del(int* effect_num, Effect** effect) {
	int newsize = *effect_num - 1; //size의 크기를 3 감소시킴

								   //main의 arr보다 길이가 3준 배열 생성
	Effect* temp = (Effect*)malloc(sizeof(Effect)*newsize);

	//ar의 값을 temp에 복사
	for (int i = 0; i < *effect_num - 1; i++)
		temp[i] = (*effect)[i];

	free(*effect); //이전 배열 삭제

	*effect = temp;
	*effect_num -= 1; //main의 size를 3감소시킴
}

bool rectcrash(RECT a, RECT b) {				// 사각형 충돌
	if (a.left < b.right && a.top < b.bottom && a.right > b.left && a.bottom > b.top) {
		return true;
	}
	return false;
}

bool inrange(int range, float tower_x, float tower_y, float monster_x, float monster_y) {		// 사정거리 안
	float l = sqrt((monster_x - tower_x) * (monster_x - tower_x) + (monster_y - tower_y) * (monster_y - tower_y));
	if (range >= l) {
		return true;
	}
	else {
		return false;
	}
}

bool mouse_in_box(int mx, int my, Button button) {
	if (mx > button.x&&mx < button.x + button.width&&my > button.y&&my < button.y + button.height)
		return true;
	else return false;
}

double get_radian(double degree) {
	return degree / 180 * 3.141592;
}

float LengthPts(float x1, float y1, float x2, float y2)			// 좌표와 좌표 사이의 거리 구하기
{
	return (sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1)));
}

void bullet_damage(Bullet* bullet, Monster* monster) {
	if ((monster->x - 8 < bullet->x + 8 && monster->x + 64 + 8 > bullet->x + 8) &&
		(monster->y - 8 < bullet->y + 8 && monster->y + 64 + 8 > bullet->y + 8)) {
		bullet->hit = true;
		monster->hp -= bullet->atk;
		if (monster->hp < 0) {
			monster->hp = 0;
		}
	}
	return;
}

void skill_damage(Skill skill, Monster* monster, int wave) {
	switch (skill.type) {
	case 5:
		if (skill.x - skill.range_x < monster->x + 32 && skill.y - skill.range_y < monster->y + 32
			&& skill.x + skill.range_x > monster->x - 32 && skill.y + skill.range_y > monster->y - 32) {
			monster->hp -= 200 + (wave * 150);
			if (monster->hp < 0) {
				monster->hp = 0;
			}
		}
		break;
	case 9:
		if (skill.tile_x * 64 < monster->x + 32 && skill.tile_y * 64 < monster->y + 32
			&& (skill.tile_x + 1) * 64 > monster->x - 32 && (skill.tile_y + 1) * 64 > monster->y - 32) {
			monster->hp -= 500 + (wave * 250);
			if (monster->hp < 0) {
				monster->hp = 0;
			}
		}
		break;
	default:
		if (skill.x - skill.range_x < monster->x + 32 && skill.y - skill.range_y < monster->y + 32
			&& skill.x + skill.range_x > monster->x - 32 && skill.y + skill.range_y > monster->y - 32) {
			monster->hp -= 1000 + (wave * 350);
			if (monster->hp < 0) {
				monster->hp = 0;
			}
		}
		break;
	}
}

bool upgrade(float* upgrade, int* money) {
	if (*money < 3)
		return false;
	*money -= 3;
	if (play_lotto(50)) {
		*upgrade += (float)0.05;
		return true;
	}
	else return false;
}

bool play_lotto(int num) {
	int lotto;
	lotto = rand() % 100;
	if (lotto < num)
		return true;
	else return false;
}


void bossmod(Monster** boss, Tile* map, Effect** effect, int* effect_num, Skill* skill) {	// 보스모드
	int rx, ry;
	Tile* tmp;
	tmp = map;
	switch ((*boss)->kind) {
	case 1:
		(*boss)->boss.skillcool += 1;
		if ((*boss)->hp > 0 && (*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
			if ((*boss)->mv_way == 0) {
				(*boss)->boss.act = 0;
				(*boss)->distance += (*boss)->speed;
				(*boss)->x += (*boss)->speed;
			}
			if ((*boss)->mv_way == 1) {
				(*boss)->distance += (*boss)->speed;
				(*boss)->y += (*boss)->speed;
			}
			if ((*boss)->mv_way == 2) {
				(*boss)->boss.act = 3;
				(*boss)->distance += (*boss)->speed;
				(*boss)->x -= (*boss)->speed;
			}
			if ((*boss)->mv_way == 3) {
				(*boss)->distance += (*boss)->speed;
				(*boss)->y -= (*boss)->speed;
			}
		}
		if ((*boss)->boss.skillcool > 500 && (*boss)->boss.skill == false) {
			int stack = 0;
			if ((*boss)->boss.act == 0 || (*boss)->boss.act == 3) {
				while (tmp->install == false) {
						(*boss)->boss.skilltaget = rand() % 143;
						tmp = map + (*boss)->boss.skilltaget;
						if (play_lotto(5) && tmp->kind == 1) {
							break;
						}
				}
			}
			if ((*boss)->boss.act == 0) {
				(*boss)->boss.act = 1;
				(*boss)->boss.skill = true;
				(*boss)->boss.skillcool = 0;
				add(effect_num, effect);
				(*effect)[*effect_num - 1].kind = 1;
				(*effect)[*effect_num - 1].frame = 0;
				(*effect)[*effect_num - 1].maxframe = 100;
				(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)30);
				(*effect)[*effect_num - 1].rank = -3;
				(*effect)[*effect_num - 1].x = tmp->x;
				(*effect)[*effect_num - 1].y = tmp->y;
			}
			if ((*boss)->boss.act == 3) {
				(*boss)->boss.act = 4;
				(*boss)->boss.skill = true;
				(*boss)->boss.skillcool = 0;
				add(effect_num, effect);
				(*effect)[*effect_num - 1].kind = 1;
				(*effect)[*effect_num - 1].frame = 0;
				(*effect)[*effect_num - 1].maxframe = 100;
				(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)30);
				(*effect)[*effect_num - 1].rank = -3;
				(*effect)[*effect_num - 1].x = tmp->x;
				(*effect)[*effect_num - 1].y = tmp->y;
			}
		}
		
		if ((*boss)->boss.skillcool > 100 && (*boss)->boss.skill) {
			tmp = map + (*boss)->boss.skilltaget;
			if (!(skill->activate&&skill->type == 2)) {
				tmp->install = false;
			}
			if ((*boss)->boss.act == 1) {
				(*boss)->boss.act = 0;
			}
			if ((*boss)->boss.act == 4) {
				(*boss)->boss.act = 3;
			}
			(*boss)->boss.skill = false;
			(*boss)->boss.skillcool = 0;
		}
		break;

	case 2:
		(*boss)->boss.skillcool += 1;
		if ((*boss)->hp > 0 && (*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
			if ((*boss)->mv_way == 0) {
				(*boss)->boss.act = 0;
				(*boss)->distance += (*boss)->speed;
				(*boss)->x += (*boss)->speed;
			}
			if ((*boss)->mv_way == 1) {
				(*boss)->distance += (*boss)->speed;
				(*boss)->y += (*boss)->speed;
			}
			if ((*boss)->mv_way == 2) {
				(*boss)->boss.act = 3;
				(*boss)->distance += (*boss)->speed;
				(*boss)->x -= (*boss)->speed;
			}
			if ((*boss)->mv_way == 3) {
				(*boss)->distance += (*boss)->speed;
				(*boss)->y -= (*boss)->speed;
			}
		}
		if ((*boss)->boss.skillcool > 500 && (*boss)->boss.skill == false) {
			int stack = 0;
			if ((*boss)->boss.act == 0 || (*boss)->boss.act == 3) {
				while (tmp->install == false) {
					(*boss)->boss.skilltaget = rand() % 143;
					tmp = map + (*boss)->boss.skilltaget;
					if (play_lotto(5) && tmp->kind == 1) {
						break;
					}
				}
			}
			if ((*boss)->boss.act == 0) {
				(*boss)->boss.act = 1;
				(*boss)->boss.skill = true;
				(*boss)->boss.skillcool = 0;
				for (int i = 0; i < 11; ++i) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (int)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x);
					(*effect)[*effect_num - 1].y = ((*boss)->y) - 64 - (i * 64);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (int)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x);
					(*effect)[*effect_num - 1].y = ((*boss)->y) + 64 + (i * 64);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x) - 64 - (i * 64);
					(*effect)[*effect_num - 1].y = ((*boss)->y);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x) + 64 + (i * 64);
					(*effect)[*effect_num - 1].y = ((*boss)->y);
				}
			}
			if ((*boss)->boss.act == 3) {
				(*boss)->boss.act = 4;
				(*boss)->boss.skill = true;
				(*boss)->boss.skillcool = 0;

				for (int i = 0; i < 11; ++i) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (int)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x);
					(*effect)[*effect_num - 1].y = ((*boss)->y) - 64 - (i * 64);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (int)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x);
					(*effect)[*effect_num - 1].y = ((*boss)->y) + 64 + (i * 64);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x) - 64 - (i * 64);
					(*effect)[*effect_num - 1].y = ((*boss)->y);
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = 2;
					(*effect)[*effect_num - 1].maxframe = 100;
					(*effect)[*effect_num - 1].setframe = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15);
					(*effect)[*effect_num - 1].frame = (float)((float)(*effect)[*effect_num - 1].maxframe / (float)15) * i * -1;
					(*effect)[*effect_num - 1].rank = -3;
					(*effect)[*effect_num - 1].x = ((*boss)->x) + 64 + (i * 64);
					(*effect)[*effect_num - 1].y = ((*boss)->y);
				}
			}
		}

		if ((*boss)->boss.skillcool > 100 && (*boss)->boss.skill) {
			tmp = map;
			RECT a = { 0, (*boss)->y, 768, (*boss)->y + 64 };
			RECT b = { (*boss)->x, 0, (*boss)->x + 64, 768 };
			for (int i = 0; i < 144; ++i) {
				tmp = map + i;
				RECT c = { tmp->x, tmp->y, tmp->x + 64, tmp->y + 64 };
				if (rectcrash(a, c)) {
					if (!(skill->activate&&skill->type == 2)) {
						tmp->install = false;
					}
				}
				if (rectcrash(b, c)) {
					if (!(skill->activate&&skill->type == 2)) {
						tmp->install = false;
					}
				}
			}
			if ((*boss)->boss.act == 1) {
				(*boss)->boss.act = 0;
			}
			if ((*boss)->boss.act == 4) {
				(*boss)->boss.act = 3;
			}
			(*boss)->boss.skill = false;
			(*boss)->boss.skillcool = 0;
		}
		break;

	case 3:
		(*boss)->boss.skillcool += 1;
		if ((*boss)->hp > 0) {
				if ((*boss)->mv_way == 0) {
					if ((*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
						(*boss)->boss.act = 0;
					}
					(*boss)->distance += (*boss)->speed;
					(*boss)->x += (*boss)->speed;
				}
				if ((*boss)->mv_way == 1) {
					(*boss)->distance += (*boss)->speed;
					(*boss)->y += (*boss)->speed;
				}
				if ((*boss)->mv_way == 2) {
					if ((*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
						(*boss)->boss.act = 3;
					}
					(*boss)->distance += (*boss)->speed;
					(*boss)->x -= (*boss)->speed;
				}
				if ((*boss)->mv_way == 3) {
					(*boss)->distance += (*boss)->speed;
					(*boss)->y -= (*boss)->speed;
				}
			}
		if ((*boss)->boss.skillcool > 500 && (*boss)->boss.skill == false) {
				int stack = 0;
				if ((*boss)->boss.act == 0) {
					(*boss)->boss.act = 1;
					(*boss)->boss.skill = true;
					(*boss)->boss.skillcool = 0;

				}
				if ((*boss)->boss.act == 3) {
					(*boss)->boss.act = 4;
					(*boss)->boss.skill = true;
					(*boss)->boss.skillcool = 0;
				}
			}

		if ((*boss)->boss.skillcool > 150 && (*boss)->boss.skill) {
				tmp = map + (*boss)->boss.skilltaget;
				if ((*boss)->boss.act == 1) {
					(*boss)->boss.act = 0;
				}
				if ((*boss)->boss.act == 4) {
					(*boss)->boss.act = 3;
				}
				(*boss)->boss.skill = false;
				(*boss)->boss.skillcool = 0;
			}
		break;

	case 4:
		(*boss)->boss.skillcool += 1;
		if ((*boss)->hp > 0 && (*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
				if ((*boss)->mv_way == 0) {
					if ((*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
						(*boss)->boss.act = 0;
					}
					(*boss)->distance += (*boss)->speed;
					(*boss)->x += (*boss)->speed;
				}
				if ((*boss)->mv_way == 1) {
					(*boss)->distance += (*boss)->speed;
					(*boss)->y += (*boss)->speed;
				}
				if ((*boss)->mv_way == 2) {
					if ((*boss)->boss.act != 1 && (*boss)->boss.act != 4) {
						(*boss)->boss.act = 3;
					}
					(*boss)->distance += (*boss)->speed;
					(*boss)->x -= (*boss)->speed;
				}
				if ((*boss)->mv_way == 3) {
					(*boss)->distance += (*boss)->speed;
					(*boss)->y -= (*boss)->speed;
				}
			}
		if ((*boss)->boss.skillcool > 500 && (*boss)->boss.skill == false) {
			if ((*boss)->boss.act == 0) {
					(*boss)->boss.act = 1;
					(*boss)->boss.skill = true;
					(*boss)->boss.skillcool = 0;
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y - (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 32), (*boss)->y - (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 32), (*boss)->y + (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 32), (*boss)->y + (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 32), (*boss)->y - (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y - (2 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y - (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (2 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y + (2 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (2 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y - (1 * 64), 0, (*effect_num), effect);
				}
			if ((*boss)->boss.act == 3) {
					(*boss)->boss.act = 4;
					(*boss)->boss.skill = true;
					(*boss)->boss.skillcool = 0;
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y - (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 32), (*boss)->y - (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 32), (*boss)->y + (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 32), (*boss)->y + (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 32), (*boss)->y - (1 * 32), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y - (2 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y - (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (2 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x + (1 * 64), (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x, (*boss)->y + (2 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y + (1 * 64), 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (2 * 64), (*boss)->y, 0, (*effect_num), effect);
					add(effect_num, effect);
					seteffect((*boss)->x - (1 * 64), (*boss)->y - (1 * 64), 0, (*effect_num), effect);
				}
		}

		if ((*boss)->boss.skillcool > 150 && (*boss)->boss.skill) {
				tmp = map;
				RECT a = { (*boss)->x, (*boss)->y - 128, (*boss)->x + 64, (*boss)->y + 196 };
				RECT b = { (*boss)->x - 64, (*boss)->y - 64, (*boss)->x + 128, (*boss)->y + 128};
				RECT d = { (*boss)->x - 128, (*boss)->y, (*boss)->x + 196, (*boss)->y + 64 };
				for (int i = 0; i < 144; ++i) {
					tmp = map + i;
					RECT c = { tmp->x, tmp->y, tmp->x + 64, tmp->y + 64 };
					if (rectcrash(a, c)) {
						if (!(skill->activate&&skill->type == 2)) {
							tmp->install = false;
						}
					}
					if (rectcrash(b, c)) {
						if (!(skill->activate&&skill->type == 2)) {
							tmp->install = false;
						}
					}
					if (rectcrash(d, c)) {
						if (!(skill->activate&&skill->type == 2)) {
							tmp->install = false;
						}
					}
				}
				if ((*boss)->boss.act == 1) {
					(*boss)->boss.act = 0;
				}
				if ((*boss)->boss.act == 4) {
					(*boss)->boss.act = 3;
				}
				(*boss)->boss.skill = false;
				(*boss)->boss.skillcool = 0;
			}
		break;
	}
}

void seteffect(int x, int y, int frame, int effect_num, Effect** effect) {
	(*effect)[effect_num - 1].kind = 4;
	(*effect)[effect_num - 1].maxframe = 100;
	(*effect)[effect_num - 1].setframe = (float)((float)(*effect)[effect_num - 1].maxframe / (float)15);
	(*effect)[effect_num - 1].frame = frame;
	(*effect)[effect_num - 1].rank = -3;
	(*effect)[effect_num - 1].x = x;
	(*effect)[effect_num - 1].y = y;
}

void towerset(Tower* tower) {
	switch (tower->rank) {
	case 0:
		tower->atk = 50;
		tower->speed_atk = 40;
		tower->range = 200;
		tower->bulspeed = 6;
		tower->bulframe = 1;
		break;
	case 1:
		switch (tower->kind) {
		case 0:
			tower->atk = 200;
			tower->speed_atk = 100;
			tower->range = 300;
			tower->bulspeed = 8;
			tower->bulframe = 28;
			break;
		case 1:
			tower->atk = 50;
			tower->speed_atk = 25;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 2:
			tower->atk = 30;
			tower->speed_atk = 10;
			tower->range = 128;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 3:
			tower->atk = 100;
			tower->speed_atk = 50;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 4:
			tower->atk = 66;
			tower->speed_atk = 36;
			tower->range = 250;
			tower->bulspeed = 7;
			tower->bulframe = 28;
			break;
		case 5:
			tower->atk = 110;
			tower->speed_atk = 50;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 6:
			tower->atk = 150;
			tower->speed_atk = 50;
			tower->range = 150;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 7:
			tower->atk = 60;
			tower->speed_atk = 35;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 8:
			tower->atk = 80;
			tower->speed_atk = 40;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		}
		break;
	case 2:
		switch (tower->kind) {
		case 0:
			tower->atk = 600;
			tower->speed_atk = 100;
			tower->range = 300;
			tower->bulspeed = 8;
			tower->bulframe = 28;
			break;
		case 1:
			tower->atk = 150;
			tower->speed_atk = 25;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 2:
			tower->atk = 80;
			tower->speed_atk = 8;
			tower->range = 150;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 3:
			tower->atk = 300;
			tower->speed_atk = 50;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 4:
			tower->atk = 166;
			tower->speed_atk = 36;
			tower->range = 266;
			tower->bulspeed = 7;
			tower->bulframe = 28;
			break;
		case 5:
			tower->atk = 330;
			tower->speed_atk = 45;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 6:
			tower->atk = 450;
			tower->speed_atk = 45;
			tower->range = 150;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 7:
			tower->atk = 200;
			tower->speed_atk = 35;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 8:
			tower->atk = 250;
			tower->speed_atk = 40;
			tower->range = 200;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		}
		break;
	case 3:
		switch (tower->kind) {
		case 0:
			tower->atk = 2000;
			tower->speed_atk = 120;
			tower->range = 400;
			tower->bulspeed = 8;
			tower->bulframe = 28;
			break;
		case 1:
			tower->atk = 400;
			tower->speed_atk = 20;
			tower->range = 250;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 2:
			tower->atk = 220;
			tower->speed_atk = 6;
			tower->range = 150;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 3:
			tower->atk = 900;
			tower->speed_atk = 40;
			tower->range = 240;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 4:
			tower->atk = 566;
			tower->speed_atk = 30;
			tower->range = 266;
			tower->bulspeed = 7;
			tower->bulframe = 28;
			break;
		case 5:
			tower->atk = 1000;
			tower->speed_atk = 45;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 6:
			tower->atk = 1200;
			tower->speed_atk = 30;
			tower->range = 150;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 7:
			tower->atk = 700;
			tower->speed_atk = 35;
			tower->range = 250;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		case 8:
			tower->atk = 850;
			tower->speed_atk = 40;
			tower->range = 225;
			tower->bulspeed = 6;
			tower->bulframe = 28;
			break;
		}
		break;
	}
	return;
}


void towercombine(Tower* tower) {
	tower->kind = rand() % 9;
	tower->rank = tower->rank + 1;
	tower->group = tower->kind / 3;
	towerset(tower);
}

void subskill(Tower* tower, Monster** monster, int* monster_num, Bullet** bullet, int* bullet_num, Effect** effect, int* effect_num, Info* info) {		// 추가함수
	int temp = NULL;
	if (tower->rank == 3) {
		switch (tower->kind) {
		case 0:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 1000) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(bullet_num, bullet);
					(*bullet)[*bullet_num - 1].x = tower->x;
					(*bullet)[*bullet_num - 1].y = tower->y;
					(*bullet)[*bullet_num - 1].target = tower->target;
					(*bullet)[*bullet_num - 1].speed = 10;
					(*bullet)[*bullet_num - 1].kind = tower->kind;
					(*bullet)[*bullet_num - 1].rank = tower->rank;
					(*bullet)[*bullet_num - 1].hit = false;
					(*bullet)[*bullet_num - 1].target_lose = false;
					(*bullet)[*bullet_num - 1].ur = true;
					(*bullet)[*bullet_num - 1].atk = 4000 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					(*bullet)[*bullet_num - 1].frame = 0;
					(*bullet)[*bullet_num - 1].maxframe = 1;
					(*bullet)[*bullet_num - 1].t_maxf = 75;
					(*bullet)[*bullet_num - 1].t_setf = (*bullet)[*bullet_num - 1].t_maxf / 3;
					tower->skillcool = 0;
				}
			}
			break;
		case 1:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 500) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 0;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 50;
					(*effect)[*effect_num - 1].setframe = 50 / 10;
					(*effect)[*effect_num - 1].x = tower->x + 32;
					(*effect)[*effect_num - 1].y = tower->y + 32;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 200 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		case 2:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 500) {
				if (tower->target < *monster_num && tower->target != -1) {
					if (tower->speed_atk != 3) {
						add(effect_num, effect);
						(*effect)[*effect_num - 1].kind = tower->kind;
						(*effect)[*effect_num - 1].frame = 0;
						(*effect)[*effect_num - 1].target = NULL;
						(*effect)[*effect_num - 1].rank = tower->rank;
						(*effect)[*effect_num - 1].maxframe = 100;
						(*effect)[*effect_num - 1].setframe = 100 / 92;
						(*effect)[*effect_num - 1].x = tower->x;
						(*effect)[*effect_num - 1].y = tower->y;
						(*effect)[*effect_num - 1].ur = true;
						tower->speed_atk = 3;
						tower->skillcool = 500;
					}
				}
			}
			if (tower->skillcool > 600 && tower->speed_atk == 3) {
				tower->speed_atk = 5;
				tower->skillcool = 0;
			}
			break;
		case 3:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 1100) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 0;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 110;
					(*effect)[*effect_num - 1].setframe = 110 / 22;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 32;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 3000 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		case 4:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 1050) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 0;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 150;
					(*effect)[*effect_num - 1].setframe = 150 / 30;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 32;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 10 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		case 5:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 900) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 27;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 180;
					(*effect)[*effect_num - 1].setframe = 180 / 27;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 32;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 200 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		case 6:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 1000) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 19;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 200;
					(*effect)[*effect_num - 1].setframe = 200 / 19;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 64;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 200 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		case 7:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->atk_tmr == 35 && tower->target < *monster_num && tower->target != -1) {
				if (play_lotto(25)) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 19;
					(*effect)[*effect_num - 1].target = tower->target;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 120;
					(*effect)[*effect_num - 1].setframe = 120 / 23;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 32;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 700 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					(*monster)[(*effect)[*effect_num - 1].target].hp -= (*effect)[*effect_num - 1].atk;
					if ((*monster)[(*effect)[*effect_num - 1].target].boss.skill == false && (*monster)[(*effect)[*effect_num - 1].target].boss.boss && (*monster)[(*effect)[*effect_num - 1].target].kind == 2) {		// 2번째 보스 때릴때마다 스킬쿨감소
						(*monster)[(*effect)[*effect_num - 1].target].boss.skillcool -= (float)(*effect)[*effect_num - 1].atk / (float)120;
						if ((*monster)[(*effect)[*effect_num - 1].target].boss.skillcool < 0) {
							(*monster)[(*effect)[*effect_num - 1].target].boss.skillcool = 0;
						}
					}
					if ((*monster)[(*effect)[*effect_num - 1].target].boss.skill == false && (*monster)[(*effect)[*effect_num - 1].target].boss.boss && (*monster)[(*effect)[*effect_num - 1].target].kind == 4) {		// 4번째 보스 때릴때마다 스킬쿨감소
						(*monster)[(*effect)[*effect_num - 1].target].boss.skillcool -= (float)(*effect)[*effect_num - 1].atk / (float)200;
						if ((*monster)[(*effect)[*effect_num - 1].target].boss.skillcool < 0) {
							(*monster)[(*effect)[*effect_num - 1].target].boss.skillcool = 0;
						}
					}
					if ((*monster)[(*effect)[*effect_num - 1].target].hp < 0) {
						(*monster)[(*effect)[*effect_num - 1].target].hp = 0;
					}
					tower->skillcool = 0;
				}
			}
			break;
		case 8:
			if (tower->ur_skillchk == false) {
				tower->ur_skillchk = true;
			}
			if (tower->ur_skillchk) {
				tower->skillcool++;
			}
			if (tower->skillcool > 1100) {
				if (tower->target < *monster_num && tower->target != -1) {
					add(effect_num, effect);
					(*effect)[*effect_num - 1].kind = tower->kind;
					(*effect)[*effect_num - 1].frame = 28;
					(*effect)[*effect_num - 1].target = NULL;
					(*effect)[*effect_num - 1].rank = tower->rank;
					(*effect)[*effect_num - 1].maxframe = 200;
					(*effect)[*effect_num - 1].setframe = 200 / 28;
					(*effect)[*effect_num - 1].x = (*monster)[tower->target].x + 32;
					(*effect)[*effect_num - 1].y = (*monster)[tower->target].y + 64;
					(*effect)[*effect_num - 1].ur = true;
					(*effect)[*effect_num - 1].atk = 250 * (*info).upgrade[tower->group] * (*info).dia_upgrade;
					tower->skillcool = 0;
				}
			}
			break;
		}
	}
}

// 업적 추가 부분
void achievement(Tile* map, Info* info, Achieve* achieve) {
	Tile* temp;
	temp = map;
	int i;
	int t;
	bool r[9] = { false, false, false, false, false, false, false, false, false };		// 레어모으기 확인
	bool sr[9] = { false, false, false, false, false, false, false, false, false };		// 슈레모으기 확인
	bool ssr[9] = { false, false, false, false, false, false, false, false, false };	// 쓔레모으기 확인
	bool ur[9] = { false, false, false, false, false, false, false, false, false };		// 울레모으기 확인
	for (i = 0; i < 144; ++i) {		// 노말 전부 다른거 하나씩 있을때
		temp = map + i;
		// 레어모으기 확인
		if (temp->install && temp->tower.rank == 0 && ((*achieve).Achive_List[0] == false || (*achieve).Achive_List[6] == false)) {
			switch (temp->tower.kind) {
			case 0:
				r[temp->tower.kind] = true;
				break;
			case 1:
				r[temp->tower.kind] = true;
				break;
			case 2:
				r[temp->tower.kind] = true;
				break;
			case 3:
				r[temp->tower.kind] = true;
				break;
			case 4:
				r[temp->tower.kind] = true;
				break;
			case 5:
				r[temp->tower.kind] = true;
				break;
			case 6:
				r[temp->tower.kind] = true;
				break;
			case 7:
				r[temp->tower.kind] = true;
				break;
			case 8:
				r[temp->tower.kind] = true;
				break;
			}
		}
		// 슈레모으기 확인
		else if (temp->install && temp->tower.rank == 1 && ((*achieve).Achive_List[1] == false || (*achieve).Achive_List[6] == false)) {
			switch (temp->tower.kind) {
			case 0:
				sr[temp->tower.kind] = true;
				break;
			case 1:
				sr[temp->tower.kind] = true;
				break;
			case 2:
				sr[temp->tower.kind] = true;
				break;
			case 3:
				sr[temp->tower.kind] = true;
				break;
			case 4:
				sr[temp->tower.kind] = true;
				break;
			case 5:
				sr[temp->tower.kind] = true;
				break;
			case 6:
				sr[temp->tower.kind] = true;
				break;
			case 7:
				sr[temp->tower.kind] = true;
				break;
			case 8:
				sr[temp->tower.kind] = true;
				break;
			}
		}
		// 쓔레모으기 확인
		else if (temp->install && temp->tower.rank == 2 && ((*achieve).Achive_List[2] == false || (*achieve).Achive_List[6] == false)) {
			switch (temp->tower.kind) {
			case 0:
				ssr[temp->tower.kind] = true;
				break;
			case 1:
				ssr[temp->tower.kind] = true;
				break;
			case 2:
				ssr[temp->tower.kind] = true;
				break;
			case 3:
				ssr[temp->tower.kind] = true;
				break;
			case 4:
				ssr[temp->tower.kind] = true;
				break;
			case 5:
				ssr[temp->tower.kind] = true;
				break;
			case 6:
				ssr[temp->tower.kind] = true;
				break;
			case 7:
				ssr[temp->tower.kind] = true;
				break;
			case 8:
				ssr[temp->tower.kind] = true;
				break;
			}
		}
		// 쓔레모으기 확인
		else if (temp->install && temp->tower.rank == 3 && ((*achieve).Achive_List[3] == false || (*achieve).Achive_List[6] == false)) {
			switch (temp->tower.kind) {
			case 0:
				ur[temp->tower.kind] = true;
				break;
			case 1:
				ur[temp->tower.kind] = true;
				break;
			case 2:
				ur[temp->tower.kind] = true;
				break;
			case 3:
				ur[temp->tower.kind] = true;
				break;
			case 4:
				ur[temp->tower.kind] = true;
				break;
			case 5:
				ur[temp->tower.kind] = true;
				break;
			case 6:
				ur[temp->tower.kind] = true;
				break;
			case 7:
				ur[temp->tower.kind] = true;
				break;
			case 8:
				ur[temp->tower.kind] = true;
				break;
			}
		}
	}
	// 일정킬 달성 업적
	if ((*info).kill_count == 100 && (*achieve).Achive_List[4] == false) {
		(*info).money += 20;
		(*achieve).Achive_List[4] = true;
	}

	if ((*info).kill_count == 500 && (*achieve).Achive_List[5] == false) {
		(*info).money += 20;
		(*achieve).Achive_List[5] = true;
	}

	// 레어모으기 업적 확인
	if (r[0] && r[1] && r[2] && r[3] && r[4] && r[5] && r[6] && r[7] && r[8] && (*achieve).Achive_List[0] == false) {
		(*info).money += 30;
		(*achieve).Achive_List[0] = true;
	}
	// 슈레모으기 업적 확인
	t = 0;
	for (i = 0; i < 9; ++i) {
		if (sr[i])
			t++;
	}
	if (t >= 7 && (*achieve).Achive_List[1] == false) {
		(*info).money += 30;
		(*achieve).Achive_List[1] = true;
	}
	// 쓔레모으기 업적 확인
	t = 0;
	for (i = 0; i < 9; ++i) {
		if (ssr[i])
			t++;
	}
	if (t >= 5 && (*achieve).Achive_List[2] == false) {
		(*info).money += 30;
		(*achieve).Achive_List[2] = true;
	}
	// 울레모으기 업적 확인
	t = 0;
	for (i = 0; i < 9; ++i) {
		if (ur[i])
			t++;
	}
	if (t >= 4 && (*achieve).Achive_List[3] == false) {
		(*info).nextrank = 2;
		(*achieve).Achive_List[3] = true;
	}
	// 4집센터마리
	t = 0;
	if (r[2] && sr[2] && ssr[2] && ur[2] && (*achieve).Achive_List[6] == false) {
		(*info).remain_life += 4;
		(*achieve).Achive_List[6] = true;
	}
	// 업그레이드 10강일때
	if ((*info).upgrade_stack[0] == 10 && (*achieve).Achive_List[7] == false) {
		(*info).money += 15;
		(*achieve).Achive_List[7] = true;
	}
	if ((*info).upgrade_stack[1] == 10 && (*achieve).Achive_List[8] == false) {
		(*info).money += 15;
		(*achieve).Achive_List[8] = true;
	}
	if ((*info).upgrade_stack[2] == 10 && (*achieve).Achive_List[9] == false) {
		(*info).money += 15;
		(*achieve).Achive_List[9] = true;
	}
	// 생명 4 남았을때
	if ((*info).remain_life == 4 && (*achieve).Achive_List[11] == false) {
		(*info).money += 40;
		(*achieve).Achive_List[11] = true;
	}
}
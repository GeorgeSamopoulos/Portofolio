ALLEGRO_BITMAP* npc_tileset;
class Sprite;
enum MOVE_TYPE { WALK, ACTIVE, PASSIVE };
enum move { UP, DOWN, LEFT, RIGHT, ATTACK };
Sprite* sprites[3][8];
int run_npc_Parser();
void scan_npc_tileset();
int player_walk = 0;
void display_player(int, int, Sprite*);
Sprite* load_sprite(bool, bool, bool, move*, move*, move);
void display_win_link(ALLEGRO_TIMER* , float , float , Sprite *);

class Sprite {
public:
	float dx, dy;

	Sprite(float x, float y) {
		this->dx = x;
		this->dy = y;
	}
};
int run_npc_Parser() {
	scan_npc_tileset();
	Map = createMap();
	return 1;

}

void scan_npc_tileset() {

	npc_tileset = al_load_bitmap("link-sprites.png");


}


void display_player(int x, int y, Sprite* sprite) {

	al_draw_bitmap_region(npc_tileset, sprite->dy, sprite->dx, 32, 32, x, y, 0);
	
}

void display_win_link(ALLEGRO_TIMER * clock , float x , float y , Sprite * sp) {
		sp->dy = 40 * 3;
		sp->dx = 40 * 2;
}

Sprite* load_sprite(bool jump_event, bool sit_flag, bool gravity_flag, move* posx, move* posy, move action) {
	Sprite* sp = new Sprite(0.0, 0.0);
	if (sit_flag) {

		if (action == ATTACK) {
			if (*posx == RIGHT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 7;
			}
			else if (*posx == LEFT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 0;
			}
			return sp;

		}

		if (action == LEFT || action == RIGHT) {
			*posx = action;
		}
		else if (action == UP || action == DOWN) {
			*posy = action;
		}

		if (action == RIGHT) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 6;
		}
		else if (action == LEFT) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 1;
		}
		return sp;
	}

	if (action == ATTACK) {
		if (*posx == RIGHT) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 5;
		}
		else if (*posx == LEFT) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 2;
		}
	}

	if (action == UP) {
		if (jump_event) {
			if (*posx == RIGHT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 6;
			}
			else if (*posx == LEFT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 1;
			}
		}
		else {
			if (*posx == RIGHT) {
				sp->dx = 40 * 0;
				sp->dy = 40 * 4;
			}
			else if (*posx == LEFT) {
				sp->dx = 40 * 0;
				sp->dy = 40 * 3;
			}
		}


	}

	if (action == DOWN) {
		if (gravity_flag == true && sit_flag == false) {
			if (*posx == RIGHT) {
				sp->dx = 40 * 0;
				sp->dy = 40 * 4;
			}
			else if (*posx == LEFT) {
				sp->dx = 40 * 0;
				sp->dy = 40 * 3;
			}
		}
		else {
			if (*posx == RIGHT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 6;
			}
			else if (*posx == LEFT) {
				sp->dx = 40 * 1;
				sp->dy = 40 * 1;
			}
		}
	}

	if (action == RIGHT) {
		if (jump_event || *posy == DOWN) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 6;
		}
		else if (gravity_flag || *posx == LEFT) {
			sp->dx = 40 * 0;
			sp->dy = 40 * 4;
		}
		else if (*posx == RIGHT) {
			player_walk = (player_walk + 1) % 4;
			sp->dx = 40 * 0;
			sp->dy = 40 * (4 + player_walk);
		}
	}

	if (action == LEFT) {
		if (jump_event || *posy == DOWN) {
			sp->dx = 40 * 1;
			sp->dy = 40 * 1;
		}
		else if (gravity_flag || *posx == RIGHT) {

			sp->dx = 40 * 0;
			sp->dy = 40 * 3;
		}
		else if (*posx == LEFT) {
			player_walk = (player_walk + 1) % 4;
			sp->dx = 40 * 0;
			sp->dy = 40 * (3 - player_walk);
		}
	}


	if (action != *posx) {
		player_walk = 0;
	}
	if (action == LEFT || action == RIGHT) {
		*posx = action;
	}
	else if (action == UP) {
		*posy = action;
	}

	return sp;
}
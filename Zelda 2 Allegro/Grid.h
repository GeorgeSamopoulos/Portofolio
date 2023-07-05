
class GridTile;
class Player;

std::vector<std::vector<GridTile>> GridMap;
int solid_tiles[100];
bool jump_event = false;
int jump_pixel = 0;
bool grav_flag = false;
bool elevator_flag = true;



bool testGridPlayer(Player*, move, int, int);
void init_solid_tiles();
void createGridMap(std::vector <std::vector <Tile>>);

class Player {
public:
	int points, life, extra_life, magic_point;
	int attack_damage;
	bool attack_enable;
	bool shield;
	double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4;
	double height, width;
	double posx1, posy1, posx2, posy2;
	bool enable_jump,sit_flag;
	move posx,posy;
	Sprite* sprite; 
	bool has_key, winFlag;
	bool in_collision;
	double in_collision_time;
	bool isDamaged;
	bool isDead;
	int jump_limit;
	double damage_filter;

	Player(double x, double y, double height, double width) {
		this->life = 100;
		this->magic_point = 0;
		this->extra_life = 0;
		this->points = 0;
		this->attack_damage = 1;
		this->attack_enable = true;
		this->shield = false;
		this->has_key = false;
		this->winFlag = false;
		this->enable_jump = true;
		this->height = height - 1;
		this->width = width - 1;
		this->dx1 = x;
		this->dy1 = y;
		this->dx2 = x + this->width;
		this->dy2 = y;
		this->dx3 = x;
		this->dy3 = y + this->height;
		this->dx4 = x + this->width;
		this->dy4 = y + this->height;
		this->in_collision = false;
		
		this->isDamaged = false;
		this->isDead = false;

		this->jump_limit = 32;

		this->posx1 = dx1;
		this->posy1 = dy1;
		this->posx2 = dx4;
		this->posy2 = dy4;

		this->sit_flag = false;
		this->sprite = NULL;
		this->posx = RIGHT;
		this->posy = UP;

		this->damage_filter = 1.0;
	}
	void start_player() {
		move_camera(0, 0);
		sprite = new Sprite(0.0, 40*4);
		display_player(dx1, dy1, this->sprite);

	}
	void move_player(double x, double y, move m) {
		move action = m;

		if (sit_flag) {
			action = m;
			move_camera(0, 0);
			this->sprite = load_sprite(jump_event, sit_flag, grav_flag, &posx, &posy, action);
			display_player(posx1, posy1, this->sprite);
			return;
		}

		if (dx1 + x < 0) {
			return;
		}

		if (dy1 + y < 0) {
			return;
		}

		if (m == LEFT) {
			dx1 += x;
			dx2 += x;
			dx3 += x;
			dx4 += x;

			if (dx1 - LeftBorder[currm] < 320) {
				posx1 = (int)dx1 - LeftBorder[currm];
				posx2 = (int)dx4 - LeftBorder[currm];
				move_camera(0, 0);
			}
			else {

				if (posx1 > 320) {
					posx1 += x;
					posx2 += x;
					move_camera(0, 0);
				}
				else {
					posx1 = 320;
					posx2 = 320 + width;
					move_camera(x, y);
				}
			}

			action = LEFT;


		}
		else if (m == RIGHT) {
			dx1 += x;
			dx2 += x;
			dx3 += x;
			dx4 += x;

			if (dx1 - LeftBorder[currm] <= 320) {
				posx1 = (int)dx1 - LeftBorder[currm];
				posx2 = (int)dx4 - LeftBorder[currm];
				move_camera(0, 0);
			}
			else {
				if (!move_camera(x, y)) {
					posx1 += x;
					posx2 += x;
				}
				else {
					posx1 = 320;
					posx2 = 320 + width;
				}
			}

			action = RIGHT;


		}
		else if (m == UP) {

			dy1 += y;
			dy2 += y;
			dy3 += y;
			dy4 += y;

			if (dy1 < 240) {
				posy1 = dy1;
				posy2 = dy4;
			}
			else {
				posy1 += y;
				posy2 += y;
			}
			move_camera(0, 0);

			action = UP;
		}
		else if (m == DOWN) {
			dy1 += y;
			dy2 += y;
			dy3 += y;
			dy4 += y;

			if (dy1 <= 240) {
				posy1 = dy1;
				posy2 = dy4;
			}
			else {
				posy1 += y;
				posy2 += y;
			}
			move_camera(0, 0);

			action = DOWN;
		}


		//std::cout << "x1 = " << dx1 << " y1 = " << dy1 << " x4 = " << dx4 << " y4 = " << dy4 << std::endl;
		this->sprite = load_sprite(jump_event, sit_flag, grav_flag, &posx, &posy, action);
		//display_player(posx1, posy1, this->sprite);

	}

	bool check_gravity() {
		bool f = false;
		if (testGridPlayer(this, DOWN, 0, 2)) {
			move_player(0, 2, DOWN);
			f = true;
		}
		else if (testGridPlayer(this, DOWN, 0, 1)) {
			move_player(0, 1, DOWN);
			f = true;
		}
		else {
			enable_jump = true;
		}
		return f;
	}

	void jump() {

		int i = 0;

		if (jump_pixel > this->jump_limit || !testGridPlayer(this, UP, -4, 0)) {
			jump_event = false;
			jump_pixel = 0;
			return;
		}
		jump_pixel += 4;
		move_player(0, -4, UP);

		display_player(posx1, posy1, this->sprite);
	}

	void sit_down() {
		shield = true;
		move_player(0, 0, DOWN);
	}

	bool check_elevator() {

		if (!elevator_flag) {
			return false;
		}
		int i, j;

		j = dy3 / 16;
		i = dx3 / 16;
		Tile test2 = Map[j + 1][i];

		if (test2.number == 12) {
			currm = 1;
			elevator_flag = false;
			//std::cout << "elevator" << std::endl;

			cam_position[0] = 1522;
			cam_position[1] = 0;
			dx1 = 1522 + 320;
			dx2 = dx1 + width;
			dx3 = dx1;
			dx4 = dx3 + width;

			posx1 = 320;
			posx2 = 320 + width;
			posy1 = 400;
			posy2 = 400 + height;

			dy1 = posy1;
			dy2 = posy1;
			dy3 = posy2;
			dy4 = posy2;

			al_draw_bitmap_region(map_bitmap, cam_position[0], cam_position[1], 640, 480, 0, 0, 0);

			/*if (oldSprite != NULL)
				display_player(posx1, posy1, this->sprite);*/
			return true;
		}
		return false;
	}

	void check_door() {
		int tempx2 = this->dx2 /16;
		if ((Map[dy2/16][tempx2].number==23 || Map[dy2/16][tempx2].number == 33 || Map[dy2/16][tempx2].number == 43)  && this->has_key) {
			change_door_display(tempx2,dy2/16,dx2,dy2);
			solid_tiles[23] = 0;
			solid_tiles[33] = 0;
			solid_tiles[43] = 0;

		}
	}

	bool check_finish() {
		bool isFinished = false;
		
		if (this->life <= 0) {
			isFinished = true;
		}else if(Map[(int)dy2 / 16][(int)dx2 / 16].number == 52) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 53) {
			isFinished = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 62) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 63) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 72) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 73) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 81) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 82) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 83) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 84) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 91) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 92) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 93) {
			isFinished = true;
			this->winFlag = true;
		}
		else if (Map[(int)dy2 / 16][(int)dx2 / 16].number == 94) {
			isFinished = true;
			this->winFlag = true;
		}
		if (this->isDead) {
			isFinished = true;
		}
		return isFinished;
	}

	bool attack() {
		move_camera(0, 0);
		this->sprite = load_sprite(jump_event, sit_flag, grav_flag, &posx, &posy, ATTACK);
		display_player(posx1, posy1, this->sprite);
		return true;
	}
	Sprite* oldSprite = NULL;
	void get_attack(int damage, move from) {
		check_life(damage*this->damage_filter);
		if (posx == RIGHT) {
			if (from == RIGHT) {
				move_player(20, 0, RIGHT);
			}
			if (from == LEFT) {
				move_player(-20, 0, LEFT);
			}
			posx = RIGHT;
			oldSprite = new Sprite(this->sprite->dx, this->sprite->dy);
			this->sprite->dy = 40 * 6;
			this->sprite->dx = 40 * 9;

		}
		if (posx==LEFT) {
			if (from == RIGHT) {
				move_player(20, 0, RIGHT);
			}
			if (from == LEFT) {
				move_player(-20, 0, LEFT);
			}
			posx = LEFT;
			oldSprite = new Sprite(this->sprite->dx, this->sprite->dy);
			this->sprite->dy = 40 * 1;
			this->sprite->dx = 40 * 9;
		}

		
		this->isDamaged = true;
	}


	void get_off_damage() {
		this->sprite->dx = oldSprite->dx;
		this->sprite->dy = oldSprite->dy;
		this->isDamaged = false;
	}

	void check_life(int damage) {
		life -= damage;
		if (life <= 0) {
			if (extra_life>0) {
				life = 100;
				extra_life--;
			}
			else {
				isDead = true;
			}
		}

	}
	
};

class GridTile {

public:
	int solid;
	int number;
	int x, y;

	GridTile(int solid, int x, int y, int number) {
		this->x = x;
		this->y = y;
		this->solid = solid;
		this->number = number;
	};
};

void createGridMap(std::vector <std::vector <Tile>> map) {
	init_solid_tiles();
	int i, j;
	for (i = 0; i < map.size(); i++) {
		std::vector <GridTile> new_vec;
		GridMap.push_back(new_vec);
		for (j = 0; j < map[i].size(); j++) {
			int s = 0;
			s = solid_tiles[map[i][j].number];
			GridMap[i].push_back(GridTile(s, j, i, map[i][j].number));
		}
	}
}


bool testGridPlayer(Player* p, move m, int x, int y) {
	int tempx1 = p->dx1 + x + 6;
	int tempx2 = p->dx2 + x - 6;
	int tempx3 = p->dx3 + x + 6;
	int tempx4 = p->dx4 + x - 6;

	int tempy1 = p->dy1 + y;
	int tempy2 = p->dy2 + y;
	int tempy3 = p->dy3 + y;
	int tempy4 = p->dy4 + y;

	int i, j, mj, mi;
	Tile test1, test2, test3;
	if (m == UP) {
		j = tempy1 / 16;
		i = tempx1 / 16;
		test1 = Map[j][i];


		j = tempy2 / 16;
		i = tempx2 / 16;
		test2 = Map[j][i];

	}
	else if (m == LEFT) {
		j = tempy1 / 16;
		i = tempx1 / 16;
		test1 = Map[j][i];

		mj = ((tempy1 + tempy3) / 2) / 16;
		test3 = Map[mj][i];
		if (solid_tiles[test3.number]) {
			return false;
		}

		j = tempy3 / 16;
		i = tempx3 / 16;
		test2 = Map[j][i];

	}
	else if (m == DOWN) {
		j = tempy3 / 16;
		i = tempx3 / 16;
		test1 = Map[j][i];

		j = tempy4 / 16;
		i = tempx4 / 16;
		test2 = Map[j][i];

	}
	else if (m == RIGHT) {
		j = tempy2 / 16;
		i = tempx2 / 16;
		test1 = Map[j][i];

		mj = ((tempy4 + tempy2) / 2) / 16;
		test3 = Map[mj][i];
		if (solid_tiles[test3.number]) {
			return false;
		}

		j = tempy4 / 16;
		i = tempx4 / 16;
		test2 = Map[j][i];

	}
	if (solid_tiles[test1.number] || solid_tiles[test2.number]) {

		return false;
	}
	return true;
}


void init_solid_tiles() {
	int i, j;

	for (i = 0; i < 100; i++) {
		solid_tiles[i] = 0;
	}
	solid_tiles[12] = 1;
	solid_tiles[13] = 1;
	solid_tiles[14] = 1;
	solid_tiles[19] = 1;
	solid_tiles[24] = 1;
	solid_tiles[25] = 1;
	solid_tiles[26] = 1;
	solid_tiles[27] = 1;
	solid_tiles[28] = 1;
	solid_tiles[29] = 1;
	solid_tiles[31] = 1;
	solid_tiles[33] = 1;
	solid_tiles[35] = 1;
	solid_tiles[36] = 1;
	solid_tiles[37] = 1;
	solid_tiles[38] = 1;
	solid_tiles[39] = 1;
	solid_tiles[40] = 1;
	solid_tiles[41] = 1;
	solid_tiles[43] = 1;
	solid_tiles[44] = 1;
	solid_tiles[45] = 1;
	solid_tiles[47] = 1;
	solid_tiles[48] = 1;
	solid_tiles[52] = 1;
	solid_tiles[53] = 1;
	solid_tiles[62] = 1;
	solid_tiles[63] = 1;
	solid_tiles[72] = 1;
	solid_tiles[73] = 1;
	solid_tiles[81] = 1;
	solid_tiles[82] = 1;
	solid_tiles[83] = 1;
	solid_tiles[84] = 1;
	solid_tiles[91] = 1;
	solid_tiles[92] = 1;
	solid_tiles[93] = 1;
	solid_tiles[94] = 1;
}
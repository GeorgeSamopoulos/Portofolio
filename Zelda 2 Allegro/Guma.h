ALLEGRO_BITMAP* guma_tileset;
class Guma;
int run_guma_Parser();
void scan_guma_tileset();

class Guma {
public:
	int hp = 16;
	int power = 24;
	move posx = RIGHT;

	double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4, weapon_dx1, weapon_dy1, weapon_dx2, weapon_dy2, weapon_dx3, weapon_dy3, weapon_dx4, weapon_dy4;
	double height, width, weapon_height, weapon_width;
	int spritenum, weapon_spritenum;
	int steps;
	bool weapon_thrown;
	bool isDead = false;

	Guma(double x, double y, double height, double width) {
		this->height = height;
		this->width = width;
		this->dx1 = x;
		this->dy1 = y;
		this->dx2 = x + this->width;
		this->dy2 = y;
		this->dx3 = x;
		this->dy3 = y + this->height;
		this->dx4 = x + this->width;
		this->dy4 = y + this->height;
		this->spritenum = 5;
		this->steps = 0;

		this->weapon_height = 16;
		this->weapon_width = 16;
		this->weapon_dx1 = x;
		this->weapon_dy1 = y;
		this->weapon_dx2 = x + this->weapon_width;
		this->weapon_dy2 = y;
		this->weapon_dx3 = x;
		this->weapon_dy3 = y + this->weapon_height;
		this->weapon_dx4 = x + this->weapon_width;
		this->weapon_dy4 = y + this->weapon_height;
		this->weapon_thrown = false;
		this->weapon_spritenum = 3;
	}

	void move() {
		if (this->steps < 32) {
			if (this->steps%16 > 8) {
				throw_weapon_right();
			}
			else {
				unthrow_weapon();
				move_right();
			}
		}
		else {
			if (this->steps % 16 > 8) {
				throw_weapon_left();
			}
			else {
				unthrow_weapon();
				move_left();
			}
		}
		this->steps++;
		this->steps = this->steps % 64;
	}

	void move_right() {
		posx = RIGHT;
		this->dx1 += 4;
		this->dx2 += 4;
		this->dx3 += 4;
		this->dx4 += 4;
		if (this->spritenum == 5) {
			this->spritenum = 4;
		}
		else if (this->spritenum == 4) {
			this->spritenum = 3;
		}
		else if (this->spritenum == 3) {
			this->spritenum = 2;
		}
		else {
			this->spritenum = 5;
		}
	}

	void move_left() {
		posx = LEFT;
		this->dx1 -= 4;
		this->dx2 -= 4;
		this->dx3 -= 4;
		this->dx4 -= 4;
		if (this->spritenum == 6) {
			this->spritenum = 7;
		}
		else if (this->spritenum == 7) {
			this->spritenum = 8;
		}
		else if (this->spritenum == 8) {
			this->spritenum = 9;
		}
		else {
			this->spritenum = 6;
		}
	}

	void throw_weapon_left() {
		weapon_thrown = true;
		this->weapon_dx1 -= 16;
		this->weapon_dx2 -= 16;
		this->weapon_dx3 -= 16;
		this->weapon_dx4 -= 16;
		if (this->weapon_spritenum == 3) {
			this->weapon_spritenum = 2;
		}
		else if (this->weapon_spritenum == 2) {
			this->weapon_spritenum = 1;
		}
		else if (this->weapon_spritenum == 1) {
			this->weapon_spritenum = 0;
		}
		else {
			this->weapon_spritenum = 3;
		}
	}

	void throw_weapon_right() {
		weapon_thrown = true;
		this->weapon_dx1 += 16;
		this->weapon_dx2 += 16;
		this->weapon_dx3 += 16;
		this->weapon_dx4 += 16;
		if (this->weapon_spritenum == 0) {
			this->weapon_spritenum = 1;
		}
		else if (this->weapon_spritenum == 1) {
			this->weapon_spritenum = 2;
		}
		else if (this->weapon_spritenum == 2) {
			this->weapon_spritenum = 3;
		}
		else {
			this->weapon_spritenum = 0;
		}
	}

	void unthrow_weapon() {
		weapon_thrown = false;
		this->weapon_dx1 = this->dx1;
		this->weapon_dx2 = this->dx2;
		this->weapon_dx3 = this->dx3;
		this->weapon_dx4 = this->dx4;
	}

	void display_guma(int x, int y, int spritenum) {
		if (!this->isDead)
			al_draw_bitmap_region(guma_tileset, spritenum * 32, 0, 32, 32, x, y, ALLEGRO_FLIP_HORIZONTAL);
		
	}

	void display_weapon(int x, int y, int spritenum) {
		if(!this->isDead)
			al_draw_bitmap_region(guma_tileset, spritenum * 16, 8, 16, 16, x, y, ALLEGRO_FLIP_HORIZONTAL);
		
	}

	void start_guma() {
		spritenum=9;
		display_guma(dx1, dy1, this->spritenum);
	}

	bool check_guma_collision(Player* p) {
		int temp_dx1 = p->dx1 + 8;
		int temp_dx2 = p->dx2 - 8;
		if (((temp_dx1 <= weapon_dx1 && weapon_dx1 <= temp_dx2)
			|| (temp_dx1 <= weapon_dx2 && weapon_dx2 <= temp_dx2))
			&& (p->dy1 <= weapon_dy1 && weapon_dy1 <= p->dy3)) {
			/*std::cout << "Collision with Guma weapon" << std::endl;
			std::cout << temp_dx1 << ", " << dx1 << std::endl;
			std::cout << temp_dx2 << ", " << dx2 << std::endl;*/
			return true;
		}
		return false;
	}


	bool check_guma_weapon_collision(Player * p) {
		int temp_dx1 = p->dx1 + 8;
		int temp_dx2 = p->dx2 - 8;
		if (((temp_dx1 <= dx1 && dx1 <= temp_dx2)
			|| (temp_dx1 <= dx2 && dx2 <= temp_dx2))
			&& (p->dy1 <= dy1 && dy1 <= p->dy3)) {
			/*std::cout << "Collision with Guma weapon" << std::endl;
			std::cout << temp_dx1 << ", " << dx1 << std::endl;
			std::cout << temp_dx2 << ", " << dx2 << std::endl;*/
			return true;
		}
		return false;

	}
};



int run_guma_Parser() {
	scan_guma_tileset();
	Map = createMap();
	return 1;

}

void scan_guma_tileset() {
	std::vector <Tile> tileset_obj;
	guma_tileset = al_load_bitmap("Guma.png");
	al_convert_mask_to_alpha(guma_tileset, al_map_rgb(82, 163, 163));
}

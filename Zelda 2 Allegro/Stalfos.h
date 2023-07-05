ALLEGRO_BITMAP* stalfos_tileset;
class Stalfos;
int run_stalfos_Parser();
void scan_stalfos_tileset();
enum attack {ON , OFF};

class Stalfos {
	public:
		int hp = 8;
		int power = 16;
		move posx = RIGHT;
		attack mode = OFF;

		double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4;
		double height, width;
		int spritenum;
		int steps;
		bool falling;
		bool has_fallen;
		bool isDead = false;
		
		Stalfos(double x, double y, double height, double width) {
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
			this->spritenum = 0;
			this->steps = 0;
			this->falling = false;
			this->has_fallen = false;
		}

		void move() {
			if (this->steps < 16 || (this->steps >= 48 && this->steps < 64)) {
				if (this->steps % 16 > 8) {
					fight_right();
				}
				else {
					move_right();
				}
			}
			else {
				if (this->steps % 16 > 8) {
					fight_left();
				}
				else {
					move_left();
				}
			}
			this->steps++;
			this->steps = this->steps % 64;
		}

		void move_right() {
			mode = OFF;
			posx = RIGHT;
			this->dx1 += 4;
			this->dx2 += 4;
			this->dx3 += 4;
			this->dx4 += 4;
			if (this->spritenum == 7) {
				this->spritenum = 6;
			}
			else if (this->spritenum == 6) {
				this->spritenum = 5;
			}
			else if (this->spritenum == 5) {
				this->spritenum = 4;
			}
			else {
				this->spritenum = 7;
			}
		}

		void move_left() {
			mode = OFF;
			posx = LEFT;
			this->dx1 -= 4;
			this->dx2 -= 4;
			this->dx3 -= 4;
			this->dx4 -= 4;
			if (this->spritenum == 8) {
				this->spritenum = 9;
			}
			else if (this->spritenum == 9) {
				this->spritenum = 10;
			}
			else if (this->spritenum == 10) {
				this->spritenum = 11;
			}
			else {
				this->spritenum = 8;
			}

		}

		void fight_left() {
			mode = ON;
			this->spritenum = 12;
		}

		void fight_right() {
			mode = ON;
			this->spritenum = 3;
		}

		void fall() {
			this->dy1 += 4;
			this->dy2 += 4;
			this->dy3 += 4;
			this->dy4 += 4;
			if (this->dy1==448.0-64.0) {
				this->falling = false;
				this->has_fallen = true;
			}
			else {
				falling = true;
			}
		}

		void display_stalfos(int x, int y, int spritenum) {
			if (!this->isDead)
				al_draw_bitmap_region(stalfos_tileset, spritenum * 16, 0,16, 32, x, y, ALLEGRO_FLIP_HORIZONTAL);
			//al_flip_display();
		}

		void start_stalfos() {
			spritenum = 0;
			display_stalfos(dx1, dy1, this->spritenum);
		}

		bool check_stalfos_collision(Player* p) {
			int temp_dx1 = p->dx1 + 8;
			int temp_dx2 = p->dx2 - 8;
			if (((temp_dx1 <= dx1 && dx1 <= temp_dx2)
				|| (temp_dx1 <= dx2 && dx2 <= temp_dx2))
				&& (p->dy1 <= dy1 && dy1 <= p->dy3)) {
				/*std::cout << "Collision with Stalfos" << std::endl;
				std::cout << temp_dx1 << ", " << dx1 << std::endl;
				std::cout << temp_dx2 << ", " << dx2 << std::endl;*/
				return true;
			}
			return false;
		}

};
int run_stalfos_Parser() {
	scan_stalfos_tileset();
	Map = createMap();
	return 1;

}

void scan_stalfos_tileset() {

	std::vector <Tile> tileset_obj;
	stalfos_tileset = al_load_bitmap("Stalfos.png");
	al_convert_mask_to_alpha(stalfos_tileset, al_map_rgb(82, 163, 163));

}



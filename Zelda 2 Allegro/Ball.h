ALLEGRO_BITMAP* ball_tileset;
class Ball;
int run_ball_Parser();
void scan_ball_tileset();

class Ball {
	public:
		int hp = 4;
		int power = 10;
		move posx = RIGHT;
		double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4;
		double height, width;
		int spritenum;
		int steps;
		bool isDead = false;

		Ball(double x, double y, double height, double width) {
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
		}

		void move() {
			if (this->steps < 32) {
				move_right();
			}
			else {
				move_left();
			}
			if (this->steps%4 == 0 || this->steps % 4 == 1) {
				move_up();
			}
			else {
				move_down();
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
			if (this->spritenum == 0) {
				this->spritenum = 1;
			}
			else {
				this->spritenum = 0;
			}
		}

		void move_left() {
			posx = LEFT;
			this->dx1 -= 4;
			this->dx2 -= 4;
			this->dx3 -= 4;
			this->dx4 -= 4;
			if (this->spritenum == 0) {
				this->spritenum = 1;
			}
			else {
				this->spritenum = 0;
			}
		}

		void move_up() {
			this->dy1 -= 8;
			this->dy2 -= 8;
			this->dy3 -= 8;
			this->dy4 -= 8;
		}

		void move_down() {
			this->dy1 += 8;
			this->dy2 += 8;
			this->dy3 += 8;
			this->dy4 += 8;
		}

		void display_ball(int x, int y, int spritenum) {
			if (!this->isDead)
				al_draw_bitmap_region(ball_tileset, spritenum*16, 0, 16, 16, x, y, ALLEGRO_FLIP_HORIZONTAL);
			//al_flip_display();
		}

		void start_ball() {
			spritenum =0;
			display_ball(dx1, dy1, this->spritenum);
		}

		bool check_ball_collision(Player* p) {
			int temp_dx1 = p->dx1 + 8;
			int temp_dx2 = p->dx2 - 8;
			if (((temp_dx1 <= dx1 && dx1 <= temp_dx2)
				|| (temp_dx1 <= dx2 && dx2 <= temp_dx2))
				&& (p->dy1 <= dy1 && dy1 <= p->dy3)) {
				/*std::cout << "Collision with Ball" << std::endl;
				std::cout << temp_dx1 << ", " << dx1 << std::endl;
				std::cout << temp_dx2 << ", " << dx2 << std::endl;*/
				return true;
			}
			return false;
		}
};

int run_ball_Parser() {
	scan_ball_tileset();
	Map = createMap();
	return 1;

}

void scan_ball_tileset() {

	std::vector <Tile> tileset_obj;
	ball_tileset = al_load_bitmap("Ball.png");
	al_convert_mask_to_alpha(ball_tileset, al_map_rgb(82, 163, 163));

}



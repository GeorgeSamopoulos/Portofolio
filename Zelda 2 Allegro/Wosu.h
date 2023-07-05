ALLEGRO_BITMAP* wosu_tileset;
class Wosu;
int run_wosu_Parser();
void scan_wosu_tileset();

class Wosu {
public:
	int hp = 1;
	int power = 8;
	move posx = RIGHT;
	double dx1, dy1, dx2, dy2, dx3, dy3, dx4, dy4;
	double height, width;
	int spritenum;
	int steps = 0;
	bool isDead = false;

	Wosu(double x, double y, double height, double width) {
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
	void display_wosu(int x, int y,int spritenum) {
		if (!this->isDead)
			al_draw_bitmap_region(wosu_tileset, spritenum * 16, 0, 16, 32, x, y, ALLEGRO_FLIP_HORIZONTAL);
		//al_flip_display();
	}

	void move() {
		if (this->steps<32) {
			move_right();
		}
		else{
			move_left();
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
		if (this->spritenum==0) {
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
		if (this->spritenum == 2) {
			this->spritenum = 3;
		}
		else {
			this->spritenum = 2;
		}
	}

	void start_wosu() {
		spritenum = 0;
		display_wosu(dx1, dy1, this->spritenum);
	}

	bool check_wosu_collision(Player* p) {
		int temp_dx1 = p->dx1 + 8;
		int temp_dx2 = p->dx2 - 8;
		if (((temp_dx1 <= dx1 && dx1 <= temp_dx2)
			|| (temp_dx1 <= dx2 && dx2 <= temp_dx2))
			&& (p->dy1 <= dy1 && dy1 <= p->dy3)) {
		/*std::cout << "Collision with Wosu" << std::endl;
		std::cout << temp_dx1 << ", " << dx1 << std::endl;
		std::cout << temp_dx2 << ", " << dx2 << std::endl;*/
			return true;
		}
		return false;
	}
};

int run_wosu_Parser() {
	scan_wosu_tileset();
	Map = createMap();
	return 1;

}

void scan_wosu_tileset() {

	std::vector <Tile> tileset_obj;
	wosu_tileset = al_load_bitmap("Wosu.png");
	al_convert_mask_to_alpha(wosu_tileset, al_map_rgb(82, 163, 163));

}


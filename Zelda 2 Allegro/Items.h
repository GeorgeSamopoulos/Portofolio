
ALLEGRO_BITMAP* items_tileset;
class Item;
void consume_item(Player * , Item );
void check_fire(int);
std::vector <Item> items;

class Item {

public:
	std::string name;
	int fire_steps; 
	move turn = RIGHT;

	double dx1, dy1, dx2, dy2;
	double posx1, posy1, posx2, posy2;
	bool active = true;
	int points;

	Item(std::string name, double x, double y ,double posx,double posy,int points) {
		this->name = name;
		this->dx1 = x;
		this->dy1 = y;
		this->dx2 = dx1 + 16;
		this->dy2 = dy1 + 8;

		this->posx1 = posx;
		this->posx2 = posx+16;
		this->posy1 = posy;
		this->posy2 = posy+8;
		this->points = points;
	}

	Item(std::string name, double x, double y, double posx, double posy, int points , move m) {
		turn = m;
		fire_steps = 16;
		this->name = name;
		this->dx1 = x;
		this->dy1 = y;
		this->dx2 = dx1 + 16;
		this->dy2 = dy1 + 16;

		this->posx1 = posx;
		this->posx2 = posx + 16;
		this->posy1 = posy;
		this->posy2 = posy + 16;
		this->points = points;
	}
};

void init_items() {
	items_tileset = al_load_bitmap("items-objects-sprites.png");
	al_convert_mask_to_alpha(items_tileset, al_map_rgb(128, 0, 128));

	//items.push_back(*new Item("point_bag", 2, 12, 916, 480 - 5 * 16));
	items.push_back(*new Item("blue_potion", 30, 12, 1940, 480 - 3*16,0));
	items.push_back(*new Item("red_potion", 41, 12, 2400, 480 - 3 * 16, 0));
	items.push_back(*new Item("key", 101, 12, 848 , 480 - 7 * 16, 0));
	items.push_back(*new Item("up_doll", 70, 12, 1248, 480 - 3 * 16, 0));

}

void check_for_item(Player* p) {
	move posx = RIGHT;
	double dx1 = p->dx3;
	double dx2 = p->dx4;
	double dy1 = p->dy3;
	double dy2 = p->dy4;

	for (int i = 0; i < items.size(); i++) {
		

		if (items[i].name == "fire" && items[i].active == true) {
			check_fire(i);
		}
		else if (items[i].posx1<=dx1 && items[i].posx2>=dx1 ) {
			if (items[i].active == true) {
				consume_item(p, items[i]);
				al_stop_sample_instance(song_instance);
				al_play_sample(level_up, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				al_play_sample_instance(song_instance);
				items[i].active = false;
			}
		}else if (items[i].posx1 <= dx2 && items[i].posx2 >= dx2 ) {
			if (items[i].active == true) {
				consume_item(p, items[i]);
				al_stop_sample_instance(song_instance);
				al_play_sample(level_up, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				al_play_sample_instance(song_instance);
				items[i].active = false;
			}
		}


	}


}

void consume_item(Player * p , Item it) {
	
	//std::cout << it.name << std::endl;

	if (it.name == "point_bag") {
		p->points += it.points;
		//std::cout << it.name << std::endl;
	}
	else if (it.name == "blue_potion") {
		if (p->magic_point + 24 < 128)
			p->magic_point += 24;
		else
			p->magic_point = 128;
		//std::cout << it.name << std::endl;
	}
	else if (it.name == "red_potion") {
		p->magic_point = 128;
		//std::cout << it.name << std::endl;

	}
	else if (it.name == "key") {
		p->has_key = true;
		al_stop_sample_instance(song_instance);
		al_play_sample(key, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		al_play_sample_instance(song_instance);
		//std::cout << it.name << std::endl;
	}
	else if (it.name == "up_doll") {
		p->extra_life++;
		//std::cout << it.name << std::endl;
	}


}


void display_items() {
	for (int i = 0; i < items.size(); i++) {
		if (items[i].active == true) {
			al_draw_bitmap_region(items_tileset,items[i].dx1, items[i].dy1, items[i].dy2 - items[i].dy1, items[i].dx2 - items[i].dx1, items[i].posx1-cam_position[0], items[i].posy1, 0);
		}
	}
}


void add_point_bag(int points,int x,int y) {

	items.push_back(*new Item("point_bag", 2, 12, x, y,points));

}

void create_fire(Player * p) {

	if (p->posx == LEFT) {
		items.push_back(*new Item("fire", 86, 42, p->dx1-16,p->dy1,0,p->posx));

	}
	if (p->posx == RIGHT) {
		items.push_back(*new Item("fire", 86, 42, p->dx1 + 16, p->dy1, 0, p->posx));

	}
}


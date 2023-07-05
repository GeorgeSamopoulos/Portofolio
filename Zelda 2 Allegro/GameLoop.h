ALLEGRO_EVENT_QUEUE* event_queue;
ALLEGRO_TIMER* big_clock , * frame_clock , *attack_timer;

enum Enemy {wosu,stalfos,guma,ball};
Player* p;
Stalfos* stalf;
Ball* ba;
Guma* gum;
Wosu* wos;
int enemies_interval;
void event_controller(ALLEGRO_EVENT event);
void check_link_attack(Stalfos*, Ball*, Guma*, Wosu*, Player*);
bool check_enemies_attack(int* sec, int* sec_collision);
void update_sprites_display();
void enemies_attack();
void display_spells();
void display_win();
void display_lose();
bool checkShield(Enemy);
void spell_shield();
void spell_jump();
void spell_life();
void spell_fairy();
void spell_fire();
void spell_reflect();
void spell_thunder();
void reset_spells();
bool keys_enabled[ALLEGRO_KEY_MAX];
bool isFinished = false;
bool fireEnable = false , fireLock=true; 
namespace app {
	class App {
	protected:
		Game game;

	public:

		void	Initialise(void) {

			std::cout << "----------  ----------   |          |--------\\                /\\             |      |" << std::endl;
			std::cout << "        /   |            |          |         \\              /  \\            |      |" << std::endl;
			std::cout << "       /    |            |          |          \\            /    \\           |      |" << std::endl;
			std::cout << "      /     |            |          |           \\          /      \\          |      |" << std::endl;
			std::cout << "     /      |            |          |            \\        /        \\         |      |" << std::endl;
			std::cout << "    /       |--------    |          |            /       /----------\\        |      |" << std::endl;
			std::cout << "   /        |            |          |           /       /            \\       |      |" << std::endl;
			std::cout << "  /         |            |          |          /       /              \\      |      |" << std::endl;
			std::cout << " /          |            |          |         /       /                \\     |      |" << std::endl;
			std::cout << "/_________  |_________   |________  |________/       /                  \\    |      |" << std::endl;
			al_init();

			al_init_primitives_addon();

			al_install_keyboard();

			event_queue = al_create_event_queue();

			//al_install_mouse();

			al_init_image_addon();

			init_items();

			display = al_create_display(5000, 5000);

			big_clock = al_create_timer(1.0 / 60);
			frame_clock = al_create_timer(1.0 / 60);
			attack_timer = al_create_timer(1.0 / 60);

			al_clear_to_color(al_map_rgb(255, 255, 255));;

			p = new Player(16.0, 448.0 - 32.0, 32.0, 32.0);

			stalf = new Stalfos(2128, 128.0, 16, 32);
			ba = new Ball(1020, 448.0 - 16.0, 16, 16);
			gum = new Guma(2645, 448.0 - 32.0, 32, 32);
			wos = new Wosu(1461, 448.0 - 32.0, 32, 16);
		}

		void	Load(void) {
			run_Parser("new_palace.csv");
			run_npc_Parser();
			run_wosu_Parser();
			run_guma_Parser();
			run_ball_Parser();
			run_stalfos_Parser();
			createGridMap(Map);
			display_map();

		}
		void	Run(void) {

			////std::cout << "ok run" << std::endl;
			//p->start_player();

			game.MainLoopIteration();
		}
		void	RunIteration(void)
		{
			game.MainLoopIteration();
		}
		Game& GetGame(void) { return game; }
		const Game& GetGame(void) const { return game; }
		void	Clear(void) {}
		void Main(void) {
			Initialise();
			Load();
			Run();
			Clear();
		}
	};
}

double temp_pos[] = { 0.0,0.0 };
bool mouse_flag = false;
bool pause_flag = false;
bool spells_display = false;
int selected_spell = 0;
void (*spell_functions[7])() = { spell_shield,spell_jump, spell_life, spell_fairy, spell_fire, spell_reflect, spell_thunder }; 
void Game::MainLoopIteration() {
	//al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(big_clock));
	al_init_font_addon();
	al_init_ttf_addon();
	zelda_pause_font = al_load_font("arial.ttf", 24, 0);
	zelda_bar_font = al_load_font("arial.ttf", 10, 0);
	
	al_install_audio();
	al_init_acodec_addon();

	al_reserve_samples(10);
	song = al_load_sample("theme_song.mp3");
	shoot = al_load_sample("attack.mp3");
	key = al_load_sample("key.mp3");
	level_up = al_load_sample("level_up.mp3");
	win = al_load_sample("wining.mp3");
	lose = al_load_sample("lose.mp3");
	song_instance = al_create_sample_instance(song);
	al_set_sample_instance_playmode(song_instance, ALLEGRO_PLAYMODE_LOOP);
	al_attach_sample_instance_to_mixer(song_instance, al_get_default_mixer());
	al_play_sample_instance(song_instance);

	al_start_timer(big_clock);
	p->start_player();

	stalf->start_stalfos();
	ba->start_ball();
	gum->start_guma();
	wos->start_wosu();
	enemies_interval = 1;
	int sec = 0,  sec_collision = 0, sec_spell=0;
	double sec_attack = 0;
	while (!isFinished) {
		al_start_timer(frame_clock);
		al_flip_display();
		if (isFinished = p->check_finish()) {
			continue;
		}
		ALLEGRO_EVENT event;
		
		al_wait_for_event(event_queue, &event);
		event_controller(event);
		
		while (pause_flag) {
			al_wait_for_event(event_queue, &event);
			event_controller(event);
		}

		sec = (int)(al_get_timer_count(big_clock) * al_get_timer_speed(big_clock));
		if (check_enemies_attack(&sec, &sec_collision)) {
			sec_attack = sec;
			enemies_attack();
			sec_collision = (int)(al_get_timer_count(big_clock) * al_get_timer_speed(big_clock));
		}
		//sec_attack = (al_get_timer_count(attack_timer) * al_get_timer_speed(attack_timer));
		if (p->isDamaged && (sec - sec_attack) >= 1) {
			//al_stop_timer(attack_timer);
			p->isDamaged = false;
			sec_attack = 0;
			p->get_off_damage();
		}
		update_sprites_display();
		display_items();
		if (selected_spell != 0 && !spells_display) {
			spell_functions[selected_spell - 1]();
			selected_spell = 0;
			sec_spell = (int)(al_get_timer_count(big_clock) * al_get_timer_speed(big_clock));
		}

		if (sec_spell != 0) {
			if (sec_spell + 30 < sec) {
				reset_spells();
				sec_spell = 0;
			}
		}
		if (spells_display) display_spells();
		display_bar(p->life,p->extra_life, p->magic_point , p->points);
		if (fireEnable) check_for_item(p);
		while (al_get_timer_count(frame_clock) < (al_get_timer_speed(frame_clock) * 1000));
		al_stop_timer(frame_clock);
		
	}

	if (p->winFlag) {
		//std::cout << "win";
		al_stop_sample_instance(song_instance);
		al_play_sample(win, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		display_win_link(big_clock,p->dx1,p->dy1,p->sprite);
		update_sprites_display();
		al_flip_display();
		Sleep(3 * 1000);
		display_win();
	}
	else {
		al_stop_sample_instance(song_instance);
		al_play_sample(lose, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
		Sleep(1000);
		display_lose();

	}
	system("pause");
}

void display_win() {
	al_draw_filled_rectangle(0, 0, 640, 480, al_map_rgba(0, 0, 0, 175));
	al_draw_text(zelda_pause_font, al_map_rgb(255, 255, 0), 320, 240, ALLEGRO_ALIGN_CENTRE, "YOU WON");
	al_flip_display();
}

void display_lose() {
	al_draw_filled_rectangle(0, 0, 640, 480, al_map_rgba(0, 0, 0, 175));
	al_draw_text(zelda_pause_font, al_map_rgb(255, 255, 0), 320, 240, ALLEGRO_ALIGN_CENTRE, "GAME OVER");
	al_flip_display();
}

void display_spells() {
	int spells[7] = { 165, 180, 195, 210, 225, 240, 255 };
	al_draw_filled_rectangle(195, 124, 445, 294, al_map_rgb(128, 128, 128));
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 150, ALLEGRO_ALIGN_LEFT, "SPELL");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 150, ALLEGRO_ALIGN_LEFT, "MAGIC");

	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 165, ALLEGRO_ALIGN_LEFT, "Shield");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 165, ALLEGRO_ALIGN_LEFT, "32");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 180, ALLEGRO_ALIGN_LEFT, "Jump");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 180, ALLEGRO_ALIGN_LEFT, "48");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 195, ALLEGRO_ALIGN_LEFT, "Life");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 195, ALLEGRO_ALIGN_LEFT, "70");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 210, ALLEGRO_ALIGN_LEFT, "Fairy");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 210, ALLEGRO_ALIGN_LEFT, "80");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 225, ALLEGRO_ALIGN_LEFT, "Fire");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 225, ALLEGRO_ALIGN_LEFT, "120");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 240, ALLEGRO_ALIGN_LEFT, "Reflect");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 240, ALLEGRO_ALIGN_LEFT, "80");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 265, 255, ALLEGRO_ALIGN_LEFT, "Thunder");
	al_draw_text(zelda_bar_font, al_map_rgb(0, 0, 0), 315, 255, ALLEGRO_ALIGN_LEFT, "80");

	if (selected_spell != 0) {
		al_draw_filled_triangle(345, spells[selected_spell - 1] + 5, 355, spells[selected_spell - 1] + 10, 355, spells[selected_spell - 1], al_map_rgb(0, 0, 0));

	}
}



void update_sprites_display() {
	if (enemies_interval == 0) {
		wos->move();
		ba->move();
		gum->move();
		if(stalf->has_fallen) stalf->move();
	}
	move_camera(0, 0);
	if (door_changed) change_door_display(151, 26, p->dx2, p->dy2);
	display_player(p->posx1, p->posy1, p->sprite);
	
	wos->display_wosu(wos->dx1 - cam_position[0], wos->dy1, wos->spritenum);
	
	ba->display_ball(ba->dx1 - cam_position[0], ba->dy1, ba->spritenum);
	
	gum->display_guma(gum->dx1 - cam_position[0], gum->dy1, gum->spritenum);	
	if (gum->weapon_thrown) {
		gum->display_weapon(gum->weapon_dx1 - cam_position[0], gum->weapon_dy1, gum->weapon_spritenum);
	}
	
	stalf->display_stalfos(stalf->dx1 - cam_position[0], stalf->dy1, stalf->spritenum);
	if (stalf->spritenum==12) {
		stalf->display_stalfos(stalf->dx1 - cam_position[0] - 16, stalf->dy1, 13);
	}
	else if (stalf->spritenum == 3) {
		stalf->display_stalfos(stalf->dx1 - cam_position[0] + 16, stalf->dy1,  2);
	}
	if ((p->dx1 == 2128 && stalf->has_fallen == false) || stalf->falling) {
		stalf->fall();
	}
	enemies_interval++;
	enemies_interval = enemies_interval % 5;

}
void event_controller(ALLEGRO_EVENT event) {

	if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
		if (spells_display && (27 > event.keyboard.keycode || event.keyboard.keycode > 34)) {
			return;
		}
		keys_enabled[event.keyboard.keycode] = true;
		if (event.keyboard.keycode == ALLEGRO_KEY_TAB) {
			spells_display = true;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_1) {
			selected_spell = 1;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_2) {
			selected_spell = 2;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_3) {
			selected_spell = 3;

		}
		if (event.keyboard.keycode == ALLEGRO_KEY_4) {
			selected_spell = 4;

		}
		if (event.keyboard.keycode == ALLEGRO_KEY_5) {
			selected_spell = 5;

		}
		if (event.keyboard.keycode == ALLEGRO_KEY_6) {
			selected_spell = 6;

		}
		if (event.keyboard.keycode == ALLEGRO_KEY_7) {
			selected_spell = 7;

		}
		if (event.keyboard.keycode == ALLEGRO_KEY_0) {
			selected_spell = 0;
		}
	}
	else if (event.type == ALLEGRO_EVENT_KEY_UP) {
		keys_enabled[event.keyboard.keycode] = false;
		if (event.keyboard.keycode==ALLEGRO_KEY_ESCAPE) {
			pause_flag = !pause_flag;
			if (pause_flag) {
				al_stop_timer(big_clock);
				display_pause();

			}
			else {
				al_resume_timer(big_clock);
			}
			return;
		}
		if (event.keyboard.keycode == ALLEGRO_KEY_TAB) {
			spells_display = false;
		}
		if (keys_enabled[ALLEGRO_KEY_DOWN] == false) {
			p->shield=false;
			p->sit_flag = false;
			p->move_player(0, 0, UP);
		}
		else if (keys_enabled[ALLEGRO_KEY_A] == false) {
			
			if (p->sit_flag) {
				p->sit_flag = false;
			}
		}

		if (keys_enabled[ALLEGRO_KEY_A] == false) {
			p->attack_enable = true;
		}
		if (keys_enabled[ALLEGRO_KEY_S] == false) {
			fireLock = true;
		}
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
		mouse_flag = true;
	}
	else if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
		mouse_flag = false;

	}
	else if (event.type == ALLEGRO_EVENT_TIMER) {
		
		if (pause_flag) {
			return;
		}
		
		if (p->isDamaged && pause_flag==false) {
			return;
		}

		if (keys_enabled[ALLEGRO_KEY_A]) {
			if (p->enable_jump) {
				al_play_sample(shoot, 1, 0, 1, ALLEGRO_PLAYMODE_ONCE, 0);
				p->attack();
				if (p->attack_enable) {
					p->attack_enable = false;
					p->check_door();
					check_for_item(p);
					check_link_attack(stalf, ba, gum, wos, p);
				}
				return;
			}
		}
		if (keys_enabled[ALLEGRO_KEY_S]) {
			if (fireEnable && fireLock) {
				fireLock = false;
				create_fire(p);
			}
		}
		if (keys_enabled[ALLEGRO_KEY_RIGHT]) {
			if (testGridPlayer(p, RIGHT, 2, 0)) {
				p->move_player(2, 0, RIGHT);
			}else {
				p->move_player(0, 0, RIGHT);
			}
		}
		if (keys_enabled[ALLEGRO_KEY_LEFT]) {
			if (testGridPlayer(p, LEFT, -2, 0)) {
				p->move_player(-2, 0, LEFT);
			}else {
				p->move_player(0, 0, LEFT);
			}
		}
		if (keys_enabled[ALLEGRO_KEY_UP]) {
			if (p->enable_jump && p->sit_flag==false) {
				p->enable_jump = false;
				jump_event = true;
			}
		}
		if (keys_enabled[ALLEGRO_KEY_DOWN]) {
			
			if (p->enable_jump == true) {
				if (!p->sit_flag ) {
					p->sit_down();
				}
				p->sit_flag = true;
			}

		}
		
		if (jump_event) {
				p->jump();
		}
		else {

			grav_flag=p->check_gravity();
		}
		p->check_elevator();
	}
}


void check_link_attack(Stalfos* st, Ball* b, Guma* g, Wosu* w , Player * pl) {
	if (pl->posx == LEFT) {
		double tempx = pl->dx1;
		double tempy = (pl->dy1 + pl->dy3) / 2;

		if ((w->dx2 >= tempx) && (w->dx1 <= tempx) && (w->dy1 <= tempy) && (w->dy3 >= tempy) && !w->isDead) {
			w->hp--;
			if (w->hp<=0) {
				w->isDead = true;
				
			}
			//std::cout << "left attack wosu" << std::endl;

		}

		if ((b->dx2 >= tempx) && (b->dx1 <= tempx) && (b->dy1 <= tempy) && (b->dy3 >= tempy) && !b->isDead) {
			b->hp--;
			if (b->hp <= 0) {
				b->isDead = true;
				add_point_bag(10,b->dx1,b->dy1);
			}
			//std::cout << "left attack ball" << std::endl;

		}

		if ((st->dx2 >= tempx) && (st->dx1 <= tempx) && (st->dy1 <= tempy) && (st->dy3 >= tempy) && !st->isDead && p->sit_flag) {
			st->hp--;
			if (st->hp <= 0) {
				st->isDead = true;
				add_point_bag(30, st->dx1, st->dy1);
			}
			//std::cout << "left attack stalfos" << std::endl;

		}

		if ((g->dx2 >= tempx) && (g->dx1 <= tempx) && (g->dy1 <= tempy) && (g->dy3 >= tempy) && !g->isDead) {
			g->hp--;
			if (g->hp <= 0) {
				g->isDead = true;
				add_point_bag(50, g->dx1, g->dy1);
			}
			//std::cout << "left attack guma" << std::endl;

		}
	}
	else if (pl->posx == RIGHT) {
		double tempx = pl->dx2;
		double tempy = (pl->dy2 + pl->dy4) / 2;

		if ((w->dx1 <= tempx) && (w->dx2 >= tempx) && (w->dy1 <= tempy) && (w->dy3 >= tempy) && !w->isDead) {
			w->hp--;
			if (w->hp <= 0) {
				w->isDead = true;
			}
			//std::cout << "right attack wosu" << std::endl;

		}

		if ((b->dx1 <= tempx) && (b->dx2 >= tempx) && (b->dy1 <= tempy) && (b->dy3 >= tempy) && !b->isDead) {
			b->hp--;
			if (b->hp <= 0) {
				b->isDead = true;
				add_point_bag(10, b->dx1, b->dy1);
			}
			
			//std::cout << "right attack ball" << std::endl;

		}
		
		if ((st->dx1 <= tempx) && (st->dx2 >= tempx) && (st->dy1 <= tempy) && (st->dy3 >= tempy) && !st->isDead && p->sit_flag) {
			st->hp--;
			if (st->hp <= 0) {
				st->isDead = true;
				add_point_bag(30, st->dx1, st->dy1);
			}
			//std::cout << "right attack stalfos" << std::endl;

		}

		if ((g->dx1 <= tempx) && (g->dx2 >= tempx) && (g->dy1 <= tempy) && (g->dy3 >= tempy) && !g->isDead) {
			g->hp--;
			if (g->hp <= 0) {
				g->isDead = true;
				add_point_bag(50, g->dx1, g->dy1);
			}
			//std::cout << "right attack guma" << std::endl;

		}

	}

	////std::cout << st->hp<<std::endl;

}


bool check_enemies_attack(int* sec, int* sec_collision) {
	bool collision_detected = false;
	////std::cout << "collision time: " << *sec_collision << ", time: " << *sec << std::endl;
	if (*sec - *sec_collision >= 2) {
		p->in_collision = false;
	}
	if (!p->in_collision) {
		if ( !wos->isDead && wos->check_wosu_collision(p)) {
			//p->get_attack(wos->power);
			p->in_collision = true;
			*sec_collision = *sec; 
			collision_detected = true;
		}
		else if (!ba->isDead && ba->check_ball_collision(p)) {
			//p->get_attack(ba->power);
			p->in_collision = true;
			*sec_collision = *sec; 
			collision_detected = true;
		}
		else if (!stalf->isDead && stalf->check_stalfos_collision(p) ) {
			//p->get_attack(stalf->power);
			p->in_collision = true;
			*sec_collision = *sec; 
			collision_detected = true;
		}
		else if (!gum->isDead && gum->check_guma_collision(p)) {
			//p->get_attack(gum->power);
			p->in_collision = true;
			*sec_collision = *sec; 
			collision_detected = true;
		}
	}
	return collision_detected;
}


void enemies_attack() {

	if (!wos->isDead && wos->check_wosu_collision(p) ) {
		if (!p->shield) {
			p->get_attack(wos->power, wos->posx);
		}
		else if (checkShield(wosu)) {
			p->get_attack(wos->power, wos->posx);
		}
	}
	else if (!ba->isDead && ba->check_ball_collision(p) ) {
		if (!p->shield) {
			p->get_attack(ba->power,ba->posx);
		}
		else if (checkShield(ball)) {
			p->get_attack(ba->power, ba->posx);
		}
		
	}
	else if (!stalf->isDead && stalf->check_stalfos_collision(p) ) {
		
			if (!p->shield) {
				p->get_attack(stalf->power, stalf->posx);
			}
			else if (checkShield(stalfos)) {
				p->get_attack(stalf->power, stalf->posx);
			}
		
	}
	else if (!gum->isDead && (gum->check_guma_collision(p) || gum->check_guma_weapon_collision(p))) {
		if (!p->shield) {
			p->get_attack(gum->power, gum->posx);
		}
		else if (checkShield(guma)) {
			p->get_attack(gum->power, gum->posx);
		}
		
	}

}

void spell_shield() {
	//std::cout << "Shield" << std::endl;
	if (p->magic_point >= 32) {
		p->damage_filter = 0.5;
		p->magic_point -= 32;
	}
}
void spell_jump() {
	//std::cout << "Jump" << std::endl;
	if (p->magic_point >= 48) {
		p->jump_limit += 32;
		p->magic_point -= 48;
	}
}
void spell_life() {
	//std::cout << "Life" << std::endl;
	if (p->magic_point >= 70) {
		p->magic_point -= 70;
		if (p->life <= 50) {
			p->life += 50;
		}
		else {
			p->life = 100;
		}
	}
}
void spell_fairy() {
	//std::cout << "Fairy" << std::endl;
	if (p->magic_point >= 80) {
		p->magic_point -= 80;
	}


}
void spell_fire() {
	//std::cout << "Fire" << std::endl;
	if (p->magic_point >= 120) {
		p->magic_point -= 120;
	}
	fireEnable = true;
}
void spell_reflect() {
	//std::cout << "Reflect" << std::endl;
	if (p->magic_point >= 120) {
		p->magic_point -= 120;
	}
}
void spell_thunder() {
	//std::cout << "Thunder" << std::endl;
	if (p->magic_point >= 120) {
		p->magic_point -= 120;
	}

	if ((wos->dx2 >= cam_position[0]) && (cam_position[0]+640>=wos->dx1)) {
		wos->isDead = true;
		
	}

	if ((ba->dx2 >= cam_position[0]) && (cam_position[0] + 640 >= ba->dx1)) {
		ba->isDead = true;
		add_point_bag(10, ba->dx1, ba->dy1);
	}

	if ((stalf->dx2 >= cam_position[0]) && (cam_position[0] + 640 >= stalf->dx1)) {
		stalf->isDead = true;
		add_point_bag(30, stalf->dx1, stalf->dy1);
	}

	if ((gum->dx2 >= cam_position[0]) && (cam_position[0] + 640 >= gum->dx1)) {
		gum->isDead = true;
		add_point_bag(50, gum->dx1, gum->dy1);
	}
}

void reset_spells() {
	p->jump_limit = 32;
	p->damage_filter = 1.0;
	fireEnable = false;
	for (int i = 0;i< items.size(); i++) {
		if (items[i].name == "fire") {
			items[i].active = false;
		}
	}
	//std::cout << "Spells reset" << std::endl;
}

bool checkShield(Enemy en) {
	bool flag = false;

	if (en==wosu) {
		if (p->posx==wos->posx) {
			if (p->posx == LEFT) {
				if ((wos->dx1 >= p->dx1) && (wos->dx1 <= p->dx2)) {
					flag = true;
				}
			}
			else if (p->posx == RIGHT) {
				if ((wos->dx2 >= p->dx1) && (wos->dx2 <= p->dx2)) {
					flag = true;
				}
			}
		}
	}
	else if (en==ball) {
		if (p->posx == ba->posx) {
			if (p->posx == LEFT) {
				if ((ba->dx1 >= p->dx1) && (ba->dx1 <= p->dx2)) {
					flag = true;
				}
			}
			else if (p->posx == RIGHT) {
				if ((ba->dx2 >= p->dx1) && (ba->dx2 <= p->dx2)) {
					flag = true;
				}
			}
		}
	}
	else if (en == stalfos) {
		if (p->posx == stalf->posx) {
			if (p->posx == LEFT) {
				if ((stalf->dx1 >= p->dx1) && (stalf->dx1 <= p->dx2)) {
					flag = true;
				}
			}
			else if (p->posx == RIGHT) {
				if ((stalf->dx2 >= p->dx1) && (stalf->dx2 <= p->dx2)) {
					flag = true;
				}
			}
		}
	}
	else if (en == guma) {
		if (p->posx == gum->posx) {
			if (p->posx == LEFT) {
				if ((gum->weapon_dx1 >= p->dx1) && (gum->weapon_dx1 <= p->dx2)) {
					flag = true;
				}
				if ((gum->dx1 >= p->dx1) && (gum->dx1 <= p->dx2)) {
					flag = true;
				}
			}
			else if (p->posx == RIGHT) {
				if ((gum->dx2 >= p->dx1) && (gum->dx2 <= p->dx2)) {
					flag = true;
				}
			}
		}
	}
	return flag;
}



void check_fire(int i) {
	items[i].fire_steps--;
	if (items[i].fire_steps <= 0) {
		items[i].active = false;
	}
	if (items[i].turn == LEFT) {


		items[i].posx1 -= 4;
		items[i].posx2 -= 4;

		if ((stalf->dx1 <= items[i].posx1 && stalf->dx2 >= items[i].posx1)) {
			stalf->hp--;
			if (stalf->hp<=0) {
				stalf->isDead = true;
			}
			items[i].active = false;
		}
		else if ((wos->dx1 <= items[i].posx1 && wos->dx2 >= items[i].posx1)) {
			wos->hp--;
			if (wos->hp <= 0) {
				wos->isDead = true;
			}
			items[i].active = false;
		}
		else if ((ba->dx1 <= items[i].posx1 && ba->dx2 >= items[i].posx1)) {
			ba->hp--;
			if (ba->hp <= 0) {
				ba->isDead = true;
			}
			items[i].active = false;
		}
		else if ((gum->dx1 <= items[i].posx1 && gum->dx2 >= items[i].posx1)) {
			gum->hp--;
			if (gum->hp <= 0) {
				gum->isDead = true;
			}
			items[i].active = false;
		}

	}
	if (items[i].turn == RIGHT) {
		items[i].posx1 += 4;
		items[i].posx2 += 4;
		if ((stalf->dx1 <= items[i].posx2 && stalf->dx2 >= items[i].posx2)) {
			stalf->hp--;
			if (stalf->hp <= 0) {
				stalf->isDead = true;
			}
			items[i].active = false;
		}
		else if ((wos->dx1 <= items[i].posx2 && wos->dx2 >= items[i].posx2)) {
			wos->hp--;
			if (wos->hp <= 0) {
				wos->isDead = true;
			}
			items[i].active = false;
		}
		else if ((ba->dx1 <= items[i].posx2 && ba->dx2 >= items[i].posx2)) {
			ba->hp--;
			if (ba->hp <= 0) {
				ba->isDead = true;
			}
			items[i].active = false;
		}
		else if ((gum->dx1 <= items[i].posx2 && gum->dx2 >= items[i].posx2)) {
			gum->hp--;
			if (gum->hp <= 0) {
				gum->isDead = true;
			}
			items[i].active = false;
		}
		
	}
}
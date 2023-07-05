#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstring>
#define size_block 16
#define WINDOW_W 640
#define WINDOW_H 480
class Tile;
class Game;

void ReadTextMap(std::string name);
std::vector <std::string> split_string(std::string line);
std::vector <Tile> scan_Tileset(std::string tileset_name);
std::vector<std::vector<Tile>> createMap();
int run_Parser(std::string name);
void display_map();
bool move_camera(double x, double y);
void display_pause();
void display_bar(int , int , int , int);
ALLEGRO_FONT* zelda_pause_font;
ALLEGRO_FONT* zelda_bar_font;

ALLEGRO_SAMPLE* song;
ALLEGRO_SAMPLE* shoot;
ALLEGRO_SAMPLE* key;
ALLEGRO_SAMPLE* level_up;
ALLEGRO_SAMPLE* win;
ALLEGRO_SAMPLE* lose;
ALLEGRO_SAMPLE_INSTANCE* song_instance;

ALLEGRO_BITMAP* tileset;
ALLEGRO_BITMAP* map_bitmap;
ALLEGRO_DISPLAY* display;
std::vector<Tile>Tileset;
std::vector <std::vector <Tile>> Map;
bool move_cam = false;
bool door_changed = false;
int currm = 0;

int LeftBorder[2] = {
	0 , 800
};

int RightBorder[2] = {
	800, 2960
};

class Tile {

public:
	int number;
	ALLEGRO_COLOR pixels[16][16];

	Tile copy_tile() {
		Tile copy;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 16; j++) {
				copy.pixels[i][j] = this->pixels[i][j];
				copy.number = this->number;
			}
		}

		return copy;
	}
};


class Game {

public: void MainLoop() {

}

public:	void MainLoopIteration();

};


std::vector<std::vector <int>> csv_num;

void ReadTextMap(std::string name) {

	char const* name_file = name.data();
	std::fstream file(name, std::ios::in);

	if (!file) {
		std::cout << "No such a file";
	}

	std::string line;
	while (getline(file, line)) {
		std::vector <std::string> results = split_string(line);
		std::vector<int> line_num;
		for (int i = 0; i < results.size(); i++) {
			//std::cout << results[i] << std::endl;
			line_num.push_back(stoi(results[i]));
		}
		csv_num.push_back(line_num);
		line_num.clear();
	}



}


/*splits the string into numbers and returns a vector of them*/
std::vector <std::string> split_string(std::string line) {
	std::vector <std::string> results;
	int i = 0;
	std::string number;
	while (line[i] != '\0') {
		if (line[i] == ',') {
			results.push_back(number);
			number.clear();
		}
		else if (line[i + 1] == '\0') {
			number += line[i];
			results.push_back(number);
			number.clear();
		}
		else {
			number += line[i];

		}

		i++;
	}
	return results;
}

std::vector <Tile> scan_Tileset(std::string tileset_name) {

	std::vector <Tile> tileset_obj;
	tileset = al_load_bitmap("zelda.png");

	al_lock_bitmap(tileset, al_get_bitmap_format(tileset), ALLEGRO_LOCK_READONLY);



	int w = al_get_bitmap_width(tileset);
	int h = al_get_bitmap_height(tileset);

	/*std::cout << w << " weight\n";
	std::cout << h << "height\n";*/

	int weight_blocks = w / 16;
	int height_blocks = h / 16;

	for (int i = 0; i < height_blocks; i++) {
		//std::cout << "Line i : ";
		for (int j = 0; j < weight_blocks; j++) {

			Tile* a = new Tile();
			for (int line_number = 0; line_number < 16; line_number++) {
				for (int col_number = 0; col_number < 16; col_number++) {
					a->pixels[line_number][col_number] = al_get_pixel(tileset, line_number + (j * 16), col_number + (i * 16));
				}
			}
			a->number = Tileset.size();
			Tileset.push_back(*a);
			//std::cout << a->number << " ";
		}
		//std::cout << std::endl;
	}


	al_unlock_bitmap(tileset);

	return tileset_obj;
}


int run_Parser(std::string name) {
	ReadTextMap(name);
	scan_Tileset("zelda.png");
	Map = createMap();
	return 1;

}

std::vector<std::vector<Tile>> createMap() {
	std::vector<std::vector<Tile>> map;

	for (int i = 0; i < csv_num.size(); i++) {
		Tile new_tile;
		std::vector <Tile> row;
		//std::cout << "Line " + i << ": ";
		for (int j = 0; j < csv_num[i].size(); j++) {
			int num = csv_num[i][j];

			if (num<0 || num>Tileset.size()) {
				continue;
			}

			new_tile = Tileset[num].copy_tile();
			//std::cout << csv_num[i][j] << "=" << Tileset[num].number << " ";
			row.push_back(new_tile);

		}
		//std::cout << std::endl;
		//system("pause");
		map.push_back(row);
		row.clear();
	}

	return map;
}


void display_map() {

	for (int r = 0; r < Map.size(); r++) {
		for (int c = 0; c < Map[r].size(); c++) {
			for (int i1 = 0; i1 < 16; i1++) {
				for (int i2 = 0; i2 < 16; i2++) {
					al_draw_pixel(i1 + (16 * c), i2 + (16 * r), Map[r][c].pixels[i1][i2]);
				}
			}
		}
	}
	//al_flip_display();
	//std::cout << "ok" << std::endl;
	map_bitmap = al_clone_bitmap(al_get_backbuffer(display));
	al_resize_display(display, 640, 480);
	al_set_window_position(display, 0, 0);
	//std::cout << "ok" << std::endl;

}

double cam_position[2] = { 0.0, 0.0 };
bool move_camera(double x, double y) {

	double tx = cam_position[0];
	double ty = cam_position[1];
	cam_position[0] += x;
	cam_position[1] += y;

	if (cam_position[0] < LeftBorder[currm]) {
		cam_position[0] = LeftBorder[currm];
	}
	if (cam_position[1] < 0) {
		cam_position[1] = 0.0;
	}

	if (cam_position[0] + WINDOW_W >= RightBorder[currm] ) {
		cam_position[0] -= x;
	}
	if (cam_position[1] + WINDOW_H >= (Map.size() *16) ) {
		cam_position[1] -= y;
	}


	al_draw_bitmap_region(map_bitmap, cam_position[0], cam_position[1], 640, 480, 0, 0, 0);
	//al_flip_display();
	if (tx == cam_position[0] && ty == cam_position[1]) {
		return false;
	}

	return true;
}

void display_pause() {
	al_draw_filled_rectangle(0, 0, 640, 480, al_map_rgba(0, 0, 0, 175));
	al_draw_text(zelda_pause_font, al_map_rgb(255, 255, 0), 320, 240, ALLEGRO_ALIGN_CENTRE, "GAME PAUSED");
	al_flip_display();
}

void display_bar(int life ,int extra_life, int magic ,int points) {
	if (life < 0) life = 0;
	al_draw_filled_rectangle(0, 0, 640, 45, al_map_rgb(0, 0, 0));
	std::string slife = "LIFE-" + std::to_string(extra_life + 1);
	const char* life_title = slife.c_str();
	al_draw_text(zelda_bar_font, al_map_rgb(255, 255, 255), 120, 5, ALLEGRO_ALIGN_LEFT, life_title);
	al_draw_filled_rectangle(118, 18, 212, 32, al_map_rgb(255, 255, 255));
	al_draw_filled_rectangle(120, 20, (life*0.9)+120, 30, al_map_rgb(255, 0, 0));
	al_draw_line(135, 20, 135, 30, al_map_rgb(255, 255, 255), 2);
	al_draw_line(150, 20, 150, 30, al_map_rgb(255, 255, 255), 2);
	al_draw_line(165, 20, 165, 30, al_map_rgb(255, 255, 255), 2);
	al_draw_line(180, 20, 180, 30, al_map_rgb(255, 255, 255), 2);
	al_draw_line(195, 20, 195, 30, al_map_rgb(255, 255, 255), 2);

	al_draw_text(zelda_bar_font, al_map_rgb(255, 255, 255), 320, 5, ALLEGRO_ALIGN_LEFT, "MAGIC-1");
	al_draw_filled_rectangle(318, 18, 412, 32, al_map_rgb(0, 255, 255));
	al_draw_filled_rectangle(320, 20, (magic * 90/128)+320, 30, al_map_rgb(255, 255, 255));
	al_draw_line(335, 18, 335, 32, al_map_rgb(0, 255, 255), 2);
	al_draw_line(350, 18, 350, 32, al_map_rgb(0, 255, 255), 2);
	al_draw_line(365, 18, 365, 32, al_map_rgb(0, 255, 255), 2);
	al_draw_line(380, 18, 380, 32, al_map_rgb(0, 255, 255), 2);
	al_draw_line(395, 18, 395, 32, al_map_rgb(0, 255, 255), 2);
	std::string pt = std::to_string(points) + " / 2200";
	const char* ds = pt.c_str();
	al_draw_text(zelda_bar_font, al_map_rgb(255, 255, 255), 520, 5, ALLEGRO_ALIGN_LEFT, "NEXT");
	al_draw_text(zelda_bar_font, al_map_rgb(255, 255, 255), 520, 20, ALLEGRO_ALIGN_LEFT,ds);
}



void change_door_display(float x , float y ,float dx , float dy) {

	door_changed = true;
	int i, j;
	al_draw_bitmap_region(tileset,7*16,0,16,16,(16*x-cam_position[0])-1, 16 * y -1, 0);
	al_draw_bitmap_region(tileset, 7 * 16, 0, 16, 16, (16 * x - cam_position[0]) - 1, 16 * (y+1)-1, 0);
	al_draw_bitmap_region(tileset, 7 * 16, 0, 16, 16, (16 * x - cam_position[0]) - 1, 16 * (y-1) - 1, 0);
	
}
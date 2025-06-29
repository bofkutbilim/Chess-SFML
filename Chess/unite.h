#include <SFML/Graphics.hpp>
#include <functional>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <cassert>
#include <set>
#include <fstream>
#include <iterator>

using namespace std;

#define MAXH 800
#define MAXW 1200
#define CHSIZE 8
#define CELLSIZE (MAXH/CHSIZE)
#define FIGSIZE 6

const string StrFigures[] = {"Pawn", "Knight", "King", "Bishop", "Rook", "Queen"};

#define Pawn 0
#define Knight 1
#define King 2
#define Bishop 3
#define Rook 4
#define Queen 5

const string StrColors[] = {"White", "Black"};

#define White 0
#define Black 1

///MAIN>CPP
class Player {
public:
	int i, j;
	Player(int i, int j) : i(i), j(j) {}
	Player() {i = j = -1;}
};
extern Player player;
extern int REZHIM;
void Control(sf::RenderWindow&);

/// FACE>CPP
extern sf::Texture WhiteCell_t, BlackCell_t;
extern sf::Sprite WhiteCell_s, BlackCell_s;

extern sf::Image image_fig[2][FIGSIZE];
extern sf::Texture texture_fig[2][FIGSIZE];
extern sf::Sprite sprite_fig[2][FIGSIZE];

class Cell {
public:
	bool hereIsFigure;
	int getType() {return type;}
	int getColor() {return color;}
	void setType(int _type) {type = _type;}
	void setColor(int _color) {color = _color;}
	Cell(int color, int type) : color(color), type(type), hereIsFigure(true) {}
	Cell() {hereIsFigure = false; color = type = 0;}
private:
	int color;
	int type;
};
extern Cell f[CHSIZE][CHSIZE];

void Set_theme();
void Placing_figures();
void Draw_cell(sf::RenderWindow&, int i, int j);
void Draw_figure(sf::RenderWindow&, int i, int j);

/// CHECKMVOEPLACES>CPP
extern sf::RectangleShape eatrect, justrect, chooserect;
extern set<pair<int, int>> justmove, eatmove, castling;
extern function<void(int,int)> Check_move_places[FIGSIZE];

///CHECKANDMATE>CPP
char Check(int);
char Mate(int);

///ANIMATION>CPP
extern char figure_moving;
void Figure_moving(sf::RenderWindow&app, int pi, int pj, int ni, int nj);
void Swap_position(sf::RenderWindow&app);
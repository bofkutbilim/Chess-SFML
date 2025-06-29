#include "unite.h"

sf::Texture WhiteCell_t, BlackCell_t;
sf::Sprite WhiteCell_s, BlackCell_s;

sf::Image image_fig[2][FIGSIZE];
sf::Texture texture_fig[2][FIGSIZE];
sf::Sprite sprite_fig[2][FIGSIZE];

Cell f[CHSIZE][CHSIZE];

void Placing_figures() {
	for (int i = 0; i < CHSIZE; i++) {
    for (int j = 0; j < CHSIZE; j++) {
			if (i == 1) f[i][j] = Cell(Black, Pawn);
			if (i == 0 && (j == 0 || j == CHSIZE - 1)) f[i][j] = Cell(Black, Rook);
			if (i == 0 && (j == 1 || j == CHSIZE - 2)) f[i][j] = Cell(Black, Knight);
			if (i == 0 && (j == 2 || j == CHSIZE - 3)) f[i][j] = Cell(Black, Bishop);
			if (i == 0 && (j == 3)) f[i][j] = Cell(Black, Queen);
			if (i == 0 && (j == 4)) f[i][j] = Cell(Black, King);
			if (i == CHSIZE - 2) f[i][j] = Cell(White, Pawn);
			if (i == CHSIZE - 1 && (j == 0 || j == CHSIZE - 1)) f[i][j] = Cell(White, Rook);
			if (i == CHSIZE - 1 && (j == 1 || j == CHSIZE - 2)) f[i][j] = Cell(White, Knight);
			if (i == CHSIZE - 1 && (j == 2 || j == CHSIZE - 3)) f[i][j] = Cell(White, Bishop);
			if (i == CHSIZE - 1 && (j == 3)) f[i][j] = Cell(White, Queen);
			if (i == CHSIZE - 1 && (j == 4)) f[i][j] = Cell(White, King);

    }
  }
}

void Set_theme() {
	ifstream fin("theme_id.txt");
	string style;
	fin >> style;
	WhiteCell_t.loadFromFile("Images/WhiteCell"+style+".png");
	WhiteCell_s = sf::Sprite(WhiteCell_t);
	WhiteCell_s.setScale(CELLSIZE/165.0, CELLSIZE/165.0);

	BlackCell_t.loadFromFile("Images/BlackCell"+style+".png");
	BlackCell_s = sf::Sprite(BlackCell_t);
	BlackCell_s.setScale(CELLSIZE/165.0, CELLSIZE/165.0);

	for (int color = 0; color < 2; color++) {
		for (int type = 0; type < FIGSIZE; type++) {
			image_fig[color][type].loadFromFile("Images/"+StrColors[color]+StrFigures[type]+style+".png");
			image_fig[color][type].createMaskFromColor(sf::Color(252, 228, 178));
			texture_fig[color][type].loadFromImage(image_fig[color][type]);
			sprite_fig[color][type] = sf::Sprite(texture_fig[color][type]);
			sprite_fig[color][type].setScale(CELLSIZE/165.0, CELLSIZE/165.0);
		}
	}

	eatrect = sf::RectangleShape(sf::Vector2f(CELLSIZE, CELLSIZE));
	justrect = chooserect = eatrect;
	justrect.setFillColor(sf::Color(66, 236, 142, 70));
	eatrect.setFillColor(sf::Color(237, 40, 18, 70));
	chooserect.setFillColor(sf::Color(154, 215, 243, 100));
}

void Draw_cell(sf::RenderWindow & app, int i, int j) {
	if (i%2 == j%2) {
		WhiteCell_s.setPosition(j*CELLSIZE, i*CELLSIZE);
		app.draw(WhiteCell_s);
	} else {
		BlackCell_s.setPosition(j*CELLSIZE, i*CELLSIZE);
		app.draw(BlackCell_s);
	}
}
void Draw_figure(sf::RenderWindow & app, int i, int j) {
	int color = f[i][j].getColor();
	int type = f[i][j].getType();
	sprite_fig[color][type].setPosition(j*CELLSIZE, i*CELLSIZE);
	app.draw(sprite_fig[color][type]);
}

#include "unite.h"

Player player;
int REZHIM;
set<pair<int, int>> justmove, eatmove, castling;
pair<int, int> choose;

sf::RectangleShape eatrect, justrect, chooserect;



int main() {
	sf::RenderWindow app(sf::VideoMode(MAXW, MAXH), "Chess");

	Set_theme();
	Placing_figures();

	while (app.isOpen()) {
		sf::Event event;
		while (app.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				app.close();
		}

		app.clear();

		for (int i = 0; i < CHSIZE; i++) {
			for (int j = 0; j < CHSIZE; j++) {
				Draw_cell(app, i, j);
				if (eatmove.count({ i, j })) {
					eatrect.setPosition(j * CELLSIZE, i * CELLSIZE);
					app.draw(eatrect);
				}
				if (justmove.count({ i, j })) {
					justrect.setPosition(j * CELLSIZE, i * CELLSIZE);
					app.draw(justrect);
				}
				if (player.i == i && player.j == j) {
					chooserect.setPosition(j * CELLSIZE, i * CELLSIZE);
					app.draw(chooserect);
				}
				if (f[i][j].hereIsFigure) {
					Draw_figure(app, i, j);
				}
			}
		}

		app.display();
	
		Control(app);
	}
	return EXIT_SUCCESS;
}

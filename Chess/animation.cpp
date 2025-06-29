#include "unite.h"

char figure_moving = 1;

void Figure_moving(sf::RenderWindow & app, int pi, int pj, int ni, int nj) {
	if (figure_moving) {
		int color = f[pi][pj].getColor();
		int type = f[pi][pj].getType();
		double sx = pj * CELLSIZE, sy = pi * CELLSIZE;
		double fx = nj * CELLSIZE, fy = ni * CELLSIZE;
		double dx = fabs(fx - sx) / 200.0, dy = fabs(fy - sy) / 200.0;
		for (int iter = 0; iter < 200; iter++) {
			app.clear();
			sx += (fx > sx ? dx : -dx);
			sy += (fy > sy ? dy : -dy);
			for (int i = 0; i < CHSIZE; i++) {
				for (int j = 0; j < CHSIZE; j++) {
					Draw_cell(app, i, j);
					if (f[i][j].hereIsFigure && (pi != i || pj != j))
						Draw_figure(app, i, j);
				}
			}
			sprite_fig[color][type].setPosition(sx, sy);
			app.draw(sprite_fig[color][type]);
			app.display();
		}
	}
}

void Swap_position(sf::RenderWindow& app) {
	app.clear();

	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			Draw_cell(app, i, j);
			if (f[i][j].hereIsFigure) {
				Draw_figure(app, i, j);
			}
		}
	}

	sf::Texture texture;
	texture.create(MAXW, MAXH);
	texture.update(app);

	app.display();

	sf::Time second = sf::milliseconds(100);
	sf::sleep(second);


	vector<vector<Cell>> sw(CHSIZE, vector<Cell>(CHSIZE, Cell()));
	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			sw[CHSIZE - i - 1][CHSIZE - j - 1] = f[i][j];
		}
	}
	for (int i = 0; i < CHSIZE; i++) {
		for (int j = 0; j < CHSIZE; j++) {
			f[i][j] = sw[i][j];
		}
	}

	sf::Time sleeping_before_swaping = sf::seconds(1);

	sf::sleep(sleeping_before_swaping);
}
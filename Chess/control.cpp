#include "unite.h"

void Control(sf::RenderWindow& app) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		bool ok = false;
		int this_color = REZHIM / 2;
		int other_color = this_color == White ? Black : White;
		if (REZHIM % 2 == 0) {
			sf::Vector2i pos = sf::Mouse::getPosition(app);
			int pi = pos.y / CELLSIZE, pj = pos.x / CELLSIZE;

			if (pi >= 0 && pi < CHSIZE && pj >= 0 && pj < CHSIZE) {
				if (f[pi][pj].hereIsFigure && f[pi][pj].getColor() == this_color) {
					ok = true;
					player = Player(pi, pj);
					Check_move_places[f[pi][pj].getType()](pi, pj);
				}
			}
		}
		else {
			sf::Vector2i pos = sf::Mouse::getPosition(app);
			int pi = pos.y / CELLSIZE, pj = pos.x / CELLSIZE;

			if (pi >= 0 && pi < CHSIZE && pj >= 0 && pj < CHSIZE) {
				if (f[pi][pj].hereIsFigure && f[pi][pj].getColor() == f[player.i][player.j].getColor()) {
					justmove.clear();
					eatmove.clear();
					player = Player(pi, pj);
					Check_move_places[f[pi][pj].getType()](pi, pj);
				}
				else {
					if (justmove.count({ pi, pj }) || eatmove.count({ pi, pj })) {
						justmove.clear();
						eatmove.clear();

						Figure_moving(app, player.i, player.j, pi, pj);

						f[pi][pj] = f[player.i][player.j];
						f[player.i][player.j] = Cell();
						ok = true;
						player = Player();

						Swap_position(app);

						if (Check(other_color)) {
							sf::Time check_time = sf::seconds(2);
							sf::Texture chk;
							chk.loadFromFile("Images/check.png");
							sf::Sprite che;
							che = sf::Sprite(chk);
							app.draw(che);
							app.display();
							sf::sleep(check_time);

							if (Mate(other_color)) {
								chk.loadFromFile("Images/mate.png");
								che = sf::Sprite(chk);
								app.draw(che);
								app.display();;
								sf::sleep(check_time);
								app.clear();
							}
						}
					}
				}
			}
		}
		if (ok) {
			REZHIM = (REZHIM + 1) % 4;
		}
	}
}
#include "unite.h"

char Replace_and_check(int pi, int pj, int ni, int nj) {
	Cell temp = f[ni][nj];
	f[ni][nj] = f[pi][pj];
	f[pi][pj] = Cell();

	if (Check(f[ni][nj].getColor())) {
		f[pi][pj] = f[ni][nj];
		f[ni][nj] = temp;
		return 1;
	}
	f[pi][pj] = f[ni][nj];
	f[ni][nj] = temp;
	return 0;
}

void Pawn_move(int pi, int pj) {
	if (pi - 1 >= 0 && !f[pi - 1][pj].hereIsFigure) {
		if (!Replace_and_check(pi, pj, pi - 1, pj)) justmove.insert({pi - 1, pj});
		if (pi == CHSIZE - 2 && !f[pi - 2][pj].hereIsFigure) {
			if (!Replace_and_check(pi, pj, pi - 2, pj)) justmove.insert({ pi - 2, pj });
		}
	}
	if (pi - 1 >= 0) {
		if (pj - 1 >= 0 && f[pi - 1][pj - 1].hereIsFigure && f[pi - 1][pj - 1].getColor() != f[pi][pj].getColor()) {
			if (!Replace_and_check(pi, pj, pi - 1, pj - 1)) eatmove.insert({ pi - 1, pj - 1 });
		}
		if (pj + 1 < CHSIZE && f[pi - 1][pj + 1].hereIsFigure && f[pi - 1][pj + 1].getColor() != f[pi][pj].getColor()) {
			if (!Replace_and_check(pi, pj, pi - 1, pj + 1)) eatmove.insert({ pi - 1, pj + 1 });
		}
	}
}
void Knight_move(int pi, int pj) {
	for (int x = -2; x <= 2; x++) {
		for (int y = -2; y <= 2; y++) {
			if (abs(x * y) == 2) {
				int ni = pi + x, nj = pj + y;
				if (ni >= 0 && ni < CHSIZE && nj >= 0 && nj < CHSIZE) {
					if (!f[ni][nj].hereIsFigure) {
						if (!Replace_and_check(pi, pj, ni, nj)) justmove.insert({ ni, nj});
					}
					else if (f[pi][pj].getColor() != f[ni][nj].getColor()) {
						if (!Replace_and_check(pi, pj, ni, nj)) eatmove.insert({ ni, nj });
					}
				}
			}
		}
	}
}
void King_move(int pi, int pj) {
	for (int x = -1; x <= 1; x++) {
		for (int y = -1; y <= 1; y++) {
			if (!(x == 0 && y == 0)) {
				int ni = pi + x, nj = pj + y;
				if (ni >= 0 && ni < CHSIZE && nj >= 0 && nj < CHSIZE) {
					if (!f[ni][nj].hereIsFigure) {
						if (!Replace_and_check(pi, pj, ni, nj)) justmove.insert({ ni, nj });
					}
					else if (f[pi][pj].getColor() != f[ni][nj].getColor()) {
						if (!Replace_and_check(pi, pj, ni, nj)) eatmove.insert({ ni, nj });
					}
				}
			}
		}
	}
}
void Bishop_move(int pi, int pj) {

	int x, y;

	for (x = pj + 1, y = pi + 1; x < CHSIZE && y < CHSIZE && !f[y][x].hereIsFigure; x++, y++) {
		if (!Replace_and_check(pi, pj, y, x)) justmove.insert({ y, x });
	}

	if (x < CHSIZE&& y < CHSIZE&& f[y][x].hereIsFigure&& f[y][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, x)) eatmove.insert({ y, x });
	}

	for (x = pj - 1, y = pi - 1; x > -1 && y > -1 && !f[y][x].hereIsFigure; x--, y--) {
		if (!Replace_and_check(pi, pj, y, x)) justmove.insert({ y, x });
	}

	if (x > -1 && y > -1 && f[y][x].hereIsFigure && f[y][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, x)) eatmove.insert({ y, x });
	}

	for (x = pj - 1, y = pi + 1; x > -1 && y < CHSIZE && !f[y][x].hereIsFigure; x--, y++) {
		if (!Replace_and_check(pi, pj, y, x)) justmove.insert({ y, x });
	}

	if (x > -1 && y < CHSIZE && f[y][x].hereIsFigure && f[y][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, x)) eatmove.insert({ y, x });
	}

	for (x = pj + 1, y = pi - 1; x < CHSIZE && y > -1 && !f[y][x].hereIsFigure; x++, y--) {
		if (!Replace_and_check(pi, pj, y, x)) justmove.insert({ y, x });
	}

	if (x < CHSIZE && y > -1 && f[y][x].hereIsFigure && f[y][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, x)) eatmove.insert({ y, x });
	}
}
void Rook_move(int pi, int pj) {
	int x, y;
	for (x = pj + 1; x < CHSIZE && !f[pi][x].hereIsFigure; x++) {
		if (!Replace_and_check(pi, pj, pi, x)) justmove.insert({ pi, x });
	}

	if (x < CHSIZE&& f[pi][x].hereIsFigure&& f[pi][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, pi, x)) eatmove.insert({ pi, x });
	}

	for (x = pj - 1; x > -1 && !f[pi][x].hereIsFigure; x--) {
		if (!Replace_and_check(pi, pj, pi, x)) justmove.insert({ pi, x });
	}

	if (x > -1 && f[pi][x].hereIsFigure && f[pi][x].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, pi, x)) eatmove.insert({ pi, x });
	}

	for (y = pi + 1; y < CHSIZE && !f[y][pj].hereIsFigure; y++) {
		if (!Replace_and_check(pi, pj, y, pj)) justmove.insert({ y, pj });
	}

	if (y < CHSIZE&& f[y][pj].hereIsFigure&& f[y][pj].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, pj)) eatmove.insert({ y, pj });
	}

	for (y = pi - 1; y > -1 && !f[y][pj].hereIsFigure; y--) {
		if (!Replace_and_check(pi, pj, y, pj)) justmove.insert({ y, pj });
	}

	if (y > -1 && f[y][pj].hereIsFigure && f[y][pj].getColor() != f[pi][pj].getColor()) {
		if (!Replace_and_check(pi, pj, y, pj)) eatmove.insert({ y, pj });
	}
}
void Queen_move(int pi, int pj) {
	Rook_move(pi, pj);
	Bishop_move(pi, pj);
}


function<void(int, int)> Check_move_places[FIGSIZE] = {
	Pawn_move,
	Knight_move,
	King_move,
	Bishop_move,
	Rook_move,
	Queen_move
};

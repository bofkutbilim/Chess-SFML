#include "unite.h"

char Pawn_beat(int pi, int pj, int ni, int nj) {
    if (pi - 1 == ni)
        if (pj - 1 == nj || pj + 1 == nj)
            return 1;
    return 0;
}
char Knight_beat(int pi, int pj, int ni, int nj) {
    if (abs(pi - ni) * abs(pj - nj) == 2) return 1;
    return 0;
}
char King_beat(int pi, int pj, int ni, int nj) {
    if (abs(pi - ni) <= 1 && abs(pj - nj) <= 1) return 1;
    return 0;
}
char Bishop_beat(int pi, int pj, int ni, int nj) {
    if (abs(ni - pi) != abs(nj - pj)) return 0;
    for (int x = pj + (nj > pj ? +1 : -1), y = pi + (ni > pi ? +1 : -1); x >= 0 && x < CHSIZE && y >= 0 && y < CHSIZE; x += (nj > pj ? +1 : -1), y += (ni > pi ? +1 : -1)) {
        if (f[y][x].hereIsFigure) {
            if (x == nj && y == ni) return 1;
            break;
        }
    }
    return 0;
}
char Rook_beat(int pi, int pj, int ni, int nj) {
    if (pi == ni) {
        for (int x = pj + (nj > pj ? +1 : -1); x >= 0 && x < CHSIZE; x += (nj > pj ? +1 : -1)) {
            if (f[pi][x].hereIsFigure) {
                if (x == nj) return 1;
                break;
            }
        }
    }
    if (pj == nj) {
        for (int y = pi + (ni > pi ? +1 : -1); y >= 0 && y < CHSIZE; y += (ni > pi ? +1 : -1)) {
            if (f[y][pj].hereIsFigure) {
                if (y == ni) return 1;
                break;
            }
        }
    }
    return 0;
}
char Queen_beat(int pi, int pj, int ni, int nj) {
    if (Rook_beat(pi, pj, ni, nj) || Bishop_beat(pi, pj, ni, nj)) return 1;
    return 0;
}

function<char(int, int, int, int)> Beat[FIGSIZE] = {
    Pawn_beat,
    Knight_beat,
    King_beat,
    Bishop_beat,
    Rook_beat,
    Queen_beat
};

char Mate(int color) {
    for (int i = 0; i < CHSIZE; i++) {
        for (int j = 0; j < CHSIZE; j++) {
            if (f[i][j].hereIsFigure)
                if (f[i][j].getColor() == color) {
                    Check_move_places[f[i][j].getType()](i, j);
                    if (!justmove.empty() || !eatmove.empty()) {
                        if (!justmove.empty()) cout << justmove.begin()->first << "\n";
                        else cout << eatmove.begin()->first << "\n";
                        justmove.clear();
                        eatmove.clear();
                        return 0;
                    }
                }
        }
    }
    return 1;
}

char Check(int color) {
    int pi, pj;
    for (int i = 0; i < CHSIZE; i++) {
        for (int j = 0; j < CHSIZE; j++) {
            if (f[i][j].hereIsFigure && f[i][j].getColor() == color && f[i][j].getType() == King) {
                pi = i; pj = j;
                goto afterfor;
            }
        }
    }
    afterfor:;
    for (int i = 0; i < CHSIZE; i++) {
        for (int j = 0; j < CHSIZE; j++) {
            if (f[i][j].hereIsFigure && f[i][j].getColor() != color) {
                if (Beat[f[i][j].getType()](i, j, pi, pj)) return 1; // true if color in dangerous
            }
        }
    }
    return 0;
}
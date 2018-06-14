#include "Card.h"

const int BLUE = 0;
const int RED = 1;

Card CardList[] = {
    {
        /* Name:  */ "BOAR", RED,
        /* Moves: */ { M(-1, 0), M(0, 1), M(1, 0) }
    },
    {
        /* Name:  */ "COBRA", RED,
        /* Moves: */ { M(-1, 0), M(1, -1), M(1, 1) }
    },
    {
        /* Name:  */ "CRAB", BLUE,
        /* Moves: */ { M(-2, 0), M(0, 1), M(2, 0) }
    },
    {
        /* Name:  */ "CRANE", BLUE,
        /* Moves: */ { M(-1, -1), M(0, 1), M(1, -1) }
    },
    {
        /* Name:  */ "DRAGON", RED,
        /* Moves: */ { M(-2, 1), M(-1, -1), M(1, -1), M(2, 1) }
    },
    {
        /* Name:  */ "EEL", BLUE,
        /* Moves: */ { M(-1, -1), M(-1, 1), M(1, 0) }
    },
    {
        /* Name:  */ "ELEPHANT", RED,
        /* Moves: */ { M(-1, 0), M(-1, 1), M(1, 0), M(1, 1) }
    },
    {
        /* Name:  */ "FROG", RED,
        /* Moves: */ { M(-2, 0), M(-1, 1), M(1, -1) }
    },
    {
        /* Name:  */ "GOOSE", BLUE,
        /* Moves: */ { M(-1, 0), M(-1, 1), M(1, 0), M(1, -1) }
    },
    {
        /* Name:  */ "HORSE", RED,
        /* Moves: */ { M(-1, 0), M(0, -1), M(0, 1) }
    },
    {
        /* Name:  */ "MANTIS", RED,
        /* Moves: */ { M(-1, 1), M(0, -1), M(1, 1) }
    },
    {
        /* Name:  */ "MONKEY", BLUE,
        /* Moves: */ { M(-1, -1), M(-1, 1), M(1, -1), M(1, 1) }
    },
    {
        /* Name:  */ "OX", BLUE,
        /* Moves: */ { M(0, -1), M(0, 1), M(1, 0) }
    },
    {
        /* Name:  */ "RABBIT", BLUE,
        /* Moves: */ { M(-1, -1), M(1, 1), M(2, 0) }
    },
    {
        /* Name:  */ "ROOSTER", RED,
        /* Moves: */ { M(-1, -1), M(-1, 0), M(1, 0), M(1, 1) }
    },
    {
        /* Name:  */ "TIGER", BLUE,
        /* Moves: */ { M(0, -1), M(0, 2) }
    }
};

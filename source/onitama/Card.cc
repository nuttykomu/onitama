#include "Card.h"

const int BLUE = 0;
const int RED = 1;

std::vector<Card> CardList = {
    {
        /* Name:  */ "BOAR", RED, 0,
        /* Moves: */ { M(-1, 0), M(0, 1), M(1, 0) }
    },
    {
        /* Name:  */ "COBRA", RED, 1,
        /* Moves: */ { M(-1, 0), M(1, -1), M(1, 1) }
    },
    {
        /* Name:  */ "CRAB", BLUE, 2,
        /* Moves: */ { M(-2, 0), M(0, 1), M(2, 0) }
    },
    {
        /* Name:  */ "CRANE", BLUE, 3,
        /* Moves: */ { M(-1, -1), M(0, 1), M(1, -1) }
    },
    {
        /* Name:  */ "DRAGON", RED, 4,
        /* Moves: */ { M(-2, 1), M(-1, -1), M(1, -1), M(2, 1) }
    },
    {
        /* Name:  */ "EEL", BLUE, 5,
        /* Moves: */ { M(-1, -1), M(-1, 1), M(1, 0) }
    },
    {
        /* Name:  */ "ELEPHANT", RED, 6,
        /* Moves: */ { M(-1, 0), M(-1, 1), M(1, 0), M(1, 1) }
    },
    {
        /* Name:  */ "FROG", RED, 7,
        /* Moves: */ { M(-2, 0), M(-1, 1), M(1, -1) }
    },
    {
        /* Name:  */ "GOOSE", BLUE, 8,
        /* Moves: */ { M(-1, 0), M(-1, 1), M(1, 0), M(1, -1) }
    },
    {
        /* Name:  */ "HORSE", RED, 9,
        /* Moves: */ { M(-1, 0), M(0, -1), M(0, 1) }
    },
    {
        /* Name:  */ "MANTIS", RED, 10,
        /* Moves: */ { M(-1, 1), M(0, -1), M(1, 1) }
    },
    {
        /* Name:  */ "MONKEY", BLUE, 11,
        /* Moves: */ { M(-1, -1), M(-1, 1), M(1, -1), M(1, 1) }
    },
    {
        /* Name:  */ "OX", BLUE, 12,
        /* Moves: */ { M(0, -1), M(0, 1), M(1, 0) }
    },
    {
        /* Name:  */ "RABBIT", BLUE, 13,
        /* Moves: */ { M(-1, -1), M(1, 1), M(2, 0) }
    },
    {
        /* Name:  */ "ROOSTER", RED, 14,
        /* Moves: */ { M(-1, -1), M(-1, 0), M(1, 0), M(1, 1) }
    },
    {
        /* Name:  */ "TIGER", BLUE, 15,
        /* Moves: */ { M(0, -1), M(0, 2) }
    }
};

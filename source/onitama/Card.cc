#include "Card.h"

const int BLUE = 0;
const int RED = 1;

Card CardList[] = {
    {
        /* Name:  */ "BOAR", RED,
        /* Moves: */ { {-1, 0}, {0, 1}, {1, 0} },
    },
    {
        /* Name:  */ "COBRA", RED,
        /* Moves: */ { {-1, 0}, {1, -1}, {1, 1} }
    },
    {
        /* Name:  */ "CRAB", BLUE,
        /* Moves: */ { {-2, 0}, {0, 1}, {2, 0} }
    },
    {
        /* Name:  */ "CRANE", BLUE,
        /* Moves: */ { {-1, -1}, {0, 1}, {1, -1} }
    },
    {
        /* Name:  */ "DRAGON", RED,
        /* Moves: */ { {-2, 1}, {-1, -1}, {1, -1}, {2, 1} }
    },
    {
        /* Name:  */ "EEL", BLUE,
        /* Moves: */ { {-1, -1}, {-1, 1}, {1, 0} }
    },
    {
        /* Name:  */ "ELEPHANT", RED,
        /* Moves: */ { {-1, 0}, {-1, 1}, {1, 0}, {1, 1} }
    },
    {
        /* Name:  */ "FROG", RED,
        /* Moves: */ { {-2, 0}, {-1, 1}, {1, -1} }
    },
    {
        /* Name:  */ "GOOSE", BLUE,
        /* Moves: */ { {-1, 0}, {-1, 1}, {1, 0}, {1, -1} }
    },
    {
        /* Name:  */ "HORSE", RED,
        /* Moves: */ { {-1, 0}, {0, -1}, {0, 1} }
    },
    {
        /* Name:  */ "MANTIS", RED,
        /* Moves: */ { {-1, 1}, {0, -1}, {1, 1} }
    },
    {
        /* Name:  */ "MONKEY", BLUE,
        /* Moves: */ { {-1, -1}, {-1, 1}, {1, -1}, {1, 1} }
    },
    {
        /* Name:  */ "OX", BLUE,
        /* Moves: */ { {0, -1}, {0, 1}, {1, 0} }
    },
    {
        /* Name:  */ "RABBIT", BLUE,
        /* Moves: */ { {-1, -1}, {1, 1}, {2, 0} }
    },
    {
        /* Name:  */ "ROOSTER", RED,
        /* Moves: */ { {-1, -1}, {-1, 0}, {1, 0}, {1, 1} }
    },
    {
        /* Name:  */ "TIGER", BLUE,
        /* Moves: */ { {0, -1}, {0, 2} }
    }
};

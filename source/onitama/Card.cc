#include "Card.h"

std::vector<Card> CARD_LIST = {
    {
        /* Index: */ 0,
        /* Color: */ 🔴,
        /* Name:  */ "BOAR",
        /* Moves: */ {
            Vector(-1,  0),
            Vector( 0, +1),
            Vector(+1,  0)
        }
    },
    {
        /* Index: */ 1,
        /* Color: */ 🔴,
        /* Name:  */ "COBRA",
        /* Moves: */ {
            Vector(-1,  0),
            Vector(+1, -1),
            Vector(+1, +1)
        }
    },
    {
        /* Index: */ 2,
        /* Color: */ 🔵,
        /* Name:  */ "CRAB",
        /* Moves: */ {
            Vector(-2,  0),
            Vector( 0, +1),
            Vector(+2,  0)
        }
    },
    {
        /* Index: */ 3,
        /* Color: */ 🔵,
        /* Name:  */ "CRANE",
        /* Moves: */ {
            Vector(-1, -1),
            Vector( 0, +1),
            Vector(+1, -1)
        }
    },
    {
        /* Index: */ 4,
        /* Color: */ 🔴,
        /* Name:  */ "DRAGON",
        /* Moves: */ {
            Vector(-2, +1),
            Vector(-1, -1),
            Vector(+1, -1),
            Vector(+2, +1)
        }
    },
    {
        /* Index: */ 5,
        /* Color: */ 🔵,
        /* Name:  */ "EEL",
        /* Moves: */ {
            Vector(-1, -1),
            Vector(-1, +1),
            Vector(+1,  0)
        }
    },
    {
        /* Index: */ 6,
        /* Color: */ 🔴,
        /* Name:  */ "ELEPHANT",
        /* Moves: */ {
            Vector(-1,  0),
            Vector(-1, +1),
            Vector(+1,  0),
            Vector(+1, +1)
        }
    },
    {
        /* Index: */ 7,
        /* Color: */ 🔴,
        /* Name:  */ "FROG",
        /* Moves: */ {
            Vector(-2,  0),
            Vector(-1, +1),
            Vector(+1, -1)
        }
    },
    {
        /* Index: */ 8,
        /* Color: */ 🔵,
        /* Name:  */ "GOOSE",
        /* Moves: */ {
            Vector(-1,  0),
            Vector(-1, +1),
            Vector(+1,  0),
            Vector(+1, -1)
        }
    },
    {
        /* Index: */ 9,
        /* Color: */ 🔴,
        /* Name:  */ "HORSE",
        /* Moves: */ {
            Vector(-1,  0),
            Vector( 0, -1),
            Vector( 0, +1)
        }
    },
    {
        /* Index: */ 10,
        /* Color: */ 🔴,
        /* Name:  */ "MANTIS",
        /* Moves: */ {
            Vector(-1, +1),
            Vector( 0, -1),
            Vector(+1, +1)
        }
    },
    {
        /* Index: */ 11,
        /* Color: */ 🔵,
        /* Name:  */ "MONKEY",
        /* Moves: */ {
            Vector(-1, -1),
            Vector(-1, +1),
            Vector(+1, -1),
            Vector(+1, +1)
        }
    },
    {
        /* Index: */ 12,
        /* Color: */ 🔵,
        /* Name:  */ "OX",
        /* Moves: */ {
            Vector( 0, -1),
            Vector( 0, +1),
            Vector(+1,  0)
        }
    },
    {
        /* Index: */ 13,
        /* Color: */ 🔵,
        /* Name:  */ "RABBIT",
        /* Moves: */ {
            Vector(-1, -1),
            Vector(+1, +1),
            Vector(+2,  0)
        }
    },
    {
        /* Index: */ 14,
        /* Color: */ 🔴,
        /* Name:  */ "ROOSTER",
        /* Moves: */ {
            Vector(-1, -1),
            Vector(-1,  0),
            Vector(+1,  0),
            Vector(+1, +1)
        }
    },
    {
        /* Index: */ 15,
        /* Color: */ 🔵,
        /* Name:  */ "TIGER",
        /* Moves: */ {
            Vector( 0, -1),
            Vector( 0, +2)
        }
    }
};
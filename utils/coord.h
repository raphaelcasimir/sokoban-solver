#ifndef COORD_H_INCLUDED
#define COORD_H_INCLUDED

enum
{
    MIN_DIR = 0, TOP = 0, BOTTOM = 1, LEFT = 2, RIGHT = 3, NONE = -1, MAX_DIR = 4       // En semble des directions poossible pour le player
};

struct Coord
{
    static int m_nb_col;

    inline static void coord2D(unsigned short pos, unsigned int& l, unsigned int& c);   // Fonction qui renvoie les coordonnées en 2 dimensions avec la ligne et la colonne
    inline static unsigned short coord1D(unsigned int l, unsigned int c);       // Fnction qui renvoie les coordonnées en 1 dimension

    inline static char getPosDir(int pos)       // Fonction qui détermine la direction en fonction de laersfa position et du nb de colonne
    {
        char dir = NONE;
        if (pos == -1) dir = LEFT;
        else if (pos == 1) dir = RIGHT;
        else if (pos == -m_nb_col) dir = TOP;
        else if (pos == m_nb_col) dir = BOTTOM;

        return dir;
    }

    inline static unsigned short getDirPos(unsigned short pos, char dir);
    inline static unsigned short getOppositeDirPos(unsigned short pos, char dir);
};

inline unsigned short Coord::coord1D(unsigned int l, unsigned int c)
{
    return (l * m_nb_col + c);
}

inline void Coord::coord2D(unsigned short pos, unsigned int& l, unsigned int& c)
{
    l = (pos / m_nb_col);
    c = (pos % m_nb_col);
}

inline unsigned short Coord::getDirPos(unsigned short pos, char dir)
{
    switch (dir)
    {
        case TOP:
            pos -= m_nb_col;
            break;
        case BOTTOM:
            pos += m_nb_col;
            break;
        case LEFT:
            --pos;
            break;
        case RIGHT:
            ++pos;
            break;
    }
    return pos;
}

inline unsigned short Coord::getOppositeDirPos(unsigned short pos, char dir)
{
    switch (dir)
    {
        case TOP:
            pos += m_nb_col;
            break;
        case BOTTOM:
            pos -= m_nb_col;
            break;
        case LEFT:
            ++pos;
            break;
        case RIGHT:
            --pos;
            break;
    }
    return pos;
}

#endif // COORD_H_INCLUDED

/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#ifndef MAZE_H_INCLUDED
#define MAZE_H_INCLUDED

#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <string>
#include <iostream>

// Max size for the field
#define NB_MAX_WIDTH     30
#define NB_MAX_HEIGHT    30

class Graphic;

enum
{
    SPRITE_GROUND = 0, SPRITE_WALL = 1, SPRITE_BOX = 2,
    SPRITE_BOX_PLACED = 3, SPRITE_GOAL = 4, SPRITE_MARIO = 5,
    SPRITE_DEADSQUARE = 9
};

class Maze
{
    private:
        unsigned char m_lig, m_col;
        unsigned short m_pos_player;
        unsigned short m_pos_playerReset; // pour la réinisialisation
        char m_dir_player;
        std::string m_level_path;

        std::vector<unsigned char> m_field; // field
        std::vector<unsigned char> m_fieldReset; // field pour la réinitialisatin du niveau
        std::vector<unsigned short> m_pos_boxes; // box positions
        std::vector<unsigned short> m_pos_goals; // goal positions

        friend std::ostream& operator << (std::ostream& O, const Maze& n);

        bool _load(const std::string& path);

    public:
        bool _canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const;
        bool _isCompleted() const;

        Maze(const std::string& path);
        ~Maze();


        bool init();
        bool updatePlayer(char dir);
        void draw(const Graphic& g) const;
        void resetNiveau(Maze& m);

        // Specific solver functions
        bool solveBFS(Maze m, Graphic& g);
        bool bruteForce(Maze& m, Graphic& g);
        std::map <int, char> bfsMario (Maze mc);
        int mouvementBF(Maze& m, int compteur, Graphic& g);


        // Specific getters for field
        bool isSquareWalkable(unsigned short pos) const;
        bool isSquareGround(unsigned short pos) const;
        bool isSquareBox(unsigned short pos) const;
        bool isSquareGoal(unsigned short pos) const;
        bool isSquareWall(unsigned short pos) const;
        bool isSquareBoxPlaced(unsigned short pos) const;
        std::vector <unsigned short> getKey() const;

        // Other getters
        const std::string& getLevelPath() const;
        unsigned short getPosPlayer() const;
        unsigned int getSize() const;
        unsigned char getCol() const; // Useful
        void setSquare(unsigned short pos, unsigned char s);
        const std::vector<unsigned char>& getField() const;
        const std::vector<unsigned short>& getGoals() const;
        std::vector<unsigned short> getPosBoxes() const;

        // Setter
        void setPlayerPos(unsigned short p);
};

// Inline implementation of getters and setters (DO NOT TOUCH !)

inline void Maze::setPlayerPos(unsigned short p) {
    if (p < this->getSize()) // NB: p always > 0 because unsigned short
        this->m_pos_player = p;
}

inline const std::string& Maze::getLevelPath() const { return this->m_level_path; }
inline const std::vector<unsigned short>& Maze::getGoals() const { return this->m_pos_goals; }
inline const std::vector<unsigned char>& Maze::getField() const { return this->m_field; }

inline unsigned int Maze::getSize() const { return this->m_field.size(); }
inline unsigned char Maze::getCol() const { return this->m_col;} // Added useful getter
inline std::vector <unsigned short> Maze::getPosBoxes() const { return m_pos_boxes; }
inline unsigned short Maze::getPosPlayer() const { return m_pos_player;}

// Makes the map key that characterizes the state of the field, inlined since it's quite short
inline std::vector <unsigned short> Maze::getKey()const {
    std::vector <unsigned short> key;
    key.reserve(sizeof(unsigned short) + this->getPosBoxes().size());
    key.push_back(this->getPosPlayer());
    key.insert(key.end(),this->getPosBoxes().begin(),this->getPosBoxes().end());
    return key;
}

inline void Maze::setSquare(unsigned short pos, unsigned char s)
{
    if (pos < (this->m_lig*this->m_col))
    {
        this->m_field[pos] = s;
    }
}

inline bool Maze::isSquareWalkable(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_GROUND || this->m_field[pos] == SPRITE_GOAL) ? true : false);
}

inline bool Maze::isSquareGround(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_GROUND) ? true : false);
}

inline bool Maze::isSquareBox(unsigned short pos) const
{
    return ((this->m_field[pos] == SPRITE_BOX || this->m_field[pos] == SPRITE_BOX_PLACED) ? true : false);
}

inline bool Maze::isSquareGoal(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_GOAL ? true : false);
}

inline bool Maze::isSquareWall(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_WALL ? true : false);
}

inline bool Maze::isSquareBoxPlaced(unsigned short pos) const
{
    return (this->m_field[pos] == SPRITE_BOX_PLACED ? true : false);
}

#endif // MAZE_H_INCLUDED

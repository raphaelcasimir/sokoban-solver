/************************************************************
Sokoban project - Maze file
Copyright Florent DIEDLER
Date : 27/02/2016

Please do not remove this header, if you use this file !
************************************************************/

#include "maze.h"
#include "graphic.h"
#include "utils/console.h"
#include "utils/coord.h"
#include <fstream>
#include <iomanip>


Maze::Maze(const std::string& path)
    : m_lig(0), m_col(0), m_pos_player(0), m_dir_player(TOP), m_level_path(path)
{
}

Maze::~Maze()
{
}

bool Maze::init()
{
    bool res = this->_load(this->m_level_path);
    if (!res)
    {
        std::cerr << "Cannot load maze... Check file : " << this->m_level_path << std::endl;
        return false;
    }

    return res;
}

// Check if all boxes are on a goal
bool Maze::_isCompleted() const
{
    for (unsigned int i=0; i<this->m_pos_boxes.size(); ++i)
    {
        if (!this->isSquareBoxPlaced(this->m_pos_goals[i]))
            return false;
    }
    return true;
}

// Check if we can push a box in a direction
// INPUT: position of the box to check, direction,
// OUTPUT : the position of the box after pushing
//      TRUE if all goes right otherwise FALSE
bool Maze::_canPushBox(unsigned short posBox, char dir, unsigned short& newPosBox) const
{
    // Check if this position is a box !
    if (!this->isSquareBox(posBox))
        return false;

    // Compute new position according to push direction
    newPosBox = Coord::getDirPos(posBox, dir);

    // Can we push the box ?
    return this->isSquareWalkable(newPosBox);
}

// Load a maze from a file (DO NOT TOUCH)
bool Maze::_load(const std::string& path)
{
    std::vector<unsigned short> tmpPosBoxes;
    std::ifstream ifs(path.c_str());
    if (ifs)
    {
        std::vector<std::string> lines;
        std::string line;
        while (std::getline(ifs, line))
        {
            lines.push_back(line);
            this->m_lig++;
            this->m_col = (this->m_col < line.size() ? line.size() : this->m_col);
        }
        ifs.close();

        if (this->m_col > NB_MAX_WIDTH || this->m_lig > NB_MAX_HEIGHT)
        {
            std::cerr << "Maze::load => Bad formatting in level data..." << std::endl;
            return false;
        }

        Coord::m_nb_col = this->m_col;
        for (unsigned int i=0; i<lines.size(); i++)
        {
            //LDebug << "Maze::load => Reading : " << lines[i];
            for (unsigned int j=0; j<this->m_col; j++)
            {
                if (j < lines[i].size())
                {
                    bool both = false;
                    unsigned short pos = Coord::coord1D(i, j);
                    unsigned char s = (unsigned char)(lines[i][j] - '0');

                    // Need to add a goal and a box ;)
                    if (s == SPRITE_BOX_PLACED)
                    {
                        both = true;
                    }

                    if (s == SPRITE_GOAL || both)
                    {
                        this->m_pos_goals.push_back(pos);
                    }
                    if (s == SPRITE_BOX || both)
                    {
                        tmpPosBoxes.push_back(pos);
                    }

                    // Assign player position
                    if (s == SPRITE_MARIO)
                    {
                        this->m_pos_player = pos;
                        this->m_pos_playerReset = pos;
                        //LDebug << "\tAdding player pos (" << pos << ")";
                        s = SPRITE_GROUND;
                    }

                    // Add this value in the field
                    this->m_field.push_back(s);
                    this->m_fieldReset.push_back(s);
                }
                else
                {
                    // Here - Out of bound
                    this->m_field.push_back(SPRITE_GROUND);
                    this->m_fieldReset.push_back(SPRITE_GROUND);
                }
            }
        }

        // Copy box position
        this->m_pos_boxes.resize(tmpPosBoxes.size());
        for (unsigned int i=0; i<tmpPosBoxes.size(); ++i)
        {
            this->m_pos_boxes[i] = tmpPosBoxes[i];
        }

        return (this->m_pos_boxes.size() == this->m_pos_goals.size());
    }
    else
    {
        std::cerr << "Maze::load => File does not exist..." << std::endl;
    }

    return false;
}


void Maze::resetNiveau(Maze& m)     // Fonction qui reset le niveau, ave cles coordonnées de base du niveau chargé
{
<<<<<<< HEAD
    for(unsigned int i=0; i<m.m_field.size(); i++)
        m.m_field[i]=m.m_fieldReset[i];             // Position de m_field copié dedans

    m.m_pos_player=m.m_pos_playerReset;     // Position initiale deesd de player

    for (unsigned int i=0; i<m.m_pos_playerBruteforceTab.size(); i++)
        m.m_pos_playerBruteforceTab.pop_back();     // Vecteur de position de player qui reset

    for (unsigned int j=0; j<m.m_fieldBruteforceTab.size(); j++)
        m.m_fieldBruteforceTab.pop();       // Pile de position du niveau m_field
}

void Maze::setFieldBruteforce(Maze& m)
{
    for(unsigned int i=0; i<m.m_field.size(); i++)
        m.m_fieldBruteforce[i]=m.m_field[i];            //Réinirital k ekl sation du field avec la position précédente, on reprend le niveau ua déplacment précedent

    m.m_fieldBruteforceTab.push(m.m_fieldBruteforce);           // On rentre le veteur dans la pile
    m.m_pos_playerBruteforceTab.push_back(m.m_pos_player);      // On rentre la position de player dans le vecteur
}

void Maze::retourArriere(Maze& m)
{
    std::vector<unsigned char> m_fieldTampon=m.m_fieldBruteforceTab.top();  // Vecteur tampon qui sert à reinisialiser  la position du niveau au mouvement précédent            ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb ekljhgbnnjhhghvncgfbvnb

    for(unsigned int i=0; i<m.m_field.size(); i++)
        m.m_field[i]=m_fieldTampon[i];

    m.m_pos_player=m.m_pos_playerBruteforceTab[m.m_pos_playerBruteforceTab.size()-1];
    m.m_pos_playerBruteforceTab.pop_back();
    m.m_fieldBruteforceTab.pop();
=======
    for(unsigned int i=0; i<m_field.size(); i++)
        m_field[i]=m_fieldReset[i];

    m_pos_player=m_pos_playerReset;
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
}

int Maze::mouvementBF(Maze& m, int compteur, Graphic& g)    // Fonction qui donne le mouvement de player dans les 4 directions de base
{
    bool win=false;

    for (int i=0; i<4; i++)
        {
<<<<<<< HEAD
        m.setFieldBruteforce(m);        // On enregistre la positio actuelle pour pouvoir revenir en arriere qi le niveau n'est pas termine

        if (g.keyGet(KEY_ESC))      // Si on appuye sur ESC on quitte le brute force
            return -2;

            if (i==0)           // On essaye les quatre direections une par une
=======
            if (i==0)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                win = updatePlayer(TOP);            // Mouvement TOP
                std::cout<<"^ = "<<i<<std::endl;                //Affichage dans la console puis sur allegro
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
<<<<<<< HEAD
                rest(10);
                if (win==true)
                    return -1;
                if (compteur>0)             // Si après le déplacement le niveau n'est pas terminé on relance al fonction récursive
=======
                rest(1000);
                if (compteur>=1)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
                {
                    compteur--;
                    compteur=mouvementBF(m,compteur, g);
                }
            }

            if (i==1)           // On essaye les quatre direections une par une
            {
                win = updatePlayer(BOTTOM);            // Mouvement BOTTOM
                std::cout<<"B = "<<i<<std::endl;                //Affichage dans la console puis sur allegro
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
<<<<<<< HEAD
                rest(10);
                if (compteur>0)             // Si après le déplacement le niveau n'est pas terminé on relance al fonction récursive
=======
                rest(1000);
                if (compteur>=1)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
                {
                    compteur--;
                    compteur=mouvementBF(m,compteur, g);
                }
            }

            if (i==3)           // On essaye les quatre direections une par une
            {
                win = updatePlayer(RIGHT);                      // Mouvement RIGHT
                std::cout<<"> = "<<i<<std::endl;                //Affichage dans la console puis sur allegro
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
<<<<<<< HEAD
                rest(10);
                if (compteur>0)             // Si après le déplacement le niveau n'est pas terminé on relance al fonction récursive
=======
                rest(1000);
                if (compteur>=1)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
                {
                    compteur--;
                    compteur=mouvementBF(m,compteur, g);
                }
            }

            if (i==2)           // On essaye les quatre direections une par une
            {
                win = updatePlayer(LEFT);                           // Mouvement LEFT
                std::cout<<"< = "<<i<<std::endl;                //Affichage dans la console puis sur allegro
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
<<<<<<< HEAD
                rest(10);
                if (compteur>0)             // Si après le déplacement le niveau n'est pas terminé on relance al fonction récursive
=======
                rest(1000);
                if (compteur>=1)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
                {
                    compteur--;
                    compteur=mouvementBF(m,compteur, g);
                }
            }
<<<<<<< HEAD
            if (win==false&&compteur==0&&i==3&&m.m_fieldBruteforceTab.size()>1)
            {
                m.retourArriere(m);
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
                rest(10);
            }
            if (win==false&&compteur==0)            // Si le niveau n'est pas terminé après le dernier déplacement on revient en arriere
=======

            if (win==false&&compteur==0)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                m.resetNiveau(m);
                g.clear();
                m.draw(g);
                g.display(Coord::m_nb_col);
                rest(1000);
            }

<<<<<<< HEAD
            if (_isCompleted())     // On verifie si le niveau est terminé
=======
            if (win==true)
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
                return -1;

        }
        compteur++;

    return compteur;
}

bool Maze::bruteForce(Maze& m, Graphic& g)
{
    int compteur=0;

    while (compteur!=-1||compteur==-2)
    {
        std::cout<<"cpt = "<<compteur<<std::endl;
        compteur = mouvementBF(m, compteur, g);
    }

<<<<<<< HEAD
    if (compteur==-1)
        return true;
    if (compteur==-2)
        return false;

=======
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
    return true;
}



bool Maze::updatePlayer(char dir)               // Cette méthode sert à déplacer le joueur manuellement avec les flèches du clavier
{
    if (dir < 0 || dir > MAX_DIR)               // On verifie que la direction est cohérente
    {
        std::cerr << "Maze::updatePlayer => Direction not correct... " << +dir << std::endl;
        return false;
    }

    // Implement player moving and pushing here

    m_dir_player=dir;
    unsigned short pos=Coord::getDirPos(m_pos_player,dir);
    unsigned short newPosBox=Coord::getDirPos(pos,dir);

    switch (dir)            // Ici on fait un switch pour les 4 directions possibles
    {
    case TOP:
        if (isSquareWalkable(pos))              // On verifie que la prochaine case est vide
            m_pos_player=pos;

        else if (isSquareBox(pos)&&_canPushBox(pos,dir,newPosBox))      // On verifie que la prochaine case est une caisse et qu'elle est poussables
        {
<<<<<<< HEAD
            if (isSquareGround(newPosBox)&&isSquareBoxPlaced(pos))      // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGround(newPosBox)&&(!isSquareBoxPlaced(pos)))      // Ici on s'occupe des caisses pas encore placées
=======
            if (isSquareGround(newPosBox))
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GROUND);
            }
            if (isSquareGoal(newPosBox)&&isSquareBoxPlaced(pos))        // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGoal(newPosBox)&&(!isSquareBoxPlaced(pos)))     // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GROUND);
            }

            m_pos_player=pos;
        }
        break;

    case BOTTOM:
        if (isSquareWalkable(pos))          // On verifie que la prochaine case est vide
            m_pos_player=pos;

        else if (isSquareBox(pos)&&_canPushBox(pos,dir,newPosBox))          // On verifie que la prochaine case est une caisse et qu'elle est poussables
        {
<<<<<<< HEAD
            if (isSquareGround(newPosBox)&&isSquareBoxPlaced(pos))          // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGround(newPosBox)&&(!isSquareBoxPlaced(pos)))       // Ici on s'occupe des caisses pas encore placées
=======
            if (isSquareGround(newPosBox))
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GROUND);
            }
            if (isSquareGoal(newPosBox)&&isSquareBoxPlaced(pos))            // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGoal(newPosBox)&&(!isSquareBoxPlaced(pos)))         // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GROUND);
            }

            m_pos_player=pos;
        }
        break;

    case RIGHT:
        if (isSquareWalkable(pos))              // On verifie que la prochaine case est vide
            m_pos_player=pos;

        else if (isSquareBox(pos)&&_canPushBox(pos,dir,newPosBox))          // On verifie que la prochaine case est une caisse et qu'elle est poussables
        {
<<<<<<< HEAD
            if (isSquareGround(newPosBox)&&isSquareBoxPlaced(pos))          // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGround(newPosBox)&&(!isSquareBoxPlaced(pos)))       // Ici on s'occupe des caisses pas encore placées
=======
            if (isSquareGround(newPosBox))
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GROUND);
            }
            if (isSquareGoal(newPosBox)&&isSquareBoxPlaced(pos))        // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGoal(newPosBox)&&(!isSquareBoxPlaced(pos)))     // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GROUND);
            }

            m_pos_player=pos;
        }
        break;

    case LEFT:
        if (isSquareWalkable(pos))                  // On verifie que la prochaine case est vide
            m_pos_player=pos;

        else if (isSquareBox(pos)&&_canPushBox(pos,dir,newPosBox))          // On verifie que la prochaine case est une caisse et qu'elle est poussables
        {
<<<<<<< HEAD
            if (isSquareGround(newPosBox)&&isSquareBoxPlaced(pos))          // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGround(newPosBox)&&(!isSquareBoxPlaced(pos)))       // Ici on s'occupe des caisses pas encore placées
=======
            if (isSquareGround(newPosBox))
>>>>>>> b911a656e2497472068c367cd9c3139faaf18838
            {
                setSquare(newPosBox,SPRITE_BOX);
                setSquare(pos,SPRITE_GROUND);
            }
            if (isSquareGoal(newPosBox)&&isSquareBoxPlaced(pos))        // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GOAL);
            }
            if (isSquareGoal(newPosBox)&&(!isSquareBoxPlaced(pos)))         // Ici on s'occupe des caisses pas encore placées
            {
                setSquare(newPosBox,SPRITE_BOX_PLACED);
                setSquare(pos,SPRITE_GROUND);
            }

            m_pos_player=pos;
        }
        break;
    }

    if (_isCompleted())
        return true;

    return false;
}

// Display maze on screen with Allegro
void Maze::draw(const Graphic& g) const
{
    for(unsigned int i=0; i<this->getSize(); i++)
    {
        unsigned int l = 0, c = 0;
        Coord::coord2D(i, l, c);

        if (i == this->m_pos_player)
        {
            g.drawT(g.getSpritePlayer(this->m_dir_player), c, l);
        }
        else
        {
            g.drawT(g.getSprite(this->m_field[i]), c, l);
        }
    }
}

// DO NOT TOUCH !
// Overload function for displaying debug information
// about Maze class
std::ostream& operator << (std::ostream& O, const Maze& m)
{
    unsigned int l, c;
    int i = 0;
    Coord::coord2D(m.m_pos_player, l, c);
    O << "Player position " << m.m_pos_player << " (" << l << "," << c << ")" << std::endl;
    O << "Field Size " << +m.m_lig << " x " << +m.m_col << " = " << m.getSize() << std::endl;
    O << "Field Vector capacity : " << m.m_field.capacity() << std::endl;
    O << "Field array : " << std::endl << std::endl;
    for(unsigned int l=0; l<m.getSize(); l++)
    {
        if (l == m.m_pos_player) Console::getInstance()->setColor(_COLOR_YELLOW);
        else if (m.isSquareWall(l)) Console::getInstance()->setColor(_COLOR_PURPLE);
        else if (m.isSquareBoxPlaced(l) || m.isSquareGoal(l)) Console::getInstance()->setColor(_COLOR_GREEN);
        else if (m.isSquareBox(l)) Console::getInstance()->setColor(_COLOR_BLUE);
        else if (m.m_field[l] == SPRITE_DEADSQUARE) Console::getInstance()->setColor(_COLOR_RED);
        else Console::getInstance()->setColor(_COLOR_WHITE);

        O << std::setw(2) << +m.m_field[l] << " "; // + => print as "int"

        if ((l+1) % m.m_col == 0)
        {
            O << std::endl;
        }
    }
    Console::getInstance()->setColor(_COLOR_DEFAULT);

    O << std::endl;
    O << "Box position : " << std::endl;
    for (unsigned int i=0; i<m.m_pos_boxes.size(); i++)
    {
        Coord::coord2D(m.m_pos_boxes[i], l, c);
        O << "\t" << "Box #" << i << " => " << std::setw(3) << m.m_pos_boxes[i] << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
    }

    O << std::endl;
    O << "Goal position : " << std::endl;
    for (const auto& goal : m.m_pos_goals)
    {
        unsigned int l, c;
        Coord::coord2D(goal, l, c);
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_GREEN);
        O << "\t" << "Goal #" << i << " => " << std::setw(3) << goal << std::setw(2) << " (" << l << "," << c << ")" << std::endl;
        if (m.isSquareBoxPlaced(goal)) Console::getInstance()->setColor(_COLOR_DEFAULT);
        i++;
    }

    return O;
}
void Maze::detectDeadlocks()
{
    char dir = NONE;
    unsigned short posActual;
    bool range(true);
    unsigned int lig=0;
    unsigned int col=0;
    std::vector<unsigned short> vecteur_de_coins;

    for(unsigned short i(0); i<m_field.size(); i++)
    {
        if((isSquareWalkable(i) || isSquareBox(i))&&(!isSquareGoal(i)))
        {

            Coord::coord2D(i,lig,col);
            if((lig!=0)&&(lig!=m_lig)&&(col!=0)&&(col!=m_col))
            {
                if((isSquareWall(Coord::getDirPos(i,dir+1)))&&(((isSquareWall(Coord::getDirPos(i,dir+4)))||(isSquareWall(Coord::getDirPos(i,dir+3))))))
                {
                    setSquare(i,SPRITE_DEADSQUARE);
                    vecteur_de_coins.push_back(i);
                }
                else if((isSquareWall(Coord::getDirPos(i,dir+2)))&&(((isSquareWall(Coord::getDirPos(i,dir+4)))||(isSquareWall(Coord::getDirPos(i,dir+3))))))
                {
                    setSquare(i,SPRITE_DEADSQUARE);
                    vecteur_de_coins.push_back(i);
                }
            }
        }
    }
    while(!vecteur_de_coins.empty())
    {
        for(char direc=TOP; direc!=TOP+4; direc++)
        {
            if((isSquareWall(Coord::getDirPos(vecteur_de_coins.back(),direc))))
            {
                //Ajouter la possibilite de trouver un cul de sac et de remplir  tout le couloir qui mene au cul de sac
                if((direc<=1)&&(isSquareWall(Coord::getDirPos(vecteur_de_coins.back(),LEFT))))
                {
                    posActual=vecteur_de_coins.back();
                    std::cout << "Coin TOP-LEFT ou BOTTOM-LEFT : " << posActual << std::endl;
                    range=true;
                    while((isSquareWall(Coord::getDirPos(posActual,direc)) || isSquareWall(Coord::getDirPos(posActual,(direc+1)%2)))
                            &&(!isSquareWall(Coord::getDirPos(posActual,RIGHT))))
                    {
                        posActual=Coord::getDirPos(posActual,RIGHT);
                        if((isSquareGoal(posActual))||(isSquareBoxPlaced(posActual)))
                            range=false;
                    }
                    if(isSquareDeadSquare(posActual)&& range)
                    {
                        while(!isSquareWall(Coord::getDirPos(posActual,LEFT)))
                        {
                            posActual=Coord::getDirPos(posActual,LEFT);
                            if(isSquareGround(posActual)) setSquare(posActual,SPRITE_DEADSQUARE);
                        }
                    }
                }
                else if(((direc>=2)&&(direc<=3))&&(isSquareWall(Coord::getDirPos(vecteur_de_coins.back(),TOP))))
                {
                    posActual=vecteur_de_coins.back();
                    range=true;
                    while((isSquareWall(Coord::getDirPos(posActual,direc)) || isSquareWall(Coord::getDirPos(posActual, ((direc+1)%2)+2)))
                        &&(!isSquareWall(Coord::getDirPos(posActual,BOTTOM))))
                    {
                        posActual=Coord::getDirPos(posActual,BOTTOM);
                        if((isSquareGoal(posActual))||(isSquareBoxPlaced(posActual)))
                            range=false;
                    }
                    if(isSquareDeadSquare(posActual)&& range)
                    {
                        while(!isSquareWall(Coord::getDirPos(posActual,TOP)))
                        {
                            posActual=Coord::getDirPos(posActual,TOP);
                            if(isSquareGround(posActual)) setSquare(posActual,SPRITE_DEADSQUARE);
                        }
                    }
                }
            }
        }
        vecteur_de_coins.pop_back();
    }
}

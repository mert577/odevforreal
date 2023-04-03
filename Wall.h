#ifndef WALL_H
#define WALL_H

class Wall
{
public:
    int row;
    int col;
    Wall(int row, int col, bool isBroken = false)
    {
        this->row = row;
        this->col = col;
        this->isBroken = isBroken;
    }

    void breakeWall()
    {
        //  std::cout << "Wall is broken" << std::endl;
        isBroken = true;
    }

    bool isBrokenWall()
    {
        return isBroken;
    }

private:
    bool isBroken;
};

#endif // WALL_H
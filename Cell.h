#ifndef CELL_H
#define CELL_H

#include "Wall.h"
#include "LinkedList.h"

class Cell
{
public:
    Cell(int col, int row)
        : row(row), col(col), up(nullptr), down(nullptr), left(nullptr), right(nullptr) {}

    int getRow() const { return row; }
    int getCol() const { return col; }
    bool isVisited() const { return visited; }

    void SetWalls(Wall *up, Wall *down, Wall *left, Wall *right)
    {
        this->up = up;
        this->down = down;
        this->left = left;
        this->right = right;
    }

    int getWallDirection(Wall *wall)
    {

        if (wall == up)
            return 0;
        else if (wall == down)
            return 1;
        else if (wall == left)
            return 2;
        else if (wall == right)
            return 3;
        else
            return -1;
    }

    void BreakWall(Wall *wall)
    {

        if (numberOfWalls == 0)
            return;

        if (wall == up)
            up->breakeWall();
        else if (wall == down)
            down->breakeWall();
        else if (wall == left)
            left->breakeWall();
        else if (wall == right)
            right->breakeWall();

        numberOfWalls--;
    }

    LinkedList<Wall *> getUnBrokenWalls(int rows, int cols)
    {
        LinkedList<Wall *> unBrokenWalls;

        if (!up->isBrokenWall() && up->row != 0)
            unBrokenWalls.prepend(up);
        if (!down->isBrokenWall() && down->row != rows)
            unBrokenWalls.prepend(down);
        if (!left->isBrokenWall() && left->col != 0)
            unBrokenWalls.prepend(left);
        if (!right->isBrokenWall() && right->col != cols)
            unBrokenWalls.prepend(right);

        return unBrokenWalls;
    }

    Wall *getUpWall()
    {
        return up;
    }

    Wall *getDownWall()
    {
        return down;
    }

    Wall *getLeftWall()
    {
        return left;
    }

    Wall *getRightWall()
    {
        return right;
    }

    int getUp()
    {

        if (up->isBrokenWall())
            return 0;
        else
            return 1;
    }

    int getDown()
    {

        if (down->isBrokenWall())
            return 0;
        else
            return 1;
    }

    int getLeft()
    {

        if (left->isBrokenWall())
            return 0;
        else
            return 1;
    }

    int getRight()
    {

        if (right->isBrokenWall())
            return 0;
        else
            return 1;
    }

    void setVisited(bool visited)
    {
        this->visited = visited;
    }

private:
    bool visited = false;
    int row;
    int col;

    int numberOfWalls = 4;
    Wall *up;
    Wall *down;
    Wall *left;
    Wall *right;
};

#endif // CELL_H
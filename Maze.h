#ifndef MAZE_H
#define MAZE_H

#include "Cell.h"
#include "Stack.h"
#include "LinkedList.h"

class Maze
{

public:
    Maze(int rows, int cols)
    {
        this->rows = rows;
        this->cols = cols;
    }
    ~Maze()
    {
        // delete all cells
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                delete cells.get(i)->get(j);
            }

            delete cells.get(i);
        }

        // delete all wall columns
        for (int i = 0; i < cols + 1; i++)
        {
            delete wallColumns.get(i);
        }

        // delete all wall rows
        for (int i = 0; i < rows + 1; i++)
        {
            delete wallRows.get(i);
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }

    void initilizeMaze()
    {

        // number of wall columns is equal to columns + 1
        for (int i = 0; i < cols + 1; i++)
        {
            // the number of walls in each column is rows
            LinkedList<Wall *> *column = new LinkedList<Wall *>();
            for (int j = 0; j < rows; j++)
            {
                Wall *wall = new Wall(i, j);
                column->append(wall);
            }
            wallColumns.append(column);
        }

        std::cout << "Wall columns initialized" << std::endl;

        // number of wall rows is equal to rows + 1
        for (int i = 0; i < rows + 1; i++)
        {
            // the number of walls in each row is columns
            LinkedList<Wall *> *row = new LinkedList<Wall *>();
            for (int j = 0; j < cols; j++)
            {
                Wall *wall = new Wall(i, j);
                row->append(wall);
            }
            wallRows.append(row);
        }

        std::cout << "Wall rows initialized" << std::endl;

      
        for (int i = 0; i < cols; i++)
        {
            LinkedList<Cell*>* column = new LinkedList<Cell *>();
            std::cout << "Cells rows initiaed" << std::endl;
            for (int j = 0; j < rows; j++)
            {
                Cell* cell = new Cell(i, j);

                std::cout << "Cell created x: " << cell->getCol() << " y: " << cell->getRow() << std::endl;
                cell->SetWalls(wallRows.get(j + 1)->get(i), wallRows.get(j)->get(i), wallColumns.get(i)->get(j), wallColumns.get(i + 1)->get(j));
                column->append(cell);
            }
            cells.append(column);
        }

      
        std::cout << "Cells initialized" << std::endl;
    }

    void DebugMaze()
    {
        initilizeMaze();

        BreakWallOfCell(0, 0, 0);
        BreakWallOfCell(2, 2, 3);
    }
    /*Start with an initially empty stack.
    2. Push (0,0) cell to your stack.
    3. Use the top element (currentCell) in the stack to choose the next cell to be added to your maze.
    4. Choose a random wall of the currentCell to add a new unvisited cell to the maze.
    5. Knock down the wall and add the new cell to the stack.
    6. If no wall exists to knock down for the currentCell, backtrack using the stack until you find a cell
    which has an unvisited neighbor cell.
    7. Continue steps 3-6 until no cell remains unvisited.*/

    void generateMaze()
    {

        initilizeMaze();
        std::cout << "Maze initialized" << std::endl;
        Stack<Cell *> S;
        Cell *firstCell = cells.get(0)->get(0);
        S.push(firstCell);
         LinkedList<Cell *> unVisitedNeighbours;
        while (!S.empty())
        {
            Cell *currentCell = S.top();
            std::cout << "1k";
           
            unVisitedNeighbours.clear();

            int  zart=0;
            if(currentCell->getCol() > 0)
            {
                
                Cell *leftCell = cells.get(currentCell->getCol() - 1)->get(currentCell->getRow());
                if(!leftCell->isVisited())
                {
                         std::cout << "2k";
                    unVisitedNeighbours.append(leftCell);
                    zart++;
                }
            }

            if(currentCell->getCol() < cols - 1)
            {
                Cell *rightCell = cells.get(currentCell->getCol() + 1)->get(currentCell->getRow());
                if(!rightCell->isVisited())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(rightCell);
                    zart++;
                }
            }

            if(currentCell->getRow() > 0)
            {
                Cell *upCell = cells.get(currentCell->getCol())->get(currentCell->getRow() - 1);
                if(!upCell->isVisited())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(upCell);
                    zart++;
                }
            }

            if(currentCell->getRow() < rows - 1)
            {
                Cell *downCell = cells.get(currentCell->getCol())->get(currentCell->getRow() + 1);
                if(!downCell->isVisited())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(downCell);
                    zart++;
                }
            }

            


                

            std::cout << "3k";
            if (zart>0)
            {

                int randomIndex = rand() % unVisitedNeighbours.getSize();
                Cell *randomNeighbour = unVisitedNeighbours.get(randomIndex);

                Wall *wallToBreak = getNeighbouringWall(currentCell, randomNeighbour);
                wallToBreak->breakeWall();

                std::cout << "New  cell  will badded to stack";
                S.push(randomNeighbour);
                randomNeighbour->setVisited(true);

                std::cout << "New cell added to stack";
            }
            else
            {
                S.pop();
            }
        }

        std::cout << "Maze generated" << std::endl;
    }

    void BreakWallOfCell(int col, int row, int wallIndex)
    {
        Cell *cell = cells.get(col)->get(row);

        if (wallIndex == 0)
        {
            cell->getUpWall()->breakeWall();
        }
        else if (wallIndex == 1)
        {
            cell->getDownWall()->breakeWall();
        }
        else if (wallIndex == 2)
        {
            cell->getLeftWall()->breakeWall();
        }
        else if (wallIndex == 3)
        {
            cell->getRightWall()->breakeWall();
        }
    }

    LinkedList<Cell *> getUnVisitedNeigbours(Cell *cell)
    {
        LinkedList<Cell *> unVisitedNeighbours;
        int cellCol = cell->getCol();
        int cellRow = cell->getRow();

        if (cellCol > 0)
        {
            Cell *leftCell = cells.get(cellCol - 1)->get(cellRow);
            if (!leftCell->isVisited())
            {
                unVisitedNeighbours.append(leftCell);
            }
        }
        if (cellCol < cols - 1)
        {
            Cell *rightCell = cells.get(cellCol + 1)->get(cellRow);
            if (!rightCell->isVisited())
            {
                unVisitedNeighbours.append(rightCell);
            }
        }
        if (cellRow > 0)
        {
            Cell *upCell = cells.get(cellCol)->get(cellRow - 1);
            if (!upCell->isVisited())
            {
                unVisitedNeighbours.append(upCell);
            }
        }
        if (cellRow < rows - 1)
        {
            Cell *downCell = cells.get(cellCol)->get(cellRow + 1);
            if (!downCell->isVisited())
            {
                unVisitedNeighbours.append(downCell);
            }
        }

        return unVisitedNeighbours;
    }

    Wall *getNeighbouringWall(Cell *cell1, Cell *cell2)
    {
        int cell1Col = cell1->getCol();
        int cell1Row = cell1->getRow();
        int cell2Col = cell2->getCol();
        int cell2Row = cell2->getRow();

        if (cell1Col == cell2Col)
        {
            if (cell1Row > cell2Row)
            {
                return cell1->getDownWall();
            }
            else
            {
                return cell1->getUpWall();
            }
        }
        else
        {
            if (cell1Col > cell2Col)
            {
                return cell1->getLeftWall();
            }
            else
            {
                return cell1->getRightWall();
            }
        }
    }

    void ResetMazeVisited()
    {
        for (int i = 0; i < cols; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                cells.get(i)->get(j)->setVisited(false);
            }
        }

        std::cout << "Maze reset" << std::endl;
    }

    friend void printMaze(Maze *maze);
    friend void printMazeToFile(Maze *maze, std::string fileName);
    friend void SolveMaze(int startCol, int startRow, int endCol, int EndRow, Maze *mazeToSolve, int id);

    // print each cell with its walls in the following format:
    //  x=0 y=0 u=0 d=0 l=0 r=0
    // Note that the walls are represented by 1 if they are not broken and 0 if they are broken

private:
    int rows;
    int cols;
    LinkedList<LinkedList<Cell *> *> cells;
    LinkedList<LinkedList<Wall *> *> wallColumns;
    LinkedList<LinkedList<Wall *> *> wallRows;
};

#endif MAZE_H
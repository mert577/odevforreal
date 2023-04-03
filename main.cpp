#include <iostream>
#include <fstream>
#include <string>
#include "Maze.h"

int main() {


    //asks the user three inputs, K, M, and N 
    //K is the number of mazes to generate
    //M is the number of rows in each maze
    //N is the number of columns in each maze

    int K, M, N;
    std::cout << "Enter the number of mazes to generate: ";
    std::cin >> K;
    std::cout << "Enter the number of rows in each maze: ";
    std::cin >> M;
    std::cout << "Enter the number of columns in each maze: ";
    std::cin >> N;



    LinkedList<Maze *> mazes;
    //generates K mazes with M rows and N columns
    for (int i = 0; i < K; i++)
    {
       //   std::cout<<"start generating"<<std::endl;
        Maze* maze = new Maze(M, N);
        maze->generateMaze();
       //  maze->initilizeMaze();
      // maze.DebugMaze();
        //prints the maze to a file named maze_K.txt
    
       std::string fileName = "maze_" + std::to_string(i) + ".txt";
        printMazeToFile(maze, fileName);

         mazes.append(maze);

      //  std::cout<<"maze_"<<i<<".txt"<<std::endl;
    //    printMaze(maze);
    }
    
    //ask the user which maze to solve
    int mazeToSolve;
    std::cout << "Enter the id of the maze to solve: ";
    std::cin >> mazeToSolve;

    //ask the user for the start and end points
    int startCol, startRow, endCol, endRow;

    std::cout << "Enter the start column: ";
    std::cin >> startCol;
    std::cout << "Enter the start row: ";
    std::cin >> startRow;
    std::cout << "Enter the end column: ";
    std::cin >> endCol;
    std::cout << "Enter the end row: ";
    std::cin >> endRow;


    Maze* maze = mazes.get(mazeToSolve);
    std::cout<<"Maze chosen"<<std::endl;
    //solve the mazes
    SolveMaze(startCol, startRow, endCol, endRow, maze,mazeToSolve );


    return 0;
}


/*1. Start with an initially empty stack.
2. Push the entry cell to your stack (will be entered by the user).
3. Use the top element in the stack to choose the next cell to visit.
4. If you cannot find any cell to go, backtrack using the stack until you find an unvisited cell to go.
5. Continue steps 3-4 until you reach the exit point.*/
 void SolveMaze(int startCol,int startRow, int endCol, int endRow, Maze* mazeToSolve, int id){
 

    mazeToSolve->ResetMazeVisited();

    Stack<Cell*> solveStack;
    Cell* startCell = mazeToSolve->cells.get(startCol)->get(startRow);
    startCell->setVisited(true);
    std::cout<<"Start Cell"<<std::endl;
    Cell* endCell = mazeToSolve->cells.get(endCol)->get(endRow);
    std::cout<<"End Cell"<<std::endl;

    solveStack.push(startCell);

    while(solveStack.top() != endCell){
         Cell *currentCell = solveStack.top();
        
         LinkedList<Cell*> unVisitedNeighbours;

         int zart =0;
           if(currentCell->getCol() > 0)
            {
                
                Cell *leftCell = mazeToSolve->cells.get(currentCell->getCol() - 1)->get(currentCell->getRow());
               
                
                if(!leftCell->isVisited()&& mazeToSolve->getNeighbouringWall(currentCell,leftCell)->isBrokenWall() )
                {
                    std::cout << "2k";
                    unVisitedNeighbours.append(leftCell);
                    zart++;
                }
            }

            if(currentCell->getCol() <  mazeToSolve->cols - 1)
            {
                Cell *rightCell =  mazeToSolve->cells.get(currentCell->getCol() + 1)->get(currentCell->getRow());
                if(!rightCell->isVisited() && mazeToSolve->getNeighbouringWall(currentCell,rightCell)->isBrokenWall())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(rightCell);
                    zart++;
                }
            }

            if(currentCell->getRow() > 0)
            {
                Cell *upCell =  mazeToSolve->cells.get(currentCell->getCol())->get(currentCell->getRow() - 1);
                if(!upCell->isVisited() && mazeToSolve->getNeighbouringWall(currentCell,upCell)->isBrokenWall())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(upCell);
                    zart++;
                }
            }

            if(currentCell->getRow() <  mazeToSolve->rows - 1)
            {
                Cell *downCell =  mazeToSolve->cells.get(currentCell->getCol())->get(currentCell->getRow() + 1);
                if(!downCell->isVisited() && mazeToSolve->getNeighbouringWall(currentCell,downCell)->isBrokenWall())
                {
                       std::cout << "2k";
                    unVisitedNeighbours.append(downCell);
                    zart++;
                }
            }









            if(zart> 0){
                Cell* nextCell = unVisitedNeighbours.get(rand() % unVisitedNeighbours.getSize());
                nextCell->setVisited(true);
                solveStack.push(nextCell);
            }
            else{
                solveStack.pop();
            }
      
    }

    std::string fileName = "maze_"+ std::to_string(id)+"_path_"+std::to_string(startCol)+"_"+std::to_string(startRow)+"_"+std::to_string(endCol)+"_"+std::to_string(endRow)+".txt";
    
    //print the stack to a file
    std::ofstream file;
    file.open(fileName);
    LinkedList<Cell*> path;
    while(!solveStack.empty()){
     Cell* cell = solveStack.pop();
      path.prepend(cell);
    }
    
    for(int i = 0; i < path.getSize(); i++){
        Cell* cell = path.get(i);
        file<<cell->getCol()<<" "<<cell->getRow()<<std::endl;
    }
  
    std::cout<<"Solved Maze"<<std::endl;

}


void printMazeToFile(Maze* maze, std::string fileName){
    std::ofstream file;


    file.open(fileName);

    file<<maze->getRows()<<" "<<maze->getCols()<<std::endl;
    for (int i = 0; i < maze->getCols(); i++)
    {
        for (int j = 0; j < maze->getRows(); j++)
        {
            Cell *cell = maze->cells.get(i)->get(j);
            file << "x=" << cell->getCol() << " y=" << cell->getRow() << " u=" << cell->getUp() << " d=" << cell->getDown() << " l=" << cell->getLeft() << " r=" << cell->getRight() << std::endl;
        }
    }
    file.close();
}
 void printMaze(Maze* maze){

        std::cout << maze->getRows() << " " << maze->getCols() << std::endl;
        for (int i = 0; i < maze->getCols(); i++)
        {
            for (int j = 0; j < maze->getRows(); j++)
            {
                Cell *cell = maze->cells.get(i)->get(j);
                std::cout << "x=" << cell->getCol() << " y=" << cell->getRow() << " u=" << cell->getUp() << " d=" << cell->getDown() << " l=" << cell->getLeft() << " r=" << cell->getRight() << std::endl;
            }
        }

}
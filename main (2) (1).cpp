#include <iostream>
#include <vector>
#include <string>

int i = 0;

enum Color : char {
	white = 'w',
	black = 'b'
};

enum figureTypes : char {
	king = 'K',
	queen = 'Q',
	bishop = 'B',
	horse = 'H',
	pawn = 'P',
	empty = 'E'
};

struct Figure {
	Color color;
	figureTypes figureType;

	//Инициализация фигуры без цвета (может потребоваться при ситуации, если каждая фигура бьет каждую. Тогда при инициализации к фигуре будут относиться только правила перемещения))
	Figure(figureTypes figType) : figureType{ figType } {};
};

//Структура, описывающая клетку на доске
struct Cell {
	Color color;
	Figure figureOnCell{ empty };//Каждая клетка инициализируется без фигуры на ней
};

enum HorizontallCoordinates : int {
	_A = 0,
	_B = 1,
	_C = 2,
	_D = 3,
	_E = 4,
	_F = 5,
	_G = 6,
	_H = 7
};

enum VerticalCoordinates : int {
	_8 = 0,
	_7 = 1,
	_6 = 2,
	_5 = 3,
	_4 = 4,
	_3 = 5,
	_2 = 6,
	_1 = 7
};

struct Coordinate
{
	HorizontallCoordinates horCoord;
	VerticalCoordinates vertCoord;

	Coordinate(HorizontallCoordinates horCrd, VerticalCoordinates vertCrd) : horCoord{ horCrd }, vertCoord{ vertCrd }{};
};

//Структура, описывающая шахматную доску
struct Chessboard {
	Cell cells[8][8]; //Первый размер - цифра, второй размер - буква
};

//Функция, которая првоеряет стоит ли на доске фигура. Вроде как, использовалась везде где нужна данная проверка, кроме функции, распечатывающей шахматную доску.
bool isCellEmpty(const Chessboard chessboard, Coordinate c) {
	if (chessboard.cells [c.vertCoord] [c.horCoord].figureOnCell.figureType != empty) {
	   return false;   
	}
	return true;
}

//Функция, которая проверяет стоит ли на доске фигура. Вроде как, использовалась только при распечатке шахматной доски. В других случаях использовалась функиция, которая расположена выше.
bool isCellEmpty(const Chessboard chessboard, char HorizontallCoordinate, int VerticalCoordinate) {
	if (chessboard.cells[VerticalCoordinate][HorizontallCoordinate -  65].figureOnCell.figureType == empty) {
	    return true;   
	}
	return false;
	

}

//Функция, которая дает всем клеткам на шахматной доске цвета (черный и белый).
Chessboard paintBoard(Chessboard& chessboard) {

	int col = 1;

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (col == 1) {
				chessboard.cells[i][j].color = white;
				col = -1;
			}
			else if (col == -1) {
				chessboard.cells[i][j].color = black;
				col = 1;
			}
		}
		col = -col;
	}
	return chessboard;
}

// если на клетке нет фигуры, распечатывается цвет клетки
void Func1(Chessboard& chessboard, int i, int j) {
    
				if (chessboard.cells[i][j].color == white) {
				std::cout << "_|";
				}
				if (chessboard.cells[i][j].color == black) {
					std::cout << "*|";
				}
    
}

void Func2(Chessboard& chessboard, int i, int j) {
    switch (chessboard.cells[i][j].figureOnCell.figureType) //Если на клетке будет стоять фигура, то она распечатается на доске в консоле.
				{
				case king: {std::cout << "K|"; break; }
				case queen: {std::cout << "Q|"; break; }
				case bishop: {std::cout << "B|"; break; }
				case horse: {std::cout << "H|"; break; }
				case pawn: {std::cout << "P|"; break; }

				default: 
					break;
				}
}

void Func3 () {
    for (int i = 0; i < 8; i++) {
		if (i == 0)
			std::cout << ' ';

		std::cout << "|" << char(65 + i);
		if (i == 7)
			std::cout << '|';
	}
}

//Функция, которая распечатывает шахматную доску в консоль.
void printBoard(Chessboard& chessboard) {
	for (int i = 0; i < 8; i++) {
		//Распечатка цифр на шахматной доске.
		std::cout << 8 - i << "|";
		for (int j = 0; j < 8; j++) {
			if (isCellEmpty(chessboard, char(65 + j), i)) {
			    Func1(chessboard, i, j);
			}
			else {
				Func2(chessboard, i, j);
			}
		}
		std::cout << std::endl;
	}
	//Распечатка букв на шахматной доске
	Func3();
}

//Функция, которая ставит фигуру вне зависимости от безопасности место, т.е. просто ставит фигуру на выбранное место, если до нее на клетке не было фигуры.
void placeFigure(Chessboard& chessboard, Figure figure, HorizontallCoordinates HorizontallCoordinate, VerticalCoordinates VerticalCoordinate) {

	//Проверка на то, стоит ли на клетке фигура, если не стоит, то на клетку ставится фигура.
	if (isCellEmpty(chessboard, HorizontallCoordinate, VerticalCoordinate)) {
		chessboard.cells[VerticalCoordinate][HorizontallCoordinate].figureOnCell.figureType = figure.figureType;
	}
}

void removeFigure(Chessboard& chessboard, HorizontallCoordinates HorizontallCoordinate, VerticalCoordinates VerticalCoordinate) {
	chessboard.cells[VerticalCoordinate][HorizontallCoordinate].figureOnCell.figureType = empty;
}



//Аналогичная проверке по горизонтали и вертикали проверка по вертикали по диагонали.
bool checkDiagonallyEmpty(const Chessboard chessboard, HorizontallCoordinates horCoordinate, VerticalCoordinates vertCoordinate) {
    for (int a = 0; a < 4; a++) {
        int j = horCoordinate;
	    int i = vertCoordinate;
	    while (i > -1 && i < 8 && j > -1 && j < 8) {
		    if (!isCellEmpty(chessboard, HorizontallCoordinates(j), VerticalCoordinates(i))) {
			    return false;
		    }
		    switch (a) {
		        case 0: j--; i--;
		            break;
		        case 1: j--; i++;
		            break;
		        case 2: j++; i--;
		            break;
		        case 3: j++; i++;
		            break;
		    }
	    }
    }
	
	return true;
}

bool checkHorizontallyEmpty(const Chessboard chessboard, HorizontallCoordinates horCoordinate, VerticalCoordinates vertCoordinate)
{
	for (int i = 0; i < 8; i++)
	{
		if (!isCellEmpty(chessboard, HorizontallCoordinates(i), VerticalCoordinates(vertCoordinate))) return false;
	}
	return true;
}

bool isPositionSafe(const Chessboard& chessboard, int hor, int vert) {

	if (!checkHorizontallyEmpty || !checkDiagonallyEmpty(chessboard, HorizontallCoordinates(hor), VerticalCoordinates(vert))) return false;
	return true;
}

int placeAllQueens(Chessboard& board, int queensOnBoard)
{
	if (queensOnBoard == 8) return queensOnBoard;
	for (int i = 7; i >= 0; i--)
	{
		if (isPositionSafe(board, queensOnBoard, i))
		{
			placeFigure(board, queen, HorizontallCoordinates(queensOnBoard), VerticalCoordinates(i));
			if (placeAllQueens(board, queensOnBoard + 1)) return 1;
			board.cells[i][queensOnBoard].figureOnCell.figureType = empty ;
			removeFigure(board, HorizontallCoordinates(queensOnBoard), VerticalCoordinates(i));
		}
	}
	return 0;
}
// expected - ожидаемый результат, vertberAlg - номер алгоритма (горизонталь/диагональ)
void сorrectAlg(Chessboard test_chessboard, HorizontallCoordinates Horizontall, VerticalCoordinates vert, int expected, int vertberAlg) {
	if (i == 0 || i == 2)
		printBoard(test_chessboard);
	i++;

	std::cout << "\n\n Предположительный ферзь - " << char(65 + Horizontall) << 8 - vert << std::endl;
	std::cout << "\n -- Ожидаемый результат алгоритма: " << expected << " --" << std::endl;
	std::cout << " -- Фактический результат алгоритма: ";

	if (vertberAlg == 1) {
		std::cout << checkHorizontallyEmpty(test_chessboard, Horizontall, vert) << " --" << std::endl;
	}
	else if (vertberAlg == 2) {
		std::cout << checkDiagonallyEmpty(test_chessboard, Horizontall, vert) << " --" << std::endl;
	}
	 
	if (expected == 1)
		placeFigure(test_chessboard, queen, Horizontall, vert);

	std::cout << "\nИтог: " << std::endl;
	printBoard(test_chessboard);

	if (expected == 1)
		removeFigure(test_chessboard, Horizontall, vert);
}
 
void testingCorrectAlg() {
	Chessboard test_chessboard;
	paintBoard(test_chessboard);
	placeFigure(test_chessboard, queen, _A, _1);

	std::cout << "\n\n --- ПРОВЕРКА ГОРИЗОНТАЛИ --- \n\n" << std::endl;
	сorrectAlg(test_chessboard, _B, _3, 1, 1);
	сorrectAlg(test_chessboard, _C, _1, 0, 1);
	std::cout << "\n\n --- ПРОВЕРКА ДИАГОНАЛИ --- \n\n" << std::endl;
	сorrectAlg(test_chessboard, _B, _3, 1, 2);
	сorrectAlg(test_chessboard, _B, _2, 0, 2);
}

int main() {
	setlocale(LC_ALL, "RUS");
	testingCorrectAlg();

	std::cout << "\n\n\n --- Расстановка восьми ферзей ---  \n" << std::endl;
	Chessboard chessboard;
	paintBoard(chessboard);
	placeAllQueens(chessboard, 0);
	printBoard(chessboard);
	return 1;
}
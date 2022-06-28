#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

void printHorizontal(int size)
{
    cout << "    ";
    for (char i = 'A'; i < size + 'A'; i++)
    {
        cout << "    " << i << "   ";
    }
    cout << endl;
}

void printHorizontalLine(int size)
{
    cout << "    ";
    for (int i = 0; i < size; ++i)
    {
        cout << " -------";
    }
    cout << endl;
}

void printVerticalLine(int size)
{
    cout << "    ";
    for (int i = 0; i < size + 1; ++i)
    {
        cout << "|       ";
    }
    cout << endl;
}

void setBoard(char board[][2], int pos[], char name_chess[2][2], int size, int PLAYER1, int PLAYER2)
{

    for (int i = 0; i < size * size; i++)
    {
        memcpy(board[i], " ", 2);
    }

    for (int i = 0; i < size * size; i++)
    {
        if (pos[i] == PLAYER1)
            memcpy(board[i], name_chess[0], 2);
        else if (pos[i] == PLAYER2)
            memcpy(board[i], name_chess[1], 2);
    }
}

void printBoard(char board[][2], int size, int pos[], char name_chess[][2], int PLAYER1, int PLAYER2)
{
    setBoard(board, pos, name_chess, size, PLAYER1, PLAYER2);

    printHorizontal(size);
    printHorizontalLine(size);

    for (int i = 0; i < size; i++)
    {
        printVerticalLine(size);

        cout << i << "   ";
        for (int j = 0; j < size; j++)
        {
            cout << "|   " << board[i * size + j] << "   ";
        }
        cout << "|" << endl;

        printVerticalLine(size);
        printHorizontalLine(size);
    }
}


void setting(int &size, char name_chess[2][2])
{
    cout << "WELCOME TO THE TIC TAC TOE GAME!" << endl;
    cout << "Choose the grid size (3x3, 5x5, 7x7): ";
    cin >> size;

    string name_chess_temp;

    cout << "Enter icon chess 1: ";
    cin >> name_chess_temp;

    for (int i = 0; i < 2; i++)
    {
        name_chess[0][i] = name_chess_temp[i];
    }

    cout << "Enter icon chess 2: ";
    cin >> name_chess_temp;

    for (int i = 0; i < 2; i++)
    {
        name_chess[1][i] = name_chess_temp[i];
    }
}

void check_input(int pos[], int size, int chess, int PLAYER1, int PLAYER2)
{
    string input;

    bool flag = true;
    do
    {
        cout << "Enter input (" << chess << "): ";
        cin >> input;
        char i = input[0] - 48;
        int j = (int)input[1] - 65;
        if (pos[i * size + j] == 0)
        {
            if (chess == 1)
                pos[i * size + j] = PLAYER1;
            else if (chess == 2)
                pos[i * size + j] = PLAYER2;
            flag = false;
        }
        else
        {
            flag = true;
            cout << "Can not move forward." << endl;
        }
    } while (flag);
}

int playGame(int size, int pos[], char name_chess[][2], int PLAYER1, int PLAYER2)
{
    int count_horizontal_row_player1 = 0;
    int count_horizontal_row_player2 = 0;
    int count_vertical_row_player1 = 0;
    int count_vertical_row_player2 = 0;

    for (int i = 0; i < size; i++)
    {
        count_horizontal_row_player1 = 0;
        count_horizontal_row_player2 = 0;
        count_vertical_row_player1 = 0;
        count_vertical_row_player2 = 0;

        for (int j = 0; j < size; j++)
        {
            if (pos[i * size + j] == PLAYER1)
                ++count_horizontal_row_player1;
            else if (pos[i * size + j] == PLAYER2)
                ++count_horizontal_row_player2;

            if (pos[j * size + i] == PLAYER1)
                ++count_vertical_row_player1;
            else if (pos[j * size + i] == PLAYER2)
                ++count_vertical_row_player2;
        }
        if (count_horizontal_row_player1 == size || count_vertical_row_player1 == size)
        {
            cout << name_chess[0] << " win." << endl;
            return 1;
        }
        else if (count_horizontal_row_player2 == size || count_vertical_row_player2 == size)
        {
            cout << name_chess[1] << " win." << endl;
            return 2;
        }
    }

    int diagonal_row_left_player1 = 0;
    int diagonal_row_left_player2 = 0;
    int diagonal_row_right_player1 = 0;
    int diagonal_row_right_player2 = 0;

    for (int i = 0; i < size; i++)
    {
        if (pos[i * (size + 1)] == PLAYER1)
            ++diagonal_row_left_player1;
        else if (pos[i * (size + 1)] == PLAYER2)
            ++diagonal_row_left_player2;

        if (pos[(i + 1) * (size - 1)] == PLAYER1)
            ++diagonal_row_right_player1;
        else if (pos[(i + 1) * (size - 1)] == PLAYER2)
            ++diagonal_row_right_player2;
    }

    if (diagonal_row_left_player1 == size || diagonal_row_right_player1 == size)
    {
        cout << name_chess[0] << " win." << endl;
        return 1;
    }
    else if (diagonal_row_left_player2 == size || diagonal_row_right_player2 == size)
    {
        cout << name_chess[1] << " win." << endl;
        return 2;
    }

    int n = 0;
    for (int i = 0; i < size * size; i++)
    {
        if (pos[i] != 0)
            ++n;
    }

    if (n == size * size)
    {
        cout << "Draw match." << endl;
        return 0;
    }

    return 0;
}

bool gameReplay(bool start)
{
    char c;
    cout << "Do you want to play game again (Y/N)?: ";
    cin >> c;
    switch (c)
    {
    case 'Y':
    case 'y':
    {
        start = true;
        break;
    }
    case 'N':
    case 'n':
    {
        start = false;
        break;
    }
    default:
    {
        start = false;
    }
    }
    return start;
}

int chooseColor()
{
    int n;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 192);
    cout << "Color: 192 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 160);
    cout << "Color: 160 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 80);
    cout << "Color: 80 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "Color: 11 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
    cout << "Color: 2 ";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "Color: 7 ";
    cout << endl;
    cout << "Choose colors: ";
    cin >> n;
    return n;
}

void match(int &numOfGame, int winner, int NUGame[2], char name_chess[2][2], int PLAYER1, int PLAYER2, int numOfMove[2])
{
    numOfGame++;
    cout << "Total number of match: " << numOfGame << endl;
    if (winner == PLAYER1) NUGame[0]++;
    else if (winner == PLAYER2) NUGame[1]++;
    cout << name_chess[0] << " move " << numOfMove[0] << " step." <<  endl;
    cout << name_chess[1] << " move " << numOfMove[1] << " step." <<  endl;

    cout << name_chess[0] << " win " << NUGame[0] << " match. " << (NUGame[0] / (1.0 * numOfGame) * 100) << "% win." << endl;
    cout << name_chess[1] << " win " << NUGame[1] << " match. " << (NUGame[1] / (1.0 * numOfGame) * 100) << "% win." << endl;

}
int main()
{
    int size;
    const int PLAYER1 = 1;
    const int PLAYER2 = 2;
    char name_chess[2][2];

    setting(size, name_chess);

    char board[size * size][2];
    int pos[size * size] = {0};

    printBoard(board, size, pos, name_chess, PLAYER1, PLAYER2);

    bool start = true;
    int NUGame[2] = {0};
    int numOfGame = 0;
    int numOfMove[2] = {0};
    while (start)
    {
        int winner = 0;
        int n = chooseColor();
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n);
        int pos[size * size] = {0};
        printBoard(board, size, pos, name_chess, PLAYER1, PLAYER2);

        while (winner == 0)
        {
            check_input(pos, size, 1, PLAYER1, PLAYER2);
            printBoard(board, size, pos, name_chess, PLAYER1, PLAYER2);
            winner = playGame(size, pos, name_chess, PLAYER1, PLAYER2);
            numOfMove[0]++;
            if (winner != 0) break;

            check_input(pos, size, 2, PLAYER1, PLAYER2);
            printBoard(board, size, pos, name_chess, PLAYER1, PLAYER2);
            winner = playGame(size, pos, name_chess, PLAYER1, PLAYER2);
            numOfMove[1]++;
            if (winner != 0) break;
        }
        match(numOfGame, winner, NUGame, name_chess, PLAYER1, PLAYER2, numOfMove);
        start = gameReplay(start);
    }
}

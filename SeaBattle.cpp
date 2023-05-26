#include <iostream>
#include <iomanip>
#include <random> 
#include <windows.h>
#include <conio.h>
#include <stdio.h>

void reset() {
    printf("\033[0m");
}
void red()
{
    printf("\033[1;31m");
}
void white()
{
    printf("\033[1;37m");
}
void yellow()
{
    printf("\033[1;33m");
}
void blue()
{
    printf("\033[1;34m");
}
void purple()
{
    printf("\033[1;35m");
}
#define SIZE 10
#define def '.'
#define occup '-'
#define sing 's'
#define doub 'd'
#define trip 't'
#define four 'f'
#define shot '#'
#define kill 'X'
#define miss '!'
using namespace std;

pair <int, int> lshot;
pair <int, int> fshot;
pair <int, int> lshot2;
pair <int, int> fshot2;
pair <int, int> yfshot;
pair <int, int> randfshot;
int row = 0;
int row2 = 0;
int yourrow = 0;
int randrow = 0;
int bot1shots = 0;
int botrandshots = 0;
int bot2shots = 0;
int playershots = 0;
int gamemode;//Èãðîâûå ðåæèìû; 1 - èãðîê ïðîòèâ êîìïüþòåðà, 0 - êîìïüþòåð ïðîòèâ êîìïüþòåðà, 2 - îòêðûòü ñïðàâêó
char key;
pair<int, int> translate(string str); //Ïåðåâîä êîäà ââåäåííîãî èãðîêîì â èíäåêñû ìàññèâà
string randomGen(); //Ôóíêöèÿ ðàíäîìíîé ãåíåðàöèè êîäà êëåòêè
void delayPrint(string str, int delay);
void delayPrintNoEndl(string str, int delay);
void fillArr(char arr[SIZE][SIZE], char symb);
void autoPlacing(char arr[SIZE][SIZE]);
void manualPlacing(char boardl[SIZE][SIZE], char boardr[SIZE][SIZE]);
void boardPrint(char arr1[SIZE][SIZE], char arr2[][SIZE]);
void cantReplaceHere(char boardr[SIZE][SIZE], pair<int, int> place);
bool ñanIPlaceSingle(char boardr[SIZE][SIZE], pair<int, int> place);
bool ñanIPlaceDouble(char boardr[SIZE][SIZE], pair<int, int> place);
bool ñanIPlaceTriple(char boardr[SIZE][SIZE], pair<int, int> place);
bool canIPlaceFour(char boardr[SIZE][SIZE], pair<int, int> place);
void occupie(char boardr[SIZE][SIZE], pair<int, int> place, char ship);
bool isNext(char boardr[SIZE][SIZE], pair<int, int> place, char symb);
bool isTripleOk(char boardr[SIZE][SIZE], pair<int, int> place);
bool isFourOk(char boardr[SIZE][SIZE], pair<int, int> place);
bool isCodeRight(string str);
bool isDead(char board[SIZE][SIZE], pair<int, int> place);
bool isFourDead(char board[SIZE][SIZE], pair <int, int> place);
void damagetoKill(char board[SIZE][SIZE], pair<int, int> place);
bool yourStrike(char boardhide[SIZE][SIZE], char boardl[SIZE][SIZE], char boardr[SIZE][SIZE]);
bool botStrikeRand(char boardl[SIZE][SIZE], char board[SIZE][SIZE]);
bool botStrikeIQ(char boardl[SIZE][SIZE], char board[SIZE][SIZE]);
bool botStrikeIQ2(char boardl[SIZE][SIZE], char board[SIZE][SIZE]);
void killToMiss(char board[SIZE][SIZE]);
void occupieToDef(char board[SIZE][SIZE]);
pair <int, int> bot1(char boardr[SIZE][SIZE], pair <int, int> place);
pair <int, int> bot2(char boardr[SIZE][SIZE], pair <int, int> place);
random_device rd;
mt19937 gen(rd());
uniform_int_distribution<> dist1(65, 74); //Ãåíåðàöèÿ ñëó÷àéíûõ ÷èñåë â äèàïàçîíå.
uniform_int_distribution<> dist2(48, 57);
int main()
{
menu:
    system("cls");
    row = 0;
    row2 = 0;
    yourrow = 0;
    randrow = 0;
    bot1shots = 0;
    bot2shots = 0;
    playershots = 0;
    botrandshots = 0;
    int hint = 0;
    int replace = 1;
    int placing;//Ðàññòàíîâêà êîðàáëåé; 1 - Àâòîìàòè÷åñêè, 0 - Âðó÷íóþ 
    int iqmode; //Ðåæèì áîòà; 1 - áîò îáëàäàåò èíòåëëåêòîì, 0 - áîò äåëàåò ñëó÷àéíûå âûñòðåëû
    char boardr[SIZE][SIZE]{};
    char boardl[SIZE][SIZE]{};
    char boardhide[SIZE][SIZE]{};
    blue();
    delayPrint("Authors: Andrey Odintsov & Dmitry Balashov", 35);
    white();
    delayPrint("SeaBattle Welcomes You! Press ENTER to Start", 35);
    char enter;
    do
    {
        enter = _getch();
    } while (enter != 13);
    fillArr(boardl, def);
    fillArr(boardhide, def);
gamemode:
    delayPrint("Choose the Gamemode:", 35);
    delayPrint("0 - PC vs PC", 35);
    delayPrint("1 - Player vs PC", 35);
    delayPrint("2 - Information about the Game", 35);
    cin >> gamemode;
    if (gamemode > 2 || gamemode < 0)
    {
        while (!(gamemode == 1) || !(gamemode == 0) || !(gamemode == 3))
        {
            cout << "There is no such option" << endl;
            cin >> gamemode;
        }
    }
    switch (gamemode)
    {
    case 1:
        delayPrint("Choose ship-placing mode: ", 35);
        delayPrint("1 - Autoplacing", 35);
        delayPrint("0 - Manual placing", 35);
        cin >> placing;
        if (placing > 1 || placing < 0)
        {
            while (!(placing == 1) || !(placing == 0))
            {
                cout << "There is no such option" << endl;
                cin >> placing;
            }
        }
        switch (placing)
        {
        case 1: //Àâòîðàññòàíîâêà
            autoPlacing(boardhide);
            occupieToDef(boardhide);
            for (int count = 0; replace; count++)
            {
                fillArr(boardr, def);
                autoPlacing(boardr);
                occupieToDef(boardr);
                boardPrint(boardl, boardr);
                if (!count)
                {
                    delayPrint("Do You Want to Refresh the Field?", 35);
                    delayPrint("1 - Yes", 35);
                    delayPrint("0 - Continue", 35);
                }
                if (count > 0)
                {
                    cout << "Do You Want to Refresh the Field?" << endl;
                    cout << "---" << endl;
                    cout << "1 - Yes" << endl;
                    cout << "---" << endl;
                    cout << "0 - Continue" << endl;
                    cout << "---" << endl;
                }
                cin >> replace;
                count++;
            }
            boardPrint(boardl, boardr);
            break;
        case 0: //Ðàññòàíîâêà âðó÷íóþ
            fillArr(boardr, def);
            autoPlacing(boardhide);
            occupieToDef(boardhide);
            boardPrint(boardl, boardr);
            manualPlacing(boardl, boardr);
            occupieToDef(boardr);
            boardPrint(boardl, boardr);
        }
        delayPrint("Choose Bot Gamestyle:", 35);
        delayPrint("1 - Smart", 35);
        delayPrint("0 - Random Strike", 35);
        cin >> iqmode;
        boardPrint(boardl, boardr);
        if (iqmode > 1 || iqmode < 0)
        {
            while (!(iqmode == 1) || !(iqmode == 0))
            {
                cout << "There is no such option" << endl;
                cin >> iqmode;
            }
        }
        do
        {
            if (!hint)
            {
                delayPrint("Type coordinates to strike(f.e. A0)", 30);
                hint++;
            }
            while (yourStrike(boardhide, boardl, boardr))
            {
                if (playershots == 10)
                    break;
            }
            if (playershots == 10)
                continue;
            if (iqmode)
                while (botStrikeIQ(boardl, boardr))
                {
                    if (bot1shots == 10)
                        break;
                }
            else
                while (botStrikeRand(boardl, boardr));
            if (bot1shots == 10)
                continue;
            if (!iqmode)
                (bot1shots = botrandshots);
        } while (playershots < 10 && bot1shots < 10);
        if (playershots == 10)         // êîë-âî óíè÷òîæåíèé, íåîáõîäèìûõ äëÿ ïîáåäû
            delayPrint("Congratulations! You have Won the Match!", 35);
        else
            delayPrint("Bot has Won the Match", 35);
        do
        {
            yellow();
            delayPrint("Press ENTER to Start a New Game.", 35);
            reset();
            key = _getch();
            system("cls");
            goto menu;
        } while (key != 13);
        break;
    case 0:
        fillArr(boardr, def);
        fillArr(boardl, def);
        autoPlacing(boardl);
        occupieToDef(boardl);
        autoPlacing(boardr);
        occupieToDef(boardr);
        boardPrint(boardl, boardr);
        do
        {
            do
            {
                delayPrint("Press SPACE to Continue", 30);
                key = _getch();
                if (key == 27)
                    goto menu;
            } while (key != ' ');
            while (botStrikeIQ(boardl, boardr))
            {
                do
                {
                    delayPrint("Press SPACE to Continue", 30);
                    key = _getch();
                    if (key == 27)
                        goto menu;
                } while (key != ' ');
            }
            if (bot1shots == 10)
                continue;
            do
            {
                delayPrint("Press SPACE to Continue", 30);
                key = _getch();
                if (key == 27)
                    goto menu;
            } while (key != ' ');
            while (botStrikeIQ2(boardl, boardr))
            {
                do
                {
                    delayPrint("Press SPACE to Continue", 30);
                    key = _getch();
                    if (key == 27)
                        goto menu;
                } while (key != ' ');
            }
        } while (bot1shots < 10 && bot2shots < 10);
        if (bot1shots == 10)
            cout << "Bot 1 wins the game!" << endl;
        else
            cout << "Bot 2 wins the game!" << endl;
        do
        {
            yellow();
            cout << "---";
            cout << endl;
            delayPrint("Press ENTER to Start New Game.", 35);
            reset();
            key = _getch();
            system("cls");
            goto gamemode;
        } while (key != 13);
        break;
    case 2:
        delayPrintNoEndl("Welcome to the fun-made game Battleship! Battleship (also Battleships or Sea Battle) is a strategy type guessing game for two players. It is played on ruled grids (paper or board) on which each player's fleet of ships (including battleships) are marked. The locations of the fleets are concealed from the other player. Players alternate turns calling 'shots' at the other player's ships, and the objective of the game is to destroy the opposing player's fleet.", 13);
        delayPrintNoEndl(" The game is played on two grids, one for each player. The grids are typically square - usually 10x10 - and the individual squares in the grid are identified by letter and number. On one grid the player arranges ships and records the shots by the opponent. On the other grid the player records their own shots. Before play begins, each player secretly arranges their ships on their primary grid.", 13);
        cout << endl;
        do
        {
            yellow();
            cout << "---";
            cout << endl;
            delayPrint("Press ENTER to Leave.", 35);
            reset();
            key = _getch();
            system("cls");
            goto gamemode;
        } while (key != 13);
    }

    return 0;
}
// Ôóíêöèè***************
pair<int, int> translate(string str)
{
    pair<int, int> place;
    int letter = toupper((str[0])) - 65;
    int number = (str[1]) - 48;
    place.first = letter;
    place.second = number;
    return place;
}
string randomGen()
{
    Sleep(0.1);
    string str;
    str += dist1(gen);
    str += dist2(gen);
    return str;
}
void delayPrint(string str, int delay)
{
    for (size_t i = 0; str[i] != 0; i++)
    {
        cout << str[i];
        Sleep(delay);
    }
    cout << endl;
    cout << "---";
    cout << endl;
}
void delayPrintNoEndl(string str, int delay)
{
    for (size_t i = 0; str[i] != 0; i++)
    {
        cout << str[i];
        Sleep(delay);
    }
}
bool isFourDead(char board[SIZE][SIZE], pair <int, int> place)
{
    if (board[place.second + 1][place.first] == four && (place.second + 1) < SIZE)
        return 0;
    if (board[place.second][place.first + 1] == four && (place.first + 1) < SIZE)
        return 0;
    if (board[place.second][place.first - 1] == four && (place.first - 1) >= 0)
        return 0;
    if (board[place.second - 1][place.first] == four && (place.second - 1) >= 0)
        return 0;
    return 1;
}

bool isDead(char board[SIZE][SIZE], pair<int, int> place)
{
    if (board[place.second + 1][place.first] != shot && board[place.second + 1][place.first] != miss && board[place.second + 1][place.first] != def && (place.second + 1) < SIZE)
        return 0;
    if (board[place.second][place.first + 1] != shot && board[place.second][place.first + 1] != miss && board[place.second][place.first + 1] != def && (place.first + 1) < SIZE)
        return 0;
    if (board[place.second - 1][place.first] != shot && board[place.second - 1][place.first] != miss && board[place.second - 1][place.first] != def && (place.second - 1) >= 0)
        return 0;
    if (board[place.second][place.first - 1] != shot && board[place.second][place.first - 1] != miss && board[place.second][place.first - 1] != def && (place.first - 1) >= 0)
        return 0;
    return 1;
}
bool isDamageLeft(char board[SIZE][SIZE], pair <int, int> place)
{
    if (board[place.second + 1][place.first] == shot && (place.second + 1) < SIZE)
        return 1;
    if (board[place.second][place.first + 1] == shot && (place.first + 1) < SIZE)
        return 1;
    if (board[place.second - 1][place.first] == shot && (place.second - 1) >= 0)
        return 1;
    if (board[place.second][place.first - 1] == shot && (place.first - 1) >= 0)
        return 1;
    return 0;
}
void damagetoKill(char board[SIZE][SIZE], pair<int, int> place)
{
    pair<int, int> killed = place;
    while (isDamageLeft(board, killed))
    {
        if (board[killed.second + 1][killed.first] == shot && (killed.second + 1) < SIZE)
        {
            board[killed.second + 1][killed.first] = kill;
            killed.second++;
            continue;
        }
        if (board[killed.second][killed.first + 1] == shot && (killed.first + 1) < SIZE)
        {
            board[killed.second][killed.first + 1] = kill;
            killed.first++;
            continue;
        }
        if (board[killed.second - 1][killed.first] == shot && (killed.second - 1) >= 0)
        {
            board[killed.second - 1][killed.first] = kill;
            killed.second--;
            continue;
        }
        if (board[killed.second][killed.first - 1] == shot && (killed.first - 1) >= 0)
        {
            board[killed.second][killed.first - 1] = kill;
            killed.first--;
        }
    }
    while (isDamageLeft(board, killed))
    {
        if (board[killed.second + 1][killed.first] == shot && (killed.second + 1) < SIZE)
        {
            board[killed.second + 1][killed.first] = kill;
            killed.second++;
            continue;
        }
        if (board[killed.second][killed.first + 1] == shot && (killed.first + 1) < SIZE)
        {
            board[killed.second][killed.first + 1] = kill;
            killed.first++;
            continue;
        }
        if (board[killed.second - 1][killed.first] == shot && (killed.second - 1) >= 0)
        {
            board[killed.second - 1][killed.first] = kill;
            killed.second--;
            continue;
        }
        if (board[killed.second][killed.first - 1] == shot && (killed.first - 1) >= 0)
        {
            board[killed.second][killed.first - 1] = kill;
            killed.first--;
        }
    }
}
void fillArr(char arr[SIZE][SIZE], char symb)
{
    for (size_t i = 0; i < SIZE; i++)
    {
        for (size_t j = 0; j < SIZE; j++)
        {
            arr[i][j] = symb;
        }
    }
}
void boardPrint(char arr1[SIZE][SIZE], char arr2[][SIZE])
{
    system("cls");
    white();
    if (gamemode)
    {
        cout << "        Bot's Board";
        cout << "\t\t\t\tYour Board";
    }
    else if (!gamemode)
    {
        cout << "       1 Bot's Board";
        cout << "\t\t\t       2 Bot's Board";
    }

    cout << endl << endl;
    cout << "    A B C D E F G H I J ";
    cout << "\t\t    A B C D E F G H I J ";
    cout << endl;
    for (size_t i = 0; i < SIZE; i++)
    {
        white();
        cout << setw(2) << i << " ";
        reset();
        for (size_t j = 0; j < SIZE; j++)
        {
            if (arr1[i][j] == shot)
                yellow();
            if (arr1[i][j] == kill)
                red();
            if (arr1[i][j] == miss)
                blue();
            if (arr1[i][j] == sing)
                purple();
            if (arr1[i][j] == doub)
                purple();
            if (arr1[i][j] == trip)
                purple();
            if (arr1[i][j] == four)
                purple();
            cout << setw(2) << arr1[i][j];
            reset();
        }
        white();
        cout << " " << setw(2) << i;
        cout << "\t\t" << setw(2) << i << " ";
        reset();
        for (size_t j = 0; j < SIZE; j++)
        {
            if (arr2[i][j] == shot)
                yellow();
            if (arr2[i][j] == kill)
                red();
            if (arr2[i][j] == miss)
                blue();
            if (arr2[i][j] == sing)
                purple();
            if (arr2[i][j] == doub)
                purple();
            if (arr2[i][j] == trip)
                purple();
            if (arr2[i][j] == four)
                purple();
            cout << setw(2) << arr2[i][j];
            reset();
        }
        white();
        cout << " " << setw(2) << i;
        cout << endl;
        reset();
    }
    white();
    cout << "    A B C D E F G H I J ";
    cout << "\t\t    A B C D E F G H I J " << endl << endl;
    reset();
}
bool isCodeRight(string str)
{
    if (str[0] < 'A')
        return 0;
    if (str[0] > 'J' && str[0] < 'a')
        return 0;
    if (str[0] > 'j')
        return 0;
    if (str[1] < '0' || str[1]>'9')
        return 0;
    if (str.length() > 2)
        return 0;
    return 1;
}
void cantReplaceHere(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (place.first != SIZE - 1)
        boardr[place.second][place.first + 1] = occup;
    if (place.first != 0)
        boardr[place.second][place.first - 1] = occup;
    if (place.second != SIZE - 1)
        boardr[place.second + 1][place.first] = occup;
    if (place.second != 0)
        boardr[place.second - 1][place.first] = occup;
    if (place.second != SIZE - 1 && place.first != SIZE - 1)
        boardr[place.second + 1][place.first + 1] = occup;
    if (place.second != 0 && place.first != 0)
        boardr[place.second - 1][place.first - 1] = occup;
    if (place.second != 0 && place.first != SIZE - 1)
        boardr[place.second - 1][place.first + 1] = occup;
    if (place.second != SIZE - 1 && place.first != 0)
        boardr[place.second + 1][place.first - 1] = occup;
}
bool ñanIPlaceSingle(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (boardr[place.second][place.first] != def)
        return 0;
    return 1;
}
bool ñanIPlaceDouble(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (ñanIPlaceSingle(boardr, place) == 0)
        return 0;
    if (boardr[place.second + 1][place.first] == def && (place.second + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first + 1] == def && (place.first + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first - 1] == def && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == def && (place.second - 1) >= 0)
        return 1;
    return 0;
}
bool ñanIPlaceTriple(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (ñanIPlaceSingle(boardr, place) == 0)
        return 0;
    if (boardr[place.second + 1][place.first] == def && boardr[place.second + 2][place.first] == def && (place.second + 2) < SIZE)
        return 1;
    if (boardr[place.second][place.first + 1] == def && boardr[place.second][place.first + 2] == def && (place.first + 2) < SIZE)
        return 1;
    if (boardr[place.second][place.first - 1] == def && boardr[place.second][place.first - 2] == def && (place.first - 2) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == def && boardr[place.second - 2][place.first] == def && (place.second - 2) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == def && boardr[place.second + 1][place.first] == def && (place.second - 1) >= 0 && (place.second + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first - 1] == def && boardr[place.second][place.first + 1] == def && (place.first - 1) >= 0 && (place.first + 1) < SIZE)
        return 1;
    return 0;
}
bool canIPlaceFour(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (ñanIPlaceSingle(boardr, place) == 0)
        return 0;
    if (boardr[place.second + 1][place.first] == def && boardr[place.second + 2][place.first] == def && boardr[place.second + 3][place.first] == def && (place.second + 3) < SIZE)
        return 1;
    if (boardr[place.second][place.first + 1] == def && boardr[place.second][place.first + 2] == def && boardr[place.second][place.first + 3] == def && (place.first + 3) < SIZE)
        return 1;
    if (boardr[place.second - 1][place.first] == def && boardr[place.second - 2][place.first] == def && boardr[place.second - 3][place.first] == def && (place.second - 3) >= 0)
        return 1;
    if (boardr[place.second][place.first - 1] == def && boardr[place.second][place.first - 2] == def && boardr[place.second][place.first - 3] == def && (place.first - 3) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == def && boardr[place.second + 1][place.first] == def && boardr[place.second + 2][place.first] == def && (place.second + 2) < SIZE && (place.second - 1) >= 0)
        return 1;
    if (boardr[place.second][place.first - 1] == def && boardr[place.second][place.first + 1] == def && boardr[place.second][place.first + 2] == def && (place.first + 2) < SIZE && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second + 1][place.first] == def && boardr[place.second - 1][place.first] == def && boardr[place.second - 2][place.first] == def && (place.second - 2) >= 0 && (place.second + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first + 1] == def && boardr[place.second][place.first - 1] == def && boardr[place.second][place.first - 2] == def && (place.first - 2) >= 0 && (place.first + 1) < SIZE)
        return 1;
    if (boardr[place.second + 2][place.first] == def && boardr[place.second + 1][place.first] == def && boardr[place.second - 1][place.first] == def && (place.second - 1) >= 0 && (place.second + 2) < SIZE)
        return 1;
    if (boardr[place.second][place.first + 2] == def && boardr[place.second][place.first + 1] == def && boardr[place.second][place.first - 1] == def && (place.first - 1) >= 0 && (place.first + 2) < SIZE)
        return 1;
    if (boardr[place.second - 2][place.first] == def && boardr[place.second - 1][place.first] == def && boardr[place.second + 1][place.first] == def && (place.second - 2) >= 0 && (place.second + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first - 2] == def && boardr[place.second][place.first - 1] == def && boardr[place.second][place.first + 1] == def && (place.first - 2) >= 0 && (place.first + 1) < SIZE)
        return 1;
    return 0;
}
void occupie(char boardr[SIZE][SIZE], pair<int, int> place, char ship)
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (boardr[i][j] == ship)
            {
                if (boardr[i + 1][j] == def && (i + 1) < SIZE)
                    boardr[i + 1][j] = occup;
                if (boardr[i][j + 1] == def && (j + 1) < SIZE)
                    boardr[i][j + 1] = occup;
                if (boardr[i - 1][j] == def && (i - 1) >= 0)
                    boardr[i - 1][j] = occup;
                if (boardr[i][j - 1] == def && (j - 1) >= 0)
                    boardr[i][j - 1] = occup;
                if (boardr[i - 1][j - 1] == def && (i - 1) >= 0 && (j - 1) >= 0)
                    boardr[i - 1][j - 1] = occup;
                if (boardr[i + 1][j + 1] == def && (i + 1) < SIZE && (j + 1) < SIZE)
                    boardr[i + 1][j + 1] = occup;
                if (boardr[i - 1][j + 1] == def && (i - 1) >= 0 && (j + 1) < SIZE)
                    boardr[i - 1][j + 1] = occup;
                if (boardr[i + 1][j - 1] == def && (i + 1) < SIZE && (j - 1) >= 0)
                    boardr[i + 1][j - 1] = occup;
            }
        }
    }
}
bool isTripleOk(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (boardr[place.second][place.first - 1] == trip && boardr[place.second][place.first + 1] == def && (place.first + 1) < SIZE && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second][place.first + 1] == trip && boardr[place.second][place.first - 1] == def && (place.first + 1) < SIZE && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == trip && boardr[place.second + 1][place.first] == def && (place.second + 1) < SIZE && (place.second - 1) >= 0)
        return 1;
    if (boardr[place.second + 1][place.first] == trip && boardr[place.second - 1][place.first] == def && (place.second + 1) < SIZE && (place.second - 1) >= 0)
        return 1;
    return 0;
}
bool isFourOk(char boardr[SIZE][SIZE], pair<int, int> place)
{
    if (boardr[place.second][place.first - 1] == four && boardr[place.second][place.first + 1] == def && boardr[place.second][place.first + 2] == def && (place.first + 2) < SIZE && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second][place.first + 1] == four && boardr[place.second][place.first - 1] == def && boardr[place.second][place.first - 2] == def && (place.first + 1) < SIZE && (place.first - 2) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == four && boardr[place.second + 1][place.first] == def && boardr[place.second + 2][place.first] == def && (place.second + 2) < SIZE && (place.second - 1) >= 0)
        return 1;
    if (boardr[place.second + 1][place.first] == four && boardr[place.second - 1][place.first] == def && boardr[place.second - 2][place.first] == def && (place.second + 1) < SIZE && (place.second - 2) >= 0)
        return 1;
    return 0;
}
bool isNext(char boardr[SIZE][SIZE], pair<int, int> place, char symb)
{
    if (boardr[place.second][place.first + 1] == symb && (place.first + 1) < SIZE)
        return 1;
    if (boardr[place.second + 1][place.first] == symb && (place.second + 1) < SIZE)
        return 1;
    if (boardr[place.second][place.first - 1] == symb && (place.first - 1) >= 0)
        return 1;
    if (boardr[place.second - 1][place.first] == symb && (place.second - 1) >= 0)
        return 1;
    return 0;
}
void autoPlacing(char board[SIZE][SIZE])
{
    pair <int, int> place;
    for (int i = 0; i < 1; i++) //Ðàññòàíîâêà ÷åòûðåõïàëóáíûõ êîðàáëåé
    {
        int firstvrt;
        int secondvrt;
        int firsthrs;
        int secondhrs;
        bool orient;
        for (size_t decks = 4; decks >= 1; decks--)
        {
            if (decks == 4)
            {
                do
                {
                    place = translate(randomGen());
                } while (!(canIPlaceFour(board, place)));
                board[place.second][place.first] = four;
                firstvrt = place.second;
                firsthrs = place.first;
            }
            else if (decks == 3)
            {
                do
                {
                    place = translate(randomGen());
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, four)) || !(isFourOk(board, place)));
                board[place.second][place.first] = four;
                secondvrt = place.second;
                secondhrs = place.first;
                orient = (firstvrt == secondvrt);
            }
            else if (decks == 2)
            {
                do
                {
                    place = translate(randomGen());
                    if (orient)
                    {
                        while (place.second != firstvrt)
                            place = translate(randomGen());
                    }
                    else
                    {
                        while (place.first != firsthrs)
                            place = translate(randomGen());
                    }
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, four)));
                board[place.second][place.first] = four;
            }
            else
            {
                do
                {
                    place = translate(randomGen());
                    if (orient)
                    {
                        while (place.second != firstvrt)
                            place = translate(randomGen());
                    }
                    else
                    {
                        while (place.first != firsthrs)
                            place = translate(randomGen());
                    }
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, four)));
                board[place.second][place.first] = four;
                occupie(board, place, four);
            }
        }
    }
    for (int i = 0; i < 2; i++) //Ðàññòàíîâêà òðåõïàëóáíûõ êîðàáëåé
    {
        int firstvrt;
        int secondvrt;
        int firsthrs;
        int secondhrs;
        bool orient;
        for (size_t decks = 3; decks >= 1; decks--)
        {
            if (decks == 3)
            {
                do
                {
                    place = translate(randomGen());
                } while (!(ñanIPlaceTriple(board, place)));
                board[place.second][place.first] = trip;
                firstvrt = place.second;
                firsthrs = place.first;
            }
            else if (decks == 2)
            {
                do
                {
                    place = translate(randomGen());
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, trip)) || !(isTripleOk(board, place)));
                board[place.second][place.first] = trip;
                secondvrt = place.second;
                secondhrs = place.first;
                orient = (firstvrt == secondvrt);
            }
            else
            {
                do
                {
                    place = translate(randomGen());
                    if (orient)
                    {
                        while (place.second != firstvrt)
                            place = translate(randomGen());
                    }
                    else
                    {
                        while (place.first != firsthrs)
                            place = translate(randomGen());
                    }
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, trip)));
                board[place.second][place.first] = trip;
                occupie(board, place, trip);
            }
        }
    }

    for (int i = 0; i < 3; i++) //Ðàññòàíîâêà äâóõïàëóáíûõ êîðàáëåé
    {
        for (size_t decks = 2; decks >= 1; decks--)
        {
            if (decks == 2)
            {
                do
                {
                    place = translate(randomGen());
                } while (!(ñanIPlaceDouble(board, place)));
                board[place.second][place.first] = doub;
            }
            else
            {
                do
                {
                    place = translate(randomGen());
                } while (!(ñanIPlaceSingle(board, place)) || !(isNext(board, place, doub)));
                board[place.second][place.first] = doub;
                occupie(board, place, doub);
            }

        }
    }
    for (int i = 0; i < 4; i++) //Ðàññòàíîâêà îäíîïàëóáíûõ êîðàáëåé
    {
        do
        {
            place = translate(randomGen());
        } while (!(ñanIPlaceSingle(board, place)));
        board[place.second][place.first] = sing;
        cantReplaceHere(board, place);
    }
}
bool yourStrike(char boardhide[SIZE][SIZE], char boardl[SIZE][SIZE], char boardr[SIZE][SIZE])
{
    delayPrint("Do your shot!", 35);
    pair<int, int > place;
    string shipplace;
    cin >> shipplace;
    place = translate(shipplace);
    while (!(isCodeRight(shipplace)))
    {
        delayPrint("Wrong Code!", 35);
        cin >> shipplace;
        place = translate(shipplace);
    }
    while (boardhide[place.second][place.first] == shot || boardhide[place.second][place.first] == kill || boardhide[place.second][place.first] == miss)
    {
        delayPrint("You cannot strike there!", 35);
        cin >> shipplace;
        place = translate(shipplace);
    }

    if (boardhide[place.second][place.first] != def && boardhide[place.second][place.first] != occup && boardhide[place.second][place.first] != shot && boardhide[place.second][place.first] != kill && boardhide[place.second][place.first] != miss)
    {
        if (!yourrow)
            yfshot = place;
        boardl[place.second][place.first] = shot;
        boardhide[place.second][place.first] = shot;
        yourrow++;
        if (isDead(boardhide, place) && (isDead(boardhide, yfshot)) && isFourDead(boardhide, place) && isFourDead(boardhide, yfshot))
        {
            yourrow = 0;
            playershots++;
            boardl[place.second][place.first] = kill;
            boardhide[place.second][place.first] = kill;
            damagetoKill(boardl, place);
            damagetoKill(boardhide, place);
            killToMiss(boardl);
            killToMiss(boardhide);
            boardPrint(boardl, boardr);
            delayPrint("You Have Eliminated The Enemy Ship!", 35);
        }
        else
        {
            boardPrint(boardl, boardr);
            delayPrint("You Have Damaged The Enemy Ship!", 35);
        }
    }
    else
    {
        boardl[place.second][place.first] = miss;
        boardhide[place.second][place.first] = miss;
        boardPrint(boardl, boardr);
        delayPrint("You Missed The Shot.", 35);
        return 0;
    }
    return 1;
}
bool botStrikeRand(char boardl[SIZE][SIZE], char board[SIZE][SIZE])
{
    pair<int, int > place;
    delayPrintNoEndl("Bot is striking", 30);
    Sleep(750);
    delayPrintNoEndl("...", 750);
    Sleep(300);
    do
    {
        place = translate(randomGen());
    } while (board[place.second][place.first] == shot || board[place.second][place.first] == kill || board[place.second][place.first] == miss);
    if (board[place.second][place.first] != def && board[place.second][place.first] != occup && board[place.second][place.first] != shot && board[place.second][place.first] != kill && board[place.second][place.first] != miss)
    {
        if (!randrow)
            randfshot = place;
        board[place.second][place.first] = shot;
        randrow++;
        if (isDead(board, place) && isDead(board, randfshot))
        {
            randrow = 0;
            botrandshots++;
            board[place.second][place.first] = kill;
            damagetoKill(board, place);
            killToMiss(board);
            boardPrint(boardl, board);
            delayPrintNoEndl("Bot Have Eliminated The Ship at ", 25);
            cout << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
        else
        {
            boardPrint(boardl, board);
            delayPrintNoEndl("Bot Have Damaged The Ship at ", 25);
            cout << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
    }
    else
    {
        board[place.second][place.first] = miss;
        boardPrint(boardl, board);
        delayPrintNoEndl("Bot Missed The Shot at ", 25);
        cout << char(place.first + 65) << char(place.second + 48) << endl;
        delayPrintNoEndl("---", 30);
        cout << endl;
        Sleep(300);
        return 0;
    }
    return 1;
}
bool botStrikeIQ2(char boardl[SIZE][SIZE], char board[SIZE][SIZE])
{
    int key;
    string shipplace;
    pair<int, int > place;
    delayPrintNoEndl("Bot 2 is striking", 30);
    Sleep(750);
    delayPrintNoEndl("...", 750);
    Sleep(300);
    if (row2 == 0)
    {
        do
        {

            place = translate(randomGen());
        } while (boardl[place.second][place.first] == shot || boardl[place.second][place.first] == kill || boardl[place.second][place.first] == miss);
    }
    else if (row2 == 1)
    {
        place = bot1(boardl, lshot2);
    }
    else if (row2 == 2)
        place = bot2(boardl, lshot2);
    else if (row2 == 3)
        place = bot2(boardl, lshot2);
    if (boardl[place.second][place.first] != def && boardl[place.second][place.first] != shot && boardl[place.second][place.first] != kill && boardl[place.second][place.first] != miss)
    {
        if (!row2)
            fshot2 = place;
        boardl[place.second][place.first] = shot;
        row2++;
        lshot2 = place;
        if (isDead(boardl, place) && isDead(boardl, fshot2))
        {
            boardl[place.second][place.first] = kill;
            row2 = 0;
            bot2shots++;
            damagetoKill(boardl, place);
            killToMiss(boardl);
            boardPrint(boardl, board);
            delayPrintNoEndl("Bot 2 Have Eliminated The Ship at ", 25);
            cout << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
        else
        {
            boardPrint(boardl, board);
            cout << "Bot 2 Damaged The Ship at " << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
    }
    else
    {
        boardl[place.second][place.first] = miss;
        boardPrint(boardl, board);
        delayPrintNoEndl("Bot 2 Missed The Shot at ", 25);
        cout << char(place.first + 65) << char(place.second + 48) << endl;
        delayPrintNoEndl("---", 30);
        cout << endl;
        Sleep(300);
        return 0;
    }
    return 1;
}
bool botStrikeIQ(char boardl[SIZE][SIZE], char board[SIZE][SIZE])
{
    int key;
    string shipplace;
    pair<int, int > place;
    delayPrintNoEndl("Bot is striking", 30);
    Sleep(750);
    delayPrintNoEndl("...", 750);
    Sleep(300);
    if (row == 0)
    {
        do
        {

            place = translate(randomGen());
        } while (board[place.second][place.first] == shot || board[place.second][place.first] == kill || board[place.second][place.first] == miss);
    }
    else if (row == 1)
    {
        place = bot1(board, lshot);
    }
    else if (row == 2)
        place = bot2(board, lshot);
    else if (row == 3)
        place = bot2(board, lshot);
    if (board[place.second][place.first] != def && board[place.second][place.first] != shot && board[place.second][place.first] != kill && board[place.second][place.first] != miss)
    {
        if (!row)
            fshot = place;
        board[place.second][place.first] = shot;
        row++;
        lshot = place;
        if (isDead(board, place) && isDead(board, fshot))
        {
            board[place.second][place.first] = kill;
            bot1shots++;
            row = 0;
            damagetoKill(board, place);
            killToMiss(board);
            boardPrint(boardl, board);
            delayPrintNoEndl("Bot Have Eliminated Your Ship at ", 25);
            cout << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
        else
        {
            boardPrint(boardl, board);
            delayPrintNoEndl("Bot Damaged Your Ship at ", 25);
            cout << char(place.first + 65) << char(place.second + 48) << endl;
            delayPrintNoEndl("---", 30);
            cout << endl;
            Sleep(300);
        }
    }
    else
    {
        board[place.second][place.first] = miss;
        boardPrint(boardl, board);
        delayPrintNoEndl("Bot Missed The Shot at ", 25);
        cout << char(place.first + 65) << char(place.second + 48) << endl;
        delayPrintNoEndl("---", 30);
        cout << endl;
        Sleep(300);
        return 0;
    }
    return 1;
}
pair <int, int> bot1(char boardr[SIZE][SIZE], pair <int, int> place)
{
    int option = rand() % 4;
    while (1)
    {
        if (option == 0)
        {
            if (boardr[place.second + 1][place.first] != miss && (place.second + 1) < SIZE)
            {
                place.second++;
                return place;
            }
            else
            {
                option = rand() % 4;
            }
        }
        else if (option == 1)
        {
            if (boardr[place.second][place.first + 1] != miss && (place.first + 1) < SIZE)
            {
                place.first++;
                return place;
            }
            else
            {
                option = rand() % 4;
            }
        }
        else if (option == 2)
        {
            if (boardr[place.second - 1][place.first] != miss && (place.second - 1) >= 0)
            {
                place.second--;
                return place;
            }
            else
            {
                option = rand() % 4;
                continue;
            }
        }
        else
        {
            if (boardr[place.second][place.first - 1] != miss && (place.first - 1) >= 0)
            {
                place.first--;
                return place;
            }
            else
            {
                option = rand() % 4;
                continue;
            }
        }
    }
}
pair <int, int> bot2(char boardr[SIZE][SIZE], pair <int, int> place)
{
    if (boardr[place.second - 1][place.first] == miss && boardr[place.second + 1][place.first] == shot || boardr[place.second + 1][place.first] == shot && place.second - 1 == -1)
        place.second++;
    if (boardr[place.second + 1][place.first] == miss && boardr[place.second - 1][place.first] == shot || boardr[place.second - 1][place.first] == shot && place.second + 1 == SIZE)
        place.second--;
    if (boardr[place.second][place.first + 1] == miss && boardr[place.second][place.first - 1] == shot || boardr[place.second][place.first - 1] == shot && place.first + 1 == SIZE)
        place.first--;
    if (boardr[place.second][place.first - 1] == miss && boardr[place.second][place.first + 1] == shot || boardr[place.second][place.first + 1] == shot && place.first - 1 == -1)
        place.first++;

    if (boardr[place.second - 1][place.first] == shot && boardr[place.second + 1][place.first] == shot && place.second >= 1 && place.second <= 8)
        place = fshot;
    if (boardr[place.second + 1][place.first] == shot && boardr[place.second - 1][place.first] == shot && place.second >= 1 && place.second <= 8)
        place = fshot;
    if (boardr[place.second][place.first + 1] == shot && boardr[place.second][place.first - 1] == shot && place.first >= 1 && place.first <= 8)
        place = fshot;
    if (boardr[place.second][place.first - 1] == shot && boardr[place.second][place.first + 1] == shot && place.first >= 1 && place.first <= 8)
        place = fshot;


    pair <int, int> lplace;
    bool option = rand() % 1;

    if (boardr[place.second][place.first + 1] == shot && (place.first + 1) < SIZE)
    {
        lplace.first = place.first + 1;
        if (option)
        {
            if (lplace.first + 1 < SIZE)
            {
                lplace.first++;
                return lplace;
            }
            else
            {
                place.first--;
                return place;
            }
        }
        else
        {
            if (place.first - 1 >= 0)
            {
                place.first--;
                return place;
            }
            else
            {
                lplace.first++;
                return lplace;
            }

        }
    }
    if (boardr[place.second + 1][place.first] == shot && (place.second + 1) < SIZE)
    {
        lplace.second = place.second + 1;
        if (option)
        {
            if (lplace.second + 1 < SIZE)
            {
                lplace.second++;
                return lplace;
            }
            else
            {
                place.second--;
                return place;
            }
        }
        else
        {
            if (place.second - 1 >= 0)
            {
                place.second--;
                return place;
            }
            else
            {
                lplace.second++;
                return lplace;
            }
        }
    }
    if (boardr[place.second - 1][place.first] == shot && (place.second - 1) >= 0)
    {
        lplace.second = place.second - 1;
        if (option)
        {
            if (lplace.second - 1 >= 0)
            {
                lplace.second--;
                return lplace;
            }
            else
            {
                place.second++;
                return place;
            }
        }
        else
        {
            if (place.second + 1 < SIZE)
            {
                place.second++;
                return place;
            }
            else
            {
                lplace.second--;
                return lplace;
            }
        }
    }
    if (boardr[place.second][place.first - 1] == shot && (place.first - 1) >= 0)
    {
        lplace.first = place.first - 1;
        if (option)
        {
            if (lplace.first - 1 >= 0)
            {
                lplace.first--;
                return lplace;
            }
            else
            {
                place.first++;
                return place;
            }
        }
        else
        {
            if (place.first + 1 < SIZE)
            {
                place.first++;
                return place;
            }
            else
            {
                lplace.second--;
                return lplace;
            }
        }
    }
}

void killToMiss(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == kill)
            {
                if (board[i + 1][j] != kill && (i + 1) < SIZE)
                    board[i + 1][j] = miss;
                if (board[i][j + 1] != kill && (j + 1) < SIZE)
                    board[i][j + 1] = miss;
                if (board[i - 1][j] != kill && (i - 1) >= 0)
                    board[i - 1][j] = miss;
                if (board[i][j - 1] != kill && (j - 1) >= 0)
                    board[i][j - 1] = miss;
                if (board[i - 1][j - 1] != kill && (i - 1) >= 0 && (j - 1) >= 0)
                    board[i - 1][j - 1] = miss;
                if (board[i + 1][j + 1] != kill && (i + 1) < SIZE && (j + 1) < SIZE)
                    board[i + 1][j + 1] = miss;
                if (board[i - 1][j + 1] != kill && (i - 1) >= 0 && (j + 1) < SIZE)
                    board[i - 1][j + 1] = miss;
                if (board[i + 1][j - 1] != kill && (i + 1) < SIZE && (j - 1) >= 0)
                    board[i + 1][j - 1] = miss;
            }
        }
    }
}
void occupieToDef(char board[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (board[i][j] == occup)
                board[i][j] = def;
        }
    }
}
void manualPlacing(char boardl[SIZE][SIZE], char boardr[SIZE][SIZE])
{
    string shipplace;
    pair <int, int> place;
    for (int i = 0; i < 1; i++) //Ðàññòàíîâêà ÷åòûðåõïàëóáíûõ êîðàáëåé
    {
        int firstvrt;
        int secondvrt;
        int firsthrs;
        int secondhrs;
        bool orient;
        for (size_t decks = 4; decks >= 1; decks--)
        {
            cout << "Place your four-deck ships:" << endl;
            if (decks == 4)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(canIPlaceFour(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                } while (!(canIPlaceFour(boardr, place)));
                boardr[place.second][place.first] = four;
                firstvrt = place.second;
                firsthrs = place.first;
                boardPrint(boardl, boardr);
            }
            else if (decks == 3)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    if (!(isNext(boardr, place, four)))
                        cout << "Try again! Your ship has to be connected." << endl;
                    if (!(isFourOk(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, four)) || !(isFourOk(boardr, place)));
                boardr[place.second][place.first] = four;
                secondvrt = place.second;
                secondhrs = place.first;
                orient = (firstvrt == secondvrt);
                boardPrint(boardl, boardr);
            }
            else if (decks == 2)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    if (!(isNext(boardr, place, four)))
                        cout << "Try again! Your ship has to be connected" << endl;
                    if (orient)
                    {
                        while (place.second != firstvrt)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    else
                    {
                        while (place.first != firsthrs)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, four)));
                boardr[place.second][place.first] = four;
                boardPrint(boardl, boardr);
            }
            else
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    if (!(isNext(boardr, place, four)))
                        cout << "Try again! Your ship has to be connected" << endl;
                    if (orient)
                    {
                        while (place.second != firstvrt)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    else
                    {
                        while (place.first != firsthrs)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, four)));
                boardr[place.second][place.first] = four;
                occupie(boardr, place, four);
                boardPrint(boardl, boardr);
            }
        }
    }
    for (int i = 0; i < 2; i++) //Ðàññòàíîâêà òðåõïàëóáíûõ êîðàáëåé
    {
        int firstvrt;
        int secondvrt;
        int firsthrs;
        int secondhrs;
        bool orient;
        for (size_t decks = 3; decks >= 1; decks--)
        {
            cout << "Place your triple-deck ships:" << endl;
            if (decks == 3)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceTriple(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                } while (!(ñanIPlaceTriple(boardr, place)));
                boardr[place.second][place.first] = trip;
                firstvrt = place.second;
                firsthrs = place.first;
                boardPrint(boardl, boardr);
            }
            else if (decks == 2)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    if (!(isNext(boardr, place, trip)))
                        cout << "Try again! Your ship has to be connected." << endl;
                    if (!(isTripleOk(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, trip)) || !(isTripleOk(boardr, place)));
                boardr[place.second][place.first] = trip;
                secondvrt = place.second;
                secondhrs = place.first;
                orient = (firstvrt == secondvrt);
                boardPrint(boardl, boardr);
            }
            else
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    if (!(isNext(boardr, place, trip)))
                        cout << "Try again! Your ship has to be connected" << endl;
                    if (orient)
                    {
                        while (place.second != firstvrt)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    else
                    {
                        while (place.first != firsthrs)
                        {
                            cout << "Try again! Ship has to be a straight line." << endl;
                            cin >> shipplace;
                            place = translate(shipplace);
                        }
                    }
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, trip)));
                boardr[place.second][place.first] = trip;
                occupie(boardr, place, trip);
                boardPrint(boardl, boardr);
            }
        }
    }
    for (int i = 0; i < 3; i++) //Ðàññòàíîâêà äâóõïàëóáíûõ êîðàáëåé
    {
        for (size_t decks = 2; decks >= 1; decks--)
        {
            cout << "Place your double-deck ships:" << endl;
            if (decks == 2)
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceDouble(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    place = translate(shipplace);
                } while (!(ñanIPlaceDouble(boardr, place)));
                boardr[place.second][place.first] = doub;
                boardPrint(boardl, boardr);
            }
            else
            {
                do
                {
                    cin >> shipplace;
                    place = translate(shipplace);
                    while (!(isCodeRight(shipplace)))
                    {
                        cout << "Wrong Code!" << endl;
                        cin >> shipplace;
                        place = translate(shipplace);
                    }
                    if (!(ñanIPlaceSingle(boardr, place)))
                        cout << "Try again! You can't place your ship here." << endl;
                    else if (!(isNext(boardr, place, doub)))
                        cout << "Try again! Your ship has to be connected" << endl;
                    place = translate(shipplace);
                } while (!(ñanIPlaceSingle(boardr, place)) || !(isNext(boardr, place, doub)));
                boardr[place.second][place.first] = doub;
                occupie(boardr, place, doub);
                boardPrint(boardl, boardr);
            }

        }
    }
    for (int i = 0; i < 4; i++) //Ðàññòàíîâêà îäíîïàëóáíûõ êîðàáëåé
    {
        cout << "Place your single-deck ships:" << endl;
        do
        {
            cin >> shipplace;
            place = translate(shipplace);
            while (!(isCodeRight(shipplace)))
            {
                cout << "Wrong Code!" << endl;
                cin >> shipplace;
                place = translate(shipplace);
            }
            if (!(ñanIPlaceSingle(boardr, place)))
                cout << "Try again! You can't place your ship here." << endl;
            place = translate(shipplace);
        } while (!(ñanIPlaceSingle(boardr, place)));
        boardr[place.second][place.first] = sing;
        cantReplaceHere(boardr, place);
        boardPrint(boardl, boardr);
    }
}


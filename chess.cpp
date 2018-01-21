#include<simplecpp>
const bool white = true , black = false;
const int EMPTY = -1 , PAWN = 0 , ROOK = 1 , KNIGHT = 2 , BISHOP = 3 , QUEEN = 4 , KING = 5 ;
const int cSize = 500 , winwidth = 750 ;
const double boxSide = cSize / 8.0 ;
bool gameComplete = false , turn = true ;
// winwidth : width of window
// cSize and cSize : width and height of chess

void handleClick(int L , vector < vector<Rectangle> > & board);
//functions to get cordinate from location and location from cordinate

int getLocation(int click)
{
    int x = click / 65536 ;
    int y = click % 65536 ;
    int xLocation = x / (cSize/ 8.0);
    int yLocation = y / (cSize/ 8.0);
    if(xLocation < 8 && yLocation < 8)return xLocation * 10 + yLocation ;
    click = getClick();
    return getLocation(click);
}
int getCordinate(int Location)
{
    int xLocation = Location / 10 ;
    int yLocation = Location % 10 ;
    int xCordinate = (cSize / 16) + (xLocation * cSize) / 8 ;
    int yCordinate = (cSize / 16) + (yLocation * cSize) / 8 ;
    return xCordinate * 65536 + yCordinate ;
}
//Piece Graphical
struct pieceG
{
    int ptype ;
    bool pcolor ;
    Circle c , c1 , c2 ;
    Rectangle r , r1 , r2 , r3 ;
    pieceG(){}
    pieceG(int Location , bool color , int type)
    {
        ptype = type ; pcolor = color ;
        const char * colorName ;
        if(color) colorName = "white";
        else colorName = "black";
        if(type == -1) {} //Empty
        if(type == 0)
        {
            c.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 - int((boxSide * 2 ) / 10 ) , int((boxSide * 1 ) / 10 ));
            c.setColor(COLOR(colorName));
            c.setFill(true);
            r1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 1 ) / 10 ) , int((boxSide * 4 ) / 10 ) );
            r1.setColor(COLOR(colorName));
            r1.setFill(true);
            r2.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 + int((boxSide * 2 ) / 10 ) , int((boxSide * 3 ) / 10 ) , int((boxSide * 1 ) / 10 ));
            r2.setColor(COLOR(colorName));
            r2.setFill(true);
        }
        if(type == 1)
        {
            r1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 2 ) / 10 ) , int((boxSide * 4 ) / 10 ) );
            r1.setColor(COLOR(colorName));
            r1.setFill(true);
            r2.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 + int((boxSide * 3 ) / 10 ) , int((boxSide * 6 ) / 10 ) , int((boxSide * 2 ) / 10 ) );
            r2.setColor(COLOR(colorName));
            r2.setFill(true);
            r3.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 - int((boxSide * 3 ) / 10 ) , int((boxSide * 4 ) / 10 ) , int((boxSide * 2 ) / 10 ) );
            r3.setColor(COLOR(colorName));
            r3.setFill(true);
        }
        if(type == 2)
        {
            c1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 + int((boxSide * 2 ) / 10 ) , int((boxSide * 2 ) / 10 ));
            c1.setColor(COLOR(colorName));
            c1.setFill(true);
            c2.reset(getCordinate(Location)/65536 + int((boxSide * 1 ) / 10 ) , getCordinate(Location)%65536 - int((boxSide * 2 ) / 10 ) , int((boxSide * 1 ) / 10 ));
            c2.setColor(COLOR(colorName));
            c2.setFill(true);
            r.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 2 ) / 10 ) , int((boxSide * 6 ) / 10 ) );
            r.setColor(COLOR(colorName));
            r.setFill(true);
        }
        if(type == 3)
        {
            r1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 2 ) / 10 ) , int((boxSide * 4 ) / 10 ) );
            r1.setColor(COLOR(colorName));
            r1.setFill(true);
            r2.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 + int((boxSide * 3 ) / 10 ) , int((boxSide * 4 ) / 10 ) , int((boxSide * 2 ) / 10 ) );
            r2.setColor(COLOR(colorName));
            r2.setFill(true);
            r3.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 - int((boxSide * 2 ) / 10 ) , int((boxSide * 3 ) / 10 ) , int((boxSide * 3 ) / 10 ) );
            r3.setColor(COLOR(colorName));
            r3.setFill(true);
            r3.rotate(3.14 / 4 ); // 45 degree
        }
        if(type == 4)
        {
            c1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int(boxSide / 4));
            c2.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 4 ) / 10 ));
            c2.setColor(COLOR(colorName));
            c1.setColor(COLOR(colorName));
            c1.setFill(true);
        }
        if(type == 5)
        {
            c.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 4 ) / 10 ));
            c.setColor(COLOR(colorName));
            r1.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 6 ) / 10 ) , int((boxSide * 2 ) / 10 ) );
            r1.setColor(COLOR(colorName));
            r1.setFill(true);
            r2.reset(getCordinate(Location)/65536 , getCordinate(Location)%65536 , int((boxSide * 2 ) / 10 ) , int((boxSide * 6 ) / 10 ));
            r2.setColor(COLOR(colorName));
            r2.setFill(true);
        }
    }
};
vector < vector <pieceG * > > allPieceG(8 , vector<pieceG * >(8 , NULL ));

// checks if x is present in vector vec
bool isPresent(vector <int> vec , int x)
{
    for(size_t i = 0 ; i < vec.size() ; i++)
    {
        if(vec[i] == x ) return true ;
    }
    return false ;
}
bool isPiecePresent(vector <int> vec , int type)
{
    for(size_t i = 0 ; i < vec.size() ; i++)
    {
        if(allPieceG[vec[i] / 10][vec[i] % 10] != NULL)
        {
            if(allPieceG[vec[i] / 10][vec[i] % 10] -> ptype == type) return true ;
        }
    }
    return false ;
}
// make the rectangle of default color
void makeDefaultColor(int L , vector < vector<Rectangle> > & board)
{
    Rectangle & r = board[L/10][L%10];
    if( ((L / 10) + (L % 10)) % 2 == 0 ) r.setColor(COLOR(255,211,155)); // Light Brown
    else r.setColor(COLOR(139,115,85)); // Dark Brown
}
void makeDefaultColor(vector <int> cP , vector < vector<Rectangle> > & board)
{
    for(size_t i = 0 ; i < cP.size() ; i++)
    {
        makeDefaultColor(cP[i] , board);
    }
}
// delete a piece
void deleteP(int L)
{
    if(allPieceG[L/10][L%10] != NULL)
    {
        int x = L/10 , y = L%10 ;
        delete allPieceG[x][y];
        allPieceG[x][y] = NULL;
    }
}
void deleteP(int x , int y )
{
    deleteP(x * 10 + y);
}
// create a piece
void createP(int L , bool color , int type)
{
    deleteP(L);
    int x = L/10 , y = L%10 ;
    allPieceG[x][y] = new pieceG(L , color , type);
}
void createP(int x , int y , bool color , int type)
{
    createP(x * 10 + y , color , type);
}
// Function to handle Pawn
bool isKingOnTarget(bool color)
{
    int L = 0;
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            if(allPieceG[i][j] != NULL)
            {
                if(allPieceG[i][j]->pcolor == turn && allPieceG[i][j]->ptype == 5)
                {
                    L = 10 * i + j ;
                }
            }
        }
    }
    // We have found king and it's location is L now

    // Check by Pawn
    vector <int> cP ;
    int oneForward;
    if(allPieceG[L/10][L%10]->pcolor) oneForward = -1; else oneForward = 1 ;
    if(L/10 - 1 != -1)
    {
        if(allPieceG[L/10 - 1 ][L%10 + oneForward] != NULL && allPieceG[L/10 - 1 ][L%10 + oneForward]->pcolor != turn)
        {
            cP.push_back( L - 10 + oneForward );
        }
    }
    if(L/10 + 1 != 8)
    {
        if(allPieceG[L/10 + 1][L%10 + oneForward] != NULL && allPieceG[L/10 + 1 ][L%10 + oneForward]->pcolor != turn)
        {
            cP.push_back( L + 10 + oneForward );
        }
    }
    if(isPiecePresent(cP , 0)) return true ;
    cP.resize(0);

    // Check by Rook or Queen
    int modL = L ;
    while((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 1 );
        if(allPieceG[modL/10][modL%10 + 1] != NULL) break ;
        modL++;
    }
    modL = L ;
    while(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL - 1 );
        if(allPieceG[modL/10][modL%10 - 1] != NULL)break;
        modL--;
    }
    modL = L ;
    while((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
    {
        cP.push_back( modL - 10 );
        if(allPieceG[modL/10 - 1][modL%10] != NULL)break;
        modL = modL - 10;
    }
    modL = L ;
    while(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
    {
        cP.push_back( modL + 10 );
        if(allPieceG[modL/10 + 1][modL%10] != NULL)break;
        modL = modL + 10;
    }
    if(isPiecePresent(cP , 1)) return true ;
    if(isPiecePresent(cP , 4)) return true ;
    cP.resize(0);

    // Check by Knight
    modL = L ;
    int x , y ;
    x = modL / 10 ; y = modL % 10 ;
    //1
    if((y < 6 && x < 7 ) && ((allPieceG[x + 1 ][y + 2] == NULL) || (allPieceG[x + 1][y + 2]->pcolor != turn && allPieceG[x + 1][y + 2] != NULL)))
    {
        cP.push_back( modL + 12 );
    }
    //2
    if((y < 6 && x > 0 ) && ((allPieceG[x - 1 ][y + 2] == NULL) || (allPieceG[x - 1][y + 2]->pcolor != turn && allPieceG[x - 1][y + 2] != NULL)))
    {
        cP.push_back( modL - 8 );
    }
    //3
    if((y < 7 && x < 6 ) && ((allPieceG[x + 2 ][y + 1] == NULL) || (allPieceG[x + 2 ][y + 1]->pcolor != turn && allPieceG[x + 2 ][y + 1] != NULL)))
    {
        cP.push_back( modL + 21 );
    }
    //4
    if((y > 0 && x < 6 ) && ((allPieceG[x + 2 ][y - 1] == NULL) || (allPieceG[x + 2 ][y - 1]->pcolor != turn && allPieceG[x + 2 ][y - 1] != NULL)))
    {
        cP.push_back( modL + 19 );
    }
    //5
    if((y > 1 && x < 7 ) && ((allPieceG[x + 1 ][y - 2] == NULL) || (allPieceG[x + 1][y - 2]->pcolor != turn && allPieceG[x + 1][y - 2] != NULL)))
    {
        cP.push_back( modL + 8 );
    }
    //6
    if((y > 1 && x > 0 ) && ((allPieceG[x - 1 ][y - 2] == NULL) || (allPieceG[x - 1][y - 2]->pcolor != turn && allPieceG[x - 1][y - 2] != NULL)))
    {
        cP.push_back( modL - 12 );
    }
    //7
    if((y > 0 && x > 1 ) && ((allPieceG[x - 2 ][y - 1] == NULL) || (allPieceG[x - 2 ][y - 1]->pcolor != turn && allPieceG[x - 2 ][y - 1] != NULL)))
    {
        cP.push_back( modL - 21 );
    }
    //8
    if((y < 7 && x > 1 ) && ((allPieceG[x - 2 ][y + 1] == NULL) || (allPieceG[x - 2 ][y + 1]->pcolor != turn && allPieceG[x - 2 ][y + 1] != NULL)))
    {
        cP.push_back( modL - 19 );
    }
    if(isPiecePresent(cP , 2)) return true ;
    cP.resize(0);

    // Check by Bishop
    modL = L ;
    while((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 11 );
        if(allPieceG[modL/10 + 1][modL%10 + 1] != NULL)break;
        modL = modL + 11;
    }
    modL = L ;
    while(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL + 9 );
        if(allPieceG[modL/10 + 1][modL%10 - 1] != NULL)break;
        modL = modL + 9 ;
    }
    modL = L ;
    while(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL - 9 );
        if(allPieceG[modL/10 - 1][modL%10 + 1] != NULL)break;
        modL = modL - 9;
    }
    modL = L ;
    while(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
    {
        cP.push_back( modL - 11 );
        if(allPieceG[modL/10 - 1][modL%10 - 1] != NULL)break;
        modL = modL - 11;
    }
    if(isPiecePresent(cP , 3)) return true ;
    if(isPiecePresent(cP , 4)) return true ;
    cP.resize(0);

    // Check by King
    modL = L ;
    // Top, Bottom, Left, Right
    if((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 1 );
    }
    if(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL - 1 );
    }
    if((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
    {
        cP.push_back( modL - 10 );
    }
    if(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
    {
        cP.push_back( modL + 10 );
    }
    // At Diagonal Positions
    if((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 11 );
    }

    if(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL + 9 );
    }
    if(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL - 9 );
    }
    if(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
    {
        cP.push_back( modL - 11 );
    }
    if(isPiecePresent(cP , 5)) return true ;
    cP.resize(0);

    return false ;
}
bool canThisMoveRemoveCheck(int L2 , int L , bool color)
{
    bool result = false ;
    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }
    deleteP(L2);
    createP(L2 , allPieceG[L/10][L%10]->pcolor , allPieceG[L/10][L%10]->ptype);
    deleteP(L);
    if(!isKingOnTarget(color)) result = true ;
    createP(L , allPieceG[L2/10][L2%10]->pcolor , allPieceG[L2/10][L2%10]->ptype);
    deleteP(L2);
    if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
    return result;
}
bool canRemoveCheck(vector <int> cP , int L , bool color)
{
    for(size_t i = 0 ; i < cP.size() ; i++)
    {
        if(canThisMoveRemoveCheck(cP[i] , L , color)) return true ;
    }
    return false ;
}
bool canThisPieceRemoveCheck(int L , bool color)
{
    if(allPieceG[L/10][L%10] == NULL) return false ;
    if(allPieceG[L/10][L%10] -> pcolor != color) return false ;
    int modL = L ;
     //Pawn
    if(allPieceG[L/10][L%10]->ptype == 0)
    {
        vector <int> cP ;
        int oneForward;
        if(allPieceG[L/10][L%10]->pcolor) oneForward = -1; else oneForward = 1 ;
        if(allPieceG[L/10][L%10 + oneForward] == NULL)
        {
            cP.push_back( L + oneForward );
        }
        if(L/10 - 1 != -1)
        {
            if(allPieceG[L/10 - 1 ][L%10 + oneForward] != NULL && allPieceG[L/10 - 1 ][L%10 + oneForward]->pcolor != turn)
            {
                cP.push_back( L - 10 + oneForward );
            }
        }
        if(L/10 + 1 != 8)
        {
            if(allPieceG[L/10 + 1][L%10 + oneForward] != NULL && allPieceG[L/10 + 1 ][L%10 + oneForward]->pcolor != turn)
            {
                cP.push_back( L + 10 + oneForward );
            }
        }
        if(canRemoveCheck(cP , L , color)) return true ;
    }
    //Rook or Queen
    if(allPieceG[L/10][L%10]->ptype == 1 || allPieceG[L/10][L%10]->ptype == 4)
    {
        vector <int> cP ;
        modL = L ;
        while((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL + 1 );
            if(allPieceG[modL/10][modL%10 + 1] != NULL) break ;
            modL++;
        }
        modL = L ;
        while(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
        {
            cP.push_back( modL - 1 );
            if(allPieceG[modL/10][modL%10 - 1] != NULL)break;
            modL--;
        }
        modL = L ;
        while((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
        {
            cP.push_back( modL - 10 );
            if(allPieceG[modL/10 - 1][modL%10] != NULL)break;
            modL = modL - 10;
        }
        modL = L ;
        while(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
        {
            cP.push_back( modL + 10 );
            if(allPieceG[modL/10 + 1][modL%10] != NULL)break;
            modL = modL + 10;
        }
        if(canRemoveCheck(cP , L , color)) return true ;
    }
    //Knight
    if(allPieceG[L/10][L%10]->ptype == 2)
    {
        vector <int> cP ;
        modL = L ;
        int x , y ;
        x = modL / 10 ; y = modL % 10 ;
        //1
        if((y < 6 && x < 7 ) && ((allPieceG[x + 1 ][y + 2] == NULL) || (allPieceG[x + 1][y + 2]->pcolor != turn && allPieceG[x + 1][y + 2] != NULL)))
        {
            cP.push_back( modL + 12 );
        }
        //2
        if((y < 6 && x > 0 ) && ((allPieceG[x - 1 ][y + 2] == NULL) || (allPieceG[x - 1][y + 2]->pcolor != turn && allPieceG[x - 1][y + 2] != NULL)))
        {
            cP.push_back( modL - 8 );
        }
        //3
        if((y < 7 && x < 6 ) && ((allPieceG[x + 2 ][y + 1] == NULL) || (allPieceG[x + 2 ][y + 1]->pcolor != turn && allPieceG[x + 2 ][y + 1] != NULL)))
        {
            cP.push_back( modL + 21 );
        }
        //4
        if((y > 0 && x < 6 ) && ((allPieceG[x + 2 ][y - 1] == NULL) || (allPieceG[x + 2 ][y - 1]->pcolor != turn && allPieceG[x + 2 ][y - 1] != NULL)))
        {
            cP.push_back( modL + 19 );
        }
        //5
        if((y > 1 && x < 7 ) && ((allPieceG[x + 1 ][y - 2] == NULL) || (allPieceG[x + 1][y - 2]->pcolor != turn && allPieceG[x + 1][y - 2] != NULL)))
        {
            cP.push_back( modL + 8 );
        }
        //6
        if((y > 1 && x > 0 ) && ((allPieceG[x - 1 ][y - 2] == NULL) || (allPieceG[x - 1][y - 2]->pcolor != turn && allPieceG[x - 1][y - 2] != NULL)))
        {
            cP.push_back( modL - 12 );
        }
        //7
        if((y > 0 && x > 1 ) && ((allPieceG[x - 2 ][y - 1] == NULL) || (allPieceG[x - 2 ][y - 1]->pcolor != turn && allPieceG[x - 2 ][y - 1] != NULL)))
        {
            cP.push_back( modL - 21 );
        }
        //8
        if((y < 7 && x > 1 ) && ((allPieceG[x - 2 ][y + 1] == NULL) || (allPieceG[x - 2 ][y + 1]->pcolor != turn && allPieceG[x - 2 ][y + 1] != NULL)))
        {
            cP.push_back( modL - 19 );
        }
        if(canRemoveCheck(cP , L , color)) return true ;
    }
    //Bishop or Queen
    if(allPieceG[L/10][L%10]->ptype == 3 || allPieceG[L/10][L%10]->ptype == 4)
    {
        vector <int> cP ;
        modL = L ;
        while((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL + 11 );
            if(allPieceG[modL/10 + 1][modL%10 + 1] != NULL)break;
            modL = modL + 11;
        }
        modL = L ;
        while(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
        {
            cP.push_back( modL + 9 );
            if(allPieceG[modL/10 + 1][modL%10 - 1] != NULL)break;
            modL = modL + 9 ;
        }
        modL = L ;
        while(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL - 9 );
            if(allPieceG[modL/10 - 1][modL%10 + 1] != NULL)break;
            modL = modL - 9;
        }
        modL = L ;
        while(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
        {
            cP.push_back( modL - 11 );
            if(allPieceG[modL/10 - 1][modL%10 - 1] != NULL)break;
            modL = modL - 11;
        }
        if(canRemoveCheck(cP , L , color)) return true ;
    }
    //King
    if(allPieceG[L/10][L%10]->ptype == 5)
    {
        vector <int> cP ;
        modL = L ;
        // Top, Bottom, Left, Right
        if((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL + 1 );
        }
        if(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
        {
            cP.push_back( modL - 1 );
        }
        if((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
        {
            cP.push_back( modL - 10 );
        }
        if(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
        {
            cP.push_back( modL + 10 );
        }
        // At Diagonal Positions
        if((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL + 11 );
        }

        if(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
        {
            cP.push_back( modL + 9 );
        }
        if(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
        {
            cP.push_back( modL - 9 );
        }
        if(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
        {
            cP.push_back( modL - 11 );
        }
        if(canRemoveCheck(cP , L , color)) return true ;
    }
    return false ;
}
bool isCheckmate(bool color)
{
    beginFrame();
    if(!isKingOnTarget(color))
    {
        endFrame();
        return false ;
    }
    for(int i = 0 ; i < 8 ; i++)
    {
        for(int j = 0 ; j < 8 ; j++)
        {
            if(allPieceG[i][j] != NULL)
            {
                if(allPieceG[i][j]->pcolor == color)
                {
                    if(canThisPieceRemoveCheck( i * 10 + j , color))
                    {
                        endFrame();
                        return false ;
                    }
                }
            }
        }
    }
    endFrame();
    return true ;
}
void f0(int L , vector < vector<Rectangle> > & board)
{
    vector <int> cP ; // correctPositions
    beginFrame();
    //set blue colour for pawn position
    board[L/10][L%10].setColor(COLOR("blue"));
    //for black and white turn
    int oneForward ;
    if(allPieceG[L/10][L%10]->pcolor) oneForward = -1; else oneForward = 1 ;
    //storing two step move of pawn and making it green
    if((allPieceG[L/10][L%10]->pcolor && L%10 == 6 ) || ((!allPieceG[L/10][L%10]->pcolor) && L%10 == 1) )
    {
        if(allPieceG[L/10][L%10 + 2 * oneForward] == NULL)
        {
            cP.push_back( L + 2 * oneForward );
            board[L/10][L%10 + 2 * oneForward].setColor(COLOR("green"));
        }
    }
    //storing one step move of pawn and making it green
    if(allPieceG[L/10][L%10 + oneForward] == NULL)
    {
        cP.push_back( L + oneForward );
        board[L/10][L%10 + oneForward].setColor(COLOR("green"));
    }
    //storing the enemy position at 45 angle and making it red when you are white
    if(L/10 - 1 != -1)
    {
        if(allPieceG[L/10 - 1 ][L%10 + oneForward] != NULL && allPieceG[L/10 - 1 ][L%10 + oneForward]->pcolor != turn)
        {
            cP.push_back( L - 10 + oneForward );
            board[L/10 - 1 ][L%10 + oneForward].setColor(COLOR("red"));
        }
    }
    //storing the enemy position at 45 angle and making it red when you are black
    if(L/10 + 1 != 8)
    {
        if(allPieceG[L/10 + 1][L%10 + oneForward] != NULL && allPieceG[L/10 + 1 ][L%10 + oneForward]->pcolor != turn)
        {
            cP.push_back( L + 10 + oneForward );
            board[L/10 + 1][L%10 + oneForward].setColor(COLOR("red"));
        }
    }
    endFrame();
    //if movement is not possible then return
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    int click = getClick();
    int L2 = getLocation(click);
    beginFrame();
    //**when click position is not allowed movement position then take again click
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 0);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);
    //if it reaches other end new army man will be selected
    if((allPieceG[L2/10][L2%10]->pcolor && L2%10 == 0 ) || ((!allPieceG[L2/10][L2%10]->pcolor) && L2%10 == 7) )
    {
        {
            Rectangle r;
            r.reset(cSize / 4.0 , cSize / 16.0 , cSize / 2.0 , cSize / 8.0 );
            r.setColor(COLOR("green"));
            r.setFill(true);
            pieceG p1( 00 , turn , 1);
            pieceG p2( 10 , turn , 2);
            pieceG p3( 20 , turn , 3);
            pieceG p4( 30 , turn , 4);
            endFrame();
            click = getClick();
            int L3 = getLocation(click);
            //when click outside
            while(L3 % 10 > 0 && L3 / 10 > 3)
            {
                click = getClick();
                L3 = getLocation(click);
            }
            beginFrame();
            deleteP(L);
            //creates rook , knight , bishop ,queen
            createP(L2 , turn , L3/10 + 1);
        }
        endFrame();
        beginFrame();
    }

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 0);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// Function to handle Rook
void f1(int L , vector < vector<Rectangle> > & board)
{
    beginFrame();
    vector <int> cP ; // correctPositions
    board[L/10][L%10].setColor(COLOR("blue"));
    int modL = L ;
    while((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 1 );
        if(allPieceG[modL/10][modL%10 + 1] == NULL)board[modL/10][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 + 1].setColor(COLOR("red"));
            break;
        }
        modL++;
    }
    modL = L ;
    while(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL - 1 );
        if(allPieceG[modL/10][modL%10 - 1] == NULL)board[modL/10][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 - 1].setColor(COLOR("red"));
            break ;
        }
        modL--;
    }
    modL = L ;
    while((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
    {
        cP.push_back( modL - 10 );
        if(allPieceG[modL/10 - 1][modL%10] == NULL)board[modL/10 - 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10].setColor(COLOR("red"));
            break ;
        }
        modL = modL - 10;
    }
    modL = L ;
    while(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
    {
        cP.push_back( modL + 10 );
        if(allPieceG[modL/10 + 1][modL%10] == NULL)board[modL/10 + 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10].setColor(COLOR("red"));
            break;
        }
        modL = modL + 10;
    }
    endFrame();
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    beginFrame();
    int click = getClick();
    int L2 = getLocation(click);
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 1);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 1);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// Function to handle Knight
void f2(int L , vector < vector<Rectangle> > & board)
{
    vector <int> cP ; // correctPositions
    beginFrame();
    board[L/10][L%10].setColor(COLOR("blue"));
    int modL = L ;
    int x , y ;
    x = modL / 10 ; y = modL % 10 ;
    //1
    if((y < 6 && x < 7 ) && ((allPieceG[x + 1 ][y + 2] == NULL) || (allPieceG[x + 1][y + 2]->pcolor != turn && allPieceG[x + 1][y + 2] != NULL)))
    {
        cP.push_back( modL + 12 );
        if(allPieceG[x + 1 ][y + 2] == NULL)board[x + 1 ][y + 2].setColor(COLOR("green"));
        else
        {
            board[x + 1 ][y + 2].setColor(COLOR("red"));
        }
    }
    //2
    if((y < 6 && x > 0 ) && ((allPieceG[x - 1 ][y + 2] == NULL) || (allPieceG[x - 1][y + 2]->pcolor != turn && allPieceG[x - 1][y + 2] != NULL)))
    {
        cP.push_back( modL - 8 );
        if(allPieceG[x - 1 ][y + 2] == NULL)board[x - 1 ][y + 2].setColor(COLOR("green"));
        else
        {
            board[x - 1 ][y + 2].setColor(COLOR("red"));
        }
    }
    //3
    if((y < 7 && x < 6 ) && ((allPieceG[x + 2 ][y + 1] == NULL) || (allPieceG[x + 2 ][y + 1]->pcolor != turn && allPieceG[x + 2 ][y + 1] != NULL)))
    {
        cP.push_back( modL + 21 );
        if(allPieceG[x + 2 ][y + 1] == NULL)board[x + 2 ][y + 1].setColor(COLOR("green"));
        else
        {
            board[x + 2 ][y + 1].setColor(COLOR("red"));
        }
    }
    //4
    if((y > 0 && x < 6 ) && ((allPieceG[x + 2 ][y - 1] == NULL) || (allPieceG[x + 2 ][y - 1]->pcolor != turn && allPieceG[x + 2 ][y - 1] != NULL)))
    {
        cP.push_back( modL + 19 );
        if(allPieceG[x + 2 ][y - 1] == NULL)board[x + 2 ][y - 1].setColor(COLOR("green"));
        else
        {
            board[x + 2 ][y - 1].setColor(COLOR("red"));
        }
    }
    //5
    if((y > 1 && x < 7 ) && ((allPieceG[x + 1 ][y - 2] == NULL) || (allPieceG[x + 1][y - 2]->pcolor != turn && allPieceG[x + 1][y - 2] != NULL)))
    {
        cP.push_back( modL + 8 );
        if(allPieceG[x + 1 ][y - 2] == NULL)board[x + 1 ][y - 2].setColor(COLOR("green"));
        else
        {
            board[x + 1 ][y - 2].setColor(COLOR("red"));
        }
    }
    //6
    if((y > 1 && x > 0 ) && ((allPieceG[x - 1 ][y - 2] == NULL) || (allPieceG[x - 1][y - 2]->pcolor != turn && allPieceG[x - 1][y - 2] != NULL)))
    {
        cP.push_back( modL - 12 );
        if(allPieceG[x - 1 ][y - 2] == NULL)board[x - 1 ][y - 2].setColor(COLOR("green"));
        else
        {
            board[x - 1 ][y - 2].setColor(COLOR("red"));
        }
    }
    //7
    if((y > 0 && x > 1 ) && ((allPieceG[x - 2 ][y - 1] == NULL) || (allPieceG[x - 2 ][y - 1]->pcolor != turn && allPieceG[x - 2 ][y - 1] != NULL)))
    {
        cP.push_back( modL - 21 );
        if(allPieceG[x - 2 ][y - 1] == NULL)board[x - 2 ][y - 1].setColor(COLOR("green"));
        else
        {
            board[x - 2 ][y - 1].setColor(COLOR("red"));
        }
    }
    //8
    if((y < 7 && x > 1 ) && ((allPieceG[x - 2 ][y + 1] == NULL) || (allPieceG[x - 2 ][y + 1]->pcolor != turn && allPieceG[x - 2 ][y + 1] != NULL)))
    {
        cP.push_back( modL - 19 );
        if(allPieceG[x - 2 ][y + 1] == NULL)board[x - 2 ][y + 1].setColor(COLOR("green"));
        else
        {
            board[x - 2 ][y + 1].setColor(COLOR("red"));
        }
    }
    endFrame();
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    beginFrame();
    int click = getClick();
    int L2 = getLocation(click);
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 2);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 2);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// Function to handle Bishop
void f3(int L , vector < vector<Rectangle> > & board)
{
    vector <int> cP ; // correctPositions
    beginFrame();
    board[L/10][L%10].setColor(COLOR("blue"));
    int modL = L ;
    while((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 11 );
        if(allPieceG[modL/10 + 1][modL%10 + 1] == NULL)board[modL/10 + 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 + 1].setColor(COLOR("red"));
            break;
        }
        modL = modL + 11;
    }
    modL = L ;
    while(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL + 9 );
        if(allPieceG[modL/10 + 1][modL%10 - 1] == NULL)board[modL/10 + 1 ][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 - 1].setColor(COLOR("red"));
            break ;
        }
        modL = modL + 9 ;
    }
    modL = L ;
    while(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL - 9 );
        if(allPieceG[modL/10 - 1][modL%10 + 1] == NULL)board[modL/10 - 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 + 1].setColor(COLOR("red"));
            break ;
        }
        modL = modL - 9;
    }
    modL = L ;
    while(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
    {
        cP.push_back( modL - 11 );
        if(allPieceG[modL/10 - 1][modL%10 - 1] == NULL)board[modL/10 - 1][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 - 1].setColor(COLOR("red"));
            break;
        }
        modL = modL - 11;
    }
    endFrame();
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    beginFrame();
    int click = getClick();
    int L2 = getLocation(click);
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 3);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 3);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// Function to handle Queen
void f4(int L , vector < vector<Rectangle> > & board)
{
    vector <int> cP ; // correctPositions
    beginFrame();
    board[L/10][L%10].setColor(COLOR("blue"));
    int modL = L ;
    while((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 1 );
        if(allPieceG[modL/10][modL%10 + 1] == NULL)board[modL/10][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 + 1].setColor(COLOR("red"));
            break;
        }
        modL++;
    }
    modL = L ;
    while(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL - 1 );
        if(allPieceG[modL/10][modL%10 - 1] == NULL)board[modL/10][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 - 1].setColor(COLOR("red"));
            break ;
        }
        modL--;
    }
    modL = L ;
    while((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
    {
        cP.push_back( modL - 10 );
        if(allPieceG[modL/10 - 1][modL%10] == NULL)board[modL/10 - 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10].setColor(COLOR("red"));
            break ;
        }
        modL = modL - 10;
    }
    modL = L ;
    while(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
    {
        cP.push_back( modL + 10 );
        if(allPieceG[modL/10 + 1][modL%10] == NULL)board[modL/10 + 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10].setColor(COLOR("red"));
            break;
        }
        modL = modL + 10;
    }
    modL = L ;
    while((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 11 );
        if(allPieceG[modL/10 + 1][modL%10 + 1] == NULL)board[modL/10 + 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 + 1].setColor(COLOR("red"));
            break;
        }
        modL = modL + 11;
    }
    modL = L ;
    while(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL + 9 );
        if(allPieceG[modL/10 + 1][modL%10 - 1] == NULL)board[modL/10 + 1 ][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 - 1].setColor(COLOR("red"));
            break ;
        }
        modL = modL + 9 ;
    }
    modL = L ;
    while(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL - 9 );
        if(allPieceG[modL/10 - 1][modL%10 + 1] == NULL)board[modL/10 - 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 + 1].setColor(COLOR("red"));
            break ;
        }
        modL = modL - 9;
    }
    modL = L ;
    while(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
    {
        cP.push_back( modL - 11 );
        if(allPieceG[modL/10 - 1][modL%10 - 1] == NULL)board[modL/10 - 1][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 - 1].setColor(COLOR("red"));
            break;
        }
        modL = modL - 11;
    }
    endFrame();
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    beginFrame();
    int click = getClick();
    int L2 = getLocation(click);
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 4);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 4);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// Function to handle King
void f5(int L , vector < vector<Rectangle> > & board)
{
    vector <int> cP ; // correctPositions
    beginFrame();
    board[L/10][L%10].setColor(COLOR("blue"));
    int modL = L ;
    if((modL%10 != 7) && ((allPieceG[modL/10][modL%10 + 1] == NULL) || (allPieceG[modL/10][modL%10 + 1]->pcolor != turn && allPieceG[modL/10][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 1 );
        if(allPieceG[modL/10][modL%10 + 1] == NULL)board[modL/10][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 + 1].setColor(COLOR("red"));
        }
    }
    if(((modL)%10 != 0) && ((allPieceG[modL/10][modL%10 - 1] == NULL) || (allPieceG[modL/10][modL%10 - 1]->pcolor != turn && allPieceG[modL/10][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL - 1 );
        if(allPieceG[modL/10][modL%10 - 1] == NULL)board[modL/10][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10][modL%10 - 1].setColor(COLOR("red"));
        }
    }
    if((modL >= 10 && ((allPieceG[modL/10 - 1][modL%10] == NULL) || (allPieceG[modL/10 - 1][modL%10]->pcolor != turn && allPieceG[modL/10 - 1][modL%10] != NULL))))
    {
        cP.push_back( modL - 10 );
        if(allPieceG[modL/10 - 1][modL%10] == NULL)board[modL/10 - 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10].setColor(COLOR("red"));
        }
    }
    if(((modL < 70) && ((allPieceG[modL/10 + 1][modL%10] == NULL) || (allPieceG[modL/10 + 1][modL%10]->pcolor != turn && allPieceG[modL/10 + 1][modL%10] != NULL))))
    {
        cP.push_back( modL + 10 );
        if(allPieceG[modL/10 + 1][modL%10] == NULL)board[modL/10 + 1][modL%10].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10].setColor(COLOR("red"));
        }
    }

    if((modL%10 != 7 && modL/10 != 7) && ((allPieceG[modL/10 + 1][modL%10 + 1] == NULL) || (allPieceG[modL/10 + 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL + 11 );
        if(allPieceG[modL/10 + 1][modL%10 + 1] == NULL)board[modL/10 + 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 + 1].setColor(COLOR("red"));
        }
    }

    if(((modL)%10 != 0 && modL/10 != 7 ) && ((allPieceG[modL/10 + 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 + 1 ][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 + 1][modL%10 - 1] != NULL)))
    {
        cP.push_back( modL + 9 );
        if(allPieceG[modL/10 + 1][modL%10 - 1] == NULL)board[modL/10 + 1 ][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 + 1][modL%10 - 1].setColor(COLOR("red"));

        }
    }
    if(((modL >= 10) && modL%10 != 7 ) && ((allPieceG[modL/10 - 1][modL%10 + 1 ] == NULL) || (allPieceG[modL/10 - 1][modL%10 + 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 + 1] != NULL)))
    {
        cP.push_back( modL - 9 );
        if(allPieceG[modL/10 - 1][modL%10 + 1] == NULL)board[modL/10 - 1][modL%10 + 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 + 1].setColor(COLOR("red"));
        }

    }
    if(((modL > 10 && (modL)%10 != 0 ) && ((allPieceG[modL/10 - 1][modL%10 - 1] == NULL) || (allPieceG[modL/10 - 1][modL%10 - 1]->pcolor != turn && allPieceG[modL/10 - 1][modL%10 - 1] != NULL))))
    {
        cP.push_back( modL - 11 );
        if(allPieceG[modL/10 - 1][modL%10 - 1] == NULL)board[modL/10 - 1][modL%10 - 1].setColor(COLOR("green"));
        else
        {
            board[modL/10 - 1][modL%10 - 1].setColor(COLOR("red"));

        }

    }
    endFrame();
    if(cP.size() == 0)
    {
        makeDefaultColor(L , board);
        return;
    }
    beginFrame();
    int click = getClick();
    int L2 = getLocation(click);
    while(!isPresent(cP , L2))
    {
        if(allPieceG[L2/10][L2%10] != NULL)
        {
            if(allPieceG[L2/10][L2%10] -> pcolor == turn )
            {
                makeDefaultColor(L , board);
                makeDefaultColor(cP , board);
                handleClick(L2 , board);
                return ;
            }
        }
        click = getClick();
        L2 = getLocation(click);
    }

    pieceG deletedPiece ;
    bool deleted = false;
    if(allPieceG[L2/10][L2%10] != NULL)
    {
        deletedPiece = *(allPieceG[L2/10][L2%10]);
        deleted = true ;
    }

    deleteP(L2);
    deleteP(L);
    createP(L2 , turn , 5);
    makeDefaultColor(L , board);
    makeDefaultColor(cP , board);

    endFrame();
    if(isKingOnTarget(turn))
    {
        Text textCheck(cSize / 2 , cSize / 2 , "You will be at Check, Try Another Move");
        beginFrame();
        createP(L , turn , 5);
        deleteP(L2);
        if(deleted)createP(L2 , deletedPiece.pcolor , deletedPiece.ptype);
        endFrame();
        click = getClick();
        int newL = getLocation(click);
        while(allPieceG[newL/10][newL%10] == NULL || allPieceG[newL/10][newL%10] -> pcolor != turn)
        {
            click = getClick();
            newL = getLocation(click);
        }
        handleClick(newL , board);
        return;
    }
    turn = !turn ;
}
// This function checks the type of piece and then further calls the appropriate function
void handleClick(int L , vector < vector<Rectangle> > & board)
{
    switch(allPieceG[L/10][L%10]->ptype)
    {
        case(0):
        f0(L , board);
        break;
        case(1):
        f1(L , board);
        break;
        case(2):
        f2(L , board);
        break;
        case(3):
        f3(L , board);
        break;
        case(4):
        f4(L , board);
        break;
        case(5):
        f5(L , board);
        break;
    }
}

int main()
{
    initCanvas("Chess" , winwidth , cSize);
    {
        // Drawing Chess Board
        beginFrame();

        double lx , ly , cx , cy ;
        lx = ly = cSize / 8.0 ;
        cx = cy = cSize / 16.0 ;
        Rectangle r;
        r.setFill(true);
        r.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 , winwidth - cSize , cSize);
        r.setColor(COLOR("white"));
        r.imprint();
        Text text1(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 - cSize / 8.0 , "Player_1 : White" );
        Text text2(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 - cSize / 16.0 , "Player_2 : Black" );
        vector < vector<Rectangle> > board ( 8 , vector<Rectangle>(8));
        for(int j = 0 ; j < 8 ; j++)
        {
            for(int i = 0 ; i < 8 ; i++)
            {
                r.reset(cx + lx * i , cy + ly * j , lx , ly) ;
                if((i + j) % 2 == 0) r.setColor(COLOR(255,211,155)); // Light Brown
                else r.setColor(COLOR(139,115,85)); // Dark Brown
                board[i][j] = r ;
            }
        }
        //Exit Button
        r.reset(winwidth - 10 , 10 , 20 , 20);
        r.setColor(COLOR("red"));

        //Arrange Pieces at initial position
        for(int i = 0 ; i < 8 ; i++)
        {
            createP(i , 1 , false , 0 );
            createP(i , 6 , true , 0 );
        }
        for(int i = 0 ; i < 8 ; i++)
        {
            if(i == 0 || i == 7)
            {
                createP(i * 10 + 0 , false , 1);
                createP(i * 10 + 7 , true , 1);
            }
            if(i == 1 || i == 6)
            {
                createP(i * 10 + 0 , false , 2);
                createP(i * 10 + 7 , true , 2);
            }
            if(i == 2 || i == 5)
            {
                createP(i * 10 + 0 , false , 3);
                createP(i * 10 + 7 , true , 3);
            }
            if(i == 3)
            {
                createP(i * 10 + 0 , false , 4);
                createP(i * 10 + 7 , true , 4);
            }
            if(i == 4)
            {
                createP(i * 10 + 0 , false , 5);
                createP(i * 10 + 7 , true , 5);
            }
        }
        //Arrange Pieces at initial position : Completed
        Text text3(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 16.0 , "Whose Turn : " );
        Text text4(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 8.0 , "White" );
        //Start Getting Click until the end of game

        endFrame();

        int click = getClick();
        while(!gameComplete && (click/65536 < winwidth - 20 && click%65536 > 20))
        {
            Text textCheck;
            int L = getLocation(click);
            //If clicked location has a piece of appropriate color then we will call the function
            //to handle that click
            if(allPieceG[L/10][L%10] != NULL)
            {
                if (allPieceG[L/10][L%10]->pcolor == turn) handleClick(L , board);
            }
            if(gameComplete)
            {
                if(turn) text3.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 16.0 , "Player_1(White) won !!!!" );
                else text3.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 16.0 , "Player_2(Black) won !!!!" );
                text4.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 8.0 , "Click anywhere to exit." );

            }
            else
            {
                if(turn) text4.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 8.0 , "White" );
                else text4.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 8.0 , "Black" );
            }
            if(isKingOnTarget(turn))
            {
                string s ; if(turn) s = "White" ; else s = "Black";
                if(isCheckmate(turn))
                {
                    if(!turn) text3.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 16.0 , "Player_1(White) won !!!!" );
                    else text3.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 16.0 , "Player_2(Black) won !!!!" );
                    textCheck.reset(cSize / 2 , cSize / 2 , "Checkmate !");
                    text4.reset(cSize + (winwidth - cSize)/2.0 , cSize / 2.0 + cSize / 8.0 , "Click anywhere to exit." );
                    click = getClick();
                    break;
                }
                else textCheck.reset(cSize / 2 , cSize / 2 , "Check to " + s);
            }
            click = getClick();
        }
        //Freeing up memory at the end
        beginFrame();
        for(int j = 0 ; j < 8 ; j++)
        {
            for(int i = 0 ; i < 8 ; i++ ) deleteP(i , j);

        }
    }
    endFrame();
    return 0;
}

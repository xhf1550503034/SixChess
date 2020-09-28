#include<iostream>
#include<stack>
#include<iomanip>
#include<string>
#define BLACK 0
#define WHITE 1;
using namespace std;
//棋子类，包含位置、哪方棋手等属性，以及构造函数，对外接口函数
class ChessNode {
    private:
        int location_x;
        int location_y;
        int playerid;//判断棋手 -1为无人下，0为持黑棋者，1为持白棋者
    public:
        //ChessNode(int x, int y) {
           // location_x = x;
            //location_y = y;
            //playerid = -1;
        //}//构造函数  playerid初始化为-1
        void SetX(int x) {
            location_x = x;
        }
        void setY(int y) {
            location_y = y;
        }
        void setId(int id) {
            playerid = id;
        }
        int getX() {
            return location_x;
        }
        int getY() {
            return location_y;
        }
        int getId() {
            return playerid;
        }
       
        void setChessNode(int x, int y,int id) {
            location_x = x;
            location_y = y;
            playerid = id;

        }
};
class Chessboard {
private:
    int size;
    ChessNode ** board;//二级指针
    stack <ChessNode> route;//所下的棋的路径
public:
    int getSize() {
        return size;
    }
    ChessNode** getBoard() {
        return board;
    }
    Chessboard(int size) {
        this->size = size;
        board = new ChessNode* [size + 2];
        for (int i = 0; i < size + 2; i++) {
            board[i] = new ChessNode [size + 2];
            for (int j = 0; j < size + 2; j++) {
                board[i][j].setChessNode(i, j, -1);
            }
        }

    }//构建棋盘
    
    void PlaceChessNode(int x, int y, int id) {
        if (board[x][y].getId()==-1 && x >= 1 && x <= size && y >= 1 && y <= size) {
            board[x][y].setChessNode(x, y, id);
            addtoRoute(board[x][y]);
        }
    }//放置棋子 只有所放置位置的playerid=-1时才能放棋子
    ChessNode showChessNode(int x, int y) {
        if (x >= 1 && x <= size && y >= 1 && y <= size) {
            return board[x][y];
        }
        else return board[0][0];
    }
    void addtoRoute(ChessNode c) {
        route.push(c);
    }//将下的棋压入栈中
    ChessNode showLatestNode() {
        if (!route.empty()) {
            ChessNode lc = route.top();
            return lc;
        }
        else {
            return board[0][0];
        }
    }//返回最近下的一步棋

    void ResetLCN() {
        if (!route.empty()) {
            ChessNode c = route.top();
            board[c.getX()][c.getY()].setId(-1);
            route.pop();
        }

    }//悔棋
    void showChessboard() {
        cout << "    ";
        for (int i = 1; i <= size; i++) {
            cout << setw(4) << i;
      }
        cout << endl;
        for (int i = 1; i <= size; i++) {
            cout << setw(4) << i;
            for (int j = 1; j <= size; j++) {
                if (board[i][j].getId() == -1) {
                    cout << setw(4) << '#';
                }
                else if (board[i][j].getId() == BLACK) {
                    cout << setw(4) << 'x';
                }
                else {
                    cout << setw(4) << 'o';
                }
            }
            cout << endl;
        }
    }
    
    
};
class Algorithm {
public:
   
    bool bKMP(string longstr, string shortstr) {
        char* longarr = (char*)longstr.c_str();
        char* shortarr = (char*)shortstr.c_str();
        for (int i = 0; i < longstr.length();) {
            int tmp = i;
            for (int j = 0; j < shortstr.length();) {
                if (longarr[i] == shortarr[j]) {
                    i++; j++;
                    if (j == shortstr.length()) {
                        return true;
                    }
                }
                else {
                    j = 0; i = tmp + 1;
                    break;
                }
            }
        }
        return false;
    }//返回bool类型的KMP算法 即长字符串中是否含有短字符串
    int iKMP(string longstr, string shortstr) {
        char* longarr = (char*)longstr.c_str();
        char* shortarr = (char*)shortstr.c_str();
        int count = 0;
        for (int i = 0; i < longstr.length();) {
            int tmp = i;
            for (int j = 0; j < shortstr.length();) {

                if (longarr[i] == shortarr[j]) {
                    i++; j++;
                    if (j == shortstr.length()) {
                        count++;
                        j = 0; i = tmp + 1;
                        break;
                    }
                }
               
                else {
                    j = 0; i = tmp + 1;
                    break;
                }
                
            }
        }
        return count;

    }//返回int类型的KMP算法 即长字符串中有几个短字符串
    string NodeTranslate(ChessNode c) {
        string str;
        if (c.getId() == -1) {
            str = "#";
        }
        else if (c.getId() == BLACK) {
            str = "x";
        }

        else if(c.getId()== 1){
            str ="o";
        }
        else {
            str = "";
        }
        return str;
    }
    string strReverse(string str) {
        string strr = "";
        for (int i = str.length() - 1; i >= 0; i--) {
            strr += str.at(i);
        }//最后一位是'\0';
        return strr;
    }
    string * ScanNode(Chessboard board, int size, ChessNode** node) {
        string * str=new string[8];
        for (int i = 0; i < 8;i++) {
            str[i] = "";

        }
        //str[0]从左到右扫描
        for (int i = 1; i <= size; i++) {
            str[0] += NodeTranslate(node[board.showLatestNode().getX()][i]);
        }
        //str[1]从上到下扫描
        for (int i = 1; i <= size; i++) {
            str[1] += NodeTranslate(node[i][board.showLatestNode().getY()]);
        }
        //str[2]从左上到右下扫描
        string tmp = "";
        for (int i = board.showLatestNode().getX(), j = board.showLatestNode().getY(); i >= 1 && j >= 1; i--, j--) {
            tmp += NodeTranslate(node[i][j]);
        }
        str[2] += strReverse(tmp);
        for (int i = board.showLatestNode().getX()+1, j = board.showLatestNode().getY()+1; i <= size && j <=size; i++, j++) {
            str[2] += NodeTranslate(node[i][j]);
        }
        //str[3]从左下到右上扫描
        string tmp1 = "";
        for (int i = board.showLatestNode().getX(), j = board.showLatestNode().getY(); i<=size && j >= 1; i++, j--) {
            tmp1 += NodeTranslate(node[i][j]);
        }
        str[3] += strReverse(tmp1);
        for (int i = board.showLatestNode().getX()-1, j = board.showLatestNode().getY()+1; i >= 1 && j <= size; i--, j++) {
            str[3] += NodeTranslate(node[i][j]);
        }
        for (int i = 4; i < 8; i++) {
            str[i] = strReverse(str[i - 4]);
        }
        return str;
    }
    
    
    
    int judge(Chessboard board, int size) {
        
       string * str = ScanNode(board, size, board.getBoard());
      
       //判断长连禁手
       bool flag[4] = { false,false,false,false };
       bool flag1 = false;
       for (int i = 0; i < 4; i++) {
           if (bKMP(str[i], "xxxxxxx")) {
               flag[i] = true;
               flag1 = true;
           }
           if (flag1) {
               for (int i = 0; i < 4; i++) {
                   if (!flag[i] && bKMP(str[i], "xxxxxx")) {
                       cout << "BLACK wins";
                       return BLACK;
                       
                   }
               }
               cout << "WHITE wins";
               return WHITE;


           }

       }//先判断有无长连禁手 如果有 再看其它方向上有无六连子 如果有 优先胜利
        //判断六连子
        for (int i = 0; i < 8; i++) {
            if (bKMP(str[i], "xxxxxx")) {
                cout << "BLACK wins";
                return BLACK;
            }
            else if (bKMP(str[i], "oooooo")) {
                cout << "WHITE wins";
                return WHITE;
            }
        }
        
       
        string BanRoute4[3] = { "#xxxx#","#xx#xx#","#xxx#x#"};
        int weights4[3] = { 1,1,2};
        string BanRoute5[5] = { "xxxx#x","xxx#xx","#xxxxx#","oxxxxx#","xxxxx#o"};
        int weights5[5] = { 2,2,1,2,2 };
        //判断四四禁手
        int tmp4=0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 8; j++) {
                tmp4 += weights4[i] * iKMP(str[j], BanRoute4[i]);
            }

        }
        if (tmp4 > 2) {
            cout << "WHITE wins";
            return WHITE;
        }
        //判断五五禁手
        int tmp5=0;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < 8; j++) {
                tmp4 += weights5[i] * iKMP(str[j], BanRoute5[i]);
            }

        }
        if (tmp5 > 2) {
            cout << "WHITE wins";
            return WHITE;
        }
        return -1;

    }
};

int main() {
   
    int size=6;
    Algorithm algorithm;
    Chessboard board(size);
   board.showChessboard();
  int x; int y; int id;
   bool isBlack = true;
    
    while (cin >> x >> y) {
        if (isBlack) {
            id = BLACK;
            ChessNode tmp = board.showLatestNode();
            if (tmp.getX() != x || tmp.getY() != y) {
              board.PlaceChessNode(x, y, id);
              board.showChessboard();
                string* str = algorithm.ScanNode(board, size, board.getBoard());

        for (int i = 0; i < 8; i++) {
            cout << str[i] << "  ";
        }
        cout << endl;
        int judge = algorithm.judge(board, size);
        cout << judge << endl;
       
             /* if (algorithm.judge(board, size) == BLACK) {
                   cout << "BLACK WINS";
               }
               else if (algorithm.judge(board, size) == 1) {
                  cout << "WHITE WINS";
               }*/
                
                isBlack = !isBlack;
            }//为了避免两次输入的xy坐标一样 会导致后下的棋子冲掉原来的棋子
       }
        else {
           id = WHITE;
           ChessNode tmp = board.showLatestNode();
            if (tmp.getX() != x || tmp.getY() != y) {
                board.PlaceChessNode(x, y, id);
                board.showChessboard();
                  string* str = algorithm.ScanNode(board, size, board.getBoard());

        for (int i = 0; i < 8; i++) {
            cout << str[i] << "  ";
        }
        int judge = algorithm.judge(board, size);
        cout << judge << endl;
        
               /*if (algorithm.judge(board, size) == BLACK) {
                   cout << "BLACK WINS";
               }
                else if (algorithm.judge(board, size) == 1) {
                    cout << "WHITE WINS";
                }*/
              isBlack = !isBlack;
            }
       }
        cout << endl;
       

    }
   /* Algorithm algorithm;
    if (algorithm.bKMP("fabcd", "ac")) {
        cout << "true" << endl;
    }
    else { 
        cout << "false" << endl; 
    }
    int count = algorithm.iKMP("ffffabcfff", "ff");
    cout << "count=" << count << endl;*/
   
    /*int size; cin >> size;
    Chessboard board(size);
    Algorithm algorithm;
    board.showChessboard();
    int x, y, id;
    while (cin >> x >> y >> id) {
        board.PlaceChessNode(x, y, id);
        board.showChessboard();
        string* str = algorithm.ScanNode(board, size, board.getBoard());
        
        for (int i = 0; i < 8; i++) {
            cout << str[i] << "  ";
        }
        cout << endl;
       // int judge = algorithm.judge(board, size);
        //cout << judge << endl;
      /*if (algorithm.judge(board, size) == 0) {
        cout << "BLACK WINS";
              }
        if (algorithm.judge(board, size) == 1) {
                        cout << "WHITE WINS";
         }*/
        
    //}
        return 0;
}

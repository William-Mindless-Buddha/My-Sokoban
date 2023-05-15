#include <iostream>
#include <easyx.h>
#include <conio.h>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <set>
#include <fstream>
#include <algorithm>
using namespace std;


IMAGE images_initialgameinterface[10];//用来存游戏初始界面相关图片

IMAGE images_selectlevelinterface[1];//用来存游戏普通关卡选关界面相关图片

IMAGE images_level[17];//用来存游戏关卡中的相关图片

IMAGE images_createcustomlevel[8];//用来存自定义功能界面的相关图片

class Box
{
private:
	int boxx;//箱子在地图上的横坐标
	int boxy;//箱子在地图上的纵坐标
public:
	void setbox(int x, int y);//设置箱子在地图上的横纵坐标
	int getboxx();//获取箱子在地图上的横坐标
	int getboxy();//获取箱子在地图上的纵坐标
};

class Target
{
private:
	int targetx;//目标点位在地图上的横坐标
	int targety;//目标点位在地图上的纵坐标
public:
	void settargetxy(int x, int y);//设置目标点位在地图上的横纵坐标
	int gettargetx();//获取目标点位在地图上的横坐标
	int gettargety();//获取目标点位在地图上的纵坐标
};

class Wall
{
private:
	int wallx;//墙在地图上的横坐标
	int wally;//墙在地图上的纵坐标
public:
	void setwallxy(int x, int y);//设置墙在地图上的横纵坐标
	int getwallx();//获取墙在地图上的横坐标
	int getwally();//获取墙在地图上的纵坐标
};

class Map
{
private:
	int Row = NULL;//地图行数
	int Col = NULL;//地图列数
	vector<vector<int>> map0;//地图二维数组
public:
	void setmaprc(int r, int c);//设置地图行列数同时初始化地图
	int getmapr();//获取地图行数
	int getmapc();//获取地图列数
	int getmap0data(int x, int y);//获取地图特定坐标上的数值
	void showmap();//打印地图
	void SetOnMap(int x,int y,int data);//将某物设置在地图上
};

class Character
{
private:
	int characterx0;//角色在地图上的横坐标
	int charactery0;//角色在地图上的纵坐标
	int Orientation;//角色朝向
public:
	void setcharacter(int x, int y, int o);//设置角色相关数据（横、纵坐标及朝向）
	int getcharacterx();//获取角色在地图上的横坐标
	int getcharactery();//获取角色在地图上的纵坐标
	int getcharactero();//获取角色朝向
	void characteroperate0(char ch);//操作角色并向后移动
	void characteroperate1(char ch);//操作角色并移动
};

class Gamelevel
{
public:
	int row;//当前关卡的地图行数
	int col;//当前关卡的地图列数
	int boxnum;//当前关卡的箱子数
	int targetnum;//当前关卡的目标点位数
	int wallnum;//当前关卡的墙数
	int reachedboxes;//当前关卡达到目标点位的箱子数
	vector<Box> box;//用于存当前关卡每个箱子信息的数组
	map<pair<int, int>, int> boxindex2whichbox;//从箱子坐标映射到第几个箱子
	map<int, pair<int, int>> whichbox2boxindex;//从第几个箱子映射到箱子坐标
	vector<Target> target;//用于存当前关卡每个目标点位信息的数组
	set<pair<int, int>> target_index;//用于存目标点位坐标
	vector<Wall> wall; //用于存当前关卡每个墙信息的数组
	Map gamemap;//当前关卡的地图
	Character character;//当前关卡的角色
	string encode;//对游戏关卡信息的编码，编码规则：数字间用逗号隔开，前7个数字分别为reachedbox、box、target、wall的数量和characterx、charactery、charactero，之后的数字前box对为box坐标，中间target对为target坐标，最后wall对为墙坐标
	string savedcode;//编码规则同上，表示存档的编码
	string gamename;//游戏关卡名
	int score;//游戏关卡得分
	Gamelevel(int r, int c, string code, string name);//初始化关卡
	void DeCode(int kind);//对关卡信息字符串进行解码，kind为0表示初始编码，kind为1表示存档的编码
	void MoveCharactar(char ch);//移动一个角色
	void SetBoxOnMap(int i);//将箱子设置在地图上
	void SetTargetOnMap(int i);//将目标点位设置在地图上
	void SetWallOnMap(int i);//将墙设置在地图上
	//void SetCharactarOnMap();//将角色设置在地图上
	void SetAllOnMap();//将所有物件设置在地图上
	int whichbox(int x, int y);//判断指定位置的箱子是第几个箱子
	int win();//判断某关是否赢
	void OpenLevel();//打开关卡窗口
	void CloseLevel();//关闭关卡窗口
	void DrawLevel();//绘制关卡
	void DrawChangedImage(int prex, int prey, int predata, int nowx, int nowy, int nowdata, int sufx, int sufy, int sufdata);//绘制角色移动后图片改变的部分
};

map<string, string> users_accountnumber2password;//用户账号及加密后的密码

map<string, string> users_accountnumber2name;//用户账号及用户名

set<string> users_names;//用户名集合

map<string, string> user_totalscore;//用户名映射到该用户的总得分

map<string, map<string, string>> user_level_score;//用户名映射到该用户游玩过的关卡的关卡名及该关卡对应的得分

string PasswordKey = "thequickbrownfoxjumpsoverthelazydog";//加密用户密码的密钥

map<char, char> encrypted_key;//加密密钥的映射关系


void LoadResource_InitialGameInterface();//加载游戏初始界面图片

void LoadResource_SelectLevelInterface();//加载选关界面图片

void LoadResource_Level();//加载关卡图片

void LoadResource_CreateCustomLevel();//加载关卡自定义界面图片

void OpenInitialGameInterface();//打开游戏初始界面

void OpenSelectLevelInterface();//打开选关界面

void OpenNamingCustomLevel();//打开自定义关卡命名界面

void OpenCreateCustomLevel();//打开关卡自定义界面

void OpenSelectCustomLevelInterface(int c);//打开自定义关卡选关界面

void OpenLoginInputInterface();//打开登录信息输入窗口

void OpenRegisterInputInterface();//打开注册信息输入窗口

void OpenTheRankingList();//打开排行榜页面

void CloseInitialGameInterface();//关闭游戏初始界面

void CloseSelectLevelInterface();//关闭选关界面

void CloseNamingCustomLevel();//关闭自定义关卡命名界面

void CloseSelectCustomLevelInterface();//关闭自定义关卡选关界面

void CloseLoginInputInterface();//关闭登录输入界面

void CloseRegisterInputInterface();//关闭注册输入界面

void CloseTheRankingList();//关闭排行榜页面

void DrawInitialGameInterface0();//绘制游戏初始界面，按钮为开始游戏、排行榜

void DrawInitialGameInterface1();//绘制游戏初始界面，按钮为普通关卡、自定义关卡、返回

void DrawInitialGameInterface2();//绘制自定义关卡初始界面，按钮为新建关卡、选择关卡、返回

void DrawInitialGameInterface3();//绘制登录、注册界面，按钮为登录、注册、返回

void DrawSelectLevelInterface();//绘制选关界面

string DrawNamingCustomLevel_and_ReturnName(bool& ifcancel);//绘制自定义关卡命名界面并返回文件名

void DrawCreateCustomLevel_and_CreateCustomLevel(map<int, set<pair<int, int>>>& w_b_t, Character& c, int& r, string levelname);//绘制关卡自定义界面并进行自定义，w_b_t代表墙、箱子、目标点位的信息，c代表角色信息，r代表达到目标点位的箱子数量

void DrawSelectCustomLevelInterface(int c);//绘制自定义关卡选关界面

vector<string> DrawLoginInputInterface(bool& ifcancel);//绘制登录的输入界面，并返回账户及密码的输入值

vector<string> DrawRegisterInputInterface(bool& ifcancel);//绘制注册信息输入界面，并返回注册信息

void DrawTheRankingList();//绘制排行榜页面

bool whethercircle(set<pair<int, int>> wallindex, set<pair<int, int>>& circlenode);//判断自定义关卡中的墙体是否可围成一个环

bool whetherincircle(set<pair<int, int>> wall, set<pair<int, int>> box, set<pair<int, int>> target, Character c, set<pair<int, int>>& circlenode);//是否所有物件都在墙体围成的环内

void reports_createcustomlevel_errors(int errornum);//自定义关卡报错

string encode_createcustomlevel(map<int, set<pair<int, int>>>& wbt, Character& c, int mintop, int minleft, int reachedboxnum);//对自定义的关卡信息进行编码

int Mousemessage(ExMessage* msg);//选关卡

int Mousemessage_customlevel(ExMessage* msg);//选自定义关卡

void PlayGame(Gamelevel& ln, string username);//游玩关卡

void PlayCustomGame(Gamelevel& ln, string username);//游玩自定义关卡

void allocation_encryption_key();//对密钥字符串进行加密分配

string encrypt_password(string password);//给密码加密，并返回加密的密码

void Find_total_score();//求每个用户的总分

void Change_User_Level_Score();//更改某用户关卡分数


int main()
{
	LoadResource_InitialGameInterface();//加载游戏初始界面图片
	LoadResource_SelectLevelInterface();//加载普通关卡选关界面图片
	LoadResource_Level();//加载游戏关卡图片
	LoadResource_CreateCustomLevel();//加载自定义功能界面图片
	allocation_encryption_key();//对密钥进行加密分配，将其中的各个字母依据某规则映射到其他字母上，并存进encrypted_key
	ifstream user_count_fin("Users\\user_count.dat", ios::in);//创建一个文件为Users\\user_count.dat的文件输入流对象，用于对程序传入之前注册的用户量
	int user_acount = 0;//初始化用户量为0
	user_count_fin >> user_acount;//用文件输入流输入已注册的用户量
	for (int i = 0; i < user_acount; i++)//枚举用户编号，并用文件流的方式传入已注册的所有用户信息（用户名、账号、密码），并将这些信息用于初始化users_accountnumber2password、users_accountnumber2name、users_names
	{
		string userNo = "Users\\" + to_string(i) + ".dat";
		ifstream userinformationfin(userNo, ios::in);
		string user_name = "";
		string user_account_number = "";
		string user_account_password = "";
		userinformationfin >> user_name >> user_account_number >> user_account_password;
		if (user_account_number.size() != 0 && user_account_password.size() != 0)users_accountnumber2password[user_account_number] = user_account_password;
		if (user_name.size() != 0)
		{
			users_accountnumber2name[user_account_number] = user_name;
			if (!users_names.count(user_name))users_names.insert(user_name);
		}
	}
	Change_User_Level_Score();//将用户游玩过的各关卡得分存入user_level_score
	Find_total_score();//将用户总分存入user_totalscore
	string l0code = "0,1,1,24,2,2,4,2,4,2,5,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,0,8,1,0,1,8,2,0,2,8,3,0,3,8,4,0,4,1,4,2,4,3,4,4,4,5,4,6,4,7,4,8,";
	string l1code = "0,4,4,36,4,4,4,3,5,4,3,5,6,6,4,1,5,4,1,5,8,8,4,0,4,0,5,0,6,1,4,1,6,2,4,2,6,3,0,3,1,3,2,3,3,3,4,3,6,4,0,4,6,4,7,4,8,4,9,5,0,5,1,5,2,5,3,5,9,6,3,6,5,6,6,6,7,6,8,6,9,7,3,7,5,8,3,8,5,9,3,9,4,9,5,";
	string l2code = "0,2,2,26,2,1,4,3,2,3,5,1,1,1,5,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,1,0,1,7,2,0,2,7,3,0,3,7,4,0,4,4,4,5,4,6,4,7,5,0,5,4,6,0,6,1,6,2,6,3,6,4,";
	string l3code = "0,8,8,68,8,13,4,2,5,2,9,4,7,5,9,6,6,7,7,8,9,9,7,6,3,6,4,7,3,7,4,8,3,8,4,9,3,10,3,0,2,0,3,0,4,0,5,0,6,0,7,0,8,0,9,0,10,1,2,1,10,2,2,2,10,3,0,3,1,3,2,3,3,3,4,3,5,3,10,4,0,4,10,4,11,5,0,5,11,6,0,6,8,6,9,6,11,6,12,6,13,6,14,7,0,7,8,7,9,7,14,8,0,8,14,9,0,9,4,9,5,9,6,9,8,9,9,9,10,9,12,9,14,10,0,10,12,10,13,10,14,11,0,11,12,12,0,12,12,13,0,13,1,13,2,13,3,13,4,13,5,13,6,13,7,13,8,13,9,13,10,13,11,13,12,";
	string l4code = "0,3,3,26,1,3,4,3,3,5,2,5,3,4,2,4,3,4,4,0,1,0,2,0,3,0,4,0,5,1,1,1,5,2,0,2,1,2,5,3,0,3,1,3,2,3,5,4,0,4,5,5,0,5,5,6,0,6,1,6,5,7,1,7,2,7,3,7,4,7,5,";
	string l5code = "0,5,5,98,1,16,4,3,6,4,6,7,2,7,5,8,5,6,16,7,15,7,16,8,15,8,16,0,4,0,5,0,6,0,7,0,8,0,9,0,10,0,11,0,12,0,13,0,14,0,15,0,16,0,17,1,4,1,17,2,4,2,8,2,9,2,10,2,11,2,12,2,13,2,14,2,15,2,16,2,17,3,2,3,3,3,4,3,8,3,9,3,14,3,16,4,2,4,9,4,14,4,16,5,0,5,1,5,2,5,4,5,6,5,7,5,9,5,12,5,13,5,14,5,15,5,16,5,17,5,18,5,19,6,0,6,4,6,6,6,7,6,9,6,10,6,11,6,12,6,19,7,0,7,19,8,0,8,1,8,2,8,3,8,4,8,6,8,7,8,8,8,10,8,11,8,12,8,19,9,4,9,10,9,11,9,12,9,19,10,4,10,5,10,6,10,7,10,8,10,9,10,10,10,12,10,19,11,12,11,13,11,14,11,15,11,16,11,17,11,18,11,19,";
	string l6code = "0,3,3,23,1,4,4,3,1,3,2,3,3,2,1,2,2,2,3,0,0,0,1,0,2,0,3,0,4,0,5,1,0,1,5,2,0,2,5,3,0,3,5,4,0,4,5,5,0,5,5,6,0,6,1,6,2,6,3,6,4,6,5,2,4,";
	string l7code = "0,10,10,69,3,11,4,5,10,6,5,6,11,7,11,9,7,8,10,10,8,9,11,11,7,10,10,3,3,3,4,4,3,4,4,5,3,5,4,6,3,6,4,7,3,7,4,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,1,0,1,7,2,0,2,7,2,9,2,10,2,11,2,12,2,13,3,0,3,7,3,9,3,10,3,12,3,13,4,0,4,7,4,8,4,9,4,13,5,0,5,13,6,0,6,7,6,9,6,13,7,0,7,7,7,9,7,13,8,0,8,1,8,2,8,3,8,4,8,5,8,6,8,7,8,9,8,13,9,5,9,9,9,13,10,5,10,9,10,13,11,5,11,13,12,5,12,8,12,9,12,13,13,5,13,6,13,7,13,8,13,9,13,10,13,11,13,12,13,13,";
	string l8code = "0,4,4,20,2,3,4,2,1,2,2,3,3,2,4,1,1,1,2,1,3,1,4,0,0,0,1,0,2,0,3,0,4,0,5,1,0,1,5,2,0,2,5,3,0,3,5,4,0,4,5,5,0,5,1,5,2,5,3,5,4,5,5,";
	string l9code = "0,11,11,81,2,4,4,2,9,2,10,3,6,4,3,5,9,6,2,7,2,7,4,7,6,9,2,9,3,8,11,9,10,9,11,10,10,10,11,11,10,11,11,12,10,12,11,13,10,13,11,0,7,0,8,0,9,0,10,0,11,1,0,1,1,1,2,1,3,1,4,1,5,1,6,1,7,1,11,1,12,2,0,2,1,2,3,2,6,2,7,2,12,3,0,3,12,4,0,4,6,4,7,4,8,4,12,5,0,5,1,5,2,5,4,5,5,5,6,5,7,5,8,5,10,5,11,5,12,5,13,5,14,6,0,6,5,6,6,6,7,6,14,7,0,7,14,8,0,8,5,8,6,8,7,8,14,9,0,9,5,9,7,9,14,10,0,10,3,10,4,10,5,10,7,10,14,11,0,11,1,11,2,11,3,11,7,11,14,12,7,12,14,13,7,13,14,14,7,14,8,14,9,14,10,14,11,14,12,14,13,14,14,";
	string l10code = "0,4,4,34,3,1,4,2,2,2,4,5,4,5,6,3,3,3,5,4,3,4,5,0,3,0,4,0,5,0,6,0,7,1,0,1,1,1,2,1,3,1,7,1,8,2,0,2,8,3,0,3,2,3,6,3,8,4,0,4,2,4,6,4,8,5,0,5,8,6,0,6,1,6,5,6,6,6,7,6,8,7,1,7,2,7,3,7,4,7,5,";
	string l11code = "0,6,6,42,1,1,4,2,2,4,2,6,2,6,4,4,4,4,6,3,2,5,2,7,2,6,5,4,5,1,5,0,0,0,1,0,2,0,3,0,4,0,5,0,6,1,0,1,3,1,6,2,0,2,3,2,6,2,7,2,8,2,9,3,0,3,3,3,9,4,0,4,9,5,0,5,3,5,4,5,5,5,6,5,9,6,0,6,9,7,0,7,3,7,9,8,0,8,1,8,2,8,3,8,4,8,5,8,6,8,7,8,8,8,9,";
	string l12code = "0,6,6,58,1,5,4,2,5,3,5,3,8,4,9,6,8,6,10,8,3,8,4,8,5,9,3,9,4,9,5,0,4,0,5,0,6,0,7,0,8,1,4,1,7,1,8,1,9,1,10,1,11,2,3,2,4,2,7,2,8,2,11,3,3,3,11,4,3,4,7,4,8,4,11,5,0,5,1,5,2,5,3,5,4,5,5,5,7,5,8,5,10,5,11,5,12,6,0,6,12,7,0,7,12,8,0,8,8,8,9,8,10,8,11,8,12,9,0,9,8,10,0,10,8,11,0,11,8,12,0,12,1,12,2,12,3,12,4,12,5,12,6,12,7,12,8,";
	string l13code = "0,2,2,30,5,2,4,2,2,4,6,2,6,4,2,0,3,0,4,0,5,0,6,0,7,1,1,1,0,1,2,1,3,1,7,2,0,2,5,2,7,2,8,3,0,3,8,4,0,4,1,4,3,4,8,5,1,5,5,5,6,5,7,5,8,6,1,6,2,6,3,6,4,6,5,";
	string l14code = "0,5,5,47,4,1,4,3,3,2,5,2,7,3,2,3,7,6,8,6,10,7,8,7,9,7,10,0,0,0,1,0,2,0,3,0,4,0,5,0,6,0,7,0,8,0,9,1,0,1,1,1,9,2,0,2,4,2,6,2,9,3,0,3,9,3,10,3,11,3,12,3,13,4,0,5,4,4,4,4,5,4,13,5,0,5,1,5,2,5,3,5,5,5,13,6,5,6,13,7,5,7,13,8,5,8,6,8,7,8,8,8,9,8,10,8,11,8,12,8,13,";
	string l15code = "0,2,2,52,9,2,4,4,5,5,4,6,7,7,6,0,3,0,4,0,5,1,2,1,3,1,5,1,7,1,8,1,9,1,10,2,1,2,2,2,5,2,6,2,7,2,10,3,0,3,1,3,10,4,0,4,7,4,10,5,0,5,1,5,2,5,5,5,6,5,7,5,10,6,2,6,5,6,10,7,1,7,2,7,4,7,5,7,7,7,9,7,10,8,1,8,8,8,9,9,1,9,7,9,8,10,1,10,2,10,3,10,4,10,5,10,6,10,7,";
	string l16code = "0,3,3,45,1,1,4,2,2,2,3,3,2,2,7,3,7,4,7,0,0,0,1,0,2,0,3,0,4,1,0,1,4,1,6,1,7,1,8,1,9,1,10,2,0,2,4,2,6,2,10,3,0,3,4,3,6,3,10,4,0,4,1,4,2,4,4,4,5,4,6,4,10,5,1,5,2,5,10,6,1,6,5,6,10,7,1,7,5,7,6,7,7,7,8,7,9,7,10,8,1,8,2,8,3,8,4,8,5,";
	string l17code = "0,4,4,43,3,5,4,2,5,3,7,3,10,4,9,5,3,5,4,6,3,6,4,0,4,0,5,0,6,0,7,0,8,0,9,0,10,1,4,1,10,1,11,1,12,2,0,2,1,2,2,2,3,2,4,2,6,2,7,2,8,2,12,3,0,3,12,4,0,4,7,4,11,4,12,5,0,5,7,5,11,6,0,6,7,6,8,6,9,6,10,6,11,7,0,7,1,7,2,7,3,7,4,7,5,7,6,7,7,";
	string l18code = "0,4,4,26,2,1,4,2,2,3,2,4,3,5,2,5,1,6,2,6,3,6,4,0,1,0,2,0,3,0,4,1,0,1,1,1,4,2,0,2,4,3,0,3,1,3,4,3,5,4,0,4,1,4,5,5,0,5,5,6,0,6,5,7,0,7,1,7,2,7,3,7,4,7,5,";
	string l19code = "0,4,4,62,8,11,4,4,4,4,6,6,4,6,6,2,4,4,8,6,2,8,6,0,3,0,4,0,5,0,6,0,7,0,8,0,9,1,0,1,1,1,2,1,3,1,9,2,0,2,5,2,6,2,7,2,9,3,0,3,2,3,4,3,9,3,10,4,0,4,2,4,7,4,10,5,0,5,2,5,8,5,10,6,0,6,3,6,8,6,10,7,0,7,1,7,6,7,8,7,10,7,11,7,12,8,1,8,3,8,4,8,5,8,12,9,1,9,7,9,8,9,12,10,1,10,2,10,3,10,4,10,5,10,6,10,7,10,8,10,9,10,10,10,11,10,12,";
	OpenInitialGameInterface();//打开游戏初始界面
	DrawInitialGameInterface0();//绘制游戏初始界面，按钮为：开始游戏、排行榜
	while (1)//进入游戏初始界面（按钮为：开始游戏、排行榜）循环
	{
		ExMessage msg1;
		if (peekmessage(&msg1, EM_MOUSE))//捕获鼠标信息
		{
			switch (msg1.message)
			{
			case WM_LBUTTONDOWN://按下左键
				int x1 = msg1.x;//当前鼠标在窗口中的横坐标
				int y1 = msg1.y;//当前鼠标在窗口中的纵坐标
				if (x1 >= 150 && x1 <= 350 && y1 >= 144 && y1 <= 180)//点到开始游戏
				{
					DrawInitialGameInterface3();//绘制游戏初始界面，按钮为：登录、注册、返回
					while (1)//进入游戏初始界面（按钮为：登录、注册、返回）循环
					{
						ExMessage msg4;
						bool ifback4 = false;//用于判断是否点到返回
						if (peekmessage(&msg4, EM_MOUSE))//捕获鼠标信息
						{
							switch (msg4.message)
							{
							case WM_LBUTTONDOWN://按下左键
								int x4 = msg4.x;//当前鼠标在窗口中的横坐标
								int y4 = msg4.y;//当前鼠标在窗口中的纵坐标
								if (x4 >= 150 && x4 <= 350 && y4 >= 144 && y4 <= 180)//点到登录
								{
									CloseInitialGameInterface();//关闭游戏初始界面，按钮为：登录、注册、返回
									OpenLoginInputInterface();//打开登录信息输入界面
									bool login_ifcancel = false;//用于判断是否点到取消
									vector<string> user = DrawLoginInputInterface(login_ifcancel);//绘制登录信息输入界面，输入完成后返回登录用户信息
									CloseLoginInputInterface();//关闭登录信息输入界面
									OpenInitialGameInterface();//打开游戏初始界面
									if (login_ifcancel)//若是因为点到取消才回到游戏初始界面
									{
										DrawInitialGameInterface3();//绘制游戏初始界面，按钮为：登录、注册、返回
										break;//回到游戏初始界面，按钮为：登录、注册、返回
									}
									DrawInitialGameInterface1();//绘制游戏初始界面，按钮为：普通关卡、自定义关卡、返回
									while (1)//进入游戏初始界面（按钮为：普通关卡、自定义关卡、返回）循环
									{
										ExMessage msg2;
										bool ifback = false;//用于判断是否点到返回
										if (peekmessage(&msg2, EM_MOUSE))//捕获鼠标信息
										{
											switch (msg2.message)
											{
											case WM_LBUTTONDOWN://按下左键
												int x2 = msg2.x;//当前鼠标在窗口中的横坐标
												int y2 = msg2.y;//当前鼠标在窗口中的纵坐标
												if (x2 >= 150 && x2 <= 350 && y2 >= 144 && y2 <= 180)//点击到普通关卡
												{
													CloseInitialGameInterface();//关闭游戏初始界面，按钮为：普通关卡、自定义关卡、返回
													OpenSelectLevelInterface();//打开普通关卡选关界面
													DrawSelectLevelInterface();//绘制普通关卡选关界面
													while (1)//进入普通关卡选关界面循环
													{
														ExMessage msg;
														bool ifbreak = false;//用于判断是否点到返回
														if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
														{
															switch (msg.message)
															{
															case WM_LBUTTONDOWN://按下左键
																CloseSelectLevelInterface();//关闭普通关卡选关界面
																int ln = Mousemessage(&msg);//求所选关卡编号
																//不同的ln进入不同的if代码块，然后创建对应的关卡对象、打开游戏关卡界面、进入游玩关卡函数进行游玩
																if (ln == 0)
																{
																	Gamelevel l0(5, 9, l0code, "level_0");
																	l0.OpenLevel();
																	PlayGame(l0, users_accountnumber2name[user[0]]);
																};
																if (ln == 1)
																{
																	Gamelevel l1(10, 10, l1code, "level_1");
																	l1.OpenLevel();
																	PlayGame(l1, users_accountnumber2name[user[0]]);
																};
																if (ln == 2)
																{
																	Gamelevel l2(7, 8, l2code, "level_2");
																	l2.OpenLevel();
																	PlayGame(l2, users_accountnumber2name[user[0]]);
																};
																if (ln == 3)
																{
																	Gamelevel l3(14, 15, l3code, "level_3");
																	l3.OpenLevel();
																	PlayGame(l3, users_accountnumber2name[user[0]]);
																};
																if (ln == 4)
																{
																	Gamelevel l4(8, 6, l4code, "level_4");
																	l4.OpenLevel();
																	PlayGame(l4, users_accountnumber2name[user[0]]);
																};
																if (ln == 5)
																{
																	Gamelevel l5(12, 20, l5code, "level_5");
																	l5.OpenLevel();
																	PlayGame(l5, users_accountnumber2name[user[0]]);
																};
																if (ln == 6)
																{
																	Gamelevel l6(7, 6, l6code, "level_6");
																	l6.OpenLevel();
																	PlayGame(l6, users_accountnumber2name[user[0]]);
																};
																if (ln == 7)
																{
																	Gamelevel l7(14, 14, l7code, "level_7");
																	l7.OpenLevel();
																	PlayGame(l7, users_accountnumber2name[user[0]]);
																};
																if (ln == 8)
																{
																	Gamelevel l8(6, 6, l8code, "level_8");
																	l8.OpenLevel();
																	PlayGame(l8, users_accountnumber2name[user[0]]);
																};
																if (ln == 9)
																{
																	Gamelevel l9(15, 15, l9code, "level_9");
																	l9.OpenLevel();
																	PlayGame(l9, users_accountnumber2name[user[0]]);
																};
																if (ln == 10)
																{
																	Gamelevel l10(8, 9, l10code, "level_10");
																	l10.OpenLevel();
																	PlayGame(l10, users_accountnumber2name[user[0]]);
																};
																if (ln == 11)
																{
																	Gamelevel l11(9, 10, l11code, "level_11");
																	l11.OpenLevel();
																	PlayGame(l11, users_accountnumber2name[user[0]]);
																};
																if (ln == 12)
																{
																	Gamelevel l12(13, 13, l12code, "level_12");
																	l12.OpenLevel();
																	PlayGame(l12, users_accountnumber2name[user[0]]);
																};
																if (ln == 13)
																{
																	Gamelevel l13(7, 9, l13code, "level_13");
																	l13.OpenLevel();
																	PlayGame(l13, users_accountnumber2name[user[0]]);
																};
																if (ln == 14)
																{
																	Gamelevel l14(9, 14, l14code, "level_14");
																	l14.OpenLevel();
																	PlayGame(l14, users_accountnumber2name[user[0]]);
																};
																if (ln == 15)
																{
																	Gamelevel l15(11, 11, l15code, "level_15");
																	l15.OpenLevel();
																	PlayGame(l15, users_accountnumber2name[user[0]]);
																};
																if (ln == 16)
																{
																	Gamelevel l16(9, 11, l16code, "level_16");
																	l16.OpenLevel();
																	PlayGame(l16, users_accountnumber2name[user[0]]);
																};
																if (ln == 17)
																{
																	Gamelevel l17(8, 13, l17code, "level_17");
																	l17.OpenLevel();
																	PlayGame(l17, users_accountnumber2name[user[0]]);
																};
																if (ln == 18)
																{
																	Gamelevel l18(8, 6, l18code, "level_18");
																	l18.OpenLevel();
																	PlayGame(l18, users_accountnumber2name[user[0]]);
																};
																if (ln == 19)
																{
																	Gamelevel l19(11, 13, l19code, "level_19");
																	l19.OpenLevel();
																	PlayGame(l19, users_accountnumber2name[user[0]]);
																};
																if (msg.y >= 400 && msg.y <= 450)//点到返回
																{
																	OpenInitialGameInterface();//打开游戏初始界面
																	DrawInitialGameInterface1();//绘制游戏初始界面，按钮为：普通关卡、自定义关卡、返回
																	ifbreak = true; //用于判断是否点到返回的变量置为真
																};
																break;
															}
														}
														if (ifbreak)break;//若点到返回，则退出普通关卡选关界面循环
													};
													break;
												};
												if (x2 >= 150 && x2 <= 350 && y2 >= 216 && y2 <= 252)//点到自定义关卡
												{
													DrawInitialGameInterface2();//绘制游戏初始界面，按钮为：新建关卡、选择关卡、返回
													while (1)//进入游戏初始界面（按钮为：新建关卡、选择关卡、返回）循环
													{
														ExMessage msg3;
														bool ifback2 = false;//用于判断是否点到返回
														if (peekmessage(&msg3, EM_MOUSE))//捕获鼠标信息
														{
															switch (msg3.message)
															{
															case WM_LBUTTONDOWN://按下左键
																int x3 = msg3.x;//当前鼠标在窗口中的横坐标
																int y3 = msg3.y;//当前鼠标在窗口中的纵坐标
																ifstream levelacountfin("CustomGameLevel\\level_acount.dat", ios::in);//创建一个文件为CustomGameLevel\\level_acount.dat的输入流对象，用于输入已自定义的关卡数量
																int levelacount = 0;//已自定义的关卡数量初始化为0
																levelacountfin >> levelacount;//用输入流对象读取已自定义的关卡数量，存入levelacount
																if (x3 >= 150 && x3 <= 350 && y3 >= 144 && y3 <= 180)//点到新建关卡
																{
																	CloseInitialGameInterface();//关闭游戏初始界面，按钮为：新建关卡、选择关卡、返回
																	OpenNamingCustomLevel();//打开自定义关卡命名界面
																	bool custom_ifcancel = false;//用于判断是否点到取消
																	string customlevelname = DrawNamingCustomLevel_and_ReturnName(custom_ifcancel);//绘制自定义关卡名输入界面，输入完成后返回自定义关卡名
																	CloseNamingCustomLevel();//关闭自定义关卡命名界面
																	if (custom_ifcancel)//若是因为点到取消才回到游戏初始界面
																	{
																		OpenInitialGameInterface();//打开游戏初始界面
																		DrawInitialGameInterface2();//绘制游戏初始界面，按钮为：新建关卡、选择关卡、返回
																		break;
																	}
																	map<int, set<pair<int, int>>> wall_box_target;//墙、箱子、目标点位三种物件的坐标集合哈希表
																	Character assistcharacter;//辅助角色
																	int reachedboxacount = 0;//达到目标点位的箱子数量
																	OpenCreateCustomLevel();//打开自定义关卡功能界面
																	DrawCreateCustomLevel_and_CreateCustomLevel(wall_box_target, assistcharacter, reachedboxacount, customlevelname);//绘制自定义关卡功能界面，并自定义关卡，将数据存入传入的对应参数中
																	string levelnum = "CustomGameLevel\\" + to_string(levelacount) + ".dat";//将已自定义的关卡数量转为一条文件路径，文件名即为已自定义的关卡数量，代表当前要新建的自定义关卡的编号
																	ofstream customlevelnamefout(levelnum, ios::out);//创建一个文件为levelnum的文件输出流对象
																	customlevelnamefout << customlevelname;//将之前输入的关卡名写入文件levelnum中
																	levelacount++;//已自定义的关卡数量加一，也代表下一个自定义关卡的编号
																	ofstream levelacountfout("CustomGameLevel\\level_acount.dat", ios::out);//创建一个文件为CustomGameLevel\\level_acount.dat的文件输出流对象
																	levelacountfout << levelacount;//将新的已自定义的关卡数量写入文件CustomGameLevel\\level_acount.dat中
																	OpenInitialGameInterface();//打开游戏初始界面
																	DrawInitialGameInterface2();//绘制游戏初始界面，按钮为：新建关卡、选择关卡、返回
																	break;
																};
																if (x3 >= 150 && x3 <= 350 && y3 >= 216 && y3 <= 252)//点到选择关卡
																{
																	ifstream fin("CustomGameLevel\\level_acount.dat", ios::in);//创建一个文件为CustomGameLevel\\level_acount.dat的文件输入流对象
																	int acount = 0;//已自定义的关卡数量初始化为0
																	fin >> acount;//读取已自定义的关卡数量
																	OpenSelectCustomLevelInterface(acount);//打开自定义关卡选择界面
																	DrawSelectCustomLevelInterface(acount);//绘制自定义关卡选择界面
																	while (1)//进入自定义关卡选择界面循环
																	{
																		ExMessage Msg;
																		bool ifback3 = false;//用于判断是否点到返回
																		if (peekmessage(&Msg, EM_MOUSE))//捕获鼠标信息
																		{
																			switch (Msg.message)
																			{
																			case WM_LBUTTONDOWN://按下左键
																				int ln = Mousemessage_customlevel(&Msg);//求自定义关卡编号
																				if (ln >= 0 && ln < acount)//若自定义关卡编号在范围内
																				{
																					ifstream customlevelnamefin("CustomGameLevel\\" + to_string(ln) + ".dat", ios::in);
																					string customlevelname;
																					customlevelnamefin >> customlevelname;//读取自定义关卡名
																					ifstream customlevelencodefin("CustomGameLevel\\" + customlevelname + ".dat", ios::in);
																					string customlevelencode;
																					customlevelencodefin >> customlevelencode;//读取自定义关卡编码
																					ifstream customlevelrcfin("CustomGameLevel\\" + customlevelname + "_rc.dat", ios::in);
																					string customlevelrc;
																					customlevelrcfin >> customlevelrc;//读取自定义关卡行列数
																					int r = 0;//行数初始化为0
																					int c = 0;//列数初始化为0
																					int n = customlevelrc.size();//字符串customlevelrc的大小为n
																					int i = 0;//遍历字符串customlevelrc的初始索引位置
																					string assist = "";//辅助字符串
																					for (; i < n && customlevelrc[i] != ','; i++)//求行数
																					{
																						assist.push_back(customlevelrc[i]);
																					}
																					r = stoi(assist);
																					assist = "";
																					i++;
																					for (; i < n && customlevelrc[i] != ','; i++)//求列数
																					{
																						assist.push_back(customlevelrc[i]);
																					}
																					c = stoi(assist);
																					CloseSelectCustomLevelInterface();//关闭自定义关卡选关界面
																					Gamelevel customln(r, c, customlevelencode, customlevelname);//创建自定义关卡对象
																					customln.OpenLevel();//打开自定义关卡界面
																					PlayCustomGame(customln, users_accountnumber2name[user[0]]);//游玩自定义关卡
																				}
																				if (ln == acount)//若自定义关卡编号超出范围，也即点到返回
																				{
																					OpenInitialGameInterface();//打开游戏初始界面
																					DrawInitialGameInterface2();//绘制游戏初始界面，按钮为：新建关卡、选择关卡、返回
																					ifback3 = true;//用于判断是否点到返回的变量置为真
																					break;
																				}
																			}
																			if (ifback3)break;//若点到返回，则退出自定义关卡选关界面循环
																		}
																	}
																}
																if (x3 >= 150 && x3 <= 350 && y3 >= 288 && y3 <= 324)//点到返回
																{
																	ifback2 = true;//用于判断是否点到返回的变量置为真
																	DrawInitialGameInterface1();//绘制游戏初始界面，按钮为：普通关卡、自定义关卡、返回
																	break;
																};
																break;
															}
															if (ifback2)break;//若点到返回，则退出游戏初始界面（按钮为：新建关卡、选择关卡、返回）循环
														};
													};
													break;
												};
												if (x2 >= 150 && x2 <= 350 && y2 >= 288 && y2 <= 324)//点到返回
												{
													ifback = true;//用于判断是否点到返回置为真
													DrawInitialGameInterface3();//绘制游戏初始界面，按钮为：登录、注册、返回
													break;
												};
												break;
											}
											if (ifback)break;//若点到返回则退出游戏初始界面按钮为：普通关卡、自定义关卡、返回循环
										}
									}
									break;
								};
								if (x4 >= 150 && x4 <= 350 && y4 >= 216 && y4 <= 252)//点到注册
								{
									CloseInitialGameInterface();//关闭游戏初始界面，按钮为：登录、注册、返回
									OpenRegisterInputInterface();//打开注册信息输入界面
									bool register_ifcancel = false;//用于判断是否点到取消
									vector<string> user_information = DrawRegisterInputInterface(register_ifcancel);//绘制注册信息输入界面并返回注册信息
									if (register_ifcancel)//若点到取消退出注册界面
									{
										CloseRegisterInputInterface();//关闭注册信息输入界面
										OpenInitialGameInterface();//打开游戏初始界面
										DrawInitialGameInterface3();//绘制游戏初始界面，按钮为：登录、注册、返回
										break;
									}
									//在文件名为已注册用户数量（也即当前注册的用户的用户编号）的文件中写入用户信息
									string user_n = "Users\\" + to_string(user_acount) + ".dat";
									ofstream user_information_fout(user_n, ios::out);
									user_information_fout << user_information[0] << " " << user_information[1] << " " << user_information[2];
									//将已注册用户数量加一后存入文件Users\\user_count.dat
									ofstream user_count_fout("Users\\user_count.dat", ios::out);
									user_acount++;
									user_count_fout << user_acount;
									//更新users_accountnumber2password、users_accountnumber2name、users_names
									users_accountnumber2password[user_information[1]] = user_information[2];
									users_accountnumber2name[user_information[1]] = user_information[0];
									users_names.insert(user_information[0]);
									CloseRegisterInputInterface();//关闭注册信息输入界面
									OpenInitialGameInterface();//打开游戏初始界面
									DrawInitialGameInterface3();//绘制游戏初始界面，按钮为：登录、注册、返回
									break;
								};
								if (x4 >= 150 && x4 <= 350 && y4 >= 288 && y4 <= 324)//点到返回
								{
									ifback4 = true;//用于判断是否点到返回的变量置为真
									DrawInitialGameInterface0();//绘制游戏初始界面，按钮为：开始游戏、排行榜
									break;
								};
								break;
							}
						}
						if (ifback4)break;//若点到返回，则退出游戏初始界面（按钮为：登录、注册、返回）循环
					}
				};
				if (x1 >= 150 && x1 <= 350 && y1 >= 216 && y1 <= 252)//点到排行榜
				{
					CloseInitialGameInterface();//关闭游戏初始界面
					Change_User_Level_Score();//更新用户关卡分数
					Find_total_score();//求每个用户总得分
					OpenTheRankingList();//打开排行榜界面
					DrawTheRankingList();//绘制排行榜界面
					while (1)//进入排行榜界面循环
					{
						ExMessage msg5;
						bool ifback5 = false;//用于判断是否点到返回
						if (peekmessage(&msg5, EM_MOUSE))//捕获鼠标信息
						{
							switch (msg5.message)
							{
							case WM_LBUTTONDOWN://按下左键
								int x5 = msg5.x;//当前鼠标在窗口中的横坐标
								int y5 = msg5.y;//当前鼠标在窗口中的纵坐标
								if (x5 >= 0 && x5 <= 900 && y5 >= (user_totalscore.size() + 1) * 30 && y5 <= (user_totalscore.size() + 2) * 30)//点到返回
								{
									ifback5 = true;//用于判断是否点到返回的变量置为真
									CloseTheRankingList();//关闭排行榜界面
									OpenInitialGameInterface();//打开游戏初始界面
									DrawInitialGameInterface0();//绘制游戏初始界面，按钮为：开始游戏、排行榜
									break;
								};
								break;
							}
						}
						if (ifback5)break;//若点到返回，则退出排行榜界面循环
					}
				};
				break;
			}
		}
	}
	return 0;
}


void Box::setbox(int x, int y)//设置箱子横纵坐标
{
	boxx = x;
	boxy = y;
}

int Box::getboxx()//获取箱子横坐标
{
	return boxx;
}

int Box::getboxy()//获取箱子纵坐标
{
	return boxy;
}

void Target::settargetxy(int x, int y)//设置目标点位横纵坐标
{
	targetx = x;
	targety = y;
}

int Target::gettargetx()//获取目标点位横坐标
{
	return targetx;
}

int Target::gettargety()//获取目标点位纵坐标
{
	return targety;
}

void Wall::setwallxy(int x, int y)//设置墙横纵坐标
{
	wallx = x;
	wally = y;
}

int Wall::getwallx()//获取墙横坐标
{
	return wallx;
}

int Wall::getwally()//获取墙纵坐标
{
	return wally;
}

void Map::setmaprc(int r, int c)//设置地图行列数同时初始化地图
{
	Row = r;
	Col = c;
	map0.resize(Row, vector<int>(Col));
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			map0[i][j] = 0;
		}
	}
}

int Map::getmapr()//获取地图行数
{
	return Row;
}

int Map::getmapc()//获取地图列数
{
	return Col;
}

int Map::getmap0data(int x, int y)//获取地图特定坐标上的数值
{
	return map0[x][y];
}

void Map::showmap()//打印地图
{
	for (int i = 0; i < Row; i++)
	{
		for (int j = 0; j < Col; j++)
		{
			cout << setw(4) << map0[i][j];
		}
		cout << endl;
	}
}

void Map::SetOnMap(int x, int y, int data)//将某物设置在地图上
{
	map0[x][y] = data;
}

void Character::setcharacter(int x, int y, int o)//设置角色相关数据
{
	characterx0 = x;
	charactery0 = y;
	Orientation = o;
}

int Character::getcharacterx()//获取角色横坐标
{
	return characterx0;
}

int Character::getcharactery()//获取角色纵坐标
{
	return charactery0;
}

int Character::getcharactero()//获取角色朝向
{
	return Orientation;
}

void Character::characteroperate0(char ch)//操作角色并向后移动
{
	int x = getcharacterx(), y = getcharactery();
	switch (ch)
	{
	case 'a':
	case 'A':
		setcharacter(x, y + 1, 1);//按到左移按钮，则角色在地图上的纵坐标加一
		break;
	case 'w':
	case 'W':
		setcharacter(x + 1, y, 2);//按到上移按钮，则角色在地图上的横坐标加一
		break;
	case 'd':
	case 'D':
		setcharacter(x, y - 1, 3);//按到右移按钮，则角色在地图上的纵坐标减一
		break;
	case 's':
	case 'S':
		setcharacter(x - 1, y, 4);//按到下移按钮，则角色在地图上的横坐标减一
		break;
	}
}

void Character::characteroperate1(char ch)//操作角色并移动
{
	int x = getcharacterx(), y = getcharactery();
	switch(ch)
	{
	case 'a':
	case 'A':
		setcharacter(x, y - 1, 1);//按到左移按钮，则角色在地图上的纵坐标减一，方向置为向左
		break;
	case 'w':
	case 'W':
		setcharacter(x - 1, y, 2);//按到上移按钮，则角色在地图上的横坐标减一，方向置为向上
		break;
	case 'd':
	case 'D':
		setcharacter(x, y + 1, 3);//按到右移按钮，则角色在地图上的纵坐标加一，方向置为向右
		break;
	case 's':
	case 'S':
		setcharacter(x + 1, y, 4);//按到下移按钮，则角色在地图上的横坐标加一，方向置为向下
		break;
	}
}

Gamelevel::Gamelevel(int r, int c, string code, string name)//初始化关卡
{
	row = r;//地图行数为r
	col = c;//地图列数为c
	reachedboxes = 0;//达到目标点位的箱子数为0
	encode = code;//关卡初始化编码为code
	savedcode = "";//关卡存档编码为空
	gamename = name;//关卡名为name
	score = row * col * 5 * 5;//关卡基础分为地图行列数乘积再乘25
	DeCode(0);//对初始化编码进行解码
	SetAllOnMap();//将所有物件放到地图上
}

void Gamelevel::DeCode(int kind)//对关卡信息字符串进行解码，kind为0表示初始编码，kind为1表示存档的编码
{
	string code = "";//辅助编码
	//将关卡中的相关信息清空，方便译码重置关卡
	gamemap.setmaprc(row, col);
	box.resize(0);
	whichbox2boxindex.clear();
	boxindex2whichbox.clear();
	target.resize(0);
	wall.resize(0);
	reachedboxes = 0;
	if (kind == 0)code = encode;//kind为0，则code赋值为encode
	if (kind == 1)code = savedcode;//kind为1，则code赋值为savedcode
	int i = 0;//遍历字符串code的初始索引位置
	string assist = "";//辅助字符串
	//分解编码第一部分：达到目标点位的箱子数
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	reachedboxes = stoi(assist);
	i++;
	assist = "";
	//分解编码第二部分：箱子数量
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int bnum = stoi(assist);
	boxnum = bnum;
	box.resize(bnum);
	i++;
	assist = "";
	//分解编码第三部分：目标点位数量
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int tnum = stoi(assist);
	targetnum = tnum;
	target.resize(tnum);
	i++;
	assist = "";
	//分解编码第四部分：墙数量
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int wnum = stoi(assist);
	wallnum = wnum;
	wall.resize(wnum);
	i++;
	assist = "";
	//分解编码第五部分：角色在地图上的横坐标
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int chx = stoi(assist);
	i++;
	assist = "";
	//分解编码第六部分：角色在地图上的纵坐标
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int chy = stoi(assist);
	i++;
	assist = "";
	//分解编码第七部分：角色朝向
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int cho = stoi(assist);
	//重设关卡内角色信息
	character.setcharacter(chx, chy, cho);
	i++;
	//创建三个辅助数组，分别用于存储箱子坐标、目标点位坐标、墙坐标
	vector<vector<int>> bindex(bnum, vector<int>(2));
	vector<vector<int>> tindex(tnum, vector<int>(2));
	vector<vector<int>> windex(wnum, vector<int>(2));
	//分解编码第八部分：箱子坐标
	for (int b = 0; b < bnum; b++)
	{
		string assist1 = "", assist2 = "";
		while (i < code.size() && code[i] != ',')
		{
			assist1.push_back(code[i]);
			i++;
		}
		bindex[b][0] = stoi(assist1);
		i++;
		while (i < code.size() && code[i] != ',')
		{
			assist2.push_back(code[i]);
			i++;
		}
		bindex[b][1] = stoi(assist2);
		i++;
	}
	//分解编码第九部分：目标点位坐标
	for (int t = 0; t < tnum; t++)
	{
		string assist1 = "", assist2 = "";
		while (i < code.size() && code[i] != ',')
		{
			assist1.push_back(code[i]);
			i++;
		}
		tindex[t][0] = stoi(assist1);
		i++;
		while (i < code.size() && code[i] != ',')
		{
			assist2.push_back(code[i]);
			i++;
		}
		tindex[t][1] = stoi(assist2);
		i++;
	}
	//分解编码第十部分：墙坐标
	for (int w = 0; w < wnum; w++)
	{
		string assist1 = "", assist2 = "";
		while (i < code.size() && code[i] != ',')
		{
			assist1.push_back(code[i]);
			i++;
		}
		windex[w][0] = stoi(assist1);
		i++;
		while (i < code.size() && code[i] != ',')
		{
			assist2.push_back(code[i]);
			i++;
		}
		windex[w][1] = stoi(assist2);
		i++;
	}
	//重设与箱子有关的存储变量：将每个箱子坐标存入数组box，将每个箱子坐标和箱子编号进行双映射设置
	for (int b = 0; b < bnum; b++)
	{
		box[b].setbox(bindex[b][0], bindex[b][1]);
		pair<int, int> boxindex = { bindex[b][0],bindex[b][1] };
		boxindex2whichbox[boxindex] = b;
		whichbox2boxindex[b] = boxindex;
	}
	//重设与目标点位有关的存储变量：将每个目标点位坐标存入数组target，将每个目标点位坐标存入目标点位坐标集合
	for (int t = 0; t < tnum; t++)
	{
		pair<int, int> index = { tindex[t][0],tindex[t][1] };
		target[t].settargetxy(tindex[t][0], tindex[t][1]);
		target_index.insert(index);
	}
	//重设与墙有关的存储变量：将每个墙坐标存入数组wall
	for (int w = 0; w < wnum; w++)wall[w].setwallxy(windex[w][0], windex[w][1]);
}

void Gamelevel::SetBoxOnMap(int i)//将箱子设置在地图上
{
	pair<int, int> index = { box[i].getboxx(),box[i].getboxy() };//第i个箱子的坐标
	int mdata = target_index.count(index) ? 5 : 2;//箱子显示在地图上的数字，若与某目标点位重合则该数字为5，否则该数字为2
	gamemap.SetOnMap(box[i].getboxx(), box[i].getboxy(), mdata);//游戏关卡地图对象中的map0数组的box[i].getboxx()行，box[i].getboxy()列处设为mdata
}

void Gamelevel::SetTargetOnMap(int i)//将目标点位设置在地图上
{
	gamemap.SetOnMap(target[i].gettargetx(), target[i].gettargety(), 3);//游戏关卡地图对象中的map0数组的target[i].gettargetx()行，target[i].gettargety()列处设为3
}

void Gamelevel::SetWallOnMap(int i)//将墙设置在地图上
{
	gamemap.SetOnMap(wall[i].getwallx(), wall[i].getwally(), 9);//游戏关卡地图对象中的map0数组的wall[i].getwallx()行，wall[i].getwally()列处设为9
}

void Gamelevel::SetAllOnMap()//将所有物件设置在地图上
{
	for (int i = 0; i < targetnum; i++)//放置目标点位
	{
		SetTargetOnMap(i);
	}
	for (int i = 0; i < boxnum; i++)//放置箱子
	{
		SetBoxOnMap(i);
	}
	for (int i = 0; i < wallnum; i++)//放置墙
	{
		SetWallOnMap(i);
	}
}

int Gamelevel::whichbox(int x, int y)//判断指定位置的箱子是第几个箱子
{
	pair<int, int> indexpair = { x,y };//坐标对，代表游戏关卡地图对象的map0数组中的x行，y列处
	if (!boxindex2whichbox.count(indexpair))//若箱子坐标与箱子编号的双映射中不存在坐标对indexpair，则返回NULL
	{
		cout << "坐标对错误" << endl;
		return NULL;
	}
	return boxindex2whichbox[indexpair];//返回箱子坐标所对应的箱子编号
}

void Gamelevel::MoveCharactar(char ch)//移动一个角色
{
	if (score > 0)score -= 5;//若有移动操作且当前分数大于0，则分数减5
	int x = character.getcharacterx(), y = character.getcharactery();//取出角色当前在地图数组中的坐标信息
	pair<int, int> preboxindex = { x,y };//假设当前角色位置处有箱子（方便之后判断是否有移动箱子的情况发生，若有，该如何移动），则该箱子坐标与角色坐标相同
	int mdata00 = gamemap.getmap0data(x, y);//当前角色位置处在地图数组上的数据 
	int mdata01 = y + 1 >= col ? -1 : gamemap.getmap0data(x, y + 1);//当前角色位置处向右一格在地图数组上的数据，若当前角色位置处向右一格超出了地图数组范围，则该数据为-1
	int mdata0_1 = y - 1 < 0 ? -1 : gamemap.getmap0data(x, y - 1);//当前角色位置处向左一格在地图数组上的数据，若当前角色位置处向左一格超出了地图数组范围，则该数据为-1
	int mdata10 = x + 1 >= row ? -1 : gamemap.getmap0data(x + 1, y);//当前角色位置处向下一格在地图数组上的数据，若当前角色位置处向下一格超出了地图数组范围，则该数据为-1
	int mdata_10 = x - 1 < 0 ? -1 : gamemap.getmap0data(x - 1, y);//当前角色位置处向上一格在地图数组上的数据，若当前角色位置处向上一格超出了地图数组范围，则该数据为-1
	switch (ch)
	{
	case 'a'://左移
	case 'A':
		if (mdata00 == 2 && mdata0_1 == 0)//当前位置有箱子，且向左一格为空，箱子可移动
		{
			int wb = whichbox(x, y);//获取箱子编号
			gamemap.SetOnMap(x, y, 0);//地图数组上当前位置数据置为0
			box[wb].setbox(x, y - 1);//wb号箱子坐标左移
			pair<int, int> nowboxindex = { x,y - 1 };//左移后的箱子坐标
			boxindex2whichbox.erase(preboxindex);//清除原箱子坐标到箱子编号的映射
			boxindex2whichbox[nowboxindex] = wb;//重设箱子坐标到箱子编号的映射
			whichbox2boxindex[wb] = nowboxindex;//重设箱子编号到箱子坐标的映射
			SetBoxOnMap(wb);//将更改后的wb号箱子放到地图上
		}
		if (mdata00 == 2 && mdata0_1 == 3)//当前位置有箱子，且向左一格有目标点位，箱子可移动，且箱子移动后到达目标点位
		{
			int wb = whichbox(x, y);//获取箱子编号
			gamemap.SetOnMap(x, y, 0);//地图数组上当前位置数据置为0
			box[wb].setbox(x, y - 1);//wb号箱子坐标左移
			pair<int, int> nowboxindex = { x,y - 1 };//左移后的箱子坐标
			boxindex2whichbox.erase(preboxindex);//清除原箱子坐标到箱子编号的映射
			boxindex2whichbox[nowboxindex] = wb;//重设箱子坐标到箱子编号的映射
			whichbox2boxindex[wb] = nowboxindex;//重设箱子编号到箱子坐标的映射
			reachedboxes++;//到达目标点位的箱子数加一
			gamemap.SetOnMap(x, y - 1, 5);//当前位置向左一格处在地图数组上的数据置为5
			score += 25;//使箱子抵达目标点位，分数加25
		}
		if (mdata00 == 2 && (mdata0_1 == 2 || mdata0_1 == 5 || mdata0_1 == 9))//当前位置有箱子，且向左一格有箱子或达到目标点位的箱子或墙，箱子不可移动
		{
			character.characteroperate0(ch);//角色保持朝向不变并后退
		}
		if (mdata00 == 5 || mdata00 == 9)//当前位置处有达到目标点位的箱子或墙
		{
			character.characteroperate0(ch);//角色保持朝向不变并后退
		};
		break;
		//之后的上移、右移、下移操作大同小异，不再注释
	case 'w':
	case 'W':
		if (mdata00 == 2 && mdata_10 == 0)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x - 1, y);
			pair<int, int> nowboxindex = { x - 1,y };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			SetBoxOnMap(wb);
		}
		if (mdata00 == 2 && mdata_10 == 3)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x - 1, y);
			pair<int, int> nowboxindex = { x - 1,y };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			reachedboxes++;
			gamemap.SetOnMap(x - 1, y, 5);
			score += 25;
		}
		if (mdata00 == 2 && (mdata_10 == 2 || mdata_10 == 5 || mdata_10 == 9))
		{
			character.characteroperate0(ch);
		}
		if (mdata00 == 5 || mdata00 == 9)
		{
			character.characteroperate0(ch);
		};
		break;
	case 'd':
	case 'D':
		if (mdata00 == 0)
		{
		}
		if (mdata00 == 2 && mdata01 == 0)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x, y + 1);
			pair<int, int> nowboxindex = { x,y + 1 };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			SetBoxOnMap(wb);
		}
		if (mdata00 == 2 && mdata01 == 3)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x, y + 1);
			pair<int, int> nowboxindex = { x,y + 1 };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			reachedboxes++;
			gamemap.SetOnMap(x, y + 1, 5);
			score += 25;
		}
		if (mdata00 == 2 && (mdata01 == 2 || mdata01 == 5 || mdata01 == 9))
		{
			character.characteroperate0(ch);
		}
		if (mdata00 == 5 || mdata00 == 9)
		{
			character.characteroperate0(ch);
		};
		break;
	case 's':
	case 'S':
		if (mdata00 == 2 && mdata10 == 0)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x + 1, y);
			pair<int, int> nowboxindex = { x + 1,y };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			SetBoxOnMap(wb);
		}
		if (mdata00 == 2 && mdata10 == 3)
		{
			int wb = whichbox(x, y);
			gamemap.SetOnMap(x, y, 0);
			box[wb].setbox(x + 1, y);
			pair<int, int> nowboxindex = { x + 1,y };
			boxindex2whichbox.erase(preboxindex);
			boxindex2whichbox[nowboxindex] = wb;
			whichbox2boxindex[wb] = nowboxindex;
			reachedboxes++;
			gamemap.SetOnMap(x + 1, y, 5);
			score += 25;
		}
		if (mdata00 == 2 && (mdata10 == 2 || mdata10 == 5 || mdata10 == 9))
		{
			character.characteroperate0(ch);
		}
		if (mdata00 == 5 || mdata00 == 9)
		{
			character.characteroperate0(ch);
		};
		break;
	}
}

int Gamelevel::win()//判断某关是否赢
{
	return reachedboxes == boxnum;
}

void Gamelevel::OpenLevel()//打开关卡窗口
{
	initgraph(col * 40, (row + 1) * 40);
}

void Gamelevel::CloseLevel()//关闭关卡窗口
{
	closegraph();
}

void Gamelevel::DrawLevel()//绘制关卡
{
	setbkcolor(WHITE);//设置背景颜色为白色
	cleardevice();//清空屏幕，使背景颜色变为白色
	putimage(0 * 40, row * 40, 40, 40, &images_level[13], 0, 0);//回退按钮
	putimage(1 * 40, row * 40, 40, 40, &images_level[14], 0, 0);//重置关卡按钮
	putimage(2 * 40, row * 40, 40, 40, &images_level[15], 0, 0);//存档按钮
	putimage(3 * 40, row * 40, 40, 40, &images_level[16], 0, 0);//读档按钮
	int chx = character.getcharacterx();//角色在地图上的横坐标
	int chy = character.getcharactery();//角色在地图上的纵坐标
	int cho = character.getcharactero();//角色朝向
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int mdata = gamemap.getmap0data(i, j);
			if (mdata == 3 && chx == i && chy == j && cho == 1)//有朝左角色的目标
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[4], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 2)//有朝上角色的目标
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[6], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 3)//有朝右角色的目标
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[7], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 4)//有朝下角色的目标
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[8], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 1)//朝左角色
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[1], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 2)//朝上角色
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[10], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 3)//朝右角色
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[11], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 4)//朝下角色
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[12], 0, 0);
				continue;
			}
			if (mdata == 0)//空白
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[0], 0, 0);
				continue;
			}
			if (mdata == 2)//未达到目标的箱子
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[2], 0, 0);
				continue;
			}
			if (mdata == 3 && ((chx != i && chy != j) || (chx == i && chy != j) || (chx != i && chy == j)))//无角色目标
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[3], 0, 0);
				continue;
			}
			if (mdata == 5)//达到目标的箱子
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[5], 0, 0);
				continue;
			}
			if (mdata == 9)//墙
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[9], 0, 0);
				continue;
			}
		}
	}
}

void Gamelevel::DrawChangedImage(int prex, int prey, int predata, int nowx, int nowy, int nowdata, int sufx, int sufy, int sufdata)//绘制角色移动后图片改变的部分
{
	int deltax = nowx - sufx;//移动前及移动后角色在地图上横坐标的差值
	int deltay = nowy - sufy;//移动前及移动后角色在地图上纵坐标的差值
	if (deltax == 0 && deltay == 0)//移动前、移动后角色位置未改变
	{
		int cho = character.getcharactero();//获取角色当前朝向
		switch (nowdata)//地图上当前角色位置处的数据
		{
		case 0://若为空白
			switch (cho)
			{
			case 1://角色朝左
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[1], 0, 0);
				break;
			case 2://角色朝上
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[10], 0, 0);
				break;
			case 3://角色朝右
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[11], 0, 0);
				break;
			case 4://角色朝下
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[12], 0, 0);
				break;
			};
			break;
		case 3://若为目标点位
			switch (cho)
			{
			case 1://角色朝左
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[4], 0, 0);
				break;
			case 2://角色朝上
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[6], 0, 0);
				break;
			case 3://角色朝右
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[7], 0, 0);
				break;
			case 4://角色朝下
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[8], 0, 0);
				break;
			};
			break;
		}
		return;
	}
	int deltacase = deltax * 1 + deltay * 2;//只考虑4种情况：deltax=1,deltay=0;deltax=-1,deltay=0;deltax=0,deltay=1;deltax=0,deltay=-1
	switch (deltacase)
	{
	case 1://角色向下移动
		switch (predata)//地图上角色下方一格数据
		{
		case 0://空白
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://目标点位
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://到达目标点位的箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://墙体
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//地图上当前角色位置处数据
		{
		case 0://空白
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[12], 0, 0);
			break;
		case 3://目标点位
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[8], 0, 0);
			break;
		};
		switch (sufdata)//地图上角色上方一格数据
		{
		case 0://空白
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://目标点位
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case -1://角色向上移动
		switch (predata)//地图上角色上方一格数据
		{
		case 0://空白
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://目标点位
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://到达目标点位的箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://墙体
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//地图上当前角色位置处数据
		{
		case 0://空白
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[10], 0, 0);
			break;
		case 3://目标点位
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[6], 0, 0);
			break;
		};
		switch (sufdata)//地图上角色下方一格数据
		{
		case 0://空白
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://目标点位
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case 2://角色向右移动
		switch (predata)//地图上角色右方一格数据
		{
		case 0://空白
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://目标点位
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://到达目标点位的箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://墙体
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//地图上当前角色位置处数据
		{
		case 0://空白
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[11], 0, 0);
			break;
		case 3://目标点位
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[7], 0, 0);
			break;
		};
		switch (sufdata)//地图上角色左方一格数据
		{
		case 0://空白
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://目标点位
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case -2://角色向左移动
		switch (predata)//地图上角色左方一格数据
		{
		case 0://空白
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://目标点位
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://到达目标点位的箱子
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://墙体
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//地图上当前角色位置处数据
		{
		case 0://空白
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[1], 0, 0);
			break;
		case 3://目标点位
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[4], 0, 0);
			break;
		};
		switch (sufdata)//地图上右方一格数据
		{
		case 0://空白
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://目标点位
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	}
}

void LoadResource_InitialGameInterface()//加载游戏初始界面图片
{
	char img[50] = { 0 };
	sprintf_s(img, "images_initialgameinterface\\%d.jpg", 0);
	loadimage(&images_initialgameinterface[0], img, 5 * 100, 4 * 100);
	for (int i = 1; i < 10; i++)
	{
		char imgs[50] = { 0 };
		sprintf_s(imgs, "images_initialgameinterface\\%d.jpg", i);
		loadimage(&images_initialgameinterface[i], imgs, 200, 36);
	}
}

void LoadResource_SelectLevelInterface()//加载选关界面图片
{
	char img[50] = { 0 };
	sprintf_s(img, "images_selectlevelinterface\\0.jpg");
	loadimage(&images_selectlevelinterface[0], img, 5 * 100, 4 * 100);
}

void LoadResource_Level()//加载关卡图片
{
	for (int i = 0; i < 17; i++)
	{
		char img1[50] = { 0 };
		sprintf_s(img1, "images_level\\%d.jpg", i);
		loadimage(&images_level[i], img1, 40, 40);
	}
}

void LoadResource_CreateCustomLevel()//加载关卡自定义界面图片
{
	for (int i = 0; i < 8; i++)
	{
		char img[50] = { 0 };
		sprintf_s(img, "images_createcustomlevel\\%d.jpg", i);
		loadimage(&images_createcustomlevel[i], img, 40, 40);
	}
}

void OpenInitialGameInterface()//打开游戏初始界面
{
	initgraph(5 * 100, 4 * 100);
}

void OpenSelectLevelInterface()//打开选关界面
{
	initgraph(5 * 100, 4 * 100 + 50);
}

void OpenNamingCustomLevel()//打开自定义关卡命名界面
{
	initgraph(600, 480);
}

void OpenCreateCustomLevel()//打开关卡自定义界面
{
	initgraph(1040, 760);
}

void OpenSelectCustomLevelInterface(int c)//打开自定义关卡选关界面
{
	initgraph(500, (c + 1) * 30);
}

void OpenLoginInputInterface()//打开登录信息输入窗口
{
	initgraph(600, 480);
}

void OpenRegisterInputInterface()//打开注册信息输入窗口
{
	initgraph(600, 570);
}

void OpenTheRankingList()//打开排行榜页面
{
	initgraph(100 + 400 + 400, (user_totalscore.size() + 2) * 30);
}

void CloseInitialGameInterface()//关闭游戏初始界面
{
	closegraph();
}

void CloseSelectLevelInterface()//关闭选关界面
{
	closegraph();
}

void CloseNamingCustomLevel()//关闭自定义关卡命名界面
{
	closegraph();
}

void CloseSelectCustomLevelInterface()//关闭自定义关卡选关界面
{
	closegraph();
}

void CloseLoginInputInterface()//关闭登录输入界面
{
	closegraph();
}

void CloseRegisterInputInterface()//关闭注册输入界面
{
	closegraph();
}

void CloseTheRankingList()//关闭排行榜页面
{
	closegraph();
}

void DrawInitialGameInterface0()//绘制游戏初始界面，按钮为开始游戏、排行榜
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[1], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[9], 0, 0);
}

void DrawInitialGameInterface1()//绘制游戏初始界面，按钮为普通关卡和自定义关卡
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[2], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[3], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawInitialGameInterface2()//绘制自定义关卡初始界面，按钮为新建关卡、选择关卡、返回
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[5], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[6], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawInitialGameInterface3()//绘制登录、注册界面，按钮为登录、注册、返回
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[7], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[8], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawSelectLevelInterface()//绘制选关界面
{
	setbkcolor(RGB(112, 163, 229));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(40, 0, "宋体");
	outtextxy(140, 405, "返");
	outtextxy(320, 405, "回");
	setlinecolor(BLACK);
	rectangle(0, 400, 500, 450);
	putimage(0, 0, 500, 400, &images_selectlevelinterface[0], 0, 0);
}

string DrawNamingCustomLevel_and_ReturnName(bool& ifcancel)//绘制自定义关卡命名界面并返回文件名
{
	int x = 100;//输入框左上角横坐标
	int y = 160;//输入框左上角纵坐标
	int w = 400;//输入框长度
	int h = 30;//输入框宽度
	int LineColor = BLACK;//直线颜色
	int TextColor = BLACK;//文本颜色
	int BackgroundColor = WHITE;//背景颜色
	char text[1024] = { '\0' };//用于存储文本
	int textLength = 0;//输入的文本长度
	int index = 0;//当前光标位置
	string name = "";//最终返回的文件名
	setbkcolor(BackgroundColor);//设置背景颜色
	cleardevice();//清空窗口，重初始化窗口样式
	settextstyle(20, 0, "宋体");//设置中文字体大小为20*20像素，字体为宋体
	settextcolor(TextColor);//设置文本颜色
	setlinecolor(LineColor);//设置直线颜色
	rectangle(x, y, x + w, y + h);//绘制输入框
	outtextxy(x + 5, y - 25, "请为自定义关卡命名(仅支持英文字母)：");//输出提示语，起始坐标（左上角）为（x+5，y-25）
	rectangle(x, 2 * y, x + 120, 2 * y + h);//绘制确定按钮框
	rectangle(x + 280, 2 * y, x + w, 2 * y + h);//绘制取消按钮框
	outtextxy(x + 40, 2 * y + 5, "确定");//输出确定
	outtextxy(x + 280 + 40, 2 * y + 5, "取消");//输出取消
	line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//绘制光标
	ExMessage msg;//鼠标信息
	char c;//当前输入的字符
	bool ifbreak = false;//用于判断是否推出循环
	while (1)//进入输入循环
	{
		outtextxy(x + 5, y + 5, text);//输出输入的一串字符
		rectangle(x, y, x + w, y + h);//绘制输入框
		outtextxy(x + 5, y - 25, "请为自定义关卡命名(仅支持英文字母)：");//绘制提示语
		rectangle(x, 2 * y, x + 120, 2 * y + h);//绘制确定按钮框
		rectangle(x + 280, 2 * y, x + w, 2 * y + h);//绘制取消按钮框
		outtextxy(x + 40, 2 * y + 5, "确定");//输出确定
		outtextxy(x + 280 + 40, 2 * y + 5, "取消");//输出取消
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//绘制光标
		if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
		{
			switch (msg.message)//判断鼠标信息
			{
			case WM_LBUTTONDOWN://按下鼠标左键
				int x = msg.x;//鼠标此时所指向窗口中像素位置的横坐标
				int y = msg.y;//鼠标此时所指向窗口中像素位置的纵坐标
				if (x >= 100 && x <= 220 && y >= 320 && y <= 350)//鼠标在确定按钮框范围内
				{
					for (int i = 0; i < 1024 && text[i] != '\0'; i++)//存储当前的输入文本信息
					{
						name.push_back(text[i]);
					}
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					break;
				};
				if (x >= 380 && x <= 500 && y >= 320 && y <= 350)//鼠标在取消按钮框范围内
				{
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					ifcancel = true;//是否取消置为真
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//捕获按键信息
		{
			c = _getch();//将当前按到的字符传给字符c
			if (c == '\b' && textLength > 0 && index > 0)//按到backspace且当前输入框中光标之前有可删除字符
			{
				if (index == textLength)//光标位置在输入文本的末尾
				{
					cleardevice();
					text[--textLength] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					index--;//光标位置减一
				}
				else//光标位置不在输入文本末尾
				{
					cleardevice();
					for (int i = index - 1; i < textLength; i++)text[i] = text[i + 1];//光标之后的字符依次向前移动一格
					index--;//光标位置减一
					text[--textLength] = '\0';//将最后一个字符变为结束符，输入文本长度减一
				}
			}
			else if (c == '\b' && textLength == 0)//按到backspace且已无输入文本可删除
			{
				cleardevice();
				continue;//继续循环
			}
			else if (c == '\r')//按到回车
			{
				for (int i = 0; i < 1024 && text[i] != '\0'; i++)//存储当前的输入文本信息
				{
					name.push_back(text[i]);
				}
				ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
				break;
			}
			else
			{
				if (c == 75 && index > 0)//按到左键且光标还可左移
				{
					index--;//光标位置减一
					cleardevice();
					continue;
				}
				if (c == 77 && index < textLength)//按到右键且光标还可右移
				{
					index++;//光标位置加一
					cleardevice();
					continue;
				}
				if (index == textLength && textLength < 39 && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))//按到字母且光标在已输入文本末尾
				{
					index++;//光标位置加一
					text[textLength++] = c;//使输入的文本末尾为当前字符，文本长度加一
					text[textLength] = '\0';//保证文本最后有结束符
					cleardevice();
					continue;
				}
				if (index != textLength && textLength < 39 && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))//按到字母且光标不在已输入文本末尾
				{
					for (int i = textLength; i > index; i--)text[i] = text[i - 1];//光标之后的字符全体依次向后移动一格
					text[index++] = c;//光标位置为当前字符并使光标位置加一
					textLength++;//文本长度加一
					cleardevice();
					continue;
				}
			}
		}
		if (ifbreak)break;//用于控制继续循环或退出循环
	}
	return name;//返回输入的文本信息
}

void DrawCreateCustomLevel_and_CreateCustomLevel(map<int, set<pair<int, int>>>& w_b_t, Character& c, int& r, string levelname)//绘制关卡自定义界面并进行自定义
{
	setbkcolor(WHITE);//设置背景颜色为白色
	cleardevice();//清空窗口，使背景颜色变为白色
	for (int i = 0; i < 16; i++)//绘制自定义关卡的自定义画布区域外围方框
	{
		if (i > 0 && i < 15)
		{
			putimage(0 * 40, i * 40, 40, 40, &images_createcustomlevel[7], 0, 0);
			putimage(25 * 40, i * 40, 40, 40, &images_createcustomlevel[7], 0, 0);
			continue;
		}
		for (int j = 0; j < 26; j++)
		{
			putimage(j * 40, i * 40, 40, 40, &images_createcustomlevel[7], 0, 0);
		}
	}
	int tomid = 10;//按钮调整为居中的参数
	int buttony = 17;//按钮调整到底部的参数
	putimage((0 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[0], 0, 0);//墙体方块选择按钮
	putimage((1 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[1], 0, 0);//箱子方块选择按钮
	putimage((2 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//目标点位方块选择按钮
	putimage((3 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[3], 0, 0);//角色方块选择按钮
	settextcolor(BLACK);//设置字体颜色为黑色
	settextstyle(40, 0, "宋体");//设置字体样式
	setbkcolor(RGB(182, 229, 29));//重设背景颜色，可使“确认”按钮有填充色
	outtextxy((4 + tomid) * 40, buttony * 40, "确认");//确认按钮
	setlinecolor(0x00B5E51D);//设置线条颜色
	//使五个按钮有边框
	rectangle((0 + tomid) * 40, buttony * 40, (0 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((1 + tomid) * 40, buttony * 40, (1 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((2 + tomid) * 40, buttony * 40, (2 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((3 + tomid) * 40, buttony * 40, (3 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((4 + tomid) * 40, buttony * 40, (4 + tomid) * 40 + 80, buttony * 40 + 40);
	priority_queue<int, vector<int>, greater<>> MinLeft;//升序队列（小顶堆）存储放置的墙体最小的在地图上的纵坐标
	priority_queue<int, vector<int>, less<>> MaxRight;//降序队列（大顶堆）存储放置的墙体最大的在地图上的纵坐标
	priority_queue<int, vector<int>, greater<>> MinTop;//升序队列（小顶堆）存储放置的墙体最小的在地图上的横坐标
	priority_queue<int, vector<int>, less<>> MaxBottom;//降序队列（大顶堆）存储放置的墙体最大的在地图上的横坐标
	MinLeft.emplace(25);//墙体最小在地图上的纵坐标初始化为25，可保证栈顶元素为最小
	MaxRight.emplace(0);//墙体最大在地图上的纵坐标初始化为0，可保证栈顶元素为最大
	MinTop.emplace(15);//墙体最小在地图上的横坐标初始化为15，可保证栈顶元素为最小
	MaxBottom.emplace(0);//墙体最大在地图上的横坐标初始化为0，可保证栈顶元素为最大
	int minleft = 25;//墙体最小在地图上的纵坐标初始化为25，可保证栈顶元素为最小
	int maxright = 0;//墙体最大在地图上的纵坐标初始化为0，可保证栈顶元素为最大
	int mintop = 15;//墙体最小在地图上的横坐标初始化为15，可保证栈顶元素为最小
	int maxbottom = 0;//墙体最大在地图上的横坐标初始化为0，可保证栈顶元素为最大
	ExMessage msg;
	int nowbutton = -1;//当前按到的按钮编号初始化为-1
	int prebutton = 0;//上一次按到的按钮编号初始化为0
	set<pair<int,int>> usedtargetindex;//已放置的目标点位坐标集合
	set<pair<int, int>> usedboxindex;//已放置的箱子坐标集合
	c.setcharacter(-1, -1, -1);//角色坐标初始化为{-1，-1}，朝向初始化为-1
	pair<int, int> characterindex = { -1,-1 };//角色坐标初始化为{-1，-1}
	set<pair<int, int>> usedwallindex;//已放置的墙坐标集合
	set<pair<int, int>> usedbox_targetindex;//已放置的达到目标点位的箱子坐标（也代表某目标点位坐标）集合
	bool ifbreak = false;//用于判断是否完成自定义关卡
	while (1)//进入自定义功能界面循环
	{
		if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
		{
			//按下左键的横纵坐标
			int x = msg.x;
			int y = msg.y;
			//按下右键的横纵坐标
			int x1 = msg.x;
			int y1 = msg.x;
			switch (msg.message)
			{
			case WM_LBUTTONDOWN://按下左键
				x = msg.x;
				y = msg.y;
				if (x >= (0 + tomid) * 40 && x <= (4 + tomid) * 40 + 80 && y >= buttony * 40 && y <= buttony * 40 + 40)//按到按钮
				{
					if (nowbutton != -1)prebutton = nowbutton >= 4 ? 4 : nowbutton;//重置上一个按到的按钮编号
					nowbutton = ((x / 40) - tomid) >= 4 ? 4 : ((x / 40) - tomid);//重置当前按到的按钮编号
					rectangle((prebutton + tomid) * 40, buttony * 40, (prebutton + tomid) * 40 + (prebutton == 4 ? 80 : 40), buttony * 40 + 40);//恢复上一个按钮的边框颜色
					setlinecolor(RED);//设置线条颜色为红色
					rectangle((nowbutton + tomid) * 40, buttony * 40, (nowbutton + tomid) * 40 + (nowbutton == 4 ? 80 : 40), buttony * 40 + 40);//当前按到的按钮边框颜色改为红色，代表选中
					setlinecolor(0x00B5E51D);//恢复线条颜色为原来的颜色
					if (nowbutton == 4)//按到确认按钮
					{
						for (int i = 16; i < 19; i++)//将报错区域涂白
						{
							for (int j = 0; j < tomid; j++)
							{
								putimage(j * 40, i * 40, 40, 40, &images_createcustomlevel[6], 0, 0);
							}
						}
						set<pair<int, int>> circlenode;//围墙结点坐标集合
						bool whetherclose = whethercircle(w_b_t[0], circlenode);//判断是否有封闭的围墙，并将封闭围墙上的所有墙体坐标传入circlenode集合
						bool whetherin = whetherincircle(w_b_t[0], w_b_t[1], w_b_t[2], c, circlenode);//判断是否所有的箱子、目标点位、角色都在围墙内
						int whetherclose_whetherin = (whetherclose && whetherin) ? 1 : 0;//既有围墙，所有物件又都在围墙内，则该变量为1，否则为0
						int deltaw = (maxbottom - mintop) >= 2 ? 1 : 0;//游戏地图行数是否超过2，若是，则该变量为1，否则为0
						int deltal = (maxright - minleft) >= 4 ? 1 : 0;//游戏地图列数是否超过4，若是，则该变量为1，否则为0
						int bnum_equal_tnum = (w_b_t[1].size() == w_b_t[2].size() && w_b_t[1].size() > 0) ? 1 : 0;//是否又箱子和目标点位且二者数量相同，若是，则该变量为1，否则为0
						int havecharacter = (c.getcharacterx() != -1 && c.getcharactery() != -1 && c.getcharactero() != -1) ? 1 : 0;//角色信息是否正规，若是，则代表有角色，该变量为1，否则为0
						int errornum = (whetherclose_whetherin << 4) | (deltaw << 3) | (deltal << 2) | (bnum_equal_tnum << 1) | (havecharacter);//将5个用于判断的整型变量复合为一个数，代表着这5个数取值的32种情况，用于报错和判断自定义关卡是否最大程度符合规范
						reports_createcustomlevel_errors(errornum);//依据errornum进行报错
						if (errornum == 31)//若whetherclose_whetherin、deltaw、deltal、bnum_equal_tnum、havecharacter全为1，则代表自定义的关卡已最大程度符合规范，自定义关卡建立完毕
						{
							ifbreak = true;//用于判断是否完成自定义关卡的变量置为真
							string encode = encode_createcustomlevel(w_b_t, c, mintop, minleft, r);//对自定义关卡的信息进行编码
							//将自定义关卡编码、自定义关卡行列数存入文件
							ofstream customlevelcodefout("CustomGameLevel\\" + levelname + ".dat", ios::out);
							ofstream customlevelrcfout("CustomGameLevel\\" + levelname + "_rc.dat", ios::out);
							customlevelcodefout << encode;
							string rc = to_string(maxbottom - mintop + 1) + "," + to_string(maxright - minleft + 1) + ",";
							customlevelrcfout << rc;
							break;
						}
						break;
					}
					break;
				};
				if (x >= 1 * 40 && x <= 24 * 40 && y >= 1 * 40 && y <= 14 * 40 && nowbutton >= 0 && nowbutton <= 3)//点到自定义画布
				{
					int indexx = y / 40;//物件在地图上的横坐标
					int indexy = x / 40;//物件在地图上的纵坐标
					if (nowbutton == 0)//当前选中墙体方块
					{
						pair<int, int> windex = { indexx,indexy };//墙体坐标
						if (usedtargetindex.count(windex) || usedboxindex.count(windex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(windex))//若当前位置已被占用，则不进行任何操作
						{
							break;
						}
						usedwallindex.insert(windex);//将墙体坐标存入墙坐标集合
						w_b_t[0].insert(windex);//将墙体坐标存入墙坐标集合
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[0], 0, 0);//在当前位置绘制墙
						//更新墙体最小在地图上的纵坐标、最大在地图上的纵坐标、最小在地图上的横坐标、最大在地图上的横坐标
						MinLeft.emplace(indexy);
						MaxRight.emplace(indexy);
						MinTop.emplace(indexx);
						MaxBottom.emplace(indexx);
						minleft = min(minleft, indexy);
						maxright = max(maxright, indexy);
						mintop = min(mintop, indexx);
						maxbottom = max(maxbottom, indexx);
					}
					else if (nowbutton == 1)//当前选中箱子方块
					{
						pair<int, int> bindex = { indexx,indexy };//箱子坐标
						if (usedboxindex.count(bindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(bindex))//若当前位置没有目标点位且已被其他物件占用，则不进行任何操作
						{
							break;
						}
						usedboxindex.insert(bindex);//将箱子坐标存入箱子坐标集合
						w_b_t[1].insert(bindex);//将箱子坐标存入箱子坐标集合
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[usedtargetindex.count(bindex) ? 4 : 1], 0, 0);//在当前位置绘制箱子，若当前位置有目标点位，则绘制到达目标点位的箱子
						if (usedtargetindex.count(bindex))//若当前位置有目标点位
						{
							usedbox_targetindex.insert(bindex);//将箱子坐标存入到达目标点位的箱子坐标集合
							r++;//到达目标点位的箱子数加一
						}
					}
					else if (nowbutton == 2)//当前选中目标点位方块
					{
						pair<int, int> tindex = { indexx,indexy };//目标点位坐标
						if (usedtargetindex.count(tindex) || usedboxindex.count(tindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(tindex))//若当前位置已被占用，则不进行任何操作
						{
							break;
						}
						usedtargetindex.insert(tindex);//将目标点位坐标存入目标点位坐标集合
						w_b_t[2].insert(tindex);//将目标点位坐标存入目标点位坐标集合
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//在当前位置绘制目标点位
					}
					else if (nowbutton == 3)//当前选中角色方块
					{
						pair<int, int> cindex = { indexx,indexy };//当前角色坐标
						if (usedboxindex.count(cindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(cindex))//若当前位置没有目标点位且已被其他物件占用，则不进行任何操作
						{
							break;
						}
						c.setcharacter(indexx, indexy, 4);//设置角色信息，朝向默认为向下
						pair<int, int> preindex = characterindex;//上一个角色坐标
						int preimageindex = usedtargetindex.count(preindex) ? 2 : 6;//当前应在上一个角色位置处放置的图片索引，若上一个角色坐标处有目标点位，则该变量为2，否则为6
						putimage(preindex.second * 40, preindex.first * 40, 40, 40, &images_createcustomlevel[preimageindex], 0, 0);//更改上一个角色位置处的图片
						characterindex = cindex;//将当前角色坐标传给角色坐标
						putimage(characterindex.second * 40, characterindex.first * 40, 40, 40, &images_createcustomlevel[usedtargetindex.count(characterindex) ? 5 : 3], 0, 0);//更改当前角色位置处图片，若当前角色位置有目标点位，则图片索引为5，否则为3
					}
					break;
				};
				break;
			case WM_RBUTTONDOWN://按下右键
				x1 = msg.x;
				y1 = msg.y;
				if (x1 >= 1 * 40 && x1 <= 24 * 40 && y1 >= 1 * 40 && y1 <= 14 * 40)//若鼠标在自定义画布范围内
				{
					int indexx = y / 40;//物件在地图上的横坐标
					int indexy = x / 40;//物件在地图上的纵坐标
					pair<int, int> nowindexpair = { indexx,indexy };//当前在地图上的坐标
					if (usedwallindex.count(nowindexpair))//当前位置处为墙
					{
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//当前位置涂白
						//删除两个墙坐标集合中的当前墙坐标
						usedwallindex.erase(nowindexpair);
						w_b_t[0].erase(nowindexpair);
						//更新墙体最小在地图上的纵坐标、最大在地图上的纵坐标、最小在地图上的横坐标、最大在地图上的横坐标
						if (nowindexpair.first == MinTop.top())
						{
							MinTop.pop();
							mintop = MinTop.top();
						}
						if (nowindexpair.first == MaxBottom.top())
						{
							MaxBottom.pop();
							maxbottom = MaxBottom.top();
						}
						if (nowindexpair.second == MinLeft.top())
						{
							MinLeft.pop();
							minleft = MinLeft.top();
						}
						if (nowindexpair.second == MaxRight.top())
						{
							MaxRight.pop();
							maxright = MaxRight.top();
						}
						break;
					}
					if (characterindex.first == indexx && characterindex.second == indexy)//当前位置处为角色
					{
						if (usedtargetindex.count(nowindexpair))//若当前位置处还有目标点位
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//当前位置处图片更新为目标点位图片
						}
						else
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//当前位置处涂白
						}
						c.setcharacter(-1, -1, -1);//角色坐标更改为{-1，-1}，朝向更改为-1
						characterindex = { -1,-1 };//角色坐标更改为{-1，-1}
						break;
					}
					if (usedboxindex.count(nowindexpair))//当前位置处为箱子
					{
						if (usedbox_targetindex.count(nowindexpair))//若当前位置处还有目标点位
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//当前位置处图片更新为目标点位图片
							usedbox_targetindex.erase(nowindexpair);//删除达到目标点位的箱子坐标集合中的当前坐标
							r--;//达到目标点位的箱子数减一
						}
						else
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//当前位置处涂白
						}
						//删除两个箱子坐标集合中的当前墙坐标
						usedboxindex.erase(nowindexpair);
						w_b_t[1].erase(nowindexpair);
						break;
					}
					if (usedtargetindex.count(nowindexpair))//当前位置处为目标点位
					{
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//当前位置处涂白
						//删除两个目标点位坐标集合中的当前目标点位坐标
						usedtargetindex.erase(nowindexpair);
						w_b_t[2].erase(nowindexpair);
						break;
					}
					break;
				};
				break;
			}
			if (ifbreak)break;//若完成自定义关卡，则退出自定义功能界面循环
		}
	}
}

void DrawSelectCustomLevelInterface(int c)//绘制自定义关卡选关界面
{
	setbkcolor(0x00B5E51D);//设置背景色为0x00B5E51D
	cleardevice();//清空窗口，使背景色为0x00B5E51D
	setlinecolor(BLACK);//设置线条颜色为黑色
	settextcolor(BLACK);//设置文本颜色为黑色
	for (int i = 0; i <= c + 1; i++)//绘制分隔线
	{
		line(0, i * 30, 500, i * 30);
	}
	for (int i = 0; i < c; i++)//用文件流读取关卡名，并依次打印关卡名
	{
		ifstream customlevelnamefin("CustomGameLevel\\" + to_string(i) + ".dat", ios::in);
		string levelname;
		customlevelnamefin >> levelname;
		char text[1024] = { '\0' };
		int levelnamesize = levelname.size();
		for (int j = 0; j < levelnamesize; j++)
		{
			text[j] = levelname[j];
		}
		outtextxy(5, i * 30 + 5, text);
	}
	outtextxy(5, c * 30 + 5, "返回");//返回按钮
}

vector<string> DrawLoginInputInterface(bool& ifcancel)//绘制登录的输入界面，并返回账户及密码的输入值
{
	int x0 = 240;//标题（“请登录”）左上角横坐标
	int y0 = 85;//标题（“请登录”）左上角纵坐标
	int x1 = 100;//账号输入框左上角横坐标
	int y1 = 185;//账号输入框左上角纵坐标
	int x2 = 100;//密码输入框左上角横坐标
	int y2 = 275;//密码输入框左上角纵坐标
	int x3 = 100;//确定按钮左上角横坐标
	int y3 = 365;//确定按钮左上角纵坐标
	int x4 = 380;//取消按钮左上角横坐标
	int y4 = 365;//取消按钮左上角纵坐标
	int w = 400;//输入框长度
	int h = 30;//输入框宽度
	int LineColor = BLACK;//直线颜色
	int TextColor = BLACK;//文本颜色
	int BackgroundColor = WHITE;//背景颜色
	char account_number[1024] = { '\0' };//用于存储账号文本
	char account_password[1024] = { '\0' };//用于存储密码文本
	char covered_account_password[1024] = { '\0' };//已加密覆盖的密码
	int account_number_length = 0;//输入的账号文本长度
	int account_password_length = 0;//输入的密码文本长度
	int covered_account_password_length = 0;//已加密覆盖的密码长度
	int index1 = 0;//当前光标在账号输入框中的位置
	int index2 = 0;//当前光标在密码输入框中的位置
	bool first_second = true;//光标在第一输入框还是第二输入框，真为第一输入框，假为第二输入框
	bool ifcansee = false;//密码是否可见
	vector<string> number_password(2, "");//最终返回的字符串数组，大小为2，0号位上存账号，1号位上存密码
	setbkcolor(BackgroundColor);//设置背景颜色
	cleardevice();//清空窗口，重初始化窗口样式
	settextstyle(40, 0, "宋体");//设置中文字体大小为40*40像素，字体为宋体
	outtextxy(x0, y0, "请登录");//输出标题：“请登录”
	settextstyle(20, 0, "宋体");//设置中文字体大小为20*20像素，字体为宋体
	settextcolor(TextColor);//设置文本颜色
	setlinecolor(LineColor);//设置直线颜色
	rectangle(x1, y1, x1 + w, y1 + h);//绘制账号输入框
	outtextxy(x1 + 5, y1 - 25, "请输入账号：");//输出提示语，起始坐标（左上角）为（x1+5，y1-25）
	rectangle(x2, y2, x2 + w, y2 + h);//绘制密码输入框
	rectangle(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//绘制隐藏密码按钮框
	outtextxy(x2 + 5, y2 - 25, "请输入密码：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
	outtextxy(x2 + w + 10, y2 + 5, "隐");//在隐藏密码按钮框中输出隐字
	if (!ifcansee)line(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//输出斜线
	rectangle(x3, y3, x3 + 120, y3 + h);//绘制确定按钮框
	rectangle(x4, y4, x4 + 120, y4 + h);//绘制取消按钮框
	outtextxy(x3 + 40, y3 + 5, "确定");//输出确定
	outtextxy(x4 + 40, y4 + 5, "取消");//输出取消
	line(x1 + 5 + index1 * 10, y1 + 5, x1 + 5 + index1 * 10, y1 + 25);//绘制光标
	ExMessage msg;//鼠标信息
	char c;//当前输入的字符
	bool ifbreak = false;//用于判断是否推出循环
	while (1)//进入输入循环
	{
		int x = first_second ? x1 : x2;
		int y = first_second ? y1 : y2;
		int index = first_second ? index1 : index2;
		outtextxy(x1 + 5, y1 + 5, account_number);//输出输入的账号
		outtextxy(x2 + 5, y2 + 5, !ifcansee ? covered_account_password : account_password);//输出输入的密码
		settextstyle(40, 0, "宋体");//设置中文字体大小为40*40像素，字体为宋体
		outtextxy(x0, y0, "请登录");//输出标题：“请登录”
		settextstyle(20, 0, "宋体");//设置中文字体大小为20*20像素，字体为宋体
		rectangle(x1, y1, x1 + w, y1 + h);//绘制账号输入框
		outtextxy(x1 + 5, y1 - 25, "请输入账号：");//输出提示语，起始坐标（左上角）为（x1+5，y1-25）
		rectangle(x2, y2, x2 + w, y2 + h);//绘制密码输入框
		rectangle(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//绘制隐藏密码按钮框
		outtextxy(x2 + 5, y2 - 25, "请输入密码：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
		outtextxy(x2 + w + 10, y2 + 5, "隐");//在隐藏密码按钮框中输出隐字
		if (!ifcansee)line(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//输出斜线
		rectangle(x3, y3, x3 + 120, y3 + h);//绘制确定按钮框
		rectangle(x4, y4, x4 + 120, y4 + h);//绘制取消按钮框
		outtextxy(x3 + 40, y3 + 5, "确定");//输出确定
		outtextxy(x4 + 40, y4 + 5, "取消");//输出取消
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//绘制光标
		if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
		{
			switch (msg.message)//判断鼠标信息
			{
			case WM_LBUTTONDOWN://按下鼠标左键
				cleardevice();
				int X = msg.x;//鼠标此时所指向窗口中像素位置的横坐标
				int Y = msg.y;//鼠标此时所指向窗口中像素位置的纵坐标
				if (X >= x3 && X <= x3 + 120 && Y >= y3 && Y <= y3 + h)//鼠标在确定按钮框范围内
				{
					number_password[0] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//存储当前的账号文本信息
					{
						number_password[0].push_back(account_number[i]);
					}
					if (number_password[0].size() == 0)//若未输入账号
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x1, y1 + h + 5, "账号未输入，请输入账号");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					if (!users_accountnumber2password.count(number_password[0]))//若用户不存在
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x1, y1 + h + 5, "不存在该用户");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					number_password[1] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//存储当前的密码文本信息
					{
						number_password[1].push_back(account_password[i]);
					}
					number_password[1] = encrypt_password(number_password[1]);
					if (number_password[1].size() == 0)//若未输入密码
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x2, y2 + h + 5, "密码未输入，请输入密码");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					if (users_accountnumber2password[number_password[0]] != number_password[1])//若密码错误
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x2, y2 + h + 5, "密码错误");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					break;
				};
				if (X >= x4 && X <= x4 + 120 && Y >= y4 && Y <= y4 + h)//鼠标在取消按钮框范围内
				{
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					ifcancel = true;//是否取消置为真
					break;
				};
				if (X >= x2 + w + 5 && X <= x2 + w + h + 5 && Y >= y2 && Y <= y2 + h)//鼠标在隐藏密码按钮范围内
				{
					cleardevice();
					ifcansee ^= 1;//更改密码是否可见
					break;
				};
				if (X >= x1 && X <= x1 + w && Y >= y1 && Y <= y1 + h)//鼠标在账号输入框范围内
				{
					first_second = true;//将输入区转到账号输入框
					index1 = account_number_length;//输入框光标位置放到输入框文本末尾
					break;
				};
				if (X >= x2 && X <= x2 + w && Y >= y2 && Y <= y2 + h)//鼠标在密码输入框范围内
				{
					first_second = false;//将输入区转到密码输入框
					index2 = account_password_length;//输入框光标位置放到输入框文本末尾
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//捕获按键信息
		{
			c = _getch();//将当前按到的字符传给字符c
			if (first_second)//输入账号
			{
				if (c == '\b' && account_number_length > 0 && index1 > 0)//按到backspace且当前输入框中光标之前有可删除字符
				{
					if (index1 == account_number_length)//光标位置在输入文本的末尾
					{
						cleardevice();
						account_number[--account_number_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
						index1--;//光标位置减一
					}
					else//光标位置不在输入文本末尾
					{
						cleardevice();
						for (int i = index1 - 1; i < account_number_length; i++)account_number[i] = account_number[i + 1];//光标之后的字符依次向前移动一格
						index1--;//光标位置减一
						account_number[--account_number_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					}
				}
				else if (c == '\b' && account_number_length == 0)//按到backspace且已无输入文本可删除
				{
					cleardevice();
					continue;//继续循环
				}
				else if (c == '\r')//按到回车
				{
					cleardevice();
					first_second = false;//换到密码输入
					continue;
				}
				else
				{
					if (c == 75 && index1 > 0)//按到左键且光标还可左移
					{
						index1--;//光标位置减一
						cleardevice();
						continue;
					}
					if (c == 77 && index1 < account_number_length)//按到右键且光标还可右移
					{
						index1++;//光标位置加一
						cleardevice();
						continue;
					}
					if (index1 == account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//按到数字且光标在文本末尾
					{
						index1++;//光标位置加一
						account_number[account_number_length++] = c;//使输入的文本末尾为当前字符，文本长度加一
						account_number[account_number_length] = '\0';//保证文本最后有结束符
						cleardevice();
						continue;
					}
					if (index1 != account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//按到数字且光标不在文本末尾
					{
						for (int i = account_number_length; i > index1; i--)account_number[i] = account_number[i - 1];//光标之后的字符全体依次向后移动一格
						account_number[index1++] = c;//光标位置为当前字符并使光标位置加一
						account_number_length++;//文本长度加一
						cleardevice();
						continue;
					}
				}
			}
			else//输入密码
			{
				if (c == '\b' && account_password_length > 0 && index2 > 0)//按到backspace且当前输入框中光标之前有可删除字符
				{
					if (index2 == account_password_length)//光标位置在输入文本的末尾
					{
						cleardevice();
						account_password[--account_password_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
						index2--;//光标位置减一
					}
					else//光标位置不在输入文本末尾
					{
						cleardevice();
						for (int i = index2 - 1; i < account_password_length; i++)account_password[i] = account_password[i + 1];//光标之后的字符依次向前移动一格
						index2--;//光标位置减一
						account_password[--account_password_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					}
					covered_account_password[--covered_account_password_length] = '\0';//覆盖的密码也退格
				}
				else if (c == '\b' && account_password_length == 0)//按到backspace且已无输入文本可删除
				{
					cleardevice();
					continue;//继续循环
				}
				else
				{
					if (c == 75 && index2 > 0)//按到左键且光标还可左移
					{
						index2--;//光标位置减一
						cleardevice();
						continue;
					}
					if (c == 77 && index2 < account_password_length)//按到右键且光标还可右移
					{
						index2++;//光标位置加一
						cleardevice();
						continue;
					}
					if (index2 == account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//按到支持的文本且光标在文本末尾
					{
						index2++;//光标位置加一
						account_password[account_password_length++] = c;//使输入的文本末尾为当前字符，文本长度加一
						account_password[account_password_length] = '\0';//保证文本最后有结束符
						covered_account_password[covered_account_password_length++] = '*';//覆盖密码文本多加一个‘*’
						cleardevice();
						continue;
					}
					if (index2 != account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//按到支持的文本且光标不在文本末尾
					{
						for (int i = account_password_length; i > index2; i--)account_password[i] = account_password[i - 1];//光标之后的字符全体依次向后移动一格
						account_password[index2++] = c;//光标位置为当前字符并使光标位置加一
						account_password_length++;//文本长度加一
						covered_account_password[covered_account_password_length++] = '*';//覆盖密码文本多加一个‘*’
						cleardevice();
						continue;
					}
				}
			}
			if (c == '\r')//按到回车
			{
				while (1)
				{
					number_password[0] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//存储当前的账号文本信息
					{
						number_password[0].push_back(account_number[i]);
					}
					if (number_password[0].size() == 0)//若未输入账号
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x1, y1 + h + 5, "账号未输入，请输入账号");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					if (!users_accountnumber2password.count(number_password[0]))//若用户不存在
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x1, y1 + h + 5, "不存在该用户");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					number_password[1] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//存储当前的密码文本信息
					{
						number_password[1].push_back(account_password[i]);
					}
					number_password[1] = encrypt_password(number_password[1]);
					if (number_password[1].size() == 0)//若未输入密码
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x2, y2 + h + 5, "密码未输入，请输入密码");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					if (users_accountnumber2password[number_password[0]] != number_password[1])//若密码错误
					{
						settextcolor(RED);
						settextstyle(15, 0, "宋体");
						outtextxy(x2, y2 + h + 5, "密码错误");
						settextcolor(BLACK);
						settextstyle(20, 0, "宋体");
						break;
					}
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					break;
				}
			};
		}
		if (ifbreak)break;//用于控制继续循环或退出循环
	}
	return number_password;
}

vector<string> DrawRegisterInputInterface(bool& ifcancel)//绘制注册信息输入界面，并返回注册信息
{
	int x0 = 240;//标题（“请注册”）左上角横坐标
	int y0 = 85;//标题（“请注册”）左上角纵坐标
	int x1 = 100;//用户名输入框左上角横坐标
	int y1 = 185;//用户名输入框左上角纵坐标
	int x2 = 100;//账号输入框左上角横坐标
	int y2 = 275;//账号输入框左上角纵坐标
	int x3 = 100;//密码输入框左上角横坐标
	int y3 = 365;//密码输入框左上角纵坐标
	int x4 = 100;//确定按钮左上角横坐标
	int y4 = 455;//确定按钮左上角纵坐标
	int x5 = 380;//取消按钮左上角横坐标
	int y5 = 455;//取消按钮左上角纵坐标
	int w = 400;//输入框长度
	int h = 30;//输入框宽度
	int LineColor = BLACK;//直线颜色
	int TextColor = BLACK;//文本颜色
	int BackgroundColor = WHITE;//背景颜色
	char user_name[1024] = { '\0' };//用于存储用户名文本
	char account_number[1024] = { '\0' };//用于存储账号文本
	char account_password[1024] = { '\0' };//用于存储密码文本
	char covered_account_password[1024] = { '\0' };//已加密覆盖的密码
	int user_name_length = 0;//输入的用户名长度
	int account_number_length = 0;//输入的账号文本长度
	int account_password_length = 0;//输入的密码文本长度
	int covered_account_password_length = 0;//已加密覆盖的密码长度
	int index1 = 0;//当前光标在用户名输入框中的位置
	int index2 = 0;//当前光标在账号输入框中的位置
	int index3 = 0;//当前光标在密码输入框中的位置
	int first_second_third = 0;//判断光标在第几输入框，0为第一输入框，1为第二输入框，2为第三输入框
	bool ifcansee = false;//密码是否可见
	vector<string> name_number_password(3, "");//最终返回的字符串数组，大小为3，0号位上存用户名，1号位上存账号，2号位上存密码
	setbkcolor(BackgroundColor);//设置背景颜色
	cleardevice();//清空窗口，重初始化窗口样式
	settextstyle(40, 0, "宋体");//设置中文字体大小为40*40像素，字体为宋体
	outtextxy(x0, y0, "请注册");//输出标题：“请登录”
	settextstyle(20, 0, "宋体");//设置中文字体大小为20*20像素，字体为宋体
	settextcolor(TextColor);//设置文本颜色
	setlinecolor(LineColor);//设置直线颜色
	rectangle(x1, y1, x1 + w, y1 + h);//绘制用户名输入框
	outtextxy(x1 + 5, y1 - 25, "请输入用户名(支持小写英文字母和数字)：");//输出提示语，起始坐标（左上角）为（x1+5，y1-25）
	rectangle(x2, y2, x2 + w, y2 + h);//绘制账号输入框
	outtextxy(x2 + 5, y2 - 25, "请输入账号(数字)：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
	rectangle(x3, y3, x3 + w, y3 + h);//绘制密码输入框
	rectangle(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//绘制隐藏密码按钮框
	outtextxy(x3 + 5, y3 - 25, "请输入密码(支持小写英文字母 数字 ! . * @)：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
	outtextxy(x3 + w + 10, y3 + 5, "隐");//在隐藏密码按钮框中输出隐字
	if (!ifcansee)line(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//输出斜线
	rectangle(x4, y4, x4 + 120, y4 + h);//绘制确定按钮框
	rectangle(x5, y5, x5 + 120, y5 + h);//绘制取消按钮框
	outtextxy(x4 + 40, y4 + 5, "确定");//输出确定
	outtextxy(x5 + 40, y5 + 5, "取消");//输出取消
	line(x1 + 5 + index1 * 10, y1 + 5, x1 + 5 + index1 * 10, y1 + 25);//绘制光标
	ExMessage msg;//鼠标信息
	char c;//当前输入的字符
	bool ifbreak = false;//用于判断是否推出循环
	int index = NULL;//光标位置
	while (1)//进入输入循环
	{
		int x = 100;
		int y = 185 + first_second_third * 90;
		if (first_second_third == 0)index = index1;
		if (first_second_third == 1)index = index2;
		if (first_second_third == 2)index = index3;
		outtextxy(x1 + 5, y1 + 5, user_name);//输出输入的用户名
		outtextxy(x2 + 5, y2 + 5, account_number);//输出输入的账号
		outtextxy(x3 + 5, y3 + 5, !ifcansee ? covered_account_password : account_password);//输出输入的密码
		settextstyle(40, 0, "宋体");//设置中文字体大小为40*40像素，字体为宋体
		outtextxy(x0, y0, "请注册");//输出标题：“请登录”
		settextstyle(20, 0, "宋体");//设置中文字体大小为20*20像素，字体为宋体
		rectangle(x1, y1, x1 + w, y1 + h);//绘制用户名输入框
		outtextxy(x1 + 5, y1 - 25, "请输入用户名(支持小写英文字母和数字)：");//输出提示语，起始坐标（左上角）为（x1+5，y1-25）
		rectangle(x2, y2, x2 + w, y2 + h);//绘制账号输入框
		outtextxy(x2 + 5, y2 - 25, "请输入账号(数字)：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
		rectangle(x3, y3, x3 + w, y3 + h);//绘制密码输入框
		rectangle(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//绘制隐藏密码按钮框
		outtextxy(x3 + 5, y3 - 25, "请输入密码(支持小写英文字母 数字 ! . * @)：");//输出提示语，起始坐标（左上角）为（x2+5，y2-25）
		outtextxy(x3 + w + 10, y3 + 5, "隐");//在隐藏密码按钮框中输出隐字
		if (!ifcansee)line(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//输出斜线
		rectangle(x4, y4, x4 + 120, y4 + h);//绘制确定按钮框
		rectangle(x5, y5, x5 + 120, y5 + h);//绘制取消按钮框
		outtextxy(x4 + 40, y4 + 5, "确定");//输出确定
		outtextxy(x5 + 40, y5 + 5, "取消");//输出取消
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//绘制光标
		if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
		{
			switch (msg.message)//判断鼠标信息
			{
			case WM_LBUTTONDOWN://按下鼠标左键
				cleardevice();
				int X = msg.x;//鼠标此时所指向窗口中像素位置的横坐标
				int Y = msg.y;//鼠标此时所指向窗口中像素位置的纵坐标
				if (X >= x4 && X <= x4 + 120 && Y >= y4 && Y <= y4 + h)//鼠标在确定按钮框范围内
				{
					name_number_password[0] = "";
					for (int i = 0; i < 1024 && user_name[i] != '\0'; i++)//存储当前的用户名文本信息
					{
						name_number_password[0].push_back(user_name[i]);
					}
					name_number_password[1] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//存储当前的账号文本信息
					{
						name_number_password[1].push_back(account_number[i]);
					}
					name_number_password[2] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//存储当前的密码文本信息
					{
						name_number_password[2].push_back(account_password[i]);
					}
					name_number_password[2] = encrypt_password(name_number_password[2]);
					int existname = !(users_names.count(name_number_password[0]));//用户名是否存在
					int existnumber = !(users_accountnumber2password.count(name_number_password[1]));//账号是否已被注册
					int havename = !(name_number_password[0].size() == 0);//是否输入了用户名
					int havenumber = !(name_number_password[1].size() == 0);//是否输入了账号
					int havepassword = !(name_number_password[2].size() == 0);//是否输入了密码
					if (havenumber == 0)existnumber = 0;
					if (havename == 0)existname = 0;
					int errornum = (existname << 4) | (existnumber << 3) | (havename << 2) | (havenumber << 1) | (havepassword);
					settextcolor(RED);
					settextstyle(15, 0, "宋体");
					switch (errornum)
					{
					case 0:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 1:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 2:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 3:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 4:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 5:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 6:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 7:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 8:
						break;
					case 9:
						break;
					case 10:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 11:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						break;
					case 12:
						break;
					case 13:
						break;
					case 14:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 15:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						break;
					case 16:
						break;
					case 17:
						break;
					case 18:
						break;
					case 19:
						break;
					case 20:
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 21:
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 22:
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 23:
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 24:
						break;
					case 25:
						break;
					case 26:
						break;
					case 27:
						break;
					case 28:
						break;
					case 29:
						break;
					case 30:
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 31:
						ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
						break;
					}
					settextcolor(BLACK);
					settextstyle(20, 0, "宋体");
					break;
				};
				if (X >= x5 && X <= x5 + 120 && Y >= y5 && Y <= y5 + h)//鼠标在取消按钮框范围内
				{
					ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
					ifcancel = true;//是否取消置为真
					break;
				};
				if (X >= x3 + w + 5 && X <= x3 + w + h + 5 && Y >= y3 && Y <= y3 + h)//鼠标在隐藏密码按钮范围内
				{
					cleardevice();
					ifcansee ^= 1;//更改密码是否可见
					break;
				};
				if (X >= x1 && X <= x1 + w && Y >= y1 && Y <= y1 + h)//鼠标在用户名输入框范围内
				{
					first_second_third = 0;//将输入区转到用户名输入框
					index1 = user_name_length;//输入框光标位置放到输入框文本末尾
					break;
				};
				if (X >= x2 && X <= x2 + w && Y >= y2 && Y <= y2 + h)//鼠标在账号输入框范围内
				{
					first_second_third = 1;//将输入区转到账号输入框
					index2 = account_number_length;//输入框光标位置放到输入框文本末尾
					break;
				};
				if (X >= x3 && X <= x3 + w && Y >= y3 && Y <= y3 + h)//鼠标在密码输入框范围内
				{
					first_second_third = 2;//将输入区转到密码输入框
					index3 = account_password_length;//输入框光标位置放到输入框文本末尾
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//捕获按键信息
		{
			c = _getch();//将当前按到的字符传给字符c
			switch (first_second_third)
			{
			case 0://输入用户名
				if (c == '\b' && user_name_length > 0 && index1 > 0)//按到backspace且当前输入框中光标之前有可删除字符
				{
					if (index1 == user_name_length)//光标位置在输入文本的末尾
					{
						cleardevice();
						user_name[--user_name_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
						index1--;//光标位置减一
					}
					else//光标位置不在输入文本末尾
					{
						cleardevice();
						for (int i = index1 - 1; i < user_name_length; i++)user_name[i] = user_name[i + 1];//光标之后的字符依次向前移动一格
						index1--;//光标位置减一
						user_name[--user_name_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					}
				}
				else if (c == '\b' && user_name_length == 0)//按到backspace且已无输入文本可删除
				{
					cleardevice();
					continue;//继续循环
				}
				else if (c == '\r')//按到回车
				{
					cleardevice();
					first_second_third++;//换到账号输入
					continue;
				}
				else
				{
					if (c == 75 && index1 > 0)//按到左键且光标还可左移
					{
						index1--;//光标位置减一
						cleardevice();
						continue;
					}
					if (c == 77 && index1 < user_name_length)//按到右键且光标还可右移
					{
						index1++;//光标位置加一
						cleardevice();
						continue;
					}
					if (index1 == user_name_length && user_name_length < 39 && ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))//按到支持的文本且光标在文本末尾
					{
						index1++;//光标位置加一
						user_name[user_name_length++] = c;//使输入的文本末尾为当前字符，文本长度加一
						user_name[user_name_length] = '\0';//保证文本最后有结束符
						cleardevice();
						continue;
					}
					if (index1 != user_name_length && user_name_length < 39 && ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))//按到支持的文本且光标不在文本末尾
					{
						for (int i = user_name_length; i > index1; i--)user_name[i] = user_name[i - 1];//光标之后的字符全体依次向后移动一格
						user_name[index1++] = c;//光标位置为当前字符并使光标位置加一
						user_name_length++;//文本长度加一
						cleardevice();
						continue;
					}
				}
				break;
			case 1://输入账号
				if (c == '\b' && account_number_length > 0 && index2 > 0)//按到backspace且当前输入框中光标之前有可删除字符
				{
					if (index2 == account_number_length)//光标位置在输入文本的末尾
					{
						cleardevice();
						account_number[--account_number_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
						index2--;//光标位置减一
					}
					else//光标位置不在输入文本末尾
					{
						cleardevice();
						for (int i = index2 - 1; i < account_number_length; i++)account_number[i] = account_number[i + 1];//光标之后的字符依次向前移动一格
						index2--;//光标位置减一
						account_number[--account_number_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					}
				}
				else if (c == '\b' && account_number_length == 0)//按到backspace且已无输入文本可删除
				{
					cleardevice();
					continue;//继续循环
				}
				else if (c == '\r')//按到回车
				{
					cleardevice();
					first_second_third++;//换到密码输入
					continue;
				}
				else
				{
					if (c == 75 && index2 > 0)//按到左键且光标还可左移
					{
						index2--;//光标位置减一
						cleardevice();
						continue;
					}
					if (c == 77 && index2 < account_number_length)//按到右键且光标还可右移
					{
						index2++;//光标位置加一
						cleardevice();
						continue;
					}
					if (index2 == account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//按到数字且光标在文本末尾
					{
						index2++;//光标位置加一
						account_number[account_number_length++] = c;//使输入的文本末尾为当前字符，文本长度加一
						account_number[account_number_length] = '\0';//保证文本最后有结束符
						cleardevice();
						continue;
					}
					if (index2 != account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//按到数字且光标不在文本末尾
					{
						for (int i = account_number_length; i > index2; i--)account_number[i] = account_number[i - 1];//光标之后的字符全体依次向后移动一格
						account_number[index2++] = c;//光标位置为当前字符并使光标位置加一
						account_number_length++;//文本长度加一
						cleardevice();
						continue;
					}
				}
				break;
			case 2://输入密码
				if (c == '\b' && account_password_length > 0 && index3 > 0)//按到backspace且当前输入框中光标之前有可删除字符
				{
					if (index3 == account_password_length)//光标位置在输入文本的末尾
					{
						cleardevice();
						account_password[--account_password_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
						index3--;//光标位置减一
					}
					else//光标位置不在输入文本末尾
					{
						cleardevice();
						for (int i = index3 - 1; i < account_password_length; i++)account_password[i] = account_password[i + 1];//光标之后的字符依次向前移动一格
						index3--;//光标位置减一
						account_password[--account_password_length] = '\0';//将最后一个字符变为结束符，输入文本长度减一
					}
					covered_account_password[--covered_account_password_length] = '\0';//覆盖的密码也退格
				}
				else if (c == '\b' && account_password_length == 0)//按到backspace且已无输入文本可删除
				{
					cleardevice();
					continue;//继续循环
				}
				else if (c == '\r')//按到回车
				{
					name_number_password[0] = "";
					for (int i = 0; i < 1024 && user_name[i] != '\0'; i++)//存储当前的用户名文本信息
					{
						name_number_password[0].push_back(user_name[i]);
					}
					name_number_password[1] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//存储当前的账号文本信息
					{
						name_number_password[1].push_back(account_number[i]);
					}
					name_number_password[2] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//存储当前的密码文本信息
					{
						name_number_password[2].push_back(account_password[i]);
					}
					name_number_password[2] = encrypt_password(name_number_password[2]);
					int existname = !(users_names.count(name_number_password[0]));//用户名是否存在
					int existnumber = !(users_accountnumber2password.count(name_number_password[1]));//账号是否已被注册
					int havename = !(name_number_password[0].size() == 0);//是否输入了用户名
					int havenumber = !(name_number_password[1].size() == 0);//是否输入了账号
					int havepassword = !(name_number_password[2].size() == 0);//是否输入了密码
					if (havenumber == 0)existnumber = 0;
					if (havename == 0)existname = 0;
					int errornum = (existname << 4) | (existnumber << 3) | (havename << 2) | (havenumber << 1) | (havepassword);
					settextcolor(RED);
					settextstyle(15, 0, "宋体");
					switch (errornum)
					{
					case 0:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 1:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 2:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 3:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 4:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 5:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 6:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 7:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 8:
						break;
					case 9:
						break;
					case 10:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 11:
						outtextxy(x1, y1 + h + 5, "用户名未输入，请输入用户名");
						break;
					case 12:
						break;
					case 13:
						break;
					case 14:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 15:
						outtextxy(x1, y1 + h + 5, "该用户名已存在");
						break;
					case 16:
						break;
					case 17:
						break;
					case 18:
						break;
					case 19:
						break;
					case 20:
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 21:
						outtextxy(x2, y2 + h + 5, "账号未输入，请输入账号");
						break;
					case 22:
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 23:
						outtextxy(x2, y2 + h + 5, "该账号已被注册");
						break;
					case 24:
						break;
					case 25:
						break;
					case 26:
						break;
					case 27:
						break;
					case 28:
						break;
					case 29:
						break;
					case 30:
						outtextxy(x3, y3 + h + 5, "密码未输入，请输入密码");
						break;
					case 31:
						ifbreak = true;//判断是否退出循环的变量置为真，可退出输入循环
						break;
					}
					settextcolor(BLACK);
					settextstyle(20, 0, "宋体");
					break;
				}
				else
				{
					if (c == 75 && index3 > 0)//按到左键且光标还可左移
					{
						index3--;//光标位置减一
						cleardevice();
						continue;
					}
					if (c == 77 && index3 < account_password_length)//按到右键且光标还可右移
					{
						index3++;//光标位置加一
						cleardevice();
						continue;
					}
					if (index3 == account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//按到支持的文本且光标在文本末尾
					{
						index3++;//光标位置加一
						account_password[account_password_length++] = c;//使输入的文本末尾为当前字符，文本长度加一
						account_password[account_password_length] = '\0';//保证文本最后有结束符
						covered_account_password[covered_account_password_length++] = '*';//覆盖密码文本多加一个‘*’
						cleardevice();
						continue;
					}
					if (index3 != account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//按到支持的文本且光标不在文本末尾
					{
						for (int i = account_password_length; i > index3; i--)account_password[i] = account_password[i - 1];//光标之后的字符全体依次向后移动一格
						account_password[index3++] = c;//光标位置为当前字符并使光标位置加一
						account_password_length++;//文本长度加一
						covered_account_password[covered_account_password_length++] = '*';//覆盖密码文本多加一个‘*’
						cleardevice();
						continue;
					}
				}
				break;
			}
		}
		if (ifbreak)break;//用于控制继续循环或退出循环
	}
	return name_number_password;
}

void DrawTheRankingList()//绘制排行榜页面
{
	setbkcolor(RGB(53, 255, 175));//设置背景色为RGB(53, 255, 175)
	cleardevice();//清空窗口，使背景色变为RGB(53, 255, 175)
	setlinecolor(BLACK);//设置线条颜色为黑色
	settextcolor(BLACK);//设置文本颜色为黑色
	settextstyle(20, 0, "宋体");//设置字体样式
	outtextxy(5, 5, "排名");//在窗口坐标{5，5}处打印“排名”字样
	outtextxy(5 + 100, 5, "玩家");//在窗口坐标{105，5}处打印“玩家”字样
	outtextxy(5 + 500, 5, "总分");//在窗口坐标{505，5}处打印“总分”字样
	int n = user_totalscore.size() + 2;//行数为user_totalscore.size() + 2
	for (int i = 0; i <= n; i++)//绘制行分隔线
	{
		line(0, i * 30, 1600, i * 30);
	}
	line(100, 0, 100, (n - 1) * 30);//绘制列分隔线
	line(500, 0, 500, (n - 1) * 30);//绘制列分隔线
	line(900, 0, 900, (n - 1) * 30);//绘制列分隔线
	outtextxy(5, (n - 1) * 30 + 5, "返回");//在窗口坐标{5, (n - 1) * 30 + 5}处打印“返回”字样，代表返回按钮
	vector<pair<int, string>> username_score;//分数-用户名数组
	map<string, string>::iterator iter = user_totalscore.begin();//创建一个map<string,string>的迭代器，并初始化为user_totalscore哈希表的起始位置指针
	while (iter != user_totalscore.end())//遍历用户总分哈希表
	{
		username_score.emplace_back(stoi(iter->second), iter->first);//存储每个用户的用户名及总分
		iter++;
	}
	sort(username_score.begin(), username_score.end(), greater<>());//从大到小排序分数-用户名数组
	int index = 1;//记录排名
	int un = username_score.size();//分数-用户名数组的大小
	for (int i = 0; i < un; i++)//遍历分数-用户名数组，并依次打印当前位置的名次、用户名、总分
	{
		outtextxy(5, index * 30 + 5, to_string(index).c_str());
		outtextxy(5 + 100, index * 30 + 5, username_score[i].second.c_str());
		outtextxy(5 + 500, index * 30 + 5, to_string(username_score[i].first).c_str());
		index++;
	}
}

bool whethercircle(set<pair<int, int>> wallindex, set<pair<int, int>>& circlenode)//判断自定义关卡中的墙体是否可围成一个环
{
	if (wallindex.size() == 0)return false;//若墙坐标集合为空，则返回false
	int all_node_acount = wallindex.size();//结点数量（每个墙体代表一个结点）
	int degree_1_node_acount = 0;//度小于等于1的结点数量（若每个墙体上下左右四个方向中的任意方向有其他墙体，则视为当前墙体在该方向处有连边，也即每个墙体只能在上下左右四个方向连边，度最大为4，最小为0）
	vector<pair<int, int>> orientation = { {0,-1},{-1,0},{0,1},{1,0} };//左上右下四个方向
	map<pair<int, int>, int> nodeindex_nodedegree;//墙体与该墙体的度的映射
	set<pair<int, int>>::iterator iter = wallindex.begin();//创建一个set<pair<int, int>>迭代器，初始化为wallindex集合的起始位置指针
	while (iter != wallindex.end())//遍历wallindex集合
	{
		int count = 0;//记录墙体四周的墙数
		for (int i = 0; i < 4; i++)//遍历四个方向，若有其他墙体，则count加一
		{
			pair<int, int> wallaround = { iter->first + orientation[i].first,iter->second + orientation[i].second };
			if (wallindex.count(wallaround))count++;
		}
		nodeindex_nodedegree[{iter->first, iter->second}] = count;//存储当前墙的坐标及当前墙的度
		iter++;
	}
	set<pair<int, int>> usednode;//已遍历过的结点
	map<pair<int, int>, int>::iterator iter2 = nodeindex_nodedegree.begin();//创建一个map<pair<int, int>, int>迭代器，初始化为nodeindex_nodedegree哈希表的起始位置指针
	stack<pair<int, int>> node_degree_1;//存储度小于等于1的结点
	while (iter2 != nodeindex_nodedegree.end())//遍历nodeindex_nodedegree哈希表
	{
		if (iter2->second <= 1)//若度小于等于1
		{
			node_degree_1.emplace(iter2->first);//当前节点压栈
			usednode.insert(iter2->first);//当前节点标记为已遍历过
			degree_1_node_acount++;//度小于等于1的结点数量加一
		}
		iter2++;
	}
	while (!node_degree_1.empty())//当存储度小于等于1的结点的栈不为空时
	{
		pair<int, int> node_degree_1_index = node_degree_1.top();//取出栈顶结点坐标
		node_degree_1.pop();//栈顶元素出栈
		for (int i = 0; i < 4; i++)//遍历4个方向
		{
			pair<int, int> around = { node_degree_1_index.first + orientation[i].first,node_degree_1_index.second + orientation[i].second };//当前方向处的坐标
			if (!usednode.count(around) && wallindex.count(around))//若当前方向处的结点是墙且未遍历过
			{
				nodeindex_nodedegree[around]--;//当前方向出的结点的度减一
				if (nodeindex_nodedegree[around] <= 1)//若此时该结点的度小于等于1
				{
					node_degree_1.emplace(around);//把该结点压栈
					usednode.insert(around);//将该结点标记为遍历过
					degree_1_node_acount++;//度小于等于1的结点数量加一
				}
			}
		}
	}
	iter = wallindex.begin();
	while (iter != wallindex.end())//重遍历wallindex集合，求出可组成围墙的结点，并存入circlenode集合
	{
		if (!usednode.count(*iter))
		{
			circlenode.insert(*iter);
		}
		iter++;
	}
	return all_node_acount != degree_1_node_acount;//若经过计算总结点数不等于度小于等于1的结点数，则说明有可组成围墙的部分，返回true，否则返回false
}

bool whetherincircle(set<pair<int, int>> wall, set<pair<int, int>> box, set<pair<int, int>> target, Character c, set<pair<int, int>>& circlenode)//是否所有物件都在墙体围成的环内
{
	set<pair<int, int>>::iterator biter = box.begin();//创建一个set<pair<int, int>>迭代器，并初始化为box集合的起始位置指针
	set<pair<int, int>>::iterator titer = target.begin();//创建一个set<pair<int, int>>迭代器，并初始化为target集合的起始位置指针
	int count = 0;//记录某物件上下左右四个方向的墙体数量
	while (biter != box.end())//遍历box集合，判断每个箱子上下左右四个方向的围墙结点的数量，若该数量为4，则代表当前遍历的箱子在围墙之内，满足规范性；否则不满足规范性，直接返回false
	{
		int bx = biter->first;
		int by = biter->second;
		count = 0;
		for (int i = by; i >= 1; i--)
		{
			if (wall.count({ bx,i }) && circlenode.count({ bx,i }))
			{
				count++;
				break;
			}
		}
		for (int i = by; i <= 25; i++)
		{
			if (wall.count({ bx,i }) && circlenode.count({ bx,i }))
			{
				count++;
				break;
			}
		}
		for (int i = bx; i >= 1; i--)
		{
			if (wall.count({ i,by }) && circlenode.count({ i,by }))
			{
				count++;
				break;
			}
		}
		for (int i = bx; i <= 14; i++)
		{
			if (wall.count({ i,by }) && circlenode.count({ i,by }))
			{
				count++;
				break;
			}
		}
		if (count < 4)return false;
		biter++;
	}
	while (titer != target.end())//遍历target集合，判断每个目标点位上下左右四个方向的围墙结点的数量，若该数量为4，则代表当前遍历的目标点位在围墙之内，满足规范性；否则不满足规范性，直接返回false
	{
		int tx = titer->first;
		int ty = titer->second;
		count = 0;
		for (int i = ty; i >= 1; i--)
		{
			if (wall.count({ tx,i }) && circlenode.count({ tx,i }))
			{
				count++;
				break;
			}
		}
		for (int i = ty; i <= 25; i++)
		{
			if (wall.count({ tx,i }) && circlenode.count({ tx,i }))
			{
				count++;
				break;
			}
		}
		for (int i = tx; i >= 1; i--)
		{
			if (wall.count({ i,ty }) && circlenode.count({ i,ty }))
			{
				count++;
				break;
			}
		}
		for (int i = tx; i <= 14; i++)
		{
			if (wall.count({ i,ty }) && circlenode.count({ i,ty }))
			{
				count++;
				break;
			}
		}
		if (count < 4)return false;
		titer++;
	}
	//判断角色上下左右四个方向的围墙结点的数量，若该数量为4，则代表当前遍历的角色在围墙之内，满足规范性；否则不满足规范性，直接返回false
	count = 0;
	int cx = c.getcharacterx();
	int cy = c.getcharactery();
	for (int i = cy - 1; i >= 1; i--)
	{
		if (wall.count({ cx,i }) && circlenode.count({ cx,i }))
		{
			count++;
			break;
		}
	}
	for (int i = cy + 1; i <= 25; i++)
	{
		if (wall.count({ cx,i }) && circlenode.count({ cx,i }))
		{
			count++;
			break;
		}
	}
	for (int i = cx - 1; i >= 1; i--)
	{
		if (wall.count({ i,cy }) && circlenode.count({ i,cy }))
		{
			count++;
			break;
		}
	}
	for (int i = cx + 1; i <= 14; i++)
	{
		if (wall.count({ i,cy }) && circlenode.count({ i,cy }))
		{
			count++;
			break;
		}
	}
	if (count < 4)return false;
	return true;
}

void reports_createcustomlevel_errors(int errornum)//自定义关卡报错
{
	int x = 10;//文本起始的在窗口上的横坐标
	int y = 16 * 40 + 10;//文本起始的在窗口上的纵坐标
	int delta = 20;//相邻文本间的距离
	settextstyle(20, 0, "宋体");//设置字体样式
	setbkcolor(WHITE);//设置背景颜色为白色
	settextcolor(RED);//设置文本颜色为红色
	switch (errornum)//对32种不同情况报错
	{
	case 0:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "围墙最大长度不够");
		outtextxy(x, y + 3 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 4 * delta, "无角色");
		break;
	case 1:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "围墙最大长度不够");
		outtextxy(x, y + 3 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 2:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "围墙最大长度不够");
		outtextxy(x, y + 3 * delta, "无角色");
		break;
	case 3:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "围墙最大长度不够");
		break;
	case 4:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 3 * delta, "无角色");
		break;
	case 5:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 6:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 7:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大宽度不够");
		break;
	case 8:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 3 * delta, "无角色");
		break;
	case 9:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 10:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 11:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		break;
	case 12:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 13:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 14:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		outtextxy(x, y + 1 * delta, "无角色");
		break;
	case 15:
		outtextxy(x, y, "围墙不封闭或不是所有物件都在围墙内");
		break;
	case 16:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 3 * delta, "无角色");
		break;
	case 17:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 18:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 19:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "围墙最大长度不够");
		break;
	case 20:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 21:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 22:
		outtextxy(x, y, "围墙最大宽度不够");
		outtextxy(x, y + 1 * delta, "无角色");
		break;
	case 23:
		outtextxy(x, y, "围墙最大宽度不够");
		break;
	case 24:
		outtextxy(x, y, "围墙最大长度不够");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 2 * delta, "无角色");
		break;
	case 25:
		outtextxy(x, y, "围墙最大长度不够");
		outtextxy(x, y + 1 * delta, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 26:
		outtextxy(x, y, "围墙最大长度不够");
		outtextxy(x, y + 1 * delta, "无角色");
		break;
	case 27:
		outtextxy(x, y, "围墙最大长度不够");
		break;
	case 28:
		outtextxy(x, y, "箱子数不等于目标数或无箱子或无目标");
		outtextxy(x, y + 1 * delta, "无角色");
		break;
	case 29:
		outtextxy(x, y, "箱子数不等于目标数或无箱子或无目标");
		break;
	case 30:
		outtextxy(x, y, "无角色");
		break;
	case 31:
		break;
	}
	//将文本样式、背景颜色、文本颜色恢复为原来的设置
	settextstyle(40, 0, "宋体");
	setbkcolor(RGB(182, 229, 29));
	settextcolor(BLACK);
}

string encode_createcustomlevel(map<int, set<pair<int, int>>>& wbt, Character& c, int mintop, int minleft, int reachedboxnum)//对自定义的关卡信息进行编码
{
	set<pair<int, int>>::iterator witer = wbt[0].begin();//创建一个set<pair<int, int>>迭代器，初始化为wbt[0]集合的起始位置指针，用于遍历墙坐标
	set<pair<int, int>>::iterator biter = wbt[1].begin();//创建一个set<pair<int, int>>迭代器，初始化为wbt[1]集合的起始位置指针，用于遍历箱子坐标
	set<pair<int, int>>::iterator titer = wbt[2].begin();//创建一个set<pair<int, int>>迭代器，初始化为wbt[2]集合的起始位置指针，用于遍历目标点位坐标
	vector<pair<int, int>> windex;//存储墙坐标
	vector<pair<int, int>> bindex;//存储箱子坐标
	vector<pair<int, int>> tindex;//存储目标点位坐标
	string ans = to_string(reachedboxnum) + ",";//最终返回的编码，初始化时将到达目标点位的箱子数转为字符串传给该变量
	//将所有物件向左上角调整
	c.setcharacter(c.getcharacterx() - mintop, c.getcharactery() - minleft, 4);
	while (witer != wbt[0].end())
	{
		pair<int, int> wi = { witer->first - mintop,witer->second - minleft };
		windex.push_back(wi);
		witer++;
	}
	while (biter != wbt[1].end())
	{
		pair<int, int> bi = { biter->first - mintop,biter->second - minleft };
		bindex.push_back(bi);
		biter++;
	}
	while (titer != wbt[2].end())
	{
		pair<int, int> ti = { titer->first - mintop,titer->second - minleft };
		tindex.push_back(ti);
		titer++;
	}
	int bsize = bindex.size();//箱子数量
	int tsize = tindex.size();//目标点位数量
	int wsize = windex.size();//墙数量
	ans += to_string(bsize) + ",";//将箱子数量传给编码
	ans += to_string(tsize) + ",";//将目标点位数量传给编码
	ans += to_string(wsize) + ",";//将墙数量传给编码
	ans += to_string(c.getcharacterx()) + ",";//将角色在地图上的横坐标传给编码
	ans += to_string(c.getcharactery()) + ",";//将角色在地图上的纵坐标传给编码
	ans += to_string(c.getcharactero()) + ",";//将角色朝向传给编码
	for (int i = 0; i < bsize; i++)//将所有箱子的坐标信息传给编码
	{
		int x = bindex[i].first;
		int y = bindex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	for (int i = 0; i < tsize; i++)//将所有目标点位的坐标信息传给编码
	{
		int x = tindex[i].first;
		int y = tindex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	for (int i = 0; i < wsize; i++)//将所有墙的坐标信息传给编码
	{
		int x = windex[i].first;
		int y = windex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	return ans;//返回编码
}

int Mousemessage(ExMessage* msg)//选关卡
{
	int c = msg->x / 100;//鼠标处于关卡矩阵第c列（从0开始）
	int r = msg->y / 100;//鼠标处于关卡矩阵第r行（从0开始）
	return r * 5 + c;//返回关卡编号
}

int Mousemessage_customlevel(ExMessage* msg)//选自定义关卡
{
	int which = msg->y / 30;//鼠标处于关卡列表第which列（从0开始）
	return which;
}

void PlayGame(Gamelevel& ln, string user_name)
{
	char ch = NULL;//用于存键盘按键信息
	bool ifbreak = false;//用于判断是否点到回退按钮
	ln.DrawLevel();//绘制关卡界面
	while (!ln.win())//进入游玩游戏关卡循环，当判断为胜利时退出循环
	{
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))//捕获鼠标信息
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN://按下左键
				int y = msg.x / 40;//鼠标在游戏关卡地图上的纵坐标
				int x = msg.y / 40;//鼠标在游戏关卡地图上的横坐标
				if (x == ln.row && y == 0)//回退
				{
					ln.CloseLevel();//关闭游戏关卡界面
					OpenSelectLevelInterface();//打开普通关卡选关界面
					DrawSelectLevelInterface();//绘制普通关卡选关界面
					ifbreak = true;//用于判断是否点到回退按钮的变量置为真
					break;
				};
				if (x == ln.row && y == 1)//重新开始
				{
					ln.DeCode(0);//解码初始编码
					ln.score = ln.row * ln.col * 5 * 5;//重置游戏关卡分数
					ln.SetAllOnMap();//将所有物件放到地图上
					ln.DrawLevel();//绘制游戏关卡界面
					break;
				};
				if (x == ln.row && y == 2)//存档
				{
					string gamelevelname = "GameLevel\\" + ln.gamename + ".dat";//存储存档编码的文件路径
					string gamelevelscore = "GameLevel\\" + ln.gamename + "_score.dat";//存储分数的文件路径
					ofstream fout(gamelevelname, ios::out);//创建一个文件为gamelevelname的文件输出流对象
					ofstream scorefout(gamelevelscore, ios::out);//创建一个文件为gamelevelscore的文件输出流对象
					ln.savedcode = "";//初始化关卡存档编码为空
					int rb = ln.reachedboxes;//达到目标点位的箱子数
					int b = ln.boxnum;//箱子数
					int t = ln.targetnum;//目标点位数
					int w = ln.wallnum;//墙体数
					//编码，并存入ln.savedcode
					ln.savedcode += to_string(rb);
					ln.savedcode += ",";
					ln.savedcode += to_string(b);
					ln.savedcode += ",";
					ln.savedcode += to_string(t);
					ln.savedcode += ",";
					ln.savedcode += to_string(w);
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharacterx());
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharactery());
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharactero());
					ln.savedcode += ",";
					for (int i = 0; i < b; i++)ln.savedcode += (to_string(ln.box[i].getboxx()) + "," + to_string(ln.box[i].getboxy()) + ",");
					for (int i = 0; i < t; i++)ln.savedcode += (to_string(ln.target[i].gettargetx()) + "," + to_string(ln.target[i].gettargety()) + ",");
					for (int i = 0; i < w; i++)ln.savedcode += (to_string(ln.wall[i].getwallx()) + "," + to_string(ln.wall[i].getwally()) + ",");
					fout << ln.savedcode;//将存档编码写入文件gamelevelname
					scorefout << ln.score;//将分数写入文件gamelevelscore
					break;
				};
				if (x == ln.row && y == 3)//读档
				{
					string gamelevelname = "GameLevel\\" + ln.gamename + ".dat";//存储存档编码的文件路径
					string gamelevelscore = "GameLevel\\" + ln.gamename + "_score.dat";//存储分数的文件路径
					ifstream fin(gamelevelname, ios::in);//创建一个文件为gamelevelname的文件输入流对象
					ifstream scorefin(gamelevelscore, ios::in);//创建一个文件为gamelevelscore的文件输入流对象
					string assist = "";//辅助字符串
					fin >> assist;//将存档编码取出，并存入辅助字符串assist中
					scorefin >> ln.score;//将得分取出，并存入关卡分数ln.score中
					if (ln.savedcode.size() == 0)ln.savedcode = assist;//若关卡存档编码为空，则将assist赋值给关卡存档编码
					if (ln.savedcode.size() == 0)break;//若关卡存档编码仍为空，则退出switch
					ln.DeCode(1);//对关卡存档编码进行解码
					ln.SetAllOnMap();//将所有物件放到地图上
					ln.DrawLevel();//重绘游戏关卡解面
					break;
				}
			}
			if (ifbreak)break;//若点到回退按钮，则退出游玩游戏关卡循环
		}
		if (_kbhit())//捕获按键信息
		{
			int sufchx = ln.character.getcharacterx();//获取移动前角色在地图上的横坐标
			int sufchy = ln.character.getcharactery();//获取移动前角色在地图上的纵坐标
			int sufdata = ln.gamemap.getmap0data(sufchx, sufchy);//获取移动前地图上角色位置处的数据
			ch = _getch();//键盘按键信息赋值给ch
			ln.character.characteroperate1(ch);//角色向指定方向移动
			ln.MoveCharactar(ch);//操作角色移动（判断是该保持位置不变还是该向后退一格），并改变需要改变的物件
			int nowchx = ln.character.getcharacterx();//获取移动后角色在地图上的横坐标
			int nowchy = ln.character.getcharactery();//获取移动后角色在地图上的纵坐标
			int nowdata = ln.gamemap.getmap0data(nowchx, nowchy);//获取移动后地图上角色位置处的数据
			int prechx = NULL, prechy = NULL;//角色移动后，角色面向方向前一格的在地图上的坐标
			switch(ch)
			{
			case 'a':
			case 'A':
				prechx = nowchx;
				prechy = nowchy - 1;
				break;
			case 'w':
			case 'W':
				prechx = nowchx - 1;
				prechy = nowchy;
				break;
			case 'd':
			case 'D':
				prechx = nowchx;
				prechy = nowchy + 1;
				break;
			case 's':
			case 'S':
				prechx = nowchx + 1;
				prechy = nowchy;
				break;
			}
			int predata = ln.gamemap.getmap0data(prechx, prechy);//获取移动后地图上角色面向方向前一格位置处的数据
			if (ch == 'a' || ch == 'A' || ch == 'w' || ch == 'W' || ch == 'd' || ch == 'D' || ch == 's' || ch == 'S')
			{
				ln.DrawChangedImage(prechx, prechy, predata, nowchx, nowchy, nowdata, sufchx, sufchy, sufdata);//改变需要改变的图片
			}
		}
	}
	if (!ifbreak)//若不是因为点到回退按钮而退出循环，则代表已赢得游戏
	{
		int finalscore = ln.score;//最终得分
		if (user_level_score[user_name].count(ln.gamename))//若用户user_name游玩过关卡ln.gamename
		{
			int prescore = stoi(user_level_score[user_name][ln.gamename]);//用户user_name游玩的关卡ln.gamename的原得分
			if (prescore > ln.score)//取当前的分和原得分的最大值
			{
				finalscore = prescore;
			}
		}
		user_level_score[user_name][ln.gamename] = to_string(finalscore);//更改用户user_name游玩的关卡ln.gamename的得分（最高得分）
		ofstream ulsfout("Users_Score\\" + user_name + ".dat", ios::app);//创建一个文件为"Users_Score\\" + user_name + ".dat"的文件输出流对象，写入方式为附加写入
		ulsfout << ln.gamename << " " << to_string(ln.score) << endl;//附加存入关卡名及得分
		Sleep(1000);//程序休眠1秒，让玩家反应过来自己赢了
		ln.CloseLevel();//关闭游戏关卡界面
		OpenSelectLevelInterface();//打开普通关卡选关界面
		DrawSelectLevelInterface();//绘制普通关卡选关界面
	}
}

void PlayCustomGame(Gamelevel& ln, string user_name)//游玩自定义关卡
{
	//与PlayGame(Gamelevel& ln, string user_name)函数大同小异，不再进行注释
	char ch = NULL;
	bool ifbreak = false;
	ln.DrawLevel();
	while (!ln.win())
	{
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				int y = msg.x / 40;
				int x = msg.y / 40;
				if (x == ln.row && y == 0)//回退
				{
					ln.CloseLevel();
					ifstream fin("CustomGameLevel\\level_acount.dat", ios::in);
					int acount;
					fin >> acount;
					OpenSelectCustomLevelInterface(acount);
					DrawSelectCustomLevelInterface(acount);
					ifbreak = true;
					break;
				};
				if (x == ln.row && y == 1)//重新开始
				{
					ln.DeCode(0);
					ln.score = ln.row * ln.col * 5 * 5;
					ln.SetAllOnMap();
					ln.DrawLevel();
					break;
				};
				if (x == ln.row && y == 2)//存档
				{
					string gamelevelname = "CustomGameLevel\\SavedCustomGameLevel\\" + ln.gamename + ".dat";
					string gamelevelscore = "CustomGameLevel\\SavedCustomGameLevel\\" + ln.gamename + "_score.dat";
					ofstream fout(gamelevelname, ios::out);
					ofstream scorefout(gamelevelscore, ios::out);
					ln.savedcode = "";
					int rb = ln.reachedboxes;
					int b = ln.boxnum;
					int t = ln.targetnum;
					int w = ln.wallnum;
					ln.savedcode += to_string(rb);
					ln.savedcode += ",";
					ln.savedcode += to_string(b);
					ln.savedcode += ",";
					ln.savedcode += to_string(t);
					ln.savedcode += ",";
					ln.savedcode += to_string(w);
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharacterx());
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharactery());
					ln.savedcode += ",";
					ln.savedcode += to_string(ln.character.getcharactero());
					ln.savedcode += ",";
					for (int i = 0; i < b; i++)ln.savedcode += (to_string(ln.box[i].getboxx()) + "," + to_string(ln.box[i].getboxy()) + ",");
					for (int i = 0; i < t; i++)ln.savedcode += (to_string(ln.target[i].gettargetx()) + "," + to_string(ln.target[i].gettargety()) + ",");
					for (int i = 0; i < w; i++)ln.savedcode += (to_string(ln.wall[i].getwallx()) + "," + to_string(ln.wall[i].getwally()) + ",");
					fout << ln.savedcode;
					scorefout << ln.score;
					break;
				};
				if (x == ln.row && y == 3)//读档
				{
					string gamelevelname = "CustomGameLevel\\SavedCustomGameLevel\\" + ln.gamename + ".dat";
					string gamelevelscore = "CustomGameLevel\\SavedCustomGameLevel\\" + ln.gamename + "_score.dat";
					ifstream fin(gamelevelname, ios::in);
					ifstream scorefin(gamelevelscore, ios::in);
					string assist = "";
					fin >> assist;
					scorefin >> ln.score;
					if (ln.savedcode.size() == 0)ln.savedcode = assist;
					if (ln.savedcode.size() == 0)break;
					ln.DeCode(1);
					ln.SetAllOnMap();
					ln.DrawLevel();
					break;
				}
			}
			if (ifbreak)break;
		}
		if (_kbhit())
		{
			int sufchx = ln.character.getcharacterx();
			int sufchy = ln.character.getcharactery();
			int sufdata = ln.gamemap.getmap0data(sufchx, sufchy);
			ch = _getch();
			ln.character.characteroperate1(ch);
			ln.MoveCharactar(ch);
			int nowchx = ln.character.getcharacterx();
			int nowchy = ln.character.getcharactery();
			int nowdata = ln.gamemap.getmap0data(nowchx, nowchy);
			int prechx = NULL, prechy = NULL;
			switch (ch)
			{
			case 'a':
			case 'A':
				prechx = nowchx;
				prechy = nowchy - 1;
				break;
			case 'w':
			case 'W':
				prechx = nowchx - 1;
				prechy = nowchy;
				break;
			case 'd':
			case 'D':
				prechx = nowchx;
				prechy = nowchy + 1;
				break;
			case 's':
			case 'S':
				prechx = nowchx + 1;
				prechy = nowchy;
				break;
			}
			int predata = ln.gamemap.getmap0data(prechx, prechy);
			if (ch == 'a' || ch == 'A' || ch == 'w' || ch == 'W' || ch == 'd' || ch == 'D' || ch == 's' || ch == 'S')
			{
				ln.DrawChangedImage(prechx, prechy, predata, nowchx, nowchy, nowdata, sufchx, sufchy, sufdata);
			}
		}
	}
	if (!ifbreak)
	{
		int finalscore = ln.score;
		if (user_level_score[user_name].count(ln.gamename))
		{
			int prescore = stoi(user_level_score[user_name][ln.gamename]);
			if (prescore > ln.score)
			{
				finalscore = prescore;
			}
		}
		user_level_score[user_name][ln.gamename] = to_string(finalscore);
		ofstream ulsfout("Users_Score\\" + user_name + ".dat", ios::app);
		ulsfout << ln.gamename << " " << to_string(ln.score) << endl;
		Sleep(1000);
		ln.CloseLevel();
		ifstream fin("CustomGameLevel\\level_acount.dat", ios::in);
		int acount;
		fin >> acount;
		OpenSelectCustomLevelInterface(acount);
		DrawSelectCustomLevelInterface(acount);
	}
}

void allocation_encryption_key()//对密钥字符串进行加密分配
{
	set<char> usedletter;//已映射的字母
	int letterindex = 0;//26个字典序小写字母索引，初始化为0
	int n = PasswordKey.size();//密钥大小
	for (int i = 0; i < n; i++)//遍历密钥，使每个'a'+letterindex映射到第一次出现的字母上
	{
		if (!usedletter.count(PasswordKey[i]) && letterindex < 26)
		{
			usedletter.insert(PasswordKey[i]);
			encrypted_key['a' + letterindex] = PasswordKey[i];
			letterindex++;
		}
	}
	while (letterindex < 26)//将剩余的未映射的26个字典序小写字母映射到自己
	{
		encrypted_key['a' + letterindex] = 'a' + letterindex;
		letterindex++;
	}
}

string encrypt_password(string password)//给密码加密，并返回加密的密码
{
	string ans = "";//最终要返回的加密的密码，初始化为空
	int n = password.size();//密码大小
	for (int i = 0; i < n; i++)//遍历密码，只加密密码中的小写字母，其他字符不变
	{
		if (encrypted_key.count(password[i]))ans.push_back(encrypted_key[password[i]]);
		else ans.push_back(password[i]);
	}
	return ans;//返回加密后的密码
}

void Find_total_score()//求每个用户的总分
{
	map<string, map<string, string>>::iterator iter = user_level_score.begin();//创建一个迭代器，初始化为用户关卡分数哈希表的起始指针位置
	while (iter != user_level_score.end())//用迭代器遍历用户关卡分数哈希表
	{
		map<string, string>::iterator iter2 = user_level_score[iter->first].begin();//创建一个迭代器，初始化为关卡分数哈希表的起始指针位置
		int s = 0;//用于求总分，初始化为0
		while (iter2 != user_level_score[iter->first].end())//用迭代器遍历关卡分数哈希表
		{
			s += stoi(iter2->second);
			iter2++;
		}
		user_totalscore[iter->first] = to_string(s);//将总分存进用户总分哈希表中
		iter++;
	}
}

void Change_User_Level_Score()//更改某用户关卡分数
{
	set<string>::iterator iter = users_names.begin();//创建一个迭代器，初始化为用户名集合的起始指针位置
	while (iter != users_names.end())//用迭代器遍历用户名集合
	{
		user_level_score[*iter]["NULL"] = "0";//若某用户未玩过任何关卡，则这条语句可以保证他的总分为0
		string UserName = "Users_Score\\" + *iter + ".dat";//记录某用户的关卡分数文件的文件路径
		ifstream users_levels_score_fin(UserName);//创建一个文件为UserName的文件输入流对象
		string line = "";//用于存储文件流的输入信息
		while (getline(users_levels_score_fin, line))//读取文件UserName的每一行，并将读取到的信息存入line，字符串line一定被一个空格符分为两部分，空格前的部分为关卡名，空格后的部分为用户游玩该关卡的得分
		{
			string levelname = "";//用于存储line中的关卡名信息
			string score = "";//用于存储line中的得分信息
			int j = 0;//对line进行遍历的初始索引
			for (; j < line.size() && line[j] != ' '; j++)//求line中的关卡名
			{
				levelname.push_back(line[j]);
			}
			while (line[j] == ' ')j++;//跳过空格
			for (; j < line.size(); j++)//求line中的得分
			{
				score.push_back(line[j]);
			}
			if (user_level_score[*iter].count(levelname))//若用户已游玩过关卡levelname且已有得分
			{
				int prescore = 0;//原得分
				int nowscore = stoi(score);//现得分
				prescore = stoi(user_level_score[*iter][levelname]);//记录原得分
				user_level_score[*iter][levelname] = to_string(max(prescore, nowscore));//将原得分和现得分中的较大值存起来
				line = "";//将line变为空
				continue;
			}
			user_level_score[*iter][levelname] = score;//记录得分
			line = "";//将line变为空
		}
		iter++;
	}
}

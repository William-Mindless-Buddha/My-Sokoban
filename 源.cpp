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


IMAGE images_initialgameinterface[10];//��������Ϸ��ʼ�������ͼƬ

IMAGE images_selectlevelinterface[1];//��������Ϸ��ͨ�ؿ�ѡ�ؽ������ͼƬ

IMAGE images_level[17];//��������Ϸ�ؿ��е����ͼƬ

IMAGE images_createcustomlevel[8];//�������Զ��幦�ܽ�������ͼƬ

class Box
{
private:
	int boxx;//�����ڵ�ͼ�ϵĺ�����
	int boxy;//�����ڵ�ͼ�ϵ�������
public:
	void setbox(int x, int y);//���������ڵ�ͼ�ϵĺ�������
	int getboxx();//��ȡ�����ڵ�ͼ�ϵĺ�����
	int getboxy();//��ȡ�����ڵ�ͼ�ϵ�������
};

class Target
{
private:
	int targetx;//Ŀ���λ�ڵ�ͼ�ϵĺ�����
	int targety;//Ŀ���λ�ڵ�ͼ�ϵ�������
public:
	void settargetxy(int x, int y);//����Ŀ���λ�ڵ�ͼ�ϵĺ�������
	int gettargetx();//��ȡĿ���λ�ڵ�ͼ�ϵĺ�����
	int gettargety();//��ȡĿ���λ�ڵ�ͼ�ϵ�������
};

class Wall
{
private:
	int wallx;//ǽ�ڵ�ͼ�ϵĺ�����
	int wally;//ǽ�ڵ�ͼ�ϵ�������
public:
	void setwallxy(int x, int y);//����ǽ�ڵ�ͼ�ϵĺ�������
	int getwallx();//��ȡǽ�ڵ�ͼ�ϵĺ�����
	int getwally();//��ȡǽ�ڵ�ͼ�ϵ�������
};

class Map
{
private:
	int Row = NULL;//��ͼ����
	int Col = NULL;//��ͼ����
	vector<vector<int>> map0;//��ͼ��ά����
public:
	void setmaprc(int r, int c);//���õ�ͼ������ͬʱ��ʼ����ͼ
	int getmapr();//��ȡ��ͼ����
	int getmapc();//��ȡ��ͼ����
	int getmap0data(int x, int y);//��ȡ��ͼ�ض������ϵ���ֵ
	void showmap();//��ӡ��ͼ
	void SetOnMap(int x,int y,int data);//��ĳ�������ڵ�ͼ��
};

class Character
{
private:
	int characterx0;//��ɫ�ڵ�ͼ�ϵĺ�����
	int charactery0;//��ɫ�ڵ�ͼ�ϵ�������
	int Orientation;//��ɫ����
public:
	void setcharacter(int x, int y, int o);//���ý�ɫ������ݣ��ᡢ�����꼰����
	int getcharacterx();//��ȡ��ɫ�ڵ�ͼ�ϵĺ�����
	int getcharactery();//��ȡ��ɫ�ڵ�ͼ�ϵ�������
	int getcharactero();//��ȡ��ɫ����
	void characteroperate0(char ch);//������ɫ������ƶ�
	void characteroperate1(char ch);//������ɫ���ƶ�
};

class Gamelevel
{
public:
	int row;//��ǰ�ؿ��ĵ�ͼ����
	int col;//��ǰ�ؿ��ĵ�ͼ����
	int boxnum;//��ǰ�ؿ���������
	int targetnum;//��ǰ�ؿ���Ŀ���λ��
	int wallnum;//��ǰ�ؿ���ǽ��
	int reachedboxes;//��ǰ�ؿ��ﵽĿ���λ��������
	vector<Box> box;//���ڴ浱ǰ�ؿ�ÿ��������Ϣ������
	map<pair<int, int>, int> boxindex2whichbox;//����������ӳ�䵽�ڼ�������
	map<int, pair<int, int>> whichbox2boxindex;//�ӵڼ�������ӳ�䵽��������
	vector<Target> target;//���ڴ浱ǰ�ؿ�ÿ��Ŀ���λ��Ϣ������
	set<pair<int, int>> target_index;//���ڴ�Ŀ���λ����
	vector<Wall> wall; //���ڴ浱ǰ�ؿ�ÿ��ǽ��Ϣ������
	Map gamemap;//��ǰ�ؿ��ĵ�ͼ
	Character character;//��ǰ�ؿ��Ľ�ɫ
	string encode;//����Ϸ�ؿ���Ϣ�ı��룬����������ּ��ö��Ÿ�����ǰ7�����ֱַ�Ϊreachedbox��box��target��wall��������characterx��charactery��charactero��֮�������ǰbox��Ϊbox���꣬�м�target��Ϊtarget���꣬���wall��Ϊǽ����
	string savedcode;//�������ͬ�ϣ���ʾ�浵�ı���
	string gamename;//��Ϸ�ؿ���
	int score;//��Ϸ�ؿ��÷�
	Gamelevel(int r, int c, string code, string name);//��ʼ���ؿ�
	void DeCode(int kind);//�Թؿ���Ϣ�ַ������н��룬kindΪ0��ʾ��ʼ���룬kindΪ1��ʾ�浵�ı���
	void MoveCharactar(char ch);//�ƶ�һ����ɫ
	void SetBoxOnMap(int i);//�����������ڵ�ͼ��
	void SetTargetOnMap(int i);//��Ŀ���λ�����ڵ�ͼ��
	void SetWallOnMap(int i);//��ǽ�����ڵ�ͼ��
	//void SetCharactarOnMap();//����ɫ�����ڵ�ͼ��
	void SetAllOnMap();//��������������ڵ�ͼ��
	int whichbox(int x, int y);//�ж�ָ��λ�õ������ǵڼ�������
	int win();//�ж�ĳ���Ƿ�Ӯ
	void OpenLevel();//�򿪹ؿ�����
	void CloseLevel();//�رչؿ�����
	void DrawLevel();//���ƹؿ�
	void DrawChangedImage(int prex, int prey, int predata, int nowx, int nowy, int nowdata, int sufx, int sufy, int sufdata);//���ƽ�ɫ�ƶ���ͼƬ�ı�Ĳ���
};

map<string, string> users_accountnumber2password;//�û��˺ż����ܺ������

map<string, string> users_accountnumber2name;//�û��˺ż��û���

set<string> users_names;//�û�������

map<string, string> user_totalscore;//�û���ӳ�䵽���û����ܵ÷�

map<string, map<string, string>> user_level_score;//�û���ӳ�䵽���û�������Ĺؿ��Ĺؿ������ùؿ���Ӧ�ĵ÷�

string PasswordKey = "thequickbrownfoxjumpsoverthelazydog";//�����û��������Կ

map<char, char> encrypted_key;//������Կ��ӳ���ϵ


void LoadResource_InitialGameInterface();//������Ϸ��ʼ����ͼƬ

void LoadResource_SelectLevelInterface();//����ѡ�ؽ���ͼƬ

void LoadResource_Level();//���عؿ�ͼƬ

void LoadResource_CreateCustomLevel();//���عؿ��Զ������ͼƬ

void OpenInitialGameInterface();//����Ϸ��ʼ����

void OpenSelectLevelInterface();//��ѡ�ؽ���

void OpenNamingCustomLevel();//���Զ���ؿ���������

void OpenCreateCustomLevel();//�򿪹ؿ��Զ������

void OpenSelectCustomLevelInterface(int c);//���Զ���ؿ�ѡ�ؽ���

void OpenLoginInputInterface();//�򿪵�¼��Ϣ���봰��

void OpenRegisterInputInterface();//��ע����Ϣ���봰��

void OpenTheRankingList();//�����а�ҳ��

void CloseInitialGameInterface();//�ر���Ϸ��ʼ����

void CloseSelectLevelInterface();//�ر�ѡ�ؽ���

void CloseNamingCustomLevel();//�ر��Զ���ؿ���������

void CloseSelectCustomLevelInterface();//�ر��Զ���ؿ�ѡ�ؽ���

void CloseLoginInputInterface();//�رյ�¼�������

void CloseRegisterInputInterface();//�ر�ע���������

void CloseTheRankingList();//�ر����а�ҳ��

void DrawInitialGameInterface0();//������Ϸ��ʼ���棬��ťΪ��ʼ��Ϸ�����а�

void DrawInitialGameInterface1();//������Ϸ��ʼ���棬��ťΪ��ͨ�ؿ����Զ���ؿ�������

void DrawInitialGameInterface2();//�����Զ���ؿ���ʼ���棬��ťΪ�½��ؿ���ѡ��ؿ�������

void DrawInitialGameInterface3();//���Ƶ�¼��ע����棬��ťΪ��¼��ע�ᡢ����

void DrawSelectLevelInterface();//����ѡ�ؽ���

string DrawNamingCustomLevel_and_ReturnName(bool& ifcancel);//�����Զ���ؿ��������沢�����ļ���

void DrawCreateCustomLevel_and_CreateCustomLevel(map<int, set<pair<int, int>>>& w_b_t, Character& c, int& r, string levelname);//���ƹؿ��Զ�����沢�����Զ��壬w_b_t����ǽ�����ӡ�Ŀ���λ����Ϣ��c�����ɫ��Ϣ��r����ﵽĿ���λ����������

void DrawSelectCustomLevelInterface(int c);//�����Զ���ؿ�ѡ�ؽ���

vector<string> DrawLoginInputInterface(bool& ifcancel);//���Ƶ�¼��������棬�������˻������������ֵ

vector<string> DrawRegisterInputInterface(bool& ifcancel);//����ע����Ϣ������棬������ע����Ϣ

void DrawTheRankingList();//�������а�ҳ��

bool whethercircle(set<pair<int, int>> wallindex, set<pair<int, int>>& circlenode);//�ж��Զ���ؿ��е�ǽ���Ƿ��Χ��һ����

bool whetherincircle(set<pair<int, int>> wall, set<pair<int, int>> box, set<pair<int, int>> target, Character c, set<pair<int, int>>& circlenode);//�Ƿ������������ǽ��Χ�ɵĻ���

void reports_createcustomlevel_errors(int errornum);//�Զ���ؿ�����

string encode_createcustomlevel(map<int, set<pair<int, int>>>& wbt, Character& c, int mintop, int minleft, int reachedboxnum);//���Զ���Ĺؿ���Ϣ���б���

int Mousemessage(ExMessage* msg);//ѡ�ؿ�

int Mousemessage_customlevel(ExMessage* msg);//ѡ�Զ���ؿ�

void PlayGame(Gamelevel& ln, string username);//����ؿ�

void PlayCustomGame(Gamelevel& ln, string username);//�����Զ���ؿ�

void allocation_encryption_key();//����Կ�ַ������м��ܷ���

string encrypt_password(string password);//��������ܣ������ؼ��ܵ�����

void Find_total_score();//��ÿ���û����ܷ�

void Change_User_Level_Score();//����ĳ�û��ؿ�����


int main()
{
	LoadResource_InitialGameInterface();//������Ϸ��ʼ����ͼƬ
	LoadResource_SelectLevelInterface();//������ͨ�ؿ�ѡ�ؽ���ͼƬ
	LoadResource_Level();//������Ϸ�ؿ�ͼƬ
	LoadResource_CreateCustomLevel();//�����Զ��幦�ܽ���ͼƬ
	allocation_encryption_key();//����Կ���м��ܷ��䣬�����еĸ�����ĸ����ĳ����ӳ�䵽������ĸ�ϣ������encrypted_key
	ifstream user_count_fin("Users\\user_count.dat", ios::in);//����һ���ļ�ΪUsers\\user_count.dat���ļ��������������ڶԳ�����֮ǰע����û���
	int user_acount = 0;//��ʼ���û���Ϊ0
	user_count_fin >> user_acount;//���ļ�������������ע����û���
	for (int i = 0; i < user_acount; i++)//ö���û���ţ������ļ����ķ�ʽ������ע��������û���Ϣ���û������˺š����룩��������Щ��Ϣ���ڳ�ʼ��users_accountnumber2password��users_accountnumber2name��users_names
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
	Change_User_Level_Score();//���û�������ĸ��ؿ��÷ִ���user_level_score
	Find_total_score();//���û��ִܷ���user_totalscore
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
	OpenInitialGameInterface();//����Ϸ��ʼ����
	DrawInitialGameInterface0();//������Ϸ��ʼ���棬��ťΪ����ʼ��Ϸ�����а�
	while (1)//������Ϸ��ʼ���棨��ťΪ����ʼ��Ϸ�����а�ѭ��
	{
		ExMessage msg1;
		if (peekmessage(&msg1, EM_MOUSE))//���������Ϣ
		{
			switch (msg1.message)
			{
			case WM_LBUTTONDOWN://�������
				int x1 = msg1.x;//��ǰ����ڴ����еĺ�����
				int y1 = msg1.y;//��ǰ����ڴ����е�������
				if (x1 >= 150 && x1 <= 350 && y1 >= 144 && y1 <= 180)//�㵽��ʼ��Ϸ
				{
					DrawInitialGameInterface3();//������Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
					while (1)//������Ϸ��ʼ���棨��ťΪ����¼��ע�ᡢ���أ�ѭ��
					{
						ExMessage msg4;
						bool ifback4 = false;//�����ж��Ƿ�㵽����
						if (peekmessage(&msg4, EM_MOUSE))//���������Ϣ
						{
							switch (msg4.message)
							{
							case WM_LBUTTONDOWN://�������
								int x4 = msg4.x;//��ǰ����ڴ����еĺ�����
								int y4 = msg4.y;//��ǰ����ڴ����е�������
								if (x4 >= 150 && x4 <= 350 && y4 >= 144 && y4 <= 180)//�㵽��¼
								{
									CloseInitialGameInterface();//�ر���Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
									OpenLoginInputInterface();//�򿪵�¼��Ϣ�������
									bool login_ifcancel = false;//�����ж��Ƿ�㵽ȡ��
									vector<string> user = DrawLoginInputInterface(login_ifcancel);//���Ƶ�¼��Ϣ������棬������ɺ󷵻ص�¼�û���Ϣ
									CloseLoginInputInterface();//�رյ�¼��Ϣ�������
									OpenInitialGameInterface();//����Ϸ��ʼ����
									if (login_ifcancel)//������Ϊ�㵽ȡ���Żص���Ϸ��ʼ����
									{
										DrawInitialGameInterface3();//������Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
										break;//�ص���Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
									}
									DrawInitialGameInterface1();//������Ϸ��ʼ���棬��ťΪ����ͨ�ؿ����Զ���ؿ�������
									while (1)//������Ϸ��ʼ���棨��ťΪ����ͨ�ؿ����Զ���ؿ������أ�ѭ��
									{
										ExMessage msg2;
										bool ifback = false;//�����ж��Ƿ�㵽����
										if (peekmessage(&msg2, EM_MOUSE))//���������Ϣ
										{
											switch (msg2.message)
											{
											case WM_LBUTTONDOWN://�������
												int x2 = msg2.x;//��ǰ����ڴ����еĺ�����
												int y2 = msg2.y;//��ǰ����ڴ����е�������
												if (x2 >= 150 && x2 <= 350 && y2 >= 144 && y2 <= 180)//�������ͨ�ؿ�
												{
													CloseInitialGameInterface();//�ر���Ϸ��ʼ���棬��ťΪ����ͨ�ؿ����Զ���ؿ�������
													OpenSelectLevelInterface();//����ͨ�ؿ�ѡ�ؽ���
													DrawSelectLevelInterface();//������ͨ�ؿ�ѡ�ؽ���
													while (1)//������ͨ�ؿ�ѡ�ؽ���ѭ��
													{
														ExMessage msg;
														bool ifbreak = false;//�����ж��Ƿ�㵽����
														if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
														{
															switch (msg.message)
															{
															case WM_LBUTTONDOWN://�������
																CloseSelectLevelInterface();//�ر���ͨ�ؿ�ѡ�ؽ���
																int ln = Mousemessage(&msg);//����ѡ�ؿ����
																//��ͬ��ln���벻ͬ��if����飬Ȼ�󴴽���Ӧ�Ĺؿ����󡢴���Ϸ�ؿ����桢��������ؿ�������������
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
																if (msg.y >= 400 && msg.y <= 450)//�㵽����
																{
																	OpenInitialGameInterface();//����Ϸ��ʼ����
																	DrawInitialGameInterface1();//������Ϸ��ʼ���棬��ťΪ����ͨ�ؿ����Զ���ؿ�������
																	ifbreak = true; //�����ж��Ƿ�㵽���صı�����Ϊ��
																};
																break;
															}
														}
														if (ifbreak)break;//���㵽���أ����˳���ͨ�ؿ�ѡ�ؽ���ѭ��
													};
													break;
												};
												if (x2 >= 150 && x2 <= 350 && y2 >= 216 && y2 <= 252)//�㵽�Զ���ؿ�
												{
													DrawInitialGameInterface2();//������Ϸ��ʼ���棬��ťΪ���½��ؿ���ѡ��ؿ�������
													while (1)//������Ϸ��ʼ���棨��ťΪ���½��ؿ���ѡ��ؿ������أ�ѭ��
													{
														ExMessage msg3;
														bool ifback2 = false;//�����ж��Ƿ�㵽����
														if (peekmessage(&msg3, EM_MOUSE))//���������Ϣ
														{
															switch (msg3.message)
															{
															case WM_LBUTTONDOWN://�������
																int x3 = msg3.x;//��ǰ����ڴ����еĺ�����
																int y3 = msg3.y;//��ǰ����ڴ����е�������
																ifstream levelacountfin("CustomGameLevel\\level_acount.dat", ios::in);//����һ���ļ�ΪCustomGameLevel\\level_acount.dat�����������������������Զ���Ĺؿ�����
																int levelacount = 0;//���Զ���Ĺؿ�������ʼ��Ϊ0
																levelacountfin >> levelacount;//�������������ȡ���Զ���Ĺؿ�����������levelacount
																if (x3 >= 150 && x3 <= 350 && y3 >= 144 && y3 <= 180)//�㵽�½��ؿ�
																{
																	CloseInitialGameInterface();//�ر���Ϸ��ʼ���棬��ťΪ���½��ؿ���ѡ��ؿ�������
																	OpenNamingCustomLevel();//���Զ���ؿ���������
																	bool custom_ifcancel = false;//�����ж��Ƿ�㵽ȡ��
																	string customlevelname = DrawNamingCustomLevel_and_ReturnName(custom_ifcancel);//�����Զ���ؿ���������棬������ɺ󷵻��Զ���ؿ���
																	CloseNamingCustomLevel();//�ر��Զ���ؿ���������
																	if (custom_ifcancel)//������Ϊ�㵽ȡ���Żص���Ϸ��ʼ����
																	{
																		OpenInitialGameInterface();//����Ϸ��ʼ����
																		DrawInitialGameInterface2();//������Ϸ��ʼ���棬��ťΪ���½��ؿ���ѡ��ؿ�������
																		break;
																	}
																	map<int, set<pair<int, int>>> wall_box_target;//ǽ�����ӡ�Ŀ���λ������������꼯�Ϲ�ϣ��
																	Character assistcharacter;//������ɫ
																	int reachedboxacount = 0;//�ﵽĿ���λ����������
																	OpenCreateCustomLevel();//���Զ���ؿ����ܽ���
																	DrawCreateCustomLevel_and_CreateCustomLevel(wall_box_target, assistcharacter, reachedboxacount, customlevelname);//�����Զ���ؿ����ܽ��棬���Զ���ؿ��������ݴ��봫��Ķ�Ӧ������
																	string levelnum = "CustomGameLevel\\" + to_string(levelacount) + ".dat";//�����Զ���Ĺؿ�����תΪһ���ļ�·�����ļ�����Ϊ���Զ���Ĺؿ�����������ǰҪ�½����Զ���ؿ��ı��
																	ofstream customlevelnamefout(levelnum, ios::out);//����һ���ļ�Ϊlevelnum���ļ����������
																	customlevelnamefout << customlevelname;//��֮ǰ����Ĺؿ���д���ļ�levelnum��
																	levelacount++;//���Զ���Ĺؿ�������һ��Ҳ������һ���Զ���ؿ��ı��
																	ofstream levelacountfout("CustomGameLevel\\level_acount.dat", ios::out);//����һ���ļ�ΪCustomGameLevel\\level_acount.dat���ļ����������
																	levelacountfout << levelacount;//���µ����Զ���Ĺؿ�����д���ļ�CustomGameLevel\\level_acount.dat��
																	OpenInitialGameInterface();//����Ϸ��ʼ����
																	DrawInitialGameInterface2();//������Ϸ��ʼ���棬��ťΪ���½��ؿ���ѡ��ؿ�������
																	break;
																};
																if (x3 >= 150 && x3 <= 350 && y3 >= 216 && y3 <= 252)//�㵽ѡ��ؿ�
																{
																	ifstream fin("CustomGameLevel\\level_acount.dat", ios::in);//����һ���ļ�ΪCustomGameLevel\\level_acount.dat���ļ�����������
																	int acount = 0;//���Զ���Ĺؿ�������ʼ��Ϊ0
																	fin >> acount;//��ȡ���Զ���Ĺؿ�����
																	OpenSelectCustomLevelInterface(acount);//���Զ���ؿ�ѡ�����
																	DrawSelectCustomLevelInterface(acount);//�����Զ���ؿ�ѡ�����
																	while (1)//�����Զ���ؿ�ѡ�����ѭ��
																	{
																		ExMessage Msg;
																		bool ifback3 = false;//�����ж��Ƿ�㵽����
																		if (peekmessage(&Msg, EM_MOUSE))//���������Ϣ
																		{
																			switch (Msg.message)
																			{
																			case WM_LBUTTONDOWN://�������
																				int ln = Mousemessage_customlevel(&Msg);//���Զ���ؿ����
																				if (ln >= 0 && ln < acount)//���Զ���ؿ�����ڷ�Χ��
																				{
																					ifstream customlevelnamefin("CustomGameLevel\\" + to_string(ln) + ".dat", ios::in);
																					string customlevelname;
																					customlevelnamefin >> customlevelname;//��ȡ�Զ���ؿ���
																					ifstream customlevelencodefin("CustomGameLevel\\" + customlevelname + ".dat", ios::in);
																					string customlevelencode;
																					customlevelencodefin >> customlevelencode;//��ȡ�Զ���ؿ�����
																					ifstream customlevelrcfin("CustomGameLevel\\" + customlevelname + "_rc.dat", ios::in);
																					string customlevelrc;
																					customlevelrcfin >> customlevelrc;//��ȡ�Զ���ؿ�������
																					int r = 0;//������ʼ��Ϊ0
																					int c = 0;//������ʼ��Ϊ0
																					int n = customlevelrc.size();//�ַ���customlevelrc�Ĵ�СΪn
																					int i = 0;//�����ַ���customlevelrc�ĳ�ʼ����λ��
																					string assist = "";//�����ַ���
																					for (; i < n && customlevelrc[i] != ','; i++)//������
																					{
																						assist.push_back(customlevelrc[i]);
																					}
																					r = stoi(assist);
																					assist = "";
																					i++;
																					for (; i < n && customlevelrc[i] != ','; i++)//������
																					{
																						assist.push_back(customlevelrc[i]);
																					}
																					c = stoi(assist);
																					CloseSelectCustomLevelInterface();//�ر��Զ���ؿ�ѡ�ؽ���
																					Gamelevel customln(r, c, customlevelencode, customlevelname);//�����Զ���ؿ�����
																					customln.OpenLevel();//���Զ���ؿ�����
																					PlayCustomGame(customln, users_accountnumber2name[user[0]]);//�����Զ���ؿ�
																				}
																				if (ln == acount)//���Զ���ؿ���ų�����Χ��Ҳ���㵽����
																				{
																					OpenInitialGameInterface();//����Ϸ��ʼ����
																					DrawInitialGameInterface2();//������Ϸ��ʼ���棬��ťΪ���½��ؿ���ѡ��ؿ�������
																					ifback3 = true;//�����ж��Ƿ�㵽���صı�����Ϊ��
																					break;
																				}
																			}
																			if (ifback3)break;//���㵽���أ����˳��Զ���ؿ�ѡ�ؽ���ѭ��
																		}
																	}
																}
																if (x3 >= 150 && x3 <= 350 && y3 >= 288 && y3 <= 324)//�㵽����
																{
																	ifback2 = true;//�����ж��Ƿ�㵽���صı�����Ϊ��
																	DrawInitialGameInterface1();//������Ϸ��ʼ���棬��ťΪ����ͨ�ؿ����Զ���ؿ�������
																	break;
																};
																break;
															}
															if (ifback2)break;//���㵽���أ����˳���Ϸ��ʼ���棨��ťΪ���½��ؿ���ѡ��ؿ������أ�ѭ��
														};
													};
													break;
												};
												if (x2 >= 150 && x2 <= 350 && y2 >= 288 && y2 <= 324)//�㵽����
												{
													ifback = true;//�����ж��Ƿ�㵽������Ϊ��
													DrawInitialGameInterface3();//������Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
													break;
												};
												break;
											}
											if (ifback)break;//���㵽�������˳���Ϸ��ʼ���水ťΪ����ͨ�ؿ����Զ���ؿ�������ѭ��
										}
									}
									break;
								};
								if (x4 >= 150 && x4 <= 350 && y4 >= 216 && y4 <= 252)//�㵽ע��
								{
									CloseInitialGameInterface();//�ر���Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
									OpenRegisterInputInterface();//��ע����Ϣ�������
									bool register_ifcancel = false;//�����ж��Ƿ�㵽ȡ��
									vector<string> user_information = DrawRegisterInputInterface(register_ifcancel);//����ע����Ϣ������沢����ע����Ϣ
									if (register_ifcancel)//���㵽ȡ���˳�ע�����
									{
										CloseRegisterInputInterface();//�ر�ע����Ϣ�������
										OpenInitialGameInterface();//����Ϸ��ʼ����
										DrawInitialGameInterface3();//������Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
										break;
									}
									//���ļ���Ϊ��ע���û�������Ҳ����ǰע����û����û���ţ����ļ���д���û���Ϣ
									string user_n = "Users\\" + to_string(user_acount) + ".dat";
									ofstream user_information_fout(user_n, ios::out);
									user_information_fout << user_information[0] << " " << user_information[1] << " " << user_information[2];
									//����ע���û�������һ������ļ�Users\\user_count.dat
									ofstream user_count_fout("Users\\user_count.dat", ios::out);
									user_acount++;
									user_count_fout << user_acount;
									//����users_accountnumber2password��users_accountnumber2name��users_names
									users_accountnumber2password[user_information[1]] = user_information[2];
									users_accountnumber2name[user_information[1]] = user_information[0];
									users_names.insert(user_information[0]);
									CloseRegisterInputInterface();//�ر�ע����Ϣ�������
									OpenInitialGameInterface();//����Ϸ��ʼ����
									DrawInitialGameInterface3();//������Ϸ��ʼ���棬��ťΪ����¼��ע�ᡢ����
									break;
								};
								if (x4 >= 150 && x4 <= 350 && y4 >= 288 && y4 <= 324)//�㵽����
								{
									ifback4 = true;//�����ж��Ƿ�㵽���صı�����Ϊ��
									DrawInitialGameInterface0();//������Ϸ��ʼ���棬��ťΪ����ʼ��Ϸ�����а�
									break;
								};
								break;
							}
						}
						if (ifback4)break;//���㵽���أ����˳���Ϸ��ʼ���棨��ťΪ����¼��ע�ᡢ���أ�ѭ��
					}
				};
				if (x1 >= 150 && x1 <= 350 && y1 >= 216 && y1 <= 252)//�㵽���а�
				{
					CloseInitialGameInterface();//�ر���Ϸ��ʼ����
					Change_User_Level_Score();//�����û��ؿ�����
					Find_total_score();//��ÿ���û��ܵ÷�
					OpenTheRankingList();//�����а����
					DrawTheRankingList();//�������а����
					while (1)//�������а����ѭ��
					{
						ExMessage msg5;
						bool ifback5 = false;//�����ж��Ƿ�㵽����
						if (peekmessage(&msg5, EM_MOUSE))//���������Ϣ
						{
							switch (msg5.message)
							{
							case WM_LBUTTONDOWN://�������
								int x5 = msg5.x;//��ǰ����ڴ����еĺ�����
								int y5 = msg5.y;//��ǰ����ڴ����е�������
								if (x5 >= 0 && x5 <= 900 && y5 >= (user_totalscore.size() + 1) * 30 && y5 <= (user_totalscore.size() + 2) * 30)//�㵽����
								{
									ifback5 = true;//�����ж��Ƿ�㵽���صı�����Ϊ��
									CloseTheRankingList();//�ر����а����
									OpenInitialGameInterface();//����Ϸ��ʼ����
									DrawInitialGameInterface0();//������Ϸ��ʼ���棬��ťΪ����ʼ��Ϸ�����а�
									break;
								};
								break;
							}
						}
						if (ifback5)break;//���㵽���أ����˳����а����ѭ��
					}
				};
				break;
			}
		}
	}
	return 0;
}


void Box::setbox(int x, int y)//�������Ӻ�������
{
	boxx = x;
	boxy = y;
}

int Box::getboxx()//��ȡ���Ӻ�����
{
	return boxx;
}

int Box::getboxy()//��ȡ����������
{
	return boxy;
}

void Target::settargetxy(int x, int y)//����Ŀ���λ��������
{
	targetx = x;
	targety = y;
}

int Target::gettargetx()//��ȡĿ���λ������
{
	return targetx;
}

int Target::gettargety()//��ȡĿ���λ������
{
	return targety;
}

void Wall::setwallxy(int x, int y)//����ǽ��������
{
	wallx = x;
	wally = y;
}

int Wall::getwallx()//��ȡǽ������
{
	return wallx;
}

int Wall::getwally()//��ȡǽ������
{
	return wally;
}

void Map::setmaprc(int r, int c)//���õ�ͼ������ͬʱ��ʼ����ͼ
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

int Map::getmapr()//��ȡ��ͼ����
{
	return Row;
}

int Map::getmapc()//��ȡ��ͼ����
{
	return Col;
}

int Map::getmap0data(int x, int y)//��ȡ��ͼ�ض������ϵ���ֵ
{
	return map0[x][y];
}

void Map::showmap()//��ӡ��ͼ
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

void Map::SetOnMap(int x, int y, int data)//��ĳ�������ڵ�ͼ��
{
	map0[x][y] = data;
}

void Character::setcharacter(int x, int y, int o)//���ý�ɫ�������
{
	characterx0 = x;
	charactery0 = y;
	Orientation = o;
}

int Character::getcharacterx()//��ȡ��ɫ������
{
	return characterx0;
}

int Character::getcharactery()//��ȡ��ɫ������
{
	return charactery0;
}

int Character::getcharactero()//��ȡ��ɫ����
{
	return Orientation;
}

void Character::characteroperate0(char ch)//������ɫ������ƶ�
{
	int x = getcharacterx(), y = getcharactery();
	switch (ch)
	{
	case 'a':
	case 'A':
		setcharacter(x, y + 1, 1);//�������ư�ť�����ɫ�ڵ�ͼ�ϵ��������һ
		break;
	case 'w':
	case 'W':
		setcharacter(x + 1, y, 2);//�������ư�ť�����ɫ�ڵ�ͼ�ϵĺ������һ
		break;
	case 'd':
	case 'D':
		setcharacter(x, y - 1, 3);//�������ư�ť�����ɫ�ڵ�ͼ�ϵ��������һ
		break;
	case 's':
	case 'S':
		setcharacter(x - 1, y, 4);//�������ư�ť�����ɫ�ڵ�ͼ�ϵĺ������һ
		break;
	}
}

void Character::characteroperate1(char ch)//������ɫ���ƶ�
{
	int x = getcharacterx(), y = getcharactery();
	switch(ch)
	{
	case 'a':
	case 'A':
		setcharacter(x, y - 1, 1);//�������ư�ť�����ɫ�ڵ�ͼ�ϵ��������һ��������Ϊ����
		break;
	case 'w':
	case 'W':
		setcharacter(x - 1, y, 2);//�������ư�ť�����ɫ�ڵ�ͼ�ϵĺ������һ��������Ϊ����
		break;
	case 'd':
	case 'D':
		setcharacter(x, y + 1, 3);//�������ư�ť�����ɫ�ڵ�ͼ�ϵ��������һ��������Ϊ����
		break;
	case 's':
	case 'S':
		setcharacter(x + 1, y, 4);//�������ư�ť�����ɫ�ڵ�ͼ�ϵĺ������һ��������Ϊ����
		break;
	}
}

Gamelevel::Gamelevel(int r, int c, string code, string name)//��ʼ���ؿ�
{
	row = r;//��ͼ����Ϊr
	col = c;//��ͼ����Ϊc
	reachedboxes = 0;//�ﵽĿ���λ��������Ϊ0
	encode = code;//�ؿ���ʼ������Ϊcode
	savedcode = "";//�ؿ��浵����Ϊ��
	gamename = name;//�ؿ���Ϊname
	score = row * col * 5 * 5;//�ؿ�������Ϊ��ͼ�������˻��ٳ�25
	DeCode(0);//�Գ�ʼ��������н���
	SetAllOnMap();//����������ŵ���ͼ��
}

void Gamelevel::DeCode(int kind)//�Թؿ���Ϣ�ַ������н��룬kindΪ0��ʾ��ʼ���룬kindΪ1��ʾ�浵�ı���
{
	string code = "";//��������
	//���ؿ��е������Ϣ��գ������������ùؿ�
	gamemap.setmaprc(row, col);
	box.resize(0);
	whichbox2boxindex.clear();
	boxindex2whichbox.clear();
	target.resize(0);
	wall.resize(0);
	reachedboxes = 0;
	if (kind == 0)code = encode;//kindΪ0����code��ֵΪencode
	if (kind == 1)code = savedcode;//kindΪ1����code��ֵΪsavedcode
	int i = 0;//�����ַ���code�ĳ�ʼ����λ��
	string assist = "";//�����ַ���
	//�ֽ�����һ���֣��ﵽĿ���λ��������
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	reachedboxes = stoi(assist);
	i++;
	assist = "";
	//�ֽ����ڶ����֣���������
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
	//�ֽ����������֣�Ŀ���λ����
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
	//�ֽ������Ĳ��֣�ǽ����
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
	//�ֽ������岿�֣���ɫ�ڵ�ͼ�ϵĺ�����
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int chx = stoi(assist);
	i++;
	assist = "";
	//�ֽ����������֣���ɫ�ڵ�ͼ�ϵ�������
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int chy = stoi(assist);
	i++;
	assist = "";
	//�ֽ������߲��֣���ɫ����
	while (code[i] != ',')
	{
		assist.push_back(code[i]);
		i++;
	}
	int cho = stoi(assist);
	//����ؿ��ڽ�ɫ��Ϣ
	character.setcharacter(chx, chy, cho);
	i++;
	//���������������飬�ֱ����ڴ洢�������ꡢĿ���λ���ꡢǽ����
	vector<vector<int>> bindex(bnum, vector<int>(2));
	vector<vector<int>> tindex(tnum, vector<int>(2));
	vector<vector<int>> windex(wnum, vector<int>(2));
	//�ֽ����ڰ˲��֣���������
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
	//�ֽ����ھŲ��֣�Ŀ���λ����
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
	//�ֽ�����ʮ���֣�ǽ����
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
	//�����������йصĴ洢��������ÿ�����������������box����ÿ��������������ӱ�Ž���˫ӳ������
	for (int b = 0; b < bnum; b++)
	{
		box[b].setbox(bindex[b][0], bindex[b][1]);
		pair<int, int> boxindex = { bindex[b][0],bindex[b][1] };
		boxindex2whichbox[boxindex] = b;
		whichbox2boxindex[b] = boxindex;
	}
	//������Ŀ���λ�йصĴ洢��������ÿ��Ŀ���λ�����������target����ÿ��Ŀ���λ�������Ŀ���λ���꼯��
	for (int t = 0; t < tnum; t++)
	{
		pair<int, int> index = { tindex[t][0],tindex[t][1] };
		target[t].settargetxy(tindex[t][0], tindex[t][1]);
		target_index.insert(index);
	}
	//������ǽ�йصĴ洢��������ÿ��ǽ�����������wall
	for (int w = 0; w < wnum; w++)wall[w].setwallxy(windex[w][0], windex[w][1]);
}

void Gamelevel::SetBoxOnMap(int i)//�����������ڵ�ͼ��
{
	pair<int, int> index = { box[i].getboxx(),box[i].getboxy() };//��i�����ӵ�����
	int mdata = target_index.count(index) ? 5 : 2;//������ʾ�ڵ�ͼ�ϵ����֣�����ĳĿ���λ�غ��������Ϊ5�����������Ϊ2
	gamemap.SetOnMap(box[i].getboxx(), box[i].getboxy(), mdata);//��Ϸ�ؿ���ͼ�����е�map0�����box[i].getboxx()�У�box[i].getboxy()�д���Ϊmdata
}

void Gamelevel::SetTargetOnMap(int i)//��Ŀ���λ�����ڵ�ͼ��
{
	gamemap.SetOnMap(target[i].gettargetx(), target[i].gettargety(), 3);//��Ϸ�ؿ���ͼ�����е�map0�����target[i].gettargetx()�У�target[i].gettargety()�д���Ϊ3
}

void Gamelevel::SetWallOnMap(int i)//��ǽ�����ڵ�ͼ��
{
	gamemap.SetOnMap(wall[i].getwallx(), wall[i].getwally(), 9);//��Ϸ�ؿ���ͼ�����е�map0�����wall[i].getwallx()�У�wall[i].getwally()�д���Ϊ9
}

void Gamelevel::SetAllOnMap()//��������������ڵ�ͼ��
{
	for (int i = 0; i < targetnum; i++)//����Ŀ���λ
	{
		SetTargetOnMap(i);
	}
	for (int i = 0; i < boxnum; i++)//��������
	{
		SetBoxOnMap(i);
	}
	for (int i = 0; i < wallnum; i++)//����ǽ
	{
		SetWallOnMap(i);
	}
}

int Gamelevel::whichbox(int x, int y)//�ж�ָ��λ�õ������ǵڼ�������
{
	pair<int, int> indexpair = { x,y };//����ԣ�������Ϸ�ؿ���ͼ�����map0�����е�x�У�y�д�
	if (!boxindex2whichbox.count(indexpair))//���������������ӱ�ŵ�˫ӳ���в����������indexpair���򷵻�NULL
	{
		cout << "����Դ���" << endl;
		return NULL;
	}
	return boxindex2whichbox[indexpair];//����������������Ӧ�����ӱ��
}

void Gamelevel::MoveCharactar(char ch)//�ƶ�һ����ɫ
{
	if (score > 0)score -= 5;//�����ƶ������ҵ�ǰ��������0���������5
	int x = character.getcharacterx(), y = character.getcharactery();//ȡ����ɫ��ǰ�ڵ�ͼ�����е�������Ϣ
	pair<int, int> preboxindex = { x,y };//���赱ǰ��ɫλ�ô������ӣ�����֮���ж��Ƿ����ƶ����ӵ�������������У�������ƶ�������������������ɫ������ͬ
	int mdata00 = gamemap.getmap0data(x, y);//��ǰ��ɫλ�ô��ڵ�ͼ�����ϵ����� 
	int mdata01 = y + 1 >= col ? -1 : gamemap.getmap0data(x, y + 1);//��ǰ��ɫλ�ô�����һ���ڵ�ͼ�����ϵ����ݣ�����ǰ��ɫλ�ô�����һ�񳬳��˵�ͼ���鷶Χ���������Ϊ-1
	int mdata0_1 = y - 1 < 0 ? -1 : gamemap.getmap0data(x, y - 1);//��ǰ��ɫλ�ô�����һ���ڵ�ͼ�����ϵ����ݣ�����ǰ��ɫλ�ô�����һ�񳬳��˵�ͼ���鷶Χ���������Ϊ-1
	int mdata10 = x + 1 >= row ? -1 : gamemap.getmap0data(x + 1, y);//��ǰ��ɫλ�ô�����һ���ڵ�ͼ�����ϵ����ݣ�����ǰ��ɫλ�ô�����һ�񳬳��˵�ͼ���鷶Χ���������Ϊ-1
	int mdata_10 = x - 1 < 0 ? -1 : gamemap.getmap0data(x - 1, y);//��ǰ��ɫλ�ô�����һ���ڵ�ͼ�����ϵ����ݣ�����ǰ��ɫλ�ô�����һ�񳬳��˵�ͼ���鷶Χ���������Ϊ-1
	switch (ch)
	{
	case 'a'://����
	case 'A':
		if (mdata00 == 2 && mdata0_1 == 0)//��ǰλ�������ӣ�������һ��Ϊ�գ����ӿ��ƶ�
		{
			int wb = whichbox(x, y);//��ȡ���ӱ��
			gamemap.SetOnMap(x, y, 0);//��ͼ�����ϵ�ǰλ��������Ϊ0
			box[wb].setbox(x, y - 1);//wb��������������
			pair<int, int> nowboxindex = { x,y - 1 };//���ƺ����������
			boxindex2whichbox.erase(preboxindex);//���ԭ�������굽���ӱ�ŵ�ӳ��
			boxindex2whichbox[nowboxindex] = wb;//�����������굽���ӱ�ŵ�ӳ��
			whichbox2boxindex[wb] = nowboxindex;//�������ӱ�ŵ����������ӳ��
			SetBoxOnMap(wb);//�����ĺ��wb�����ӷŵ���ͼ��
		}
		if (mdata00 == 2 && mdata0_1 == 3)//��ǰλ�������ӣ�������һ����Ŀ���λ�����ӿ��ƶ����������ƶ��󵽴�Ŀ���λ
		{
			int wb = whichbox(x, y);//��ȡ���ӱ��
			gamemap.SetOnMap(x, y, 0);//��ͼ�����ϵ�ǰλ��������Ϊ0
			box[wb].setbox(x, y - 1);//wb��������������
			pair<int, int> nowboxindex = { x,y - 1 };//���ƺ����������
			boxindex2whichbox.erase(preboxindex);//���ԭ�������굽���ӱ�ŵ�ӳ��
			boxindex2whichbox[nowboxindex] = wb;//�����������굽���ӱ�ŵ�ӳ��
			whichbox2boxindex[wb] = nowboxindex;//�������ӱ�ŵ����������ӳ��
			reachedboxes++;//����Ŀ���λ����������һ
			gamemap.SetOnMap(x, y - 1, 5);//��ǰλ������һ���ڵ�ͼ�����ϵ�������Ϊ5
			score += 25;//ʹ���ӵִ�Ŀ���λ��������25
		}
		if (mdata00 == 2 && (mdata0_1 == 2 || mdata0_1 == 5 || mdata0_1 == 9))//��ǰλ�������ӣ�������һ�������ӻ�ﵽĿ���λ�����ӻ�ǽ�����Ӳ����ƶ�
		{
			character.characteroperate0(ch);//��ɫ���ֳ��򲻱䲢����
		}
		if (mdata00 == 5 || mdata00 == 9)//��ǰλ�ô��дﵽĿ���λ�����ӻ�ǽ
		{
			character.characteroperate0(ch);//��ɫ���ֳ��򲻱䲢����
		};
		break;
		//֮������ơ����ơ����Ʋ�����ͬС�죬����ע��
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

int Gamelevel::win()//�ж�ĳ���Ƿ�Ӯ
{
	return reachedboxes == boxnum;
}

void Gamelevel::OpenLevel()//�򿪹ؿ�����
{
	initgraph(col * 40, (row + 1) * 40);
}

void Gamelevel::CloseLevel()//�رչؿ�����
{
	closegraph();
}

void Gamelevel::DrawLevel()//���ƹؿ�
{
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	cleardevice();//�����Ļ��ʹ������ɫ��Ϊ��ɫ
	putimage(0 * 40, row * 40, 40, 40, &images_level[13], 0, 0);//���˰�ť
	putimage(1 * 40, row * 40, 40, 40, &images_level[14], 0, 0);//���ùؿ���ť
	putimage(2 * 40, row * 40, 40, 40, &images_level[15], 0, 0);//�浵��ť
	putimage(3 * 40, row * 40, 40, 40, &images_level[16], 0, 0);//������ť
	int chx = character.getcharacterx();//��ɫ�ڵ�ͼ�ϵĺ�����
	int chy = character.getcharactery();//��ɫ�ڵ�ͼ�ϵ�������
	int cho = character.getcharactero();//��ɫ����
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			int mdata = gamemap.getmap0data(i, j);
			if (mdata == 3 && chx == i && chy == j && cho == 1)//�г����ɫ��Ŀ��
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[4], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 2)//�г��Ͻ�ɫ��Ŀ��
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[6], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 3)//�г��ҽ�ɫ��Ŀ��
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[7], 0, 0);
				continue;
			}
			if (mdata == 3 && chx == i && chy == j && cho == 4)//�г��½�ɫ��Ŀ��
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[8], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 1)//�����ɫ
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[1], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 2)//���Ͻ�ɫ
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[10], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 3)//���ҽ�ɫ
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[11], 0, 0);
				continue;
			}
			if (chx == i && chy == j && cho == 4)//���½�ɫ
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[12], 0, 0);
				continue;
			}
			if (mdata == 0)//�հ�
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[0], 0, 0);
				continue;
			}
			if (mdata == 2)//δ�ﵽĿ�������
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[2], 0, 0);
				continue;
			}
			if (mdata == 3 && ((chx != i && chy != j) || (chx == i && chy != j) || (chx != i && chy == j)))//�޽�ɫĿ��
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[3], 0, 0);
				continue;
			}
			if (mdata == 5)//�ﵽĿ�������
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[5], 0, 0);
				continue;
			}
			if (mdata == 9)//ǽ
			{
				putimage(j * 40, i * 40, 40, 40, &images_level[9], 0, 0);
				continue;
			}
		}
	}
}

void Gamelevel::DrawChangedImage(int prex, int prey, int predata, int nowx, int nowy, int nowdata, int sufx, int sufy, int sufdata)//���ƽ�ɫ�ƶ���ͼƬ�ı�Ĳ���
{
	int deltax = nowx - sufx;//�ƶ�ǰ���ƶ����ɫ�ڵ�ͼ�Ϻ�����Ĳ�ֵ
	int deltay = nowy - sufy;//�ƶ�ǰ���ƶ����ɫ�ڵ�ͼ��������Ĳ�ֵ
	if (deltax == 0 && deltay == 0)//�ƶ�ǰ���ƶ����ɫλ��δ�ı�
	{
		int cho = character.getcharactero();//��ȡ��ɫ��ǰ����
		switch (nowdata)//��ͼ�ϵ�ǰ��ɫλ�ô�������
		{
		case 0://��Ϊ�հ�
			switch (cho)
			{
			case 1://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[1], 0, 0);
				break;
			case 2://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[10], 0, 0);
				break;
			case 3://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[11], 0, 0);
				break;
			case 4://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[12], 0, 0);
				break;
			};
			break;
		case 3://��ΪĿ���λ
			switch (cho)
			{
			case 1://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[4], 0, 0);
				break;
			case 2://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[6], 0, 0);
				break;
			case 3://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[7], 0, 0);
				break;
			case 4://��ɫ����
				putimage(nowy * 40, nowx * 40, 40, 40, &images_level[8], 0, 0);
				break;
			};
			break;
		}
		return;
	}
	int deltacase = deltax * 1 + deltay * 2;//ֻ����4�������deltax=1,deltay=0;deltax=-1,deltay=0;deltax=0,deltay=1;deltax=0,deltay=-1
	switch (deltacase)
	{
	case 1://��ɫ�����ƶ�
		switch (predata)//��ͼ�Ͻ�ɫ�·�һ������
		{
		case 0://�հ�
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://����
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://����Ŀ���λ������
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://ǽ��
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//��ͼ�ϵ�ǰ��ɫλ�ô�����
		{
		case 0://�հ�
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[12], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[8], 0, 0);
			break;
		};
		switch (sufdata)//��ͼ�Ͻ�ɫ�Ϸ�һ������
		{
		case 0://�հ�
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case -1://��ɫ�����ƶ�
		switch (predata)//��ͼ�Ͻ�ɫ�Ϸ�һ������
		{
		case 0://�հ�
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://����
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://����Ŀ���λ������
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://ǽ��
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//��ͼ�ϵ�ǰ��ɫλ�ô�����
		{
		case 0://�հ�
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[10], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[6], 0, 0);
			break;
		};
		switch (sufdata)//��ͼ�Ͻ�ɫ�·�һ������
		{
		case 0://�հ�
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case 2://��ɫ�����ƶ�
		switch (predata)//��ͼ�Ͻ�ɫ�ҷ�һ������
		{
		case 0://�հ�
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://����
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://����Ŀ���λ������
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://ǽ��
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//��ͼ�ϵ�ǰ��ɫλ�ô�����
		{
		case 0://�հ�
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[11], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[7], 0, 0);
			break;
		};
		switch (sufdata)//��ͼ�Ͻ�ɫ��һ������
		{
		case 0://�հ�
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	case -2://��ɫ�����ƶ�
		switch (predata)//��ͼ�Ͻ�ɫ��һ������
		{
		case 0://�հ�
			putimage(prey * 40, prex * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 2://����
			putimage(prey * 40, prex * 40, 40, 40, &images_level[2], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(prey * 40, prex * 40, 40, 40, &images_level[3], 0, 0);
			break;
		case 5://����Ŀ���λ������
			putimage(prey * 40, prex * 40, 40, 40, &images_level[5], 0, 0);
			break;
		case 9://ǽ��
			putimage(prey * 40, prex * 40, 40, 40, &images_level[9], 0, 0);
			break;
		};
		switch (nowdata)//��ͼ�ϵ�ǰ��ɫλ�ô�����
		{
		case 0://�հ�
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[1], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(nowy * 40, nowx * 40, 40, 40, &images_level[4], 0, 0);
			break;
		};
		switch (sufdata)//��ͼ���ҷ�һ������
		{
		case 0://�հ�
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[0], 0, 0);
			break;
		case 3://Ŀ���λ
			putimage(sufy * 40, sufx * 40, 40, 40, &images_level[3], 0, 0);
			break;
		};
		break;
	}
}

void LoadResource_InitialGameInterface()//������Ϸ��ʼ����ͼƬ
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

void LoadResource_SelectLevelInterface()//����ѡ�ؽ���ͼƬ
{
	char img[50] = { 0 };
	sprintf_s(img, "images_selectlevelinterface\\0.jpg");
	loadimage(&images_selectlevelinterface[0], img, 5 * 100, 4 * 100);
}

void LoadResource_Level()//���عؿ�ͼƬ
{
	for (int i = 0; i < 17; i++)
	{
		char img1[50] = { 0 };
		sprintf_s(img1, "images_level\\%d.jpg", i);
		loadimage(&images_level[i], img1, 40, 40);
	}
}

void LoadResource_CreateCustomLevel()//���عؿ��Զ������ͼƬ
{
	for (int i = 0; i < 8; i++)
	{
		char img[50] = { 0 };
		sprintf_s(img, "images_createcustomlevel\\%d.jpg", i);
		loadimage(&images_createcustomlevel[i], img, 40, 40);
	}
}

void OpenInitialGameInterface()//����Ϸ��ʼ����
{
	initgraph(5 * 100, 4 * 100);
}

void OpenSelectLevelInterface()//��ѡ�ؽ���
{
	initgraph(5 * 100, 4 * 100 + 50);
}

void OpenNamingCustomLevel()//���Զ���ؿ���������
{
	initgraph(600, 480);
}

void OpenCreateCustomLevel()//�򿪹ؿ��Զ������
{
	initgraph(1040, 760);
}

void OpenSelectCustomLevelInterface(int c)//���Զ���ؿ�ѡ�ؽ���
{
	initgraph(500, (c + 1) * 30);
}

void OpenLoginInputInterface()//�򿪵�¼��Ϣ���봰��
{
	initgraph(600, 480);
}

void OpenRegisterInputInterface()//��ע����Ϣ���봰��
{
	initgraph(600, 570);
}

void OpenTheRankingList()//�����а�ҳ��
{
	initgraph(100 + 400 + 400, (user_totalscore.size() + 2) * 30);
}

void CloseInitialGameInterface()//�ر���Ϸ��ʼ����
{
	closegraph();
}

void CloseSelectLevelInterface()//�ر�ѡ�ؽ���
{
	closegraph();
}

void CloseNamingCustomLevel()//�ر��Զ���ؿ���������
{
	closegraph();
}

void CloseSelectCustomLevelInterface()//�ر��Զ���ؿ�ѡ�ؽ���
{
	closegraph();
}

void CloseLoginInputInterface()//�رյ�¼�������
{
	closegraph();
}

void CloseRegisterInputInterface()//�ر�ע���������
{
	closegraph();
}

void CloseTheRankingList()//�ر����а�ҳ��
{
	closegraph();
}

void DrawInitialGameInterface0()//������Ϸ��ʼ���棬��ťΪ��ʼ��Ϸ�����а�
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[1], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[9], 0, 0);
}

void DrawInitialGameInterface1()//������Ϸ��ʼ���棬��ťΪ��ͨ�ؿ����Զ���ؿ�
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[2], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[3], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawInitialGameInterface2()//�����Զ���ؿ���ʼ���棬��ťΪ�½��ؿ���ѡ��ؿ�������
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[5], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[6], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawInitialGameInterface3()//���Ƶ�¼��ע����棬��ťΪ��¼��ע�ᡢ����
{
	putimage(0, 0, 500, 400, &images_initialgameinterface[0], 0, 0);
	putimage(150, 144, 200, 36, &images_initialgameinterface[7], 0, 0);
	putimage(150, 216, 200, 36, &images_initialgameinterface[8], 0, 0);
	putimage(150, 288, 200, 36, &images_initialgameinterface[4], 0, 0);
}

void DrawSelectLevelInterface()//����ѡ�ؽ���
{
	setbkcolor(RGB(112, 163, 229));
	cleardevice();
	settextcolor(BLACK);
	settextstyle(40, 0, "����");
	outtextxy(140, 405, "��");
	outtextxy(320, 405, "��");
	setlinecolor(BLACK);
	rectangle(0, 400, 500, 450);
	putimage(0, 0, 500, 400, &images_selectlevelinterface[0], 0, 0);
}

string DrawNamingCustomLevel_and_ReturnName(bool& ifcancel)//�����Զ���ؿ��������沢�����ļ���
{
	int x = 100;//��������ϽǺ�����
	int y = 160;//��������Ͻ�������
	int w = 400;//����򳤶�
	int h = 30;//�������
	int LineColor = BLACK;//ֱ����ɫ
	int TextColor = BLACK;//�ı���ɫ
	int BackgroundColor = WHITE;//������ɫ
	char text[1024] = { '\0' };//���ڴ洢�ı�
	int textLength = 0;//������ı�����
	int index = 0;//��ǰ���λ��
	string name = "";//���շ��ص��ļ���
	setbkcolor(BackgroundColor);//���ñ�����ɫ
	cleardevice();//��մ��ڣ��س�ʼ��������ʽ
	settextstyle(20, 0, "����");//�������������СΪ20*20���أ�����Ϊ����
	settextcolor(TextColor);//�����ı���ɫ
	setlinecolor(LineColor);//����ֱ����ɫ
	rectangle(x, y, x + w, y + h);//���������
	outtextxy(x + 5, y - 25, "��Ϊ�Զ���ؿ�����(��֧��Ӣ����ĸ)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x+5��y-25��
	rectangle(x, 2 * y, x + 120, 2 * y + h);//����ȷ����ť��
	rectangle(x + 280, 2 * y, x + w, 2 * y + h);//����ȡ����ť��
	outtextxy(x + 40, 2 * y + 5, "ȷ��");//���ȷ��
	outtextxy(x + 280 + 40, 2 * y + 5, "ȡ��");//���ȡ��
	line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//���ƹ��
	ExMessage msg;//�����Ϣ
	char c;//��ǰ������ַ�
	bool ifbreak = false;//�����ж��Ƿ��Ƴ�ѭ��
	while (1)//��������ѭ��
	{
		outtextxy(x + 5, y + 5, text);//��������һ���ַ�
		rectangle(x, y, x + w, y + h);//���������
		outtextxy(x + 5, y - 25, "��Ϊ�Զ���ؿ�����(��֧��Ӣ����ĸ)��");//������ʾ��
		rectangle(x, 2 * y, x + 120, 2 * y + h);//����ȷ����ť��
		rectangle(x + 280, 2 * y, x + w, 2 * y + h);//����ȡ����ť��
		outtextxy(x + 40, 2 * y + 5, "ȷ��");//���ȷ��
		outtextxy(x + 280 + 40, 2 * y + 5, "ȡ��");//���ȡ��
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//���ƹ��
		if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
		{
			switch (msg.message)//�ж������Ϣ
			{
			case WM_LBUTTONDOWN://����������
				int x = msg.x;//����ʱ��ָ�򴰿�������λ�õĺ�����
				int y = msg.y;//����ʱ��ָ�򴰿�������λ�õ�������
				if (x >= 100 && x <= 220 && y >= 320 && y <= 350)//�����ȷ����ť��Χ��
				{
					for (int i = 0; i < 1024 && text[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
					{
						name.push_back(text[i]);
					}
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					break;
				};
				if (x >= 380 && x <= 500 && y >= 320 && y <= 350)//�����ȡ����ť��Χ��
				{
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					ifcancel = true;//�Ƿ�ȡ����Ϊ��
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//���񰴼���Ϣ
		{
			c = _getch();//����ǰ�������ַ������ַ�c
			if (c == '\b' && textLength > 0 && index > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
			{
				if (index == textLength)//���λ���������ı���ĩβ
				{
					cleardevice();
					text[--textLength] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					index--;//���λ�ü�һ
				}
				else//���λ�ò��������ı�ĩβ
				{
					cleardevice();
					for (int i = index - 1; i < textLength; i++)text[i] = text[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
					index--;//���λ�ü�һ
					text[--textLength] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
				}
			}
			else if (c == '\b' && textLength == 0)//����backspace�����������ı���ɾ��
			{
				cleardevice();
				continue;//����ѭ��
			}
			else if (c == '\r')//�����س�
			{
				for (int i = 0; i < 1024 && text[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
				{
					name.push_back(text[i]);
				}
				ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
				break;
			}
			else
			{
				if (c == 75 && index > 0)//��������ҹ�껹������
				{
					index--;//���λ�ü�һ
					cleardevice();
					continue;
				}
				if (c == 77 && index < textLength)//�����Ҽ��ҹ�껹������
				{
					index++;//���λ�ü�һ
					cleardevice();
					continue;
				}
				if (index == textLength && textLength < 39 && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))//������ĸ�ҹ�����������ı�ĩβ
				{
					index++;//���λ�ü�һ
					text[textLength++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
					text[textLength] = '\0';//��֤�ı�����н�����
					cleardevice();
					continue;
				}
				if (index != textLength && textLength < 39 && (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'))//������ĸ�ҹ�겻���������ı�ĩβ
				{
					for (int i = textLength; i > index; i--)text[i] = text[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
					text[index++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
					textLength++;//�ı����ȼ�һ
					cleardevice();
					continue;
				}
			}
		}
		if (ifbreak)break;//���ڿ��Ƽ���ѭ�����˳�ѭ��
	}
	return name;//����������ı���Ϣ
}

void DrawCreateCustomLevel_and_CreateCustomLevel(map<int, set<pair<int, int>>>& w_b_t, Character& c, int& r, string levelname)//���ƹؿ��Զ�����沢�����Զ���
{
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	cleardevice();//��մ��ڣ�ʹ������ɫ��Ϊ��ɫ
	for (int i = 0; i < 16; i++)//�����Զ���ؿ����Զ��廭��������Χ����
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
	int tomid = 10;//��ť����Ϊ���еĲ���
	int buttony = 17;//��ť�������ײ��Ĳ���
	putimage((0 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[0], 0, 0);//ǽ�巽��ѡ��ť
	putimage((1 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[1], 0, 0);//���ӷ���ѡ��ť
	putimage((2 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//Ŀ���λ����ѡ��ť
	putimage((3 + tomid) * 40, buttony * 40, 40, 40, &images_createcustomlevel[3], 0, 0);//��ɫ����ѡ��ť
	settextcolor(BLACK);//����������ɫΪ��ɫ
	settextstyle(40, 0, "����");//����������ʽ
	setbkcolor(RGB(182, 229, 29));//���豳����ɫ����ʹ��ȷ�ϡ���ť�����ɫ
	outtextxy((4 + tomid) * 40, buttony * 40, "ȷ��");//ȷ�ϰ�ť
	setlinecolor(0x00B5E51D);//����������ɫ
	//ʹ�����ť�б߿�
	rectangle((0 + tomid) * 40, buttony * 40, (0 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((1 + tomid) * 40, buttony * 40, (1 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((2 + tomid) * 40, buttony * 40, (2 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((3 + tomid) * 40, buttony * 40, (3 + tomid) * 40 + 40, buttony * 40 + 40);
	rectangle((4 + tomid) * 40, buttony * 40, (4 + tomid) * 40 + 80, buttony * 40 + 40);
	priority_queue<int, vector<int>, greater<>> MinLeft;//������У�С���ѣ��洢���õ�ǽ����С���ڵ�ͼ�ϵ�������
	priority_queue<int, vector<int>, less<>> MaxRight;//������У��󶥶ѣ��洢���õ�ǽ�������ڵ�ͼ�ϵ�������
	priority_queue<int, vector<int>, greater<>> MinTop;//������У�С���ѣ��洢���õ�ǽ����С���ڵ�ͼ�ϵĺ�����
	priority_queue<int, vector<int>, less<>> MaxBottom;//������У��󶥶ѣ��洢���õ�ǽ�������ڵ�ͼ�ϵĺ�����
	MinLeft.emplace(25);//ǽ����С�ڵ�ͼ�ϵ��������ʼ��Ϊ25���ɱ�֤ջ��Ԫ��Ϊ��С
	MaxRight.emplace(0);//ǽ������ڵ�ͼ�ϵ��������ʼ��Ϊ0���ɱ�֤ջ��Ԫ��Ϊ���
	MinTop.emplace(15);//ǽ����С�ڵ�ͼ�ϵĺ������ʼ��Ϊ15���ɱ�֤ջ��Ԫ��Ϊ��С
	MaxBottom.emplace(0);//ǽ������ڵ�ͼ�ϵĺ������ʼ��Ϊ0���ɱ�֤ջ��Ԫ��Ϊ���
	int minleft = 25;//ǽ����С�ڵ�ͼ�ϵ��������ʼ��Ϊ25���ɱ�֤ջ��Ԫ��Ϊ��С
	int maxright = 0;//ǽ������ڵ�ͼ�ϵ��������ʼ��Ϊ0���ɱ�֤ջ��Ԫ��Ϊ���
	int mintop = 15;//ǽ����С�ڵ�ͼ�ϵĺ������ʼ��Ϊ15���ɱ�֤ջ��Ԫ��Ϊ��С
	int maxbottom = 0;//ǽ������ڵ�ͼ�ϵĺ������ʼ��Ϊ0���ɱ�֤ջ��Ԫ��Ϊ���
	ExMessage msg;
	int nowbutton = -1;//��ǰ�����İ�ť��ų�ʼ��Ϊ-1
	int prebutton = 0;//��һ�ΰ����İ�ť��ų�ʼ��Ϊ0
	set<pair<int,int>> usedtargetindex;//�ѷ��õ�Ŀ���λ���꼯��
	set<pair<int, int>> usedboxindex;//�ѷ��õ��������꼯��
	c.setcharacter(-1, -1, -1);//��ɫ�����ʼ��Ϊ{-1��-1}�������ʼ��Ϊ-1
	pair<int, int> characterindex = { -1,-1 };//��ɫ�����ʼ��Ϊ{-1��-1}
	set<pair<int, int>> usedwallindex;//�ѷ��õ�ǽ���꼯��
	set<pair<int, int>> usedbox_targetindex;//�ѷ��õĴﵽĿ���λ���������꣨Ҳ����ĳĿ���λ���꣩����
	bool ifbreak = false;//�����ж��Ƿ�����Զ���ؿ�
	while (1)//�����Զ��幦�ܽ���ѭ��
	{
		if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
		{
			//��������ĺ�������
			int x = msg.x;
			int y = msg.y;
			//�����Ҽ��ĺ�������
			int x1 = msg.x;
			int y1 = msg.x;
			switch (msg.message)
			{
			case WM_LBUTTONDOWN://�������
				x = msg.x;
				y = msg.y;
				if (x >= (0 + tomid) * 40 && x <= (4 + tomid) * 40 + 80 && y >= buttony * 40 && y <= buttony * 40 + 40)//������ť
				{
					if (nowbutton != -1)prebutton = nowbutton >= 4 ? 4 : nowbutton;//������һ�������İ�ť���
					nowbutton = ((x / 40) - tomid) >= 4 ? 4 : ((x / 40) - tomid);//���õ�ǰ�����İ�ť���
					rectangle((prebutton + tomid) * 40, buttony * 40, (prebutton + tomid) * 40 + (prebutton == 4 ? 80 : 40), buttony * 40 + 40);//�ָ���һ����ť�ı߿���ɫ
					setlinecolor(RED);//����������ɫΪ��ɫ
					rectangle((nowbutton + tomid) * 40, buttony * 40, (nowbutton + tomid) * 40 + (nowbutton == 4 ? 80 : 40), buttony * 40 + 40);//��ǰ�����İ�ť�߿���ɫ��Ϊ��ɫ������ѡ��
					setlinecolor(0x00B5E51D);//�ָ�������ɫΪԭ������ɫ
					if (nowbutton == 4)//����ȷ�ϰ�ť
					{
						for (int i = 16; i < 19; i++)//����������Ϳ��
						{
							for (int j = 0; j < tomid; j++)
							{
								putimage(j * 40, i * 40, 40, 40, &images_createcustomlevel[6], 0, 0);
							}
						}
						set<pair<int, int>> circlenode;//Χǽ������꼯��
						bool whetherclose = whethercircle(w_b_t[0], circlenode);//�ж��Ƿ��з�յ�Χǽ���������Χǽ�ϵ�����ǽ�����괫��circlenode����
						bool whetherin = whetherincircle(w_b_t[0], w_b_t[1], w_b_t[2], c, circlenode);//�ж��Ƿ����е����ӡ�Ŀ���λ����ɫ����Χǽ��
						int whetherclose_whetherin = (whetherclose && whetherin) ? 1 : 0;//����Χǽ����������ֶ���Χǽ�ڣ���ñ���Ϊ1������Ϊ0
						int deltaw = (maxbottom - mintop) >= 2 ? 1 : 0;//��Ϸ��ͼ�����Ƿ񳬹�2�����ǣ���ñ���Ϊ1������Ϊ0
						int deltal = (maxright - minleft) >= 4 ? 1 : 0;//��Ϸ��ͼ�����Ƿ񳬹�4�����ǣ���ñ���Ϊ1������Ϊ0
						int bnum_equal_tnum = (w_b_t[1].size() == w_b_t[2].size() && w_b_t[1].size() > 0) ? 1 : 0;//�Ƿ������Ӻ�Ŀ���λ�Ҷ���������ͬ�����ǣ���ñ���Ϊ1������Ϊ0
						int havecharacter = (c.getcharacterx() != -1 && c.getcharactery() != -1 && c.getcharactero() != -1) ? 1 : 0;//��ɫ��Ϣ�Ƿ����棬���ǣ�������н�ɫ���ñ���Ϊ1������Ϊ0
						int errornum = (whetherclose_whetherin << 4) | (deltaw << 3) | (deltal << 2) | (bnum_equal_tnum << 1) | (havecharacter);//��5�������жϵ����ͱ�������Ϊһ��������������5����ȡֵ��32����������ڱ�����ж��Զ���ؿ��Ƿ����̶ȷ��Ϲ淶
						reports_createcustomlevel_errors(errornum);//����errornum���б���
						if (errornum == 31)//��whetherclose_whetherin��deltaw��deltal��bnum_equal_tnum��havecharacterȫΪ1��������Զ���Ĺؿ������̶ȷ��Ϲ淶���Զ���ؿ��������
						{
							ifbreak = true;//�����ж��Ƿ�����Զ���ؿ��ı�����Ϊ��
							string encode = encode_createcustomlevel(w_b_t, c, mintop, minleft, r);//���Զ���ؿ�����Ϣ���б���
							//���Զ���ؿ����롢�Զ���ؿ������������ļ�
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
				if (x >= 1 * 40 && x <= 24 * 40 && y >= 1 * 40 && y <= 14 * 40 && nowbutton >= 0 && nowbutton <= 3)//�㵽�Զ��廭��
				{
					int indexx = y / 40;//����ڵ�ͼ�ϵĺ�����
					int indexy = x / 40;//����ڵ�ͼ�ϵ�������
					if (nowbutton == 0)//��ǰѡ��ǽ�巽��
					{
						pair<int, int> windex = { indexx,indexy };//ǽ������
						if (usedtargetindex.count(windex) || usedboxindex.count(windex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(windex))//����ǰλ���ѱ�ռ�ã��򲻽����κβ���
						{
							break;
						}
						usedwallindex.insert(windex);//��ǽ���������ǽ���꼯��
						w_b_t[0].insert(windex);//��ǽ���������ǽ���꼯��
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[0], 0, 0);//�ڵ�ǰλ�û���ǽ
						//����ǽ����С�ڵ�ͼ�ϵ������ꡢ����ڵ�ͼ�ϵ������ꡢ��С�ڵ�ͼ�ϵĺ����ꡢ����ڵ�ͼ�ϵĺ�����
						MinLeft.emplace(indexy);
						MaxRight.emplace(indexy);
						MinTop.emplace(indexx);
						MaxBottom.emplace(indexx);
						minleft = min(minleft, indexy);
						maxright = max(maxright, indexy);
						mintop = min(mintop, indexx);
						maxbottom = max(maxbottom, indexx);
					}
					else if (nowbutton == 1)//��ǰѡ�����ӷ���
					{
						pair<int, int> bindex = { indexx,indexy };//��������
						if (usedboxindex.count(bindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(bindex))//����ǰλ��û��Ŀ���λ���ѱ��������ռ�ã��򲻽����κβ���
						{
							break;
						}
						usedboxindex.insert(bindex);//��������������������꼯��
						w_b_t[1].insert(bindex);//��������������������꼯��
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[usedtargetindex.count(bindex) ? 4 : 1], 0, 0);//�ڵ�ǰλ�û������ӣ�����ǰλ����Ŀ���λ������Ƶ���Ŀ���λ������
						if (usedtargetindex.count(bindex))//����ǰλ����Ŀ���λ
						{
							usedbox_targetindex.insert(bindex);//������������뵽��Ŀ���λ���������꼯��
							r++;//����Ŀ���λ����������һ
						}
					}
					else if (nowbutton == 2)//��ǰѡ��Ŀ���λ����
					{
						pair<int, int> tindex = { indexx,indexy };//Ŀ���λ����
						if (usedtargetindex.count(tindex) || usedboxindex.count(tindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(tindex))//����ǰλ���ѱ�ռ�ã��򲻽����κβ���
						{
							break;
						}
						usedtargetindex.insert(tindex);//��Ŀ���λ�������Ŀ���λ���꼯��
						w_b_t[2].insert(tindex);//��Ŀ���λ�������Ŀ���λ���꼯��
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//�ڵ�ǰλ�û���Ŀ���λ
					}
					else if (nowbutton == 3)//��ǰѡ�н�ɫ����
					{
						pair<int, int> cindex = { indexx,indexy };//��ǰ��ɫ����
						if (usedboxindex.count(cindex) || (characterindex.first == indexx && characterindex.second == indexy) || usedwallindex.count(cindex))//����ǰλ��û��Ŀ���λ���ѱ��������ռ�ã��򲻽����κβ���
						{
							break;
						}
						c.setcharacter(indexx, indexy, 4);//���ý�ɫ��Ϣ������Ĭ��Ϊ����
						pair<int, int> preindex = characterindex;//��һ����ɫ����
						int preimageindex = usedtargetindex.count(preindex) ? 2 : 6;//��ǰӦ����һ����ɫλ�ô����õ�ͼƬ����������һ����ɫ���괦��Ŀ���λ����ñ���Ϊ2������Ϊ6
						putimage(preindex.second * 40, preindex.first * 40, 40, 40, &images_createcustomlevel[preimageindex], 0, 0);//������һ����ɫλ�ô���ͼƬ
						characterindex = cindex;//����ǰ��ɫ���괫����ɫ����
						putimage(characterindex.second * 40, characterindex.first * 40, 40, 40, &images_createcustomlevel[usedtargetindex.count(characterindex) ? 5 : 3], 0, 0);//���ĵ�ǰ��ɫλ�ô�ͼƬ������ǰ��ɫλ����Ŀ���λ����ͼƬ����Ϊ5������Ϊ3
					}
					break;
				};
				break;
			case WM_RBUTTONDOWN://�����Ҽ�
				x1 = msg.x;
				y1 = msg.y;
				if (x1 >= 1 * 40 && x1 <= 24 * 40 && y1 >= 1 * 40 && y1 <= 14 * 40)//��������Զ��廭����Χ��
				{
					int indexx = y / 40;//����ڵ�ͼ�ϵĺ�����
					int indexy = x / 40;//����ڵ�ͼ�ϵ�������
					pair<int, int> nowindexpair = { indexx,indexy };//��ǰ�ڵ�ͼ�ϵ�����
					if (usedwallindex.count(nowindexpair))//��ǰλ�ô�Ϊǽ
					{
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//��ǰλ��Ϳ��
						//ɾ������ǽ���꼯���еĵ�ǰǽ����
						usedwallindex.erase(nowindexpair);
						w_b_t[0].erase(nowindexpair);
						//����ǽ����С�ڵ�ͼ�ϵ������ꡢ����ڵ�ͼ�ϵ������ꡢ��С�ڵ�ͼ�ϵĺ����ꡢ����ڵ�ͼ�ϵĺ�����
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
					if (characterindex.first == indexx && characterindex.second == indexy)//��ǰλ�ô�Ϊ��ɫ
					{
						if (usedtargetindex.count(nowindexpair))//����ǰλ�ô�����Ŀ���λ
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//��ǰλ�ô�ͼƬ����ΪĿ���λͼƬ
						}
						else
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//��ǰλ�ô�Ϳ��
						}
						c.setcharacter(-1, -1, -1);//��ɫ�������Ϊ{-1��-1}���������Ϊ-1
						characterindex = { -1,-1 };//��ɫ�������Ϊ{-1��-1}
						break;
					}
					if (usedboxindex.count(nowindexpair))//��ǰλ�ô�Ϊ����
					{
						if (usedbox_targetindex.count(nowindexpair))//����ǰλ�ô�����Ŀ���λ
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[2], 0, 0);//��ǰλ�ô�ͼƬ����ΪĿ���λͼƬ
							usedbox_targetindex.erase(nowindexpair);//ɾ���ﵽĿ���λ���������꼯���еĵ�ǰ����
							r--;//�ﵽĿ���λ����������һ
						}
						else
						{
							putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//��ǰλ�ô�Ϳ��
						}
						//ɾ�������������꼯���еĵ�ǰǽ����
						usedboxindex.erase(nowindexpair);
						w_b_t[1].erase(nowindexpair);
						break;
					}
					if (usedtargetindex.count(nowindexpair))//��ǰλ�ô�ΪĿ���λ
					{
						putimage(indexy * 40, indexx * 40, 40, 40, &images_createcustomlevel[6], 0, 0);//��ǰλ�ô�Ϳ��
						//ɾ������Ŀ���λ���꼯���еĵ�ǰĿ���λ����
						usedtargetindex.erase(nowindexpair);
						w_b_t[2].erase(nowindexpair);
						break;
					}
					break;
				};
				break;
			}
			if (ifbreak)break;//������Զ���ؿ������˳��Զ��幦�ܽ���ѭ��
		}
	}
}

void DrawSelectCustomLevelInterface(int c)//�����Զ���ؿ�ѡ�ؽ���
{
	setbkcolor(0x00B5E51D);//���ñ���ɫΪ0x00B5E51D
	cleardevice();//��մ��ڣ�ʹ����ɫΪ0x00B5E51D
	setlinecolor(BLACK);//����������ɫΪ��ɫ
	settextcolor(BLACK);//�����ı���ɫΪ��ɫ
	for (int i = 0; i <= c + 1; i++)//���Ʒָ���
	{
		line(0, i * 30, 500, i * 30);
	}
	for (int i = 0; i < c; i++)//���ļ�����ȡ�ؿ����������δ�ӡ�ؿ���
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
	outtextxy(5, c * 30 + 5, "����");//���ذ�ť
}

vector<string> DrawLoginInputInterface(bool& ifcancel)//���Ƶ�¼��������棬�������˻������������ֵ
{
	int x0 = 240;//���⣨�����¼�������ϽǺ�����
	int y0 = 85;//���⣨�����¼�������Ͻ�������
	int x1 = 100;//�˺���������ϽǺ�����
	int y1 = 185;//�˺���������Ͻ�������
	int x2 = 100;//������������ϽǺ�����
	int y2 = 275;//������������Ͻ�������
	int x3 = 100;//ȷ����ť���ϽǺ�����
	int y3 = 365;//ȷ����ť���Ͻ�������
	int x4 = 380;//ȡ����ť���ϽǺ�����
	int y4 = 365;//ȡ����ť���Ͻ�������
	int w = 400;//����򳤶�
	int h = 30;//�������
	int LineColor = BLACK;//ֱ����ɫ
	int TextColor = BLACK;//�ı���ɫ
	int BackgroundColor = WHITE;//������ɫ
	char account_number[1024] = { '\0' };//���ڴ洢�˺��ı�
	char account_password[1024] = { '\0' };//���ڴ洢�����ı�
	char covered_account_password[1024] = { '\0' };//�Ѽ��ܸ��ǵ�����
	int account_number_length = 0;//������˺��ı�����
	int account_password_length = 0;//����������ı�����
	int covered_account_password_length = 0;//�Ѽ��ܸ��ǵ����볤��
	int index1 = 0;//��ǰ������˺�������е�λ��
	int index2 = 0;//��ǰ���������������е�λ��
	bool first_second = true;//����ڵ�һ������ǵڶ��������Ϊ��һ����򣬼�Ϊ�ڶ������
	bool ifcansee = false;//�����Ƿ�ɼ�
	vector<string> number_password(2, "");//���շ��ص��ַ������飬��СΪ2��0��λ�ϴ��˺ţ�1��λ�ϴ�����
	setbkcolor(BackgroundColor);//���ñ�����ɫ
	cleardevice();//��մ��ڣ��س�ʼ��������ʽ
	settextstyle(40, 0, "����");//�������������СΪ40*40���أ�����Ϊ����
	outtextxy(x0, y0, "���¼");//������⣺�����¼��
	settextstyle(20, 0, "����");//�������������СΪ20*20���أ�����Ϊ����
	settextcolor(TextColor);//�����ı���ɫ
	setlinecolor(LineColor);//����ֱ����ɫ
	rectangle(x1, y1, x1 + w, y1 + h);//�����˺������
	outtextxy(x1 + 5, y1 - 25, "�������˺ţ�");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x1+5��y1-25��
	rectangle(x2, y2, x2 + w, y2 + h);//�������������
	rectangle(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//�����������밴ť��
	outtextxy(x2 + 5, y2 - 25, "���������룺");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
	outtextxy(x2 + w + 10, y2 + 5, "��");//���������밴ť�����������
	if (!ifcansee)line(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//���б��
	rectangle(x3, y3, x3 + 120, y3 + h);//����ȷ����ť��
	rectangle(x4, y4, x4 + 120, y4 + h);//����ȡ����ť��
	outtextxy(x3 + 40, y3 + 5, "ȷ��");//���ȷ��
	outtextxy(x4 + 40, y4 + 5, "ȡ��");//���ȡ��
	line(x1 + 5 + index1 * 10, y1 + 5, x1 + 5 + index1 * 10, y1 + 25);//���ƹ��
	ExMessage msg;//�����Ϣ
	char c;//��ǰ������ַ�
	bool ifbreak = false;//�����ж��Ƿ��Ƴ�ѭ��
	while (1)//��������ѭ��
	{
		int x = first_second ? x1 : x2;
		int y = first_second ? y1 : y2;
		int index = first_second ? index1 : index2;
		outtextxy(x1 + 5, y1 + 5, account_number);//���������˺�
		outtextxy(x2 + 5, y2 + 5, !ifcansee ? covered_account_password : account_password);//������������
		settextstyle(40, 0, "����");//�������������СΪ40*40���أ�����Ϊ����
		outtextxy(x0, y0, "���¼");//������⣺�����¼��
		settextstyle(20, 0, "����");//�������������СΪ20*20���أ�����Ϊ����
		rectangle(x1, y1, x1 + w, y1 + h);//�����˺������
		outtextxy(x1 + 5, y1 - 25, "�������˺ţ�");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x1+5��y1-25��
		rectangle(x2, y2, x2 + w, y2 + h);//�������������
		rectangle(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//�����������밴ť��
		outtextxy(x2 + 5, y2 - 25, "���������룺");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
		outtextxy(x2 + w + 10, y2 + 5, "��");//���������밴ť�����������
		if (!ifcansee)line(x2 + w + 5, y2, x2 + w + h + 5, y2 + h);//���б��
		rectangle(x3, y3, x3 + 120, y3 + h);//����ȷ����ť��
		rectangle(x4, y4, x4 + 120, y4 + h);//����ȡ����ť��
		outtextxy(x3 + 40, y3 + 5, "ȷ��");//���ȷ��
		outtextxy(x4 + 40, y4 + 5, "ȡ��");//���ȡ��
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//���ƹ��
		if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
		{
			switch (msg.message)//�ж������Ϣ
			{
			case WM_LBUTTONDOWN://����������
				cleardevice();
				int X = msg.x;//����ʱ��ָ�򴰿�������λ�õĺ�����
				int Y = msg.y;//����ʱ��ָ�򴰿�������λ�õ�������
				if (X >= x3 && X <= x3 + 120 && Y >= y3 && Y <= y3 + h)//�����ȷ����ť��Χ��
				{
					number_password[0] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//�洢��ǰ���˺��ı���Ϣ
					{
						number_password[0].push_back(account_number[i]);
					}
					if (number_password[0].size() == 0)//��δ�����˺�
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x1, y1 + h + 5, "�˺�δ���룬�������˺�");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					if (!users_accountnumber2password.count(number_password[0]))//���û�������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x1, y1 + h + 5, "�����ڸ��û�");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					number_password[1] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
					{
						number_password[1].push_back(account_password[i]);
					}
					number_password[1] = encrypt_password(number_password[1]);
					if (number_password[1].size() == 0)//��δ��������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x2, y2 + h + 5, "����δ���룬����������");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					if (users_accountnumber2password[number_password[0]] != number_password[1])//���������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x2, y2 + h + 5, "�������");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					break;
				};
				if (X >= x4 && X <= x4 + 120 && Y >= y4 && Y <= y4 + h)//�����ȡ����ť��Χ��
				{
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					ifcancel = true;//�Ƿ�ȡ����Ϊ��
					break;
				};
				if (X >= x2 + w + 5 && X <= x2 + w + h + 5 && Y >= y2 && Y <= y2 + h)//������������밴ť��Χ��
				{
					cleardevice();
					ifcansee ^= 1;//���������Ƿ�ɼ�
					break;
				};
				if (X >= x1 && X <= x1 + w && Y >= y1 && Y <= y1 + h)//������˺������Χ��
				{
					first_second = true;//��������ת���˺������
					index1 = account_number_length;//�������λ�÷ŵ�������ı�ĩβ
					break;
				};
				if (X >= x2 && X <= x2 + w && Y >= y2 && Y <= y2 + h)//��������������Χ��
				{
					first_second = false;//��������ת�����������
					index2 = account_password_length;//�������λ�÷ŵ�������ı�ĩβ
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//���񰴼���Ϣ
		{
			c = _getch();//����ǰ�������ַ������ַ�c
			if (first_second)//�����˺�
			{
				if (c == '\b' && account_number_length > 0 && index1 > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
				{
					if (index1 == account_number_length)//���λ���������ı���ĩβ
					{
						cleardevice();
						account_number[--account_number_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
						index1--;//���λ�ü�һ
					}
					else//���λ�ò��������ı�ĩβ
					{
						cleardevice();
						for (int i = index1 - 1; i < account_number_length; i++)account_number[i] = account_number[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
						index1--;//���λ�ü�һ
						account_number[--account_number_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					}
				}
				else if (c == '\b' && account_number_length == 0)//����backspace�����������ı���ɾ��
				{
					cleardevice();
					continue;//����ѭ��
				}
				else if (c == '\r')//�����س�
				{
					cleardevice();
					first_second = false;//������������
					continue;
				}
				else
				{
					if (c == 75 && index1 > 0)//��������ҹ�껹������
					{
						index1--;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (c == 77 && index1 < account_number_length)//�����Ҽ��ҹ�껹������
					{
						index1++;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (index1 == account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//���������ҹ�����ı�ĩβ
					{
						index1++;//���λ�ü�һ
						account_number[account_number_length++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
						account_number[account_number_length] = '\0';//��֤�ı�����н�����
						cleardevice();
						continue;
					}
					if (index1 != account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//���������ҹ�겻���ı�ĩβ
					{
						for (int i = account_number_length; i > index1; i--)account_number[i] = account_number[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
						account_number[index1++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
						account_number_length++;//�ı����ȼ�һ
						cleardevice();
						continue;
					}
				}
			}
			else//��������
			{
				if (c == '\b' && account_password_length > 0 && index2 > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
				{
					if (index2 == account_password_length)//���λ���������ı���ĩβ
					{
						cleardevice();
						account_password[--account_password_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
						index2--;//���λ�ü�һ
					}
					else//���λ�ò��������ı�ĩβ
					{
						cleardevice();
						for (int i = index2 - 1; i < account_password_length; i++)account_password[i] = account_password[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
						index2--;//���λ�ü�һ
						account_password[--account_password_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					}
					covered_account_password[--covered_account_password_length] = '\0';//���ǵ�����Ҳ�˸�
				}
				else if (c == '\b' && account_password_length == 0)//����backspace�����������ı���ɾ��
				{
					cleardevice();
					continue;//����ѭ��
				}
				else
				{
					if (c == 75 && index2 > 0)//��������ҹ�껹������
					{
						index2--;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (c == 77 && index2 < account_password_length)//�����Ҽ��ҹ�껹������
					{
						index2++;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (index2 == account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//����֧�ֵ��ı��ҹ�����ı�ĩβ
					{
						index2++;//���λ�ü�һ
						account_password[account_password_length++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
						account_password[account_password_length] = '\0';//��֤�ı�����н�����
						covered_account_password[covered_account_password_length++] = '*';//���������ı����һ����*��
						cleardevice();
						continue;
					}
					if (index2 != account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//����֧�ֵ��ı��ҹ�겻���ı�ĩβ
					{
						for (int i = account_password_length; i > index2; i--)account_password[i] = account_password[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
						account_password[index2++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
						account_password_length++;//�ı����ȼ�һ
						covered_account_password[covered_account_password_length++] = '*';//���������ı����һ����*��
						cleardevice();
						continue;
					}
				}
			}
			if (c == '\r')//�����س�
			{
				while (1)
				{
					number_password[0] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//�洢��ǰ���˺��ı���Ϣ
					{
						number_password[0].push_back(account_number[i]);
					}
					if (number_password[0].size() == 0)//��δ�����˺�
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x1, y1 + h + 5, "�˺�δ���룬�������˺�");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					if (!users_accountnumber2password.count(number_password[0]))//���û�������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x1, y1 + h + 5, "�����ڸ��û�");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					number_password[1] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
					{
						number_password[1].push_back(account_password[i]);
					}
					number_password[1] = encrypt_password(number_password[1]);
					if (number_password[1].size() == 0)//��δ��������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x2, y2 + h + 5, "����δ���룬����������");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					if (users_accountnumber2password[number_password[0]] != number_password[1])//���������
					{
						settextcolor(RED);
						settextstyle(15, 0, "����");
						outtextxy(x2, y2 + h + 5, "�������");
						settextcolor(BLACK);
						settextstyle(20, 0, "����");
						break;
					}
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					break;
				}
			};
		}
		if (ifbreak)break;//���ڿ��Ƽ���ѭ�����˳�ѭ��
	}
	return number_password;
}

vector<string> DrawRegisterInputInterface(bool& ifcancel)//����ע����Ϣ������棬������ע����Ϣ
{
	int x0 = 240;//���⣨����ע�ᡱ�����ϽǺ�����
	int y0 = 85;//���⣨����ע�ᡱ�����Ͻ�������
	int x1 = 100;//�û�����������ϽǺ�����
	int y1 = 185;//�û�����������Ͻ�������
	int x2 = 100;//�˺���������ϽǺ�����
	int y2 = 275;//�˺���������Ͻ�������
	int x3 = 100;//������������ϽǺ�����
	int y3 = 365;//������������Ͻ�������
	int x4 = 100;//ȷ����ť���ϽǺ�����
	int y4 = 455;//ȷ����ť���Ͻ�������
	int x5 = 380;//ȡ����ť���ϽǺ�����
	int y5 = 455;//ȡ����ť���Ͻ�������
	int w = 400;//����򳤶�
	int h = 30;//�������
	int LineColor = BLACK;//ֱ����ɫ
	int TextColor = BLACK;//�ı���ɫ
	int BackgroundColor = WHITE;//������ɫ
	char user_name[1024] = { '\0' };//���ڴ洢�û����ı�
	char account_number[1024] = { '\0' };//���ڴ洢�˺��ı�
	char account_password[1024] = { '\0' };//���ڴ洢�����ı�
	char covered_account_password[1024] = { '\0' };//�Ѽ��ܸ��ǵ�����
	int user_name_length = 0;//������û�������
	int account_number_length = 0;//������˺��ı�����
	int account_password_length = 0;//����������ı�����
	int covered_account_password_length = 0;//�Ѽ��ܸ��ǵ����볤��
	int index1 = 0;//��ǰ������û���������е�λ��
	int index2 = 0;//��ǰ������˺�������е�λ��
	int index3 = 0;//��ǰ���������������е�λ��
	int first_second_third = 0;//�жϹ���ڵڼ������0Ϊ��һ�����1Ϊ�ڶ������2Ϊ���������
	bool ifcansee = false;//�����Ƿ�ɼ�
	vector<string> name_number_password(3, "");//���շ��ص��ַ������飬��СΪ3��0��λ�ϴ��û�����1��λ�ϴ��˺ţ�2��λ�ϴ�����
	setbkcolor(BackgroundColor);//���ñ�����ɫ
	cleardevice();//��մ��ڣ��س�ʼ��������ʽ
	settextstyle(40, 0, "����");//�������������СΪ40*40���أ�����Ϊ����
	outtextxy(x0, y0, "��ע��");//������⣺�����¼��
	settextstyle(20, 0, "����");//�������������СΪ20*20���أ�����Ϊ����
	settextcolor(TextColor);//�����ı���ɫ
	setlinecolor(LineColor);//����ֱ����ɫ
	rectangle(x1, y1, x1 + w, y1 + h);//�����û��������
	outtextxy(x1 + 5, y1 - 25, "�������û���(֧��СдӢ����ĸ������)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x1+5��y1-25��
	rectangle(x2, y2, x2 + w, y2 + h);//�����˺������
	outtextxy(x2 + 5, y2 - 25, "�������˺�(����)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
	rectangle(x3, y3, x3 + w, y3 + h);//�������������
	rectangle(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//�����������밴ť��
	outtextxy(x3 + 5, y3 - 25, "����������(֧��СдӢ����ĸ ���� ! . * @)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
	outtextxy(x3 + w + 10, y3 + 5, "��");//���������밴ť�����������
	if (!ifcansee)line(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//���б��
	rectangle(x4, y4, x4 + 120, y4 + h);//����ȷ����ť��
	rectangle(x5, y5, x5 + 120, y5 + h);//����ȡ����ť��
	outtextxy(x4 + 40, y4 + 5, "ȷ��");//���ȷ��
	outtextxy(x5 + 40, y5 + 5, "ȡ��");//���ȡ��
	line(x1 + 5 + index1 * 10, y1 + 5, x1 + 5 + index1 * 10, y1 + 25);//���ƹ��
	ExMessage msg;//�����Ϣ
	char c;//��ǰ������ַ�
	bool ifbreak = false;//�����ж��Ƿ��Ƴ�ѭ��
	int index = NULL;//���λ��
	while (1)//��������ѭ��
	{
		int x = 100;
		int y = 185 + first_second_third * 90;
		if (first_second_third == 0)index = index1;
		if (first_second_third == 1)index = index2;
		if (first_second_third == 2)index = index3;
		outtextxy(x1 + 5, y1 + 5, user_name);//���������û���
		outtextxy(x2 + 5, y2 + 5, account_number);//���������˺�
		outtextxy(x3 + 5, y3 + 5, !ifcansee ? covered_account_password : account_password);//������������
		settextstyle(40, 0, "����");//�������������СΪ40*40���أ�����Ϊ����
		outtextxy(x0, y0, "��ע��");//������⣺�����¼��
		settextstyle(20, 0, "����");//�������������СΪ20*20���أ�����Ϊ����
		rectangle(x1, y1, x1 + w, y1 + h);//�����û��������
		outtextxy(x1 + 5, y1 - 25, "�������û���(֧��СдӢ����ĸ������)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x1+5��y1-25��
		rectangle(x2, y2, x2 + w, y2 + h);//�����˺������
		outtextxy(x2 + 5, y2 - 25, "�������˺�(����)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
		rectangle(x3, y3, x3 + w, y3 + h);//�������������
		rectangle(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//�����������밴ť��
		outtextxy(x3 + 5, y3 - 25, "����������(֧��СдӢ����ĸ ���� ! . * @)��");//�����ʾ���ʼ���꣨���Ͻǣ�Ϊ��x2+5��y2-25��
		outtextxy(x3 + w + 10, y3 + 5, "��");//���������밴ť�����������
		if (!ifcansee)line(x3 + w + 5, y3, x3 + w + h + 5, y3 + h);//���б��
		rectangle(x4, y4, x4 + 120, y4 + h);//����ȷ����ť��
		rectangle(x5, y5, x5 + 120, y5 + h);//����ȡ����ť��
		outtextxy(x4 + 40, y4 + 5, "ȷ��");//���ȷ��
		outtextxy(x5 + 40, y5 + 5, "ȡ��");//���ȡ��
		line(x + 5 + index * 10, y + 5, x + 5 + index * 10, y + 25);//���ƹ��
		if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
		{
			switch (msg.message)//�ж������Ϣ
			{
			case WM_LBUTTONDOWN://����������
				cleardevice();
				int X = msg.x;//����ʱ��ָ�򴰿�������λ�õĺ�����
				int Y = msg.y;//����ʱ��ָ�򴰿�������λ�õ�������
				if (X >= x4 && X <= x4 + 120 && Y >= y4 && Y <= y4 + h)//�����ȷ����ť��Χ��
				{
					name_number_password[0] = "";
					for (int i = 0; i < 1024 && user_name[i] != '\0'; i++)//�洢��ǰ���û����ı���Ϣ
					{
						name_number_password[0].push_back(user_name[i]);
					}
					name_number_password[1] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//�洢��ǰ���˺��ı���Ϣ
					{
						name_number_password[1].push_back(account_number[i]);
					}
					name_number_password[2] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
					{
						name_number_password[2].push_back(account_password[i]);
					}
					name_number_password[2] = encrypt_password(name_number_password[2]);
					int existname = !(users_names.count(name_number_password[0]));//�û����Ƿ����
					int existnumber = !(users_accountnumber2password.count(name_number_password[1]));//�˺��Ƿ��ѱ�ע��
					int havename = !(name_number_password[0].size() == 0);//�Ƿ��������û���
					int havenumber = !(name_number_password[1].size() == 0);//�Ƿ��������˺�
					int havepassword = !(name_number_password[2].size() == 0);//�Ƿ�����������
					if (havenumber == 0)existnumber = 0;
					if (havename == 0)existname = 0;
					int errornum = (existname << 4) | (existnumber << 3) | (havename << 2) | (havenumber << 1) | (havepassword);
					settextcolor(RED);
					settextstyle(15, 0, "����");
					switch (errornum)
					{
					case 0:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 1:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 2:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 3:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						break;
					case 4:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 5:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 6:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 7:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						break;
					case 8:
						break;
					case 9:
						break;
					case 10:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 11:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						break;
					case 12:
						break;
					case 13:
						break;
					case 14:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 15:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
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
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 21:
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 22:
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 23:
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
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
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 31:
						ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
						break;
					}
					settextcolor(BLACK);
					settextstyle(20, 0, "����");
					break;
				};
				if (X >= x5 && X <= x5 + 120 && Y >= y5 && Y <= y5 + h)//�����ȡ����ť��Χ��
				{
					ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
					ifcancel = true;//�Ƿ�ȡ����Ϊ��
					break;
				};
				if (X >= x3 + w + 5 && X <= x3 + w + h + 5 && Y >= y3 && Y <= y3 + h)//������������밴ť��Χ��
				{
					cleardevice();
					ifcansee ^= 1;//���������Ƿ�ɼ�
					break;
				};
				if (X >= x1 && X <= x1 + w && Y >= y1 && Y <= y1 + h)//������û��������Χ��
				{
					first_second_third = 0;//��������ת���û��������
					index1 = user_name_length;//�������λ�÷ŵ�������ı�ĩβ
					break;
				};
				if (X >= x2 && X <= x2 + w && Y >= y2 && Y <= y2 + h)//������˺������Χ��
				{
					first_second_third = 1;//��������ת���˺������
					index2 = account_number_length;//�������λ�÷ŵ�������ı�ĩβ
					break;
				};
				if (X >= x3 && X <= x3 + w && Y >= y3 && Y <= y3 + h)//��������������Χ��
				{
					first_second_third = 2;//��������ת�����������
					index3 = account_password_length;//�������λ�÷ŵ�������ı�ĩβ
					break;
				};
				break;
			}
			if (ifbreak)break;
		}
		if (_kbhit())//���񰴼���Ϣ
		{
			c = _getch();//����ǰ�������ַ������ַ�c
			switch (first_second_third)
			{
			case 0://�����û���
				if (c == '\b' && user_name_length > 0 && index1 > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
				{
					if (index1 == user_name_length)//���λ���������ı���ĩβ
					{
						cleardevice();
						user_name[--user_name_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
						index1--;//���λ�ü�һ
					}
					else//���λ�ò��������ı�ĩβ
					{
						cleardevice();
						for (int i = index1 - 1; i < user_name_length; i++)user_name[i] = user_name[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
						index1--;//���λ�ü�һ
						user_name[--user_name_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					}
				}
				else if (c == '\b' && user_name_length == 0)//����backspace�����������ı���ɾ��
				{
					cleardevice();
					continue;//����ѭ��
				}
				else if (c == '\r')//�����س�
				{
					cleardevice();
					first_second_third++;//�����˺�����
					continue;
				}
				else
				{
					if (c == 75 && index1 > 0)//��������ҹ�껹������
					{
						index1--;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (c == 77 && index1 < user_name_length)//�����Ҽ��ҹ�껹������
					{
						index1++;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (index1 == user_name_length && user_name_length < 39 && ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))//����֧�ֵ��ı��ҹ�����ı�ĩβ
					{
						index1++;//���λ�ü�һ
						user_name[user_name_length++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
						user_name[user_name_length] = '\0';//��֤�ı�����н�����
						cleardevice();
						continue;
					}
					if (index1 != user_name_length && user_name_length < 39 && ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')))//����֧�ֵ��ı��ҹ�겻���ı�ĩβ
					{
						for (int i = user_name_length; i > index1; i--)user_name[i] = user_name[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
						user_name[index1++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
						user_name_length++;//�ı����ȼ�һ
						cleardevice();
						continue;
					}
				}
				break;
			case 1://�����˺�
				if (c == '\b' && account_number_length > 0 && index2 > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
				{
					if (index2 == account_number_length)//���λ���������ı���ĩβ
					{
						cleardevice();
						account_number[--account_number_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
						index2--;//���λ�ü�һ
					}
					else//���λ�ò��������ı�ĩβ
					{
						cleardevice();
						for (int i = index2 - 1; i < account_number_length; i++)account_number[i] = account_number[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
						index2--;//���λ�ü�һ
						account_number[--account_number_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					}
				}
				else if (c == '\b' && account_number_length == 0)//����backspace�����������ı���ɾ��
				{
					cleardevice();
					continue;//����ѭ��
				}
				else if (c == '\r')//�����س�
				{
					cleardevice();
					first_second_third++;//������������
					continue;
				}
				else
				{
					if (c == 75 && index2 > 0)//��������ҹ�껹������
					{
						index2--;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (c == 77 && index2 < account_number_length)//�����Ҽ��ҹ�껹������
					{
						index2++;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (index2 == account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//���������ҹ�����ı�ĩβ
					{
						index2++;//���λ�ü�һ
						account_number[account_number_length++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
						account_number[account_number_length] = '\0';//��֤�ı�����н�����
						cleardevice();
						continue;
					}
					if (index2 != account_number_length && account_number_length < 39 && c >= '0' && c <= '9')//���������ҹ�겻���ı�ĩβ
					{
						for (int i = account_number_length; i > index2; i--)account_number[i] = account_number[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
						account_number[index2++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
						account_number_length++;//�ı����ȼ�һ
						cleardevice();
						continue;
					}
				}
				break;
			case 2://��������
				if (c == '\b' && account_password_length > 0 && index3 > 0)//����backspace�ҵ�ǰ������й��֮ǰ�п�ɾ���ַ�
				{
					if (index3 == account_password_length)//���λ���������ı���ĩβ
					{
						cleardevice();
						account_password[--account_password_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
						index3--;//���λ�ü�һ
					}
					else//���λ�ò��������ı�ĩβ
					{
						cleardevice();
						for (int i = index3 - 1; i < account_password_length; i++)account_password[i] = account_password[i + 1];//���֮����ַ�������ǰ�ƶ�һ��
						index3--;//���λ�ü�һ
						account_password[--account_password_length] = '\0';//�����һ���ַ���Ϊ�������������ı����ȼ�һ
					}
					covered_account_password[--covered_account_password_length] = '\0';//���ǵ�����Ҳ�˸�
				}
				else if (c == '\b' && account_password_length == 0)//����backspace�����������ı���ɾ��
				{
					cleardevice();
					continue;//����ѭ��
				}
				else if (c == '\r')//�����س�
				{
					name_number_password[0] = "";
					for (int i = 0; i < 1024 && user_name[i] != '\0'; i++)//�洢��ǰ���û����ı���Ϣ
					{
						name_number_password[0].push_back(user_name[i]);
					}
					name_number_password[1] = "";
					for (int i = 0; i < 1024 && account_number[i] != '\0'; i++)//�洢��ǰ���˺��ı���Ϣ
					{
						name_number_password[1].push_back(account_number[i]);
					}
					name_number_password[2] = "";
					for (int i = 0; i < 1024 && account_password[i] != '\0'; i++)//�洢��ǰ�������ı���Ϣ
					{
						name_number_password[2].push_back(account_password[i]);
					}
					name_number_password[2] = encrypt_password(name_number_password[2]);
					int existname = !(users_names.count(name_number_password[0]));//�û����Ƿ����
					int existnumber = !(users_accountnumber2password.count(name_number_password[1]));//�˺��Ƿ��ѱ�ע��
					int havename = !(name_number_password[0].size() == 0);//�Ƿ��������û���
					int havenumber = !(name_number_password[1].size() == 0);//�Ƿ��������˺�
					int havepassword = !(name_number_password[2].size() == 0);//�Ƿ�����������
					if (havenumber == 0)existnumber = 0;
					if (havename == 0)existname = 0;
					int errornum = (existname << 4) | (existnumber << 3) | (havename << 2) | (havenumber << 1) | (havepassword);
					settextcolor(RED);
					settextstyle(15, 0, "����");
					switch (errornum)
					{
					case 0:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 1:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 2:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 3:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						break;
					case 4:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 5:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 6:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 7:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						break;
					case 8:
						break;
					case 9:
						break;
					case 10:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 11:
						outtextxy(x1, y1 + h + 5, "�û���δ���룬�������û���");
						break;
					case 12:
						break;
					case 13:
						break;
					case 14:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 15:
						outtextxy(x1, y1 + h + 5, "���û����Ѵ���");
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
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 21:
						outtextxy(x2, y2 + h + 5, "�˺�δ���룬�������˺�");
						break;
					case 22:
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 23:
						outtextxy(x2, y2 + h + 5, "���˺��ѱ�ע��");
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
						outtextxy(x3, y3 + h + 5, "����δ���룬����������");
						break;
					case 31:
						ifbreak = true;//�ж��Ƿ��˳�ѭ���ı�����Ϊ�棬���˳�����ѭ��
						break;
					}
					settextcolor(BLACK);
					settextstyle(20, 0, "����");
					break;
				}
				else
				{
					if (c == 75 && index3 > 0)//��������ҹ�껹������
					{
						index3--;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (c == 77 && index3 < account_password_length)//�����Ҽ��ҹ�껹������
					{
						index3++;//���λ�ü�һ
						cleardevice();
						continue;
					}
					if (index3 == account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//����֧�ֵ��ı��ҹ�����ı�ĩβ
					{
						index3++;//���λ�ü�һ
						account_password[account_password_length++] = c;//ʹ������ı�ĩβΪ��ǰ�ַ����ı����ȼ�һ
						account_password[account_password_length] = '\0';//��֤�ı�����н�����
						covered_account_password[covered_account_password_length++] = '*';//���������ı����һ����*��
						cleardevice();
						continue;
					}
					if (index3 != account_password_length && account_password_length < 39 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || c == '!' || c == '.' || c == '*' || c == '@'))//����֧�ֵ��ı��ҹ�겻���ı�ĩβ
					{
						for (int i = account_password_length; i > index3; i--)account_password[i] = account_password[i - 1];//���֮����ַ�ȫ����������ƶ�һ��
						account_password[index3++] = c;//���λ��Ϊ��ǰ�ַ���ʹ���λ�ü�һ
						account_password_length++;//�ı����ȼ�һ
						covered_account_password[covered_account_password_length++] = '*';//���������ı����һ����*��
						cleardevice();
						continue;
					}
				}
				break;
			}
		}
		if (ifbreak)break;//���ڿ��Ƽ���ѭ�����˳�ѭ��
	}
	return name_number_password;
}

void DrawTheRankingList()//�������а�ҳ��
{
	setbkcolor(RGB(53, 255, 175));//���ñ���ɫΪRGB(53, 255, 175)
	cleardevice();//��մ��ڣ�ʹ����ɫ��ΪRGB(53, 255, 175)
	setlinecolor(BLACK);//����������ɫΪ��ɫ
	settextcolor(BLACK);//�����ı���ɫΪ��ɫ
	settextstyle(20, 0, "����");//����������ʽ
	outtextxy(5, 5, "����");//�ڴ�������{5��5}����ӡ������������
	outtextxy(5 + 100, 5, "���");//�ڴ�������{105��5}����ӡ����ҡ�����
	outtextxy(5 + 500, 5, "�ܷ�");//�ڴ�������{505��5}����ӡ���ܷ֡�����
	int n = user_totalscore.size() + 2;//����Ϊuser_totalscore.size() + 2
	for (int i = 0; i <= n; i++)//�����зָ���
	{
		line(0, i * 30, 1600, i * 30);
	}
	line(100, 0, 100, (n - 1) * 30);//�����зָ���
	line(500, 0, 500, (n - 1) * 30);//�����зָ���
	line(900, 0, 900, (n - 1) * 30);//�����зָ���
	outtextxy(5, (n - 1) * 30 + 5, "����");//�ڴ�������{5, (n - 1) * 30 + 5}����ӡ�����ء������������ذ�ť
	vector<pair<int, string>> username_score;//����-�û�������
	map<string, string>::iterator iter = user_totalscore.begin();//����һ��map<string,string>�ĵ�����������ʼ��Ϊuser_totalscore��ϣ�����ʼλ��ָ��
	while (iter != user_totalscore.end())//�����û��ֹܷ�ϣ��
	{
		username_score.emplace_back(stoi(iter->second), iter->first);//�洢ÿ���û����û������ܷ�
		iter++;
	}
	sort(username_score.begin(), username_score.end(), greater<>());//�Ӵ�С�������-�û�������
	int index = 1;//��¼����
	int un = username_score.size();//����-�û�������Ĵ�С
	for (int i = 0; i < un; i++)//��������-�û������飬�����δ�ӡ��ǰλ�õ����Ρ��û������ܷ�
	{
		outtextxy(5, index * 30 + 5, to_string(index).c_str());
		outtextxy(5 + 100, index * 30 + 5, username_score[i].second.c_str());
		outtextxy(5 + 500, index * 30 + 5, to_string(username_score[i].first).c_str());
		index++;
	}
}

bool whethercircle(set<pair<int, int>> wallindex, set<pair<int, int>>& circlenode)//�ж��Զ���ؿ��е�ǽ���Ƿ��Χ��һ����
{
	if (wallindex.size() == 0)return false;//��ǽ���꼯��Ϊ�գ��򷵻�false
	int all_node_acount = wallindex.size();//���������ÿ��ǽ�����һ����㣩
	int degree_1_node_acount = 0;//��С�ڵ���1�Ľ����������ÿ��ǽ�����������ĸ������е����ⷽ��������ǽ�壬����Ϊ��ǰǽ���ڸ÷��������ߣ�Ҳ��ÿ��ǽ��ֻ�������������ĸ��������ߣ������Ϊ4����СΪ0��
	vector<pair<int, int>> orientation = { {0,-1},{-1,0},{0,1},{1,0} };//���������ĸ�����
	map<pair<int, int>, int> nodeindex_nodedegree;//ǽ�����ǽ��Ķȵ�ӳ��
	set<pair<int, int>>::iterator iter = wallindex.begin();//����һ��set<pair<int, int>>����������ʼ��Ϊwallindex���ϵ���ʼλ��ָ��
	while (iter != wallindex.end())//����wallindex����
	{
		int count = 0;//��¼ǽ�����ܵ�ǽ��
		for (int i = 0; i < 4; i++)//�����ĸ�������������ǽ�壬��count��һ
		{
			pair<int, int> wallaround = { iter->first + orientation[i].first,iter->second + orientation[i].second };
			if (wallindex.count(wallaround))count++;
		}
		nodeindex_nodedegree[{iter->first, iter->second}] = count;//�洢��ǰǽ�����꼰��ǰǽ�Ķ�
		iter++;
	}
	set<pair<int, int>> usednode;//�ѱ������Ľ��
	map<pair<int, int>, int>::iterator iter2 = nodeindex_nodedegree.begin();//����һ��map<pair<int, int>, int>����������ʼ��Ϊnodeindex_nodedegree��ϣ�����ʼλ��ָ��
	stack<pair<int, int>> node_degree_1;//�洢��С�ڵ���1�Ľ��
	while (iter2 != nodeindex_nodedegree.end())//����nodeindex_nodedegree��ϣ��
	{
		if (iter2->second <= 1)//����С�ڵ���1
		{
			node_degree_1.emplace(iter2->first);//��ǰ�ڵ�ѹջ
			usednode.insert(iter2->first);//��ǰ�ڵ���Ϊ�ѱ�����
			degree_1_node_acount++;//��С�ڵ���1�Ľ��������һ
		}
		iter2++;
	}
	while (!node_degree_1.empty())//���洢��С�ڵ���1�Ľ���ջ��Ϊ��ʱ
	{
		pair<int, int> node_degree_1_index = node_degree_1.top();//ȡ��ջ���������
		node_degree_1.pop();//ջ��Ԫ�س�ջ
		for (int i = 0; i < 4; i++)//����4������
		{
			pair<int, int> around = { node_degree_1_index.first + orientation[i].first,node_degree_1_index.second + orientation[i].second };//��ǰ���򴦵�����
			if (!usednode.count(around) && wallindex.count(around))//����ǰ���򴦵Ľ����ǽ��δ������
			{
				nodeindex_nodedegree[around]--;//��ǰ������Ľ��Ķȼ�һ
				if (nodeindex_nodedegree[around] <= 1)//����ʱ�ý��Ķ�С�ڵ���1
				{
					node_degree_1.emplace(around);//�Ѹý��ѹջ
					usednode.insert(around);//���ý����Ϊ������
					degree_1_node_acount++;//��С�ڵ���1�Ľ��������һ
				}
			}
		}
	}
	iter = wallindex.begin();
	while (iter != wallindex.end())//�ر���wallindex���ϣ���������Χǽ�Ľ�㣬������circlenode����
	{
		if (!usednode.count(*iter))
		{
			circlenode.insert(*iter);
		}
		iter++;
	}
	return all_node_acount != degree_1_node_acount;//�����������ܽ���������ڶ�С�ڵ���1�Ľ��������˵���п����Χǽ�Ĳ��֣�����true�����򷵻�false
}

bool whetherincircle(set<pair<int, int>> wall, set<pair<int, int>> box, set<pair<int, int>> target, Character c, set<pair<int, int>>& circlenode)//�Ƿ������������ǽ��Χ�ɵĻ���
{
	set<pair<int, int>>::iterator biter = box.begin();//����һ��set<pair<int, int>>������������ʼ��Ϊbox���ϵ���ʼλ��ָ��
	set<pair<int, int>>::iterator titer = target.begin();//����һ��set<pair<int, int>>������������ʼ��Ϊtarget���ϵ���ʼλ��ָ��
	int count = 0;//��¼ĳ������������ĸ������ǽ������
	while (biter != box.end())//����box���ϣ��ж�ÿ���������������ĸ������Χǽ������������������Ϊ4�������ǰ������������Χǽ֮�ڣ�����淶�ԣ���������淶�ԣ�ֱ�ӷ���false
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
	while (titer != target.end())//����target���ϣ��ж�ÿ��Ŀ���λ���������ĸ������Χǽ������������������Ϊ4�������ǰ������Ŀ���λ��Χǽ֮�ڣ�����淶�ԣ���������淶�ԣ�ֱ�ӷ���false
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
	//�жϽ�ɫ���������ĸ������Χǽ������������������Ϊ4�������ǰ�����Ľ�ɫ��Χǽ֮�ڣ�����淶�ԣ���������淶�ԣ�ֱ�ӷ���false
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

void reports_createcustomlevel_errors(int errornum)//�Զ���ؿ�����
{
	int x = 10;//�ı���ʼ���ڴ����ϵĺ�����
	int y = 16 * 40 + 10;//�ı���ʼ���ڴ����ϵ�������
	int delta = 20;//�����ı���ľ���
	settextstyle(20, 0, "����");//����������ʽ
	setbkcolor(WHITE);//���ñ�����ɫΪ��ɫ
	settextcolor(RED);//�����ı���ɫΪ��ɫ
	switch (errornum)//��32�ֲ�ͬ�������
	{
	case 0:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 3 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 4 * delta, "�޽�ɫ");
		break;
	case 1:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 3 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 2:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 3 * delta, "�޽�ɫ");
		break;
	case 3:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "Χǽ��󳤶Ȳ���");
		break;
	case 4:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 3 * delta, "�޽�ɫ");
		break;
	case 5:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 6:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 7:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ����Ȳ���");
		break;
	case 8:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 3 * delta, "�޽�ɫ");
		break;
	case 9:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 10:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 11:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		break;
	case 12:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 13:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 14:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		outtextxy(x, y + 1 * delta, "�޽�ɫ");
		break;
	case 15:
		outtextxy(x, y, "Χǽ����ջ��������������Χǽ��");
		break;
	case 16:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 3 * delta, "�޽�ɫ");
		break;
	case 17:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 18:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 19:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "Χǽ��󳤶Ȳ���");
		break;
	case 20:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 21:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 22:
		outtextxy(x, y, "Χǽ����Ȳ���");
		outtextxy(x, y + 1 * delta, "�޽�ɫ");
		break;
	case 23:
		outtextxy(x, y, "Χǽ����Ȳ���");
		break;
	case 24:
		outtextxy(x, y, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 2 * delta, "�޽�ɫ");
		break;
	case 25:
		outtextxy(x, y, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 1 * delta, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 26:
		outtextxy(x, y, "Χǽ��󳤶Ȳ���");
		outtextxy(x, y + 1 * delta, "�޽�ɫ");
		break;
	case 27:
		outtextxy(x, y, "Χǽ��󳤶Ȳ���");
		break;
	case 28:
		outtextxy(x, y, "������������Ŀ�����������ӻ���Ŀ��");
		outtextxy(x, y + 1 * delta, "�޽�ɫ");
		break;
	case 29:
		outtextxy(x, y, "������������Ŀ�����������ӻ���Ŀ��");
		break;
	case 30:
		outtextxy(x, y, "�޽�ɫ");
		break;
	case 31:
		break;
	}
	//���ı���ʽ��������ɫ���ı���ɫ�ָ�Ϊԭ��������
	settextstyle(40, 0, "����");
	setbkcolor(RGB(182, 229, 29));
	settextcolor(BLACK);
}

string encode_createcustomlevel(map<int, set<pair<int, int>>>& wbt, Character& c, int mintop, int minleft, int reachedboxnum)//���Զ���Ĺؿ���Ϣ���б���
{
	set<pair<int, int>>::iterator witer = wbt[0].begin();//����һ��set<pair<int, int>>����������ʼ��Ϊwbt[0]���ϵ���ʼλ��ָ�룬���ڱ���ǽ����
	set<pair<int, int>>::iterator biter = wbt[1].begin();//����һ��set<pair<int, int>>����������ʼ��Ϊwbt[1]���ϵ���ʼλ��ָ�룬���ڱ�����������
	set<pair<int, int>>::iterator titer = wbt[2].begin();//����һ��set<pair<int, int>>����������ʼ��Ϊwbt[2]���ϵ���ʼλ��ָ�룬���ڱ���Ŀ���λ����
	vector<pair<int, int>> windex;//�洢ǽ����
	vector<pair<int, int>> bindex;//�洢��������
	vector<pair<int, int>> tindex;//�洢Ŀ���λ����
	string ans = to_string(reachedboxnum) + ",";//���շ��صı��룬��ʼ��ʱ������Ŀ���λ��������תΪ�ַ��������ñ���
	//��������������Ͻǵ���
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
	int bsize = bindex.size();//��������
	int tsize = tindex.size();//Ŀ���λ����
	int wsize = windex.size();//ǽ����
	ans += to_string(bsize) + ",";//������������������
	ans += to_string(tsize) + ",";//��Ŀ���λ������������
	ans += to_string(wsize) + ",";//��ǽ������������
	ans += to_string(c.getcharacterx()) + ",";//����ɫ�ڵ�ͼ�ϵĺ����괫������
	ans += to_string(c.getcharactery()) + ",";//����ɫ�ڵ�ͼ�ϵ������괫������
	ans += to_string(c.getcharactero()) + ",";//����ɫ���򴫸�����
	for (int i = 0; i < bsize; i++)//���������ӵ�������Ϣ��������
	{
		int x = bindex[i].first;
		int y = bindex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	for (int i = 0; i < tsize; i++)//������Ŀ���λ��������Ϣ��������
	{
		int x = tindex[i].first;
		int y = tindex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	for (int i = 0; i < wsize; i++)//������ǽ��������Ϣ��������
	{
		int x = windex[i].first;
		int y = windex[i].second;
		ans += (to_string(x) + "," + to_string(y) + ",");
	}
	return ans;//���ر���
}

int Mousemessage(ExMessage* msg)//ѡ�ؿ�
{
	int c = msg->x / 100;//��괦�ڹؿ������c�У���0��ʼ��
	int r = msg->y / 100;//��괦�ڹؿ������r�У���0��ʼ��
	return r * 5 + c;//���عؿ����
}

int Mousemessage_customlevel(ExMessage* msg)//ѡ�Զ���ؿ�
{
	int which = msg->y / 30;//��괦�ڹؿ��б��which�У���0��ʼ��
	return which;
}

void PlayGame(Gamelevel& ln, string user_name)
{
	char ch = NULL;//���ڴ���̰�����Ϣ
	bool ifbreak = false;//�����ж��Ƿ�㵽���˰�ť
	ln.DrawLevel();//���ƹؿ�����
	while (!ln.win())//����������Ϸ�ؿ�ѭ�������ж�Ϊʤ��ʱ�˳�ѭ��
	{
		ExMessage msg;
		if (peekmessage(&msg, EM_MOUSE))//���������Ϣ
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN://�������
				int y = msg.x / 40;//�������Ϸ�ؿ���ͼ�ϵ�������
				int x = msg.y / 40;//�������Ϸ�ؿ���ͼ�ϵĺ�����
				if (x == ln.row && y == 0)//����
				{
					ln.CloseLevel();//�ر���Ϸ�ؿ�����
					OpenSelectLevelInterface();//����ͨ�ؿ�ѡ�ؽ���
					DrawSelectLevelInterface();//������ͨ�ؿ�ѡ�ؽ���
					ifbreak = true;//�����ж��Ƿ�㵽���˰�ť�ı�����Ϊ��
					break;
				};
				if (x == ln.row && y == 1)//���¿�ʼ
				{
					ln.DeCode(0);//�����ʼ����
					ln.score = ln.row * ln.col * 5 * 5;//������Ϸ�ؿ�����
					ln.SetAllOnMap();//����������ŵ���ͼ��
					ln.DrawLevel();//������Ϸ�ؿ�����
					break;
				};
				if (x == ln.row && y == 2)//�浵
				{
					string gamelevelname = "GameLevel\\" + ln.gamename + ".dat";//�洢�浵������ļ�·��
					string gamelevelscore = "GameLevel\\" + ln.gamename + "_score.dat";//�洢�������ļ�·��
					ofstream fout(gamelevelname, ios::out);//����һ���ļ�Ϊgamelevelname���ļ����������
					ofstream scorefout(gamelevelscore, ios::out);//����һ���ļ�Ϊgamelevelscore���ļ����������
					ln.savedcode = "";//��ʼ���ؿ��浵����Ϊ��
					int rb = ln.reachedboxes;//�ﵽĿ���λ��������
					int b = ln.boxnum;//������
					int t = ln.targetnum;//Ŀ���λ��
					int w = ln.wallnum;//ǽ����
					//���룬������ln.savedcode
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
					fout << ln.savedcode;//���浵����д���ļ�gamelevelname
					scorefout << ln.score;//������д���ļ�gamelevelscore
					break;
				};
				if (x == ln.row && y == 3)//����
				{
					string gamelevelname = "GameLevel\\" + ln.gamename + ".dat";//�洢�浵������ļ�·��
					string gamelevelscore = "GameLevel\\" + ln.gamename + "_score.dat";//�洢�������ļ�·��
					ifstream fin(gamelevelname, ios::in);//����һ���ļ�Ϊgamelevelname���ļ�����������
					ifstream scorefin(gamelevelscore, ios::in);//����һ���ļ�Ϊgamelevelscore���ļ�����������
					string assist = "";//�����ַ���
					fin >> assist;//���浵����ȡ���������븨���ַ���assist��
					scorefin >> ln.score;//���÷�ȡ����������ؿ�����ln.score��
					if (ln.savedcode.size() == 0)ln.savedcode = assist;//���ؿ��浵����Ϊ�գ���assist��ֵ���ؿ��浵����
					if (ln.savedcode.size() == 0)break;//���ؿ��浵������Ϊ�գ����˳�switch
					ln.DeCode(1);//�Թؿ��浵������н���
					ln.SetAllOnMap();//����������ŵ���ͼ��
					ln.DrawLevel();//�ػ���Ϸ�ؿ�����
					break;
				}
			}
			if (ifbreak)break;//���㵽���˰�ť�����˳�������Ϸ�ؿ�ѭ��
		}
		if (_kbhit())//���񰴼���Ϣ
		{
			int sufchx = ln.character.getcharacterx();//��ȡ�ƶ�ǰ��ɫ�ڵ�ͼ�ϵĺ�����
			int sufchy = ln.character.getcharactery();//��ȡ�ƶ�ǰ��ɫ�ڵ�ͼ�ϵ�������
			int sufdata = ln.gamemap.getmap0data(sufchx, sufchy);//��ȡ�ƶ�ǰ��ͼ�Ͻ�ɫλ�ô�������
			ch = _getch();//���̰�����Ϣ��ֵ��ch
			ln.character.characteroperate1(ch);//��ɫ��ָ�������ƶ�
			ln.MoveCharactar(ch);//������ɫ�ƶ����ж��Ǹñ���λ�ò��仹�Ǹ������һ�񣩣����ı���Ҫ�ı�����
			int nowchx = ln.character.getcharacterx();//��ȡ�ƶ����ɫ�ڵ�ͼ�ϵĺ�����
			int nowchy = ln.character.getcharactery();//��ȡ�ƶ����ɫ�ڵ�ͼ�ϵ�������
			int nowdata = ln.gamemap.getmap0data(nowchx, nowchy);//��ȡ�ƶ����ͼ�Ͻ�ɫλ�ô�������
			int prechx = NULL, prechy = NULL;//��ɫ�ƶ��󣬽�ɫ������ǰһ����ڵ�ͼ�ϵ�����
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
			int predata = ln.gamemap.getmap0data(prechx, prechy);//��ȡ�ƶ����ͼ�Ͻ�ɫ������ǰһ��λ�ô�������
			if (ch == 'a' || ch == 'A' || ch == 'w' || ch == 'W' || ch == 'd' || ch == 'D' || ch == 's' || ch == 'S')
			{
				ln.DrawChangedImage(prechx, prechy, predata, nowchx, nowchy, nowdata, sufchx, sufchy, sufdata);//�ı���Ҫ�ı��ͼƬ
			}
		}
	}
	if (!ifbreak)//��������Ϊ�㵽���˰�ť���˳�ѭ�����������Ӯ����Ϸ
	{
		int finalscore = ln.score;//���յ÷�
		if (user_level_score[user_name].count(ln.gamename))//���û�user_name������ؿ�ln.gamename
		{
			int prescore = stoi(user_level_score[user_name][ln.gamename]);//�û�user_name����Ĺؿ�ln.gamename��ԭ�÷�
			if (prescore > ln.score)//ȡ��ǰ�ķֺ�ԭ�÷ֵ����ֵ
			{
				finalscore = prescore;
			}
		}
		user_level_score[user_name][ln.gamename] = to_string(finalscore);//�����û�user_name����Ĺؿ�ln.gamename�ĵ÷֣���ߵ÷֣�
		ofstream ulsfout("Users_Score\\" + user_name + ".dat", ios::app);//����һ���ļ�Ϊ"Users_Score\\" + user_name + ".dat"���ļ����������д�뷽ʽΪ����д��
		ulsfout << ln.gamename << " " << to_string(ln.score) << endl;//���Ӵ���ؿ������÷�
		Sleep(1000);//��������1�룬����ҷ�Ӧ�����Լ�Ӯ��
		ln.CloseLevel();//�ر���Ϸ�ؿ�����
		OpenSelectLevelInterface();//����ͨ�ؿ�ѡ�ؽ���
		DrawSelectLevelInterface();//������ͨ�ؿ�ѡ�ؽ���
	}
}

void PlayCustomGame(Gamelevel& ln, string user_name)//�����Զ���ؿ�
{
	//��PlayGame(Gamelevel& ln, string user_name)������ͬС�죬���ٽ���ע��
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
				if (x == ln.row && y == 0)//����
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
				if (x == ln.row && y == 1)//���¿�ʼ
				{
					ln.DeCode(0);
					ln.score = ln.row * ln.col * 5 * 5;
					ln.SetAllOnMap();
					ln.DrawLevel();
					break;
				};
				if (x == ln.row && y == 2)//�浵
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
				if (x == ln.row && y == 3)//����
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

void allocation_encryption_key()//����Կ�ַ������м��ܷ���
{
	set<char> usedletter;//��ӳ�����ĸ
	int letterindex = 0;//26���ֵ���Сд��ĸ��������ʼ��Ϊ0
	int n = PasswordKey.size();//��Կ��С
	for (int i = 0; i < n; i++)//������Կ��ʹÿ��'a'+letterindexӳ�䵽��һ�γ��ֵ���ĸ��
	{
		if (!usedletter.count(PasswordKey[i]) && letterindex < 26)
		{
			usedletter.insert(PasswordKey[i]);
			encrypted_key['a' + letterindex] = PasswordKey[i];
			letterindex++;
		}
	}
	while (letterindex < 26)//��ʣ���δӳ���26���ֵ���Сд��ĸӳ�䵽�Լ�
	{
		encrypted_key['a' + letterindex] = 'a' + letterindex;
		letterindex++;
	}
}

string encrypt_password(string password)//��������ܣ������ؼ��ܵ�����
{
	string ans = "";//����Ҫ���صļ��ܵ����룬��ʼ��Ϊ��
	int n = password.size();//�����С
	for (int i = 0; i < n; i++)//�������룬ֻ���������е�Сд��ĸ�������ַ�����
	{
		if (encrypted_key.count(password[i]))ans.push_back(encrypted_key[password[i]]);
		else ans.push_back(password[i]);
	}
	return ans;//���ؼ��ܺ������
}

void Find_total_score()//��ÿ���û����ܷ�
{
	map<string, map<string, string>>::iterator iter = user_level_score.begin();//����һ������������ʼ��Ϊ�û��ؿ�������ϣ�����ʼָ��λ��
	while (iter != user_level_score.end())//�õ����������û��ؿ�������ϣ��
	{
		map<string, string>::iterator iter2 = user_level_score[iter->first].begin();//����һ������������ʼ��Ϊ�ؿ�������ϣ�����ʼָ��λ��
		int s = 0;//�������ܷ֣���ʼ��Ϊ0
		while (iter2 != user_level_score[iter->first].end())//�õ����������ؿ�������ϣ��
		{
			s += stoi(iter2->second);
			iter2++;
		}
		user_totalscore[iter->first] = to_string(s);//���ִܷ���û��ֹܷ�ϣ����
		iter++;
	}
}

void Change_User_Level_Score()//����ĳ�û��ؿ�����
{
	set<string>::iterator iter = users_names.begin();//����һ������������ʼ��Ϊ�û������ϵ���ʼָ��λ��
	while (iter != users_names.end())//�õ����������û�������
	{
		user_level_score[*iter]["NULL"] = "0";//��ĳ�û�δ����κιؿ��������������Ա�֤�����ܷ�Ϊ0
		string UserName = "Users_Score\\" + *iter + ".dat";//��¼ĳ�û��Ĺؿ������ļ����ļ�·��
		ifstream users_levels_score_fin(UserName);//����һ���ļ�ΪUserName���ļ�����������
		string line = "";//���ڴ洢�ļ�����������Ϣ
		while (getline(users_levels_score_fin, line))//��ȡ�ļ�UserName��ÿһ�У�������ȡ������Ϣ����line���ַ���lineһ����һ���ո����Ϊ�����֣��ո�ǰ�Ĳ���Ϊ�ؿ������ո��Ĳ���Ϊ�û�����ùؿ��ĵ÷�
		{
			string levelname = "";//���ڴ洢line�еĹؿ�����Ϣ
			string score = "";//���ڴ洢line�еĵ÷���Ϣ
			int j = 0;//��line���б����ĳ�ʼ����
			for (; j < line.size() && line[j] != ' '; j++)//��line�еĹؿ���
			{
				levelname.push_back(line[j]);
			}
			while (line[j] == ' ')j++;//�����ո�
			for (; j < line.size(); j++)//��line�еĵ÷�
			{
				score.push_back(line[j]);
			}
			if (user_level_score[*iter].count(levelname))//���û���������ؿ�levelname�����е÷�
			{
				int prescore = 0;//ԭ�÷�
				int nowscore = stoi(score);//�ֵ÷�
				prescore = stoi(user_level_score[*iter][levelname]);//��¼ԭ�÷�
				user_level_score[*iter][levelname] = to_string(max(prescore, nowscore));//��ԭ�÷ֺ��ֵ÷��еĽϴ�ֵ������
				line = "";//��line��Ϊ��
				continue;
			}
			user_level_score[*iter][levelname] = score;//��¼�÷�
			line = "";//��line��Ϊ��
		}
		iter++;
	}
}

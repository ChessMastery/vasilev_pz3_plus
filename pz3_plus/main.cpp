#include <iostream>
#include <fstream>
#include <chrono>
#include <time.h>
#include <queue>
#include <stack>
#include <Windows.h>
#include <conio.h>

using namespace std;

fstream in;
ofstream out;

class btree
{
private:
   bool dfs(btree *node, int elem);
public:
   int elem; btree *left, *right;
   btree(int val = 0, btree *c = NULL) : elem(val), left(c), right(c) {}
   ~btree() {} // ���������� ����� ������������ ��� ����� ������� ���������� ������ ������ ��� �������� ������������ private-�����
   bool search(int elem);
} *root = NULL;

bool btree::search(int elem)
{
   return btree::dfs(this, elem);
}

bool btree::dfs(btree *node, int elem)
{
   stack<btree *> S;
   S.push(node);
   while (!S.empty())
   {
      node = S.top();
      S.pop();
      if (node->elem == elem)
         return true;
      if (node->left)
         S.push(node->left);
      if (node->right)
         S.push(node->right);
   }
   return false;
}

void PutNumRand(int num, btree *node)
{
   if (rand() % 2)
      if (!node->right)
         node->right = new btree(num);
      else
         PutNumRand(num, node->right);
   else
      if (!node->left)
         node->left = new btree(num);
      else
         PutNumRand(num, node->left);
}

void PutNumSort(int num, btree *node)
{
   if (num > node->elem)
      if (!node->right)
         node->right = new btree(num);
      else
      {
         node = node->right;
         PutNumSort(num, node);
      }
   else
      if (!node->left)
         node->left = new btree(num);
      else
      {
         node = node->left;
         PutNumSort(num, node);
      }
}

void InputGenerator(int k)
{
   try
   {
      in.open("in.txt", fstream::badbit | fstream::failbit);
   }
   catch (const fstream::failure &exeption)
   {
      cout << exeption.what() << endl;
      cout << exeption.code() << endl;
   }
   int num;
   for (int i = 0; i < k; i++)
   {
      num = rand();
      in << num << ' ';
   }
   in.close();
}

void GenerationManager(btree *root)
{
   enum SComands { CMD_RAND = 1, CMD_SORT, CMD_IN, CMD_BACK};

   int n = 0, exitFlag = 0, m = 0, k = 0, num = 0;
   do {
      cout << "<1> - ������������� ��������� ������\n";
      cout << "<2> - ������������� ������ ������\n";
      cout << "<3> - ��������� �������� �� ����� in.txt\n";
      cout << "<4> - � ����������� ����\n";
      int repeatFlag = 0;
      do {
         cout << "������� ����� ������� (�� 1 �� 4): ";
         if (!(cin >> n))
         {
            cout << "������ �����\n";
            _getch();
            return;
         }
         switch (n)
         {
         case CMD_RAND: exitFlag = 1;
            cout << "������� ���������� ��������� ������: ";
            cin >> k;
            InputGenerator(k);
            in.open("in.txt", fstream::in);
            in >> num;
            root->elem = num;
            while (in >> num)
               PutNumRand(num, root);
            in.close();
            cout << "��������� ���������!\n";
            break;
         case CMD_SORT: exitFlag = 1;
            cout << "������� ���������� ��������� ������: ";
            cin >> k;
            InputGenerator(k);
            in.open("in.txt", fstream::in);
            in >> num;
            root->elem = num;
            while (in >> num)
               PutNumSort(num, root);
            in.close();
            cout << "��������� ���������!\n";
            break;
         case CMD_IN: exitFlag = 1;
            in.open("in.txt", fstream::in);
            while (in >> num)
               PutNumSort(num, root);
            in.close();
            cout << "��������� ���������!\n";
            break;
         case CMD_BACK: exitFlag = 1;
            break;
         default: printf_s("������: �������� ����� �������\n");
            repeatFlag = 1;
         }
      } while (!repeatFlag && !exitFlag);
   } while (!exitFlag);
}

void PreorderTraversal(btree *node)
{
   cout << node->elem << ' ';
   if (node->left)
      PreorderTraversal(node->left);
   if (node->right)
      PreorderTraversal(node->right);
}

void InorderTraversal(btree *node)
{
   if (node->left)
      InorderTraversal(node->left);
   cout << node->elem << ' ';
   if (node->right)
      InorderTraversal(node->right);
      
}

void PostorderTraversal(btree *node)
{
   if (node->left)
      PostorderTraversal(node->left);
   if (node->right)
      PostorderTraversal(node->right);
      cout << node->elem << ' ';
}

void BFS(btree *node)
{
   queue<btree *> Q;
   Q.push(node);
   do
   {
      node = Q.front();
      Q.pop();
      cout << node->elem << ' ';
      if (node->left)
         Q.push(node->left);
      if (node->right)
         Q.push(node->right);
   } while
      (!Q.empty());
}

int main()
{
   int cp, cp1;
   cp = GetConsoleCP();
   cp1 = GetConsoleOutputCP();

   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);
 
   out.open("out.txt");
   if (!out.is_open())
      cout << "������ �������� ����� out.txt" << endl;

   enum Comands { CMD_GENERATE = 1, CMD_PREORD, CMD_INORD, CMD_POSTORD, CMD_BFS, CMD_SEARCH, CMD_EXIT };

   int n = 0, exitFlag = 0, m = 0, num = 0, i = 0;
   do {
      cout << "<1> - ������������� ����� ������\n";
      cout << "<2> - ���������� �����\n";
      cout << "<3> - ��������� �����\n";
      cout << "<4> - ����������� �����\n";
      cout << "<5> - ����� � ������\n";
      cout << "<6> - ����� ��������� ��������\n";
      cout << "<7> - �����\n";
      int repeatFlag = 0;
      do {
         cout << "������� ����� ������� (�� 1 �� 7): ";
         if (!(cin >> n))
         {
            cout << "������ �����\n";
            _getch();
            return 1;
         }
         switch (n)
         {
         case CMD_GENERATE: repeatFlag = 1;
            if (root) delete root;
            root = new btree;
            GenerationManager(root);
            break;
         case CMD_PREORD: repeatFlag = 1;
            if (!root)
               cout << "�������� ������!\n";
            else
            {
               auto start_time = chrono::high_resolution_clock::now();
               PreorderTraversal(root);
               auto end_time = chrono::high_resolution_clock::now();
               cout << endl;

               double elapsed_time = chrono::duration<double>(end_time - start_time).count();

               i++;
               out << "����� � " << i << ": ����������" << endl;
               out.precision(10);
               out << "����������� �����: " << elapsed_time << " ���." << endl;
            }
            break;
         case CMD_INORD: repeatFlag = 1;
            if (!root)
               cout << "�������� ������!\n";
            else
            {
               auto start_time = chrono::high_resolution_clock::now();
               InorderTraversal(root);
               auto end_time = chrono::high_resolution_clock::now();
               cout << endl;

               double elapsed_time = chrono::duration<double>(end_time - start_time).count();

               i++;
               out << "����� � " << i << ": ���������" << endl;
               out.precision(10);
               out << "����������� �����: " << elapsed_time << " ���." << endl;
            }
            break;
         case CMD_POSTORD: repeatFlag = 1;
            if (!root)
               cout << "�������� ������!\n";
            else
            {
               auto start_time = chrono::high_resolution_clock::now();
               PostorderTraversal(root);
               auto end_time = chrono::high_resolution_clock::now();
               cout << endl;

               double elapsed_time = chrono::duration<double>(end_time - start_time).count();

               i++;
               out << "����� � " << i << ": �����������" << endl;
               out.precision(10);
               out << "����������� �����: " << elapsed_time << " ���." << endl;
            }
            break;
         case CMD_BFS: repeatFlag = 1;
            if (!root)
               cout << "�������� ������!";
            else
            {
               auto start_time = chrono::high_resolution_clock::now();
               BFS(root);
               auto end_time = chrono::high_resolution_clock::now();
               cout << endl;

               double elapsed_time = chrono::duration<double>(end_time - start_time).count();

               i++;
               out << "����� � " << i << ": ����� � ������\n";
               out.precision(10);
               out << "����������� �����: " << elapsed_time << " ���.\n";
            }
            break;
         case CMD_SEARCH: repeatFlag = 1;
            cout << "������� �������� �������� ��������: ";
            cin >> num;
            if (root->search(num))
               cout << "������� ������.\n";
            else
               cout << "������� �� ������.\n";
            break;
         case CMD_EXIT: exitFlag = 1;
            break;
         default: cout << "������: �������� ����� �������\n";
            repeatFlag = 1;
         }
      } while (!repeatFlag && !exitFlag);
   } while (!exitFlag);

   out.close();
   SetConsoleCP(cp);
   SetConsoleOutputCP(cp1);
   return 0;
}
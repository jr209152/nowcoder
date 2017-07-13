﻿
auto 关键字 用于 iterator等处 方便
getline()读取一行字符串
string str;  包含#inclue<string>即可
getline(cin, str);




/********	----------------------------------------------------------------------------DFS BFS******
经典题目：
[LeetCode]419 --- Battleships in a Board 平板上的战船   
 

Given an 2D board, count how many different battleships are in it. The battleships are represented with 'X's, 
empty slots are represented with '.'s. You may assume the following rules:

You receive a valid board, made of only battleships or empty slots.
Battleships can only be placed horizontally or vertically. In other words, 
they can only be made of the shape 1xN (1 row, N columns) or Nx1 (N rows, 1 column), where N can be of any size.
At least one horizontal or vertical cell separates between two battleships - there are no adjacent battleships.
Example:

X..X
...X
...X
In the above board there are 2 battleships.

Invalid Example:

...X
XXXX
...X
This is not a valid board - as battleships will always have a cell separating between them.

Your algorithm should not modify the value of the board.

 

这道题好像之前在地里面见过，忘了是哪家公司的面试题了，现在被LeetCode收录了，感觉现在LeetCode更新越来越快了，感觉要成为第一大题库了，
赞一个👍。这道题让我们求战舰的个数，所谓的战舰就是只能是一行或者一列，不能有拐弯
。这道题降低了难度的做法是限定了不会有相邻的两个战舰的存在，有了这一点限制，那么我们只需要遍历一次二维数组就行了
，只要找出战舰的起始点。所谓的战舰起始点，就是为X的点，而且该点的上方和左边的点不能为X，
所以我们只要找出所有满足这个条件的点即可，参见代码如下：

 

解法一：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int res = 0, m = board.size(), n = board[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == '.' || (i > 0 && board[i - 1][j] == 'X') || (j > 0 && board[i][j - 1] == 'X')) continue;
                ++res;
            }
        }
        return res;
    }
};
 

/*
然而我自己在做的时候并没有注意到题目中限制了两艘战舰不能相邻的情况，
我加上了处理方法，首先我算出来了所有连续X的区域的个数，
方法跟之前那道Number of Islands一样，稍有不同的是，
我分别记录下来每一个连续区域的i和j，把所有的点的横纵坐标分别或了起来，
这样做的好处是如果是在一条直线上的战舰，那么所有点肯定是要么横坐标都相同，
要么纵坐标都相同，所以最后我们检测如果横纵坐标的累积或都跟之前的i和j不同的话，
那么一定不是题目中定义的战舰，那么我们就不累加结果res，参见代码如下：
 

解法二：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int m = board.size(), n = board[0].size(), res = 0;
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' && !visited[i][j]) {
                    int vertical = 0, horizontal = 0;
                    dfs(board, visited, vertical, horizontal, i, j);
                    if (vertical == i || horizontal == j) ++res;
                }
            }
        }
        return res;
    }
    void dfs(vector<vector<char>>& board, vector<vector<bool>>& visited, int& vertical, int& horizontal, int i, int j) {
        int m = board.size(), n = board[0].size();
        if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || board[i][j] == '.') return;
        vertical |= i; horizontal |= j;
        visited[i][j] = true;
        dfs(board, visited, vertical, horizontal, i - 1, j);
        dfs(board, visited, vertical, horizontal, i + 1, j);
        dfs(board, visited, vertical, horizontal, i, j - 1);
        dfs(board, visited, vertical, horizontal, i, j + 1);
    }
};

/*
既然DFS能实现，那么BFS就应该没啥问题，这里完全按题目的要求，默认两个战舰不会相邻，并没有添加解法二中的过滤条件，参见代码如下：

 

解法三：
*/
class Solution {
public:
    int countBattleships(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return 0;
        int res = 0, m = board.size(), n = board[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));
        vector<vector<int>> dirs{{0,-1},{-1,0},{0,1},{1,0}};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'X' && !visited[i][j]) {
                    ++res;
                    queue<pair<int, int>> q;
                    q.push({i, j});
                    while (!q.empty()) {
                        auto t = q.front(); q.pop();
                        visited[t.first][t.second] = true;
                        for (auto dir : dirs) {
                            int x = t.first + dir[0], y = t.second + dir[1];
                            if (x < 0 || x >= m || y < 0 || y >= n || visited[x][y] || board[x][y] == '.') continue;
                            q.push({x, y});
                        }
                    }
                }
            }
        }
        return res;
    }
};
/*leetcode-200-Number of Islands
Given a 2d grid map of '1's (land) and '0's (water), 
count the number of islands. An island is surrounded by water
 and is formed by connecting adjacent lands horizontally or vertically.
 You may assume all four edges of the grid are all surrounded by water.

Example 1:

11110
11010
11000
00000
Answer: 1

Example 2:

11000
11000
00100
00011
Answer: 3
*/ 

	 void dfsisland(vector<vector<char>>& grid, vector<vector<bool>>& visited,int i,int j)
	 {
		 int m = grid.size(), n = grid[0].size();
		 if (i < 0 || i >= m || j < 0 || j >= n || visited[i][j] || grid[i][j] == '0')return;
		 visited[i][j] = true;
		 dfsisland(grid, visited, i + 1, j);
		 dfsisland(grid, visited, i - 1, j);
		 dfsisland(grid, visited, i, j + 1);
		 dfsisland(grid, visited, i, j - 1);
	 }
	 int numIslands(vector<vector<char>>& grid)
	 {
		 if (grid.empty())return 0;
		 int m = grid.size(), n = grid[0].size();
		 vector<vector<bool>>visited(m, vector<bool>(n, false));
		 int ret = 0;
		 for (int i = 0; i < m;i++)
		 {
			 for (int j = 0; j < n;j++)
			 {
				 if (grid[i][j] == '1' && !visited[i][j])
				 {
					 dfsisland(grid, visited,i,j);
					 ret++;
				 }
			 }
		 }
		 return ret;
	 }
/*-------------------------------------------------------------------------------------HASH  桶排序

Given a non-empty array of integers, return the k most frequent elements.

For example,
Given [1,1,1,2,2,3] and k = 2, return [1,2].

Note: 

You may assume k is always valid, 1 ? k ? number of unique elements.
Your algorithm's time complexity must be better than O(n log n), where n is the array's size.
思路：

首先用map统计数字出现的次数，然后再将出现的次数作为关键词，使用桶排序，然后从后遍历，返回关键字即可。
后来又看到有人用优先队列存储，感觉更方便了。*/
	vector<int> topKFrequent(vector<int>& nums, int k)
    {
         if (nums.empty())return{};
         map<int, int>mp;
         vector<vector<int>>bucket(nums.size() + 1);
         for (auto a:nums)mp[a]++;
         for (auto it : mp)bucket[it.second].push_back(it.first);
         vector<int>ret;
         for (int i = nums.size(); i >= 0 && k>0;i--)
         {
             if (!bucket[i].empty())
             {
                 for (int j = 0; j < bucket[i].size() && k>0; j++)
                 {
                     ret.push_back(bucket[i][j]);
                     k--;
                 }
             }
         }
          
         return ret;
    }
	 
	 vector<int> topKFrequent(vector<int>& nums, int k)
	 {
        unordered_map<int,int> map;
        for(int num : nums){
            map[num]++;
        }
        
        vector<int> res;
        // pair<first, second>: first is frequency,  second is number
        priority_queue<pair<int,int>> pq; 
        for(auto it = map.begin(); it != map.end(); it++){
            pq.push(make_pair(it->second, it->first));
            if(pq.size() > (int)map.size() - k){
                res.push_back(pq.top().second);
                pq.pop();
            }
        }
        return res;
    }
	
	
	/*  字符串  stringstream 的应用 以及查找字符的find函数
	
A group of duplicate files consists of at least two files that have exactly the same content.

A single directory info string in the input list has the following format:

"root/d1/d2/.../dm f1.txt(f1_content) f2.txt(f2_content) ... fn.txt(fn_content)"

It means there are n files (f1.txt, f2.txt ... fn.txt with content f1_content, f2_content ... fn_content, respectively) in directory root/d1/d2/.../dm. Note that n >= 1 and m >= 0. If m = 0, it means the directory is just the root directory.

The output is a list of group of duplicate file paths. For each group, it contains all the file paths of the files that have the same content. A file path is a string that has the following format:

"directory_path/file_name.txt"

Example 1:
Input:
["root/a 1.txt(abcd) 2.txt(efgh)", "root/c 3.txt(abcd)", "root/c/d 4.txt(efgh)", "root 4.txt(efgh)"]
Output:  
[["root/a/2.txt","root/c/d/4.txt","root/4.txt"],["root/a/1.txt","root/c/3.txt"]]*/
	vector<vector<string>> findDuplicate(vector<string>& paths)
	{
    unordered_map<string, vector<string>> files;
    vector<vector<string>> result;

    for (auto path : paths) {
	    stringstream ss(path);
	    string root;
	    string s;
	    getline(ss, root, ' ');
	    while (getline(ss, s, ' ')) {
		    string fileName = root + '/' + s.substr(0, s.find('('));
		    string fileContent = s.substr(s.find('(') + 1, s.find(')') - s.find('(') - 1);
		    files[fileContent].push_back(fileName);
	    }
    }

    for (auto file : files) {
	    if (file.second.size() > 1)
		    result.push_back(file.second);
    }

    return result;
}
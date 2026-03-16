#include <iostream>
#include <vector>
#include <tuple>
#include <climits>
#include <cmath>

using namespace std;

int n, m;
vector<vector<bool>> field;
vector<tuple<int,int,int>> ans_figures;
int best = INT_MAX;
long long ways = 0;

pair<int,int> free_cell(const vector<vector<bool>>& board)
{
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!board[i][j])
                return {i, j};
        }
    }
    return {-1, -1};
}

bool fits(const vector<vector<bool>>& board, int x, int y, int size)
{
    if (x + size > n || y + size > m)
        return false;

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(board[x + i][y + j])
                return false;
        }
    }
    return true;
}

void place(vector<vector<bool>>& board, int x, int y, int size, bool val)
{
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            board[x + i][y + j] = val;
        }
    }
}

int max_square_size(const vector<vector<bool>>& board, int x, int y)
{
    int mx = min(n - x, m - y);
    if(n == m && mx == n) mx--;
    int res = 0;

    for(int i = 1; i <= mx; i++){
        if(!fits(board, x, y, i))
            break;
        res = i;
    }
    return res;
}

int get_remained(int x, int y)
{
  int c =0 ;
   for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(!field[i][j]) c++;
    }
   }
  
  return c;
}

void backtrack(vector<tuple<int,int,int>>& figures)
{
    if ((int)figures.size() >= best)
        return;


    auto [x, y] = free_cell(field);

    if(x == -1){
        if ((int)figures.size() < best){
            best = (int)figures.size();
            ans_figures = figures;
            ways = 1;
        }
        else if((int)figures.size() == best){
            ways++;
        }
        return;
    }
    
    int remained_cells = get_remained(x,y); 
    int max_size = max_square_size(field, x, y);
    if (ceil(remained_cells / (max_size * max_size)) + figures.size() >= best) return;


    for(int size = max_size; size >= 1; size--){
        if(fits(field, x, y, size)){
            place(field, x, y, size, true);
            figures.push_back({x + 1, y + 1, size});

            backtrack(figures);

            figures.pop_back();
            place(field, x, y, size, false);
        }
    }
}

int get_greedy(vector<tuple<int,int,int>>& greedy_figures)
{
    vector<vector<bool>> temp(n, vector<bool>(m, false));
    int c = 0;

    while(true){
        auto [x, y] = free_cell(temp);
        if(x == -1) break;

        int mx = max_square_size(temp, x, y);
        place(temp, x, y, mx, true);
        greedy_figures.push_back({x + 1, y + 1, mx});
        c++;
    }
    ways = 1;

    return c;
}

int main()
{
    cin >> n >> m;
    if(n > m) swap(n, m);

    field.assign(n, vector<bool>(m, false));

    vector<tuple<int,int,int>> greedy_figures;
    best = get_greedy(greedy_figures);
    ans_figures = greedy_figures;

    vector<tuple<int,int,int>> figures;
    figures.reserve(n * m);

    backtrack(figures);

    cout << "ways: " << ways << "\n";
    cout << "min: " << best << "\n";
    cout << "x y w\n";
    for (auto& [x, y, w] : ans_figures) {
        cout << x << " " << y << " " << w << "\n";
    }

    return 0;
}
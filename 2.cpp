#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n, m; // Объявление границ координатной плоскости
vector<vector<int>> buildinds; // Двумерный вектор наличия здания по координатам
vector<int> Ox, Oy;
int sum = 0; // Итоговая сумма
int k = 0; // Вспомогательная переменная, нужна для фиксирования количества зданий на карте 

bool cmp(const int &lhs, const int &rhs) {
    return lhs > rhs;
}

inline void inputBuildinds() {
    for (int x = 0; x < n; ++x) {
        for (int y = 0; y < m; ++y) {
            cin >> buildinds[x][y];
            if (buildinds[x][y] == 1) {
                Ox.emplace_back(x);
                Oy.emplace_back(y);
                ++k;
            }
        }
    }
}

/* 

Вспомогательная процедура для подсчета длины оптического кабеля
между всеми зданиями без учета высот зданий

*/

inline void calculatingDistances(const vector<int> &arr) {
    int cnt = arr.size() - 1;
    for (auto &elem : arr) {
        sum += cnt * elem;
        cnt -= 2;
    }
}

/*

Функция нужна для подсчета оставшейся длины, 
которую мы не учли - длина удвоенных высот зданий.

Функция принемает вектор заранее известных высот
по каждому учтенному зданию.

Высоты бли получены при помощи API 2GIS.

*/

inline int calculatingOtherDistances(const vector<int> &buildingHeights) {
    int sum = 0;
    for (auto &elem : buildingHeights) {
        sum += 2 * elem;
    }
    return sum;
}

/*

Ввод количества этажей зданий (для примера)
В действительности они должны быть получены заранее через API

*/

vector<int> API_cnt_floors() {
    vector<int> buildings_cnt_floors(k);
    for (auto &elem : buildings_cnt_floors) {
        cin >> elem;
    }
    return buildings_cnt_floors;
}

int main() {
    cin >> n >> m;
    buildinds.resize(n, vector<int>(m));
    inputBuildinds();
    sort(Ox.begin(), Ox.end(), cmp); // Сортировка по не возрастанию
    sort(Oy.begin(), Oy.end(), cmp);
    calculatingDistances(Ox); // Главная функци, подсчитывает все расстояния между зданиями
    calculatingDistances(Oy);
    sum += calculatingOtherDistances(API_cnt_floors()); // Изменение длины с учетом высот зданий
    cout << sum; // Вывод результирующей суммы расстояний
    return 0;
}

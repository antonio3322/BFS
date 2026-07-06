#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main() {
    setlocale(LC_ALL, "RU");
    int n, m;
    cin >> n >> m;

    // Создаём граф
    vector<vector<int>> G(n + 1);

    // Читаем рёбра
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        G[a].push_back(b);
        G[b].push_back(a);
    }

    int start, finish;
    cin >> start >> finish;  // Вводим начальную и конечную вершины

    // BFS
    queue<int> q;
    q.push(start);

    vector<int> Len(n + 1, -1);  // Расстояния
    Len[start] = 0;

    vector<bool> Mark(n + 1, false);  // Посещённые вершины
    Mark[start] = true;

    vector<int> Parent(n + 1, -1);  // Для восстановления пути

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();

        // Проходим по всем соседям вершины tmp
        for (int i = 0; i < G[tmp].size(); i++) {
            int neighbor = G[tmp][i];

            if (!Mark[neighbor]) {
                Mark[neighbor] = true;
                Len[neighbor] = Len[tmp] + 1;
                Parent[neighbor] = tmp;
                q.push(neighbor);
            }
        }
    }

    // Проверяем, достижима ли конечная вершина
    if (Len[finish] == -1) {
        cout << "Путь не существует!" << endl;
        return 0;
    }

    cout << Len[finish] << endl;

    // Восстановление маршрута с конца
    vector<int> Res;
    int buf = finish;

    // Идём от finish к start по родителям
    while (buf != -1) {
        Res.push_back(buf);
        if (buf == start) break;
        buf = Parent[buf];
    }

    // Выводим маршрут в обратном порядке (от конца к началу)
    // Так как Res хранит путь от finish к start,
    // выводим с конца вектора к началу
    for (int i = Res.size() - 1; i >= 0; i--) {
        cout << Res[i] << " ";
    }
    cout << endl;

    return 0;
}
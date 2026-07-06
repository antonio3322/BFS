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

    vector<bool> MarkComp(n + 1, false);
    int count = 0;
    vector<vector<int>> Components;  // Для хранения вершин каждого компонента

    for (int start = 1; start <= n; start++) {
        if (!MarkComp[start]) {
            count++;
            vector<int> component;

            queue<int> q;
            q.push(start);
            MarkComp[start] = true;

            while (!q.empty()) {
                int v = q.front();
                q.pop();
                component.push_back(v);

                for (int i = 0; i < G[v].size(); i++) {
                    int neighbor = G[v][i];
                    if (!MarkComp[neighbor]) {
                        MarkComp[neighbor] = true;
                        q.push(neighbor);
                    }
                }
            }
            Components.push_back(component);
        }
    }

    // Вывод информации о компонентах
    cout << count << endl;

    for (int i = 0; i < Components.size(); i++) {
        cout << "Компонент " << i + 1 << " (размер " << Components[i].size() << "): ";
        for (int v : Components[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    int start, finish;
    cin >> start >> finish;

    if (start < 1 || start > n || finish < 1 || finish > n) {
        cout << "Неверные номера вершин!" << endl;
        return 0;
    }

    // Если старт и финиш совпадают
    if (start == finish) {
        cout << "Расстояние: 0" << endl;
        cout << "Путь: " << start << endl;
        return 0;
    }

    // BFS для поиска пути
    queue<int> q;
    q.push(start);

    vector<int> Len(n + 1, -1);
    Len[start] = 0;

    vector<bool> Mark(n + 1, false);
    Mark[start] = true;

    vector<int> Putty(n + 1, -1);

    while (!q.empty()) {
        int tmp = q.front();
        q.pop();

        for (int i = 0; i < G[tmp].size(); i++) {
            int neighbor = G[tmp][i];

            if (!Mark[neighbor]) {
                Mark[neighbor] = true;
                Len[neighbor] = Len[tmp] + 1;
                Putty[neighbor] = tmp;
                q.push(neighbor);
            }
        }
    }

    // Проверяем, достижима ли конечная вершина
    if (Len[finish] == -1) {
        cout << "Путь не существует" << endl;
        return 0;
    }

    cout << Len[finish] << endl;

    // Восстановление маршрута
    vector<int> Res;
    int buf = finish;

    while (buf != -1) {
        Res.push_back(buf);
        if (buf == start) break;
        buf = Putty[buf];
    }

    // Вывод маршрута
    for (int i = Res.size() - 1; i >= 0; i--) {
        cout << Res[i];
        if (i > 0) cout << " -> ";
    }
    cout << endl;

    return 0;
}

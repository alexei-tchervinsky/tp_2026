#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <tuple>

using namespace std;

int main()
{
    setlocale(LC_ALL, "Russian");

    cout << "========================================" << endl;
    cout << "   АЛГОРИТМЫ НА ГРАФАХ (ЗАДАНИЕ 2.6)" << endl;
    cout << "========================================" << endl;

    vector<vector<pair<int, int>>> graph(5);

    graph[0].push_back({ 1, 10 });
    graph[0].push_back({ 2, 5 });

    graph[1].push_back({ 2, 2 });
    graph[1].push_back({ 3, 1 });

    graph[2].push_back({ 1, 3 });
    graph[2].push_back({ 3, 9 });
    graph[2].push_back({ 4, 2 });

    graph[3].push_back({ 4, 4 });

    cout << "\n1. АЛГОРИТМ ДЕЙКСТРЫ (от вершины 0)" << endl;
    cout << "----------------------------------------" << endl;

    int start = 0;
    int n = 5;

    vector<int> dist(n, INT_MAX);
    dist[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q;
    q.push({ 0, start });

    while (!q.empty())
    {
        int curDist = q.top().first;
        int u = q.top().second;
        q.pop();

        if (curDist > dist[u]) continue;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist[u] + weight < dist[v])
            {
                dist[v] = dist[u] + weight;
                q.push({ dist[v], v });
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout << "Расстояние до " << i << " = ";
        if (dist[i] == INT_MAX)
            cout << "нет пути" << endl;
        else
            cout << dist[i] << endl;
    }

    cout << "\n2. ВОЛНОВОЙ АЛГОРИТМ (путь из 0 в 4)" << endl;
    cout << "----------------------------------------" << endl;

    int target = 4;

    vector<int> dist2(n, INT_MAX);
    vector<int> parent(n, -1);

    dist2[start] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> q2;
    q2.push({ 0, start });

    while (!q2.empty())
    {
        int curDist = q2.top().first;
        int u = q2.top().second;
        q2.pop();

        if (curDist > dist2[u]) continue;

        if (u == target) break;

        for (auto edge : graph[u])
        {
            int v = edge.first;
            int weight = edge.second;

            if (dist2[u] + weight < dist2[v])
            {
                dist2[v] = dist2[u] + weight;
                parent[v] = u;
                q2.push({ dist2[v], v });
            }
        }
    }

    if (dist2[target] == INT_MAX)
    {
        cout << "Путь не найден!" << endl;
    }
    else
    {
        vector<int> path;
        for (int v = target; v != -1; v = parent[v])
        {
            path.push_back(v);
        }
        reverse(path.begin(), path.end());

        cout << "Самый короткий путь: ";
        for (int v : path)
        {
            cout << v << " ";
        }
        cout << endl;
        cout << "Длина пути = " << dist2[target] << endl;
    }

    cout << "\n3. АЛГОРИТМ БЕЛЛМАНА-ФОРДА (отрицательные веса)" << endl;
    cout << "----------------------------------------" << endl;

    vector<tuple<int, int, int>> edges;
    edges.push_back({ 0, 1, 4 });
    edges.push_back({ 0, 2, 2 });
    edges.push_back({ 1, 2, -3 });

    int n2 = 3;
    vector<int> dist3(n2, INT_MAX);
    dist3[start] = 0;

    for (int i = 0; i < n2 - 1; i++)
    {
        for (auto e : edges)
        {
            int u = get<0>(e);
            int v = get<1>(e);
            int w = get<2>(e);

            if (dist3[u] != INT_MAX && dist3[u] + w < dist3[v])
            {
                dist3[v] = dist3[u] + w;
            }
        }
    }

    bool hasNegativeCycle = false;
    for (auto e : edges)
    {
        int u = get<0>(e);
        int v = get<1>(e);
        int w = get<2>(e);

        if (dist3[u] != INT_MAX && dist3[u] + w < dist3[v])
        {
            hasNegativeCycle = true;
            break;
        }
    }

    if (hasNegativeCycle)
    {
        cout << "Обнаружен отрицательный цикл!" << endl;
    }
    else
    {
        for (int i = 0; i < n2; i++)
        {
            cout << "Расстояние до " << i << " = " << dist3[i] << endl;
        }
    }

    cout << "\n========================================" << endl;
    cout << "Программа завершена!" << endl;

    cout << "\nНажми Enter для выхода...";
    cin.get();

    return 0;
}

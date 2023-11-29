#include <iostream>
#include <queue>
#include <unordered_map>

int knight(std::string pos1, std::string pos2);

int main() {
    std::string startPos, endPos;
    while (true) {
        std::cout << "Начальная позиция: ";
        std::cin >> startPos;
        std::cout << "Конечная позиция: ";
        std::cin >> endPos;

        int moves = knight(startPos, endPos);
        if (moves != -1) {
            std::cout << "Минимальное количество ходов: " << moves << std::endl;
        }
        else std::cout << "Конь не может достичь заданной позициии. " << std::endl;


        std::cout << "Продолжить? (y/n): ";
        char choise;
        std::cin >> choise;
        if (choise != 'y') {
            break;
        }
    }

    return 0;
}

int knight(std::string pos1, std::string pos2) {

    int startX = pos1[0] - 'a';
    int startY = pos1[1] - '1';
    int endX = pos2[0] - 'a';
    int endY = pos2[1] - '1';

    // Возможные ходы
    std::vector<std::pair<int, int>>moves = {
            {-2,-1}, {-2,1}, {2,-1}, {2,1},
            {-1,-2}, {-1,2}, {1,-2}, {1,2}
    };

    std::queue<std::pair<int, int>> q;
    q.emplace(startX, startY);

    // Мапа для хранения минимального количества ходов для каждой позиции коня
    std::unordered_map<int, int> minMoves;
    minMoves[startX * 8 + startY] = 0;

    // Поиск минимального количества ходов с помощью алгоритма поиска в ширину
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == endX && y == endY) {
            return minMoves[x * 8 + y];
        }

        for (const auto& move : moves) {
            int newX = x + move.first;
            int newY = y + move.second;
            if (newX >= 0 && newX < 8 && newY >= 0 && newY < 8) {
                if (!minMoves.count(newX * 8 + newY)) {
                    minMoves[newX * 8 + newY] = minMoves[x * 8 + y] + 1;
                    q.emplace(newX, newY);
                }
            }
        }
    }

    return -1;
}

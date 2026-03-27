//
// Created by unkn0 on 2026-03-24.
//

#include <memory>
#include <queue>

constexpr int WIDTH = 30;
constexpr int HEIGHT = 20;

constexpr int dx[] = {0, 1, 0, -1};
constexpr int dy[] = {-1, 0, 1, 0};

enum Cell { NONE, WALL, SNAKE_HEAD, SNAKE_BODY, FOOD, NEG_FOOD };

Cell board[WIDTH][HEIGHT];

class State;

struct Coordinate {
    int x;
    int y;
};

struct Step {
    std::unique_ptr<State> newState;
    int direction;
    int cost;
};

class State {
public:
    explicit State(const std::deque<Coordinate>& snake) {
        m_Snake = snake;
    }

    [[nodiscard]] Coordinate getHeadPosition() const {
        return m_Snake.back();
    }

    std::vector<Step> getSuccessors() {
        std::vector<Step> result;
        for (int dir = 0; dir < 4; dir++) {
            auto [x, y] = getHeadPosition();
            int newX = x + dx[dir];
            int newY = y + dy[dir];
            if (isValidCell(newX, newY)) {
                auto newState = std::make_unique<State>(m_Snake);
                newState->moveForward(dir);
                Step step { (std::move(newState)), dir, 1 };
                if (board[newX][newY] == NEG_FOOD) {
                    step.cost += 10;
                }
                result.push_back(std::move(step));
            }
        }
        return result;
    }

private:
    std::deque<Coordinate> m_Snake;

    bool selfCollides(const int nx, const int ny) {
        for (auto [x, y] : m_Snake) {
            if (x == nx && y == ny) {
                return true;
            }
        }
        return false;
    }

    static bool isValidCell(const int x, const int y) {
        const Cell cell = board[x][y];
        return cell != WALL && cell != SNAKE_BODY && cell != SNAKE_HEAD;
    }

    void moveForward(const int dir) {
        auto [x, y] = getHeadPosition();
        const Coordinate newHead { x + dx[dir], y + dy[dir] };
        const Cell targetCell = board[newHead.x][newHead.y];
        m_Snake.push_back(newHead);
        if (targetCell == FOOD) {
            return;
        }
        m_Snake.pop_front();
        if (targetCell == NEG_FOOD) {
            m_Snake.pop_front();
        }
    }
};

class AStarSearchAgent {
public:
    AStarSearchAgent(const int foodX, const int foodY, std::unique_ptr<State> initialState) {
        this->foodX = foodX;
        this->foodY = foodY;
        this->initState = std::move(initialState);
        for (int i = 0; i < WIDTH; i++) {
            for (int j = 0; j < HEIGHT; j++) {
                pathTo[i][j] = -1;
            }
        }
    }

private:
    int foodX;
    int foodY;
    int pathTo[WIDTH][HEIGHT];
    std::unique_ptr<State> initState;

    [[nodiscard]] bool isGoalState(const int x, const int y) const {
        return x == foodX && y == foodY;
    }
};

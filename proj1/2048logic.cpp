// ============================================
// 2048 游戏核心逻辑 - 请实现以下四个函数
// ============================================
// 
// 棋盘是一个 4x4 的二维数组 board[4][4]
// 值为 0 表示空格，其他值为 2 的幂次（2, 4, 8, ...）
//
// 每个函数需要：
//   1. 将所有非零元素向指定方向"平移"（去掉中间的空格）
//   2. 将相邻且相同的元素"合并"（求和），每个元素每次移动只能合并一次
//   3. 合并后再次平移，填充空位
//   4. 返回本次移动获得的分数（所有合并产生的值之和）
//
// 提示：可以先实现一个"处理单行向左压缩"的辅助函数，
//       然后其他三个方向都可以通过"转换→处理→转换回"来实现。

const int LEN = 4;

// 辅助函数：将一行向左压缩并合并
// 参数：arr[4] 是一行的数据，len 固定为 4
// 返回值：本次压缩获得的分数
int compressLeft(int arr[], int len) {
    int score = 0;

    // TODO: 第一步 - 将所有非零元素移到左边（去掉中间的0）

    // TODO: 第二步 - 合并相邻的相同元素

    // TODO: 第三步 - 再次将非零元素移到左边

    /**
     * 这个算法需要遍历 5 次 arr 数组, 时间复杂度是 O(n).
     * 理论上最优的解法可以在只遍历一次 arr 的情况下完成合并.
     */

    int leftMost = 0, curr = 0; // leftMost 指向当前最左边的空格子
    for (; curr < len; curr++) {
        if (arr[curr] != 0) {
            arr[leftMost++] = arr[curr];
        }
    }
    while (leftMost < len) {
        arr[leftMost++] = 0;
    }
    for (curr = 0; curr < len && arr[curr] != 0; curr++) {
        if (curr + 1 < len && arr[curr] == arr[curr + 1]) {
            arr[curr] *= 2;
            arr[curr + 1] = 0;
            score += arr[curr];
        }
    }
    for (curr = 0, leftMost = 0; curr < len; curr++) {
        if (arr[curr] != 0) {
            arr[leftMost++] = arr[curr];
        }
    }
    while (leftMost < len) {
        arr[leftMost++] = 0;
    }

    return score;
}

/** 来自 ChatGPT 的优化方案, 仅需要 1 次遍历. 
int compressLeft(int arr[], int len) {
    int score = 0;
    int write = 0;
    int pending = 0;

    for (int i = 0; i < len; i++) {
        int v = arr[i];
        if (v == 0) continue;

        if (pending == 0) {
            pending = v;
        }
        else if (pending == v) {
            int merged = v * 2;
            arr[write++] = merged;
            score += merged;
            pending = 0;
        }
        else {
            arr[write++] = pending;
            pending = v;
        }
    }

    if (pending != 0) {
        arr[write++] = pending;
    }

    while (write < len) {
        arr[write++] = 0;
    }

    return score;
}
*/

// 向左移动
int moveLeft(int board[4][4]) {
    int score = 0;
    for (int i = 0; i < 4; i++) {
        score += compressLeft(board[i], 4);
    }
    return score;
}

// 向右移动
int moveRight(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 可以先把每行翻转，调用 compressLeft，再翻转回来
    int row[LEN];
    for (int r = 0; r < LEN; r++) {
        for (int i = 0; i < LEN; i++) {
            row[i] = board[r][LEN - 1 - i];
        }
        score += compressLeft(row, LEN);
        for (int i = 0; i < LEN; i++) {
            board[r][LEN - 1 - i] = row[i];
        }
    }
    return score;
}

// 向上移动
int moveUp(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 可以提取每一列作为临时数组，调用 compressLeft，再放回去
    int col[LEN];
    for (int c = 0; c < LEN; c++) {
        for (int i = 0; i < LEN; i++) {
            col[i] = board[i][c];
        }
        score += compressLeft(col, LEN);
        for (int i = 0; i < LEN; i++) {
            board[i][c] = col[i];
        }
    }
    return score;
}

// 向下移动
int moveDown(int board[4][4]) {
    int score = 0;
    // TODO: 提示 - 类似向上，但需要先翻转列
    int col[LEN];
    for (int c = 0; c < LEN; c++) {
        for (int i = 0; i < LEN; i++) {
            col[i] = board[LEN - 1 - i][c];
        }
        score += compressLeft(col, LEN);
        for (int i = 0; i < LEN; i++) {
            board[LEN - 1 - i][c] = col[i];
        }
    }
    return score;
}

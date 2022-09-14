#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int>> Block;
int map[500][500];
int h, w;

std::vector<Block> blocks {
    Block {
        {1, 1, 1, 1}
    },

    Block {
        {1},
        {1},
        {1},
        {1}
    },

    Block {
        {1, 1},
        {1, 1},
    },

    Block {
        {1, 0},
        {1, 0},
        {1, 1},
    },

    Block {
        {0, 1},
        {0, 1},
        {1, 1},
    },

    Block {
        {1, 1, 1},
        {1, 0, 0},
    },

    Block {
        {1, 1, 1},
        {0, 0, 1},
    },

    Block {
        {1, 1},
        {0, 1},
        {0, 1},
    },

    Block {
        {1, 1},
        {1, 0},
        {1, 0},
    },

    Block {
        {0, 0, 1},
        {1, 1, 1},
    },

    Block {
        {1, 0, 0},
        {1, 1, 1},
    },

    Block {
        {1, 0},
        {1, 1},
        {0, 1},
    },

    Block {
        {0, 1, 1},
        {1, 1, 0},
    },
    
    Block {
        {0, 1},
        {1, 1},
        {1, 0},
    },

    Block {
        {1, 1, 0},
        {0, 1, 1},
    },

    Block {
        {1, 1, 1},
        {0, 1, 0},
    },

    Block {
        {0, 1, 0},
        {1, 1, 1},
    },

    Block {
        {1, 0},
        {1, 1},
        {1, 0},
    },

    Block {
        {0, 1},
        {1, 1},
        {0, 1},
    },
};

int GetMax(const Block& b)
{
    int bHeight = b.size();
    int bWidth = b[0].size();

    int maxScore = 0;
    for (int row = 0; row < h - bHeight + 1; ++row)
    {
        for (int col = 0; col < w - bWidth + 1; ++col)
        {
            int score = 0;
            for (int i = 0; i < bHeight; ++i)
                for (int j = 0; j < bWidth; ++j)
                    score += b[i][j] * map[row + i][col + j];
            maxScore = std::max(maxScore, score);
        }
    }

    return maxScore;
}

int main()
{
    scanf("%d %d", &h, &w);

    for (int row = 0; row < h; ++row)
        for (int col = 0; col < w; ++col)
            scanf("%d", &map[row][col]);

    int result = 0;
    for (Block& b : blocks)
        result = std::max(result, GetMax(b));
    printf("%d", result);
}
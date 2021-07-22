#include <iostream>
#include <queue>
#include <functional>

struct Lecture {
    int number, start, end, assigned;

    Lecture(int n, int s, int e) {
        number = n;
        start = s;
        end = e;
    }

    Lecture() : Lecture(0, 0, 0) {}
};

struct Room {
    int end, number;

    Room(int e, int n) {
        end = e;
        number = n;
    }

    Room() : Room(0, 0) {}
};

struct LectureHeapComparer {
    bool operator()(const Lecture* l1, const Lecture* l2) const {
        if (l1->start != l2->start) {
            return l1->start > l2->start;
        }
        return l1->end > l2->end;
    }
};

struct RoomHeapComparer {
    bool operator()(const Room& r1, const Room& r2) const {
        return r1.end > r2.end;
    }
};

Lecture lecs[100000];

int main() {
    int n;
    scanf("%d", &n);

    std::priority_queue<Lecture*, std::vector<Lecture*>, LectureHeapComparer> q;
    std::priority_queue<Room, std::vector<Room>, RoomHeapComparer> rooms;
    rooms.emplace(0, 1);

    for (int i = 0; i < n; ++i) {
        int num, start, end;
        scanf("%d %d %d", &num, &start, &end);
        lecs[num-1] = Lecture(num, start, end);
        q.push(lecs+num-1);
    }
    
    while (!q.empty()) {
        Lecture* lec = q.top();
        q.pop();

        auto room = rooms.top();
        if (room.end <= lec->start) {
            rooms.pop();
            lec->assigned = room.number;
        } else {
            lec->assigned = (int)rooms.size() + 1;
        }
        rooms.emplace(lec->end, lec->assigned);
    }

    printf("%d\n", (int)rooms.size());
    for (int i = 0; i < n; ++i) {
        printf("%d\n", lecs[i].assigned);
    }

    return 0;
}
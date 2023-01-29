// 구현 참고 : kks227 님
// https://blog.naver.com/PostView.nhn?blogId=kks227&logNo=221411526404&redirect=Dlog&widgetTypeCall=true&directAccess=false

#include <algorithm>

const int RANGE = 100001; // x, y의 최대 범위
const int POINT_COUNT = 10001; // 쿼리에서 다루는 점의 개수
const int MAX_DEPTH = 18; // 세그먼트 트리의 최대 높이. log2(RANGE) 보다 커야 함.
const int INIT_COUNT = 1 << MAX_DEPTH; // 트리 초기화에 사용되는 노드의 개수
const int TOTAL_COUNT = INIT_COUNT + RANGE * MAX_DEPTH; // 프로그램 전체에서 사용되는 노드의 개수

struct Node
{
    int value; // 이 노드가 나타내는 값 (주로 구간 합)
    int start, end; // 이 노드가 포함하는 구간 [start, end)
    int num; // 노드의 번호
    int left, right; // 이 노드의 왼쪽 자식과 오른쪽 자식의 번호
    
    Node(int s, int e, int n) : value(0), start(s), end(e), num(n), left(-1), right(-1) {}
    Node() : Node(-1, -1, -1) {}
};

class PST
{
private:
    int treeCount; // 현재 트리의 개수
    int nodeCount; // 현재 노드의 개수
    int root[POINT_COUNT]; // i번째 트리의 루트 노드 번호
    Node nodeArr[TOTAL_COUNT];

    int AddNode(Node& prev, int y, int add, int s, int e)
    {
        // 노드의 구간이 y를 포함하지 않는다면 갱신하지 않고 이전 노드를 돌려줌.
        if (e <= y || y < s)
            return prev.num;
        
        Node& curr = nodeArr[nodeCount] = Node(s, e, nodeCount);
        ++nodeCount;

        // 만약 추가하는 노드가 리프라면?
        if (s + 1 == e)
            curr.value = prev.value + add;
        // 만약 추가하는 노드가 인터널 노드라면?
        else
        {
            int mid = (s + e) / 2;
            curr.left = AddNode(nodeArr[prev.left], y, add, s, mid);
            curr.right = AddNode(nodeArr[prev.right], y, add, mid, e);
            curr.value = nodeArr[curr.left].value + nodeArr[curr.right].value;
        }

        return curr.num;
    }

    int Sum(Node& curr, int s, int e)
    {
        if (e <= curr.start || curr.end <= s)
            return 0;
        if (s <= curr.start && curr.end <= e)
            return curr.value;
        
        return Sum(nodeArr[curr.left], s, e) + Sum(nodeArr[curr.right], s, e);
    }

public:
    PST(): treeCount(0), nodeCount(0)
    {
        std::fill(root, root + POINT_COUNT, -1);
        // 0번 트리를 비어있는 포화 이진 트리 구축 후 0번 트리로 설정
        root[treeCount++] = Init(0, INIT_COUNT / 2);
    }

    // 비어있는 포화 이진 트리를 구축하고 이것의 번호를 반환
    int Init(int s, int e)
    {
        Node& top = nodeArr[nodeCount] = Node(s, e, nodeCount);
        ++nodeCount;

        if (s + 1 < e)
        {
            int mid = (s + e) / 2;
            top.left = Init(s, mid);
            top.right = Init(mid, e);
        }

        return top.num;
    }

    // 새 트리를 만들면서 인덱스 y인 리프 노드에 add 만큼 더함
    void AddNode(int y, int add)
    {
        root[treeCount] = AddNode(nodeArr[root[treeCount - 1]], y, add, 0, INIT_COUNT / 2);
        ++treeCount;
    }

    // tIndex 번째 트리의 구간 [s, e)의 합을 구함
    int Sum(int tIndex, int s, int e)
    {
        return Sum(nodeArr[root[tIndex]], s, e);
    }
};
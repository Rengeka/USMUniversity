def conflicts(state):
    h = 0
    for i in range(len(state)):
        for j in range(i+1, len(state)):
            if state[i] == -1 or state[j] == -1:
                continue
            if state[i] == state[j] or abs(state[i]-state[j]) == abs(i-j):
                h += 1
    return h

def is_goal(state):
    return -1 not in state and conflicts(state) == 0

def neighbors(state):
    r = state.index(-1)
    res = []
    for c in range(8):
        s = state.copy()
        s[r] = c
        if conflicts(s) == 0:
            res.append(s)
    return res

def dfs(state):
    if is_goal(state):
        return state
    for n in neighbors(state):
        res = dfs(n)
        if res:
            return res
    return None

import heapq
def astar(start):
    pq = []
    heapq.heappush(pq, (conflicts(start), start))
    while pq:
        f, state = heapq.heappop(pq)
        if is_goal(state):
            return state
        for n in neighbors(state):
            g = 8 - n.count(-1)
            h = conflicts(n)
            heapq.heappush(pq, (g+h, n))
    return None

start = [-1]*8
print("DFS:", dfs(start))
print("A* :", astar(start))
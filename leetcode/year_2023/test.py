from heapq import heappush, heappop

def min_laundry_time(N: int, M: int, L: int, D: int, W: list) -> int:
    washers = [(0, W[i]) for i in range(N)]
    dryers =  [] * M
    for _ in range(L):
        wash_end, wash_time = heappop(washers)
        dry_start = max(wash_end, min(dryers))
        dry_end = dry_start + D
        heappush(washers, (wash_end + wash_time, wash_time))
        dryers[dryers.index(min(dryers))] = dry_end
    return max(dryers)
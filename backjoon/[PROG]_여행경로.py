def solution(tickets):
    answer = []
    tick = []
    used = [0] * len(tickets)
    for start ,end in tickets:
        tick.append([end, start])
    tick.sort()

    def dfs(now, visit,  result):
        if len(result) != 0:
            return result
        
        if 0 not in used:
            return visit
        
        for x in range(len(tickets)):
            if used[x] == 0:
                if tick[x][1] == now:
                    used[x] = 1
                    result = dfs(tick[x][0], visit + [tick[x][0]], result)
                    used[x] = 0
        return result
                    
    answer = dfs('ICN', ['ICN'], [])
    
    return answer
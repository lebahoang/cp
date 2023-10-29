class Solution:
    def printAnswer(self, n, ans):
        cur = []
        for i in range(n):
            t = ''
            for j in range(n):
                t += ans[i][j]
            cur.append(t)
        return cur
    def getKey(self, n, ans):
        cur = []
        for i in range(n):
            t = ''
            for j in range(n):
                t += ans[i][j]
            cur.append(t)
        return cur
    def checkValid(self, a, b, n, cur):
        cnt = 0
        for j in range(n):
            if cur[a][j] == 'Q':
                cnt += 1
        if cnt > 0:
            return False
        cnt = 0
        for i in range(n):
            if cur[i][b] == 'Q':
                cnt += 1
        if cnt > 0:
            return False
        
        x = a
        y = b
        cnt = 0
        while x >= 0 and x < n and y >= 0 and y < n:
            if cur[x][y] == 'Q':
                cnt += 1
            x += 1
            y += 1
        if cnt > 0:
            return False
        x = a
        y = b
        cnt = 0
        while x >= 0 and x < n and y >= 0 and y < n:
            if cur[x][y] == 'Q':
                cnt += 1
            x += 1
            y -= 1
        if cnt > 0:
            return False
        x = a
        y = b
        cnt = 0
        while x >= 0 and x < n and y >= 0 and y < n:
            if cur[x][y] == 'Q':
                cnt += 1
            x -= 1
            y -= 1
        if cnt > 0:
            return False
        x = a
        y = b
        cnt = 0
        while x >= 0 and x < n and y >= 0 and y < n:
            if cur[x][y] == 'Q':
                cnt += 1
            x -= 1
            y += 1
        if cnt > 0:
            return False
        return True
    def go(self, i, n, did,  cur, rs):
        if i == n:
            val = self.printAnswer(n, cur)
            key = ','.join(val)
            if key not in rs:
                print(key)
                # print('--------')
                rs[key] = val
            return
        for b in range(n):
            if self.checkValid(i, b, n, cur):
                cur[i][b] = 'Q'
                val = self.getKey(n, cur)
                key = ','.join(val)
                if key not in did:
                    did[key] = 1
                    self.go(i+1, n, did, cur, rs)
                cur[i][b] = '.'
    def solveNQueens(self, n: int) -> list[list[str]]:
        did = {}
        rs = {}
        cur = [['.' for _ in range(n)] for _ in range(n)]
        self.go(0, n, did, cur, rs)
        return rs.values()
    
x = Solution()
print(x.solveNQueens(13))
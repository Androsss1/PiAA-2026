
def minDistance(word1: str, word2: str,replace : int,insert: int,delete: int,change: int) -> int:
    n = len(word1)
    m = len(word2)
    if m < n:
        n,m = m,n
        word1 ,word2 = word2,word1

    dp = [[0] * (m+1) for _ in range(n+1)]

    dp[0][0] = 0

    for i in range(1,n+1):
        dp[i][0] = delete + dp[i-1][0]
        
    for j in range(1,m+1):
        dp[0][j] = insert + dp[0][j-1]
        
    for i in range(1,n+1):
        for j in range(1,m+1):
            if word1[i-1] == word2[j-1]:
                dp[i][j] = dp[i-1][j-1]
            else:
                changed = float("inf")
                if j >1: changed = change + dp[i-1][j-2]
                dp[i][j] = min(
                    changed,
                    replace + dp[i-1][j-1],
                    delete + dp[i-1][j],
                    insert + dp[i][j-1],
                )
    print_matrix(dp,word1,word2)
    return dp[n][m]



def print_matrix(dp, s1, s2):
    print("    ", " ".join(f"{c:>3}" for c in " " + s2))
    for i, row in enumerate(dp):
        char = " " if i == 0 else s1[i-1]
        print(f"{char:>3}", " ".join(f"{v:>3}" for v in row))




if __name__ == "__main__":
    replace,insert,delete,change = map(int,input().split())
    w1 = input()
    w2 = input()
    ans = minDistance(w1,w2,replace,insert,delete,change)
    print(ans)
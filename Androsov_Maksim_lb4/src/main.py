

def prefix_func(p):
    n = len(p)
    arr = [0] * n
    for i in range(1,n):
        j = arr[i-1]
        while j > 0 and p[i] !=p[j]:
            j = arr[j-1]
        if p[i] == p[j]: j +=1 
        arr[i] = j 

    return arr 




def kmp_search(p, t):
    arr = prefix_func(p)
    n = len(t)
    m = len(p)
    ans = []

    j = 0
    for i in range(n):
        while j > 0 and t[i] != p[j]:
            j = arr[j-1]
        
        if t[i] == p[j]: 
            j +=1 

        if j == m: 
            ans.append(i - m + 1)
            j = arr[j-1]
    
    return ans





if __name__ == "__main__":
    p = input().strip()
    t = input().strip() 
    ans = kmp_search(p,t)
    if len(ans) == 0: print(-1)
    else: print(",".join(map(str,ans)))



def prefix_func(p):
    n = len(p)
    arr = [0] * n

    for i in range(1, n):
        j = arr[i - 1]
        while j > 0 and p[i] != p[j]:
            j = arr[j - 1]
        if p[i] == p[j]:
            j += 1
        arr[i] = j

    print("\n prefix array")
    print(*arr)
    print(" ")
    return arr


def kmp_search(p, t):
    arr = prefix_func(p)
    n = len(t)
    m = len(p)
    ans = []

    j = 0
    for i in range(n):
        print(f"i={i}, j={j}, t[i]='{t[i]}', p[j]='{p[j]}'")
        while j > 0 and t[i] != p[j]:
            j = arr[j - 1]
            print(f"  j shifted to {j}")

        if t[i] == p[j]:
            j += 1
            print(f"  match, j={j}")
        else:
            print(f"  no match")

        if j == m:
            ans.append(i - m + 1)
            print(f"  found match at index {i - m + 1}")
            j = arr[j - 1]
            print(f"  j reset to {j}")

    return ans


if __name__ == "__main__":
    p = input().strip()
    t = input().strip()
    ans = kmp_search(p, t)
    if len(ans) == 0:
        print(-1)
    else:
        print(",".join(map(str, ans)))

def minDistance(
    word1: str, word2: str, replace: int, insert: int, delete: int, change: int
) -> int:
    n = len(word1)
    m = len(word2)

    # Для удобства делаем word1 короче
    if m < n:
        n, m = m, n
        word1, word2 = word2, word1

    dp = [[0] * (m + 1) for _ in range(n + 1)]
    dp[0][0] = 0

    for i in range(1, n + 1):
        dp[i][0] = delete + dp[i - 1][0]

    for j in range(1, m + 1):
        dp[0][j] = insert + dp[0][j - 1]

    for i in range(1, n + 1):
        for j in range(1, m + 1):
            print(f"\n--- dp[{i}][{j}] ---")
            print(
                f"Сравнение: '{word1[i - 1]}' (из {word1}) vs '{word2[j - 1]}' (из {word2})"
            )

            if word1[i - 1] == word2[j - 1]:
                print(f"Символы совпали")
                dp[i][j] = dp[i - 1][j - 1]
                print(f"  dp[{i}][{j}] = dp[{i - 1}][{j - 1}] = {dp[i][j]}")
            else:
                print(f"Символы НЕ совпали")

                # Вычисляем все варианты
                changed = float("inf")
                if j > 1:
                    changed = change + dp[i - 1][j - 2]
                    print(f"  change({change}+{dp[i - 1][j - 2]}) = {changed}")

                replace_cost = replace + dp[i - 1][j - 1]
                print(f"  replace({replace}+{dp[i - 1][j - 1]}) = {replace_cost}")

                delete_cost = delete + dp[i - 1][j]
                print(f"  delete({delete}+{dp[i - 1][j]}) = {delete_cost}")

                insert_cost = insert + dp[i][j - 1]
                print(f"  insert({insert}+{dp[i][j - 1]}) = {insert_cost}")

                dp[i][j] = min(changed, replace_cost, delete_cost, insert_cost)
                print(f"  min = {dp[i][j]}")

    print_matrix(dp, word1, word2)
    print(f"\nОтвет: {dp[n][m]}")

    return dp[n][m]


def print_matrix(dp, s1, s2):
    """Аккуратный вывод матрицы"""
    # Заголовок
    print("\n     ", end="")
    for j, ch in enumerate(" " + s2):
        print(f"{ch:^5}", end="")
    print("\n     " + "-" * (6 * (len(s2) + 1)))

    # Строки матрицы
    for i in range(len(dp)):
        if i == 0:
            label = "  "
        else:
            label = s1[i - 1]
        print(f"{label:>2} |", end="")
        for j in range(len(dp[0])):
            if dp[i][j] == float("inf"):
                print(f" {'∞':^5}", end="")
            else:
                print(f" {dp[i][j]:^5}", end="")
        print()


if __name__ == "__main__":
    replace, insert, delete, change = map(
        int, input("Стоимости (replace insert delete change): ").split()
    )
    w1 = input("Первая строка: ")
    w2 = input("Вторая строка: ")

    ans = minDistance(w1, w2, replace, insert, delete, change)

def height(n, m):
    h, bk = 0, 1
    for i in range(1, n + 1):
        bk = bk * m // i
        h += bk 
        m -= 1
    return h

print(height(10, 2))


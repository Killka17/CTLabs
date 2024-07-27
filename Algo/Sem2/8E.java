import java.util.*;

public class Main {
    static class Acc {
        static final int N = 100000 + 9;
        static int[] sz = new int[N];
        static int[][] f = new int[N][20];
        static int[] d = new int[N];
        static List<Integer>[] G = new List[N];

        static {
            for (int i = 0; i < N; i++) {
                G[i] = new ArrayList<>();
            }
        }

        static void dfs(int u, int fa) {
            d[u] = d[fa] + 1;
            f[u][0] = fa;
            sz[u] = 1;
            for (int i = 0; f[u][i] != 0; i++) {
                f[u][i + 1] = f[f[u][i]][i];
            }
            for (int v : G[u]) {
                if (v != fa) {
                    dfs(v, u);
                    sz[u] += sz[v];
                }
            }
        }

        static int LCA(int x, int y) {
            if (d[x] < d[y]) {
                int temp = x;
                x = y;
                y = temp;
            }
            for (int i = 18; i >= 0; i--) {
                if (d[f[x][i]] >= d[y]) {
                    x = f[x][i];
                }
            }
            if (x == y) {
                return x;
            }
            for (int i = 18; i >= 0; i--) {
                if (f[x][i] != f[y][i]) {
                    x = f[x][i];
                    y = f[y][i];
                }
            }
            return f[x][0];
        }

        static void work() {
            Scanner scanner = new Scanner(System.in);
            int n = scanner.nextInt();
            int m;
            int x, y, z;
            for (int i = 1; i < n; i++) {
                x = scanner.nextInt();
                y = scanner.nextInt();
                G[x].add(y);
                G[y].add(x);
            }
            dfs(1, 0);
            m = scanner.nextInt();
            while (m-- > 0) {
                x = scanner.nextInt();
                y = scanner.nextInt();
                if ((d[x] + d[y]) % 2 != 0) {
                    System.out.println("0");
                } else {
                    if (d[x] < d[y]) {
                        int temp = x;
                        x = y;
                        y = temp;
                    }
                    z = (d[x] + d[y]) / 2 - d[LCA(x, y)] - 1;
                    for (int i = 18; i >= 0; i--) {
                        if ((z >> i & 1) != 0) {
                            x = f[x][i];
                            y = f[y][i];
                        }
                    }
                    if (d[x] != d[y]) {
                        System.out.println(sz[f[x][0]] - sz[x]);
                    } else {
                        System.out.println(n - sz[x] - sz[y]);
                    }
                }
            }
            scanner.close();
        }
    }

    public static void main(String[] args) {
        Acc.work();
    }
}

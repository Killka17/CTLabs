import java.io.*;
import java.util.*;

public class Main {
    static int n, l;
    static List<List<Integer>> adj;
    static int timer;
    static int[] tin, tout, height, g;
    static long[] a, dp;
    static int[][] up;

    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out));

        n = Integer.parseInt(br.readLine());
        a = new long[n];
        String[] aValues = br.readLine().split(" ");
        for (int i = 0; i < n; i++) {
            a[i] = Long.parseLong(aValues[i]);
        }
        n++; // Increment n to match the 1-based indexing used in the original code

        adj = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            adj.add(new ArrayList<>());
        }

        for (int i = 0; i < n - 2; i++) {
            String[] edge = br.readLine().split(" ");
            int x = Integer.parseInt(edge[0]);
            int y = Integer.parseInt(edge[1]);
            adj.get(x).add(y);
            adj.get(y).add(x);
        }

        preprocess(1);

        int m = Integer.parseInt(br.readLine());
        for (int i = 0; i < m; i++) {
            String[] query = br.readLine().split(" ");
            int x = Integer.parseInt(query[0]);
            int y = Integer.parseInt(query[1]);
            int ancestor = lca(x, y);
            long ans = dp[x] + dp[y] - 2 * dp[ancestor] + a[ancestor - 1];
            bw.write(ans + "\n");
        }
        bw.flush();
    }

    static void dfs(int v, int p, long sum) {
        sum += a[v - 1];
        dp[v] = sum;
        g[v] = p;
        height[v] = height[p] + 1;
        tin[v] = ++timer;
        up[v][0] = p;
        for (int i = 1; i <= l; i++) {
            up[v][i] = up[up[v][i - 1]][i - 1];
        }

        for (int u : adj.get(v)) {
            if (u != p) {
                dfs(u, v, sum);
            }
        }
        tout[v] = ++timer;
    }

    static boolean isAncestor(int u, int v) {
        return tin[u] <= tin[v] && tout[u] >= tout[v];
    }

    static int lca(int u, int v) {
        if (isAncestor(u, v)) {
            return u;
        }
        if (isAncestor(v, u)) {
            return v;
        }
        for (int i = l; i >= 0; i--) {
            if (!isAncestor(up[u][i], v)) {
                u = up[u][i];
            }
        }
        return up[u][0];
    }

    static void preprocess(int root) {
        tin = new int[n];
        tout = new int[n];
        height = new int[n];
        g = new int[n];
        dp = new long[n];
        timer = 0;
        l = (int) Math.ceil(Math.log(n) / Math.log(2));
        up = new int[n][l + 1];
        dfs(root, root, 0);
    }
}

#include <cstdio>
#include <cstdlib>
#include <cstring>
#define N 100000

struct edge {
	int next, node;
};
struct map {
	int head[N + 1], tot;
	edge e[N + 1];
	map() { tot = 0; }
	inline void addedge(int x, int y) {
		e[++tot].next = head[x];
		e[tot].node = y;
		head[x] = tot;
	}
} fail, queries;
//Forward stars, one for fail pointer tree and one for queries
const int root = 1;
struct node {
	int f, son[26], fail;
} t[N + 1];
//Trie tree
char s[N + 1];
//Entry string
int len, tot = root, strs = 0, m;
int strNode[N + 1];
//Corresponding trie node for a string
int queue[N + 1];
int head[N + 1], tail[N + 1], count = 0;
//DFS sequence
int arr[N + 1];
//Binary indexed tree, storing how many nodes of string y are in a certain node and its subtrees
int ans[N + 1];
//Stores the answer to each of the queries

inline int query(int x) {
	int ret = 0;
	for (; x; x -= x & (-x)) {
		ret += arr[x];
	}
	return ret;
}

inline void modify(int x, int d) {
	for (; x <= count; x += x & (-x)) {
		arr[x] += d;
	}
}

void dfs(int x) {
	head[x] = ++count;
	for (int i = fail.head[x]; i; i = fail.e[i].next) {
		dfs(fail.e[i].node);
	}
	tail[x] = count;
}

int main() {
	gets(s);
	len = strlen(s);
	int now = root;
	//Read queries and build queries graph
	scanf("%d", &m);
	for (int x, y, i = 0; i < m; ++i) {
		scanf("%d%d", &x, &y);
		queries.addedge(y, x);
	}
	//Build trie tree
	for (int i = 0; i < len; ++i) {
		if (s[i] == 'P') { strNode[++strs] = now; }
		else if (s[i] == 'B') { now = t[now].f; }
		else {
			if (t[now].son[s[i] - 'a']) { now = t[now].son[s[i] - 'a']; }
			else {
				int cur = now;
				t[now = t[now].son[s[i] - 'a'] = ++tot].f = cur;
			}
		}
	}
	//Construct fail pointers and build fail pointer tree
	int l = 0, r = -1;
	for (int i = 0; i < 26; ++i) {
		if (t[root].son[i]) {
			queue[++r] = t[root].son[i];
			fail.addedge(root, queue[r]);
			t[queue[r]].fail = root;
		}
	}
	for (; l <= r; ++l) {
		for (int i = 0; i < 26; ++i)
			if (t[queue[l]].son[i]) {
				queue[++r] = t[queue[l]].son[i];
				for (now = t[queue[l]].fail; now != root && !t[now].son[i]; now = t[now].fail) ;
				t[queue[r]].fail = t[now].son[i] ? t[now].son[i] : root;
				fail.addedge(t[queue[r]].fail, queue[r]);
			}
	}
	//Construct DFS sequence of fail pointer tree
	dfs(root);
	//Traverse through trie tree while enumerating y string
	now = root, strs = 0;
	for (int qs, i = 0; i < len; ++i) {
		if (s[i] == 'B') {
			modify(head[now], -1);
			now = t[now].f;
		}
		else if (s[i] != 'P') {
			now = t[now].son[s[i] - 'a'];
			modify(head[now], 1);
		}
		else {
			for (int x = queries.head[++strs]; x; x = queries.e[x].next) {
				ans[x] = query(tail[strNode[queries.e[x].node]]) - query(head[strNode[queries.e[x].node]] - 1);
			}
		}
	}
	for (int i = 1; i <= m; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}
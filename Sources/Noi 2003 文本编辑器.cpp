/*首先建立一棵伸展树，要记录size以便快速定位。为了方便，在树中插入一个虚拟的头节点，以后每次Move到第k个字符之后只需变成把第k+1个元素Splay到根位置。以后根结点就是光标位置了（光标前面的一个元素）。

////例如1 2 3 4 5 6,如果光标在4后面,那么4就是根结点 k+1是因为有一个虚拟的头结点,由于这个虚拟的结点永远不会用到,而又是第一个插入的,这导致第1个字符前面还有一个元素,所以第k个字符是第k+1个元素


插入一段字符串，要先把这段字符串建成一个Splay，怎么建都行，我是把它猥琐地建成了一条链。如果当前光标位置是最后一位，直接把新建 的树接到根节点右子树。否则把根结点的后继节点Splay到根节点右子树的根位置，接下来把新建的树接到根节点右子树根节点的左子树下面。这种插入的方法 常数较小，时间复杂度为O(L*logN)。要注意维护size。

删除也很容易，如果根结点的位置为k，要删除的长度为len，把第k+len+1这个元素Splay到根结点的右子树根位置，然后把它的左子树删掉就行了。特殊的，如果第k+len+1个元素不存在，只需把根节点的右子树全部删除。

输出一段字符串可以效仿删除，只不过不用删掉，而是把它输出出来。极不建议用递归实现中序遍历的输出，因为Splay可能很不平衡，这样有 可能爆掉系统堆栈，所以要手动模拟栈实现。但是这种方法有些复杂了，其实可以一个一个得查找出来输出，经尝试这样不会增加很多的运行时间，却使程序缩短了 不少。
*/
/*
 * Problem: NOI2003 editor
 * Author: Guo Jiabao
 * Time: 2009.5.17 16:56
 * State: Solved
 * Memo: Splay 线性建树插入 线性输出
*/
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
using namespace std;
const int MAXS = 1024 * 1024 * 2;
struct SplayTree {
	struct SplayNode {
		SplayNode *left, *right, *father;
		int size, value;
		int lsize() {return left ? left->size : 0;}
		int rsize() {return right ? right->size : 0;}
	};
	SplayNode *root, SS[MAXS], *Stack[MAXS];
	int SC, Spos[MAXS];
	SplayNode *newSplayNode(int value, SplayNode *f) {
		SS[SC].left = SS[SC].right = 0;
		SS[SC].father = f;
		SS[SC].size = 1;
		SS[SC].value = value;
		SC++;
		return SS + SC - 1;
	}
	void init() {
		SC = 0;
		root = newSplayNode('#', 0);
	}
	void Update(SplayNode *x) {
		x->size = x->lsize() + x->rsize() + 1;
	}
	/*  以x.father进行右旋
	    下面的是左旋*/
	void Zig(SplayNode *x) {
		SplayNode *y = x->father;
		y->left = x->right;
		if (x->right) {
			x->right->father = y;
		}
		x->father = y->father;
		if (y->father) {
			if (y->father->left == y) {
				y->father->left = x;
			}
			else {
				y->father->right = x;
			}
		}
		y->father = x;
		x->right = y;
		Update(y);
		Update(x);
	}
	void Zag(SplayNode *x) {
		SplayNode *y = x->father;
		y->right = x->left;
		if (x->left) {
			x->left->father = y;
		}
		x->father = y->father;
		if (y->father) {
			if (y->father->left == y) {
				y->father->left = x;
			}
			else {
				y->father->right = x;
			}
		}
		y->father = x;
		x->left = y;
		Update(y);
		Update(x);
	}
	void Splay(SplayNode *x, SplayNode *f) {
		while (x->father != f) {
			if (x->father->father == f) {
				if (x == x->father->left) {
					Zig(x);
				}
				else {
					Zag(x);
				}
			}
			else if (x->father->father->left == x->father) {
				if (x == x->father->left) {
					Zig(x->father), Zig(x);
				}
				else {
					Zag(x), Zig(x);
				}
			}
			else {
				if (x == x->father->right) {
					Zag(x->father), Zag(x);
				}
				else {
					Zig(x), Zag(x);
				}
			}
		}
		if (f == 0) {
			root = x;
		}
	}
	/*  把位置为k+i的元素splay到右子树的根结点上
	    将根结点后一个字符splay到根结点的右子树上*/
	void Select(int k, SplayNode *f) {
		SplayNode *x = root;
		for (int l; k != (l = x->lsize()) + 1/*左结点个数+根节点 刚好为在这边需要选择的k的个数 */ ;) {
			if (k <= l) { //第k+i个元素不在其左子树中
				x = x->left;
			}
			else {
				k -= l + 1; //在右子树中选择到其的k-(l+1)个数
				x = x->right;
			}
		}
		Splay(x, f);
	}
	void Insert(int *Str, int len) {
		SplayNode *x = newSplayNode(Str[1], 0), *r, *y;
		r = x;
		for (int i = 2; i <= len; i++) {
			x->right = newSplayNode(Str[i], x);
			x = x->right;
		}
		if (root->right) {
			//这里select是为了把root.right.left的全部元素都放到root.right.right中,这样这插入一棵新子树就可以保证其位置全部大于后面的而小于根结点
			//+2可以保证其选择到的一定是最左边的结点,其左结点个数为0,没有比其小的
			//将根结点的字符后一个splay到其右结点上
			Select(root->lsize() + 2, root);
			y = root->right;
			y->left = r;
		}
		else {
			y = root;
			y->right = r;
		}
		r->father = y;
		for (; x; x = x->father) {
			Update(x);
		}
	}
	void Delete(int len) {
		if (root->lsize() + 2 + len <= root->size) {
			Select(root->lsize() + 2 + len, root);
			root->right->left = 0;
			Update(root->right);
		}
		else {
			root->right = 0;
		}
		Update(root);
	}
	void Get(int len) {
		SplayNode *x = root;
		int k = x->lsize() + 1;
		for (int i = 1; i <= len; i++) {
			Select(k + i, root);
			putchar(root->right->value);
		}
		putchar('\n');
	}
} Splay;
int N, Str[MAXS], Position;
void init() {
	freopen("editor2003.in", "r", stdin);
	freopen("editor2003.out", "w", stdout);
	scanf("%d", &N);
	Splay.init();
}
void solve() {
	int i, c, t, l;
	char Cmd[10];
	for (i = 1; i <= N; i++) {
		while ((c = getchar()) == 10 || c == 13); ungetc(c, stdin);
		for (t = 0; (c = getchar()) != ' ' && c != 10 && c != 13;) {
			Cmd[++t] = c;
		}
		switch (Cmd[1]) {
		case 'M':
			scanf("%d", &t);
			//你懂得了
			Splay.Select(t + 1, 0);
			Position = t + 1;
			break;
		case 'P':
			Splay.Select(--Position, 0);
			break;
		case 'N':
			Splay.Select(++Position, 0);
			break;
		case 'I':
			scanf("%d", &l);
			for (t = 0; t < l;) {
				while ((c = getchar()) == 10 || c == 13);
				Str[++t] = c;
			}
			Splay.Insert(Str, l);
			break;
		case 'D':
			scanf("%d", &l);
			Splay.Delete(l);
			break;
		case 'G':
			scanf("%d", &l);
			Splay.Get(l);
			break;
		}
	}
}
int main() {
	init();
	solve();
	return 0;
}

<<<<<<< HEAD
/*æ¯æ¬¡ï¼Œä»Žæœ€å·¦ä¸‹çš„ä¸€ä¸ªç‚¹å¼€å§‹ï¼ˆè¿™ä¸ªç‚¹ä¸€å®šåœ¨å¤–å›´ï¼‰ï¼Œä¸æ–­å‘å·¦è¡Œèµ°ï¼Œç›´åˆ°å›žåˆ°èµ·ç‚¹ã€‚
è¿™æ ·ä¸€å®šå¯ä»¥å¾—åˆ°ä¸€ä¸ªåœˆã€‚åœ¨è¿™ä¸ªåœˆä¸Šå‡ºçŽ°2æ¬¡çš„è¾¹ï¼Œå°±æ˜¯è¦è¾“å‡ºçš„è¾¹ã€‚
å’Œå‰¥æ´‹è‘±çš®ä¸€æ ·ï¼Œä¸€å±‚ä¸€å±‚çš„åˆ åœˆã€‚

å…¶å®žè¿™é¢˜çš„è¾¹æ²¡æœ‰å¿…è¦ä¸Žåæ ‡è½´å¹³è¡Œï¼Œè¿™æ ·å¾ˆæœ‰è¿·æƒ‘æ€§ï¼Œå¯¼è‡´å¤§å®¶æƒ³å›¾è®ºç®—æ³•ï¼ˆå¹¶æŸ¥é›†, BFSç­‰ï¼‰ã€‚
å› ä¸ºè¿™é¢˜ä¸éœ€è¦è¾“å‡ºå¤šå°‘å°æ—¶åŽå®ŒæˆæŽ¨å¢™ï¼Œå°±ä¸ç”¨æ±‚æœ€çŸ­è·¯ã€‚
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAX_N = 100000;

int n, m;
pair<int, int> p[MAX_N];
pair<int, int> graph[MAX_N][4];
int order[MAX_N];
int stamp[MAX_N * 2];
int curStamp;

bool walk(int s)
{
	curStamp++;
	int d = stamp[graph[s][0].second] >= curStamp ? 0 :
	stamp[graph[s][1].second] >= curStamp ? 1 : -1;
	if (d == -1) return false;
	for (int i = s; d += 3; d %= 4)
	{
		while (stamp[graph[i][d % 4].second] < curStamp) d++;
		stamp[graph[i][d % 4].second] =
		stamp[graph[i][d % 4].second] == curStamp ? -1 : curStamp;
		i = graph[i][d % 4].first;
		if (i == s) break;
	}
	return true;
}
bool lessThan(int i, int j)
{
	return p[i] < p[j];
}
/*
å½“jçš„æ¨ªåæ ‡å¤§äºŽi (first),åˆ™è¿”å›ž0,åœ¨içš„å³è¾¹
åœ¨å·¦è¾¹æ—¶,è¿”å›ž2

åœ¨içš„ä¸Šé¢æ—¶,è¿”å›ž1
åœ¨içš„ä¸‹é¢æ—¶,è¿”å›ž3

åæ ‡ä¸ºç¬›å¡å°”åæ ‡ç³»çš„åæ ‡
æœªç»éªŒè¯*/
int getDirection(int i, int j)
{
	return (p[i] > p[j]) * 2 + (p[i].first == p[j].first);
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &p[i].first, &p[i].second);
		order[i] = i;
	}
	sort(order, order + n, lessThan);
	memset(graph, 0, sizeof(graph));
	scanf("%d", &m);
	for (int k = 1; k <= m; k++)
	{
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		graph[i][getDirection(i, j)] = make_pair(j, k);
		graph[j][getDirection(j, i)] = make_pair(i, k);
	}

	memset(stamp, 1, sizeof(stamp));
	stamp[0] = -1;
	curStamp = 0;
	for (int i = 0; i < n; i++)
	while (walk(order[i]));

	printf("%d\n", count(stamp + 1, stamp + m + 1, -1));
	for (int k = 1; k <= m; k++)
		if (stamp[k] == -1)
	printf("%d\n", k);
	return 0;
}
=======
/*Ã¿´Î£¬´Ó×î×óÏÂµÄÒ»¸öµã¿ªÊ¼£¨Õâ¸öµãÒ»¶¨ÔÚÍâÎ§£©£¬²»¶ÏÏò×óÐÐ×ß£¬Ö±µ½»Øµ½Æðµã¡£
ÕâÑùÒ»¶¨¿ÉÒÔµÃµ½Ò»¸öÈ¦¡£ÔÚÕâ¸öÈ¦ÉÏ³öÏÖ2´ÎµÄ±ß£¬¾ÍÊÇÒªÊä³öµÄ±ß¡£
ºÍ°þÑó´ÐÆ¤Ò»Ñù£¬Ò»²ãÒ»²ãµÄÉ¾È¦¡£

ÆäÊµÕâÌâµÄ±ßÃ»ÓÐ±ØÒªÓë×ø±êÖáÆ½ÐÐ£¬ÕâÑùºÜÓÐÃÔ»óÐÔ£¬µ¼ÖÂ´ó¼ÒÏëÍ¼ÂÛËã·¨£¨²¢²é¼¯, BFSµÈ£©¡£
ÒòÎªÕâÌâ²»ÐèÒªÊä³ö¶àÉÙÐ¡Ê±ºóÍê³ÉÍÆÇ½£¬¾Í²»ÓÃÇó×î¶ÌÂ·¡£
*/

#include <algorithm>
#include <cstdio>
using namespace std;

const int MAX_N = 100000;

int n, m;
pair<int, int> p[MAX_N];
pair<int, int> graph[MAX_N][4];
int order[MAX_N];
int stamp[MAX_N * 2];
int curStamp;

bool walk(int s)
{
	curStamp++;
	int d = stamp[graph[s][0].second] >= curStamp ? 0 :
	stamp[graph[s][1].second] >= curStamp ? 1 : -1;
	if (d == -1) return false;
	for (int i = s; d += 3; d %= 4)
	{
		while (stamp[graph[i][d % 4].second] < curStamp) d++;
		stamp[graph[i][d % 4].second] =
		stamp[graph[i][d % 4].second] == curStamp ? -1 : curStamp;
		i = graph[i][d % 4].first;
		if (i == s) break;
	}
	return true;
}
bool lessThan(int i, int j)
{
	return p[i] < p[j];
}
int getDirection(int i, int j)
{
	return (p[i] > p[j]) * 2 + (p[i].first == p[j].first);
}
int main()
{
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%d%d", &p[i].first, &p[i].second);
		order[i] = i;
	}
	sort(order, order + n, lessThan);
	memset(graph, 0, sizeof(graph));
	scanf("%d", &m);
	for (int k = 1; k <= m; k++)
	{
		int i, j;
		scanf("%d%d", &i, &j);
		i--, j--;
		graph[i][getDirection(i, j)] = make_pair(j, k);
		graph[j][getDirection(j, i)] = make_pair(i, k);
	}

	memset(stamp, 1, sizeof(stamp));
	stamp[0] = -1;
	curStamp = 0;
	for (int i = 0; i < n; i++)
	while (walk(order[i]));

	printf("%d\n", count(stamp + 1, stamp + m + 1, -1));
	for (int k = 1; k <= m; k++)
		if (stamp[k] == -1)
	printf("%d\n", k);
	return 0;
}
>>>>>>> origin/master

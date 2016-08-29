{这是NOI的第一道交互式题，貌似很复杂，但实际上不难，只要仔细分析。


//在找裁判的时候,ask(a,b)与ask(b,a)不同
//b是星星队的话,ask1会返回1,而ask2会返回0
//如果是月亮队的,ask1返回0,ask2返回1

//神奇的脑洞，怎么想到的
分析可以发现，对于两个人a,b，只要a,b均不是裁判，Ask(a,b,0)，如果回答Yes则a,b同属于一队，否则a,b不同属于一队，所以Ask(a,b,0)一定等于Ask(b,a,0)。因此我们可以以此判断出裁判，如果Ask(a,b,0)不等于Ask(b,a,0)，则a,b中有一个是裁判。于是我们可以分别正着和倒着问一圈，找出唯一的一组Ask(a,b,0)不等于Ask(b,a,0)，则a为裁判，而且可以判断出b所属队伍，进而判断出所有人所属队伍，这样每个人都只问了两遍。

晕，找不到C++版的交互库，害我还得写Pascal，真不舒服。


 * Problem: NOI2002 child
 * Author: Guo Jiabao
 * Time: 2009.5.19 20:05
 * State: Solved
 * Memo: 交互式提问 逻辑判断
}
program child;
uses childlib;
const
    MAX=1000;
var
    N,M,T:integer;
    belong,ansp,ansn:array [1..MAX] of integer;

procedure solve;
var
    i,a,b,k:integer;
begin
    GetNM(N,M);
    T:=N+M+1;
    for i:=1 to T do
    begin
        a:=i;b:=i+1;
        if i=T then b:=1;
        ansn[i]:=Ask(a,b,0);
    end;
    for i:=T downto 1 do
    begin
        a:=i;b:=i-1;
        if i=1 then b:=T;
        ansp[i]:=Ask(a,b,0);
    end;
    for i:=1 to T do
    begin
        a:=i;b:=i+1;
        if i=T then b:=1;
        if ansn[a]<>ansp[b] then
        begin
            belong[a]:=2;
            if ansn[a]=1 then
                belong[b]:=0
            else
                belong[b]:=1;
            k:=b;b:=b+1;if b>T then b:=1;
            while a<>b do
            begin
                if ansn[k]=1 then
                    belong[b]:=belong[k]
                else
                    belong[b]:=1-belong[k];
                k:=b;b:=b+1;if b>T then b:=1;
            end;
            break;
        end;
    end;
end;

procedure print;
var
    i:integer;
begin
    for i:=1 to T do
        Answer(belong[i]);
end;

begin
    solve;
    print;
end.
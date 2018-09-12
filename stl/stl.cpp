sort(a,a+len);
len=unique(a,a+len)-a;
for (int i=0;i<n;++i)
{
    int x,y;
    x=lower_bound(a,a+len,st[i])-a;
    y=lower_bound(a,a+len,en[i])-a;
    solve(x,y,op[i]);
}

//ʵ�ʾ����ź�ϵͳ��ʱ����Ƶ����˵ķ������źŵľ�������ʽ�������֣��������һ����˼ 
#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>> 
#define Pi acos(-1.0)//����Pi��ֵ
#define N 200000
using namespace std;
struct complex //���帴���ṹ��
{
  double re,im;
  complex(double r=0.0,double i=0.0)
  {  re=r,im=i; }  //��ʼ��
   //������������ 
  complex operator +(complex o)
  { return complex(re+o.re,im+o.im);}
  complex operator -(complex o)
  { return complex(re-o.re,im-o.im);}
  complex operator *(complex o)
  { return complex(re*o.re-im*o.im,re*o.im+im*o.re);}
}x1[N],x2[N];
char a[N/2],b[N/2];
int sum[N];    //�洢���Ľ��

void BRC(complex *y,int len)//�����Ʒ�ת����
{
  int i,j,k;
  for(i=1,j=len/2;i<len-1;i++)
  {
     if(i<j)swap(y[i],y[j]);//i<j��ֻ֤����һ��
     k=len/2;
     while(j>=k)
     {
       j-=k;k=k/2;
     }
   if(j<k)j+=k;
  }
}
void FFT(complex *y,int len ,double on)//on=1��ʾ˳��-1��ʾ��
{
  int i,j,k,h;
  complex u,t;
  BRC(y,len);
  for(h=2;h<=len;h<<=1)//���Ʋ���
  {
      //��ʼ����λ����
    complex wn(cos(on*2*Pi/h),sin(on*2*Pi/h));
    for(j=0;j<len;j+=h)//������ʼ�±�
    {
      //��ʼ����������
        complex w(1,0);
        for(k=j;k<j+h/2;k++)
        {
            u=y[k];
            t=w*y[k+h/2];
            y[k]=u+t;
            y[k+h/2]=u-t;
            w=w*wn;//������������
        }    
    }
  }
if(on==-1)
   for(i=0;i<len;i++) //��FFT(IDFT)
       y[i].re/=len;

}
int main()
{
    int len1,len2,len,i;
  while(scanf("%s%s",a,b)!=EOF)
  { 
     len1=strlen(a);
     len2=strlen(b);
     len=1;
//�����������2*n
     while(len<2*len1||len<2*len2)len<<=1;//�����൱��len=len*2
//���ô洢
     for(i=0;i<len1;i++)
     { x1[i].re=a[len1-1-i]-'0';x1[i].im=0.0;}
     for(;i<len1;i++)  //����������ʼ��Ϊ0
     {x1[i].re=x1[i].im=0.0;}
     for(i=0;i<len2;i++)
     { x2[i].re=b[len2-1-i]-'0';x2[i].im=0.0;}
     for(;i<len2;i++)  //����������ʼ��Ϊ0
     {x2[i].re=x2[i].im=0.0;}
//FFT��ֵ
     FFT(x1,len,1);//FFT(a) 1��ʾ˳ -1��ʾ��
     FFT(x2,len,1);//FFT(b)
//��ˣ��������x1
     for(i=0;i<len;i++)
         x1[i]=x1[i]*x2[i];
//��ֵ����FFT��IDTF��
     FFT(x1,len,-1);

//ϸ�ڴ���
     for(i=0;i<len;i++)
         sum[i]=x1[i].re+0.5;//��������
     for(i=0;i<len;i++)     //��λ
     {
       sum[i+1]+=sum[i]/10;
       sum[i]%=10;
     }
//���
     len=len1+len2-1;
     while(sum[len]<=0&&len>0)len--;//�������λ
     for(i=len;i>=0;i--)   //�������
      cout<<sum[i];
      cout<<endl;
  }
return 0;
}

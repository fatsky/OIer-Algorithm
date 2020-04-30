// 代码搬运自https://blog.csdn.net/update7/article/details/70943545
// 欧拉函数φ
//      欧拉定理是用来阐述素数模下，指数同余的性质。
//      欧拉定理：对于正整数N，代表小于等于N的与N互质的数的个数，记作φ(N)
//     欧拉定理引理：
//     ①：如果n为某一个素数p，则φ(p)=p-1;
//     ①证明：因为素数p的质因数只有1和它本身，p和p不为互质，所以φ(p)=p-1；

//     ②：如果n为某一个素数p的幂次，那么φ(p^a)=(p-1)*p^(a-1)；
//     ②因为比p^a小的数有p^a-1个，那么有p^(a-1)-1个数能被p所整除（因为把1~p^a-1的p的倍数都筛去了）
//        所以φ(p)=p^a-1-(p^(a-1)-1)=(p-1)*p^(a-1)

//     ③：如果n为任意两个数a和b的积，那么φ(a*b)=φ(a)*φ(b)
//     ③因为比a*b小的数有a*b-1个，条件是a与b互质
//        那么可以知道，只有那些既满足a与其互质且既满足b与其互质的数满足条件。
//        根据乘法原理，这样的数可以互相组合，那么就有φ(a)*φ(b)个
//        所以可以得知φ(a*b)=φ(a)*φ(b) (注意条件必须满足a和b互质)

//    ④：设n=(p1^a1)*(p2^a2)*……*(pk^ak) (为N的分解式)，那么φ(n)=n*(1-1/p1)*(1-1/p2)*……*(1-1/pk)
//    ④因为各个分解完的p1、p2、……pk均为素数，所以它们均为互质的
//       每次再刨去它们本身，乘起来
//       剩下的运用容斥原理，再根据引理②和引理③就可以得出

//     欧拉定理：a^(φ(m))同余1(mod m) (a与m互质)

// 欧拉函数的线性筛法
// 在线性时间内求出1~N的所有φ
//     有以下三条性质：
//     ①：φ(p)=p-1
//     ②：φ(p*i)=p*φ(i) （当p%i==0时）
//     ③：φ(p*i)=(p-1)*φ(i) (当p%i!=0时)

#include<iostream>
#include<cstring>
#include<cstdio>

using namespace std;

int prime[100001], mark[1000001];       //prime是素数数组，mark为标记不是素数的数组
int tot, phi[100001];                   //phi为φ(),tot为1~i现求出的素数个数

void getphi(int N) {
    phi[1] = 1;                     //φ(1) = 1
    for(int i = 2; i <= N; i++) {   //从2枚举到N
        if(!mark[i]) {              //如果是素数
            prime[++tot] = i;       //那么进素数数组，指针加1
            phi[i] = i - 1;         //根据性质1所得
        }
        for(int j = 1; j <= tot; j++) {         //从现求出素数枚举
            if(i * prime[j] > N) break;         //如果超出了所求范围就没有意义了
            mark[i * prime[j]] = 1;             //标记i*prime[j]不是素数
            if(i % prime[j] == 0) {             //应用性质2
                phi[i * prime[j]] = phi[i] * prime[j];
                break;
            }
            else phi[i * prime[j]] = phi[i] * phi[prime[j]];    //应用性质3
        }
    }
}


int N;
int main(){
    cin >> N;
    getphi(N);
    for(int i = 1; i <= N; i++){
        cout << i << ":phi ( " << phi[i] << " )" << endl;     //输出phi(i)
    }
    return 0;
}
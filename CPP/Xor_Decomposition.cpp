#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp> // Common file
#include <ext/pb_ds/tree_policy.hpp> // Including tree_order_statistics_node_update
#include <ext/pb_ds/detail/standard_policies.hpp>

using namespace std;
using namespace __gnu_pbds;

// #define  part ..
#define ook order_of_key
#define fbo find_by_order 
#define pb(a) push_back(a)
#define all(a) a.begin(),a.end() 
#define mod 1000000007
#define tot_time cerr << "Runtime is: " << clock() * 1.0 / CLOCKS_PER_SEC << endl;
//#define maxx 200006
#define fixed cout<<fixed<<setprecision(14);
#define ll long long 
#define quick    ios_base::sync_with_stdio(NULL),cin.tie(0);
#define listll vector< long long > 
#define listi vector< int> 
#define pii   pair<int , int> 
#define pll pair<long long , long long > 
#define minheap priority_queue<long long , vector< long long >, greater<long long > >
#define rep(i,a,b) for(int i=a;i<b;i++)
#define memo(a,x ) memset( a, x ,sizeof ( a) )
#define randoms mt19937 rng(26);

const long long oo = 1e18;
double PI = 3.14159265358979323846; 


template  < class  T >
vector< T > readvector  ( T  n ) {  vector < T > arr(n ) ;
	    for( int  i =0; i < n ; i ++ ) cin>>arr[i] ;
		return arr; }


ll gcd(ll a,ll b) { return b?gcd(b,a%b):a;}

ll power( ll a, ll n, ll m= 1000000007){
  ll ans = 1;
  while(n){
  if(n&1)
  {
  ans *= a;
  ans%=m;
  }
  a*=a;
  a%=m;
  n/=2;
  }
  return ans ;
} 


vector< int > prm ;
vector < bool > vsp ;

void prime ( int nn = 100000 ) {
	vsp = vector < bool > ( nn+1, 0 );
	int size_prime = nn;
	for( ll i =2; i*i < size_prime ; i++){
		
		if( vsp[i] == 1)
		continue;
		for(ll j = i*i; j < size_prime ;j+=i){
			
			vsp[j] =1;
			
		}
		
		
	}
	
	for( int i= 2; i < size_prime ; i++)
	if (vsp[i] == 0)
	prm.pb(i);
	
	
}

template < class T > using oset = tree< T , null_type, less  < T  > , rb_tree_tag , tree_order_statistics_node_update > ;

const int maxx = 2e5+26;

int Main(){

   
    ll n ;
    cin>>n;
    ll k;
    cin>>k;
    
    vector< array < ll ,2 > > dp ( n ) ;
    
    vector< ll > val = readvector( n );
    
    vector< vector< int > >adj ( n ) ;
    for( int i =0; i < n-1 ;i ++){
		int a , b;
		cin>>a>>b;
		a--,  b-- ;
		adj[ a ].pb(b);
		adj[ b].pb(a);
	}
   
   function < ll ( int ,int ) > dfs = [ &] ( int u , int par ) {
	   
	   dp[ u] [ 0] =1 ;
	   dp[ u] [1] = 0 ;
	   ll xr = val[ u] ;
	   for( int a: adj[ u] ){
		   
		   if (a != par) {	
			   
			   xr^=dfs( a ,u );
			   ll x= dp[ u][ 0 ] , y = dp[ u][1];
			   dp[ u] [0] = (dp[ a][0]*x +dp[ a][1]*y)%mod;
			   dp[ u] [1] = (dp[ a][1] *x + dp[ a][0]*y)%mod ;
		   }
		   
	   }
	   
	   if ( par!=-1){
		   ll p = (dp[ u][1]+dp[ u][0] )%mod;
		   if( xr==k) dp[ u][1] = p;
		   if ( xr==0) dp[ u][0] = p;
		   
	   }
	   return xr;
	   
   };
    
    ll xr =dfs(0,-1);
    
    ll ans =0 ;
    if ( xr== k ) ans += dp[ 0][0];
    if ( xr ==0 )ans +=dp[ 0][1] ;
    cout<<ans%mod<<endl;
  
return 0;

}

int main(){
 quick;

int t =1; 
//cin>>t;
while(t-- )
 Main();

 return 0;
}


  



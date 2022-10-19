#include <cstdio>
 
typedef long long LL;
 
int N,M,Q;
int Sx,Sy;
int p[6][2];
int NM; 
 
void read() {
	scanf("%d %d %d %d %d", &N, &M, &Q, &Sx, &Sy);
	--Sx; --Sy;
	for (int k = 0; k < 6; ++k)	{
		scanf("%d %d", &p[k][0], &p[k][1]);
	}
	NM = N * M;
}
 
 
int dx[4] = {-1, 1, 0, 0}; 
int dy[4] = {0, 0, -1, 1};
 
 
int dir[6][2] = {
	{0, 1},
	{2, 3},
	{0, 3},
	{3, 1},
	{1, 2},
	{2, 0}
};
 
const int maxNM = 34;
 
LL move[maxNM][6];
const int H = maxNM / 2;
const int HALF = (1 << H) - 1;
int bitcnt[1 << H]; 
LL cross[maxNM]; 
int r6[maxNM]; 
 
void precalc()
{
	
	for (int i = 0; i < M + N; ++i) {
		r6[i] = i % 6;
	}
 
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			for (int k = 0; k < 6; ++k) {
				
				LL grid = 1LL << (M * i + j); 
				
				for (int h = 0; h < 2; ++h) {
					int x = i, y = j;
					while (true) {
						x += dx[dir[k][h]] * p[k][h];
						y += dy[dir[k][h]] * p[k][h];
						if (!(0 <= x && x < N && 0 <= y && y < M)) {
							break;
						}
						grid |= 1LL << (M * x + y);
					}
				}
				move[M * i + j][k] = grid;
			}
		}
	}
 
	
	bitcnt[0] = 0;
	for (int i = 1; i < (1 << H); ++i) {
		bitcnt[i] = bitcnt[i / 2] + i % 2;
	}
 
	
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < M; ++j) {
			int u = M * i + j;
			cross[u] = 0;
 
			
			for (int k = 0; k < N; ++k) {
				cross[u] |= 1LL << (M * k + j);
			}
 
			
			for (int k = 0; k < M; ++k) {
				cross[u] |= 1LL << (M * i + k);
			}
		}
	}
}
 
int BITCNT(LL grid) {
	return bitcnt[grid & HALF] + bitcnt[grid >> H & HALF];
}
 
const int PER = 350000; 
const int SIZE = 700001;
LL grid;
int len; 
LL grids[PER]; 
int ind[SIZE];
int sum[PER]; 
 
void init() {
 
	for (int i = 0; i < SIZE; ++i) {
		ind[i] = -1;
	}
 
	grid = 1LL << (M * Sx + Sy);
 
	ind[grid % SIZE] = 0;
	grids[0] = grid;
	sum[0] = 1;
	len = 1;
}
 
int main() {
 
	read();
	precalc();
	init();
 
	int q = 0, p = 0;
	while (p == 0) {
 
		LL new_grid=0;
		for (int u = 0; u < NM; ++u) {
			
			if (grid & 1LL << u) {
			
				new_grid ^= move[u][BITCNT(grid & cross[u])%6];
			}
		}
		grid = new_grid;
 
	
		grids[len] = grid;
		sum[len] = sum[len - 1] + BITCNT(grid);
 
	
		int pos = grid % SIZE;
		for(;;)
		{
			
			if (ind[pos] < 0) {
				ind[pos] = len;
				++len;
				break;
			} else {
				
				if (grids[ind[pos]] == grid) {
					q = ind[pos];
					p = len;
					break;
				} else {
				
					++pos;
					
					if (pos == SIZE) {
						pos = 0;
					}
				}
			}
		}
	}
 
	int w = p - q; 
	LL period_sum = sum[p] - sum[q];
	for (int i = 0; i < Q; ++i) {
		LL T;
		scanf("%lld", &T);
 
		
		LL ans;
		if (T <= p) {
			ans=sum[T]; 
		} else {
			LL L = (T - q) / w;
			int r = T - L * w;
			ans = sum[r] + L * period_sum;
		}
		printf("%lld\n", ans);
	}
	return 0;
}  

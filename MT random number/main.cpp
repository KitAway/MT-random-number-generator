#include <iostream>
using namespace std;

namespace MT {
	#define n 624
	#define w 32
	#define m 397
	#define r 31

	#define u 11
	#define a 0x9908B0DF
	#define d 0xFFFFFFFF
	#define s 7
	#define b 0x9D2C5680
	#define t 15
	#define c 0xEFC60000
	#define l 18

	#define f 0x6C078965

	int MT[n];
	int index = n+1;
	const unsigned int lower_mask = (1 << r) - 1;
	const unsigned int upper_mask = ~lower_mask;

	inline void seed_mt(int seed)
	{
		index = n;
		MT[0] = seed;
		for (int i = 1; i < n; i++)
		{
			MT[i] = (f*MT[i - 1]) ^ ((MT[i - 1] >> (w - 2)) + i);
		}
	}

	
	inline void twist()
	{
		for (int i = 0; i < n; i++)
		{
			int x = MT[i] & upper_mask + MT[(i + 1) % n] & lower_mask;
			int xA = x >> 1;
			if (x % 2 != 0)
				xA ^= a;
			MT[i] = MT[(i + m) % n] ^ xA;
		}
		index = 0;
	}

	inline int extract_number()
	{
		if (index > n)
		{
			cout << "error" << endl;
			return 0;
		}
		if (index == n)
			twist();
		int y = MT[index];
		y ^= ((y >> u)&d);
		y ^= ((y << s)&b);
		y ^= (y >> l);
		index++;
		return y;
	}
}

int main()
{
	
	const int N = 100000000;
	const int Max = 100;
	int seed = 0;
	MT::seed_mt(seed);
	double sum = 0;
	for (int i = 0; i < N; i++)
	{
		int rng = MT::extract_number()%Max;
		sum += rng;
	}
	//cout << "reference average:" <<  << endl;
	//cout << "pseudo average:" <<  << endl;
	cout << "relative difference is :" << abs(2.0*sum /N / (Max - 1) - 1)*100 <<'%'<< endl;
	return 0;

}

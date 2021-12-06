#include "stdio.h"
#include "stdint.h"
#include "math.h"

typedef struct point
{
	int64_t x;
	int64_t y;
};

//modulo inverse extended Euclid Algorithm
uint64_t modInverse(uint64_t a, uint64_t m)
{
	uint64_t m0 = m;
	int64_t y = 0, x = 1;
	uint64_t q, t;
	if (m == 1) {
		return 0;
	}
	while (a > 1) {
		q = a / m;
		t = m;
		m = a % m;
		a = t;
		t = y;
		y = x - q * y;
		x = t;
	}
	// If x is negative make it positive
	if (x < 0)
		x += m0;
	return x;
}

int64_t p, a, b;

int64_t findmod(int64_t mod, int64_t p)
{
	if (mod >= 0)
	{
		mod = mod % p;
	}
	else
	{
		while (mod < 0)
		{
			mod = mod + p;
		}
	}

	return mod;
}
uint64_t findorderofgenerator(point gen)
{
	int64_t slope;
	int64_t slopedenom, denominverse;
	int64_t order = 2;
	point newgen = { gen.x,gen.y};
	while (!(gen.x == newgen.x && gen.y == ( p - newgen.y)))
	{
		if (gen.x == newgen.x && gen.y == newgen.y)
		{
			slopedenom = 2 * gen.y;
			denominverse = modInverse(slopedenom, p);
			slope = (((3 * gen.x * gen.x) + a) * denominverse);
			slope = findmod(slope, p);
		}
		else
		{
			slopedenom = (newgen.x - gen.x);
			slopedenom = findmod(slopedenom, p);
			denominverse = modInverse(slopedenom, p);
			slope = ((newgen.y - gen.y) * denominverse);
			slope = findmod(slope, p);
		}

		newgen.x = ((slope * slope) - gen.x - newgen.x);
		newgen.x = findmod(newgen.x, p);

		newgen.y = ((slope * (gen.x - newgen.x)) - gen.y);
		newgen.y = findmod(newgen.y, p);

		printf("%lluP is = (%llu,%llu)\n", order, newgen.x, newgen.y);
		order++;
	}
	return order - 1;
}

point findgenerator()
{
	int x = 0, y = 0;
	int left;
	int right;

	int modulo3 = 0;

	point generator = { 0 , 0 };

	uint64_t g = 0;

	while (true && g < (p * p))
	{
		if (modulo3 == 0 || modulo3 == 2)
		{
			x = (x + 1) % p;
		}
		if (modulo3 == 1)
		{
			x = (x - 1) % p;
			y = (y + 1) % p;
		}
		left = y * y;
		left = left % p;
		right = pow(x, 3) + (a * x) + b;
		right = right % p;
		if (left == right)
		{
			generator.x = x;
			generator.y = y;
			break;
		}
		modulo3++;
		if (x == y)
		{
			modulo3 = 0;
		}
		g++;
	}

	return generator;
}

point findmultipleofG(int64_t K, point gen)
{
	int64_t slope;
	int64_t slopedenom, denominverse;
	int64_t order = 2;
	point newgen = { gen.x,gen.y };
	while (!(gen.x == newgen.x && gen.y == (p - newgen.y)))
	{
		if (gen.x == newgen.x && gen.y == newgen.y)
		{
			slopedenom = 2 * gen.y;
			denominverse = modInverse(slopedenom, p);
			slope = (((3 * gen.x * gen.x) + a) * denominverse);
			slope = findmod(slope, p);
		}
		else
		{
			slopedenom = (newgen.x - gen.x);
			slopedenom = findmod(slopedenom, p);
			denominverse = modInverse(slopedenom, p);
			slope = ((newgen.y - gen.y) * denominverse);
			slope = findmod(slope, p);
		}

		newgen.x = ((slope * slope) - gen.x - newgen.x);
		newgen.x = findmod(newgen.x, p);

		newgen.y = ((slope * (gen.x - newgen.x)) - gen.y);
		newgen.y = findmod(newgen.y, p);

		if (order == K)
		{
			break;
		}
		order++;
	}
	return newgen;
}

int main()
{

	point gen;

	printf("The ellyptic curve has the equation y^2 = x^3 + a*x + b  (mod p)\n"
		"enter a prime number ");

	scanf_s("%llu", &p);

	printf("Enter a ");
	scanf_s("%llu", &a);

	printf("Enter b ");
	scanf_s("%llu", &b);

	gen = findgenerator();

	printf("\n");

	printf("generator G is %llu %llu\n", gen.x, gen.y);

	uint64_t order = findorderofgenerator(gen);

	printf("Order of the generator is %llu\n", order);

	printf("Pick a private key for A which is less than %llu\n", order);

	int64_t privatekeyA;
	scanf_s("%lld", &privatekeyA);

	point publickeysentbyA;
	publickeysentbyA = findmultipleofG(privatekeyA,gen);
	printf("Public key of A is (%lld,%lld)\n", publickeysentbyA.x, publickeysentbyA.y);

	printf("Pick a private key for B which is less than %llu\n", order);
	int64_t privatekeyB;
	scanf_s("%lld", &privatekeyB);

	point publickeysentbyB;
	publickeysentbyB = findmultipleofG(privatekeyB,gen);
	printf("Public key of B is (%lld,%lld)\n", publickeysentbyB.x, publickeysentbyB.y);

	int64_t message;
	printf("Enter the message to encrypt which is below %llu\n",p);
	scanf_s("%lld", &message);

	//Encryption
	point mid;
	mid = findmultipleofG(privatekeyA, publickeysentbyB);

	point cipher;
	cipher.x = (message + mid.x) % p;
	cipher.y = (mid.y) % p;

	printf("The cipher text is %lld,%lld\n", cipher.x, cipher.y);

	printf("\n");


	//decryption
	point d;

	point decryptionmid;
	decryptionmid = findmultipleofG(privatekeyB, publickeysentbyA);

	d.x = findmod((cipher.x - decryptionmid.x), p);
	d.y = findmod((cipher.y - decryptionmid.y), p);

	printf("the decrypted message is %lld", d.x);

	getchar();

	return 0;

}



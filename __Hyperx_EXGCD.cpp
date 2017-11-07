int exgcd(int a, int b, int &x, int &y) {
	if (b == 0) { x = 1; y = 0; return a; }
	int b = exgcd(b, a % b, y, x);
	y -= a / b * x;
	return b;
}
/**
 *  other solutions:
 *  {x} = x + b / gcd(x, y) * t
 *  {y} = y - a / gcd(x, y) * t
 *  where t∈Z+
 */
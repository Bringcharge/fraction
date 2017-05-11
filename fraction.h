

struct Fraction
{
	void zeromark(long long &a1, long long &b1)			//分子（引用），分母（引用）
	//调整函数，保证分母大于0，直接对输入进行操作。
	{
		if (b1<0)
		{
			a1 = 0 - a1;
			b1 = 0 - b1;
		}
	}
	long long euclid(long long left, long long right)	//输入： 数字a，数字b。返还：long long类型的最大公约数。
		//欧几里得算法函数，输入两个数字得到最大公约数
	{
		if (left > right) {
			left = left ^ right;
			right = left ^ right;
			left = left ^ right;		//异或交换法
		}

		long long d = 0;
		while (left != 0)
		{
			d = left;
			left = right % left;
			right = d;
		}
		if (d == 0) d = 1;
		return (d);						//这个返回的是最大公约数
	}

	long long L_C_M(long long left, long long right)//变量：数字a，数字a。返还：long long类型的最小公倍数
		//最小公倍数算法。返还值是最小公倍数。
	{
		return (left*right / euclid(left, right) == 0 ? 1 : left*right / euclid(left, right));
	}

	void reduction_of_fractions_to_a_common_denominator(long long  &a1, long long &b1, long long &a2, long long &b2)
		//变量分别为：分子1（引用），分母1（引用），分子2（引用），分母2（引用）
		//这东西名字好长啊~通分过程。加减法里面调用了的函数。是直接将两个分数的分母变为相同，分子按比例增长。
	{
		long long t, b11, b22;	//临时变量，没什么意义。还有别问为什么那么难看！硼酸告诉我的多定两个变量。
		b11 = b1; b22 = b2;
		t = L_C_M(b11, b22);
		a1 *= t / b11;
		a2 *= t / b22;
		b1 = t;
		b2 = t;				//符号问题特别麻烦。于是默认为分母是正的，分子是任意
	}

	void reduction(long long &a1, long long &b1)	//变量为：分子（引用），分母（引用）
		//约分函数，直接改变为约分后的分子和分母。
	{
		long long a, b, t;	//依旧没有意义的临时变量
		if (a1 == 0) return;
		a = a1;
		b = b1;
		if (a < 0) a = -a;	//没有用abs，因为懒得define
		if (b < 0) b = -b;
		t = euclid(a, b);	//求最大公约数
		a1 = a1 / t;
		b1 = b1 / t;	//不会用指针所以写得特难看
	}

	void  addition(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)	//输入：分子1，分母1，分子2，分母2，目标分子（引用），目标分母（引用）
		//加法函数，将 分数1 和 分数2 进行加法运算并且约分，得到的结果给 目标分子 和 目标分母
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		reduction_of_fractions_to_a_common_denominator(a1, b1, a2, b2);
		outa = a1 + a2;
		outb = b1;
		reduction(outa, outb);
	}

	void  decrease(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)//输入：分子1，分母1，分子2，分母2，目标分子（引用），目标分母（引用）
		//减法函数,将 分数1 和 分数2 进行减法运算并且约分（分数1 减 分数2），得到的结果给 目标分子 和 目标分母
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		reduction_of_fractions_to_a_common_denominator(a1, b1, a2, b2);
		outa = a1 - a2;
		outb = b1;
		reduction(outa, outb);
	}

	void multiplication(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)//输入：分子1，分母1，分子2，分母2，目标分子（引用），目标分母（引用）
		//减法函数,将 分数1 和 分数2 进行乘法运算并且约分，得到的结果给 目标分子 和 目标分母
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		outa = a1*a2;
		outb = b1*b2;
		reduction(outa, outb);
	}

	void division(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)  //输入：分子1，分母1，分子2，分母2，目标分子（引用），目标分母（引用）
		//减法函数,将 分数1 和 分数2 进行除法运算并且约分（分数1 除以 分数2），得到的结果给 目标分子 和 目标分母
	{
		a2 = a2^b2;
		b2 = a2^b2;
		a2 = a2^b2;		//异或交换法
		zeromark(a1, b1);
		zeromark(a2, b2);
		outa = a1*a2;
		outb = b1*b2;
		reduction(outa, outb);
	}

	long long fenzi;
	long long fenmu;
	void yuefen()
	{
		reduction(fenzi, fenmu);
	}
	Fraction operator * (Fraction &rhs)
	{
		Fraction ans;
		multiplication(fenzi, fenmu, rhs.fenzi, rhs.fenmu, ans.fenzi, ans.fenmu);
		return ans;
	}
	Fraction operator - (Fraction &rhs)
	{
		Fraction ans;
		decrease(fenzi, fenmu, rhs.fenzi, rhs.fenmu, ans.fenzi, ans.fenmu);
		return ans;
	}
	Fraction operator / (Fraction &rhs)
	{
		Fraction ans;
		division(fenzi, fenmu, rhs.fenzi, rhs.fenmu, ans.fenzi, ans.fenmu);
		return ans;
	}
	Fraction operator + (Fraction &rhs)
	{
		Fraction ans;
		addition(fenzi, fenmu, rhs.fenzi, rhs.fenmu, ans.fenzi, ans.fenmu);
		return ans;
	}
	Fraction(){ fenzi = 0; fenmu = 1; }
};
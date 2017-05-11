

struct Fraction
{
	void zeromark(long long &a1, long long &b1)			//���ӣ����ã�����ĸ�����ã�
	//������������֤��ĸ����0��ֱ�Ӷ�������в�����
	{
		if (b1<0)
		{
			a1 = 0 - a1;
			b1 = 0 - b1;
		}
	}
	long long euclid(long long left, long long right)	//���룺 ����a������b��������long long���͵����Լ����
		//ŷ������㷨�����������������ֵõ����Լ��
	{
		if (left > right) {
			left = left ^ right;
			right = left ^ right;
			left = left ^ right;		//��򽻻���
		}

		long long d = 0;
		while (left != 0)
		{
			d = left;
			left = right % left;
			right = d;
		}
		if (d == 0) d = 1;
		return (d);						//������ص������Լ��
	}

	long long L_C_M(long long left, long long right)//����������a������a��������long long���͵���С������
		//��С�������㷨������ֵ����С��������
	{
		return (left*right / euclid(left, right) == 0 ? 1 : left*right / euclid(left, right));
	}

	void reduction_of_fractions_to_a_common_denominator(long long  &a1, long long &b1, long long &a2, long long &b2)
		//�����ֱ�Ϊ������1�����ã�����ĸ1�����ã�������2�����ã�����ĸ2�����ã�
		//�ⶫ�����ֺó���~ͨ�ֹ��̡��Ӽ�����������˵ĺ�������ֱ�ӽ����������ķ�ĸ��Ϊ��ͬ�����Ӱ�����������
	{
		long long t, b11, b22;	//��ʱ������ûʲô���塣���б���Ϊʲô��ô�ѿ�����������ҵĶඨ����������
		b11 = b1; b22 = b2;
		t = L_C_M(b11, b22);
		a1 *= t / b11;
		a2 *= t / b22;
		b1 = t;
		b2 = t;				//���������ر��鷳������Ĭ��Ϊ��ĸ�����ģ�����������
	}

	void reduction(long long &a1, long long &b1)	//����Ϊ�����ӣ����ã�����ĸ�����ã�
		//Լ�ֺ�����ֱ�Ӹı�ΪԼ�ֺ�ķ��Ӻͷ�ĸ��
	{
		long long a, b, t;	//����û���������ʱ����
		if (a1 == 0) return;
		a = a1;
		b = b1;
		if (a < 0) a = -a;	//û����abs����Ϊ����define
		if (b < 0) b = -b;
		t = euclid(a, b);	//�����Լ��
		a1 = a1 / t;
		b1 = b1 / t;	//������ָ������д�����ѿ�
	}

	void  addition(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)	//���룺����1����ĸ1������2����ĸ2��Ŀ����ӣ����ã���Ŀ���ĸ�����ã�
		//�ӷ��������� ����1 �� ����2 ���мӷ����㲢��Լ�֣��õ��Ľ���� Ŀ����� �� Ŀ���ĸ
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		reduction_of_fractions_to_a_common_denominator(a1, b1, a2, b2);
		outa = a1 + a2;
		outb = b1;
		reduction(outa, outb);
	}

	void  decrease(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)//���룺����1����ĸ1������2����ĸ2��Ŀ����ӣ����ã���Ŀ���ĸ�����ã�
		//��������,�� ����1 �� ����2 ���м������㲢��Լ�֣�����1 �� ����2�����õ��Ľ���� Ŀ����� �� Ŀ���ĸ
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		reduction_of_fractions_to_a_common_denominator(a1, b1, a2, b2);
		outa = a1 - a2;
		outb = b1;
		reduction(outa, outb);
	}

	void multiplication(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)//���룺����1����ĸ1������2����ĸ2��Ŀ����ӣ����ã���Ŀ���ĸ�����ã�
		//��������,�� ����1 �� ����2 ���г˷����㲢��Լ�֣��õ��Ľ���� Ŀ����� �� Ŀ���ĸ
	{
		zeromark(a1, b1);
		zeromark(a2, b2);
		outa = a1*a2;
		outb = b1*b2;
		reduction(outa, outb);
	}

	void division(long long a1, long long b1, long long a2, long long b2, long long &outa, long long &outb)  //���룺����1����ĸ1������2����ĸ2��Ŀ����ӣ����ã���Ŀ���ĸ�����ã�
		//��������,�� ����1 �� ����2 ���г������㲢��Լ�֣�����1 ���� ����2�����õ��Ľ���� Ŀ����� �� Ŀ���ĸ
	{
		a2 = a2^b2;
		b2 = a2^b2;
		a2 = a2^b2;		//��򽻻���
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
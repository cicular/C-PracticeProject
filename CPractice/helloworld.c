#include <stdio.h>

// �֐��̃v���g�^�C�v�錾
double avg(double l, double m);
void show(int n1, int n2, int n3);
void swap(int* num1, int* num2);
void pointer();

void main() {
	printf("HelloWorld.\n");
	double r = avg(4.1, 5.7);
	// printf("r = %f", r);

	printf("r�̒l��%f�A�T�C�Y��%dbytes�A�A�h���X��0x%x\n", r, sizeof(double), &r);


	pointer();

	int a = 1, b = 2;
	swap(&a, &b);
	printf("a = %d b = %d \n", a, b);
}


double avg(double l, double m) {
	double result = (l + m) / 2.0;
	return result;
}

void show(int n1, int n2, int n3) {
	printf("a = %d b = %d, c *p = %d\n", n1, n2, n3);
}

// �|�C���^
void pointer(void) {
	int a = 100;
	int b = 200;
	// �����^�̃|�C���^�ϐ�p
	int* p = NULL;
	p = &a;
	show(a, b, *p);

	*p = 300;
	show(a, b, *p);

	p = &b;
	show(a, b, *p);

	*p = 400;
	// p = 400�Ƃ���ƁACPractice.exe (�v���Z�X 4632) �́A�R�[�h -1073741819 �ŏI�����܂����B�ƂȂ��Ă��܂��B
	show(a, b, *p);
}

// �l�̓���ւ�
void swap(int* num1, int* num2) {
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

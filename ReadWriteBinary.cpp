#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void byteSwap(unsigned char* p, uint64_t &u);
void byteSwap2(unsigned char* p, uint64_t &u);
void byteSwap(unsigned char* p, double &u);
void byteSwap2(unsigned char* p, double &u);

int main() {
	ofstream wf("test.dat", ios::out | ios::binary);
	if (!wf) {
		cout << "Cannot open file!" << endl;
		return 1;
	}
	uint64_t I0 = 12345678901234567890ull;
	double pi0 = 3.1415926535897932384626;
	wf.write((char *) &I0, sizeof(I0));
	wf.write((char *)&pi0, sizeof(pi0));
	wf.close();
	if (!wf.good()) {
		cout << "Error occurred at writing time!" << endl;
		return 1;
	}


	ifstream rf("test.dat", ios::out | ios::binary);
	if (!rf) {
		cout << "Cannot open file!" << endl;
		return 1;
	}
	uint64_t I1, I2;
	double pi1, pi2;
	unsigned char p[8],p2[8];
	rf.read((char *)&p, sizeof(uint64_t));
	byteSwap(p, I1);
	byteSwap2(p, I2);
	rf.read((char*)&p2, sizeof(double));
	byteSwap(p2, pi1);
	byteSwap2(p2, pi2);
	rf.close();
	if (!rf.good()) {
		cout << "Error occurred at reading time!" << endl;
		return 1;
	}
	cout << "I1 = " << I1 << endl;
	cout << "I2 = " << I2 << endl;
	cout << "pi1 = " << pi1 << endl;
	cout << "pi2 = " << pi2 << endl;
	return 0;
}

void byteSwap(unsigned char* p, uint64_t &u)
{
	/* // This commented out section can be used to investigate each left shift interpretation of each character
	uint64_t v;
	uint64_t uio;
	memcpy(&uio, p, 8);
	uint64_t io = (uint64_t)uio;
	u = ((uint64_t)p[0] << 0);
	v = ((uint64_t)p[1] << 8);
	u += v;
	v = ((uint64_t)p[2] << 16);
	u += v;
	v = ((uint64_t)p[3] << 24);
	u += v;
	v = ((uint64_t)p[4] << 32);
	u += v;
	v = ((uint64_t)p[5] << 40);
	u += v;
	v = ((uint64_t)p[6] << 48);
	u += v;
	v = ((uint64_t)p[7] << 56);
	u += v;*/
	u =  (((uint64_t)p[0] << 0)
		+ ((uint64_t)p[1] << 8)
		+ ((uint64_t)p[2] << 16)
		+ ((uint64_t)p[3] << 24)
		+ ((uint64_t)p[4] << 32)
		+ ((uint64_t)p[5] << 40)
		+ ((uint64_t)p[6] << 48)
		+ ((uint64_t)p[7] << 56));
}

void byteSwap2(unsigned char* p, uint64_t &u)
{
	u =  (((uint64_t)p[0] << 56)
		+ ((uint64_t)p[1] << 48)
		+ ((uint64_t)p[2] << 40)
		+ ((uint64_t)p[3] << 32)
		+ ((uint64_t)p[4] << 24)
		+ ((uint64_t)p[5] << 16)
		+ ((uint64_t)p[6] << 8)
		+ ((uint64_t)p[7] << 0));
}

void byteSwap(unsigned char* p, double &d)
{
	uint64_t u;
	byteSwap(p, u);
	uint64_t* ptr_u = &u;
	double* ptr_du = (double*)ptr_u;
	d = *ptr_du;
}
void byteSwap2(unsigned char* p, double &d)
{
	uint64_t u;
	byteSwap2(p, u);
	uint64_t* ptr_u = &u;
	double* ptr_du = (double*)ptr_u;
	d = *ptr_du;
}
#include<iostream>
#include<fstream>
#include<string>
using namespace std;

void byteSwap(unsigned char* p, uint64_t &u);
void byteSwap2(unsigned char* p, uint64_t &u);

int main() {
	ofstream wf("test.dat", ios::out | ios::binary);
	if (!wf) {
		cout << "Cannot open file!" << endl;
		return 1;
	}
	uint64_t I0 = 12345678901234567890ull;
	wf.write((char *) &I0, sizeof(I0));
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
	uint64_t I, I2;
	unsigned char p[8];
	rf.read((char *)&p, sizeof(uint64_t));
	byteSwap(p, I);
	byteSwap2(p, I2);
	rf.close();
	if (!rf.good()) {
		cout << "Error occurred at reading time!" << endl;
		return 1;
	}
	cout << "I = " << I << endl;
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

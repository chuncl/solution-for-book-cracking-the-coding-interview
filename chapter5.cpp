// common bit operations: get, set, clear, update bits

bool getBit(int num, int i) {
	return (num & (1 << i)) != 0;
}

int setBit(int num, int i) {
	return num | (1 << i);
}

int clearBit(int num, int i) {
	return num & ~(1 << i);
}

// including i
int clearMSBThroughI(int num, int i) {
	return num & ((1 << i) - 1);
}

// including i
int clearLSBThroughI(int num, int i) {
	return num & ~((i << i + 1) - 1);
}

// clear bit + set bit
int updateBit(int num, int i, int v) {
	return num & ~(1 << i) | (v << i);
}
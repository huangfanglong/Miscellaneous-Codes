#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <openssl/camellia.h>

using namespace std;

int main() {
	
    int all_encrypt = 0, all_decrypt = 0, count = 100000;
    struct timespec start, stop;
    srand (time(NULL));

	// prepare Camellia key 
	CAMELLIA_KEY key;
	unsigned char keyBytes[] = { 0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef,
					   0x01, 0x23, 0x45, 0x67, 0x89, 0xab, 0xcd, 0xef };
					      
	// set the encryption key
	Camellia_set_key(keyBytes, 128, &key);
    
    // example input block: 16 bytes of data
    unsigned char *plaintext = (unsigned char *)"a secret message";	
    // buffer to hold encrypted data
    unsigned char ciphertext[16];
    // buffer to hold decrypted data
    unsigned char deciphertext[17];

    for (int i=0; i<count; i++) {


        clock_gettime(CLOCK_REALTIME, &start);
        // run encryption  
        Camellia_ecb_encrypt(plaintext, ciphertext, &key, CAMELLIA_ENCRYPT);
        
        clock_gettime(CLOCK_REALTIME, &stop);
        
        long start_time = start.tv_sec * 1000000000 + start.tv_nsec ;
        long stop_time = stop.tv_sec * 1000000000 + stop.tv_nsec;
        all_encrypt += stop_time - start_time;

        
        clock_gettime(CLOCK_REALTIME, &start);
        // run decryption
        Camellia_ecb_encrypt(ciphertext, deciphertext, &key, CAMELLIA_DECRYPT);     
        clock_gettime(CLOCK_REALTIME, &stop);
        
        start_time = start.tv_sec * 1000000000 + start.tv_nsec ;
        stop_time = stop.tv_sec * 1000000000 + stop.tv_nsec;
        all_decrypt += stop_time - start_time;
    }

    cout << "Average time used for encryption: " << (all_encrypt/count) << " nanoseconds\n";
    cout << "Average time used for decryption: " << (all_decrypt/count) << " nanoseconds\n";
    return 0;
}




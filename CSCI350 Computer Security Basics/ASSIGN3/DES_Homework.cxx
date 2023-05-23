#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <openssl/des.h>

using namespace std;

int main() {
	
    int all_encrypt = 0, all_decrypt = 0, count = 100000;
    struct timespec start, stop;
    srand (time(NULL));

    // prepare DES key:
    DES_cblock cbc_key = {0xa1,0xb2,0xc5,0xd7,0xe9,0xfb,0x01,0x45};
    DES_key_schedule key;    
    DES_set_key(&cbc_key, &key);
    
    // example input block: 8 bytes of data
    DES_cblock plaintext = {'m','y','s','e','c','r','e','t'};	
    // blocks to hold encrypted and data
    DES_cblock cyphertext, decyphertext;

    for (int i=0; i<count; i++) {
        
        clock_gettime(CLOCK_REALTIME, &start);
        // run encryption
        DES_ecb_encrypt(&plaintext, &cyphertext, &key, DES_ENCRYPT);   
        clock_gettime(CLOCK_REALTIME, &stop);
        
        long start_time = start.tv_sec * 1000000000 + start.tv_nsec ;
        long stop_time = stop.tv_sec * 1000000000 + stop.tv_nsec;
        all_encrypt += stop_time - start_time;
        
        clock_gettime(CLOCK_REALTIME, &start);
        // run decryption
        DES_ecb_encrypt(&cyphertext, &decyphertext, &key, DES_DECRYPT);        
        clock_gettime(CLOCK_REALTIME, &stop);
        
        start_time = start.tv_sec * 1000000000 + start.tv_nsec ;
        stop_time = stop.tv_sec * 1000000000 + stop.tv_nsec;
        all_decrypt += stop_time - start_time;
    }

    cout << "Average time used for encryption: " << (all_encrypt/count) << " nanoseconds\n";
    cout << "Average time used for decryption: " << (all_decrypt/count) << " nanoseconds\n";
    return 0;
}

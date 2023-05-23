#include <openssl/evp.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[])
{
	
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <input_file>" << endl;
        return 1;
    }
    
    ifstream infile(argv[1], ios::binary);
    if (!infile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    //determine input file size
    infile.seekg(0, ios::end);
    streamsize input_size = infile.tellg();
    infile.seekg(0, ios::beg);

    //allocate the buffer dynamically based on the size of the plaintext
    char* input_buffer = new char[input_size];
    if (!input_buffer) {
        cerr << "Error allocating input buffer." << endl;
        infile.close();
        return 1;
    }

    if (!infile.read(input_buffer, input_size)) {
        cerr << "Error reading input file." << endl;
        infile.close();
        delete[] input_buffer;
        return 1;
    }

    infile.close();

    //hash value
    unsigned char md_value[EVP_MAX_MD_SIZE];
    unsigned int md_len;

    //setup and create context
    EVP_MD_CTX *mdctx = nullptr;
    mdctx = EVP_MD_CTX_create();
    if (!mdctx) 
    {
        cerr << "Error creating context." << endl;
        delete[] input_buffer;
        return -1;
    }

	//initialize hash function
	//EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL);
	//implemented a return function in case of failure
    if (EVP_DigestInit_ex(mdctx, EVP_sha256(), nullptr) != 1) 
    {
        cerr << "Error initializing hash function." << endl;
        EVP_MD_CTX_destroy(mdctx);
        delete[] input_buffer;
        return -1;
    }
    
    struct timespec start, stop;
    srand (time(NULL));

	
    //initialize all_encrypt to 0 and set the number of iterations
    int all_encrypt = 0, count = 100;

    //run the encryption 'count' number of times and measure the total time
    for(int i = 0; i < count; i++) {
    //get the start time
    clock_gettime(CLOCK_REALTIME, &start);
    
    //feed data to hash function
    //EVP_DigestUpdate(mdctx, buffer, size);
    if (EVP_DigestUpdate(mdctx, input_buffer, input_size) != 1) 
    {
        cerr << "Error feeding data to hash function." << endl;
        EVP_MD_CTX_destroy(mdctx);
        delete[] input_buffer;
        return -1;
    }

    // get hash value
    // EVP_DigestFinal_ex(mdctx, md_value, &md_len);
    if (EVP_DigestFinal_ex(mdctx, md_value, &md_len) != 1) 
    {
        cerr << "Error getting hash value." << endl;
        EVP_MD_CTX_destroy(mdctx);
        delete[] input_buffer;
        return -1;
    }

	//get the stop time
    clock_gettime(CLOCK_REALTIME, &stop);
    
    //calculate the elapsed time in microseconds
    uint64_t start_time = (start.tv_sec * 1000000 + start.tv_nsec / 1000);
    uint64_t stop_time = (stop.tv_sec * 1000000 + stop.tv_nsec / 1000);
    all_encrypt += stop_time - start_time;
}
	//caalculate the average time and print it out
    cout << "Average time used for encryption: " << std::fixed << std::setprecision(3) << static_cast<double>(all_encrypt) / count << " microseconds\n";
  
    cout << "Message digest is: ";
    for(unsigned int i = 0; i < md_len; i++)
    {
        cout << hex << (int) md_value[i];
    }
    cout << endl;

    // cleanup
    EVP_MD_CTX_destroy(mdctx);
    delete[] input_buffer;
    return 0;
}
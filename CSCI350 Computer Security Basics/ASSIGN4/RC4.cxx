#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>
#include <stdint.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <cmath>
using namespace std;

void handleErrors() {
  ERR_print_errors_fp(stderr);
  abort();
}
  
int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {

  EVP_CIPHER_CTX *ctx;
  int len;
  int ciphertext_len;

  // Create and initialise the context 
  if(!(ctx = EVP_CIPHER_CTX_new())) handleErrors();

  // Initialise the encryption operation. 
  if(1 != EVP_EncryptInit_ex(ctx, EVP_rc4(), NULL, key, iv)) handleErrors();

  // Provide the message to be encrypted, and obtain the encrypted output.
  if(1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) handleErrors();
  ciphertext_len = len;

  // Finalise the encryption. Further ciphertext bytes may be written at this stage.
  if(1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}


int main(int argc, char *argv[]) {

   struct timespec start, stop;
   srand (time(NULL));
    
  //check if there are enough arguments
  if (argc < 3) {
    cout << "Usage: " << argv[0] << " <key> <input_file>" << endl;
    return 1;
  }

  //get key from command line argument
  unsigned char key[16];
  std::string key_arg(argv[1]);
  for (std::string::size_type i = 0; i < key_arg.size(); i += 2) {
    key[i/2] = std::stoi(key_arg.substr(i, 2), nullptr, 16);
  }
  
  const char *input_file = argv[2];
    
  //open the input file for reading
  ifstream in_file(input_file, ios::binary);
  if (!in_file) {
    cout << "Error: could not open input file" << endl;
    return 1;
  }

  //get the size of the input file
  in_file.seekg(0, ios::end);
  int plaintext_len = in_file.tellg();
  in_file.seekg(0, ios::beg);

  //read the plaintext from the input file
  unsigned char *plaintext = new unsigned char[plaintext_len + 1];
  in_file.read((char *)plaintext, plaintext_len);
  plaintext[plaintext_len] = '\0';
  in_file.close();

   //allocate the ciphertext buffer dynamically based on the size of the plaintext
  int ciphertext_len = plaintext_len + EVP_MAX_BLOCK_LENGTH; // add space for padding
  unsigned char *ciphertext = new unsigned char[ciphertext_len];  

    //initialize all_encrypt to 0 and set the number of iterations
    int all_encrypt = 0, count = 100;

    //run the encryption 'count' number of times and measure the total time
    for(int i = 0; i < count; i++) {
    //get the start time
    clock_gettime(CLOCK_REALTIME, &start);
    
    //encrypt the plaintext
    ciphertext_len = encrypt (plaintext, plaintext_len, key, nullptr, ciphertext);
    
    //get the stop time
    clock_gettime(CLOCK_REALTIME, &stop);
    
    //calculate the elapsed time in microseconds
    uint64_t start_time = (start.tv_sec * 1000000 + start.tv_nsec / 1000);
    uint64_t stop_time = (stop.tv_sec * 1000000 + stop.tv_nsec / 1000);
    all_encrypt += stop_time - start_time;
}

  //calculate the average time and print it out
  cout << "Average time used for encryption: " << std::fixed << std::setprecision(3) << static_cast<double>(all_encrypt) / count << " microseconds\n";
  //create the output file name by changing the extension of the input file
  string output_file = input_file;
  output_file.replace(output_file.find_last_of(".") + 1, string::npos, "crypt");

  //open the output file for writing
  ofstream out_file(output_file, ios::binary);
  if (!out_file) {
  cout << "Error: could not create output file" << endl;
  return 1;
  }

  //write the ciphertext to the output file
  int bytes_written = 0;
  bytes_written += ciphertext_len;
  out_file.write((char *)ciphertext, ciphertext_len);
  out_file.close();
  
   cout << "encrypted " << bytes_written << " bytes to " << output_file << endl;

  //free memory
  delete[] plaintext;
  delete[] ciphertext;
  
  return 0;
}

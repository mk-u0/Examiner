#include <util.h>
#include <openssl/evp.h> 
#include <iomanip>
#include <sstream>


using namespace std;

string hashPassword(const string &pass_raw) {
    EVP_MD_CTX* context = EVP_MD_CTX_new();
    const EVP_MD* md = EVP_sha256();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int lengthOfHash = 0;

    if (context == nullptr) return "";

    EVP_DigestInit_ex(context, md, nullptr);
    EVP_DigestUpdate(context, pass_raw.c_str(), pass_raw.size());
    EVP_DigestFinal_ex(context, hash, &lengthOfHash);
    
    EVP_MD_CTX_free(context);

    std::stringstream ss;
    for(unsigned int i = 0; i < lengthOfHash; i++) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    
    return ss.str();
}

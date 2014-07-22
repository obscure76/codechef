#include <stdio.h>
#include <vector>
#include <assert.h>
#include <algorithm>
using std::vector;
using std::pair;
inline unsigned int mod_fast(unsigned long long x,unsigned int m) { return x<m?x:x%m; }
inline unsigned int mod_mul(unsigned int a,unsigned int b,unsigned int m) { return mod_fast((unsigned long long)(a)*b,m); }
unsigned int mod_exp(unsigned int e,unsigned int p,unsigned int m)
{
  unsigned int ans = 1,product = e;
  for(;0 != p;p >>= 1)
  {
    if(p&1)
    {
      ans = mod_mul(ans,product,m);
    }
    product = mod_mul(product,product,m);
  }
  return ans;
}
#include <stdlib.h>
#include <locale>
class byte_in_buffer_t
{
  byte_in_buffer_t(const byte_in_buffer_t&);
  byte_in_buffer_t& operator=(const byte_in_buffer_t&);

  private:

  static const size_t buff_size = 0x1000;
  char _buff[buff_size];
  char* _p;
  char* _end;
  private:
  FILE* _file;
  public:
  byte_in_buffer_t(FILE* in):_p(_buff),_end(_buff),_file(in) { }
  ~byte_in_buffer_t() { ; }
  public:
  unsigned char readchar()
  {
    if(_p == _end)
    {
      _p = _buff;
      _end = _buff + fread(_buff,1,buff_size,_file);
    }
    return *_p++;
  }
  public:
  unsigned readuint()
  {
    unsigned char ch;
    for(;isspace(ch = readchar());) ;
    unsigned result = ch - '0';
    for(;isdigit(ch = readchar());)
      result = 10 * result + ch - '0';
    return result;
  }
};
class byte_out_buffer_t
{
  byte_out_buffer_t(const byte_out_buffer_t&);
  byte_out_buffer_t& operator=(const byte_out_buffer_t&);
  private:
  static const size_t buffer_size = 0x1000;
  static const size_t digit_size = 20;
  private:
  char _buff[buffer_size];
  char *_p;
  char *_end;
  public:
  byte_out_buffer_t():_p(_buff), _end(_buff + buffer_size) { ; }
  ~byte_out_buffer_t() { flush(); }
  public:
  void flush()
  {
    fwrite(_buff,1,_p - _buff,stdout);
    _p = _buff;
  }
  public:
  void put_char(unsigned char c)
  {
    if(_p == _end)
      flush();
    *_p++ = c;
  }
  public:
  void write_uint(unsigned int x)
  {
    char buff[digit_size],*p = buff;
    do{ *p++ = '0'+x%10;x /= 10; } while (x > 0) ;
    do put_char(*--p);while (p != buff);
  }
};
int main()
{
  static const unsigned int min_value = 1;
  static const unsigned int max_value = 100;
  static const unsigned int maxn = 100000;
  static const unsigned int max_prime_count = 30;
  vector<unsigned int> primes;
  primes.reserve(max_value);
  primes.push_back(2);
  for(unsigned int i = 3;i <= max_value;i += 2)
  {
    bool isprime = true;
    for(unsigned int k = 3;k*k <= i && isprime;k += 2)
    {
      if(0 == (i%k))
        isprime = false;
    }
    if(isprime)
      primes.push_back(i);
  }
  size_t prime_count = primes.size();
  assert(prime_count <= max_prime_count);
  vector< vector<size_t> > counts(max_value+1,vector<size_t>(prime_count,0));
  for(unsigned int i = min_value;i <= max_value;++i)
  {
    unsigned int p = i;
    for(size_t k = 0;k < prime_count;++k)
    {
      for(;0 == (p%primes[k]);p /= primes[k])
        ++counts[i][k];
    }
  }
  byte_in_buffer_t input(stdin);
  unsigned int n = input.readuint(),x = 0; // 1 <= n <= 100000
  static size_t accumulation[maxn+1][max_prime_count] = { 0 };
  for(unsigned int i = 1;i <= n;++i)
  {
    x = input.readuint(); // 1 <= x <= 100
    for(size_t k = 0;k < prime_count;++k)
    {
      accumulation[i][k] = accumulation[i-1][k] + counts[x][k];
    }
  }
  byte_out_buffer_t output;
  unsigned int t = input.readuint(); // 1 <= t <= 100000
  for(unsigned int i = 0;i < t;++i)
  {
    unsigned int l = input.readuint(),r = input.readuint(),m = input.readuint(); // 1 <= l <= r <= n,1 <= m <= 1000000000

    unsigned long long ans = 1;
    for(size_t k = 0;k < prime_count;++k)
    {
      unsigned int p = accumulation[r][k];
      if(l >= 1)
        p -= accumulation[l-1][k];
      if(0 == p)
        continue;
      unsigned int x = mod_exp(primes[k],p,m);
      //printf("%d %d %d %d\n",k,p,m,x);
      ans *= x;
      ans %= m;
    }
    output.write_uint(ans);
    output.put_char('\n');
  }
  return 0;
}


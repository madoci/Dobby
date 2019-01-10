int addition(int a, int * b)
{
  return a+*b;
}
int main(void){
  int a = 3;
  int b = 6;
  int result;
  result = addition(a, &b);
  return result;
}

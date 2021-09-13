#if !defined(MODERNIZE_H)
#define MODERNIZE_H

#define CB_INJECT(f1, f2) do{ \
  void temp_func() f2 \
  f1(temp_func); \
}while(0) \

#endif // MODERNIZE_H

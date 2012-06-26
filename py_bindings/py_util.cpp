
#include "py_util.h"
#include "png_util.h"

void assign(Func &f, const Expr &e) {
  f = e;
}

Expr add(Expr a, Expr b) { return a+b; }
Expr sub(Expr a, Expr b) { return a-b; }
Expr neg(Expr a) { return -a; }
Expr mul(Expr a, Expr b) { return a*b; }
Expr div(Expr a, Expr b) { return a/b; }
Expr mod(Expr a, Expr b) { return a%b; }

Expr lt(Expr a, Expr b) { return a < b; }
Expr le(Expr a, Expr b) { return a <= b; }
Expr eq(Expr a, Expr b) { return a == b; }
Expr ne(Expr a, Expr b) { return a != b; }
Expr gt(Expr a, Expr b) { return a > b; }
Expr ge(Expr a, Expr b) { return a >= b; }

Expr and_op(Expr a, Expr b) { return a&&b; }
Expr or_op(Expr a, Expr b) { return a||b; }
Expr invert(Expr a) { return !a; }

Expr iadd(Expr &a, Expr b) { a += b; return a; }
Expr isub(Expr &a, Expr b) { a -= b; return a; }
Expr imul(Expr &a, Expr b) { a *= b; return a; }
Expr idiv(Expr &a, Expr b) { a /= b; return a; }

FuncRef call(Func &a, Expr b) { return a(b); }
FuncRef call(Func &a, Expr b, Expr c) { return a(b, c); }
FuncRef call(Func &a, Expr b, Expr c, Expr d) { return a(b, c, d); }
FuncRef call(Func &a, Expr b, Expr c, Expr d, Expr e) { return a(b, c, d, e); }
FuncRef call(Func &a, const std::vector<Expr> &args) { return a(args); }

Expr call(const UniformImage &a, Expr b) { return a(b); }
Expr call(const UniformImage &a, Expr b, Expr c) { return a(b, c); }
Expr call(const UniformImage &a, Expr b, Expr c, Expr d) { return a(b, c, d); }
Expr call(const UniformImage &a, Expr b, Expr c, Expr d, Expr e) { return a(b, c, d, e); }

void assign(FuncRef &a, Expr b) { a = b; }

#define DEFINE_TYPE(T) void assign(UniformImage &a, Image<T> b) { a = b; }
#include "expand_types.h"
#undef DEFINE_TYPE

#define DEFINE_TYPE(T) void assign(Image<T> &a, DynImage b) { a = b; }
#include "expand_types.h"
#undef DEFINE_TYPE

#define DEFINE_TYPE(T) Image<T> load_png(Image<T> a, std::string b) { return load<T>(b); }
DEFINE_TYPE(uint8_t)
DEFINE_TYPE(uint16_t)
DEFINE_TYPE(uint32_t)
DEFINE_TYPE(float)
DEFINE_TYPE(double)
//#include "expand_types.h"
#undef DEFINE_TYPE

#define DEFINE_TYPE(T) void save_png(Image<T> a, std::string b) { save(a, b); }
DEFINE_TYPE(uint8_t)
DEFINE_TYPE(uint16_t)
DEFINE_TYPE(uint32_t)
DEFINE_TYPE(float)
DEFINE_TYPE(double)
#undef DEFINE_TYPE


//void assign(UniformImage &a, Image<uint8_t> b) { a = DynImage(b); }

/*
void test_blur() {
  UniformImage input(UInt(16), 2, "inputimage");
  Func blur_x("blur_x"), blur_y("blur_y");
  Var x("x"), y("y");

  // The algorithm
  blur_x(x, y) = (input(x-1, y) + input(x, y) + input(x+1, y))/3;
  blur_y(x, y) = (blur_x(x, y-1) + blur_x(x, y) + blur_x(x, y+1))/3;
  
  blur_y.compileToFile("halide_blur");
}


int main() {
    test_blur();
    return 0;
}
*/
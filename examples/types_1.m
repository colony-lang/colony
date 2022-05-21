//
// primitive
//
a: i64 = 1              // i64
a: i64 = 1_i64          // i64
a := 1                  // i64
a := 1_i64              // i64

a: f64 = 1.0            // f64
a: f64 = 1.0_f64        // f64
a := 1.0                // f64
a := 1.0_f64            // f64

a: u8 = 255_u8          // u8
a := 255_u8             // u8

a: bytes = b'abc'       // bytes
a := b'abc'             // bytes
a: bytes = b"abc"       // bytes
a := b"abc"             // bytes

a: str = 'abc'          // str
a := 'abc'              // str
a: str = "abc"          // str
a := "abc"              // str

//
// type alias
//
I64: type = i64
F64: type = f64

x: I64 = 1
r: F64 = 2.0

//
// union type
//
U: type = i64 | f64;
U: union = i64 | f64;

//
// struct type
//
P: struct = (x: f64=0.0, y: f64=0.0)        // struct, has :=
P: type = (x: f64=0.0, y: f64=0.0)          // struct is subtype of type, has :=
p: P = P(1.0, 2.0)                          // P
p: P = P(x=1.0, y=2.0)                      // P
x := p.x
y := p.y

p: tuple = (1.0, 2.0, 3.0, 4.0)             // tuple, hasn't :=
p: object = (1.0, 2.0, 3.0, 4.0)            // tuple is subtupe of object, hasn't :=
x := p[0]
y := p[1]

//
// generic struct
//
G: generic_struct = <X:=type, Y:=type, R:=type>     // generic_type, has :=
G: type = <X:=type, Y:=type, R:=type>               // generic_type is subtype of type, has :=
g: G = G<i64, i64, f64>                             // G
g: G = G<X=i64, Y=i64, R=f64>                       // G
X := G.X
Y := G.Y

//
// generic tuple
//
g: generic_tuple = <i64, i64, f64>          // generic_tuple, hasn't :=
g: generic_tuple = <1, 2, 3, 4>             // generic_tuple, hasn't :=
g: object = <1, 2, 3, 4>                    // generic_tuple is subtype of object, hasn't :=
x := g[0]
y := g[1]

//
// parameterized struct type
//
P: type = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default)
p0: P = P<i64>(1, 2)
p1: P = P<i64>(2, 3)

p0: P<i64> = P<i64>(1, 2)
p0: P<object> = P<i64>(1, 2)

//
// function
//
f := (x: f64, y: f64) -> f64 -> {
    r: f64 = x + y
}

a := f(1.0, 2.0)

//
// parameterized function 1
//
f := <T:=i64 | f64> -> (x: T, y: T) -> T -> {
    r: T = x + y
}

a := f<f64>(1.0, 2.0)

//
// parameterized function 2
//
G := <T:=i64 | f64>

f := G -> (x: T, y: T) -> T -> {
    r: T = x + y
}

a := f<f64>(1.0, 2.0)

//
// parameterized function 3
//
G0 := <T:=i64 | f64>
G1 := <R:=i64 | f64>

f := G0 -> G1 -> (x: T, y: T) -> R -> {
    r: R = x + y
}

a := f<f64><f64>(1.0, 2.0)

//
// parameterized function 4
//
G0 := <T:=i64 | f64>
G1 := <R:=i64 | f64>

f := <...G0, ...G1> -> (x: T, y: T) -> R -> {
    r: R = x + y
}

a := f<f64, f64>(1.0, 2.0)

//
// parameterized function 5
//
G0 := <T:=i64 | f64>
G1 := <R:=i64 | f64>

f := (G0 & G1) -> (x: T, y: T) -> R -> {
    r: R = x + y
}

a := f<f64, f64>(1.0, 2.0)

//
// parameterized function 6
//
G0 := <T:=i64 | f64>
G1 := <R:=i64 | f64>
G := G0 & G1

f := G -> (x: T, y: T) -> R -> {
    r: R = x + y
}

a := f<f64, f64>(1.0, 2.0)

//
// user-defined struct
//
P: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := (
        // __type__ := struct,
        // __bases__ := [object],
        // __name__ := 'P',
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum := (self) -> f64 -> {
            r := self.x + self.y
        },
    ),
)

p0 := P(1.0, 2.0, 3.0)
p1 := P(1.0, 2.0, 3.0)
p2 := p0 + p1
s0 := p0.sum()
s1 := p1.sum()

p0 := P::__type__::__call__(P, 1.0, 2.0, 3.0)
p1 := P::__type__::__call__(P, 1.0, 2.0, 3.0)
p2 := p0::__type__::__add__(p0, p1)
s0 := p0::__type__::sum(p0)
s1 := p1::__type__::sum(p1)

//
// import / if / recursion
//
{ print } := import('io')

fib := (n: int) -> int {
    n <= 1 ? n : fib(n - 1) + fib(n - 2)
}

r := fib(10)
print(r)

//
// Option
//
NoneType: type = (
    __type__ := (
        __type__ := type,
        __bases__ := [struct],
        __name__ := "None",
    )
)

None: NoneType = (
    __type__ := NoneType
)

Some := <V:=type> -> (
    v: V,
)

Option: type = <V:=type> -> (NoneType | Some<V>)

o0: Option<i64> = None
o1: Option<i64> = Some<i64>(1)

o0: Option = None
o1: Option = Some<i64>(1)

o0 := None
o1 := Some<i64>(1)

//
// Result
//
Ok := <V:=type> -> (
    v: V,
)

Err := <E:=type> -> (
    e: E,
)

Result: type = <V:=type, E:=type> -> (Ok<V> | Err<E>)

r0: Result<i64, str> = Ok<i64>(1)
r1: Result<i64, str> = Err<str>("Some error")

r0: Result<i64, str> = Ok<i64>(1)
r1: Result<i64, str> = Err<str>("Some error")

r0 := Ok<i64>(1)
r1 := Err<str>("Some error")

//
// if/else
//
a: Any = 10 % 2 ? { true } : { false }

//
// match 1
//
A: type = int
B: type = float
C: type = A | B
c: C = 1
c: C = 1.1

r = match(c, {
    A: y -> { y },
    B: z -> { z },
    _: () -> { 0 },
})

r = match(c)
    .case(A, y -> { y })
    .case(B, z -> { z })
    .default(_ -> { 0 })

//
// match 2
//
A: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
)

B: struct = (
    z: f64 = 0.0,
    w: f64 = 0.0,
)

C: type = A | B

r = match(c, {
    A: (x, y) -> { x + y },
    B: (z, w) -> { z + w },
    _: () -> { 0 },
})

r = match(c)
    .case(A, (x, y) -> { y })
    .case(B, (z, w) -> { z })
    .default(_ -> { 0 })

//
// range/map/filter/reduce/take_while/drop_while
//
a = range(10)
    .map(n -> { n + 1 })
    .filter(n -> { n % 2 })
    .take_while(n -> { n % 3 })
    .drop_while(n -> { n % 3 })
    .reduce((acc, n) -> { acc + n }, 0)

//
// option
//
a: Option<int> = Some<int>(1)
a: Option<int> = None<int>

r = match(a)
    .case(Some, v -> { v })
    .case(None, _ -> { 0 })
    .default(_ -> { -1 })

//
// result
//
a: Result<V=int, E=str> = Ok<V>(1)
a: Result<V=int, E=str> = Err<E>('Some error')

r = match(a)
    .case(Ok, (v) -> { v })
    .case(Err, (e) -> { 0 })
    .default(() -> { -1 })

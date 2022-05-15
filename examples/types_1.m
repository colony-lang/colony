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
// user-defined struct ???
//
P: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := (
        __type__ := struct,
        __bases__ := [object],
        __name__ := 'P',
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum := (self) -> f64 -> {
            r := self.x + self.y
        },
    ),
)

P: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(
        __type__ = struct,
        __bases__ = [object],
        __name__ = 'P',
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum = (self) -> f64 -> {
            r := self.x + self.y
        },
    ),
)

P: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(struct, [object], 'P',
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum = (self) -> f64 -> {
            r := self.x + self.y
        },
    ),
)

P: struct = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum = (self) -> f64 -> {
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
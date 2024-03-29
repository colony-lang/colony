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

a: str = 'abc'          // str
a := 'abc'              // str

//
// type
//
I64: type = i64
F64: type = f64

//
// tuple
//
P: type = (x: f64=0.0, y: f64=0.0)          // type, has :=
p: P = P(1.0, 2.0)
p: tuple = P(1.0, 2.0)
p: tuple = (1.0, 2.0)                       // tuple, hasn't :=

p0: P = P(1.0, 2.0)
p1: tuple = (2.0, 3.0)                      // tuple, hasn't :=
p2: P = P(p0.x + p1[0], p0.y + p2[1])

P := (x: f64, y: f64, z: f64)
p0 := P(1.0, 2.0, 3.0)
p1 := P(1.0, 2.0, 3.0)
p2 := P(p0.x + p1.x, p0.y + p1.y, p0.z + p1.z)

P: type = (x: f64=0.0, y: f64=0.0)
p: P = P(1.0, 2.0)
p: tuple = P(1.0, 2.0)                      // P.__bases__.has(tuple)
p: tuple = (1.0, 2.0)

// p0: tuple = (x: f64=0.0, y: f64=0.0).__type__.__call__(1.0, 2.0)
p0: tuple = (x: f64=0.0, y: f64=0.0)(1.0, 2.0)
p1: tuple = (x: f64=0.0, y: f64=0.0)(1.0)
p2: tuple = (x: f64=0.0, y: f64=0.0)()

//
// function
//
f := (x: f64, y: f64) -> f64 -> {
    r: f64 = x + y
    r
}

a := f(1.0, 2.0)

//
// function closure
//
f := (x: i64, y: i64) -> i64 -> {
    g := (x: f64, y: f64) -> i64 -> {
        h := (r: f64) -> i64 -> {
            r: i64 = r.to_i64()
        }

        r: i64 = h(x + y)
    }

    r: i64 = g(x.to_f64(), y.to_f64())
}

r: i64 = f(1, 2)
r == 3

//
// object/type
//
type.__type__ == type
type.__bases__ == [object]

object.__type__ == type
object.__bases__ == []

tuple.__type__ == type
tuple.__bases__ == [object]

union.__type__ == type
union.__bases__ == [type]

generic.__type__ == type
generic.__bases__ == [object]

P: type = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := (
        __type__ := type,
        __bases__ := [tuple],
        __name__ := 'P',
        __add__ := (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

P: type = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(
        __type__ = type,
        __bases__ = [tuple],
        __name__ = 'P',
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

P: type = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(type, [tuple], 'P',
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

P: type = (
    x: f64 = 0.0,
    y: f64 = 0.0,
    __type__ := type(
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
    ),
)

p0 := P(1.0, 2.0, 3.0)
p1 := P(1.0, 2.0, 3.0)
// p2 := p0::__type__::__add__(p0, p1)
p2 := p0 + p1

//
// struct 1 ??
//
struct.__type__ == type
struct.__bases__ == [type]

trait.__type__ == type
trait.__bases__ == [type]

Add: type = trait(
    __add__ := (self, other: Self) -> Self -> {
        Self(self.x + other.x, self.y + other.y)
    },
)

Sub: type = trait(
    __sub__ := (self, other: Self) -> Self -> {
        Self(self.x - other.x, self.y - other.y)
    },
)

S: type = struct(
    __bases__ := [Add, Sub], // ??
    x: f64 = 0.0,
    y: f64 = 0.0,
)

//
// union
//
U: union = i64 | f64
U: type = i64 | f64

//
// generic
//
G: type = <X:=Number, Y:=Number, R:=Number>
g: G = G<i64, i64, f64>
g: generic = G<i64, i64, f64>
g: generic = <i64, i64, f64>
g: generic = <1, 2, 3, 4>

//
// generic tuple
//
P: type = <T:=i64 | f64> -> (x: T=T.default, y: T=T.default)
p0: P = P<i64>(1, 2)
p1: P = P<i64>(1, 2)

//
// generic function
//
G: type = <X: type=i64 | f64, Y: type=i64 | f64, R: type=i64 | f64>

f := G -> (x: X, y: Y) -> R -> {
    r: R = x + y
}

f := <X: type=i64 | f64, Y: type=i64 | f64, R: type=i64 | f64> -> (x: X, y: Y) -> R -> {
    r: R = x + y
}

r := f<i64, i64, i64>(1, 2)

//
// generic type
//
G: type = <X: type=i64 | f64, Y: type=i64 | f64, R: type=i64 | f64>

P: type = G -> (
    x: X = X.default,
    y: Y = Y.default,
    __type__ := type(
        __add__ = (self, other: P) -> P -> {
            P(self.x + other.x, self.y + other.y)
        },
        sum = (self) -> R -> {
            r: R = self.x + self.y
        }
    ),
)
